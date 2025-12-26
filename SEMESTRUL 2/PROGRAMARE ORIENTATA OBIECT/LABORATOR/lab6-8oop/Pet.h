//
// Created by Ilinca on 25-Apr-22.
//

#ifndef LAB4_6OOP_PET_H
#define LAB4_6OOP_PET_H
#include <string>

class Pet
{
public:
    Pet() = default;
    Pet(std::string t, std::string s, double p) :type{ t }, species{ s }, price{ p } {
    }
    double getPrice() const noexcept {
        return price;
    }
    std::string getType() const {
        return type;
    }
private:
    std::string type;
    std::string species;
    double price=-1.0;

};


#endif //LAB4_6OOP_PET_H
