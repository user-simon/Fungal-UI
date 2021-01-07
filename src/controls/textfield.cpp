#include "pch.h"
using namespace fungal;

textfield::textfield(std::string name, std::string title, std::string default_value, const bool hide)
	: control(name, title), input_control(default_value)
{
	m_hide = hide;
	m_caret = m_value.end();
}

void textfield::_update_body()
{
	std::string content;
	
	if (m_hide)
		content = std::string(m_value.length(), '*');
	else
		content = m_value;

	// draw cursor if control is selected
	if (is_selected())
	{
		const UINT cursor_pos = m_caret - m_value.begin();
		const char cursor = cursor_pos < m_value.length() ? '|' : '_';
		content.insert(content.begin() + cursor_pos, cursor);
	}
	_body->add("> " + content);
}

bool textfield::_handle_input(key_event& event)
{
	if (iswprint(event.ascii))
	{
		m_caret = ++m_value.insert(m_caret, event.ascii);
		return true;
	}

	const bool ctrl_held = event.control & LEFT_CTRL_PRESSED;

	if (m_caret > m_value.begin())
	{
		switch (event.code)
		{
			case VK_LEFT:
			{
				if (ctrl_held)
					m_caret = _find_jump_point(0);
				else
					m_caret--;
				return true;
			}
			case VK_BACK:
			{
				if (ctrl_held)
					m_caret = m_value.erase(_find_jump_point(0), m_caret);
				else
					m_caret = m_value.erase(std::prev(m_caret));
				return true;
			}
		}
	}
	
	if (m_caret < m_value.end())
	{
		switch (event.code)
		{
			case VK_RIGHT:
			{
				if (ctrl_held)
					m_caret = _find_jump_point(1);
				else
					m_caret++;
				return true;
			}
			case VK_DELETE:
			{
				if (ctrl_held)
					m_caret = m_value.erase(m_caret, _find_jump_point(1));
				else
					m_caret = m_value.erase(m_caret);
				return true;
			}
		}
	}
	return false;
}

std::string::iterator textfield::_find_jump_point(const bool right)
{
	if (!m_hide)
	{
		std::string::iterator it = m_caret;

		while (right && it++ < m_value.end() - 1 || !right && it-- > m_value.begin() + 1)
		{
			const char current = *it;
			const char left = *(it - 1);
			
			if (iswpunct(current) && !iswpunct(left) || iswalnum(current) && !iswalnum(left))
				return it;
		}
	}
	return right ? m_value.end() : m_value.begin();
}

bool textfield::hidden()
{
	return m_hide;
}

void textfield::set_hidden(const bool hide_chars)
{
	m_hide = hide_chars;
}

void textfield::set_value(std::string value)
{
	m_value = value;
	m_caret = m_value.end();
}
