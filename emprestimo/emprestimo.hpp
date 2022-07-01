#ifndef EMPRESTIMO_HPP
#define EMPRESTIMO_HPP

#include "../utils/Date.hpp"
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
    Date dataEmprestimo;
    Date dataPrevDevolucao;
    usuario *usuarioEmprestimo;
    vector<itemEmprestimo> itens;
    static int proxNum;

public:
    emprestimo(){};
    emprestimo(Date _dataPrevDevolucao, usuario *_usuario);
    ~emprestimo(){};

    vector<itemEmprestimo>::iterator encontrarLivro(livro *_livro);

    void adicionarLivro(livro *_livro);
    void excluirLivro(livro *_livro);
    void devolverLivro(livro *_livro);
    void devolverTodos();

    usuario *getUsuario() const { return this->usuarioEmprestimo; }
    int getNumero() const { return this->numero; }
    Date getDataEmprestimo() const { return this->dataEmprestimo; }
    Date getDataDevolucao(livro *_livro); // TENTAR ADICIONAR CONST
    Date getDataPrevDevolucao() const { return this->dataPrevDevolucao; }
    bool livroFoiDevolvido(livro *_livro); // TENTAR ADICIONAR CONST
    vector<itemEmprestimo> getItens() const { return this->itens; }
    void setDataPenalizacao();
};

emprestimo::emprestimo(Date _dataPrevDevolucao, usuario *_usuario)
{
    this->dataEmprestimo = Date();

    if (_usuario->getDataPenalizacao() > Date())
        throw runtime_error("Usuário está penalizado! E não pode pegar um empréstimo!");

    this->numero = ++proxNum;
    this->dataPrevDevolucao = _dataPrevDevolucao;
    this->usuarioEmprestimo = _usuario;
}

Date emprestimo::getDataDevolucao(livro *_livro)
{
    vector<itemEmprestimo>::iterator it = encontrarLivro(_livro);

    if (!livroFoiDevolvido(_livro))
        throw runtime_error("Livro nao foi devolvido");

    return it->getDataDevolucao();
}

void emprestimo::adicionarLivro(livro *_livro)
{
    if (_livro->getQtdExemplares() == 0)
        throw runtime_error("Livro não tem quantidade disponível!");

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

void emprestimo::setDataPenalizacao()
{
    int deltaPenalizacao = this->getDataPrevDevolucao() - Date();
    Date dataPenalizacao = Date();
    if (deltaPenalizacao > 0)
        dataPenalizacao.incrementar3Dia(deltaPenalizacao);

    this->usuarioEmprestimo->setDataPenalizacao(dataPenalizacao);
}

void emprestimo::devolverLivro(livro *_livro)
{
    vector<itemEmprestimo>::iterator it = encontrarLivro(_livro);
    it->setDataDevolucao();
    _livro->incrementaQtdExemplares();

    for (auto i : this->itens)
        if (!i.getDataDevolucao().isZero())
            return;

    setDataPenalizacao();
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

    setDataPenalizacao();
}

bool emprestimo::livroFoiDevolvido(livro *_livro)
{
    vector<itemEmprestimo>::iterator it = encontrarLivro(_livro);

    if (it->getDataDevolucao() == Date(0))
        return false;

    return true;
}

#endif