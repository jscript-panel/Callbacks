#include "stdafx.hpp"

namespace
{
	class OutputConfigChangeCallback : public initquit, public output_config_change_callback
	{
	public:
		void on_init() final
		{
			output_manager_v2::get()->addCallback(this);
		}

		void on_quit() final
		{
			output_manager_v2::get()->removeCallback(this);
		}

		void outputConfigChanged() final
		{
			PanelManager::get()->notify(CallbackID::on_output_device_changed);
		}
	};

	FB2K_SERVICE_FACTORY(OutputConfigChangeCallback);
}
