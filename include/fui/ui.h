#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

#include "control.h"

namespace fungal
{
	template<typename>
	class input_control;

	/// <summary>
	/// FUI foundational class
	/// </summary>
	class fui_main
	{
	private:
		std::unordered_map<std::string_view, std::unique_ptr<control>> m_controls_lookup;
		std::vector<control*> m_displayed_path;

		bool m_invalidated;
		bool m_running;
		control* m_displayed;
		UINT m_height;
		UINT m_width;

		void* m_screen_buffer;
		void* m_input_stream;

	private:
		/// <summary>
		/// Gets input and sends it further to displayed_control
		/// </summary>
		void _read_console_input();

		void _on_resize(UINT width, UINT height);
		void _on_key_down(key_event&);

		void _hide_console_cursor();
		
	public:
		~fui_main();

		/// <summary>
		/// Tells the ui to redraw
		/// </summary>
		void _invalidate();

		/// <summary>
		/// Initializes the console and ui
		/// </summary>
		void init();

		/// <summary>
		/// Draws the displayed control
		/// </summary>
		void _draw();

		/// <summary>
		/// Gets the height of the ui, in characters
		/// </summary>
		UINT height();

		/// <summary>
		/// Gets the width of the ui, in characters
		/// </summary>
		UINT width();

		/// <summary>
		/// Draws the ui and starts listening for input
		/// </summary>
		[[blocking]]
		void exec();

		/// <summary>
		/// Closes down the program and switches back to the standard console buffer
		/// </summary>
		[[noreturn]]
		void exit();

		/// <summary>
		/// Stops drawing and listening for input. Restart by calling exec
		/// </summary>
		void stop();
		
		/// <summary>
		/// Displays to the previously displayed control
		/// </summary>
		void display_previous();
		
		/// <summary>
		/// Set which control is displayed in the ui
		/// </summary>
		void display(control*);

		/// <summary>
		/// Set which control is displayed in the ui
		/// </summary>
		/// <param name="name">Name of the control</param>
		void display(std::string_view name);

		/// <summary>
		/// Gets the control currently displayed in the ui
		/// </summary>
		control* displayed_control();

		/// <summary>
		/// Removes control from the ui. Throws an error if the control does not exist within the ui
		/// </summary>
		void remove(control*);
		
		/// <summary>
		/// Removes control from the ui
		/// </summary>
		/// <param name="name">Name of the control</param>
		/// <returns>Returns success</returns>
		bool remove(std::string_view name);

		/// <summary>
		/// Gets all controls in the ui
		/// </summary>
		std::vector<control*> controls();

		/// <summary>
		/// Checks if control exists in ui
		/// </summary>
		/// <param name="name">Name of the control</param>
		bool control_exists(std::string_view name);

		/// <summary>
		/// Gets pointer to control from its name
		/// </summary>
		control* get(std::string_view name);

		/// <summary>
		/// Synonym of get
		/// </summary>
		control* operator[](std::string_view name);

		/// <summary>
		/// Adds control to ui.
		/// </summary>
		void add(control*);

		/// <summary>
		/// Synonym of add but allows stringing creation of controls together
		/// </summary>
		fui_main& operator<<(control*);

		/// <summary>
		/// Gets pointer to control from its name and casts it to expected control type. Constraints should be added in C++20
		/// </summary>
		/// <typeparam name="control_t">Expected type of control</typeparam>
		/// <param name="name">Name of control</param>
		template<class CONTROL_T>
		CONTROL_T* get_as(std::string_view name);

		/// <summary>
		/// Gets value of expected type from an input_control. 
		/// </summary>
		/// <typeparam name="value_t">Expected type of value</typeparam>
		/// <param name="name">Name of input_control</param>
		template<typename VALUE_T>
		VALUE_T& get_value(std::string_view name);
	};

	// templated function definitions

	template<class CONTROL_T>
	CONTROL_T* fui_main::get_as(std::string_view name)
	{
		return get(name)->as<CONTROL_T>();
	}

	template<typename VALUE_T>
	VALUE_T& fui_main::get_value(std::string_view name)
	{
		input_control<VALUE_T>* c = get_as<input_control<VALUE_T>>(name);
		return c->value();
	}

	// "singleton" object

	inline fui_main ui;
}
