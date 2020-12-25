#pragma once
#include "control.h"

namespace fungal
{
	/// <summary>
	/// Base class for controls that get some input from the user
	/// </summary>
	/// <typeparam name="VALUE_T">Type of the value to be entered by the user</typeparam>
	template<typename VALUE_T>
	class input_control : public virtual control
	{
	private:
		VALUE_T m_default_value;

	protected:
		VALUE_T m_value;

	protected:
		input_control() {}

		/// <param name="default_value">Value the control should default to</param>
		input_control(VALUE_T default_value)
		{
			m_default_value = default_value;
			m_value = default_value;
		}

		/// <summary>
		/// Calls the on_enter callback with value
		/// </summary>
		void _on_enter() override
		{
			if (on_enter)
				on_enter(this, value());
		}

		/// <summary>
		/// Calls the on_update callback with value
		/// </summary>
		void _on_update()
		{
			if (on_update)
				on_update(this, value());
		}

	public:
		~input_control() {}

		/// <summary>
		/// Gets the value of the control
		/// </summary>
		virtual VALUE_T value()
		{
			return m_value;
		}

		/// <summary>
		/// Sets the value of the control
		/// </summary>
		virtual void set_value(VALUE_T value)
		{
			m_value = value;
			_invalidate();
		}

		// control overrides

		virtual void reset() override
		{
			set_value(m_default_value);
		}

		std::function<void(input_control*, VALUE_T)> on_enter;
		std::function<void(input_control*, VALUE_T)> on_update;
	};
}
