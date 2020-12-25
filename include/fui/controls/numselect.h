#pragma once
#include "input_control.h"

namespace fungal
{
	class container_control;

	/// <summary>
	/// Control for getting an integer input
	/// </summary>
	class numselect : public input_control<int>
	{
	private:
		int m_min;
		int m_max;
		int m_step;

	private:
		void _clamp_value();

	protected:
		void _update_body() override;

	public:
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="min">Min value</param>
		/// <param name="max">Max value</param>
		/// <param name="title">Text shown above control</param>
		/// <param name="default_val">Value that control is initialized with</param>
		/// <param name="step">Indicates the increment/decrement amount</param>
		numselect(std::string name, std::string title, int min, int max, int default_val = 0, int step = 1);

		/// <summary>
		/// Gets the minimum of the value
		/// </summary>
		int min();

		/// <summary>
		/// Sets the minimum of the value
		/// </summary>
		void set_min(int min);

		/// <summary>
		/// Gets the maximum of the value
		/// </summary>
		int max();

		/// <summary>
		/// Sets the maximum of the value
		/// </summary>
		void set_max(int max);

		/// <summary>
		/// Gets the increment/decrement amount
		/// </summary>
		int step();

		/// <summary>
		/// Sets the increment/decrement amount
		/// </summary>
		void set_step(int step);

		// control overrides

		bool _handle_input(key_event&) override;

		// input_control overrides
		
		void set_value(int value) override;
	};
}
