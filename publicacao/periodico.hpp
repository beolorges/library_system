#ifndef PERIODICO_HPP
#define PERIODICO_HPP

#include "publicacao.hpp"
using namespace std;

class periodico : public publicacao
{
private:
    string mes;
    int numEdicao;

public:
    periodico(const int _codPublicacao, const string _titulo, const string _editora, const int _ano, const string _mes, const int _numEdicao) : publicacao(_codPublicacao, _titulo, _editora, _ano), mes(_mes), numEdicao(_numEdicao){};
    ~periodico(){};

    string getMes() const { return this->mes; };
    int getNumEdicao() const { return this->numEdicao; };
};

#endif