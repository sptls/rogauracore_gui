#ifndef ROGGUI_H_
#define ROGGUI_H_

#include <gtkmm.h>
#include <giomm.h>

enum rog_color_options
{
	SINGLE_STATIC,
	SINGLE_BREATHING,
	SINGLE_COLORCYCLE,
	MULTI_STATIC,
	MULTI_BREATHING
};

enum rog_action_type
{
	THEME_CHANGE,
	BRIGHTNESS_CHANGE,
	SPEED_CHANGE
};

class RogGui
{
	public:
		Glib::RefPtr<Gtk::Builder> builder;	
		Gtk::Window* window_main;

		Gtk::RadioButton* radio_single_static;
		Gtk::RadioButton* radio_single_breathing;
		Gtk::RadioButton* radio_single_colorcycle;
		Gtk::RadioButton* radio_multi_static;
		Gtk::RadioButton* radio_multi_breathing;

		Gtk::ColorButton* colorbutton_color1;
		Gtk::ColorButton* colorbutton_color2;
		Gtk::ColorButton* colorbutton_color3;
		Gtk::ColorButton* colorbutton_color4;

		Gtk::Scale* scale_speed;
		Gtk::Scale* scale_brightness;

		Gtk::Image* image_rog_logo;

		std::string settings_path = "~/.config/rogauracore_gui/settings";
		int selected_theme;
	
		RogGui();
		~RogGui();
		std::string GetRGB(std::string str);
		void ChangeRog(int action_type = THEME_CHANGE);
		bool CheckSettingsExists();
		void LoadSettings();
		void SaveSettings();
};

#endif
