#ifndef _MANAGER_H
#define _MANAGER_H

#include "person.h"
#include <string>
#include <iostream>
#include <fstream>

namespace Mice {
    class Manager : public Person {
      public:
        Manager(std::string name, std::string id, std::string phone, double salary);
        //Server(std::istream& ist);
        //void save(std::ostream& ost);

        int salary();                  // Returns salary of this manger per hour

      private:

        double _salary;
    };
}

#endif
