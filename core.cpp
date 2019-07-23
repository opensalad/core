#include "core.h"

#include <plugin.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLibrary>
#include <QDebug>

namespace ad
{
	Core* Core::__instance = nullptr;

	Core::Core()
	{
		QFile plugins_file("plugins.json");
		plugins_file.open(QIODevice::ReadOnly);
		if(!plugins_file.isOpen())
			return;

		QJsonArray plg_list = QJsonDocument::fromJson(plugins_file.readAll()).array();
		for(QJsonValue plg : plg_list)
			loadPlugin(plg.toString());
	}

	Core* Core::instance()
	{
		return __instance == nullptr ? __instance = new Core : __instance;
	}

	Plugin<Core::string_t>* Core::findPlugin(Core::string_t const &plugin_uuid) const
	{
		return __plugin_map.value(plugin_uuid, nullptr);
	}

	Plugin<Core::string_t>* Core::loadPlugin(Core::string_t const &plugin)
	{
		typedef Plugin<string_t>* (*PluginLoaderFunction) (Core*);
		QLibrary lib(plugin);
		PluginLoaderFunction loadPlg = (PluginLoaderFunction)lib.resolve(plugin, "getInstance");
		if(loadPlg == nullptr)
		{
			qDebug() << lib.errorString();
			return nullptr;
		}

		Plugin<string_t> *plg = loadPlg(this);
		registerPlugin(plg);
		return plg;
	}

	void Core::unloadPlugin(Core::string_t const &plugin)
	{

	}

	void Core::registerPlugin(ad::Plugin<Core::string_t> *plugin)
	{
		plugin->setManager(this);
		__plugin_map.insert(plugin->uuid(), plugin);

		for(Plugin<string_t> *old_plg : __plugin_map.values()) {
			if(old_plg == plugin)
				continue;

			old_plg->onPluginLoaded(plugin);	
		}
	}

	void Core::unregisterPlugin(Plugin<Core::string_t> *plugin)
	{

	}
}
