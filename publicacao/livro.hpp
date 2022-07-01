#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <vector>
#include "publicacao.hpp"
class livro : public publicacao
{
private:
    string autores;
    int qtdExemplares;

public:
    livro(){};
    livro(const int _codPublicacao, const string _titulo, const string _editora, const int _ano, const string _autores) : publicacao(_codPublicacao, _titulo, _editora, _ano), autores(_autores), qtdExemplares(0){};
    livro(const int _codPublicacao, const string _titulo, const string _editora, const int _ano, const string _autores, const int _qtdExemplares) : publicacao(_codPublicacao, _titulo, _editora, _ano), autores(_autores), qtdExemplares(_qtdExemplares){};
    ~livro(){};

    string getAutores() const { return this->autores; };
    int getQtdExemplares() const { return this->qtdExemplares; };

    void incrementaQtdExemplares();
    void decrementaQtdExemplares();

    void setAutores(const string _autores) { this->autores = _autores; };
    void setQtdExemplares(const int _qtdExemplares) { this->qtdExemplares = _qtdExemplares; };

    void setDados(map<string, string> dados);

    bool operator==(const livro _livro) const;
};

/**
 * @brief Seta os dados de um livro inicializado sem dados
 *
 * @param dados
 */

void livro::setDados(map<string, string> dados)
{
    publicacao::setDados(dados);
    this->setAutores(dados["Autores"]);
    this->setQtdExemplares(stoi(dados["QtdExemplares"]));
}

void livro::incrementaQtdExemplares()
{
    this->qtdExemplares++;
}

void livro::decrementaQtdExemplares()
{
    if (this->getQtdExemplares() == 0)
        throw std::invalid_argument("Nao é possível remover exemplares de uma publicacao que não possui exemplares");

    this->qtdExemplares--;
}

bool livro::operator==(const livro _livro) const
{
    return (
        this->getCodPublicacao() == _livro.getCodPublicacao() &&
        this->getAno() == _livro.getAno() &&
        this->getAutores() == _livro.getAutores() &&
        this->getEditora() == _livro.getEditora() &&
        this->getTitulo() == _livro.getTitulo());
}

#endif