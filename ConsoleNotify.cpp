#include "stdafx.hpp"

namespace
{
	class ConsoleNotify : public initquit, public fb2k::console_notify
	{
	public:
		void on_init() final
		{
			if (Fb::is_v2())
			{
				fb2k::console_manager::get()->addNotify(this);
			}
		}

		void on_quit() final
		{
			if (Fb::is_v2())
			{
				fb2k::console_manager::get()->removeNotify(this);
			}
		}

		void onConsoleRefresh() final
		{
			PanelManager::get()->notify(CallbackID::on_console_refresh);
		}
	};

	FB2K_SERVICE_FACTORY(ConsoleNotify);
}
