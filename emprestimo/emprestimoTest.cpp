#include "emprestimo.hpp"
#include "../usuario/usuario.hpp"
#include "../utils/date.hpp"

int emprestimo::proxNum = 0;

void testGetUser(emprestimo _emprestimo)
{
    if (_emprestimo.getUser().getNome() != "testName")
        throw runtime_error("Error setUser");
};

void testGetNumber(emprestimo _emprestimo)
{
    if (_emprestimo.getNumber() != 1)
        throw runtime_error("Error static number");
};

void testGetDataEmprestimo(emprestimo _emprestimo)
{
    if (_emprestimo.getDataEmprestimo().getDia() != 29)
        throw runtime_error("Error setDataEmprestimo");
};

void testGetDataPrevDevolucao(emprestimo _emprestimo)
{
    if (_emprestimo.getDataPrevDevolucao().getDia() != 10)
        throw runtime_error("Error setDataPrevDevolucao");
};

void testGetItens(emprestimo _emprestimo)
{
    if (_emprestimo.getItens().size() != 0)
        throw runtime_error("Error setItens");
};

void testAdicionarLivro(emprestimo _emprestimo)
{
    livro *_livro = new livro(1, "testName", "testEditora", 2222, "testAutor", 10);
    _emprestimo.adicionarLivro(_livro);

    if (_emprestimo.getItens().size() != 1)
        throw runtime_error("Error adicionarLivro");

    if (_emprestimo.getItens()[0].getItem().getTitulo() != _livro->getTitulo())
        throw runtime_error("Error adicionarLivro name");

    if (_livro->getQtdExemplares() != 9)
        throw runtime_error("Error decrementaQtdExemplares");

    delete _livro;
};

void testExcluirLivro(emprestimo _emprestimo)
{
    livro *_livro = new livro(1, "testName", "testEditora", 2222, "testAutor", 10);
    _emprestimo.adicionarLivro(_livro);
    _emprestimo.excluirLivro(_livro);

    if (_emprestimo.getItens().size() != 0)
        throw runtime_error("Error excluirLivro");

    if (_livro->getQtdExemplares() != 10)
        throw runtime_error("Error incrementaQtdExemplares");

    delete _livro;
};

void testDevolverLivro(emprestimo _emprestimo)
{
    livro *_livro = new livro(1, "testName", "testEditora", 2222, "testAutor", 10);
    _emprestimo.adicionarLivro(_livro);
    _emprestimo.devolverLivro(_livro);

    if (_emprestimo.getItens().size() != 1)
        throw runtime_error("Error devolverLivro");

    if (_livro->getQtdExemplares() != 10)
        throw runtime_error("Error incrementaQtdExemplares");

    if (_emprestimo.getDataDevolucao(_livro).getDia() != 29)
        throw runtime_error("Error setDataDevolucao");

    delete _livro;
};

void testDevolverTodosLivros(emprestimo _emprestimo)
{
    livro *_livro = new livro(1, "testName", "testEditora", 2222, "testAutor", 10);
    livro *_livro1 = new livro(1, "testName", "testEditora", 2222, "testAutor", 10);
    livro *_livro2 = new livro(1, "testName", "testEditora", 2222, "testAutor", 10);
    _emprestimo.adicionarLivro(_livro);
    _emprestimo.adicionarLivro(_livro1);
    _emprestimo.adicionarLivro(_livro2);
    _emprestimo.devolverTodos();

    if (_livro->getQtdExemplares() != 10)
        throw runtime_error("Error incrementaQtdExemplares");

    if (_livro1->getQtdExemplares() != 10)
        throw runtime_error("Error incrementaQtdExemplares");

    if (_livro2->getQtdExemplares() != 10)
        throw runtime_error("Error incrementaQtdExemplares");

    if (_emprestimo.getDataDevolucao(_livro).getDia() != 29)
        throw runtime_error("Error setDataDevolucao");

    delete _livro;
};

int main()
{
    usuario testUser("testName", "testCpf", "rua test", "testNumber");
    date testDate(10, 10, 2022);
    emprestimo testEmprestimo(testDate, testUser);

    try
    {
        testGetUser(testEmprestimo);
        testGetNumber(testEmprestimo);
        testGetDataEmprestimo(testEmprestimo);
        testGetDataPrevDevolucao(testEmprestimo);
        testGetItens(testEmprestimo);
        testAdicionarLivro(testEmprestimo);
        testExcluirLivro(testEmprestimo);
        testDevolverLivro(testEmprestimo);

        std::cout << "Todos os testes passaram" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}