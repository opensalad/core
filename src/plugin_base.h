#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H

#include <QUuid>

__interface Plugin
{
	QUuid uuid() const;
};

#endif
