#ifndef EMPRESTIMO_HPP
#define EMPRESTIMO_HPP

#include "../utils/date.hpp"
#include "../usuario/usuario.hpp"
#include "itemEmprestimo.hpp"
#include "../publicacao/livro.hpp"
#include <vector>
#include <algorithm>

using namespace std;

class emprestimo
{
private:
    int numero;
    date dataEmprestimo;
    date dataPrevDevolucao;
    usuario usuarioEmprestimo;
    vector<itemEmprestimo> itens;
    static int proxNum;

public:
    emprestimo(date _dataPrevDevolucao, usuario _usuario) : dataPrevDevolucao(_dataPrevDevolucao), usuarioEmprestimo(_usuario), dataEmprestimo(), numero(++this->proxNum){};
    ~emprestimo(){};

    vector<itemEmprestimo>::iterator encontrarLivro(livro *_livro);

    void adicionarLivro(livro *_livro);
    void excluirLivro(livro *_livro);
    void devolverLivro(livro *_livro);
    void devolverTodos();

    usuario getUser() const { return this->usuarioEmprestimo; }
    int getNumber() const { return this->numero; }
    date getDataEmprestimo() const { return this->dataEmprestimo; }
    date getDataDevolucao(livro *_livro); // TENTAR ADICIONAR CONST
    date getDataPrevDevolucao() const { return this->dataPrevDevolucao; }
    vector<itemEmprestimo> getItens() const { return this->itens; }
};

date emprestimo::getDataDevolucao(livro *_livro)
{
    vector<itemEmprestimo>::iterator it = encontrarLivro(_livro);

    return it->getDataDevolucao();
}

void emprestimo::adicionarLivro(livro *_livro)
{
    _livro->decrementaQtdExemplares();
    this->itens.push_back(itemEmprestimo(_livro));
}

vector<itemEmprestimo>::iterator emprestimo::encontrarLivro(livro *_livro)
{
    vector<itemEmprestimo>::iterator it = this->itens.begin();
    while (it != this->itens.end())
    {
        if (it->getItem() == *_livro)
            break;

        it++;
    }

    if (it == this->itens.end())
        throw runtime_error("Livro não encontrado");

    return it;
}

void emprestimo::excluirLivro(livro *_livro)
{
    vector<itemEmprestimo>::iterator it = encontrarLivro(_livro);

    _livro->incrementaQtdExemplares();
    this->itens.erase(it);
}

void emprestimo::devolverLivro(livro *_livro)
{
    vector<itemEmprestimo>::iterator it = encontrarLivro(_livro);
    it->setDataDevolucao();
    _livro->incrementaQtdExemplares();
}

void emprestimo::devolverTodos()
{
    vector<itemEmprestimo>::iterator it = this->itens.begin();
    while (it != this->itens.end())
    {
        it->setDataDevolucao();
        it->getPonteiroParaItem()->incrementaQtdExemplares();
        it++;
    }
}

#endif