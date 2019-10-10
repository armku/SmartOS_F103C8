#include "Slave.h"
#include "Modbus.h"

Slave::Slave(ITransport* port)
{
	_port = port;

	Address	= 0;
}
void Slave::Open()
{
	this->_port->Open();
	this->_port->Register(OnReceive,this);
}

Slave::~Slave()
{
	delete _port;
	_port = nullptr;
}

/*
id 1
address 0
length 10
hoildingreg
01 03 00 00 00 0A C5 CD

id 1
address 0
length 10
inputreg
01 04 00 00 00 0A 70 0D
*/
uint16_t reginput[100];
uint16_t regHoild[100];
byte bufsend[200];
Buffer bsSend(bufsend, ArrayLength(bufsend));
uint Slave::OnReceive(ITransport* port, Buffer& bs, void* param, void* param2)
{
	auto slave = (Slave*)param;
	bs.Show(true);
	Stream ms(bs);
	Stream stsend(bsSend);
	Modbus entity;
	Modbus entitySend;
	uint16_t regadd;
	uint16_t reglen;

	if (!entity.Read(ms)) return 1;
		
	if (slave->Dispatch(entity))
	{
		//数据帧正确
		debug_printf("Frame ok \r\n");
		switch (entity.Code)
		{
		case 4:
			//input address
			regadd = entity.Data[0];
			regadd <<= 8;
			regadd += entity.Data[1];
			reglen = entity.Data[2];
			reglen <<= 8;
			reglen += entity.Data[3];
			
			debug_printf("reg:%d len:%d\r\n", regadd, reglen);
			entitySend.Address = entity.Address;
			entitySend.Code = entity.Code;
			entity.Length = reglen;
			for (int i = 0; i < reglen; i++)
			{
				reginput[regadd+i] = 100 + i;
				entitySend.Data[i * 2+1] = reginput[regadd + i]>>8;
				entitySend.Data[i * 2+2] = reginput[regadd + i];
			}
			entitySend.Length = reglen * 2+1;
			entitySend.Data[0] = reglen * 2;
			entitySend.Write(stsend);
			slave->_port->Write(Buffer(stsend.GetBuffer(), reglen*2+5));
			break;
		case 3:
			//Hoild address
			regadd = entity.Data[0];
			regadd <<= 8;
			regadd += entity.Data[1];
			reglen = entity.Data[2];
			reglen <<= 8;
			reglen += entity.Data[3];
			
			debug_printf("reg:%d len:%d\r\n", regadd, reglen);
			entitySend.Address = entity.Address;
			entitySend.Code = entity.Code;
			entity.Length = reglen;
			for (int i = 0; i < reglen; i++)
			{
				regHoild[regadd + i] = 200 + i;
				entitySend.Data[i * 2 + 1] = regHoild[regadd + i] >> 8;
				entitySend.Data[i * 2 + 2] = regHoild[regadd + i];
			}
			entitySend.Length = reglen * 2 + 1;
			entitySend.Data[0] = reglen * 2;
			entitySend.Write(stsend);
			slave->_port->Write(Buffer(stsend.GetBuffer(), reglen * 2 + 5));
			break;
		default:
			break;
		}
	}

	//bs.Show(true);
	return 0;
}

// 分发处理消息。返回值决定是否响应
bool Slave::Dispatch(Modbus& entity)
{
	debug_printf("address:%d rcvaddress:%d Code:%d rcvlength:%d\r\n",this->Address,entity.Address,entity.Code,entity.Length);
	//debug_printf("crc:%04x crc2:%04x \r\n", entity.Crc,entity.Crc2);
	// 是否本地地址，或者本地是否0接收所有消息
	if(Address && Address != entity.Address) return false;
	//this->_port->Write(String("Dispatch"));
	// 检查Crc
	if(entity.Crc != entity.Crc2)
	{
		entity.SetError(ModbusErrors::Crc);
		return true;
	}

	return true;
}
