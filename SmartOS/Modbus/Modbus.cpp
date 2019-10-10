#include "Modbus.h"
#include "Security\Crc.h"

Modbus::Modbus()
{
	Address	= 0;
	Code	= 0;
	Error	= 0;
	Length	= 0;

	Crc		= 0;
	Crc2	= 0;
}

bool Modbus::Read(Stream& ms)
{
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
	Buffer bfrcv(Data, ArrayLength(Data));
	bfrcv.SetLength(Length);
	ms.Read(bfrcv);

	Crc = ms.ReadUInt16();

	// 直接计算Crc16
	Buffer bf(buf, ms.Position() - p - 2);
	ushort crc123;
	Crc2 = Crc::Hash16(bf, crc123);
}

void Modbus::Write(Stream& ms)
{
	uint p = ms.Position();

	ms.Write(Address);

	byte code = Code;
	if(Error) code |= 0x80;
	ms.Write(code);

	Buffer buf111(Data,Length);

	if(Length > 0) ms.Write(buf111);

	byte* buf = ms.Current();
	byte len = ms.Position() - p;
	Buffer bfwrite(buf - len, len);
	// 直接计算Crc16
	Crc = Crc2 = Crc::Hash16(bfwrite, len);

	ms.Write(Crc);
}

void Modbus::SetError(ModbusErrors::Errors error)
{
	Code |= 0x80;
	Length = 1;
	Data[0] = error;
}
