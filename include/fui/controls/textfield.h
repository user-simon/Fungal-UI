#pragma once
#include "input_control.h"

namespace fungal
{
	/// <summary>
	/// Control for getting text input. Password input also supported through the hide flag
	/// </summary>
	class textfield : public input_control<std::string>
	{
	private:
		std::string::iterator m_caret;
		bool m_hide;

	protected:
		/// <summary>
		/// Gets the beginning of the closests block of non-blank characters in specified direction
		/// </summary>
		std::string::iterator _find_jump_point(const bool right);
		
		void _update_body() override;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="hide_chars">Toggle to hide the content</param>
		textfield(std::string name, std::string title, std::string default_value = "", const bool hide = false);
		
		/// <summary>
		/// Gets whether the textfield currently displays the content
		/// </summary>
		bool hidden();

		/// <summary>
		/// Sets whether the textfield currently displays the content
		/// </summary>
		void set_hidden(const bool hide_chars);

		// input_control overrides

		void set_value(std::string value) override;

		// control overrides

		bool _handle_input(key_event&) override;
	};
}
