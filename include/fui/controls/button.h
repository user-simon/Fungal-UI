#pragma once
#include "control.h"

namespace fungal
{
	class container_control;

	/// <summary>
	/// Control which performs an action when it is selected and the user presses enter
	/// </summary>
	class button : public control
	{
	protected:
		virtual void _update_body() override;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="text">Text shown on control</param>
		/// <param name="callback">Function to be called when the button is pressed</param>
		button(std::string name, std::string text, std::function<void(control*)> callback = 0);
	};
}
