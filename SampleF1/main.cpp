#include "Sys.h"
#include "Device\Port.h"
#include "Device\SerialPort.h"
#include "Drivers\AT24CXX.h"

void LedTask(void* param)
{
	auto leds = (OutputPort*)param;
	*leds = !*leds;
}

void OnPress(InputPort& port, bool down)
{
	debug_printf("Press P%c%d down=%d\r\n", _PIN_NAME(port._Pin), down);
}

uint OnUsart1Read(ITransport* port, Buffer& bs, void* param, void* param2)
{
	bs.Show(true);
	bs.AsString().Show(true);
	return 0;
}
void at24test();
int main(void)
{
	//Sys.Clock = 72000000;						 			// 设置系统时钟参数	（默认STM32F1X为72M）		
	Sys.MessagePort = COM1;					 			// 初始化系统日志打印串口（默认为串口1）
	/*SerialPort::GetMessagePort()->Close();
	SerialPort::GetMessagePort()->SetBaudRate(115200);
	SerialPort::GetMessagePort()->Register(OnUsart1Read);
	SerialPort::GetMessagePort()->Open();*/
	Sys.Init();									 			// 初始化系统配置
	Sys.ShowInfo();								 			// 打印系统配置信息（仅在Debug版本有效）

	//OutputPort leds[] = { PB0, PB1,PB5 };				 			// 初始化LED输出引脚
	OutputPort leds[] = { PB0, PD4,PD5 };
	for (int i = 0; i < ArrayLength(leds); i++)		 			// 初始化输出
		leds[i].Invert = true;					 			// 使能输出引脚的倒置功能

	Pin ips[] = { PA0,PC13 };						 			// 初始化按键输入引脚
	InputPort btns[2];							 			// 创建输入实例
	for (int i = 0; i < ArrayLength(btns); i++)		 			// 初始化输入
	{
		btns[i].Index = i;
		btns[i].Set(ips[i]);					 			// 设置引脚
		btns[i].Press = OnPress;							// 注册输入事件
		btns[i].UsePress();						 			// 使能注册输入事件
		btns[i].Open();							 			// 开启
	}
	at24test();
	Sys.AddTask(LedTask, &leds[0], 100, 100, "Led闪烁");	// 添加系统任务、

	/*Buffer::Test();
	Array::Test();
	String::Test();
	DateTime::Test();
	IList::Test(); 
	IDictionary::Test();
	OutputPort power(PE2);
	power = true;
	SerialPort::Test();*/

	Sys.Start();											// 启动SmartOS系统

	return 0;
}

SoftI2C softiic;
AT24CXX at24;

void at24test()
{
	byte send[] = { 0x0f };
	byte read[] = { 0x00 };

	Buffer bsRead(read, 1);

	softiic.SetPin(PB6,PB7);
	softiic.Open();

	at24.IIC = &softiic;

	at24.Address = 0x00;

	at24.Write(1, Buffer(send,1));
	at24.Read(1, bsRead);
	debug_printf("\r\n\r\n Write Read: ");
	bsRead.Show(true);
	
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
