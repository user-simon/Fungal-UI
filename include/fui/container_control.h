#pragma once
#include <string>
#include <vector>

#include "ui.h"
#include "control.h"

namespace fungal
{
	/// <summary>
	/// Base class for controls that contain other controls
	/// </summary>
	class container_control : public virtual control
	{
	protected:
		std::vector<control*> m_controls;
		std::vector<control*>::iterator m_selected;

	protected:
		container_control();

	public:
		~container_control();

		/// <summary>
		/// Removes control from container. Does not remove control from fui_main
		/// </summary>
		virtual void remove(control* control);

		/// <summary>
		/// Removes control from container. Does not remove control from fui_main
		/// </summary>
		/// <param name="name">Name of the control</param>
		void remove(std::string_view name);

		/// <summary>
		/// Gets currently selected control
		/// </summary>
		control* selected_control() const;

		/// <summary>
		/// Gets a list of all controls in container
		/// </summary>
		std::vector<control*>& controls();

		/// <summary>
		/// Sets selected control to control with specified index
		/// </summary>
		void set_selected_index(UINT index);

		/// <summary>
		/// Gets index of currently selected control
		/// </summary>
		UINT selected_index() const;

		/// <summary>
		/// Gets first control in container
		/// </summary>
		control* first_control() const;

		/// <summary>
		/// Gets last control in container
		/// </summary>
		control* last_control() const;

		/// <summary>
		/// Adds control to ui and container
		/// </summary>
		void add(control* control);

		/// <summary>
		/// Synonym of add but allows for stringing creation of controls together
		/// </summary>
		container_control& operator<<(control* control);

		// control overrides
		
		virtual void _on_key_down(key_event&) override;
		virtual void _update_body() override;
		virtual void _invalidate(CASCADE = CASCADE::UP) override;
	};
}
