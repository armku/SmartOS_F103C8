﻿#ifndef __Task_H__
#define __Task_H__

#include "Kernel\Sys.h"

class TaskScheduler;

// 任务
class Task
{
public:
	TaskScheduler* Host;

	uint	ID;			// 编号
	cstring	Name;		// 名称

	Action	Callback;	// 回调
	void*	Param;		// 参数

	int		Period;		// 周期ms
	UInt64	NextTime;	// 下一次执行时间ms

	int		Times;		// 执行次数
	int		SleepTime;	// 当前睡眠时间us
	int		Cost;		// 平均执行时间us
	int		CostMs;		// 平均执行时间ms
	int		MaxCost;	// 最大执行时间us

	bool	Enable;		// 是否启用
	bool	Event;		// 是否只执行一次后暂停的事件型任务
	byte	Deepth;		// 当前深度
	byte	MaxDeepth;	// 最大深度。默认1层，不允许重入

	Task();
	Task(const Task& task)	= delete;
	~Task();

	// 执行任务。返回是否正常执行。
	bool Execute(UInt64 now);
	// 设置任务的开关状态，同时运行指定任务最近一次调度的时间，0表示马上调度
	void Set(bool enable, int msNextTime = -1);
	// 显示状态
	void ShowStatus();

	// 全局任务调度器
	static TaskScheduler* Scheduler();
	static Task* Get(int taskid);
	static Task& Current();

private:
	friend class TaskScheduler;

	bool CheckTime(UInt64 end, bool isSleep);
	void Init();
};

// 任务调度器
class TaskScheduler
{
private:
	List<Task*>	_Tasks;	// 任务列表
	bool	_SkipSleep;	// 跳过最近一次睡眠，马上开始下一轮循环

	friend class Task;

public:
	cstring	Name;	// 系统名称
	int		Count;		// 任务个数
	Task*	Current;	// 正在执行的任务
	bool	Running;	// 是否正在运行
	bool	Sleeping;	// 如果当前处于Sleep状态，马上停止并退出
	byte	Deepth;		// 当前深度
	byte	MaxDeepth;	// 最大深度。默认5层

	int		Times;		// 执行次数
	int		Cost;		// 平均执行时间us
	UInt64	TotalSleep;	// 所有任务的总睡眠时间ms
	UInt64	LastTrace;	// 最后统计跟踪时间ms

	typedef void (*SAction)(int ms);
	SAction	EnterSleep;	// 通知外部，需要睡眠若干毫秒
	Func	ExitSleep;	// 通知外部，要求退出睡眠，恢复调度

	TaskScheduler(cstring name = nullptr);

	// 使用外部缓冲区初始化任务列表，避免频繁的堆分配
	void Set(Task* tasks, int count);
	// 查找任务 返回使用此函数的首个任务的ID
	uint FindID(Action func);
	// 查找任务 返回使用此函数的首个任务
	Task* FindTask(Action func);
	// 创建任务，返回任务编号。dueTime首次调度时间ms，-1表示事件型任务，period调度间隔ms，-1表示仅处理一次
	uint Add(Action func, void* param, int dueTime = 0, int period = 0, cstring name = nullptr);
	template<typename T>
	uint Add(void(T::*func)(), T* target, int dueTime = 0, int period = 0, cstring name = nullptr)
	{
		return Add(*(Action*)&func, target, dueTime, period, name);
	}
	void Remove(uint taskid);

	void Start();
	void Stop();
	// 执行一次循环。指定最大可用时间
	void Execute(uint msMax, bool& cancel);
	uint ExecuteForWait(uint msMax, bool& cancel);

	// 跳过最近一次睡眠，马上开始下一轮循环
	void SkipSleep();

	void ShowStatus();	// 显示状态

    Task* operator[](int taskid);
};

#endif
