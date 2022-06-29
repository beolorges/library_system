#include "itemEmprestimo.hpp"
#include "../publicacao/livro.hpp"

void testGetItem(itemEmprestimo _itemEmprestimo)
{
    if (_itemEmprestimo.getItem().getTitulo() != "testTitle")
        throw std::runtime_error("The title was not created correctly");
};

void testGetDataDevolucao(itemEmprestimo _itemEmprestimo)
{
    if (_itemEmprestimo.getDataDevolucao().getDia() != 0)
        throw std::runtime_error("The date was not created correctly");

    if (_itemEmprestimo.getDataDevolucao().getMes() != 0)
        throw std::runtime_error("The date was not created correctly");

    if (_itemEmprestimo.getDataDevolucao().getAno() != 0)
        throw std::runtime_error("The date was not created correctly");
};

void testSetDataDevolucao(itemEmprestimo _itemEmprestimo)
{
    _itemEmprestimo.setDataDevolucao();
    if (_itemEmprestimo.getDataDevolucao().getDia() != 29)
        throw std::runtime_error("The day was not created correctly");

    if (_itemEmprestimo.getDataDevolucao().getMes() != 6)
        throw std::runtime_error("The month was not created correctly");

    if (_itemEmprestimo.getDataDevolucao().getAno() != 2022)
        throw std::runtime_error("The year was not created correctly");
};

int main()
{
    livro *livroTest = new livro(10, "testTitle", "testEditora", 2222, "testMonth");
    try
    {
        itemEmprestimo itemEmprestimoTest(livroTest);
        testGetItem(itemEmprestimoTest);
        testGetDataDevolucao(itemEmprestimoTest);
        testSetDataDevolucao(itemEmprestimoTest);
        std::cout << "Todos os testes passaram" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}