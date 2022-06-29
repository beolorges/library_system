#ifndef PUBLICACAO_HPP
#define PUBLICACAO_HPP

#include <iostream>
using namespace std;

class publicacao
{
private:
    int codPublicacao;
    string titulo;
    string editora;
    int ano;

public:
    publicacao(const int _codPublicacao, const string _titulo, const string _editora, const int _ano) : codPublicacao(_codPublicacao), titulo(_titulo), editora(_editora), ano(_ano){};
    ~publicacao(){};

    int getCodPublicacao() const { return this->codPublicacao; };
    int getAno() const { return this->ano; };
    string getTitulo() const { return this->titulo; };
    string getEditora() const { return this->editora; };
};

#endif