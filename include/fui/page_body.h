#pragma once
#include "control_body.h"

namespace fungal
{
	class page;

	/// <summary>
	/// Contains the drawable body of a page
	/// </summary>
	class page_body : public control_body
	{
	private:
		std::string m_scrollbar;

	private:
		/// <summary>
		/// Gets a formatted string containing the indentation for content
		/// </summary>
		/// <param name="selected">Whether the indent should contain a character indicating whether a control is selected</param>
		std::string _content_indent(bool selected = false);

		/// <summary>
		/// Gets a formatted string containing the indentation for title
		/// </summary>
		std::string _title_indent();

	public:
		/// <param name="owner">Control owner of the body</param>
		/// <param name="title">Title of the control</param>
		page_body(page* owner, std::string title);

		/// <summary>
		/// Sets string to be drawn as scrollbar
		/// </summary>
		void set_scrollbar(std::string scrollbar);

		/// <summary>
		/// Adds string as row in content
		/// </summary>
		/// <param name="selected">Whether the indent should contain a character indicating that the control is selected</param>
		void add(std::string, bool selected);

		/// <summary>
		/// Adds rows from control_body in a certain range to content. If both begin and end are zero, adds all rows from control_body
		/// </summary>
		/// <param name="begin">First row to add</param>
		/// <param name="end">Last row to add</param>
		void add(control_body*, UINT begin = 0, UINT end = 0);

		// control_body overrides

		void set_title(std::string title) override;
		void newline(UINT n = 1U) override;
	};
}
