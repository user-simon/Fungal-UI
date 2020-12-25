#include "pch.h"
using namespace fungal;

fui_main::~fui_main()
{
	exit();
}

void fui_main::_invalidate()
{
	m_invalidated = true;
}

void fui_main::init()
{
	m_running = false;
	m_displayed = nullptr;

	m_screen_buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_input_stream  = CreateFile(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	
	if (!m_screen_buffer)
		exit();

	// switch to alternate console buffer
	SetConsoleActiveScreenBuffer(m_screen_buffer);

	_hide_console_cursor();

	// get console size
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(m_screen_buffer, &csbi);
	m_width = csbi.dwSize.X;
	m_height = csbi.dwSize.Y;

	// disable syncing with c i/o for performance
	std::ios::sync_with_stdio(false);
}

void fui_main::exec()
{
	m_running = true;

	_draw();

	// poll for user input
	do
	{
		if (!m_displayed)
			continue;
		
		_read_console_input();

		if (m_invalidated)
			_draw();

	} 
	while (m_running);
}

void fui_main::_read_console_input()
{
	INPUT_RECORD record;
	DWORD read = 0;

	if (!ReadConsoleInput(m_input_stream, &record, 1, &read))
		return;
	
	// only handle key and resize events
	switch (record.EventType)
	{
		case KEY_EVENT:
		{
			const KEY_EVENT_RECORD& event_record = record.Event.KeyEvent;
			
			if (!event_record.bKeyDown)
				break;

			key_event event = 
			{
				event_record.wVirtualKeyCode,
				event_record.uChar.AsciiChar,
				event_record.dwControlKeyState
			};

			for (UINT i = 0; i < event_record.wRepeatCount; i++)
				_on_key_down(event);

			break;
		}
		case WINDOW_BUFFER_SIZE_EVENT:
		{
			const COORD& size = record.Event.WindowBufferSizeEvent.dwSize;
			_on_resize(size.X, size.Y);
			break;
		}
	}
}

void fui_main::_draw()
{
	if (m_running && m_displayed)
	{
		// draw displayed control with padding on the end of each line and to the end of the console buffer such
		// that the entire console is filled with characters in order to entirely override the previous frame

		SetConsoleCursorPosition(m_screen_buffer, { 0, 0 });
		
		const UINT console_capacity = width() * height();

		std::string buffer;
		buffer.reserve(console_capacity);

		for (std::string& line : *m_displayed->body())
		{
			if (buffer.length() == console_capacity)
				break;

			buffer += line + std::string(width() - line.length(), ' ');
		}
		ASSERT(buffer.length() <= console_capacity);

		buffer += std::string(console_capacity - buffer.length(), ' ');

		DWORD written;
		WriteConsoleA(m_screen_buffer, buffer.c_str(), console_capacity, &written, NULL);
	}
	m_invalidated = false;
}

void fui_main::_hide_console_cursor()
{
	CONSOLE_CURSOR_INFO cursor_info{ 1, false };
	SetConsoleCursorInfo(m_screen_buffer, &cursor_info);
}

void fui_main::_on_resize(UINT width, UINT height)
{
	m_width = width;
	m_height = height;

	// rehide the console cursor
	_hide_console_cursor();
	
	// redraw ui
	m_displayed->_invalidate(CASCADE::DOWN);
	_draw();
}

void fui_main::_on_key_down(key_event& event)
{
	switch (event.code)
	{
	case VK_ESCAPE:
	{
		if (m_displayed_path.size() <= 1)
			exit();
		else
			display_previous();
		break;
	}
	default:
		m_displayed->_on_key_down(event);
		break;
	}
}

UINT fui_main::height()
{
	return m_height;
}

UINT fui_main::width()
{
	return m_width;
}

void fui_main::exit()
{
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	EXIT();
}

void fui_main::stop()
{
	m_running = false;
}

void fui_main::display_previous()
{
	if (m_displayed_path.size() > 1)
	{
		m_displayed_path.pop_back();
		m_displayed = *(m_displayed_path.end() - 1);
		_draw();
	}
}

void fui_main::display(control* c)
{
	m_displayed = c;
	m_displayed_path.push_back(c);
	_draw();
}

void fui_main::display(std::string_view name)
{
	if (control* c; c = get(name))
		display(c);
}

control* fui_main::displayed_control()
{
	return m_displayed;
}

void fui_main::remove(control* c)
{
	if (container_control* parent; parent = c->parent())
		parent->remove(c);

	m_controls_lookup.erase(c->name());
}

bool fui_main::remove(std::string_view name)
{
	if (control* c; c = get(name))
	{
		remove(c);
		return true;
	}
	return false;
}

std::vector<control*> fui_main::controls()
{
	std::vector<control*> controls;

	for (auto& [name, control] : m_controls_lookup)
		controls.push_back(control.get());

	return controls;
}

bool fui_main::control_exists(std::string_view name)
{
	return m_controls_lookup.count(name);
}

control* fui_main::get(std::string_view name)
{
	if (control_exists(name))
		return m_controls_lookup[name].get();

	return nullptr;
}

control* fui_main::operator[](std::string_view name)
{
	return get(name);
}

void fui_main::add(control* c)
{
	if (control_exists(c->name()))
		remove(c->name());

	m_controls_lookup.emplace(c->name(), c);
}

fui_main& fui_main::operator<<(control* c)
{
	this->add(c);
	return *this;
}
