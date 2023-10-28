#include "stdafx.hpp"

namespace
{
	class PlaybackStatisticsCollector : public playback_statistics_collector
	{
	public:
		void on_item_played(metadb_handle_ptr handle) final
		{
			auto handles = pfc::list_single_ref_t<metadb_handle_ptr>(handle);
			PanelManager::get()->notify_handles(CallbackID::on_item_played, handles);
		}
	};

	FB2K_SERVICE_FACTORY(PlaybackStatisticsCollector);
}
