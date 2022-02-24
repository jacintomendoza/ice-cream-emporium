#include "manager.h"

namespace Mice {
Manager::Manager(std::string name, std::string id, std::string phone, double salary)
             : Person(name, id, phone), _salary{salary} { }
/*Server::Server(std::istream& ist) {
    // The header must have been stripped from the incoming stream at this point
    getline(ist, _name);
    getline(ist, _id);
    getline(ist, _phone);
    ist >> _salary; ist.ignore();
    ist >> _num_orders; ist.ignore();
}*/

/*void Server::save(std::ostream& ost) {
    ost << "#" << std::endl << "SERVER" << std::endl; // header
    ost << _name << std::endl;
    ost << _id << std::endl;
    ost << _phone << std::endl;
    ost << _salary << std::endl;
    ost << _num_orders << std::endl;
}*/


}
