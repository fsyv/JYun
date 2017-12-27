#pragma once
#pragma execution_character_set("utf-8")

#include "../basic/BasicWidget.h"

#include <QWidget>

class JYunApplication : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunApplication(BasicWidget *parent = Q_NULLPTR);
	~JYunApplication();
};
