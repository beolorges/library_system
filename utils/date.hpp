#ifndef DATE_HPP
#define DATE_HPP

#include <ctime>

class date
{
public:
    int dia;
    int mes;
    int ano;

    date();
    date(int dia, int mes, int ano) : dia(dia), mes(mes), ano(ano){};
    ~date(){};
};

date::date()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    this->ano = now->tm_year + 1900;
    this->mes = now->tm_mon + 1;
    this->dia = now->tm_mday;
}

#endif