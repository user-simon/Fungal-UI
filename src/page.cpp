#include "pch.h"
using namespace fungal;

#define SCROLLBAR_HANDLE_CHAR (char)186

page::page(std::string name, std::string title) :
	control(name, title)
{
	m_scroll_offset = 0;
	_body = std::make_unique<page_body>(this, title);
}

void page::_update_body()
{
	if (m_controls.empty())
		return;

	// update pos of all controls

	UINT pos = 0;

	for (control* c : m_controls)
	{
		c->body()->set_pos(pos);
		pos += c->body()->height() + 1;
	}
	
	control* last = last_control();

	// check if controls are in bounds

	const UINT content_height = pos;
	const UINT view_height = ui.height() - _body->title().size();
	
	// always set scrollbar so it can be reset, should some controls be removed
	std::string scrollbar = "";

	// set scrollbar if controls are out of bounds
	if (content_height > view_height)
	{
		const UINT scrollbar_height = view_height - 1;
		scrollbar.reserve(scrollbar_height);

		// with a higher precision, one could reasonably round both height and pos
		// but since the margin of error is so low (due to one pixel essentially being
		// an entire char in the console) we floor one and ceil the other to make sure
		// that they line up, avoiding an issue where the handle would either go out of
		// bounds or stop one char before the bottom

		const UINT handle_space  = scrollbar_height - 2;
		const UINT handle_height = std::floor(((float)view_height     / content_height) * handle_space);
		const UINT handle_pos    = std::ceil (((float)m_scroll_offset / content_height) * handle_space);

		scrollbar = std::string(handle_space - handle_height, ' ');
		scrollbar.insert(handle_pos, std::string(handle_height, SCROLLBAR_HANDLE_CHAR));
		scrollbar = '^' + scrollbar + 'v';
	}

	// use _body_raw to get the body pointer instead of _body since _body is just a control_body*
	page_body* body = (page_body*)_body.get();
	body->set_scrollbar(scrollbar);
	
	// add controls to body

	const UINT view_top = m_scroll_offset;
	const UINT view_bottom = m_scroll_offset + view_height;

	for (control* c : m_controls)
	{
		control_body* c_body = c->body();

		const int delta_top	   = c_body->bottom() - view_top;
		const int delta_bottom = view_bottom - c_body->top();
		
		// ignore controls above our view
		if (delta_top <= 0)
			continue;

		// ignore all remaining controls when a control is below our view
		if (delta_bottom <= 0)
			break;

		UINT begin = 0;
		UINT end = 0;
		
		// check if control is cut off at the top
		if (delta_top < c_body->height())
			begin = c_body->height() - delta_top;

		// check if control is cut off at the bottom
		if (delta_bottom < c_body->height())
			end = delta_bottom;

		body->add(c->body(), begin, end);

		if (c_body->bottom() < view_bottom)
			body->newline();
	}
}

void page::_on_key_down(key_event& event)
{
	if (event.code == VK_RETURN)
		_on_enter();

	if (m_controls.empty())
		return;
	
	bool up   = event.code == VK_UP   || event.code == VK_TAB &&   event.control & SHIFT_PRESSED;
	bool down = event.code == VK_DOWN || event.code == VK_TAB && !(event.control & SHIFT_PRESSED);
	
	if (up || down)
	{
		control* prev_selected = selected_control();

		// determine if we should scroll up or down depending on whether we should wrap-around
		// or just go up/down by one
		if (up)
		{
			if (m_selected == m_controls.begin())
			{
				m_selected = m_controls.end() - 1;

				up   = 0;
				down = 1;
			}
			else
			{
				m_selected--;
			}
		}
		else
		{
			if (m_selected == m_controls.end() - 1)
			{
				m_selected = m_controls.begin();

				down = 0;
				up   = 1;
			}
			else
			{
				m_selected++;
			}
		}

		control_body* c_body = selected_control()->body();

		// calculate scroll index so scrolled-to control is always visible
		if (up)
		{
			// checks if control is cut off at the top
			if (c_body->top() < m_scroll_offset)
				m_scroll_offset = c_body->top();
		}
		else
		{
			// checks if control is cut off at the bottom
			if (c_body->bottom() >= m_scroll_offset + ui.height() - _body->title().size())
				m_scroll_offset = c_body->bottom() - ui.height() + _body->title().size() + 1;
		}

		// update old and new selected control
		prev_selected->_invalidate(CASCADE::NONE);
		selected_control()->_invalidate(CASCADE::NONE);
		_invalidate();
	}
	else
	{
		selected_control()->_on_key_down(event);
	}
}

page_body* page::body()
{
	return (page_body*)control::body();
}

void page::reset()
{
	if (m_controls.empty())
		return;

	for (control* c : m_controls)
		c->reset();

	m_selected = m_controls.begin();
}
