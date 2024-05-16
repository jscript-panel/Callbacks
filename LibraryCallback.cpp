#include "stdafx.hpp"

namespace
{
	class LibraryCallback : public library_callback_v2
	{
	public:
		void on_items_added(metadb_handle_list_cref handles) final
		{
			if (library_manager_v4::get()->is_initialized())
			{
				PanelManager::get()->notify_handles(CallbackID::on_library_items_added, handles);
			}
		}

		void on_items_modified(metadb_handle_list_cref handles) final
		{
			PanelManager::get()->notify_handles(CallbackID::on_library_items_changed, handles, is_modified_from_hook());
		}

		void on_items_removed(metadb_handle_list_cref handles) final
		{
			if (library_manager_v4::get()->is_initialized())
			{
				PanelManager::get()->notify_handles(CallbackID::on_library_items_removed, handles);
			}
		}

		void on_library_initialized() final
		{
			PanelManager::get()->notify(CallbackID::on_library_initialised);
		}

		void on_items_modified_v2(metadb_handle_list_cref, metadb_io_callback_v2_data&) final {}
	};

	FB2K_SERVICE_FACTORY(LibraryCallback);
}
