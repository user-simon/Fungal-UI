#include "pch.h"
using namespace fungal;

#define NEWLINE '\n'

control_body::control_body(control* owner, std::string title)
{
	m_owner = owner;

	if (!title.empty())
		set_title(title);

	_invalidate();
}

void control_body::_invalidate()
{
	m_invalidated = true;
}

void control_body::set_pos(UINT pos)
{
	m_pos = pos;
}

body_rows_t& control_body::rows()
{
	if (m_invalidated)
	{
		m_rows = body_rows_t(m_content);
		m_rows.insert(m_rows.begin(), m_title.begin(), m_title.end());
		m_invalidated = false;
	}
	return m_rows;
}

body_rows_t& control_body::title()
{
	return m_title;
}

void control_body::set_title(std::string title)
{
	if (title.empty())
		m_title.clear();
	else
		m_title = { title };

	_invalidate();
}

void control_body::set_title(body_rows_t& title)
{
	m_title = title;
}

body_rows_t& control_body::content()
{
	return m_content;
}

void control_body::clear_content()
{
	m_content.clear();
}

control* control_body::owner()
{
	return m_owner;
}

UINT control_body::top()
{
	return m_pos;
}

UINT control_body::bottom()
{
	return m_pos + height();
}

UINT control_body::height()
{
	return rows().size();
}

UINT control_body::width()
{
	UINT max_row_width = 0;

	for (std::string line : rows())
	{
		if (UINT length; (length = line.length()) > max_row_width)
			max_row_width = length;
	}
	return max_row_width;
}

void control_body::newline(UINT n)
{
	for (UINT i = 0; i < n; i++)
		add("");
}

body_rows_t::iterator control_body::begin()
{
	return rows().begin();
}

body_rows_t::iterator control_body::end()
{
	return rows().end();
}

void control_body::append(std::string string)
{
	if (m_content.empty())
		add(string);
	else
		*(m_content.end() - 1) += string;
}

void control_body::append(control_body* body)
{
	ASSERT(body->height() <= 1);

	if (body->height() < 1)
		return;

	append(body->rows()[0]);
}

void control_body::add(std::string string)
{
	m_content.push_back(string);
	_invalidate();
}

void control_body::add(control_body* body)
{
	m_content.insert(m_content.end(), body->begin(), body->end());
	_invalidate();
}
