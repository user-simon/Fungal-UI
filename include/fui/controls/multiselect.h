#pragma once
#include "container_control.h"
#include "input_control.h"

namespace fungal
{
	/// <summary>
	/// Control for getting multiple boolean inputs
	/// </summary>
	class multiselect : public container_control, public input_control<std::vector<bool>>
	{
	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="title">Text shown on control</param>
		/// <param name="options">Titles of the options to be displayed in the control</param>
		/// <param name="default_val">Default values of the multiselect checkboxes</param>
		multiselect(std::string name, std::string title, std::vector<std::string> options, std::vector<bool> default_values = {});
		
		// input_control overrides
		
		std::vector<bool> value() override;
		void set_value(std::vector<bool> value) override;

		// control

		virtual bool _handle_input(key_event&) override;
	};
}
