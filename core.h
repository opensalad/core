#pragma once

#include "core_global.h"
#include <plugin_mgr.h>
#include <QString>
#include <QMap>

namespace ad
{
	class CORE_EXPORT Core : public PluginManager<QString>
	{
		using string_t = QString;
		using map_t = QMap<string_t, ad::Plugin<string_t>*>;

	private:
		Core();

	public:
		static Core* instance();

		Plugin<string_t>* findPlugin(string_t const&plugin_uuid) const override;
		Plugin<string_t>* loadPlugin(string_t const&plugin) override;
		void unloadPlugin(string_t const&plugin) override;
		void registerPlugin(Plugin<string_t> *plugin) override;
		void unregisterPlugin(Plugin<string_t> *plugin) override;

	private:
		map_t __plugin_map;
		static Core* __instance;
	};
}