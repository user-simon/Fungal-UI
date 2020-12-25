#include "pch.h"
using namespace fungal;

button::button(std::string name, std::string text, std::function<void(control*)> callback) :
	control(name, text, true)
{
	on_enter = callback;
}

void button::_update_body()
{
	if (is_selected(true))
		_body->add("[ " + title() + " ]");
	else	
		_body->add("( " + title() + " )");
}
