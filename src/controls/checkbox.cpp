#include "pch.h"
using namespace fungal;

#define	CHAR_X (char)158

checkbox::checkbox(std::string name, std::string title, bool default_value)
	: control(name, title, true), input_control(default_value)
{
	
}

void checkbox::_update_body()
{
	std::string body = (is_selected(true) ? "[ ] " : "( ) ") + title();

	if (m_value)
		body[1] = CHAR_X;

	_body->add(body);
}

bool checkbox::_handle_input(key_event& event)
{
	switch (event.code)
	{
	case VK_RETURN:
	case VK_SPACE:
	case VK_LEFT:
	case VK_RIGHT:
		m_value = !m_value;
		return true;
	default:
		return false;
	}
}
