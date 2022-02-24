#ifndef _CONTAINER_H
#define _CONTAINER_H

#include "item.h"
#include <iostream>
#include <fstream>

namespace Mice {

class Container : public Item {
  public:
    Container(std::string name, std::string description, double cost, double price,
              int max_scoops);
    Container(std::istream& ist);
    void save(std::ostream& ost);
    std::string type() const override;
    int max_scoops() const;

    std::string photo() const;
    void set_photo(std::string photo);
  private:
    int _max_scoops;
    std::string _photo;
};

}
#endif
