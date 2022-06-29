#ifndef DATE_HPP
#define DATE_HPP

#include <ctime>
#include <iostream>

class date
{
public:
    int dia;
    int mes;
    int ano;

    date();
    date(int _null) : dia(0), mes(0), ano(0){};
    date(int dia, int mes, int ano);
    ~date(){};

    int getDia() const { return dia; };
    int getMes() const { return mes; };
    int getAno() const { return ano; };
};

date::date()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    this->ano = now->tm_year + 1900;
    this->mes = now->tm_mon + 1;
    this->dia = now->tm_mday;
}

date::date(int dia, int mes, int ano)
{
    if (dia < 1 || dia > 31)
        throw std::runtime_error("Invalid day");

    if (mes < 1 || mes > 12)
        throw std::runtime_error("Invalid month");

    if (ano < 0)
        throw std::runtime_error("Invalid year");

    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

#endif