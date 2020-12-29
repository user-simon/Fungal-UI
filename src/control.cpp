#include "pch.h"
using namespace fungal;

control::control(std::string name, std::string title, bool embedded_title)
{
	m_name = name;
	m_title = title;
	m_invalidated = true;

	_body = std::make_unique<control_body>(this, embedded_title ? "" : title);
	_parent = nullptr;
}

void control::_invalidate(CASCADE cascade)
{
	m_invalidated = true;

	if (cascade == CASCADE::UP)
	{
		if (_parent)
			_parent->_invalidate();
		else
			ui._invalidate();
	}
}

void control::_on_key_down(key_event& event)
{
	if (event.code == VK_RETURN)
		_on_enter();

	if (_handle_input(event))
		_invalidate();
}

bool control::_handle_input(key_event&)
{
	return false;
}

void control::_on_enter()
{
	if (on_enter)
		on_enter(this);
}

void control::_on_update()
{
	if (on_update)
		on_update(this);
}

control_body* control::body()
{
	if (m_invalidated)
	{
		_body->clear_content();
		_update_body();
		m_invalidated = false;

		_on_update();
	}
	return _body.get();
}

std::string control::name() const
{
	return m_name;
}

container_control* control::parent() const
{
	return _parent;
}

void control::set_parent(container_control* new_parent)
{
	if (_parent)
		_parent->remove(this);

	_parent = new_parent;

	if (_parent)
		*_parent << this;
}

std::string control::title() const
{
	return m_title;
}

void control::set_title(std::string title)
{
	m_title = title;
	_body->set_title(m_title);
	_invalidate();
}

void control::set_data(std::any get_data)
{
	m_data = get_data;
}

bool control::is_selected(bool cascade) const
{
	if (!_parent)
		return true;
	
	if (this != _parent->selected_control())
		return false;

	if (cascade)
		return _parent->is_selected(true);

	return true;
}

bool control::is_displayed() const
{
	return this == ui.displayed_control();
}
