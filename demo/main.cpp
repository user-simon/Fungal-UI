#include <fui/fui.h>
using namespace fungal;

void on_login(control* c)
{
	ui.display("standard_controls");
}

void asdf(control*, BUTTON_TYPE)
{
	ui.display("new_page");
}

int main()
{
	ui.init();
	
	page* login_page = new page("login_page", "Login");
	{
		login_page->add(new textfield("username", "Username"));
		login_page->add(new textfield("password", "Password", "", true));
		login_page->add(new button("button_login", "Login", on_login));

		ui.add(login_page);
	}

	// alternative syntax for creating controls through overloaded operator<<

	page* standard_controls = new page("standard_controls", "Standard page");
	{
		*standard_controls << new buttonbox("buttonbox", "Buttonbox", BUTTON_OK | BUTTON_CANCEL | BUTTON_RETRY, asdf);
		*standard_controls << new checkbox("checkbox", "Checkbox");
		*standard_controls << new multiselect("multiselect", "Multiselect", { "Option 1", "Option 2", "Option 3" });
		*standard_controls << new numselect("numselect", "Numselect", 0, 100);
		*standard_controls << new multiselect("multiselect2", "Multiselect 2", { "Option 1", "Option 2", "Option 3" });
		*standard_controls << new radioselect("radioselect", "Radioselect", { "Option 1", "Option 2", "Option 3" });
		*standard_controls << new multiselect("multiselect3", "Multiselect 3", { "Option 1", "Option 2", "Option 3" });
		*standard_controls << new checkbox("checkbox2", "Checkbox 2");

		ui << standard_controls;
	}
	
	ui << new page("new_page", "Page test");

	ui.display(login_page);
	ui.exec();
}
