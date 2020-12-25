#include "pch.h"
using namespace fungal;

multiselect::multiselect(std::string name, std::string title, std::vector<std::string> options, std::vector<bool> default_value)
	: control(name, title), input_control(default_value)
{
	const std::string base_name = std::string(name) + "_option";

	for (UINT i = 0; i < options.size(); i++)
		add(new checkbox(base_name + std::to_string(i), options[i]));
}

bool multiselect::_handle_input(key_event& event)
{
	return selected_control()->_handle_input(event);
}

std::vector<bool> multiselect::value()
{
	std::vector<bool> val;

	for (control* c : m_controls)
	{
		checkbox* cb = c->as<checkbox>();
		val.push_back(cb->value());
	}
	return val;
}

void multiselect::set_value(std::vector<bool> value)
{
	if (value.size() < m_controls.size())
		return;

	for (UINT i = 0; i < m_controls.size(); i++)
	{
		checkbox* cb = m_controls[i]->as<checkbox>();
		cb->set_value(value[i]);
	}
}
