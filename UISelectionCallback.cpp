#include "stdafx.hpp"

namespace
{
	class UISelectionCallback : public initquit, public ui_selection_callback
	{
	public:
		void on_init() final
		{
			ui_selection_manager_v2::get()->register_callback(this, 0);
		}

		void on_quit() final
		{
			ui_selection_manager_v2::get()->unregister_callback(this);
		}

		void on_selection_changed(metadb_handle_list_cref) final
		{
			PanelManager::get()->notify(CallbackID::on_selection_changed);
		}
	};

	FB2K_SERVICE_FACTORY(UISelectionCallback);
}
