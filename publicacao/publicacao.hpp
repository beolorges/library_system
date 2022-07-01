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
    publicacao(){};
    publicacao(const int _codPublicacao, const string _titulo, const string _editora, const int _ano) : codPublicacao(_codPublicacao), titulo(_titulo), editora(_editora), ano(_ano){};
    virtual ~publicacao(){};

    int getCodPublicacao() const { return this->codPublicacao; };
    int getAno() const { return this->ano; };
    string getTitulo() const { return this->titulo; };
    string getEditora() const { return this->editora; };

    void setCodPublicacao(const int _codPublicacao) { this->codPublicacao = _codPublicacao; };
    void setAno(const int _ano) { this->ano = _ano; };
    void setTitulo(const string _titulo) { this->titulo = _titulo; };
    void setEditora(const string _editora) { this->editora = _editora; };

    void setDados(map<string, string> dados);
};

void publicacao::setDados(map<string, string> dados)
{
    this->setCodPublicacao(stoi(dados["Codigo"]));
    this->setTitulo(dados["Titulo"]);
    this->setEditora(dados["Editora"]);
    this->setAno(stoi(dados["Ano"]));
}

#endif