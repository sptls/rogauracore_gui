#include <iostream>

#include "src/roggui.h"

int main(int argc, char** argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("rogauracore.gui");	
	RogGui gui;

	return app->run(*gui.window_main);
}
