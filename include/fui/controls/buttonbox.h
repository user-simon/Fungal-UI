#pragma once
#include "container_control.h"

namespace fungal
{
	/// <summary>
	/// Enum for the different types of buttons which can be used in a buttonbox
	/// </summary>
	enum BUTTON_TYPE : UINT
	{
		BUTTON_OK      = 0b1 << 0,
		BUTTON_CANCEL  = 0b1 << 1,
		BUTTON_SAVE    = 0b1 << 2,
		BUTTON_DISCARD = 0b1 << 3,
		BUTTON_YES     = 0b1 << 4,
		BUTTON_NO      = 0b1 << 5,
		BUTTON_RETRY   = 0b1 << 6,

		BUTTON_TYPE_COUNT = 7
	};

	/// <summary>
	/// Control for showing standard buttons such as "OK" or "CANCEL"
	/// </summary>
	class buttonbox : public container_control
	{
	private:
		UINT m_button_types;
		
	private:
		void _on_enter() override;
		void _on_update() override;

	protected:
		virtual void _update_body() override;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="button_types">Buttons to be displayed. Enter like "BUTTON_x | BUTTON_y"</param>
		/// <param name="callback">Function to be called when one of the buttons is pressed</param>
		buttonbox(std::string name, std::string title, UINT button_types, std::function<void(buttonbox*, BUTTON_TYPE)> callback);

		/// <summary>
		/// Gets which type of button is currently selected
		/// </summary>
		BUTTON_TYPE selected_button_type();
		
		// control overrides

		std::function<void(buttonbox*, BUTTON_TYPE)> on_enter;
		std::function<void(buttonbox*, BUTTON_TYPE)> on_update;
	};
}
