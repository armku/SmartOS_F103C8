﻿#include "Kernel\Sys.h"

#include "Interrupt.h"
#include "TTime.h"

TSys Sys;
const TTime Time;

// 系统配置
const SystemConfig g_Config = {
//SystemConfig g_Config = {
	// 操作系统 v3.2.x
	(0x03020000 | __BUILD_DATE__),
	"SmartOS_CPU",

	// 硬件
	(0x0 | __BUILD_DATE__),

	// 应用软件
	(0x0 | __BUILD_DATE__),
	(0x0 | __BUILD_DATE__),
	__BUILD_USER__,
	__BUILD_SDATE__,
};

#if defined(BOOT) || defined(APP)

struct HandlerRemap StrBoot __attribute__((at(0x2000fff0)));

#endif

// 关键性代码，放到开头
INROOT TSys::TSys()
{
	auto& cfg = g_Config;
	Config = &g_Config;

	OnInit();

	OnSleep	= nullptr;

	Code	= cfg.Code;
	Ver		= cfg.Ver;
	HardVer = cfg.HardVer;
	AppVer = cfg.AppVer;
#ifndef TINY
	Name	= cfg.Name;
	Company	= cfg.Company;
	Product = cfg.Product;

    Interrupt.Init();
#endif

	StartTimes = 1;
	HotStart = 1;

	Started	= false;
}

void TSys::Init(void)
{
	InitClock();

	// 必须在系统主频率确定以后再初始化时钟
    ((TTime&)Time).Init();
}

void TSys::ShowInfo() const
{
#if DEBUG
	debug_printf("%s::%s Code:%04X %s \r\n", Company, Name, Code, Product);
	debug_printf("Build:%s %s\r\n", __BUILD_USER__, __BUILD_STIME__);
	Version v1(AppVer);
	Version v2(HardVer);
	Version v3(Ver);
	debug_printf("AppVer:%s HardVer:%s CoreVer:%s\r\n", v1.ToString().GetBuffer(), v2.ToString().GetBuffer(), v3.ToString().GetBuffer());

	OnShowInfo();

    debug_printf("ChipID:");
	ByteArray(ID, ArrayLength(ID)).Show();

	// 新的字符串这样用会导致第一个字符被清零
	//debug_printf("\t %s", ID);
	String str;
	str.Copy(0, ID, 12);
	str.Show(true);

	debug_printf("Time : ");
	DateTime::Now().Show(false);
	debug_printf(" Start: %d/%d \r\n", HotStart, StartTimes);
	//debug_printf("Support: http://www.WsLink.cn\r\n");

    debug_printf("\r\n");
#endif
}

#define __TASK__MODULE__ 1
#ifdef __TASK__MODULE__

// 任务
#include "Task.h"

// 创建任务，返回任务编号。dueTime首次调度时间ms，period调度间隔ms，-1表示仅处理一次
uint TSys::AddTask(Action func, void* param, int dueTime, int period, cstring name) const
{
	return Task::Scheduler()->Add(func, param, dueTime, period, name);
}

void TSys::RemoveTask(uint& taskid) const
{
	if(taskid) Task::Scheduler()->Remove(taskid);
	taskid = 0;
}

// 关键性代码，放到开头
INROOT bool TSys::SetTask(uint taskid, bool enable, int msNextTime) const
{
	if(!taskid) return false;

	auto task = Task::Get(taskid);
	if(!task) return false;

	task->Set(enable, msNextTime);

	return true;
}

// 改变任务周期
INROOT bool TSys::SetTaskPeriod(uint taskid, int period) const
{
	if(!taskid) return false;

	auto task = Task::Get(taskid);
	if(!task) return false;

	if(period)
	{
		task->Period = period;

		// 改变任务周期的同时，重新计算下一次调度时间NextTime，让它立马生效
		// 否则有可能系统按照上一次计算好的NextTime再调度一次任务
		task->NextTime	= Ms() + period;
	}
	else
		task->Enable = false;

	return true;
}

void TSys::Start()
{
	OnStart();

	Started = true;

	Task::Scheduler()->Start();
}

// 延迟异步重启
void TSys::Reboot(int msDelay) const
{
	if (msDelay <= 0)Reset();

	auto func	= &TSys::Reset;
	AddTask(*(Action*)&func, (void*)this, msDelay, -1, "延迟重启");
}

// 系统启动后的毫秒数
INROOT UInt64 TSys::Ms() const { return Time.Current(); }
// 系统绝对当前时间，秒
INROOT uint TSys::Seconds() const { return Time.Seconds + Time.BaseSeconds; }

INROOT void TSys::Sleep(int ms) const
{
	// 优先使用线程级睡眠
	if(OnSleep)
		OnSleep(ms);
	else
	{
#if DEBUG
		if(ms > 1000) debug_printf("Sys::Sleep 设计错误，睡眠%dms太长！", ms);
#endif

		// 在这段时间里面，去处理一下别的任务
		if(Sys.Started && ms != 0)
		{
			bool cancel	= false;
			int ct	= Task::Scheduler()->ExecuteForWait(ms, cancel);

			if(ct >= ms) return;

			ms	-= ct;
		}
		if(ms) Time.Sleep(ms);
	}
}

INROOT void TSys::Delay(int us) const
{
	// 如果延迟微秒数太大，则使用线程级睡眠
	if(OnSleep && us >= 2000)
		OnSleep((us + 500) / 1000);
	else
	{
#if DEBUG
		if(us > 1000000) debug_printf("Sys::Sleep 设计错误，睡眠%dus太长！", us);
#endif

		// 在这段时间里面，去处理一下别的任务
		if(Sys.Started && us != 0 && us >= 1000)
		{
			bool cancel	= false;
			int ct	= Task::Scheduler()->ExecuteForWait(us / 1000, cancel);
			ct	*= 1000;

			if(ct >= us) return;

			us -= ct;
		}
		if(us) Time.Delay(us);
	}
}
#endif

/****************系统日志****************/
#include <stdarg.h>

// 打印日志
extern int SmartOS_Log(const String& msg);

extern "C"
{
	// 是否新行结尾
	static bool	newline	= false;

	WEAK int SmartOS_printf(const char* format, ...)
	{
		if(Sys.Clock == 0 || Sys.MessagePort == COM_NONE) return 0;

		char cs[512];
		int tab	= 0;

		// 先根据子任务打印缩进级别
		if(Sys.Started)
		{
			int deepth	= Task::Scheduler()->Deepth - 1;
			if(newline && deepth > 0 && (format[0] != '\0' || format[1] != '\0' || format[2] != '\0'))
			{
				String fm	= format;
				if(fm.Length() == 1)
				{
					tab	= 0;
				}
				for(int i=0; i<deepth; i++)
					cs[tab++]	= '\t';
				tab	+= snprintf(&cs[tab], sizeof(cs) - tab, "%d=>", Task::Current().ID);
			}
		}

		va_list ap;

		va_start(ap, format);
		int rs = vsnprintf(&cs[tab], sizeof(cs) - tab, format, ap);
		va_end(ap);

		// 如果格式化得到为空，则不做输出
		if(rs == 0) return rs;

		newline	= cs[tab + rs - 1] == '\r' || cs[tab + rs - 1] == '\n';

		// 必须转为cstring，否则会当作缓冲区，并把最后一个字符清零。当作缓冲区，长度加一也可以
		rs	+= SmartOS_Log(String((cstring)cs, tab + rs));

		return rs;
	}

#ifndef _MSC_VER
    /* 重载fputc可以让用户程序使用printf函数 */
    int fputc(int ch, FILE *f)
    {
#if DEBUG
        if(Sys.Clock == 0) return ch;

        int idx	= Sys.MessagePort;
        if(idx == COM_NONE) return ch;

		byte b = ch;
		SmartOS_Log(String((cstring)&b, 1));
#endif
        return ch;
    }
#endif
}

/****************系统跟踪****************/

//#if DEBUG
	#include "Device\Port.h"
	static OutputPort* _trace = nullptr;
//#endif
void TSys::InitTrace(void* port) const
{
//#if DEBUG
	_trace	= (OutputPort*)port;
//#endif
}

void TSys::Trace(int times) const
{
//#if DEBUG
	if(_trace)
	{
		while(times--) *_trace = !*_trace;
	}
//#endif
}
