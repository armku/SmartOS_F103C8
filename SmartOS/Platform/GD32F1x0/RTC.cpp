﻿#include "Kernel\TTime.h"
#include "Device\RTC.h"

#include "Platform\stm32.h"

/************************************************ HardRTC ************************************************/

bool RTC_WaitForLastTask2(uint retry = 300)
{
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET && --retry);

	return retry > 0;
}

#ifdef STM32F1
void RTC_Configuration(bool init, bool ext)
{
	/* 备份寄存器模块复位，将BKP的全部寄存器重设为缺省值 */
	if(init) BKP_DeInit();

	if(!ext)
	{
		/* Enable LSI */
		RCC_LSICmd(ENABLE);
		/* 等待稳定 */
		while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

		// 使用内部 32 KHz 晶振作为 RTC 时钟源
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	}
	else
	{
		/* 设置外部低速晶振(LSE)32.768K  参数指定LSE的状态，可以是：RCC_LSE_ON：LSE晶振ON */
		RCC_LSEConfig(RCC_LSE_ON);
		/* 等待稳定 */
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

		// RTC时钟源配置成LSE（外部32.768K）
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	}

	/* 使能RTC时钟 */
	RCC_RTCCLKCmd(ENABLE);

	/* 开启后需要等待APB1时钟与RTC时钟同步，才能读写寄存器 */
	RTC_WaitForSynchro();

	/* 每一次读写寄存器前，要确定上一个操作已经结束 */
	RTC_WaitForLastTask2();

	/* 使能秒中断 */
	//RTC_ITConfig(RTC_IT_SEC, ENABLE);

	/* 每一次读写寄存器前，要确定上一个操作已经结束 */
	//RTC_WaitForLastTask2();

	if(init)
	{
		/* 设置RTC分频器，使RTC时钟为1Hz */
		//if(!ext)
			//RTC_SetPrescaler(31999); /* RTC period = RTCCLK/RTC_PR = (32.000 KHz)/(31999+1) */
		//else
			//RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

		RTC_SetPrescaler(32);	// 为了使用低功耗，时钟为1kHz

		/* 每一次读写寄存器前，要确定上一个操作已经结束 */
		RTC_WaitForLastTask2();
	}
}
#else
void RTC_Configuration(bool init, bool ext)
{
	RTC_WriteProtectionCmd(DISABLE);

	RTC_EnterInitMode();

	RTC_InitTypeDef rtc;
	RTC_StructInit(&rtc);
	rtc.RTC_HourFormat = RTC_HourFormat_24;
	rtc.RTC_AsynchPrediv = 0x7D-1;
	rtc.RTC_SynchPrediv = 0xFF-1;
	RTC_Init(&rtc);

	RTC_ExitInitMode();
	RTC_WriteProtectionCmd(ENABLE);	//初始化完成，设置标志
}

DateTime RTC_GetCounter()
{
	DateTime dt;

	RTC_TimeTypeDef time;
	RTC_GetTime(RTC_Format_BCD, &time);

	dt.Hour		= time.RTC_Hours;
	dt.Minute	= time.RTC_Minutes;
	dt.Second	= time.RTC_Seconds;

	RTC_DateTypeDef date;
	RTC_GetDate(RTC_Format_BCD, &date);

	dt.Year		= date.RTC_Year;
	dt.Month	= date.RTC_Month;
	dt.Day		= date.RTC_Date;

	return dt;
}

void RTC_SetCounter(DateTime dt)
{
	RTC_TimeTypeDef time;
	RTC_TimeStructInit(&time);
	time.RTC_Seconds	= dt.Second;
	time.RTC_Minutes	= dt.Minute;
	time.RTC_Hours		= dt.Hour;
	time.RTC_H12		= RTC_H12_AM;
	RTC_SetTime(RTC_Format_BCD, &time);

	RTC_DateTypeDef date;
	RTC_DateStructInit(&date);
	date.RTC_Date		= dt.Day;
	date.RTC_Month		= dt.Month;
	byte weekdata = dt.DayOfWeek();
	date.RTC_WeekDay	= weekdata > 0 ? weekdata : RTC_Weekday_Sunday;
	date.RTC_Year		= dt.Year;
	RTC_SetDate(RTC_Format_BCD, &date);
}
#endif

static uint g_NextSave;	// 下一次保存Ticks的时间，避免频繁保存

void AlarmHandler(ushort num, void* param);

void HardRTC::Init()
{
	/*****************************/
	/* GD32和STM32最大的区别就是STM32给寄存器默认值，而GD32没有给默认值 */
	/* 虽然RTC靠电池工作，断电后能保持配置，但是在GD32还是得重新打开时钟 */

	/* 启用PWR和BKP的时钟 */
#ifdef STM32F1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
#else
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
#endif

	/* 后备域解锁 */
	PWR_BackupAccessCmd(ENABLE);

	// 下一次保存Ticks的数值，避免频繁保存
	g_NextSave = 0;

	Opened = true;

	if(ReadBackup(0) != 0xABCD)
	{
		RTC_Configuration(true, External);

		WriteBackup(0, 0xABCD);
	}
	else
	{
		//虽然RTC模块不需要重新配置，且掉电后依靠后备电池依然运行
		//但是每次上电后，还是要使能RTCCLK
		RTC_Configuration(false, External);

		// 从RTC还原滴答
		LoadTime();
	}

	if(LowPower)
	{
		EXTI_ClearITPendingBit(EXTI_Line17);
		EXTI_InitTypeDef  exit;
		exit.EXTI_Line		= EXTI_Line17;
		exit.EXTI_Mode		= EXTI_Mode_Interrupt;
		exit.EXTI_Trigger	= EXTI_Trigger_Rising;
		exit.EXTI_LineCmd	= ENABLE;
		EXTI_Init(&exit);

#ifdef STM32F1
		Interrupt.SetPriority(RTCAlarm_IRQn, 0);
		Interrupt.Activate(RTCAlarm_IRQn, AlarmHandler, this);
#endif
	}
}

#ifndef STM32F1
	#define RTC_IT_ALR RTC_IT_ALRA
#endif

void HardRTC::LoadTime()
{
	if(!Opened) return;

	auto& time	= (TTime&)Time;
	DateTime dt	= RTC_GetCounter();
	time.Seconds		= dt.TotalSeconds();
	//time.Milliseconds	= dt.Millisecond;
	time.Milliseconds	= dt.Ms;
}

void HardRTC::SaveTime()
{
	if(!Opened) return;

	if(g_NextSave > 0 && Time.Seconds < g_NextSave) return;
#if TIME_DEBUG
	if(g_NextSave == 0)
	{
		debug_printf("LoadTime: ");
		DateTime::Now().Show(true);

		g_Counter = 0;
	}
#endif

	/* 等待最近一次对RTC寄存器的写操作完成，也即等待RTC寄存器同步 */
	RTC_WaitForSynchro();

	RTC_SetCounter(DateTime::Now());

	// 必须打开时钟和后备域，否则写不进去时间
	// Check if the Power On Reset flag is set
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to BKP Domain */
    //PWR_BackupAccessCmd(ENABLE);

	// 这里对时间要求非常苛刻，不能等待
	RTC_WaitForLastTask2();

	// 每秒钟保存一次
	g_NextSave = Time.Seconds + 5;
}

// 暂停系统一段时间
int HardRTC::Sleep(int ms)
{
	if(!Opened || !LowPower) return ms;

	if(ms <= 0) return 0;
	//int second = ms / 1000;
	//if(second <= 0) return;

#if TIME_DEBUG
	debug_printf("进入低功耗模式 %d 毫秒\r\n", ms);
#endif
	//SaveTime();

	// 打开RTC报警中断
	RTC_ITConfig(RTC_IT_ALR, ENABLE);
    // 设定报警时间
#ifdef STM32F1
    RTC_SetAlarm(RTC_GetCounter() + ms);
	//RTC_SetCounter(0);
	//RTC_SetAlarm(ms);
#else
	RTC_AlarmTypeDef alr;
	RTC_AlarmStructInit(&alr);

	int second = ms / 1000;
	int minute = second / 60;

	// 关闭警报
	RTC_AlarmCmd( RTC_Alarm_A, DISABLE );
	alr.RTC_AlarmTime.RTC_H12		= RTC_H12_AM;
	alr.RTC_AlarmTime.RTC_Hours		= minute / 60;
	alr.RTC_AlarmTime.RTC_Minutes	= minute % 60;
	alr.RTC_AlarmTime.RTC_Seconds	= second % 60;

	// 设置警报
	alr.RTC_AlarmDateWeekDay	= 31;
	alr.RTC_AlarmDateWeekDaySel	= RTC_AlarmDateWeekDaySel_Date;
	alr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;

	RTC_SetAlarm( RTC_Format_BIN, RTC_Alarm_A, &alr );

	// 打开警报中断
	RTC_ITConfig( RTC_IT_ALRA, ENABLE );

	// 打开警报
	RTC_AlarmCmd( RTC_Alarm_A, ENABLE );
#endif
	// 等待写入操作完成
    RTC_WaitForLastTask2();

	Sys.Trace(1);
	// 进入低功耗模式
	//PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
	// 直接进入低功耗，不去控制电源，唤醒以后不需要配置系统时钟
	__WFI();

	//debug_printf("离开低功耗模式\r\n");

	return 0;
}

uint HardRTC::ReadBackup(byte addr)
{
	if(!Opened) return 0;

#ifdef STM32F1
	return BKP_ReadBackupRegister(BKP_DR1 + (addr << 2));
#else
	return RTC_ReadBackupRegister(RTC_BKP_DR0 + (addr << 2));
#endif
}

void HardRTC::WriteBackup(byte addr, uint value)
{
	if(!Opened) return;

#ifdef STM32F1
	BKP_WriteBackupRegister(BKP_DR1 + (addr << 2), value);
#else
	RTC_WriteBackupRegister(RTC_BKP_DR0 + (addr << 2), value);
#endif
}

// 从停止模式醒来后配置系统时钟，打开HSE/PLL，选择PLL作为系统时钟源
void SYSCLKConfig_STOP(void)
{
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  if(RCC_WaitForHSEStartUp() == SUCCESS)
  {
#ifdef STM32F10X_CL
    /* Enable PLL2 */
    RCC_PLL2Cmd(ENABLE);

    /* Wait till PLL2 is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET);
#endif

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08);
  }
}

void AlarmHandler(ushort num, void* param)
{
    SmartIRQ irq;

	Sys.Trace(4);
	//HardRTC* rtc = (HardRTC*)param;

	if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line17);
		// 检查唤醒标志是否设置
		if(PWR_GetFlagStatus(PWR_FLAG_WU) != RESET) PWR_ClearFlag(PWR_FLAG_WU);
		RTC_WaitForLastTask2();
		RTC_ClearITPendingBit(RTC_IT_ALR);
		RTC_WaitForLastTask2();
	}
	//SYSCLKConfig_STOP();
	//rtc->LoadTime();

	debug_printf("离开低功耗模式\r\n");
}
