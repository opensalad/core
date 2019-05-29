#include "core.h"
#include <QUuid>

Core* Core::__instance = nullptr;

Core::Core() {}

Core* Core::instance()
{
	return __instance == nullptr ? __instance = new Core : __instance;
}

Plugin* Core::findPlugin(QUuid const& plugin_uuid)
{
	return __plugin_map.value(plugin_uuid, nullptr);
}

void Core::registerPlugin(Plugin* plugin)
{
	__plugin_map.insert(plugin->uuid(), plugin);
}