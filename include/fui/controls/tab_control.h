#pragma once
#include "container_control.h"

namespace fui
{
	class page;

	/// <summary>
	/// Work in progress
	/// </summary>
	class tab_control : public container_control
	{
	private:
		tab_control(std::string name, page* parent, std::string title, std::vector<page*> pages = {});

		// control overrides

		void _update_body() override;
		void _handle_input(int key, int nav) override;
	};
}
