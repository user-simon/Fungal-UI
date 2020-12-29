#include "pch.h"
using namespace fungal;

container_control::container_control()
{
	m_selected = m_controls.end();
}

container_control::~container_control()
{
	std::vector<control*> controls_copy(m_controls);

	for (control* c : controls_copy)
		ui.remove(c);
}

void container_control::_on_key_down(key_event& event)
{
	if (!m_controls.empty() && (event.code == VK_LEFT || event.code == VK_RIGHT))
	{
		control* old_selected = selected_control();
		
		if (event.code == VK_LEFT)
		{
			if (m_selected > m_controls.begin())
				m_selected--;
			else
				m_selected = m_controls.end() - 1;
		}
		else
		{
			if (m_selected < m_controls.end() - 1)
				m_selected++;
			else
				m_selected = m_controls.begin();
		}

		// update old and new selected control
		old_selected->_invalidate(CASCADE::NONE);
		selected_control()->_invalidate(CASCADE::NONE);
		_invalidate();
	}
	else
	{
		control::_on_key_down(event);
	}
}

void container_control::_update_body()
{
	for (control* c : controls())
		_body->add(c->body());
}

void container_control::_invalidate(CASCADE cascade)
{
	if (cascade == CASCADE::DOWN)
	{
		for (control* child : m_controls)
			child->_invalidate(CASCADE::DOWN);
	}
	else
	{
		if (!m_controls.empty())
			selected_control()->_invalidate(CASCADE::NONE);
	}
	control::_invalidate(cascade);
}

void container_control::remove(control* c)
{
	std::vector<control*>::iterator it = std::find(m_controls.begin(), m_controls.end(), c);

	if (it != m_controls.end())
	{
		m_selected = m_controls.erase(it);
		_invalidate();
	}
}

void container_control::remove(std::string name)
{
	if (control* c; c = ui[name])
		remove(c);
}

control* container_control::selected_control() const
{
	if (m_controls.empty())
		return nullptr;

	return *m_selected;
}

std::vector<control*>& container_control::controls()
{
	return m_controls;
}

UINT container_control::selected_index() const
{
	return m_selected - m_controls.begin();
}

void container_control::set_selected_index(UINT index)
{
	m_selected = m_controls.begin() + index;
	_invalidate();
}

control* container_control::first_control() const
{
	if (!m_controls.empty())
		return *m_controls.begin();

	return nullptr;
}

control* container_control::last_control() const
{
	if (!m_controls.empty())
		return *(m_controls.end() - 1);

	return nullptr;
}

void container_control::add(control* c)
{
	ui.add(c);
	c->_parent = this;
	m_controls.push_back(c);
	m_selected = m_controls.begin();
	_invalidate();
}

container_control& container_control::operator<<(control* c)
{
	add(c);
	return *this;
}
