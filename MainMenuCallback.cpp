#include "stdafx.hpp"

namespace
{
	class MainMenuCallback : public mainmenu_commands
	{
	public:
		GUID get_command(uint32_t index) final
		{
			switch (index)
			{
			case 0: return guids::mainmenu_one;
			case 1: return guids::mainmenu_two;
			case 2: return guids::mainmenu_three;
			case 3: return guids::mainmenu_four;
			case 4: return guids::mainmenu_five;
			case 5: return guids::mainmenu_six;
			case 6: return guids::mainmenu_seven;
			case 7: return guids::mainmenu_eight;
			case 8: return guids::mainmenu_nine;
			case 9: return guids::mainmenu_ten;
			default: FB2K_BugCheck();
			}
		}

		GUID get_parent() final
		{
			return guids::mainmenu_group;
		}

		bool get_description(uint32_t index, pfc::string_base& out) final
		{
			if (index >= count) FB2K_BugCheck();

			out = fmt::format("Invoke on_main_menu({})", ++index);
			return true;
		}

		bool get_display(uint32_t index, pfc::string_base& out, uint32_t& flags) final
		{
			if (index >= count) FB2K_BugCheck();

			get_name(index, out);
			flags = mainmenu_commands::flag_defaulthidden;
			return true;
		}

		uint32_t get_command_count() final
		{
			return count;
		}

		void execute(uint32_t index, service_ptr_t<service_base>) final
		{
			if (index >= count) FB2K_BugCheck();

			PanelManager::get()->notify(CallbackID::on_main_menu, ++index);
		}

		void get_name(uint32_t index, pfc::string_base& out) final
		{
			if (index >= count) FB2K_BugCheck();

			out = std::to_string(++index);
		}

	private:
		static constexpr uint32_t count = 10U;
	};

	static mainmenu_group_popup_factory g_mainmenu_group(guids::mainmenu_group, mainmenu_groups::file, mainmenu_commands::sort_priority_base, Component::name.data());

	FB2K_SERVICE_FACTORY(MainMenuCallback);
}
