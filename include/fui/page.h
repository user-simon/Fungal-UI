#pragma once
#include "container_control.h"
#include "page_body.h"

namespace fungal
{
	/// <summary>
	/// Control to show arbitrary controls to be displayed at once in the ui
	/// </summary>
	class page : public container_control
	{
	private:
		UINT m_scroll_offset;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="title">Text shown above control</param>
		page(std::string name, std::string title);

		// control overrides

		void _update_body() override;
		void _on_key_down(key_event&) override;
		page_body* body() override;
		void reset() override;
	};
}
