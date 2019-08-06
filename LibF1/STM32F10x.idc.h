#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

/* 56 */
enum Pin : __int8
{
  P0 = 0xFF,
  PA0 = 0x0,
  PA1 = 0x1,
  PA2 = 0x2,
  PA3 = 0x3,
  PA4 = 0x4,
  PA5 = 0x5,
  PA6 = 0x6,
  PA7 = 0x7,
  PA8 = 0x8,
  PA9 = 0x9,
  PA10 = 0xA,
  PA11 = 0xB,
  PA12 = 0xC,
  PA13 = 0xD,
  PA14 = 0xE,
  PA15 = 0xF,
  PB0 = 0x10,
  PB1 = 0x11,
  PB2 = 0x12,
  PB3 = 0x13,
  PB4 = 0x14,
  PB5 = 0x15,
  PB6 = 0x16,
  PB7 = 0x17,
  PB8 = 0x18,
  PB9 = 0x19,
  PB10 = 0x1A,
  PB11 = 0x1B,
  PB12 = 0x1C,
  PB13 = 0x1D,
  PB14 = 0x1E,
  PB15 = 0x1F,
  PC0 = 0x20,
  PC1 = 0x21,
  PC2 = 0x22,
  PC3 = 0x23,
  PC4 = 0x24,
  PC5 = 0x25,
  PC6 = 0x26,
  PC7 = 0x27,
  PC8 = 0x28,
  PC9 = 0x29,
  PC10 = 0x2A,
  PC11 = 0x2B,
  PC12 = 0x2C,
  PC13 = 0x2D,
  PC14 = 0x2E,
  PC15 = 0x2F,
  PD0 = 0x30,
  PD1 = 0x31,
  PD2 = 0x32,
  PD3 = 0x33,
  PD4 = 0x34,
  PD5 = 0x35,
  PD6 = 0x36,
  PD7 = 0x37,
  PD8 = 0x38,
  PD9 = 0x39,
  PD10 = 0x3A,
  PD11 = 0x3B,
  PD12 = 0x3C,
  PD13 = 0x3D,
  PD14 = 0x3E,
  PD15 = 0x3F,
  PE0 = 0x40,
  PE1 = 0x41,
  PE2 = 0x42,
  PE3 = 0x43,
  PE4 = 0x44,
  PE5 = 0x45,
  PE6 = 0x46,
  PE7 = 0x47,
  PE8 = 0x48,
  PE9 = 0x49,
  PE10 = 0x4A,
  PE11 = 0x4B,
  PE12 = 0x4C,
  PE13 = 0x4D,
  PE14 = 0x4E,
  PE15 = 0x4F,
  PF0 = 0x50,
  PF1 = 0x51,
  PF2 = 0x52,
  PF3 = 0x53,
  PF4 = 0x54,
  PF5 = 0x55,
  PF6 = 0x56,
  PF7 = 0x57,
  PF8 = 0x58,
  PF9 = 0x59,
  PF10 = 0x5A,
  PF11 = 0x5B,
  PF12 = 0x5C,
  PF13 = 0x5D,
  PF14 = 0x5E,
  PF15 = 0x5F,
  PG0 = 0x60,
  PG1 = 0x61,
  PG2 = 0x62,
  PG3 = 0x63,
  PG4 = 0x64,
  PG5 = 0x65,
  PG6 = 0x66,
  PG7 = 0x67,
  PG8 = 0x68,
  PG9 = 0x69,
  PG10 = 0x6A,
  PG11 = 0x6B,
  PG12 = 0x6C,
  PG13 = 0x6D,
  PG14 = 0x6E,
  PG15 = 0x6F,
  PH0 = 0x70,
  PH1 = 0x71,
  PH2 = 0x72,
  PH3 = 0x73,
  PH4 = 0x74,
  PH5 = 0x75,
  PH6 = 0x76,
  PH7 = 0x77,
  PH8 = 0x78,
  PH9 = 0x79,
  PH10 = 0x7A,
  PH11 = 0x7B,
  PH12 = 0x7C,
  PH13 = 0x7D,
  PH14 = 0x7E,
  PH15 = 0x7F,
};

/* 101 */
typedef unsigned char byte;

/* 105 */
typedef unsigned __int8 uint8_t;

/* 106 */
typedef unsigned __int16 ushort;

/* 107 */
typedef unsigned int uint;

/* 160 */
enum IRQn : __int8
{
  NonMaskableInt_IRQn = 0xF2,
  MemoryManagement_IRQn = 0xF4,
  BusFault_IRQn = 0xF5,
  UsageFault_IRQn = 0xF6,
  SVCall_IRQn = 0xFB,
  DebugMonitor_IRQn = 0xFC,
  PendSV_IRQn = 0xFE,
  SysTick_IRQn = 0xFF,
  WWDG_IRQn = 0x0,
  PVD_IRQn = 0x1,
  TAMPER_IRQn = 0x2,
  RTC_IRQn = 0x3,
  FLASH_IRQn = 0x4,
  RCC_IRQn = 0x5,
  EXTI0_IRQn = 0x6,
  EXTI1_IRQn = 0x7,
  EXTI2_IRQn = 0x8,
  EXTI3_IRQn = 0x9,
  EXTI4_IRQn = 0xA,
  DMA1_Channel1_IRQn = 0xB,
  DMA1_Channel2_IRQn = 0xC,
  DMA1_Channel3_IRQn = 0xD,
  DMA1_Channel4_IRQn = 0xE,
  DMA1_Channel5_IRQn = 0xF,
  DMA1_Channel6_IRQn = 0x10,
  DMA1_Channel7_IRQn = 0x11,
  ADC1_2_IRQn = 0x12,
  USB_HP_CAN1_TX_IRQn = 0x13,
  USB_LP_CAN1_RX0_IRQn = 0x14,
  CAN1_RX1_IRQn = 0x15,
  CAN1_SCE_IRQn = 0x16,
  EXTI9_5_IRQn = 0x17,
  TIM1_BRK_IRQn = 0x18,
  TIM1_UP_IRQn = 0x19,
  TIM1_TRG_COM_IRQn = 0x1A,
  TIM1_CC_IRQn = 0x1B,
  TIM2_IRQn = 0x1C,
  TIM3_IRQn = 0x1D,
  TIM4_IRQn = 0x1E,
  I2C1_EV_IRQn = 0x1F,
  I2C1_ER_IRQn = 0x20,
  I2C2_EV_IRQn = 0x21,
  I2C2_ER_IRQn = 0x22,
  SPI1_IRQn = 0x23,
  SPI2_IRQn = 0x24,
  USART1_IRQn = 0x25,
  USART2_IRQn = 0x26,
  USART3_IRQn = 0x27,
  EXTI15_10_IRQn = 0x28,
  RTCAlarm_IRQn = 0x29,
  USBWakeUp_IRQn = 0x2A,
  TIM8_BRK_IRQn = 0x2B,
  TIM8_UP_IRQn = 0x2C,
  TIM8_TRG_COM_IRQn = 0x2D,
  TIM8_CC_IRQn = 0x2E,
  ADC3_IRQn = 0x2F,
  FSMC_IRQn = 0x30,
  SDIO_IRQn = 0x31,
  TIM5_IRQn = 0x32,
  SPI3_IRQn = 0x33,
  UART4_IRQn = 0x34,
  UART5_IRQn = 0x35,
  TIM6_IRQn = 0x36,
  TIM7_IRQn = 0x37,
  DMA2_Channel1_IRQn = 0x38,
  DMA2_Channel2_IRQn = 0x39,
  DMA2_Channel3_IRQn = 0x3A,
  DMA2_Channel4_5_IRQn = 0x3B,
};

/* 161 */
typedef IRQn IRQn_Type;

/* 186 */
enum FlagStatus : __int8
{
  RESET = 0x0,
  SET = 0x1,
};

/* 187 */
typedef FlagStatus ITStatus;

/* 188 */
enum FunctionalState : __int8
{
  DISABLE = 0x0,
  ENABLE = 0x1,
};

/* 189 */
enum ErrorStatus : __int8
{
  ERROR = 0x0,
  SUCCESS = 0x1,
};

/* 190 */
struct ADC_TypeDef
{
  volatile uint SR;
  volatile uint CR1;
  volatile uint CR2;
  volatile uint SMPR1;
  volatile uint SMPR2;
  volatile uint JOFR1;
  volatile uint JOFR2;
  volatile uint JOFR3;
  volatile uint JOFR4;
  volatile uint HTR;
  volatile uint LTR;
  volatile uint SQR1;
  volatile uint SQR2;
  volatile uint SQR3;
  volatile uint JSQR;
  volatile uint JDR1;
  volatile uint JDR2;
  volatile uint JDR3;
  volatile uint JDR4;
  volatile uint DR;
};

/* 191 */
struct BKP_TypeDef
{
  uint RESERVED0;
  volatile ushort DR1;
  ushort RESERVED1;
  volatile ushort DR2;
  ushort RESERVED2;
  volatile ushort DR3;
  ushort RESERVED3;
  volatile ushort DR4;
  ushort RESERVED4;
  volatile ushort DR5;
  ushort RESERVED5;
  volatile ushort DR6;
  ushort RESERVED6;
  volatile ushort DR7;
  ushort RESERVED7;
  volatile ushort DR8;
  ushort RESERVED8;
  volatile ushort DR9;
  ushort RESERVED9;
  volatile ushort DR10;
  ushort RESERVED10;
  volatile ushort RTCCR;
  ushort RESERVED11;
  volatile ushort CR;
  ushort RESERVED12;
  volatile ushort CSR;
  ushort RESERVED13[5];
  volatile ushort DR11;
  ushort RESERVED14;
  volatile ushort DR12;
  ushort RESERVED15;
  volatile ushort DR13;
  ushort RESERVED16;
  volatile ushort DR14;
  ushort RESERVED17;
  volatile ushort DR15;
  ushort RESERVED18;
  volatile ushort DR16;
  ushort RESERVED19;
  volatile ushort DR17;
  ushort RESERVED20;
  volatile ushort DR18;
  ushort RESERVED21;
  volatile ushort DR19;
  ushort RESERVED22;
  volatile ushort DR20;
  ushort RESERVED23;
  volatile ushort DR21;
  ushort RESERVED24;
  volatile ushort DR22;
  ushort RESERVED25;
  volatile ushort DR23;
  ushort RESERVED26;
  volatile ushort DR24;
  ushort RESERVED27;
  volatile ushort DR25;
  ushort RESERVED28;
  volatile ushort DR26;
  ushort RESERVED29;
  volatile ushort DR27;
  ushort RESERVED30;
  volatile ushort DR28;
  ushort RESERVED31;
  volatile ushort DR29;
  ushort RESERVED32;
  volatile ushort DR30;
  ushort RESERVED33;
  volatile ushort DR31;
  ushort RESERVED34;
  volatile ushort DR32;
  ushort RESERVED35;
  volatile ushort DR33;
  ushort RESERVED36;
  volatile ushort DR34;
  ushort RESERVED37;
  volatile ushort DR35;
  ushort RESERVED38;
  volatile ushort DR36;
  ushort RESERVED39;
  volatile ushort DR37;
  ushort RESERVED40;
  volatile ushort DR38;
  ushort RESERVED41;
  volatile ushort DR39;
  ushort RESERVED42;
  volatile ushort DR40;
  ushort RESERVED43;
  volatile ushort DR41;
  ushort RESERVED44;
  volatile ushort DR42;
  ushort RESERVED45;
};

/* 192 */
struct CAN_TxMailBox_TypeDef
{
  volatile uint TIR;
  volatile uint TDTR;
  volatile uint TDLR;
  volatile uint TDHR;
};

/* 193 */
struct CAN_FIFOMailBox_TypeDef
{
  volatile uint RIR;
  volatile uint RDTR;
  volatile uint RDLR;
  volatile uint RDHR;
};

/* 194 */
struct CAN_FilterRegister_TypeDef
{
  volatile uint FR1;
  volatile uint FR2;
};

/* 195 */
struct CAN_TypeDef
{
  volatile uint MCR;
  volatile uint MSR;
  volatile uint TSR;
  volatile uint RF0R;
  volatile uint RF1R;
  volatile uint IER;
  volatile uint ESR;
  volatile uint BTR;
  uint RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint RESERVED1[12];
  volatile uint FMR;
  volatile uint FM1R;
  uint RESERVED2;
  volatile uint FS1R;
  uint RESERVED3;
  volatile uint FFA1R;
  uint RESERVED4;
  volatile uint FA1R;
  uint RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[14];
};

/* 196 */
struct CEC_TypeDef
{
  volatile uint CFGR;
  volatile uint OAR;
  volatile uint PRES;
  volatile uint ESR;
  volatile uint CSR;
  volatile uint TXD;
  volatile uint RXD;
};

/* 197 */
struct CRC_TypeDef
{
  volatile uint DR;
  volatile uint8_t IDR;
  uint8_t RESERVED0;
  ushort RESERVED1;
  volatile uint CR;
};

/* 198 */
struct DAC_TypeDef
{
  volatile uint CR;
  volatile uint SWTRIGR;
  volatile uint DHR12R1;
  volatile uint DHR12L1;
  volatile uint DHR8R1;
  volatile uint DHR12R2;
  volatile uint DHR12L2;
  volatile uint DHR8R2;
  volatile uint DHR12RD;
  volatile uint DHR12LD;
  volatile uint DHR8RD;
  volatile uint DOR1;
  volatile uint DOR2;
};

/* 199 */
struct DBGMCU_TypeDef
{
  volatile uint IDCODE;
  volatile uint CR;
};

/* 200 */
struct DMA_Channel_TypeDef
{
  volatile uint CCR;
  volatile uint CNDTR;
  volatile uint CPAR;
  volatile uint CMAR;
};

/* 201 */
struct DMA_TypeDef
{
  volatile uint ISR;
  volatile uint IFCR;
};

/* 202 */
struct ETH_TypeDef
{
  volatile uint MACCR;
  volatile uint MACFFR;
  volatile uint MACHTHR;
  volatile uint MACHTLR;
  volatile uint MACMIIAR;
  volatile uint MACMIIDR;
  volatile uint MACFCR;
  volatile uint MACVLANTR;
  uint RESERVED0[2];
  volatile uint MACRWUFFR;
  volatile uint MACPMTCSR;
  uint RESERVED1[2];
  volatile uint MACSR;
  volatile uint MACIMR;
  volatile uint MACA0HR;
  volatile uint MACA0LR;
  volatile uint MACA1HR;
  volatile uint MACA1LR;
  volatile uint MACA2HR;
  volatile uint MACA2LR;
  volatile uint MACA3HR;
  volatile uint MACA3LR;
  uint RESERVED2[40];
  volatile uint MMCCR;
  volatile uint MMCRIR;
  volatile uint MMCTIR;
  volatile uint MMCRIMR;
  volatile uint MMCTIMR;
  uint RESERVED3[14];
  volatile uint MMCTGFSCCR;
  volatile uint MMCTGFMSCCR;
  uint RESERVED4[5];
  volatile uint MMCTGFCR;
  uint RESERVED5[10];
  volatile uint MMCRFCECR;
  volatile uint MMCRFAECR;
  uint RESERVED6[10];
  volatile uint MMCRGUFCR;
  uint RESERVED7[334];
  volatile uint PTPTSCR;
  volatile uint PTPSSIR;
  volatile uint PTPTSHR;
  volatile uint PTPTSLR;
  volatile uint PTPTSHUR;
  volatile uint PTPTSLUR;
  volatile uint PTPTSAR;
  volatile uint PTPTTHR;
  volatile uint PTPTTLR;
  uint RESERVED8[567];
  volatile uint DMABMR;
  volatile uint DMATPDR;
  volatile uint DMARPDR;
  volatile uint DMARDLAR;
  volatile uint DMATDLAR;
  volatile uint DMASR;
  volatile uint DMAOMR;
  volatile uint DMAIER;
  volatile uint DMAMFBOCR;
  uint RESERVED9[9];
  volatile uint DMACHTDR;
  volatile uint DMACHRDR;
  volatile uint DMACHTBAR;
  volatile uint DMACHRBAR;
};

/* 203 */
struct EXTI_TypeDef
{
  volatile uint IMR;
  volatile uint EMR;
  volatile uint RTSR;
  volatile uint FTSR;
  volatile uint SWIER;
  volatile uint PR;
};

/* 204 */
struct FLASH_TypeDef
{
  volatile uint ACR;
  volatile uint KEYR;
  volatile uint OPTKEYR;
  volatile uint SR;
  volatile uint CR;
  volatile uint AR;
  volatile uint RESERVED;
  volatile uint OBR;
  volatile uint WRPR;
};

/* 205 */
struct OB_TypeDef
{
  volatile ushort RDP;
  volatile ushort USER;
  volatile ushort Data0;
  volatile ushort Data1;
  volatile ushort WRP0;
  volatile ushort WRP1;
  volatile ushort WRP2;
  volatile ushort WRP3;
};

/* 206 */
struct FSMC_Bank1_TypeDef
{
  volatile uint BTCR[8];
};

/* 207 */
struct FSMC_Bank1E_TypeDef
{
  volatile uint BWTR[7];
};

/* 208 */
struct FSMC_Bank2_TypeDef
{
  volatile uint PCR2;
  volatile uint SR2;
  volatile uint PMEM2;
  volatile uint PATT2;
  uint RESERVED0;
  volatile uint ECCR2;
};

/* 209 */
struct FSMC_Bank3_TypeDef
{
  volatile uint PCR3;
  volatile uint SR3;
  volatile uint PMEM3;
  volatile uint PATT3;
  uint RESERVED0;
  volatile uint ECCR3;
};

/* 210 */
struct FSMC_Bank4_TypeDef
{
  volatile uint PCR4;
  volatile uint SR4;
  volatile uint PMEM4;
  volatile uint PATT4;
  volatile uint PIO4;
};

/* 211 */
struct GPIO_TypeDef
{
  volatile uint CRL;
  volatile uint CRH;
  volatile uint IDR;
  volatile uint ODR;
  volatile uint BSRR;
  volatile uint BRR;
  volatile uint LCKR;
};

/* 212 */
struct AFIO_TypeDef
{
  volatile uint EVCR;
  volatile uint MAPR;
  volatile uint EXTICR[4];
  uint RESERVED0;
  volatile uint MAPR2;
};

/* 213 */
struct I2C_TypeDef
{
  volatile ushort CR1;
  ushort RESERVED0;
  volatile ushort CR2;
  ushort RESERVED1;
  volatile ushort OAR1;
  ushort RESERVED2;
  volatile ushort OAR2;
  ushort RESERVED3;
  volatile ushort DR;
  ushort RESERVED4;
  volatile ushort SR1;
  ushort RESERVED5;
  volatile ushort SR2;
  ushort RESERVED6;
  volatile ushort CCR;
  ushort RESERVED7;
  volatile ushort TRISE;
  ushort RESERVED8;
};

/* 214 */
struct IWDG_TypeDef
{
  volatile uint KR;
  volatile uint PR;
  volatile uint RLR;
  volatile uint SR;
};

/* 215 */
struct PWR_TypeDef
{
  volatile uint CR;
  volatile uint CSR;
};

/* 216 */
struct RCC_TypeDef
{
  volatile uint CR;
  volatile uint CFGR;
  volatile uint CIR;
  volatile uint APB2RSTR;
  volatile uint APB1RSTR;
  volatile uint AHBENR;
  volatile uint APB2ENR;
  volatile uint APB1ENR;
  volatile uint BDCR;
  volatile uint CSR;
};

/* 217 */
struct RTC_TypeDef
{
  volatile ushort CRH;
  ushort RESERVED0;
  volatile ushort CRL;
  ushort RESERVED1;
  volatile ushort PRLH;
  ushort RESERVED2;
  volatile ushort PRLL;
  ushort RESERVED3;
  volatile ushort DIVH;
  ushort RESERVED4;
  volatile ushort DIVL;
  ushort RESERVED5;
  volatile ushort CNTH;
  ushort RESERVED6;
  volatile ushort CNTL;
  ushort RESERVED7;
  volatile ushort ALRH;
  ushort RESERVED8;
  volatile ushort ALRL;
  ushort RESERVED9;
};

/* 218 */
struct SDIO_TypeDef
{
  volatile uint POWER;
  volatile uint CLKCR;
  volatile uint ARG;
  volatile uint CMD;
  const volatile uint RESPCMD;
  const volatile uint RESP1;
  const volatile uint RESP2;
  const volatile uint RESP3;
  const volatile uint RESP4;
  volatile uint DTIMER;
  volatile uint DLEN;
  volatile uint DCTRL;
  const volatile uint DCOUNT;
  const volatile uint STA;
  volatile uint ICR;
  volatile uint MASK;
  uint RESERVED0[2];
  const volatile uint FIFOCNT;
  uint RESERVED1[13];
  volatile uint FIFO;
};

/* 219 */
struct SPI_TypeDef
{
  volatile ushort CR1;
  ushort RESERVED0;
  volatile ushort CR2;
  ushort RESERVED1;
  volatile ushort SR;
  ushort RESERVED2;
  volatile ushort DR;
  ushort RESERVED3;
  volatile ushort CRCPR;
  ushort RESERVED4;
  volatile ushort RXCRCR;
  ushort RESERVED5;
  volatile ushort TXCRCR;
  ushort RESERVED6;
  volatile ushort I2SCFGR;
  ushort RESERVED7;
  volatile ushort I2SPR;
  ushort RESERVED8;
};

/* 220 */
struct TIM_TypeDef
{
  volatile ushort CR1;
  ushort RESERVED0;
  volatile ushort CR2;
  ushort RESERVED1;
  volatile ushort SMCR;
  ushort RESERVED2;
  volatile ushort DIER;
  ushort RESERVED3;
  volatile ushort SR;
  ushort RESERVED4;
  volatile ushort EGR;
  ushort RESERVED5;
  volatile ushort CCMR1;
  ushort RESERVED6;
  volatile ushort CCMR2;
  ushort RESERVED7;
  volatile ushort CCER;
  ushort RESERVED8;
  volatile ushort CNT;
  ushort RESERVED9;
  volatile ushort PSC;
  ushort RESERVED10;
  volatile ushort ARR;
  ushort RESERVED11;
  volatile ushort RCR;
  ushort RESERVED12;
  volatile ushort CCR1;
  ushort RESERVED13;
  volatile ushort CCR2;
  ushort RESERVED14;
  volatile ushort CCR3;
  ushort RESERVED15;
  volatile ushort CCR4;
  ushort RESERVED16;
  volatile ushort BDTR;
  ushort RESERVED17;
  volatile ushort DCR;
  ushort RESERVED18;
  volatile ushort DMAR;
  ushort RESERVED19;
};

/* 221 */
struct USART_TypeDef
{
  volatile ushort SR;
  ushort RESERVED0;
  volatile ushort DR;
  ushort RESERVED1;
  volatile ushort BRR;
  ushort RESERVED2;
  volatile ushort CR1;
  ushort RESERVED3;
  volatile ushort CR2;
  ushort RESERVED4;
  volatile ushort CR3;
  ushort RESERVED5;
  volatile ushort GTPR;
  ushort RESERVED6;
};

/* 222 */
struct WWDG_TypeDef
{
  volatile uint CR;
  volatile uint CFR;
  volatile uint SR;
};

/* 231 */
enum GPIOSpeed_TypeDef : __int8
{
  GPIO_Speed_10MHz = 0x1,
  GPIO_Speed_2MHz = 0x2,
  GPIO_Speed_50MHz = 0x3,
};

/* 232 */
enum GPIOMode_TypeDef : __int8
{
  GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x4,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18,
};

/* 233 */
struct GPIO_InitTypeDef
{
  std::ushort GPIO_Pin;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOMode_TypeDef GPIO_Mode;
};

/* 234 */
enum BitAction : __int8
{
  Bit_RESET = 0x0,
  Bit_SET = 0x1,
};

/* 292 */
struct __attribute__((aligned(4))) USART_InitTypeDef
{
  uint USART_BaudRate;
  ushort USART_WordLength;
  ushort USART_StopBits;
  ushort USART_Parity;
  ushort USART_Mode;
  ushort USART_HardwareFlowControl;
};

/* 293 */
struct USART_ClockInitTypeDef
{
  ushort USART_Clock;
  ushort USART_CPOL;
  ushort USART_CPHA;
  ushort USART_LastBit;
};

/* 294 */
struct __attribute__((aligned(2))) TIM_TimeBaseInitTypeDef
{
  ushort TIM_Prescaler;
  ushort TIM_CounterMode;
  ushort TIM_Period;
  ushort TIM_ClockDivision;
  uint8_t TIM_RepetitionCounter;
};

/* 295 */
struct TIM_OCInitTypeDef
{
  ushort TIM_OCMode;
  ushort TIM_OutputState;
  ushort TIM_OutputNState;
  ushort TIM_Pulse;
  ushort TIM_OCPolarity;
  ushort TIM_OCNPolarity;
  ushort TIM_OCIdleState;
  ushort TIM_OCNIdleState;
};

/* 296 */
struct TIM_ICInitTypeDef
{
  ushort TIM_Channel;
  ushort TIM_ICPolarity;
  ushort TIM_ICSelection;
  ushort TIM_ICPrescaler;
  ushort TIM_ICFilter;
};

/* 297 */
struct TIM_BDTRInitTypeDef
{
  ushort TIM_OSSRState;
  ushort TIM_OSSIState;
  ushort TIM_LOCKLevel;
  ushort TIM_DeadTime;
  ushort TIM_Break;
  ushort TIM_BreakPolarity;
  ushort TIM_AutomaticOutput;
};

/* 298 */
struct SPI_InitTypeDef
{
  ushort SPI_Direction;
  ushort SPI_Mode;
  ushort SPI_DataSize;
  ushort SPI_CPOL;
  ushort SPI_CPHA;
  ushort SPI_NSS;
  ushort SPI_BaudRatePrescaler;
  ushort SPI_FirstBit;
  ushort SPI_CRCPolynomial;
};

/* 299 */
struct __attribute__((aligned(4))) I2S_InitTypeDef
{
  ushort I2S_Mode;
  ushort I2S_Standard;
  ushort I2S_DataFormat;
  ushort I2S_MCLKOutput;
  uint I2S_AudioFreq;
  ushort I2S_CPOL;
};

/* 300 */
struct RCC_ClocksTypeDef
{
  uint SYSCLK_Frequency;
  uint HCLK_Frequency;
  uint PCLK1_Frequency;
  uint PCLK2_Frequency;
  uint ADCCLK_Frequency;
};

/* 302 */
enum EXTIMode_TypeDef : __int8
{
  EXTI_Mode_Interrupt = 0x0,
  EXTI_Mode_Event = 0x4,
};

/* 303 */
enum EXTITrigger_TypeDef : __int8
{
  EXTI_Trigger_Rising = 0x8,
  EXTI_Trigger_Falling = 0xC,
  EXTI_Trigger_Rising_Falling = 0x10,
};

/* 304 */
struct __attribute__((aligned(2))) EXTI_InitTypeDef
{
  uint EXTI_Line;
  EXTIMode_TypeDef EXTI_Mode;
  EXTITrigger_TypeDef EXTI_Trigger;
  FunctionalState EXTI_LineCmd;
};

/* 307 */
enum ETH_TYPE : __int16
{
  ETH_ARP = 0x608,
  ETH_IP = 0x8,
  ETH_IPv6 = 0xDD86,
};

/* 309 */
enum IP_TYPE : __int8
{
  IP_NONE = 0x0,
  IP_ICMP = 0x1,
  IP_IGMP = 0x2,
  IP_TCP = 0x6,
  IP_UDP = 0x11,
};

/* 312 */
struct _TCP_HEADER
{
  ushort SrcPort;
  ushort DestPort;
  uint Seq;
  uint Ack;
  unsigned __int8 reserved_1 : 4;
  unsigned __int8 Length : 4;
  unsigned __int8 Flags : 6;
  unsigned __int8 reserved_2 : 2;
  ushort WindowSize;
  ushort Checksum;
  ushort urgt_p;
};

/* 314 */
struct _UDP_HEADER
{
  ushort SrcPort;
  ushort DestPort;
  ushort Length;
  ushort Checksum;
};

/* 315 */
struct _ICMP_HEADER
{
  byte Type;
  byte Code;
  ushort Checksum;
  ushort Identifier;
  ushort Sequence;
};

/* 318 */
typedef _UDP_HEADER UDP_HEADER;

/* 320 */
enum DHCP_OPTION : __int8
{
  DHCP_OPT_Mask = 0x1,
  DHCP_OPT_Router = 0x3,
  DHCP_OPT_TimeServer = 0x4,
  DHCP_OPT_NameServer = 0x5,
  DHCP_OPT_DNSServer = 0x6,
  DHCP_OPT_LOGServer = 0x7,
  DHCP_OPT_HostName = 0xC,
  DHCP_OPT_MTU = 0x1A,
  DHCP_OPT_StaticRout = 0x21,
  DHCP_OPT_ARPCacheTimeout = 0x23,
  DHCP_OPT_NTPServer = 0x2A,
  DHCP_OPT_RequestedIP = 0x32,
  DHCP_OPT_IPLeaseTime = 0x33,
  DHCP_OPT_MessageType = 0x35,
  DHCP_OPT_DHCPServer = 0x36,
  DHCP_OPT_ParameterList = 0x37,
  DHCP_OPT_Message = 0x38,
  DHCP_OPT_MaxMessageSize = 0x39,
  DHCP_OPT_Vendor = 0x3C,
  DHCP_OPT_ClientIdentifier = 0x3D,
  DHCP_OPT_End = 0xFF,
};

/* 319 */
struct _DHCP_OPT
{
  DHCP_OPTION Option;
  byte Length;
  byte Data;
};

/* 321 */
enum TCP_FLAGS : __int8
{
  TCP_FLAGS_FIN = 0x1,
  TCP_FLAGS_SYN = 0x2,
  TCP_FLAGS_RST = 0x4,
  TCP_FLAGS_PUSH = 0x8,
  TCP_FLAGS_ACK = 0x10,
  TCP_FLAGS_URG = 0x20,
};

/* 322 */
typedef _TCP_HEADER TCP_HEADER;

/* 323 */
typedef _ICMP_HEADER ICMP_HEADER;

/* 326 */
enum DHCP_MSGTYPE : __int8
{
  DHCP_TYPE_Discover = 0x1,
  DHCP_TYPE_Offer = 0x2,
  DHCP_TYPE_Request = 0x3,
  DHCP_TYPE_Decline = 0x4,
  DHCP_TYPE_Ack = 0x5,
  DHCP_TYPE_Nak = 0x6,
  DHCP_TYPE_Release = 0x7,
  DHCP_TYPE_Inform = 0x8,
};

/* 327 */
typedef _DHCP_OPT DHCP_OPT;

/* 383 */
struct ST_CPUID
{
  unsigned __int8 Revision : 4;
  unsigned __int16 PartNo : 12;
  unsigned __int8 Constant : 4;
  unsigned __int8 Variant : 4;
  byte Implementer;
};

/* 386 */
enum FLASH_Status : __int8
{
  FLASH_BUSY = 0x1,
  FLASH_ERROR_PG = 0x2,
  FLASH_ERROR_WRP = 0x3,
  FLASH_COMPLETE = 0x4,
  FLASH_TIMEOUT = 0x5,
};

/* 429 */
typedef unsigned int std::size_t;

/* 437 */
struct NVIC_Type
{
  volatile int ISER[8];
  int RESERVED0[24];
  volatile int ICER[8];
  int RSERVED1[24];
  volatile int ISPR[8];
  int RESERVED2[24];
  volatile int ICPR[8];
  int RESERVED3[24];
  volatile int IABR[8];
  int RESERVED4[56];
  volatile std::uint8_t IP[240];
  int RESERVED5[644];
  volatile int STIR;
};

/* 438 */
struct SCB_Type
{
  volatile int CPUID;
  volatile int ICSR;
  volatile int VTOR;
  volatile int AIRCR;
  volatile int SCR;
  volatile int CCR;
  volatile std::uint8_t SHP[12];
  volatile int SHCSR;
  volatile int CFSR;
  volatile int HFSR;
  volatile int DFSR;
  volatile int MMFAR;
  volatile int BFAR;
  volatile int AFSR;
  volatile int PFR[2];
  volatile int DFR;
  volatile int ADR;
  volatile int MMFR[4];
  volatile int ISAR[5];
};

/* 439 */
struct SysTick_Type
{
  volatile int CTRL;
  volatile int LOAD;
  volatile int VAL;
  volatile int CALIB;
};

/* 441 */
union ITM_Type::$82460A26A5C90035AF02E71C6C8D8485
{
  volatile std::uint8_t u8;
  volatile std::ushort u16;
  volatile int u32;
};

/* 440 */
struct ITM_Type
{
  volatile ITM_Type::$82460A26A5C90035AF02E71C6C8D8485 PORT[32];
  int RESERVED0[864];
  volatile int TER;
  int RESERVED1[15];
  volatile int TPR;
  int RESERVED2[15];
  volatile int TCR;
  int RESERVED3[29];
  volatile int IWR;
  volatile int IRR;
  volatile int IMCR;
  int RESERVED4[43];
  volatile int LAR;
  volatile int LSR;
  int RESERVED5[6];
  volatile int PID4;
  volatile int PID5;
  volatile int PID6;
  volatile int PID7;
  volatile int PID0;
  volatile int PID1;
  volatile int PID2;
  volatile int PID3;
  volatile int CID0;
  volatile int CID1;
  volatile int CID2;
  volatile int CID3;
};

/* 442 */
struct InterruptType_Type
{
  int RESERVED0;
  volatile int ICTR;
  int RESERVED1;
};

/* 443 */
struct CoreDebug_Type
{
  volatile int DHCSR;
  volatile int DCRSR;
  volatile int DCRDR;
  volatile int DEMCR;
};

enum GPIO_Pin : __int16
{
  GPIO_Pin_0   = 0x0001,
  GPIO_Pin_1   = 0x0002,
  GPIO_Pin_2   = 0x0004,
  GPIO_Pin_3   = 0x0008,
  GPIO_Pin_4   = 0x0010,
  GPIO_Pin_5   = 0x0020,
  GPIO_Pin_6   = 0x0040,
  GPIO_Pin_7   = 0x0080,
  GPIO_Pin_8   = 0x0100,
  GPIO_Pin_9   = 0x0200,
  GPIO_Pin_10  = 0x0400,
  GPIO_Pin_11  = 0x0800,
  GPIO_Pin_12  = 0x1000,
  GPIO_Pin_13  = 0x2000,
  GPIO_Pin_14  = 0x4000,
  GPIO_Pin_15  = 0x8000,
  GPIO_Pin_All = 0xFFFF,
};
