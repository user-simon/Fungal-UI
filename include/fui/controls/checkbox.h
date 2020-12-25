#pragma once
#include "input_control.h"

namespace fungal
{
	class container_control;

	/// <summary>
	/// Control for getting a boolean input
	/// </summary>
	class checkbox : public input_control<bool>
	{
	protected:
		void _update_body() override;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="title">Text shown on control</param>
		/// <param name="default_val">Default value of the checkbox</param>
		checkbox(std::string name, std::string title, bool default_value = false);

		// control overrides

		bool _handle_input(key_event&) override;
	};
}
