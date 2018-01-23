#include "stdafx.h"
#include "WidgetCreatedEvent.h"


WidgetCreatedEvent::WidgetCreatedEvent(QEvent::Type type):
	QEvent(type)
{
}


WidgetCreatedEvent::~WidgetCreatedEvent()
{
}
