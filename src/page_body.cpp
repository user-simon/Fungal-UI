#include "pch.h"
using namespace fungal;

#define INDENT_FACTOR	 0.14f
#define SELECTED_FACTOR	 0.8f
#define TITLE_FACTOR	 INDENT_FACTOR * SELECTED_FACTOR
#define SCROLLBAR_FACTOR SELECTED_FACTOR * 0.5f

#define CHAR_VERT_LINE (char)179
#define CHAR_HORI_LINE (char)196

page_body::page_body(page* owner, std::string title) :
	control_body(owner)
{
	set_title(title);
}

void page_body::set_title(std::string title)
{
	m_title = 
	{
		"",
		"",
		title,
		std::string(title.length(), CHAR_HORI_LINE),
		"",
	};

	for (std::string& line : m_title)
		line = _title_indent() + line;

	_invalidate();
}

void page_body::set_scrollbar(std::string scrollbar)
{
	m_scrollbar = scrollbar;
}

void page_body::newline(UINT n)
{
	for (UINT i = 0; i < n; i++)
		add(std::string(), false);
}

void page_body::add(std::string string, bool selected)
{
	control_body::add(_content_indent(selected) + string);
	_invalidate();
}

void page_body::add(control_body* body, UINT begin, UINT end)
{
	if (!body->height())
		return;

	if (end)
		end = std::min(end, body->height());
	else
		end = body->height();
	
	for (body_rows_t::iterator it = body->begin() + begin; it < body->begin() + end; it++)
		add(*it, body->owner()->is_selected());
}

std::string page_body::_content_indent(bool selected)
{
	std::string indent(ui.width() * INDENT_FACTOR, ' ');

	if (selected)
		indent[indent.length() * SELECTED_FACTOR] = CHAR_VERT_LINE;
	
	if (!m_scrollbar.empty())
	{
		indent[indent.length() * SCROLLBAR_FACTOR] = m_scrollbar[0];
		m_scrollbar.erase(m_scrollbar.begin());
	}
	return indent;
}

std::string page_body::_title_indent()
{
	static const std::string title_indent(ui.width() * TITLE_FACTOR, ' ');
	return title_indent;
}
