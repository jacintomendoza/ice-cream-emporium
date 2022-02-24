#include "mainwin.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>

Mainwin::Mainwin() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(800, 600);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //
    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         N E W   E M P O R I U M
    // (Owner) “Create a New Emporium” Append New to the File menu
    menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Emporium", true));
    menuitem_new->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_new_emporium_click));
    filemenu->append(*menuitem_new);

    //         O P E N   E M P O R I U M
    // (Owner) “Open an Emporium File” Append Open to the File menu
    menuitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_open->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_open_click));
    filemenu->append(*menuitem_open);

    //        O P E N    F I L E
    menuitem_open_file = Gtk::manage(new Gtk::MenuItem("_Open File", true));
    menuitem_open_file->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_open_file_click));
    filemenu->append(*menuitem_open_file);

    //         S A V E   E M P O R I U M
    // (Owner) “Save an Emporium File” Append Save to the File menu
    menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_save_click));
    filemenu->append(*menuitem_save);

    //         S A V E    A S
    menuitem_save_as = Gtk::manage(new Gtk::MenuItem("_Save As", true));
    menuitem_save_as->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_save_as_click));
    filemenu->append(*menuitem_save_as);

    //         S U S P E N D     S E R V E R
    menuitem_suspend_server = Gtk::manage(new Gtk::MenuItem("_Suspend Server", true));
    menuitem_suspend_server->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_suspend_server_click));
    filemenu->append(*menuitem_suspend_server);

    //         E A S T E R   E G G
    // (TODO: Test Only) “Create a New Emporium” Append Easter Egg to the File menu
    menuitem_easteregg = Gtk::manage(new Gtk::MenuItem("_Easter Egg", true));
    menuitem_easteregg->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_easteregg_click));
    filemenu->append(*menuitem_easteregg);

    //         Q U I T
    // Append Quit to the File menu
    menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    /////////////////////////////////////////////////////////////////////
    //
    //     C R E A T E
    // Create a Create menu and add to the menu bar
    Gtk::MenuItem *menuitem_create = Gtk::manage(new Gtk::MenuItem("_Create", true));
    menubar->append(*menuitem_create);
    Gtk::Menu *createmenu = Gtk::manage(new Gtk::Menu());
    menuitem_create->set_submenu(*createmenu);

    //         O R D E R
    // (All) “Create Delicious Ice Cream Treats” Append Order to the Create menu
    menuitem_order = Gtk::manage(new Gtk::MenuItem("_Order...", true));
    menuitem_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    createmenu->append(*menuitem_order);

    //         C U S T O M E R
    // (Server, Manager, Owner) “Create a New Customer” Append Customer to the Create menu
    menuitem_customer = Gtk::manage(new Gtk::MenuItem("_Customer...", true));
    menuitem_customer->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_customer_click));
    createmenu->append(*menuitem_customer);

    //         I T E M
    // (Owner, Manager) “Create a New Container, Ice Cream Flavor, or Topping” Append Item to the Create menu
    menuitem_item = Gtk::manage(new Gtk::MenuItem("_Item...", true));
    menuitem_item->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_item_click));
    createmenu->append(*menuitem_item);

    //         S E R V E R
    // (Owner, Manager) “Add a New Employee” Append Server to the Create menu
    menuitem_server = Gtk::manage(new Gtk::MenuItem("_Server...", true));
    menuitem_server->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_server_click));
    createmenu->append(*menuitem_server);

    //         M A N A G E R
    menuitem_manager = Gtk::manage(new Gtk::MenuItem("_Manager...", true));
    menuitem_manager->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_manager_click));
    createmenu->append(*menuitem_manager);

    //
    //     P R O C E S S
    // Create a Process menu and add to the menu bar
    Gtk::MenuItem *menuitem_process = Gtk::manage(new Gtk::MenuItem("_Process Order", true));
    menubar->append(*menuitem_process);
    Gtk::Menu *processmenu = Gtk::manage(new Gtk::Menu());
    menuitem_process->set_submenu(*processmenu);

    //         F I L L   O R D E R
    // (Server) “_Fill Order..."
    menuitem_fill_order = Gtk::manage(new Gtk::MenuItem("_Fill Order", true));
    menuitem_fill_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_fill_order_click));
    processmenu->append(*menuitem_fill_order);

    //         V I E W   O R D E R
    menuitem_view_order = Gtk::manage(new Gtk::MenuItem("_View Order", true));
    menuitem_view_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_order_click));
    processmenu->append(*menuitem_view_order);

    //         P A Y
    // (All) “_Pay.."
    menuitem_pay_for_order = Gtk::manage(new Gtk::MenuItem("_Pay for Order", true));
    menuitem_pay_for_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_pay_for_order_click));
    processmenu->append(*menuitem_pay_for_order);

    //         C A N C E L   O R D E R
    // (Customer, Server) “_Fill Order...", true));
    menuitem_cancel_order = Gtk::manage(new Gtk::MenuItem("_Cancel Order", true));
    menuitem_cancel_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_cancel_order_click));
    processmenu->append(*menuitem_cancel_order);

    //     R O L E
    // Create a Role menu and add to the menu bar
    Gtk::MenuItem *menuitem_role = Gtk::manage(new Gtk::MenuItem("_Role", true));
    menubar->append(*menuitem_role);
    Gtk::Menu *rolemenu = Gtk::manage(new Gtk::Menu());
    menuitem_role->set_submenu(*rolemenu);

    //           A L L
    // Append All to the Role menu
    Gtk::MenuItem *menuitem_all_role = Gtk::manage(new Gtk::MenuItem("All", true));
    menuitem_all_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_all_click));
    rolemenu->append(*menuitem_all_role);

    //           O W N E R
    // Append Owner to the Role menu
    Gtk::MenuItem *menuitem_owner_role = Gtk::manage(new Gtk::MenuItem("Owner", true));
    menuitem_owner_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_owner_click));
    rolemenu->append(*menuitem_owner_role);

    //           M A N A G E R
    // Append Manager to the Role menu
    Gtk::MenuItem *menuitem_manager_role = Gtk::manage(new Gtk::MenuItem("Manager", true));
    menuitem_manager_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_manager_click));
    rolemenu->append(*menuitem_manager_role);

    //           S E R V E R
    // Append Manager to the Role menu
    Gtk::MenuItem *menuitem_server_role = Gtk::manage(new Gtk::MenuItem("Server", true));
    menuitem_server_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_server_click));
    rolemenu->append(*menuitem_server_role);

    //           C U S T O M E R
    // Append Customer to the Role menu
    Gtk::MenuItem *menuitem_customer_role = Gtk::manage(new Gtk::MenuItem("Customer", true));
    menuitem_customer_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_customer_click));
    rolemenu->append(*menuitem_customer_role);

    ///////////////////////////////////////////////////////////
    //     A D D   I M A G E
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_add_image = Gtk::manage(new Gtk::MenuItem("_Add Image", true));
    menubar->append(*menuitem_add_image);
    Gtk::Menu *add_image_menu = Gtk::manage(new Gtk::Menu());
    menuitem_add_image->set_submenu(*add_image_menu);

    //    C O N T A I N E R      I M A G E
    menuitem_image_container = Gtk::manage(new Gtk::MenuItem("Container", true));
    menuitem_image_container->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_image_container_click));
    add_image_menu->append(*menuitem_image_container);

    //    S C O O P      I M A G E
    menuitem_image_scoop = Gtk::manage(new Gtk::MenuItem("Scoop", true));
    menuitem_image_scoop->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_image_scoop_click));
    add_image_menu->append(*menuitem_image_scoop);

    //    T O P P I N G     I M A G E
    menuitem_image_topping = Gtk::manage(new Gtk::MenuItem("Topping", true));
    menuitem_image_topping->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_image_topping_click));
    add_image_menu->append(*menuitem_image_topping);

    ///////////////////////////////////////////////////////////
    //     R E P O R T
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_report = Gtk::manage(new Gtk::MenuItem("_Report", true));
    menubar->append(*menuitem_report);
    Gtk::Menu *reportmenu = Gtk::manage(new Gtk::Menu());
    menuitem_report->set_submenu(*reportmenu);

    menuitem_profitloss_report = Gtk::manage(new Gtk::MenuItem("Profit/Loss", true));
    menuitem_profitloss_report->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_profitloss_report_click));
    reportmenu->append(*menuitem_profitloss_report);

    menuitem_inventory_report = Gtk::manage(new Gtk::MenuItem("Inventory", true));
    menuitem_inventory_report->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_inventory_report_click));
    reportmenu->append(*menuitem_inventory_report);

    menuitem_server_report = Gtk::manage(new Gtk::MenuItem("Server", true));
    menuitem_server_report->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_server_report_click));
    reportmenu->append(*menuitem_server_report);

    menuitem_order_report = Gtk::manage(new Gtk::MenuItem("Order", true));
    menuitem_order_report->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_order_report_click));
    reportmenu->append(*menuitem_order_report);

    menuitem_customer_report = Gtk::manage(new Gtk::MenuItem("Customer", true));
    menuitem_customer_report->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_customer_report_click));
    reportmenu->append(*menuitem_customer_report);

    ///////////////////////////////////////////////////////////
    //     E D I T
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_edit = Gtk::manage(new Gtk::MenuItem("_Edit", true));
    menubar->append(*menuitem_edit);
    Gtk::Menu *editmenu = Gtk::manage(new Gtk::Menu());
    menuitem_edit->set_submenu(*editmenu);

    menuitem_edit_server_salary = Gtk::manage(new Gtk::MenuItem("Server Salary", true));
    menuitem_edit_server_salary->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_edit_server_salary_click));
    editmenu->append(*menuitem_edit_server_salary);

    menuitem_edit_restock = Gtk::manage(new Gtk::MenuItem("Restock", true));
    menuitem_edit_restock->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_edit_restock_click));
    editmenu->append(*menuitem_edit_restock);

    menuitem_edit_flavor = Gtk::manage(new Gtk::MenuItem("Flavor", true));
    menuitem_edit_flavor->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_edit_flavor_click));
    editmenu->append(*menuitem_edit_flavor);

    menuitem_edit_container = Gtk::manage(new Gtk::MenuItem("Container", true));
    menuitem_edit_container->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_edit_container_click));
    editmenu->append(*menuitem_edit_container);

    menuitem_edit_topping = Gtk::manage(new Gtk::MenuItem("Topping", true));
    menuitem_edit_topping->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_edit_topping_click));
    editmenu->append(*menuitem_edit_topping);

    /////////////////////////////////////////////////////////////////////
    //
    //     R E M O V E    I T E M
    // Create a Create menu and add to the menu bar
    Gtk::MenuItem *menuitem_remove = Gtk::manage(new Gtk::MenuItem("_Remove", true));
    menubar->append(*menuitem_remove);
    Gtk::Menu *removemenu = Gtk::manage(new Gtk::Menu());
    menuitem_remove->set_submenu(*removemenu);

    menuitem_remove_item = Gtk::manage(new Gtk::MenuItem("Item", true));
    menuitem_remove_item->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_remove_item_click));
    removemenu->append(*menuitem_remove_item);

    ///////////////////////////////////////////////////////////
    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     N E W   E M P O R I U M
    // Add a new emporium icon
    new_emporium_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_emporium_button->set_tooltip_markup("Create a New Emporium");
    //new_emporium_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_file_new_click));
    toolbar->append(*new_emporium_button);

    //     C R E A T E   O R D E R
    // Add a Create Order icon
    Gtk::Image *create_order_button_image = Gtk::manage(new Gtk::Image("new_order.png"));
    create_order_button = Gtk::manage(new Gtk::ToolButton(*create_order_button_image));
    create_order_button->set_tooltip_markup("Create a new order");
    create_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    toolbar->append(*create_order_button);

    //     C R E A T E   C R E A T E   I T E M
    // Add a Create Item icon
    Gtk::Image *create_item_button_image = Gtk::manage(new Gtk::Image("create_item.png"));
    create_item_button = Gtk::manage(new Gtk::ToolButton(*create_item_button_image));
    create_item_button->set_tooltip_markup("Create a new item");
    create_item_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_item_click));
    toolbar->append(*create_item_button);

    //     Q U I T
    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit MICE");
    quit_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);  // The expanding sep forces the Quit button to the right
    toolbar->append(*sep);
    toolbar->append(*quit_button);

    // Make the box and everything in it visible
    vbox->show_all();

    // Start with a default emporium
    _emp = new Mice::Emporium{"Default"};
    set_title("Mav's Ice Cream Emporium");
}

Mainwin::~Mainwin() { }

void Mainwin::on_quit_click() {
    hide();
}

// Set sensitivities based on role

void Mainwin::on_all_click() {
    menuitem_new->set_sensitive(true);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_easteregg->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_view_order->set_sensitive(true);
    menuitem_image_container->set_sensitive(true);
    menuitem_image_scoop->set_sensitive(true);
    menuitem_image_topping->set_sensitive(true);
    menuitem_manager->set_sensitive(true);
    menuitem_profitloss_report->set_sensitive(true);
    menuitem_inventory_report->set_sensitive(true);
    menuitem_edit_flavor->set_sensitive(true);
    menuitem_edit_container->set_sensitive(true);
    menuitem_edit_topping->set_sensitive(true);
    menuitem_save_as->set_sensitive(true);
    menuitem_open_file->set_sensitive(true);
    menuitem_remove_item->set_sensitive(true);
    menuitem_suspend_server->set_sensitive(true);

    if (_suspend)
    {
      menuitem_order->set_sensitive(false);
      menuitem_edit_restock->set_sensitive(false);
    }

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_owner_click() {
    menuitem_new->set_sensitive(true);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_easteregg->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_view_order->set_sensitive(true);
    menuitem_image_container->set_sensitive(true);
    menuitem_image_scoop->set_sensitive(true);
    menuitem_image_topping->set_sensitive(true);
    menuitem_manager->set_sensitive(true);
    menuitem_profitloss_report->set_sensitive(true);
    menuitem_inventory_report->set_sensitive(true);
    menuitem_server_report->set_sensitive(true);
    menuitem_order_report->set_sensitive(true);
    menuitem_customer_report->set_sensitive(true);
    menuitem_edit_flavor->set_sensitive(true);
    menuitem_edit_container->set_sensitive(true);
    menuitem_edit_topping->set_sensitive(true);
    menuitem_save_as->set_sensitive(true);
    menuitem_open_file->set_sensitive(true);
    menuitem_remove_item->set_sensitive(true);
    menuitem_suspend_server->set_sensitive(true);

    if (_suspend)
    {
      menuitem_order->set_sensitive(false);
      menuitem_edit_restock->set_sensitive(false);
    }

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_manager_click() {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_easteregg->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_view_order->set_sensitive(true);
    menuitem_image_container->set_sensitive(true);
    menuitem_image_scoop->set_sensitive(true);
    menuitem_image_topping->set_sensitive(true);
    menuitem_manager->set_sensitive(false);
    menuitem_profitloss_report->set_sensitive(true);
    menuitem_inventory_report->set_sensitive(true);
    menuitem_server_report->set_sensitive(true);
    menuitem_order_report->set_sensitive(true);
    menuitem_customer_report->set_sensitive(true);
    menuitem_edit_flavor->set_sensitive(true);
    menuitem_edit_container->set_sensitive(true);
    menuitem_edit_topping->set_sensitive(true);
    menuitem_save_as->set_sensitive(false);
    menuitem_open_file->set_sensitive(false);
    menuitem_remove_item->set_sensitive(true);
    menuitem_suspend_server->set_sensitive(true);

    if (_suspend)
    {
      menuitem_order->set_sensitive(false);
      menuitem_edit_restock->set_sensitive(false);
    }


    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_server_click() {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(false);
    menuitem_save->set_sensitive(false);
    menuitem_easteregg->set_sensitive(false);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(false);
    menuitem_server->set_sensitive(false);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_view_order->set_sensitive(true);
    menuitem_image_container->set_sensitive(false);
    menuitem_image_scoop->set_sensitive(false);
    menuitem_image_topping->set_sensitive(false);
    menuitem_manager->set_sensitive(false);
    menuitem_profitloss_report->set_sensitive(false);
    menuitem_inventory_report->set_sensitive(false);
    menuitem_server_report->set_sensitive(false);
    menuitem_order_report->set_sensitive(false);
    menuitem_customer_report->set_sensitive(false);
    menuitem_edit_flavor->set_sensitive(false);
    menuitem_edit_container->set_sensitive(false);
    menuitem_edit_topping->set_sensitive(false);
    menuitem_save_as->set_sensitive(false);
    menuitem_open_file->set_sensitive(false);
    menuitem_remove_item->set_sensitive(false);
    menuitem_suspend_server->set_sensitive(false);

    if (_suspend)
    {
      menuitem_order->set_sensitive(false);
      menuitem_edit_restock->set_sensitive(false);
    }

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_customer_click() {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(false);
    menuitem_save->set_sensitive(false);
    menuitem_easteregg->set_sensitive(false);
    menuitem_quit->set_sensitive(false);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(false);
    menuitem_item->set_sensitive(false);
    menuitem_server->set_sensitive(false);
    menuitem_fill_order->set_sensitive(false);    // TODO: bug somewhere: fixed
    menuitem_pay_for_order->set_sensitive(false);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_view_order->set_sensitive(true);
    menuitem_image_container->set_sensitive(false);
    menuitem_image_scoop->set_sensitive(false);
    menuitem_image_topping->set_sensitive(false);
    menuitem_manager->set_sensitive(false);
    menuitem_profitloss_report->set_sensitive(false);
    menuitem_inventory_report->set_sensitive(false);
    menuitem_server_report->set_sensitive(false);
    menuitem_order_report->set_sensitive(false);
    menuitem_customer_report->set_sensitive(false);
    menuitem_edit_flavor->set_sensitive(false);
    menuitem_edit_container->set_sensitive(false);
    menuitem_edit_topping->set_sensitive(false);
    menuitem_save_as->set_sensitive(false);
    menuitem_open_file->set_sensitive(false);
    menuitem_remove_item->set_sensitive(false);
    menuitem_suspend_server->set_sensitive(false);

    if (_suspend)
    {
      menuitem_order->set_sensitive(false);
      menuitem_edit_restock->set_sensitive(false);
    }


    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_view_order_click()
{
  int order_index = select_order(Mice::Order_state::Filled);
  if (order_index < 0) return;  // protects against fault

  Gtk::MessageDialog dialog{*this, "Order " + std::to_string(order_index)};
  dialog.set_secondary_text(_emp->order(order_index).order_to_string(), true);
  dialog.run();
  dialog.close();
}

void Mainwin::on_image_container_click()
{
  if (_emp->num_containers() == 0) {
      Gtk::MessageDialog dialog{*this, "At least 1 container must be created first!"};
      dialog.run();
      dialog.close();
      return;
  }

  int container_index = select_container();
  if (container_index == -1) return;

  std::string photo_file = Dialogs::input("File Name?");

  _emp->container(container_index).set_photo(photo_file);

  //    S H O W    I M A G E
  Dialogs::image(photo_file, "File", "Container file for " + _emp->container(container_index).name() + " added: " + photo_file);
}

void Mainwin::on_image_scoop_click()
{
  if (_emp->num_scoops() == 0) {
      Gtk::MessageDialog dialog{*this, "At least 1 scoop must be created first!"};
      dialog.run();
      dialog.close();
      return;
  }

  int scoop_index = select_scoop();
  if (scoop_index == -1) return;

  std::string photo_file = Dialogs::input("File Name?");

  _emp->scoop(scoop_index).set_photo(photo_file);

  //    S H O W    I M A G E
  Dialogs::image(photo_file, "File", "Scoop file for " + _emp->scoop(scoop_index).name() + " added: " + photo_file);
}

void Mainwin::on_image_topping_click()
{
  if (_emp->num_toppings() == 0) {
      Gtk::MessageDialog dialog{*this, "At least 1 topping must be created first!"};
      dialog.run();
      dialog.close();
      return;
  }

  int topping_index = select_topping();
  if (topping_index == -1) return;

  std::string photo_file = Dialogs::input("File Name?");

  _emp->topping(topping_index).set_photo(photo_file);

  //    S H O W    I M A G E
  Dialogs::image(photo_file, "File", "Topping file for " + _emp->topping(topping_index).name() + " added: " + photo_file);
}

void Mainwin::on_profitloss_report_click()
{

  double income, expenses, total_profit, server;
  std::string _income, _expenses, _total_profit, _server;
  for (int i = 0; i <_emp->num_containers(); i++){
    income += _emp->container(i).price() * 25;
    expenses += _emp->container(i).cost() * 25;
  }
  for (int i = 0; i < _emp->num_scoops(); i++){
    income += _emp->scoop(i).price() * 25;
    expenses += _emp->scoop(i).cost() * 25;
  }
  for (int i = 0; i < _emp->num_toppings(); i++){
    income += _emp->topping(i).price() * 25;
    expenses += _emp->topping(i).cost() * 25;
  }
  total_profit = income - expenses;
  for (int i = 0; i < _emp->num_servers(); i++){
    server += _emp->server(i).salary() * 8;
  }
  for(int i = 0; i < std::to_string(income).size(); i++){
    if (_income[i - 3] == '.')     // 1 cent doesn't round
    {
      break;
    }
    _income += std::to_string(income)[i];
  }
  for(int i = 0; i < std::to_string(expenses).size(); i++){
    if (_expenses[i - 3] == '.')     // 1 cent doesn't round
    {
      break;
    }
    _expenses += std::to_string(expenses)[i];
  }
  for(int i = 0; i < std::to_string(total_profit).size(); i++){
    if (_total_profit[i - 3] == '.')     // 1 cent doesn't rou1nd
    {
      break;
    }
    _total_profit += std::to_string(total_profit)[i];
  }
  for(int i = 0; i < std::to_string(server).size(); i++){
    if (_server[i - 3] == '.')     // 1 cent doesn't rou1nd
    {
      break;
    }
    _server += std::to_string(server)[i];
  }

  Gtk::MessageDialog dialog{*this, "Profit/Loss Statement"};

  dialog.set_secondary_text("<tt>" "<u>Income</u>: <span fgcolor='#00f000'>$" + _income + "</span>\n<u>Expenses</u>: <span fgcolor='#ff0000'>$" + _expenses + "</span>\n<b>Total Profit: $" + _total_profit + "</b>" +
                           "\n*Numbers based on buying and selling a 25 stock of each item."
                           "\n\n<u>Employer Expenses</u>: <span fgcolor='#ff0000'>$" + _server + "</span>" +
                           "\n*Amount spent on all employees with 8 hour shifts per day.""</tt>", true);
  dialog.run();
  dialog.close();

}

void Mainwin::on_inventory_report_click()
{
  // list containers, scoops and toppings and their stock

  std::string result;
  result += "<u><b>Containers\n</b></u>";
  for (int i = 0; i <_emp->num_containers(); i++){
    result += _emp->container(i).name() + ": ";
    if (_emp->container(i).quantity() == 0)
    {
      result += "<span fgcolor='#ff0000'>" + std::to_string(_emp->container(i).quantity()) + "</span>\n";
    }
    else
      result += std::to_string(_emp->container(i).quantity()) + "\n";
  }
  result += "<u><b>Scoops\n</b></u>";
  for (int i = 0; i < _emp->num_scoops(); i++){
    result += _emp->scoop(i).name() + ": ";
    if (_emp->scoop(i).quantity() == 0)
    {
      result += "<span fgcolor='#ff0000'>" + std::to_string(_emp->scoop(i).quantity()) + "</span>\n";
    }
    else
      result += std::to_string(_emp->scoop(i).quantity()) + "\n";
  }
  result += "<u><b>Toppings\n</b></u>";
  for (int i = 0; i < _emp->num_toppings(); i++){
    result += _emp->topping(i).name() + ": ";
    if (_emp->topping(i).quantity() == 0)
    {
      result += "<span fgcolor='#ff0000'>" + std::to_string(_emp->topping(i).quantity()) + "</span>\n";
    }
    else
      result += std::to_string(_emp->topping(i).quantity()) + "\n";
  }
/////////////////////////////////////////////////////
  result += "<u><b>Removed Items\n</b></u>";
  for (int i = 0; i < _emp->num_removed_scoops(); i++){
    result += _emp->removed_scoop(i).name() + ": ";
    if (_emp->removed_scoop(i).quantity() == 0)
    {
      result += "<span fgcolor='#ff0000'>" + std::to_string(_emp->removed_scoop(i).quantity()) + "</span>\n";
    }
    else
      result += std::to_string(_emp->removed_scoop(i).quantity()) + "\n";
  }

  for (int i = 0; i < _emp->num_removed_containers(); i++){
    result += _emp->removed_container(i).name() + ": ";
    if (_emp->removed_container(i).quantity() == 0)
    {
      result += "<span fgcolor='#ff0000'>" + std::to_string(_emp->removed_container(i).quantity()) + "</span>\n";
    }
    else
      result += std::to_string(_emp->removed_container(i).quantity()) + "\n";
  }

  for (int i = 0; i < _emp->num_removed_toppings(); i++){
    result += _emp->removed_topping(i).name() + ": ";
    if (_emp->removed_topping(i).quantity() == 0)
    {
      result += "<span fgcolor='#ff0000'>" + std::to_string(_emp->removed_topping(i).quantity()) + "</span>\n";
    }
    else
      result += std::to_string(_emp->removed_topping(i).quantity()) + "\n";
  }


  Gtk::MessageDialog dialog{*this, "Inventory"};
  dialog.set_secondary_text(result, true);

  dialog.run();
  dialog.close();

}

void Mainwin::on_server_report_click()
{
  // list all server info
  std::string result;
  for (int i = 0; i <_emp->num_servers(); i++){
    result += "<b>" + _emp->server(i).name() + ": </b>\n";
    result += "ID: " + _emp->server(i).id() + "\n";
    result += "Phone: " + _emp->server(i).phone() + "\n";
    result += "Salary: $" + std::to_string(_emp->server(i).salary()) + "\n";
    result += "# of Orders: " + std::to_string(_emp->server(i).num_orders()) + "\n";
  }

  result += "<u><b>Removed Server\n</b></u>";
  for (int i = 0; i < _emp->num_removed_servers(); i++)
  {
    result += "<b>" + _emp->removed_server(i).name() + ": </b>\n";
    result += "ID: " + _emp->removed_server(i).id() + "\n";
    result += "Phone: " + _emp->removed_server(i).phone() + "\n";
    result += "Salary: $" + std::to_string(_emp->removed_server(i).salary()) + "\n";
    result += "# of Orders: " + std::to_string(_emp->removed_server(i).num_orders()) + "\n";
  }

  Gtk::MessageDialog dialog{*this, "Servers"};
  dialog.set_secondary_text(result, true);
  dialog.run();
  dialog.close();
}

void Mainwin::on_edit_server_salary_click()
{
  if (_emp->num_servers() == 0) {
      Gtk::MessageDialog dialog{*this, "At least 1 server must be created first!"};
      dialog.run();
      dialog.close();
      return;
    }

  int server_index = select_server();
  if (server_index == -1) return;

  double new_salary = std::stof(Dialogs::input("New Salary?").c_str());

  _emp->server(server_index).set_salary(new_salary);

}

void Mainwin::on_edit_restock_click()
{
  // /////////////////////////////
  // Select Item Type
  Gtk::Dialog dialog_type{"Select Item Type", *this};
  //dialog_type.set_title("Select Item Type");
  const int WIDTH = 15;

  // Type
  Gtk::HBox b_type;
  Gtk::Label l_type{"Type:"};
  l_type.set_width_chars(WIDTH);
  b_type.pack_start(l_type, Gtk::PACK_SHRINK);

  // TODO: Replace this with 3 large, colorful buttons
  Gtk::ComboBoxText c_type;
  c_type.set_size_request(WIDTH*10);
  const int CONTAINER = 0;
  c_type.append("Container");
  const int SCOOP = 1;
  c_type.append("Ice Cream Flavor");
  const int TOPPING = 2;
  c_type.append("Topping");
  b_type.pack_start(c_type, Gtk::PACK_SHRINK);
  dialog_type.get_vbox()->pack_start(b_type, Gtk::PACK_SHRINK);

  // Show dialog_type
  dialog_type.add_button("Cancel", 0);
  dialog_type.add_button("OK", 1);
  dialog_type.show_all();
  if (dialog_type.run() != 1) {
      dialog_type.close();
      return;
  }
  int type = c_type.get_active_row_number();

  dialog_type.close();

  //int added_stock = std::stoi(Dialogs::input("How much stock do you want to add?").c_str());

  Gtk::Dialog dialog;
  if (type == CONTAINER)
  {
    int container_index = select_container();
    _emp->container(container_index).restock();
  }
  else if (type == SCOOP)
  {
    int scoop_index = select_scoop();
    _emp->scoop(scoop_index).restock();
  }
  else // T O P P I N G
  {
    int topping_index = select_topping();
    _emp->topping(topping_index).restock();
  }
}

void Mainwin::on_order_report_click()
{
  // unfilled
  // filled (unpaid)
  //std::vector<std::string> buttons = {"No", "Yes"};
  //int option = Dialogs::question("Would you like to view completed orders as well?", "Options", buttons);
  int option;

  Gtk::Dialog dialog_option{"Would you like to view completed orders as well?", *this};
  dialog_option.set_default_size(550,50); //width, height
  dialog_option.add_button("No", -1);
  dialog_option.add_button("Yes", 1);
  option = dialog_option.run();
  dialog_option.show_all();
  dialog_option.close();


  std::string result;
  for (int i = 0; i < _emp->num_orders(); i++)
  {
    if (option == -1)
    {
      if (_emp->order(i).state() == Mice::Order_state::Paid)
        continue;
    }
    result += "Order " + std::to_string(i) + " ";
    switch(_emp->order(i).state())
    {
      case Mice::Order_state::Unfilled: result += "(Unfilled)\n"; break;
      case Mice::Order_state::Filled: result += "(Filled)\n"; break;
      case Mice::Order_state::Canceled: result += "(Cancelled)\n"; break;
      case Mice::Order_state::Paid: result += "(Paid)\n"; break;
    }

  }

  Gtk::MessageDialog dialog{*this, "Order Report"};
  dialog.set_secondary_text(result, true);
  dialog.run();
  dialog.close();

}

void Mainwin::on_customer_report_click()
{
  std::string result;
  for (int i = 0; i <_emp->num_customers(); i++){
    result += "<b>" + _emp->customer(i).name() + ": </b>\n";
    result += "ID: " + _emp->customer(i).id() + "\n";
    result += "Phone: " + _emp->customer(i).phone() + "\n";
  }
  Gtk::MessageDialog dialog{*this, "Customers"};
  dialog.set_secondary_text(result, true);
  dialog.run();
  dialog.close();
}

void Mainwin::on_edit_flavor_click()
{
    int scoop_index = select_scoop();
    if (scoop_index == -1)
    {
      return;
    }
    std::string name = _emp->scoop(scoop_index).name(), description = _emp->scoop(scoop_index).description();
    double cost, price;

    Gtk::Dialog dialog{"Edit Flavor", *this};
    //dialog_type.set_title("Select Item Type");
    const int WIDTH = 15;

    Gtk::HBox b_name;
    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(WIDTH);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);
    Gtk::Entry e_name;
    e_name.set_max_length(WIDTH*4);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    Gtk::HBox b_desc;
    Gtk::Label l_desc{"Description:"};
    l_desc.set_width_chars(WIDTH);
    b_desc.pack_start(l_desc, Gtk::PACK_SHRINK);
    Gtk::Entry e_desc;
    e_desc.set_max_length(WIDTH*4);
    b_desc.pack_start(e_desc, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_desc, Gtk::PACK_SHRINK);

    Gtk::HBox b_cost;
    Gtk::Label l_cost{"Cost:"};
    l_cost.set_width_chars(WIDTH);
    b_cost.pack_start(l_cost, Gtk::PACK_SHRINK);
    Gtk::Entry e_cost;
    e_cost.set_max_length(WIDTH*4);
    b_cost.pack_start(e_cost, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_cost, Gtk::PACK_SHRINK);

    Gtk::HBox b_price;
    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(WIDTH);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);
    Gtk::Entry e_price;
    e_price.set_max_length(WIDTH*4);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    e_name.set_text(_emp->scoop(scoop_index).name());
    e_desc.set_text(_emp->scoop(scoop_index).description());
    e_cost.set_text(std::to_string(_emp->scoop(scoop_index).cost()));
    e_price.set_text(std::to_string(_emp->scoop(scoop_index).price()));

    bool valid_data = false;
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.show_all();

    while (!valid_data) // while it isn't true
    {
      if (dialog.run() != 1){
        dialog.close();
        return;
      }
      valid_data = true;


      for (int i = 0; i < _emp->num_scoops(); i++){
        if (i == scoop_index){
          i++;
        }
        if (e_name.get_text() == _emp->scoop(i).name()){
          valid_data = false;
          e_name.set_text("*** duplicate name ***");
        }
      }
      try {
          cost = std::stod(e_cost.get_text());
      } catch(std::exception e) {
          e_cost.set_text("*** invalid cost ***");
          valid_data = false;
      }
      try {
          price = std::stod(e_price.get_text());
      } catch(std::exception e) {
          e_price.set_text("*** invalid price ***");
          valid_data = false;
      }
    }
    // Works but not effecient :)
    Mice::Scoop scoop(e_name.get_text(), e_desc.get_text(), cost, price);
    _emp->scoop_setter(scoop, scoop_index);

    dialog.close();
}

void Mainwin::on_edit_container_click(){
    int index = select_container();
    if (index == -1)
    {
      return;
    }
    std::string name = _emp->container(index).name(), description = _emp->container(index).description();
    double cost, price;
    int max_scoops;

    Gtk::Dialog dialog{"Edit Container", *this};
    //dialog_type.set_title("Select Item Type");
    const int WIDTH = 15;

    Gtk::HBox b_name;
    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(WIDTH);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);
    Gtk::Entry e_name;
    e_name.set_max_length(WIDTH*4);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    Gtk::HBox b_desc;
    Gtk::Label l_desc{"Description:"};
    l_desc.set_width_chars(WIDTH);
    b_desc.pack_start(l_desc, Gtk::PACK_SHRINK);
    Gtk::Entry e_desc;
    e_desc.set_max_length(WIDTH*4);
    b_desc.pack_start(e_desc, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_desc, Gtk::PACK_SHRINK);

    Gtk::HBox b_cost;
    Gtk::Label l_cost{"Cost:"};
    l_cost.set_width_chars(WIDTH);
    b_cost.pack_start(l_cost, Gtk::PACK_SHRINK);
    Gtk::Entry e_cost;
    e_cost.set_max_length(WIDTH*4);
    b_cost.pack_start(e_cost, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_cost, Gtk::PACK_SHRINK);

    Gtk::HBox b_price;
    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(WIDTH);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);
    Gtk::Entry e_price;
    e_price.set_max_length(WIDTH*4);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    Gtk::HBox b_max;
    Gtk::Label l_max{"Max Scoops:"};
    l_max.set_width_chars(WIDTH);
    b_max.pack_start(l_max, Gtk::PACK_SHRINK);
    Gtk::Entry e_max;
    e_max.set_max_length(WIDTH*4);
    b_max.pack_start(e_max, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_max, Gtk::PACK_SHRINK);

    e_name.set_text(_emp->container(index).name());
    e_desc.set_text(_emp->container(index).description());
    e_cost.set_text(std::to_string(_emp->container(index).cost()));
    e_price.set_text(std::to_string(_emp->container(index).price()));
    e_max.set_text(std::to_string(_emp->container(index).max_scoops()));

    bool valid_data = false;
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.show_all();

    while (!valid_data) // while it isn't true
    {
      if (dialog.run() != 1){
        dialog.close();
        return;
      }
      valid_data = true;


      for (int i = 0; i < _emp->num_containers(); i++){
        if (i == index){
          i++;
        }
        if (e_name.get_text() == _emp->container(i).name()){
          valid_data = false;
          e_name.set_text("*** duplicate name ***");
        }
      }
      try {
          cost = std::stod(e_cost.get_text());
      } catch(std::exception e) {
          e_cost.set_text("*** invalid cost ***");
          valid_data = false;
      }
      try {
          price = std::stod(e_price.get_text());
      } catch(std::exception e) {
          e_price.set_text("*** invalid price ***");
          valid_data = false;
      }
      try {
          max_scoops = std::stod(e_max.get_text());
      } catch(std::exception e) {
          e_max.set_text("*** invalid max ***");
          valid_data = false;
      }
    }
    // Works but not effecient :)
    Mice::Container container(e_name.get_text(), e_desc.get_text(), cost, price, max_scoops);
    _emp->container_setter(container, index);

    dialog.close();
}

void Mainwin::on_edit_topping_click(){

    int index = select_topping();
    if (index == -1)
    {
      return;
    }
    std::string name = _emp->topping(index).name(), description = _emp->topping(index).description();
    double cost, price;
    int amount = _emp->topping(index).amount();

    Gtk::Dialog dialog{"Edit Topping", *this};
    //dialog_type.set_title("Select Item Type");
    const int WIDTH = 15;

    Gtk::HBox b_name;
    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(WIDTH);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);
    Gtk::Entry e_name;
    e_name.set_max_length(WIDTH*4);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    Gtk::HBox b_desc;
    Gtk::Label l_desc{"Description:"};
    l_desc.set_width_chars(WIDTH);
    b_desc.pack_start(l_desc, Gtk::PACK_SHRINK);
    Gtk::Entry e_desc;
    e_desc.set_max_length(WIDTH*4);
    b_desc.pack_start(e_desc, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_desc, Gtk::PACK_SHRINK);

    Gtk::HBox b_cost;
    Gtk::Label l_cost{"Cost:"};
    l_cost.set_width_chars(WIDTH);
    b_cost.pack_start(l_cost, Gtk::PACK_SHRINK);
    Gtk::Entry e_cost;
    e_cost.set_max_length(WIDTH*4);
    b_cost.pack_start(e_cost, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_cost, Gtk::PACK_SHRINK);

    Gtk::HBox b_price;
    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(WIDTH);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);
    Gtk::Entry e_price;
    e_price.set_max_length(WIDTH*4);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    e_name.set_text(_emp->topping(index).name());
    e_desc.set_text(_emp->topping(index).description());
    e_cost.set_text(std::to_string(_emp->topping(index).cost()));
    e_price.set_text(std::to_string(_emp->topping(index).price()));

    bool valid_data = false;
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.show_all();

    while (!valid_data) // while it isn't true
    {
      if (dialog.run() != 1){
        dialog.close();
        return;
      }
      valid_data = true;


      for (int i = 0; i < _emp->num_toppings(); i++){
        if (i == index){
          i++;
        }
        if (e_name.get_text() == _emp->topping(i).name()){
          valid_data = false;
          e_name.set_text("*** duplicate name ***");
        }
      }
      try {
          cost = std::stod(e_cost.get_text());
      } catch(std::exception e) {
          e_cost.set_text("*** invalid cost ***");
          valid_data = false;
      }
      try {
          price = std::stod(e_price.get_text());
      } catch(std::exception e) {
          e_price.set_text("*** invalid price ***");
          valid_data = false;
      }
    }
    // Works but not effecient :)
    Mice::Topping topping(e_name.get_text(), e_desc.get_text(), cost, price, amount);
    _emp->topping_setter(topping, index);

    dialog.close();
}

void Mainwin::on_remove_item_click(){
  // /////////////////////////////
  // Select Item Type
  Gtk::Dialog dialog_type{"Select Item Type", *this};
  //dialog_type.set_title("Select Item Type");
  const int WIDTH = 15;

  // Type
  Gtk::HBox b_type;

  Gtk::Label l_type{"Type:"};
  l_type.set_width_chars(WIDTH);
  b_type.pack_start(l_type, Gtk::PACK_SHRINK);

  Gtk::ComboBoxText c_type;
  c_type.set_size_request(WIDTH*10);
  const int CONTAINER = 0;
  c_type.append("Container");
  const int SCOOP = 1;
  c_type.append("Ice Cream Flavor");
  const int TOPPING = 2;
  c_type.append("Topping");
  b_type.pack_start(c_type, Gtk::PACK_SHRINK);
  dialog_type.get_vbox()->pack_start(b_type, Gtk::PACK_SHRINK);

  // Show dialog_type
  dialog_type.add_button("Cancel", 0);
  dialog_type.add_button("OK", 1);
  dialog_type.show_all();
  if (dialog_type.run() != 1) {
      dialog_type.close();
      return;
  }

  int type = c_type.get_active_row_number();
  dialog_type.close();

  int index;
  if (type == CONTAINER) {
    index = select_container();
    _emp->container_remover(index);
  }
  else if (type == SCOOP) {
    index = select_scoop();
    _emp->scoop_remover(index);
  }
  else {
    index = select_topping();
    _emp->topping_remover(index);
  }

}

void Mainwin::on_file_suspend_server_click(){
  _suspend = true;
  menuitem_order->set_sensitive(false);
  menuitem_edit_restock->set_sensitive(false);

  for (int i = 0; i < _emp->num_servers(); i++) {
      if (!_emp->server(i).is_active())  // if not active
      {
        _emp->server_remover(i);
      }
  }
}

void Mainwin::on_file_restore_server_click(){
  _suspend = false;
  menuitem_order->set_sensitive(true);
  menuitem_edit_restock->set_sensitive(true);

  for (int i = 0; i < _emp->num_removed_servers(); i++)
  {
    _emp->add_server(_emp->removed_server(i));
  }
}
