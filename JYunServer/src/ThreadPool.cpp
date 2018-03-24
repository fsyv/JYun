#include "stdafx.h"

#include "ThreadPool.h"
#include "ThreadObject.h"

using namespace std;

ThreadPool::ThreadPool(int minWorker, int maxWorker) :
	m_iBossInspectionCycle(1000),
	m_bRun(true),
	m_iMaxChange(MAX_CHANGE),
	m_iMinTimer(MIN_TIMER),
	m_iMaxTimer(MAX_TIMER)
{
	//工作中的工人数量
	m_iWorking = 0;

	setScale();

	setMinWorker(minWorker);
	setMaxWorker(maxWorker);

	//创建BOSS线程
	createBoss();
}


ThreadPool::~ThreadPool()
{
	waitForAllFinished(0);
}

//添加工作
void ThreadPool::addJob(ThreadObject *job)
{

	lock_guard<mutex> lock(workerMutex);

	tasks.push(job);

	//如果任务队列数量大于1
	//就要把在休息中的老板唤醒
	//对工作进行视察
	if (tasks.size() > 1 && tasks.size() <= 2)
	{
		bossCondition.notify_one();
	}

	//唤醒一个正在休息的工人
	workerCondition.notify_one();
}

//成为老板
void ThreadPool::createBoss()
{
	boss = thread(&ThreadPool::bossJob, this);
}

//雇佣工人
void ThreadPool::hireWorker(const int &workerNumber)
{
	//一次不会超过m_iMaxChange个工人
	int amount = (workerNumber < m_iMaxChange) ? workerNumber : m_iMaxChange;

	//如果小于0视为异常
	amount = amount > 0 ? amount : 0;

	amount = workers.size() + amount < m_iMaxWorker ? amount : m_iMaxWorker - workers.size();

	for (int i = 0; i < amount; ++i)
		workers.emplace(&ThreadPool::workerJob, this);

	//修改以后老板视察频率
	if (amount > (m_iMinWorker + m_iMaxWorker) / 2)
	{
		m_iBossInspectionCycle /= m_iMaxChange;

		//老板视察时间不能小于最小时间
		m_iBossInspectionCycle = m_iBossInspectionCycle > m_iMinTimer ? m_iBossInspectionCycle : m_iMinTimer;
	}
}

//解聘工人
void ThreadPool::fireWorker(const int &workerNumber)
{
	//一次不会超过m_iMaxChange个工人
	int amount = (workerNumber < m_iMaxChange) ? workerNumber : m_iMaxChange;
	//如果小于0视为异常
	amount = amount > 0 ? amount : 0;

	amount = workers.size() - amount > m_iMinWorker ? amount : workers.size() - m_iMinWorker;

	thread headThread;
	for (int i = 0; i < amount; ++i)
	{
		headThread = move(workers.front());
		workers.pop();

		serialMutex.lock();
		workersSerialNumber[headThread.get_id()] = false;
		serialMutex.unlock();

		//让这个线程自生自灭
		headThread.detach();
	}
	workerCondition.notify_all();

	if (amount < (m_iMinWorker + m_iMaxWorker) / 2)
	{
		//减缓老板视察时间
		m_iBossInspectionCycle *= m_iMaxChange;

		//老板视察时间不能大于最小时间
		m_iBossInspectionCycle = (m_iBossInspectionCycle < m_iMaxTimer) ? m_iBossInspectionCycle : m_iMaxTimer;
	}
}

//设置最大等待比
void ThreadPool::setScale(const double &scale)
{
	m_dWWScale = scale;
}

//等待所有工作完成
//默认等待30秒
void ThreadPool::waitForAllFinished(long ms)
{
	ms = ms > 0 ? ms : 0;
	ms = ms < 30000 ? ms : 30000;

	clock_t start = clock();
	clock_t current;

	long timeLength = 0L;

	while (timeLength < ms)
	{
		current = clock();
		timeLength = current - start;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	//this_thread::sleep_for(std::chrono::milliseconds(ms));

	m_bRun = false;
	bossCondition.notify_one();
	if (boss.joinable())
		boss.join();
}

void ThreadPool::setMaxWorker(const int &workerNumber)
{
	//当前CPU最大并行线程
	int maxConcurrent = thread::hardware_concurrency();
	maxConcurrent = maxConcurrent > 0 ? maxConcurrent : 1;

	//防止线程池线程数量大于CPU的并行线程数量。
	maxConcurrent = workerNumber < maxConcurrent ? workerNumber : maxConcurrent;
	//防止比最小线程数量少而引发异常
	m_iMaxWorker = maxConcurrent > m_iMinWorker ? maxConcurrent : m_iMinWorker;
}

void ThreadPool::setMinWorker(const int &workerNumber)
{
	m_iMinWorker = workerNumber > 1 ? workerNumber : 1;
}

//老板的工作
void ThreadPool::bossJob()
{
	int worker = 0;
	while (m_bRun)
	{

		if (workers.size() < m_iMinWorker)
		{
			//不低于最小员工数量
			hireWorker(m_iMinWorker);
		}

		unique_lock<mutex> lock(bossMutex);
		//如果工人数量等于m_iMinWorker，且没有任务
		//老板则进入休息状态	
		bossCondition.wait(lock, [this] {
			if (workers.size() == m_iMinWorker && tasks.empty() && m_bRun)
			{
				//监视间隔恢复
				m_iBossInspectionCycle = m_iMaxTimer;
				return false;
			}

			return true;
		});
		lock.unlock();

		//得出理论工作量
		//这里没有处理线程同步，是一个瞬时值
		//在雇佣或者解雇人的时候时候会根据事件情况为依据
		//这里只是老板给出的一个参考
		//按当前工作量的一个比值来算
		m_iTheoryWorking = int(tasks.size() * m_dWWScale);
		worker = workers.size();
		if (worker < m_iTheoryWorking)
		{
			//实际工作量小于理论工作量
			//招人
			hireWorker(m_iTheoryWorking - worker);
		}
		else if (worker > m_iTheoryWorking)
		{
			//实际工作量大于理论工作量
			//裁员
			fireWorker(worker - m_iTheoryWorking);
		}

		this_thread::sleep_for(chrono::milliseconds(m_iBossInspectionCycle));
	}

	//告诉所有工人把手中的工作做完就下班了
	thread headThread;
	while (workers.size())
	{
		headThread = move(workers.front());
		workers.pop();

		serialMutex.lock();
		workersSerialNumber[headThread.get_id()] = false;
		serialMutex.unlock();

		//让这个线程自生自灭
		if (headThread.joinable())
			headThread.detach();
	}

	workerCondition.notify_all();
}

//工人的工作
void ThreadPool::workerJob()
{
	ThreadObject *object = nullptr;

	serialMutex.lock();
	workersSerialNumber.insert(map<thread::id, bool>::value_type(this_thread::get_id(), true));
	serialMutex.unlock();

	while (workersSerialNumber[this_thread::get_id()])
	{
		unique_lock<mutex> lock(workerMutex);

		workerCondition.wait(lock, [this] {
			//队列不为空或者workersSerialNumber值为false就不用塞
			return !tasks.empty() && workersSerialNumber[this_thread::get_id()];
		});

		if (tasks.empty() || !workersSerialNumber[this_thread::get_id()])
			continue;

		object = tasks.front();
		tasks.pop();
		++m_iWorking;

		lock.unlock();

		if (object)
			object->run();

		lock.lock();

		--m_iWorking;

		lock.unlock();
	}

	serialMutex.lock();
	workersSerialNumber.erase(this_thread::get_id());
	serialMutex.unlock();
}

