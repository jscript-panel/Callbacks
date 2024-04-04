#include "stdafx.hpp"

namespace
{
	class PlayCallbackStatic : public play_callback_static
	{
	public:
		uint32_t get_flags() final
		{
			return flag_on_playback_all | flag_on_volume_change;
		}

		void on_playback_dynamic_info(const file_info&) final
		{
			PanelManager::get()->notify(CallbackID::on_playback_dynamic_info);
		}

		void on_playback_dynamic_info_track(const file_info&) final
		{
			PanelManager::get()->notify(CallbackID::on_playback_dynamic_info_track, 0);
		}

		void on_playback_edited(metadb_handle_ptr handle) final
		{
			auto handles = pfc::list_single_ref_t<metadb_handle_ptr>(handle);
			PanelManager::get()->notify_handles(CallbackID::on_playback_edited, handles);
		}

		void on_playback_new_track(metadb_handle_ptr handle) final
		{
			auto handles = pfc::list_single_ref_t<metadb_handle_ptr>(handle);
			PanelManager::get()->notify_handles(CallbackID::on_playback_new_track, handles);
		}

		void on_playback_pause(bool state) final
		{
			PanelManager::get()->notify(CallbackID::on_playback_pause, state);
		}

		void on_playback_seek(double time) final
		{
			PanelManager::get()->notify_args(CallbackID::on_playback_seek, { time });
		}

		void on_playback_starting(playback_control::t_track_command cmd, bool paused) final
		{
			PanelManager::get()->notify_args(CallbackID::on_playback_starting, { cmd, paused });
		}

		void on_playback_stop(playback_control::t_stop_reason reason) final
		{
			PanelManager::get()->notify(CallbackID::on_playback_stop, reason);
		}

		void on_playback_time(double time) final
		{
			PanelManager::get()->notify(CallbackID::on_playback_time, js::to_uint(time));
		}

		void on_volume_change(float new_val) final
		{
			PanelManager::get()->notify_args(CallbackID::on_volume_change, { new_val });
		}
	};

	FB2K_SERVICE_FACTORY(PlayCallbackStatic);
}
