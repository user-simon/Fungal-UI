#include <fui/fui.h>
#include <Windows.h>
using namespace fungal;

void on_login(control*)
{
	// retrieve values from textfields

	std::string username = ui.get_value<std::string>("text_username");
	std::string password = ui.get_value<std::string>("text_password");

	// very secure credentials check
	if (username == "admin" && password == "password1")
		ui.display("second_page");
}

int main()
{
	// initializes variables and the console environment
	ui.init();

	// create and add controls in the login page
	page* login_page = new page("login_page", "Login");
	{
		*login_page << new textfield("text_username", "Username");
		*login_page << new textfield("text_password", "Password", "", true);
		*login_page << new button("button_confirm_login", "Login", on_login);

		ui << login_page;
	}

	// create and add second page
	page* second_page = new page("second_page", "This is a second page");
	{
		ui << second_page;
	}

	// set displayed control
	ui.display(login_page);

	// starts drawing and listening for events
	ui.exec();
}
