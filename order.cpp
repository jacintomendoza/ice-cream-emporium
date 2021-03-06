#include "order.h"
#include <iostream>
#include <stdexcept>

namespace Mice {

    Order::Order(Customer customer, int order_number)
        : _customer{customer}, _id{order_number}, _state{Order_state::Unfilled} { }
    Order::Order(std::istream& ist) {
        std::string header1, header2;

        // The header must have been stripped from the incoming stream at this point
        ist >> _id; ist.ignore();
        int state;
        ist >> state; ist.ignore();
        _state = (state == 0) ? Order_state::Canceled :
                 (state == 1) ? Order_state::Unfilled :
                 (state == 2) ? Order_state::Filled : Order_state::Paid;

        std::getline(ist, header1);
        std::getline(ist, header2);
        if (header1 != "#") throw std::runtime_error("missing # during Order's Customer input");
        if (header2 != "CUSTOMER") throw std::runtime_error("missing CUSTOMER during Order input");
        _customer = Customer{ist};

        std::getline(ist, header1);
        std::getline(ist, header2);
        if (header1 != "#") throw std::runtime_error("missing # during Order's Server input");
        if (header2 != "SERVER") throw std::runtime_error("missing SERVER during Order input");
        _server = Server{ist};

        while (true) {
            std::getline(ist, header1); // header
            std::getline(ist, header2);
            if (header1 != "#") throw std::runtime_error("missing # during Order input");

            if (header2 == "END ORDER") break;  // footer
            else if (header2 == "SERVING") _servings.push_back(Mice::Serving{ist});
            else throw std::runtime_error("invalid serving in Order");
        }
    }

    void Order::save(std::ostream& ost) {
        ost << "#" << std::endl << "ORDER" << std::endl; // header
        ost << _id << std::endl;
        ost << ((_state == Order_state::Canceled) ? 0 :
                (_state == Order_state::Unfilled) ? 1 :
                (_state == Order_state::Filled)   ? 2 : 3) << std::endl;
        _customer.save(ost);
        _server.save(ost);
        for (Serving s : _servings) s.save(ost);
        ost << "#" << std::endl << "END ORDER" << std::endl; // header
    }

    void Order::add_serving(Serving serving) {_servings.push_back(serving);}
    std::vector<Serving> Order::servings() const {return _servings;}

    void Order::fill(Server server) {process_event(Order_event::Fill, server);}
    void Order::pay() {process_event(Order_event::Pay);}
    void Order::cancel() {process_event(Order_event::Cancel);}

    int Order::id() const {return _id;}
    double Order::cost() const {return 0;}
    double Order::price() const {return 0;}
    Order_state Order::state() const {return _state;}

    // STATE MACHINE that manages Order's state
    void Order::process_event(Order_event event, Server server) {
        if (_state == Order_state::Unfilled) {
            if (event == Order_event::Fill) {
                _state = Order_state::Filled;
                _server = server;
            } else if (event == Order_event::Cancel) {
                _state = Order_state::Canceled;
            } else {
                throw std::runtime_error("Invalid state transition in Unfilled");
            }
        } else if (_state == Order_state::Filled) {
            if (event == Order_event::Pay) {
                _state = Order_state::Paid;
            } else {
                throw std::runtime_error("Invalid state transition in Filled");
            }
        } else if (_state == Order_state::Paid) {
            throw std::runtime_error("State transition attempted in Paid");
        } else if (_state == Order_state::Canceled) {
            throw std::runtime_error("State transition attempted in Canceled");
        } else {
            throw std::runtime_error("Invalid state");
        }
    }

// String output for order
std::string Order::order_to_string(){

  double price;
  std::string result;
  for (int i = 0; i < _servings.size(); i++)
  {
    result += "===Serving " + std::to_string(i + 1) + "===\n";
    result += "Container: " + servings()[i].container().name() + "\n";
    price += servings()[i].container().price(); //$$$

    result += "Scoops: ";
    for (int j = 0; j < servings()[i].scoops().size(); j++)
    {
      result += servings()[i].scoops()[j].name();
      price += servings()[i].scoops()[j].price(); //$$$

      if (j != servings()[i].scoops().size() - 1) {result += ", ";}
    }

    result += "\nToppings: ";
    for (int j = 0; j < servings()[i].toppings().size() ; j++)
    {
      result += servings()[i].toppings()[j].name();
      price += servings()[i].toppings()[j].price();

      if (j != servings()[i].toppings().size() - 1) {result += ", ";}
    }
    result += "\n\n";
  }

  result += "\tPrice: $";
  std::string string_price;
  for(int i = 0; i < std::to_string(price).size(); i++)
  {
    if (string_price[i - 3] == '.')     // 1 cent doesn't round
    {
      break;
    }
    string_price += std::to_string(price)[i];
  }
  result += string_price;
  return result;
}

}

// OPERATOR OVERLOADING for class Order
std::ostream& operator<<(std::ostream& os, const Mice::Order& order) {
    std::string nlnl = "";
    for (Mice::Serving s : order.servings()) {os << nlnl << s; nlnl = "\n\n";}
    return os;
}
