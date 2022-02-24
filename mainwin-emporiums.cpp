#include "mainwin.h"
#include "emporium.h"
#include <exception>
#include <stdexcept>

void Mainwin::on_file_open_click() {
    try {
        std::ifstream ifs{"emporium.emp", std::ifstream::in};
        _emp = new Mice::Emporium{ifs};
    } catch (std::exception& e) {
        Gtk::MessageDialog dialog{*this, "Unable to open emporium.emp"};
        dialog.set_secondary_text(e.what());
        dialog.run();
        dialog.close();
    }
}

void Mainwin::on_file_save_click() {
    try {
        std::ofstream ofs{"emporium.emp", std::ofstream::out};
        _emp->save(ofs);
    } catch (std::exception& e) {
        Gtk::MessageDialog dialog{*this, "Unable to save emporium.emp"};
        dialog.set_secondary_text(e.what());
        dialog.run();
        dialog.close();
    }
}

void Mainwin::on_file_save_as_click(){
  Gtk::Dialog dialog;
  dialog.set_title("Save As");
  dialog.set_transient_for(*this);
  Gtk::HBox b_name;
  Gtk::Label l_name{"File Name?"};
  l_name.set_width_chars(20);
  b_name.pack_start(l_name, Gtk::PACK_SHRINK);
  Gtk::Entry e_name;
  e_name.set_max_length(20*4);
  b_name.pack_start(e_name, Gtk::PACK_SHRINK);
  dialog.get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

  dialog.add_button("Cancel", 0);
  dialog.add_button("Enter", 1);
  dialog.show_all();
  if (dialog.run() == 0)
  {
    return;
  }
  dialog.close();
  std::string name = e_name.get_text();
  std::regex str_num{"^[:alnum:]"};  // REGEX

  if (std::regex_match(name, str_num))    // REGEX
  {
    Gtk::MessageDialog dialog_f{*this, "Unable to save " + e_name.get_text()};
    dialog_f.run();
    dialog_f.close();
  }

  try {
      std::ofstream ofs{e_name.get_text(), std::ofstream::out};
      _emp->save(ofs);
  } catch (std::exception& e) {
      Gtk::MessageDialog dialog_f{*this, "Unable to save " + e_name.get_text()};
      dialog_f.set_secondary_text(e.what());
      dialog_f.run();
      dialog_f.close();
  }
}

void Mainwin::on_file_open_file_click(){

  Gtk::Dialog dialog;
  dialog.set_title("Open File");
  dialog.set_transient_for(*this);
  Gtk::HBox b_name;
  Gtk::Label l_name{"File Name?"};
  l_name.set_width_chars(20);
  b_name.pack_start(l_name, Gtk::PACK_SHRINK);
  Gtk::Entry e_name;
  e_name.set_max_length(20*4);
  b_name.pack_start(e_name, Gtk::PACK_SHRINK);
  dialog.get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

  dialog.add_button("Cancel", 0);
  dialog.add_button("Enter", 1);
  dialog.show_all();
  if (dialog.run() == 0)
  {
    return;
  }
  dialog.close();

  try {
      std::ifstream ifs{e_name.get_text(), std::ifstream::in};
      _emp = new Mice::Emporium{ifs};
  } catch (std::exception& e) {
      Gtk::MessageDialog dialog_f{*this, "Unable to open emporium.emp"};
      dialog_f.set_secondary_text(e.what());
      dialog_f.run();
      dialog_f.close();
  }
}

void Mainwin::on_file_new_emporium_click(){
  emporiums.push_back(_emp);
}
