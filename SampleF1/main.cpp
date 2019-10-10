#include "Sys.h"
#include "Device\Port.h"
#include "Device\SerialPort.h"
#include "Modbus/Slave.h"

SerialPort sp3(COM3);
Slave modbusSlave(&sp3);

void LedTask(void* param)
{
	auto leds = (OutputPort*)param;
	*leds = !*leds;
}

uint OnUsart1Read(ITransport* port, Buffer& bs, void* param, void* param2)
{
	bs.Show(true);
	bs.AsString().Show(true);
	return 0;
}

int main(void)
{
	Sys.MessagePort = COM1;					 			// 初始化系统日志打印串口（默认为串口1）
	Sys.Init();									 			// 初始化系统配置
	Sys.ShowInfo();								 			// 打印系统配置信息（仅在Debug版本有效）
	
	modbusSlave.Address = 1;
	modbusSlave.Open();

	OutputPort leds[] = { PA8};
	for (int i = 0; i < ArrayLength(leds); i++)		 			// 初始化输出
		leds[i].Invert = true;					 			// 使能输出引脚的倒置功能
	
	Sys.AddTask(LedTask, &leds[0], 100, 100, "Led闪烁");	// 添加系统任务、

	Sys.Start();											// 启动SmartOS系统

	return 0;
}

extern "C"
{
	__asm uint32_t __get_MSP(void)
	{
		mrs r0, msp
			bx lr
	}
	__asm void __set_MSP(uint32_t mainStackPointer)
	{
		msr msp, r0
			bx lr
	}
	__asm void __set_PSP(uint32_t topOfProcStack)
	{
		msr psp, r0
			bx lr
	}

	__asm uint32_t __get_PSP(void)
	{
		mrs r0, psp
			bx lr
	}
	__asm uint32_t __REV16(uint16_t value)
	{
		rev16 r0, r0
			bx lr
	}

}
