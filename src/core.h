#ifndef CORE_H
#define CORE_H

#include "core_global.h"
#include "plugin_base.h"
#include <QMap>

class QUuid;

class CORE_EXPORT Core
{
private:
	Core();
	Core(Core const&) = delete;
	Core& operator = (Core const&) = delete;
	~Core() = delete;

public:
	static Core* instance();

	Plugin* findPlugin(QUuid const& plugin_uuid);
	void registerPlugin(Plugin* plugin);

	template <typename T>
	T* findPlugin();

private:
	QMap<QUuid, Plugin*> __plugin_map;
	static Core* __instance;
};

template <typename T>
T* Core::findPlugin()
{
	static_assert(std::is_base_of<Plugin, T>::value, "The plugin must be derived from the \"Plugin\" class.");
	for (Plugin* i : Core::__plugin_map.values())
	{
		T* plugin = dynamic_cast<T*>(i);

		if (plugin != nullptr)
			return plugin;
	}

	return nullptr;
}

#endif