#ifndef ITEMEMPRESTIMO_HPP
#define ITEMEMPRESTIMO_HPP

#include "../publicacao/livro.hpp"
#include "../utils/date.hpp"

class itemEmprestimo
{
private:
    livro item;
    date dataDevolucao;

public:
    itemEmprestimo(livro _item) : item(_item), dataDevolucao(0){};
    ~itemEmprestimo(){};

    livro getItem() const { return item; };
    date getDataDevolucao() const { return dataDevolucao; };

    void setDataDevolucao() { this->dataDevolucao = date(); };
};

#endif