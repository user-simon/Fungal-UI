#include "pch.h"
using namespace fungal;

constexpr const char* BUTTON_TYPE_TITLES[] = { "OK", "Cancel", "Save", "Discard", "Yes", "No", "Retry" };

buttonbox::buttonbox(std::string name, std::string title, UINT button_types, std::function<void(buttonbox*, BUTTON_TYPE)> callback)
	: control(name, title)
{
	m_button_types = button_types;
	on_enter = callback;

	const std::string base_name = std::string(name) + "_button";

	// create the specified button types
	for (UINT i = 0; i < BUTTON_TYPE::BUTTON_TYPE_COUNT; i++)
	{
		const UINT type = 0b1 << i;

		if (button_types & type)
		{
			// create button and set button data to button type so it can be retrieved later
			button* b = new button(base_name + std::to_string(i), std::string(BUTTON_TYPE_TITLES[i]));
			b->set_data((BUTTON_TYPE)type);
			add(b);
		}
	}
}

void buttonbox::_on_enter()
{
	if (on_enter)
		on_enter(this, selected_button_type());
}

void buttonbox::_on_update()
{
	if (on_update)
		on_update(this, selected_button_type());
}

void buttonbox::_update_body()
{
	for (control* c : m_controls)
	{
		_body->append(c->body());
		_body->append(" ");
	}
}

BUTTON_TYPE buttonbox::selected_button_type()
{
	return selected_control()->get_data<BUTTON_TYPE>();
}
