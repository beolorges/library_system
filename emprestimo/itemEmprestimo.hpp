#ifndef ITEMEMPRESTIMO_HPP
#define ITEMEMPRESTIMO_HPP

#include "../publicacao/livro.hpp"
#include "../utils/Date.hpp"

class itemEmprestimo
{
private:
    livro *item;
    Date dataDevolucao;

public:
    itemEmprestimo(livro *_item) : item(_item), dataDevolucao(0){};
    ~itemEmprestimo(){};

    livro *getPonteiroParaItem() const { return this->item; }
    livro getItem() const { return *item; };
    Date getDataDevolucao() const { return dataDevolucao; };

    void setDataDevolucao() { this->dataDevolucao = Date(); };
};

#endif