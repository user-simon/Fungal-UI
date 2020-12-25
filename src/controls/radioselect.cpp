#include "pch.h"
using namespace fungal;

#define CHAR_ARROW_FILLED_RIGHT (char)16

// radiobutton

radiobutton::radiobutton(std::string name, std::string title, UINT index) :
	control(name, title, true)
{
	m_index = index;
}

void radiobutton::_update_body()
{
	std::string body = "    " + title();

	if (is_selected())
		body[1] = CHAR_ARROW_FILLED_RIGHT;

	_body->add(body);
}

UINT radiobutton::index()
{
	return m_index;
}

// radioselect

radioselect::radioselect(std::string name, std::string title, std::vector<std::string> options)
	: control(name, title)
{
	const std::string base_name = std::string(name) + "_option";

	for (UINT i = 0; i < options.size(); i++)
		add(new radiobutton(base_name + std::to_string(i), options[i], i));
}

UINT radioselect::index()
{
	return value()->index();
}

void radioselect::set_index(UINT index)
{
	if (index < m_controls.size())
		m_selected = m_controls.begin() + index;
}

radiobutton* radioselect::value()
{
	return (*m_selected)->as<radiobutton>();
}

void radioselect::reset()
{
	set_index(0);
}
