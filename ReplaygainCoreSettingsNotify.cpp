#include "stdafx.hpp"

namespace
{
	class ReplaygainCoreSettingsNotify : public initquit, public replaygain_core_settings_notify
	{
	public:
		void on_changed(const t_replaygain_config& cfg) final
		{
			PanelManager::get()->notify(CallbackID::on_replaygain_mode_changed, cfg.m_source_mode);
		}

		void on_init() final
		{
			replaygain_manager_v2::get()->add_notify(this);
		}

		void on_quit() final
		{
			replaygain_manager_v2::get()->remove_notify(this);
		}
	};

	FB2K_SERVICE_FACTORY(ReplaygainCoreSettingsNotify);
}
