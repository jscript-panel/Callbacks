#include "stdafx.hpp"

namespace
{
	class PlaybackQueueCallback : public playback_queue_callback
	{
	public:
		void on_changed(t_change_origin origin) final
		{
			PanelManager::get()->notify(CallbackID::on_playback_queue_changed, origin);
		}
	};

	FB2K_SERVICE_FACTORY(PlaybackQueueCallback);
}
