#ifndef EMPORIUM_H
#define EMPORIUM_H

#include "container.h"
#include "scoop.h"
#include "topping.h"
#include "serving.h"
#include "order.h"
#include "server.h"
#include "customer.h"
#include "manager.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace Mice {

class Emporium {
    public:
        Emporium(std::string name);
        Emporium(std::istream& ist);
        void save(std::ostream& ost);

        std::string name();
        double cash_register();
        void debit(double amount);
        void credit(double amount);
        int next_id();

        int num_containers();
        int num_scoops();
        int num_toppings();
        int num_orders();
        int num_servers();
        int num_customers();

        int num_removed_containers();
        int num_removed_scoops();
        int num_removed_toppings();
        int num_removed_servers();

        Container& removed_container(int index);
        Scoop& removed_scoop(int index);
        Topping& removed_topping(int index);
        Server& removed_server(int index);

        Container& container(int index);
        Scoop& scoop(int index);
        Topping& topping(int index);
        Order& order(int index);
        Server& server(int index);
        Customer& customer(int index);

        void add_container(Container container);
        void add_scoop(Scoop scoop);
        void add_topping(Topping topping);
        void add_order(Order order);
        void add_server(Server server);
        void add_customer(Customer customer);
        void add_manager(Manager manager);

        void scoop_setter(Scoop scoop, int scoop_index);
        void container_setter(Container container, int index);
        void topping_setter(Topping toppping, int index);

        void container_remover(int index);
        void scoop_remover(int index);
        void topping_remover(int index);
        void server_remover(int index);

    private:
        std::string _name;
        double _cash_register;
        int _id;

        std::vector<Mice::Container> _containers;      // All defined containers
        std::vector<Mice::Scoop> _scoops;              // All defined scoops
        std::vector<Mice::Topping> _toppings;          // All defined toppings
        std::vector<Mice::Order> _orders;              // All defined orders
        std::vector<Mice::Server> _servers;            // All defined servers
        std::vector<Mice::Customer> _customers;        // All defined customers
        std::vector<Mice::Manager> _managers;

        std::vector<Mice::Container> _removed_containers;
        std::vector<Mice::Scoop> _removed_scoops;
        std::vector<Mice::Topping> _removed_toppings;
        std::vector<Mice::Server> _removed_servers;
};

}
#endif
