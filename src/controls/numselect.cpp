#include "pch.h"
using namespace fungal;

numselect::numselect(std::string name, std::string title, int min, int max, int default_value, int step)
	: control(name, title), input_control(default_value)
{
	m_min = min;
	m_max = max;
	m_step = step;

	_clamp_value();
}

void numselect::_update_body()
{
	_body->add("< " + std::to_string(m_value) + " >");
}

bool numselect::_handle_input(key_event& event)
{
	if (event.code == VK_LEFT)
		m_value -= m_step;
	else if (event.code == VK_RIGHT)
		m_value += m_step;
	else
		return false;

	_clamp_value();
	return true;
}

void numselect::_clamp_value()
{
	m_value = std::clamp(m_value, m_min, m_max);
}

int numselect::min()
{
	return m_min;
}

void numselect::set_min(int min)
{
	m_min = std::min(min, m_max);
	_clamp_value();
}

int numselect::max()
{
	return m_max;
}

void numselect::set_max(int max)
{
	m_max = std::max(max, m_min);
	_clamp_value();
}

int numselect::step()
{
	return m_step;
}

void numselect::set_step(int step)
{
	m_step = step;
}

void numselect::set_value(int val)
{
	m_value = val;
	_clamp_value();
}
