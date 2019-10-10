#include "Modbus.h"
#include "Security/Crc.h"

Modbus::Modbus()
{
	Address	= 0;
	Code	= 0;
	Error	= 0;
	Length	= 0;

	Crc		= 0;
	Crc2	= 0;
	for (int i = 0; i < ArrayLength(this->Data); i++)
		this->Data[i] = 0;
}

bool Modbus::Read(Stream& ms)
{
	//Buffer bs11(ms.GetBuffer(), 8);
	//bs11.Show(true);
	//debug_printf("ms length:%d\r\n", ms.Length);
	if(ms.Remain() < 4) return false;
	
	byte* buf = ms.Current();
	uint p = ms.Position();
		
	Address	= ms.ReadByte();
	Code	= ms.ReadByte();

	if(Code & 0x80)
	{
		Code	&= 0x7F;
		Error	= 1;
	}

	Length = ms.Remain() - 2;
	Buffer bs(Data, Length);
	ms.Read(bs);
	//ms.Read(&Data, 0, Length);

	Crc = ms.ReadUInt16();

	// 直接计算Crc16
	Crc2 = Crc::Hash16(Buffer(buf, ms.Position() - p - 2));

	//Crc2 = Sys.Crc16(buf, ms.Position() - p - 2);
	return true;
}

void Modbus::Write(Stream& ms)
{
	uint p = ms.Position();

	ms.Write(Address);

	byte code = Code;
	if(Error) code |= 0x80;
	ms.Write(code);

	if (Length > 0) ms.Write(Buffer(Data, Length));
	//if(Length > 0) ms.Write(Data, 0, Length);

	byte* buf = ms.Current();
	byte len = ms.Position() - p;
	// 直接计算Crc16
	//Crc = Crc2 = Sys.Crc16(buf - len, len);
	Crc = Crc2 = Crc::Hash16(Buffer(buf - len, len));

	ms.Write(Crc);
}

void Modbus::SetError(ModbusErrors::Errors error)
{
	Code |= 0x80;
	Length = 1;
	Data[0] = error;
}
