#pragma once
#include "container_control.h"

namespace fungal
{
	class radiobutton : public control
	{
	private:
		unsigned int m_index;

	protected:
		void _update_body() override;

	public:
		radiobutton(std::string name, std::string title, unsigned int index);

		unsigned int index();
	};

	/// <summary>
	/// Control for getting a choice between different options.
	/// </summary>
	class radioselect : public container_control, public input_control<radiobutton*>
	{
	private:
		// hide set_value as control should be interfaced with via indexes instead
		void set_value(radiobutton*) override {}

	public:
		/// <summary>Radiobuttons will be created with name with format "[radioselect name]_option[index]"</summary>
		/// <param name="name">Internal name used to identify the control</param>
		/// <param name="options">Option names</param>
		/// <param name="title">Text shown above control</param>
		radioselect(std::string name, std::string title, std::vector<std::string> options);
		
		unsigned int index();
		void set_index(unsigned int index);

		// input_control overrides
		
		radiobutton* value() override;
		void reset() override;
	};
}
