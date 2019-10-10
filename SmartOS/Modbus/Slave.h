#ifndef __Slave_H__
#define __Slave_H__

#include "Kernel\Sys.h"
#include "Net/ITransport.h"

class Modbus;
// Modbus从机
class Slave
{
public:
	byte	Address;	// 地址
	
	Slave(ITransport* port);
	~Slave();
	void Open();
private:
	static uint OnReceive(ITransport* port, Buffer& bs, void* param, void* param2);

	// 分发处理消息。返回值决定是否响应
	bool Dispatch(Modbus& entity);
private:
	ITransport* _port;	// 传输口

};

#endif
