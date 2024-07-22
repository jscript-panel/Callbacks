#include "stdafx.hpp"

namespace
{
	class NowPlayingAlbumArtNotify : public initquit, public now_playing_album_art_notify
	{
	public:
		void on_album_art(album_art_data_ptr) final
		{
			if (!Path::now_playing().starts_with("file://"))
			{
				PanelManager::get()->notify(CallbackID::on_playback_dynamic_info_track, 1);
			}
		}

		void on_init() final
		{
			now_playing_album_art_notify_manager::get()->add(this);
		}

		void on_quit() final
		{
			now_playing_album_art_notify_manager::get()->remove(this);
		}
	};

	FB2K_SERVICE_FACTORY(NowPlayingAlbumArtNotify);
}
