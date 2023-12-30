#include "stdafx.hpp"

namespace
{
	class PlaylistCallbackStatic : public playlist_callback_static
	{
	public:
		void on_default_format_changed() final {}
		void on_items_modified_fromplayback(size_t, const pfc::bit_array&, playback_control::t_display_level) final {}
		void on_items_removing(size_t, const pfc::bit_array&, size_t, size_t) final {}
		void on_playlists_removing(const pfc::bit_array&, size_t, size_t) final {}

		uint32_t get_flags() final
		{
			return flag_on_item_ensure_visible | flag_on_item_focus_change | flag_on_items_added | flag_on_items_modified |
				flag_on_items_removed | flag_on_items_reordered | flag_on_items_replaced | flag_on_items_selection_change |
				flag_on_playback_order_changed | flag_on_playlist_activate | flag_on_playlist_created | flag_on_playlist_locked |
				flag_on_playlists_removed | flag_on_playlist_renamed | flag_on_playlists_reorder;
		}

		void on_item_ensure_visible(size_t playlist, size_t index) final
		{
			PanelManager::get()->notify_args(CallbackID::on_playlist_item_ensure_visible, { playlist, index });
		}

		void on_item_focus_change(size_t playlist, size_t from, size_t to) final
		{
			PanelManager::get()->notify_args(CallbackID::on_item_focus_change, { playlist, from, to });
		}

		void on_items_added(size_t playlist, size_t, metadb_handle_list_cref, const pfc::bit_array&) final
		{
			PanelManager::get()->notify(CallbackID::on_playlist_items_added, playlist);
		}

		void on_items_modified(size_t playlist, const pfc::bit_array&) final
		{
			PanelManager::get()->notify(CallbackID::on_playlist_items_changed, playlist);
		}

		void on_items_removed(size_t playlist, const pfc::bit_array&, size_t, size_t new_count) final
		{
			PanelManager::get()->notify_args(CallbackID::on_playlist_items_removed, { playlist, new_count });
		}

		void on_items_reordered(size_t playlist, const size_t*, size_t) final
		{
			PanelManager::get()->notify(CallbackID::on_playlist_items_reordered, playlist);
		}

		void on_items_replaced(size_t playlist, const pfc::bit_array&, const pfc::list_base_const_t<t_on_items_replaced_entry>&) final
		{
			PanelManager::get()->notify(CallbackID::on_playlist_items_replaced, playlist);
		}

		void on_items_selection_change(size_t, const pfc::bit_array&, const pfc::bit_array&) final
		{
			PanelManager::get()->notify(CallbackID::on_playlist_items_selection_change);
		}

		void on_playback_order_changed(size_t new_index) final
		{
			PanelManager::get()->notify(CallbackID::on_playback_order_changed, new_index);
		}

		void on_playlist_activate(size_t old_index, size_t new_index) final
		{
			if (old_index != new_index)
			{
				PanelManager::get()->notify(CallbackID::on_playlist_switch);
			}
		}

		void on_playlist_created(size_t, const char*, size_t) final
		{
			PanelManager::get()->notify(CallbackID::on_playlists_changed);
		}

		void on_playlist_locked(size_t, bool) final
		{
			PanelManager::get()->notify(CallbackID::on_playlists_changed);
		}

		void on_playlist_renamed(size_t, const char*, size_t) final
		{
			PanelManager::get()->notify(CallbackID::on_playlists_changed);
		}

		void on_playlists_removed(const pfc::bit_array&, size_t, size_t) final
		{
			PanelManager::get()->notify(CallbackID::on_playlists_changed);
		}

		void on_playlists_reorder(const size_t*, size_t) final
		{
			PanelManager::get()->notify(CallbackID::on_playlists_changed);
		}
	};

	FB2K_SERVICE_FACTORY(PlaylistCallbackStatic);
}
