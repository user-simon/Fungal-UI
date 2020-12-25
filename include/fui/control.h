#pragma once
#include <string_view>
#include <functional>
#include <type_traits>
#include <utility>
#include <memory>
#include <any>

#include "types.h"
#include "control_body.h"

namespace fungal
{
	class container_control;

	enum class CASCADE
	{
		NONE,
		DOWN,
		UP
	};
	
	/// <summary>
	/// Base class for all controls
	/// </summary>
	class control
	{
	private:
		std::string m_name;
		std::string m_title;
		std::any m_data;
		bool m_invalidated;
		
	public:
		std::unique_ptr<control_body> _body;
		container_control* _parent;

	protected:
		control() = default;

		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="title">Text shown on control</param>
		///	<param name="embedded_title">Whether the control draws the title within the content of the body and not seperately</param>
		control(std::string name, std::string title, bool embedded_title = false);

		/// <summary>
		/// Calls the on_enter callback with the appropriate parameters
		/// </summary>
		virtual void _on_enter();

		/// <summary>
		/// Calls the on_update callback with the appropriate parameters
		/// </summary>
		virtual void _on_update();

		/// <summary>
		/// Updates m_control_body
		/// </summary>
		virtual void _update_body() = 0;

	public:
		virtual ~control() = default;
		
		/// <summary>
		/// Defines generic actions to be taken upon a key-press
		/// </summary>
		virtual void _on_key_down(key_event&);

		/// <summary>
		/// Defines control-specific actions to be taken upon a key-press
		/// </summary>
		virtual bool _handle_input(key_event&);
		
		/// <summary>
		/// Tells the control to update its body
		/// </summary>
		/// <param name="cascade">Determines how the invalidate event should cascade</param>
		virtual void _invalidate(CASCADE cascade = CASCADE::UP);

		/// <summary>
		/// Updates the body if control is invalidated and returns its pointer
		/// </summary>
		virtual control_body* body();

		/// <summary>
		/// Resets the control to its initial state
		/// </summary>
		virtual void reset() {};

		/// <summary>
		/// Gets the internal name referring to the control
		/// </summary>
		std::string_view name() const;

		/// <summary>
		/// Gets the parent of the control
		/// </summary>
		container_control* parent() const;

		/// <summary>
		/// Removes control from current parent and re-adds it to new parent
		/// </summary>
		void set_parent(container_control* parent);

		/// <summary>
		/// Gets the title of the control
		/// </summary>
		std::string title() const;

		/// <summary>
		/// Sets the title of the control
		/// </summary>
		void set_title(std::string title);
		
		/// <summary>
		/// Gets the arbitrary data set for the control, casted to expected type
		/// </summary>
		template<typename DATA_T>
		DATA_T get_data();

		/// <summary>
		/// Sets arbitrary data to be associated with the control
		/// </summary>
		void set_data(std::any data);
		
		/// <summary>
		/// Returns whether control is currently selected in parent
		/// </summary>
		/// <param name="cascade">If true, cascades selected check upwards</param>
		bool is_selected(bool cascade = false) const;

		/// <summary>
		/// Returns whether the control is currently displayed in fui_main
		/// </summary>
		bool is_displayed() const;

		/// <summary>
		/// Casts control to arbitrary control subclass
		/// </summary>
		template<class CONTROL_T>
		CONTROL_T* as();

		/// <summary>
		/// On enter callback
		/// </summary>
		std::function<void(control*)> on_enter;

		/// <summary>
		/// On update callback
		/// </summary>
		std::function<void(control*)> on_update;
	};
	
	// templated function definitions

	template<typename DATA_T>
	DATA_T control::get_data()
	{
		return std::any_cast<DATA_T>(m_data);
	}

	template<class CONTROL_T>
	CONTROL_T* control::as()
	{
		return dynamic_cast<CONTROL_T*>(this);
	}
}
