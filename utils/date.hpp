#ifndef DATE_HPP
#define DATE_HPP

#include <ctime>
#include <iostream>

using namespace std;

class Date
{
public:
    int dia;
    int mes;
    int ano;

    Date();
    Date(string);
    Date(int _null) : dia(0), mes(0), ano(0){};
    Date(int dia, int mes, int ano);
    ~Date(){};

    int getDia() const { return dia; };
    int getMes() const { return mes; };
    int getAno() const { return ano; };

    void incrementar3Dia(const int);

    bool isZero() const { return this->dia == 0 && this->mes == 0 && this->ano == 0; };

    friend ostream &operator<<(ostream &os, const Date &dt);
    friend istream &operator<<(istream &is, const Date &dt);
    friend bool operator==(const Date &dt1, const Date &dt2);
    friend bool operator>(const Date &dt1, const Date &dt2);
    int operator-(const Date &dt1) const;
};

bool operator>(const Date &dt1, const Date &dt2)
{
    if (dt1.ano > dt2.ano)
        return true;

    else if (dt1.ano == dt2.ano)
    {
        if (dt1.mes > dt2.mes)
            return true;

        else if (dt1.mes == dt2.mes)
        {
            if (dt1.dia > dt2.dia)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

/**
 * @brief Construct a new Date:: Date object com a data atual do sistema
 *
 */

Date::Date()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    this->ano = now->tm_year + 1900;
    this->mes = now->tm_mon + 1;
    this->dia = now->tm_mday;
}

/**
 * @brief Construct a new Date:: Date object a partir de um dia, mes e ano
 * Validação para o dia, mês e ano
 * @param dia
 * @param mes
 * @param ano
 */

Date::Date(int dia, int mes, int ano)
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

Date::Date(string data)
{
    if (data.size() != 10)
    {
        throw std::runtime_error("Invalid date");
    }
    this->dia = stoi(data.substr(0, 2));
    this->mes = stoi(data.substr(3, 2));
    this->ano = stoi(data.substr(6, 4));
}

/**
 * @brief Sobrecarga do operador << para imprimir a data
 *
 * @param os Ostream para imprimir a data
 * @param dt data a ser imprimida
 * @return ostream&
 */

ostream &operator<<(ostream &os, const Date &dt)
{
    if (dt.dia < 10)
        os << '0' << dt.dia << '/';
    else
        os << dt.dia << '/';

    if (dt.mes < 10)
        os << '0' << dt.mes << '/';
    else
        os << dt.mes << '/';

    os << dt.ano;

    return os;
}

istream &operator>>(istream &is, Date &dt)
{
    string data;
    is >> data;
    dt = Date(data);
    return is;
}

int Date::operator-(const Date &dt1) const
{
    int diferenca = 0;
    diferenca += this->dia - dt1.dia;
    diferenca += (this->mes - dt1.mes) * 12;
    diferenca += (this->ano - dt1.ano) * 365;

    return diferenca;
}

/**
 * @brief Compara se duas datas são iguais
 *
 * @param dt1
 * @param dt2
 * @return true
 * @return false
 */

bool operator==(const Date &dt1, const Date &dt2)
{
    return dt1.dia == dt2.dia && dt1.mes == dt2.mes && dt1.ano == dt2.ano;
}

/**
 * @brief Função para incrementar 3 dias a partir de uma data atual na classa
 * considerando que todos os meses tem apenas 30 dias
 *
 */

void Date::incrementar3Dia(const int quantidadeDias)
{
    for (int i = 0; i < quantidadeDias; i++)
    {
        this->dia += 3;
        if (this->dia > 30)
        {
            this->dia -= 30;
            this->mes++;
        }
        if (this->mes > 12)
        {
            this->mes -= 12;
            this->ano++;
        }
    }
}

#endif