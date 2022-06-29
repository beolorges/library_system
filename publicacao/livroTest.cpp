#include "livro.hpp"
#include <cstring>

void testGetTitulo(livro _livro)
{
    if (_livro.getTitulo() != "testTitle")
        throw std::runtime_error("The title was not created correctly");
}

void testGetEditora(livro _livro)
{
    if (_livro.getEditora() != "testEditora")
        throw std::runtime_error("The editora was not created correctly");
}

void testGetAno(livro _livro)
{
    if (_livro.getAno() != 2222)
        throw std::runtime_error("The year was not created correctly");
}

void testGetAutores(livro _livro)
{
    if (_livro.getAutores() != "testAutor")
        throw std::runtime_error("The autores was not created correctly");
}

void testGetQtdExemplares(livro _livro)
{
    if (_livro.getQtdExemplares() != 0)
        throw std::runtime_error("The qtdExemplares was not created correctly");

    livro lTest1(1, "testName", "testEditora", 2222, "testAutor", 10);

    if (lTest1.getQtdExemplares() != 10)
        throw std::runtime_error("The qtdExemplares was not created correctly without the number of examples");
}

void testIncrementaQtdExemplares(livro _livro)
{
    _livro.incrementaQtdExemplares();

    if (_livro.getQtdExemplares() != 1)
        throw std::runtime_error("The qtdExemplares was not incremented correctly");

    livro lTest1(1, "testName", "testEditora", 2222, "testAutor", 10);

    lTest1.incrementaQtdExemplares();

    if (lTest1.getQtdExemplares() != 11)
        throw std::runtime_error("The qtdExemplares was not incremented correctly at lTest1");
}

void testDecrementaQtdExemplares(livro _livro)
{
    try
    {
        _livro.decrementaQtdExemplares();
        throw std::runtime_error("Not thrown exception");
    }
    catch (const std::exception &e)
    {
        if (strcmp(e.what(), "Nao é possível remover exemplares de uma publicacao que não possui exemplares") != 0)
            throw std::runtime_error("Exception is not correct");
    }

    livro lTest1(1, "testName", "testEditora", 2222, "testAutor", 10);

    lTest1.decrementaQtdExemplares();

    if (lTest1.getQtdExemplares() != 9)
        throw std::runtime_error("The qtdExemplares was not decremented correctly");
}

int main()
{
    try
    {
        livro lTest(1, "testTitle", "testEditora", 2222, "testAutor");
        testGetTitulo(lTest);
        testGetEditora(lTest);
        testGetAno(lTest);
        testGetAutores(lTest);
        testGetQtdExemplares(lTest);
        testIncrementaQtdExemplares(lTest);
        testDecrementaQtdExemplares(lTest);

        std::cout << "Todos os testes passaram" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}