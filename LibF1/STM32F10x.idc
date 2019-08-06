#define UNLOADED_FILE   1
#include <idc.idc>

static main(void)
{
  // set 'loading idc file' mode
  SetCharPrm(INF_GENFLAGS, INFFL_LOADIDC|GetCharPrm(INF_GENFLAGS));
  Segments();           // segmentation
  Bytes();              // individual bytes (code,data)
  // clear 'loading idc file' mode
  SetCharPrm(INF_GENFLAGS, ~INFFL_LOADIDC&GetCharPrm(INF_GENFLAGS));
}

static Segments(void) {
	auto addr;
	auto size;

	SetSelector(0X1,0);

	addr	= 0x20000000;
	size	= 0x8000;
	AddSegEx(addr, addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"ram");
	SegClass (addr,"DATA");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);
	SetSegmentType(addr,3);

	addr	= 0X40000000;
	size	= 0x8000;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"APB1");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	addr	= 0X40010000;
	size	= 0x8000;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"APB2");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	addr	= 0X40020000;
	size	= 0x8200;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"AHB");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	addr	= 0x1FFFF800;
	size	= 0x800;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"segOB");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	addr	= 0xA0000000;
	size	= 0x800;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"segFSMC");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	addr	= 0xE0000000;
	size	= 0x100;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"segITM");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	addr	= 0xE000E000;
	size	= 0x1000;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"segCORE");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	addr	= 0xE0042000;
	size	= 0x800;
	AddSegEx(addr,addr+size,0X1,1,1,2,ADDSEG_NOSREG);
	SegRename(addr,"segDBG");
	SegClass (addr,"");
	SegDefReg(addr,"T",0x0);
	SegDefReg(addr,"DS",0x1);

	LowVoids(0x8000000);
	HighVoids(0x42000000);
}

static Bytes_0(void) {
        auto x;
#define id x

	MakeDword	(0X8000000);
	MakeDword	(x=0X8000004);
	OpOff		(x,	0,	0);
	OpOff		(x,	128,	0);
	MakeDword	(x=0X8000008);
	OpOff		(x,	0,	0);
	OpOff		(x,	128,	0);
	MakeDword	(x=0X800000C);
	OpOff		(x,	0,	0);
	OpOff		(x,	128,	0);
	MakeDword	(x=0X8000010);
	OpOff		(x,	0,	0);
	OpOff		(x,	128,	0);
	MakeDword	(x=0X8000014);
	OpOff		(x,	0,	0);
	OpOff		(x,	128,	0);
	MakeDword	(x=0X8000018);
	OpOff		(x,	0,	0);
	OpOff		(x,	128,	0);
	MakeDword	(x=0X800001C);
	MakeArray	(x,	0X31);
	OpOff		(x,	0,	0);
	OpOff		(x,	128,	0);
	MakeName	(0x40000000, "TIM2");
	MakeStruct	(0x40000000, "TIM_TypeDef");
	MakeName	(0x40000400, "TIM3");
	MakeStruct	(0x40000400, "TIM_TypeDef");
	MakeName	(0x40000800, "TIM4");
	MakeStruct	(0x40000800, "TIM_TypeDef");
	MakeName	(0x40000C00, "TIM5");
	MakeStruct	(0x40000C00, "TIM_TypeDef");
	MakeName	(0x40001000, "TIM6");
	MakeStruct	(0x40001000, "TIM_TypeDef");
	MakeName	(0x40001400, "TIM7");
	MakeStruct	(0x40001400, "TIM_TypeDef");
	MakeName	(0x40001800, "TIM12");
	MakeStruct	(0x40001800, "TIM_TypeDef");
	MakeName	(0x40001C00, "TIM13");
	MakeStruct	(0x40001C00, "TIM_TypeDef");
	MakeName	(0x40002000, "TIM14");
	MakeStruct	(0x40002000, "TIM_TypeDef");
	MakeName	(0x40002800, "RTC");
	MakeStruct	(0x40002800, "RTC_TypeDef");
	MakeName	(0x40002C00, "WWDG");
	MakeStruct	(0x40002C00, "WWDG_TypeDef");
	MakeName	(0x40003000, "IWDG");
	MakeStruct	(0x40003000, "IWDG_TypeDef");
	MakeName	(0x40003800, "SPI2");
	MakeStruct	(0x40003800, "SPI_TypeDef");
	MakeName	(0x40003C00, "SPI3");
	MakeStruct	(0x40003C00, "SPI_TypeDef");
	MakeName	(0x40004400, "USART2");
	MakeStruct	(0x40004400, "USART_TypeDef");
	MakeName	(0x40004800, "USART3");
	MakeStruct	(0x40004800, "USART_TypeDef");
	MakeName	(0x40004C00, "UART4");
	MakeStruct	(0x40004C00, "USART_TypeDef");
	MakeName	(0x40005000, "UART5");
	MakeStruct	(0x40005000, "USART_TypeDef");
	MakeName	(0x40005400, "I2C1");
	MakeStruct	(0x40005400, "I2C_TypeDef");
	MakeName	(0x40005800, "I2C2");
	MakeStruct	(0x40005800, "I2C_TypeDef");
	MakeName	(0x40006400, "CAN1");
	MakeStruct	(0x40006400, "CAN_TypeDef");
	MakeName	(0x40006800, "CAN2");
	MakeStruct	(0x40006800, "CAN_TypeDef");
	MakeName	(0x40006C00, "BKP");
	MakeStruct	(0x40006C00, "BKP_TypeDef");
	MakeName	(0x40007000, "PWR");
	MakeStruct	(0x40007000, "PWR_TypeDef");
	MakeName	(0x40007400, "DAC");
	MakeStruct	(0x40007400, "DAC_TypeDef");
	MakeName	(0x40007800, "CEC");
	MakeStruct	(0x40007800, "CEC_TypeDef");
	MakeName	(0x40010000, "AFIO");
	MakeStruct	(0x40010000, "AFIO_TypeDef");
	MakeName	(0x40010400, "EXTI");
	MakeStruct	(0x40010400, "EXTI_TypeDef");
	MakeName	(0x40010800, "GPIOA");
	MakeStruct	(0x40010800, "GPIO_TypeDef");
	MakeName	(0x40010C00, "GPIOB");
	MakeStruct	(0x40010C00, "GPIO_TypeDef");
	MakeName	(0x40011000, "GPIOC");
	MakeStruct	(0x40011000, "GPIO_TypeDef");
	MakeName	(0x40011400, "GPIOD");
	MakeStruct	(0x40011400, "GPIO_TypeDef");
	MakeName	(0x40011800, "GPIOE");
	MakeStruct	(0x40011800, "GPIO_TypeDef");
	MakeName	(0x40011C00, "GPIOF");
	MakeStruct	(0x40011C00, "GPIO_TypeDef");
	MakeName	(0x40012000, "GPIOG");
	MakeStruct	(0x40012000, "GPIO_TypeDef");
	MakeName	(0x40012400, "ADC1");
	MakeStruct	(0x40012400, "ADC_TypeDef");
	MakeName	(0x40012800, "ADC2");
	MakeStruct	(0x40012800, "ADC_TypeDef");
	MakeName	(0x40012C00, "TIM1");
	MakeStruct	(0x40012C00, "TIM_TypeDef");
	MakeName	(0x40013000, "SPI1");
	MakeStruct	(0x40013000, "SPI_TypeDef");
	MakeName	(0x40013400, "TIM8");
	MakeStruct	(0x40013400, "TIM_TypeDef");
	MakeName	(0x40013800, "USART1");
	MakeStruct	(0x40013800, "USART_TypeDef");
	MakeName	(0x40013C00, "ADC3");
	MakeStruct	(0x40013C00, "ADC_TypeDef");
	MakeName	(0x40014000, "TIM15");
	MakeStruct	(0x40014000, "TIM_TypeDef");
	MakeName	(0x40014400, "TIM16");
	MakeStruct	(0x40014400, "TIM_TypeDef");
	MakeName	(0x40014800, "TIM17");
	MakeStruct	(0x40014800, "TIM_TypeDef");
	MakeName	(0x40014C00, "TIM9");
	MakeStruct	(0x40014C00, "TIM_TypeDef");
	MakeName	(0x40015000, "TIM10");
	MakeStruct	(0x40015000, "TIM_TypeDef");
	MakeName	(0x40015400, "TIM11");
	MakeStruct	(0x40015400, "TIM_TypeDef");
	MakeName	(0x40018000, "SDIO");
	MakeStruct	(0x40018000, "SDIO_TypeDef");
	MakeName	(0x40020000, "DMA1");
	MakeStruct	(0x40020000, "DMA_TypeDef");
	MakeName	(0x40020400, "DMA2");
	MakeStruct	(0x40020400, "DMA_TypeDef");
	MakeName	(0x40020008, "DMA1_Channel1");
	MakeStruct	(0x40020008, "DMA_Channel_TypeDef");
	MakeName	(0x4002001C, "DMA1_Channel2");
	MakeStruct	(0x4002001C, "DMA_Channel_TypeDef");
	MakeName	(0x40020030, "DMA1_Channel3");
	MakeStruct	(0x40020030, "DMA_Channel_TypeDef");
	MakeName	(0x40020044, "DMA1_Channel4");
	MakeStruct	(0x40020044, "DMA_Channel_TypeDef");
	MakeName	(0x40020058, "DMA1_Channel5");
	MakeStruct	(0x40020058, "DMA_Channel_TypeDef");
	MakeName	(0x4002006C, "DMA1_Channel6");
	MakeStruct	(0x4002006C, "DMA_Channel_TypeDef");
	MakeName	(0x40020080, "DMA1_Channel7");
	MakeStruct	(0x40020080, "DMA_Channel_TypeDef");
	MakeName	(0x40020408, "DMA2_Channel1");
	MakeStruct	(0x40020408, "DMA_Channel_TypeDef");
	MakeName	(0x4002041C, "DMA2_Channel2");
	MakeStruct	(0x4002041C, "DMA_Channel_TypeDef");
	MakeName	(0x40020430, "DMA2_Channel3");
	MakeStruct	(0x40020430, "DMA_Channel_TypeDef");
	MakeName	(0x40020444, "DMA2_Channel4");
	MakeStruct	(0x40020444, "DMA_Channel_TypeDef");
	MakeName	(0x40020458, "DMA2_Channel5");
	MakeStruct	(0x40020458, "DMA_Channel_TypeDef");
	MakeName	(0x40021000, "RCC");
	MakeStruct	(0x40021000, "RCC_TypeDef");
	MakeName	(0x40023000, "CRC");
	MakeStruct	(0x40023000, "CRC_TypeDef");
	MakeName	(0x40022000, "FLASH");
	MakeStruct	(0x40022000, "FLASH_TypeDef");
	MakeName	(0x1FFFF800, "OB");
	MakeStruct	(0x1FFFF800, "OB_TypeDef");
	MakeName	(0x40028000, "ETH");
	MakeStruct	(0x40028000, "ETH_TypeDef");
	MakeName	(0xA0000000, "FSMC_Bank1");
	MakeStruct	(0xA0000000, "FSMC_Bank1_TypeDef");
	MakeName	(0xA0000104, "FSMC_Bank1E");
	MakeStruct	(0xA0000104, "FSMC_Bank1E_TypeDef");
	MakeName	(0xA0000060, "FSMC_Bank2");
	MakeStruct	(0xA0000060, "FSMC_Bank2_TypeDef");
	MakeName	(0xA0000080, "FSMC_Bank3");
	MakeStruct	(0xA0000080, "FSMC_Bank3_TypeDef");
	MakeName	(0xA00000A0, "FSMC_Bank4");
	MakeStruct	(0xA00000A0, "FSMC_Bank4_TypeDef");
	MakeName	(0xE0042000, "DBGMCU");
	MakeStruct	(0xE0042000, "DBGMCU_TypeDef");

	MakeName	(0xE000E000, "InterruptType");
	MakeStruct	(0xE000E000, "InterruptType_Type");
	MakeName	(0xE000ED00, "SCB");
	MakeStruct	(0xE000ED00, "SCB_Type");
	MakeName	(0xE000E010, "SysTick");
	MakeStruct	(0xE000E010, "SysTick_Type");
	MakeName	(0xE000E100, "NVIC");
	MakeStruct	(0xE000E100, "NVIC_Type");
	MakeName	(0xE0000000, "ITM");
	MakeStruct	(0xE0000000, "ITM_Type");
	MakeName	(0xE000EDF0, "CoreDebug");
	MakeStruct	(0xE000EDF0, "CoreDebug_Type");
}

static Bytes(void) {
	Bytes_0();
    EndTypeUpdating(UTP_STRUCT);
}
