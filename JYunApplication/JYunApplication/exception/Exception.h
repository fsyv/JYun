#pragma once
#pragma execution_character_set("utf-8")

class Exception 
{
public:
	Exception(const QString &info);
	virtual ~Exception();
};

