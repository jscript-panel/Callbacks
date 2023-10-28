#include "stdafx.hpp"

namespace
{
	class ConfigObjectNotify : public config_object_notify
	{
	public:
		GUID get_watched_object(size_t index) final
		{
			return *guids::watched_objects[index].first;
		}

		size_t get_watched_object_count() final
		{
			return guids::watched_objects.size();
		}

		void on_watched_object_changed(const config_object::ptr& object) final
		{
			const auto it = std::ranges::find_if(guids::watched_objects, [g = object->get_guid()](const auto& item) { return g == *item.first; });
			if (it != guids::watched_objects.end())
			{
				const bool b = object->get_data_bool_simple(false);
				PanelManager::get()->notify(it->second, b);
			}
		}
	};

	FB2K_SERVICE_FACTORY(ConfigObjectNotify);
}
