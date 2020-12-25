#pragma once
#include <string>
#include <vector>

#include "types.h"

namespace fungal
{
	class control;

	typedef std::vector<std::string> body_rows_t;

	/// <summary>
	/// Contains the drawable body of a control
	/// </summary>
	class control_body
	{
	protected:
		body_rows_t m_title;
		body_rows_t m_content;
		control* m_owner;
		UINT m_pos;

		bool m_invalidated;
		body_rows_t m_rows;

	public:
		/// <param name="owner">Control owner of the body</param>
		/// <param name="title">Title of the control</param>
		control_body(control* owner, std::string title = "");
		
		/// <summary>
		/// Signifies that the control_body has updated and m_rows should update
		/// </summary>
		void _invalidate();

		/// <summary>
		/// Sets the position of the body relative to other bodies in the container
		/// </summary>
		void set_pos(UINT pos);
		
		/// <summary>
		/// Gets the title + content rows
		/// </summary>
		body_rows_t& rows();

		/// <summary>
		/// Gets the body rows containing the formatted title
		/// </summary>
		body_rows_t& title();

		/// <summary>
		/// Sets title
		/// </summary>
		virtual void set_title(std::string title);

		/// <summary>
		/// Sets pre-formatted title
		/// </summary>
		virtual void set_title(body_rows_t& title_rows);

		/// <summary>
		/// Gets the body rows containing the content
		/// </summary>
		body_rows_t& content();

		/// <summary>
		/// Removes all content
		/// </summary>
		void clear_content();

		/// <summary>
		/// Gets the owner
		/// </summary>
		control* owner();

		/// <summary>
		/// Gets the top position, relative to other bodies in the container
		/// </summary>
		UINT top();

		/// <summary>
		/// Gets the bottom position, relative to other bodies in the container
		/// </summary>
		UINT bottom();

		/// <summary>
		/// Gets the height, in characters
		/// </summary>
		UINT height();

		/// <summary>
		/// Gets the width, in characters
		/// </summary>
		UINT width();

		/// <summary>
		/// Inserts a newline at the end
		/// </summary>
		virtual void newline(UINT n = 1U);

		/// <summary>
		/// Gets the begin iterator of all rows
		/// </summary>
		body_rows_t::iterator begin();

		/// <summary>
		/// Gets the end iterator of all rows
		/// </summary>
		body_rows_t::iterator end();

		/// <summary>
		/// Adds string to the last row in content
		/// </summary>
		virtual void append(std::string);

		/// <summary>
		/// Adds body to the last row in content
		/// </summary>
		virtual void append(control_body*);

		/// <summary>
		/// Adds string as row in content
		/// </summary>
		virtual void add(std::string);

		/// <summary>
		/// Adds other control_body to content
		/// </summary>
		virtual void add(control_body*);
	};
}
