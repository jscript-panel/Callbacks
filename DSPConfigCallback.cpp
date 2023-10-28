#include "stdafx.hpp"

namespace
{
	class DSPConfigCallback : public dsp_config_callback
	{
	public:
		void on_core_settings_change(const dsp_chain_config&) final
		{
			PanelManager::get()->notify(CallbackID::on_dsp_preset_changed);
		}
	};

	FB2K_SERVICE_FACTORY(DSPConfigCallback);
}
