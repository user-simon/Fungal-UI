#include "pch.h"
#include "controls/tab_control.h"
using namespace fui;

tab_control::tab_control(std::string name, page* parent, std::string title, std::vector<page*> pages)
	: control(name, (container_control*)parent, "")
{
	for (page* p : pages)
		_add((control*)p);
}

void tab_control::_update_body()
{
	
}

void tab_control::_handle_input(int key, int nav)
{

}
