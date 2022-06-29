#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "../utils/date.hpp"
#include <iostream>
using namespace std;

class usuario
{
private:
    string nome;
    string cpf;
    string endereco;
    string fone;
    date dataPenalizacao;

public:
    usuario(const string _nome, const string _cpf, const string _endereco, const string _fone) : nome(_nome), cpf(_cpf), endereco(_endereco), fone(_fone), dataPenalizacao(){};
    ~usuario(){};

    string getNome() const { return this->nome; };
    string getCpf() const { return this->cpf; };
    string getEndereco() const { return this->endereco; };
    string getFone() const { return this->fone; };
    date getDataPenalizacao() const { return this->dataPenalizacao; };
};

#endif