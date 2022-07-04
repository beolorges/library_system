#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "../date/date.hpp"

using namespace std;

class User
{
private:
    string name;
    string cpf;
    string address;
    string phone;
    Date penalizationDate;

public:
    User(string name, string cpf, string address, string phone) : name(name), cpf(cpf), address(address), phone(phone), penalizationDate(Date().getToday()){};
    User(string name, string cpf, string address, string phone, string penalizationDate) : name(name), cpf(cpf), address(address), phone(phone), penalizationDate(penalizationDate){};
    ~User(){};

    void returnAllBooks(Date);
    bool isPenalized() const { return this->getPenalizationDate() > Date().getToday(); };

    inline string getName() const { return name; };
    inline string getCpf() const { return cpf; };
    inline string getAddress() const { return address; };
    inline string getPhone() const { return phone; };
    inline Date getPenalizationDate() const { return penalizationDate; };
};

#endif