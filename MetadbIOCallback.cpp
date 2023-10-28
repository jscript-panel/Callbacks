#include "stdafx.hpp"

namespace
{
	class MetadbIOCallback : public metadb_io_callback
	{
	public:
		void on_changed_sorted(metadb_handle_list_cref handles, bool fromhook) final
		{
			PanelManager::get()->notify_handles(CallbackID::on_metadb_changed, handles, fromhook);
		}
	};

	FB2K_SERVICE_FACTORY(MetadbIOCallback);
}
