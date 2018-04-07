#ifndef THREADOBJECT_H_
#define THREADOBJECT_H_

class ThreadObject
{
public:
	ThreadObject();
	virtual ~ThreadObject();

	virtual void run() = 0;
};

#endif //THREADOBJECT_H_