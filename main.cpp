#include <iostream>

#include "src/roggui.h"

int main(int argc, char** argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("org.gtkmm.example");	
	RogGui gui;

	return app->run(*gui.window_main);
}
