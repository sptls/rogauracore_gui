#include "roggui.h"

#include <gtkmm.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

RogGui::RogGui()
{
	settings_path = getenv("HOME");
	settings_path += "/.config/rogauracore_gui/settings";
	
	builder = Gtk::Builder::create_from_resource("/gui/rog_gui.glade");

	builder->get_widget("window_main", window_main);
	builder->get_widget("radio_single_static", radio_single_static);
	builder->get_widget("radio_single_breathing", radio_single_breathing);
	builder->get_widget("radio_single_colorcycle", radio_single_colorcycle);
	builder->get_widget("radio_multi_static", radio_multi_static);
	builder->get_widget("radio_multi_breathing", radio_multi_breathing);
	builder->get_widget("colorbutton_color1", colorbutton_color1);
	builder->get_widget("colorbutton_color2", colorbutton_color2);
	builder->get_widget("colorbutton_color3", colorbutton_color3);
	builder->get_widget("colorbutton_color4", colorbutton_color4);
	builder->get_widget("scale_speed", scale_speed);
	builder->get_widget("scale_brightness", scale_brightness);
	builder->get_widget("image_rog_logo", image_rog_logo);

	image_rog_logo->set_from_resource("/gui/rog_logo.png");

	scale_speed->set_value(1.0);


	radio_single_static->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));
	radio_single_breathing->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));
	radio_single_colorcycle->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));
	radio_multi_static->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));
	radio_multi_breathing->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));

	scale_speed->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), SPEED_CHANGE));
	scale_brightness->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), BRIGHTNESS_CHANGE));

	colorbutton_color1->signal_color_set().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));
	colorbutton_color2->signal_color_set().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));
	colorbutton_color3->signal_color_set().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));
	colorbutton_color4->signal_color_set().connect(sigc::bind(sigc::mem_fun(*this, &RogGui::ChangeRog), THEME_CHANGE));

	if(CheckSettingsExists())
		LoadSettings();
	else
	{
		std::string home_path = "mkdir ";
		home_path += getenv("HOME");
		home_path += "/.config/rogauracore_gui";
		system(home_path.c_str());
		SaveSettings();
	}
};


RogGui::~RogGui()
{
	
};

std::string RogGui::GetRGB(std::string str)
{
	std::string out;
	int colors[3];
	std::string tmp;
	for(int i = 4, col = 0; ;i++)
	{
		if(str[i] != ',' && str[i] != ')')
			tmp.push_back(str[i]);
		else
		{
			colors[col++] = atoi(tmp.c_str());
			tmp.clear();
		}
		if(str[i] == ')')
			break;
	}
	std::string str_col[3];
	for(int i = 0; i < 3; i++)
	{
		std::stringstream stream;
		stream << std::hex << colors[i];
		str_col[i]= (stream.str());
		if(str_col[i].length() < 2)
		{
			std::string tmp_col = "0";
			tmp_col += str_col[i];
			str_col[i] = tmp_col;
		}
		out += str_col[i];
	}
	
	return out;
};

void RogGui::ChangeRog(int action_type)
{
	std::string command = "rogauracore ";
	if(action_type == THEME_CHANGE || action_type == SPEED_CHANGE)
	{
		int option = 0;	
		if(radio_single_static->get_active())
			option = SINGLE_STATIC;
		if(radio_single_breathing->get_active())
			option = SINGLE_BREATHING;
		if(radio_single_colorcycle->get_active())
			option = SINGLE_COLORCYCLE;
		if(radio_multi_static->get_active())
			option = MULTI_STATIC;
		if(radio_multi_breathing->get_active())
			option = MULTI_BREATHING;
		
		std::string tmp;
		int speed = (int)scale_speed->get_value();
		selected_theme = option;
		switch(option)
		{
			case SINGLE_STATIC:
				command += "single_static ";
				tmp = colorbutton_color1->get_rgba().to_string();
				tmp = GetRGB(tmp);
				command += tmp;
				break;
			case SINGLE_BREATHING:
				command += "single_breathing ";
				tmp = colorbutton_color1->get_rgba().to_string();
				tmp = GetRGB(tmp);
				command += tmp;
				command += " ";
				tmp = colorbutton_color2->get_rgba().to_string();
				tmp = GetRGB(tmp);
				command += tmp;
				command += " ";
				command += std::to_string(speed);
				break;
			case SINGLE_COLORCYCLE:
				command += "single_colorcycle ";
				command += std::to_string(speed);
				break;
			case MULTI_STATIC:
				command += "multi_static ";
				tmp = GetRGB(colorbutton_color1->get_rgba().to_string());
				command += tmp;
				command += " ";
				tmp = GetRGB(colorbutton_color2->get_rgba().to_string());
				command += tmp;
				command += " ";
				tmp = GetRGB(colorbutton_color3->get_rgba().to_string());
				command += tmp;
				command += " ";
				tmp = GetRGB(colorbutton_color4->get_rgba().to_string());
				command += tmp;
				break;
			case MULTI_BREATHING:
				command += "multi_breathing ";
				tmp = GetRGB(colorbutton_color1->get_rgba().to_string());
				command += tmp;
				command += " ";
				tmp = GetRGB(colorbutton_color2->get_rgba().to_string());
				command += tmp;
				command += " ";
				tmp = GetRGB(colorbutton_color3->get_rgba().to_string());
				command += tmp;
				command += " ";
				tmp = GetRGB(colorbutton_color4->get_rgba().to_string());
				command += tmp;
				command += " ";
				command += std::to_string(speed);
				break;
		}
		system(command.c_str());
		SaveSettings();
		return;
	}

	if(action_type == BRIGHTNESS_CHANGE)
	{
		command = "rogauracore brightness ";
		int brightness = (int)scale_brightness->get_value();
		command += std::to_string(brightness);
		system(command.c_str());
		SaveSettings();
		return;
	}
};

bool RogGui::CheckSettingsExists()
{
	std::ifstream file(settings_path);
	return file.good();
};

void RogGui::LoadSettings()
{
	std::ifstream file(settings_path);
	std::string tmp;

	getline(file, tmp);
	switch(atoi(tmp.c_str()))
	{
		case SINGLE_STATIC:
			radio_single_static->set_active(true);
			break;
		case SINGLE_BREATHING:
			radio_single_breathing->set_active(true);
			break;
		case SINGLE_COLORCYCLE:
			radio_single_colorcycle->set_active(true);
			break;
		case MULTI_STATIC:
			radio_multi_static->set_active(true);
			break;
		case MULTI_BREATHING:
			radio_multi_breathing->set_active(true);
			break;
	}
	getline(file, tmp);
	scale_brightness->set_value(atoi(tmp.c_str()));

	getline(file, tmp);
	scale_speed->set_value(atoi(tmp.c_str()));

	getline(file, tmp);
	colorbutton_color1->set_rgba(Gdk::RGBA(tmp));
	getline(file, tmp);
	colorbutton_color2->set_rgba(Gdk::RGBA(tmp));
	getline(file, tmp);
	colorbutton_color3->set_rgba(Gdk::RGBA(tmp));
	getline(file, tmp);
	colorbutton_color4->set_rgba(Gdk::RGBA(tmp));

	ChangeRog(THEME_CHANGE);
	ChangeRog(BRIGHTNESS_CHANGE);
};

void RogGui::SaveSettings()
{
	std::ofstream file(settings_path);
	file << selected_theme;
	file << "\n";
	file << scale_brightness->get_value();
	file << "\n";
	file << scale_speed->get_value();
	file << "\n";
	file << colorbutton_color1->get_rgba().to_string();
	file << "\n";
	file << colorbutton_color2->get_rgba().to_string();
	file << "\n";
	file << colorbutton_color3->get_rgba().to_string();
	file << "\n";
	file << colorbutton_color4->get_rgba().to_string();
	file << "\n";
	file.close();
};
