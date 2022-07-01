#include "biblioteca.hpp"
#include <cstring>

int emprestimo::proxNum = 0;

void testAdicionarUsuario(biblioteca _biblioteca)
{
    usuario *testUser = new usuario("testName", "testCpf", "rua test", "testNumber");
    _biblioteca.adicionarUsuario(testUser);
    if (_biblioteca.getUsuarios().size() != 1)
        throw runtime_error("Erro ao adicionar usuario");

    delete testUser;
}

void testAdicionarPublicacao(biblioteca _biblioteca)
{
    livro *testBook = new livro(1, "Titulo", "Editora", 2019, "Autor", 10);
    _biblioteca.adicionarPublicacao(testBook);
    if (_biblioteca.getPublicacoes().size() != 1)
        throw runtime_error("Erro ao adicionar livro");

    delete testBook;
}

void testAdicionarEmprestimo(biblioteca _biblioteca)
{
    usuario *testUser = new usuario("testName", "testCpf", "rua test", "testNumber");
    Date testDate(10, 10, 2022);

    emprestimo *testEmprestimo = new emprestimo(testDate, *testUser);
    _biblioteca.adicionarEmprestimo(testEmprestimo);
    if (_biblioteca.getEmprestimos().size() != 1)
        throw runtime_error("Erro ao adicionar emprestimo");

    delete testUser;
    delete testEmprestimo;
}

void testAdicionarItemAoEmprestimo(biblioteca _biblioteca)
{
    usuario *testUser = new usuario("testName", "testCpf", "rua test", "testNumber");
    Date testDate(10, 10, 2022);

    emprestimo *testEmprestimo = new emprestimo(testDate, *testUser);
    livro *testBook = new livro(1, "Titulo", "Editora", 2019, "Autor", 10);
    _biblioteca.adicionarEmprestimo(testEmprestimo);
    _biblioteca.adicionarItemAoEmprestimo(testEmprestimo, testBook);
    if (_biblioteca.getEmprestimos()[0]->getItens().size() != 1)
        throw runtime_error("Erro ao adicionar item ao emprestimo");

    delete testUser;
    delete testEmprestimo;
    delete testBook;
}

void testRemoverUsuario(biblioteca _biblioteca)
{
    usuario *testUser = new usuario("testName", "testCpf", "rua test", "testNumber");
    _biblioteca.adicionarUsuario(testUser);
    _biblioteca.removerUsuario(testUser);
    if (_biblioteca.getUsuarios().size() != 0)
        throw runtime_error("Erro ao remover usuario");

    delete testUser;
}

void testRemoverPublicacao(biblioteca _biblioteca)
{
    livro *testBook = new livro(1, "Titulo", "Editora", 2019, "Autor", 10);
    livro *testBook1 = new livro(1, "TituloTest2", "Editora", 2019, "Autor", 10);
    _biblioteca.adicionarPublicacao(testBook);
    _biblioteca.adicionarPublicacao(testBook1);
    _biblioteca.removerPublicacao(testBook);

    if (_biblioteca.getPublicacoes().size() != 1)
        throw runtime_error("Erro ao remover livro");

    if (_biblioteca.getPublicacoes()[0]->getTitulo() != "TituloTest2")
        throw runtime_error("Erro ao remover livro");

    delete testBook;
}

void testRemoverEmprestimo(biblioteca _biblioteca)
{
    usuario *testUser = new usuario("testName", "testCpf", "rua test", "testNumber");
    Date testDate(10, 10, 2022);

    emprestimo *testEmprestimo = new emprestimo(testDate, *testUser);
    _biblioteca.adicionarEmprestimo(testEmprestimo);
    _biblioteca.removerEmprestimo(testEmprestimo);
    if (_biblioteca.getEmprestimos().size() != 0)
        throw runtime_error("Erro ao remover emprestimo");

    delete testUser;
    delete testEmprestimo;
}

void testBuscarPeloTitulo(biblioteca _biblioteca)
{
    livro *testBook = new livro(1, "Titulo", "Editora", 2019, "Autor", 10);
    livro *testBook1 = new livro(1, "TituloTest2", "Editora", 2019, "Autor", 10);
    periodico *testPeriodico = new periodico(3, "TituloPeriodicoTest", "Editora", 2022, "Junho", 2);
    _biblioteca.adicionarPublicacao(testBook);
    _biblioteca.adicionarPublicacao(testBook1);
    _biblioteca.adicionarPublicacao(testPeriodico);

    if (_biblioteca.buscarPublicacaoPeloTitulo("Test2")[0]->getTitulo() != testBook1->getTitulo())
        throw runtime_error("Erro ao encontrar livro pelo título");

    try
    {
        _biblioteca.buscarPublicacaoPeloTitulo("abacaxi");
        throw runtime_error("Não está tratando exceção");
    }
    catch (const std::exception &e)
    {
        if (strcmp(e.what(), "Não existem livros com o título pesquisado") != 0)
            throw std::runtime_error("Exception is not correct");
    }

    if (_biblioteca.buscarPublicacaoPeloTitulo("Titulo").size() != 3)
        throw std::runtime_error("Não está retornando mais de um");

    _biblioteca.removerPublicacao(testBook1);
    try
    {
        _biblioteca.buscarPublicacaoPeloTitulo("Test2");
        throw runtime_error("Não está tratando exceção após remoção");
    }
    catch (const std::exception &e)
    {
        if (strcmp(e.what(), "Não existem livros com o título pesquisado") != 0)
            throw std::runtime_error("Exception is not correct após remoção");
    }
}

void testBuscarPeloAutor(biblioteca _biblioteca)
{
    livro *testBook = new livro(1, "Titulo", "Editora", 2019, "Leonardo Borges", 10);
    livro *testBook1 = new livro(1, "TituloTest2", "Editora", 2019, "Bruna Borges", 10);
    periodico *testPeriodico = new periodico(3, "TituloPeriodicoTest", "Editora", 2022, "Junho", 2);

    _biblioteca.adicionarPublicacao(testBook);
    _biblioteca.adicionarPublicacao(testBook1);
    _biblioteca.adicionarPublicacao(testPeriodico);

    if (_biblioteca.buscarLivroPeloAutor("Bruna")[0]->getTitulo() != testBook1->getTitulo())
        throw runtime_error("Erro ao encontrar livro pelo autor");

    try
    {
        _biblioteca.buscarLivroPeloAutor("abacaxi");
        throw runtime_error("Não está tratando exceção");
    }
    catch (const std::exception &e)
    {
        if (strcmp(e.what(), "Não existem livros com o autor pesquisado") != 0)
            throw std::runtime_error("Exception is not correct");
    }

    if (_biblioteca.buscarLivroPeloAutor("Borges").size() != 2)
        throw std::runtime_error("Não está retornando mais de um");

    _biblioteca.removerPublicacao(testBook1);
    try
    {
        _biblioteca.buscarLivroPeloAutor("Bruna");
        throw runtime_error("Não está tratando exceção após remoção");
    }
    catch (const std::exception &e)
    {
        if (strcmp(e.what(), "Não existem livros com o autor pesquisado") != 0)
            throw std::runtime_error("Exception is not correct após remoção");
    }
}

void testGravarDados(biblioteca _biblioteca)
{
    usuario *testUser = new usuario("testName", "testCpf", "rua test", "testNumber");
    usuario *testUser2 = new usuario("testName2", "testCpf2", "rua test2", "testNumber2");
    Date testDate(10, 10, 2022);
    Date testDate2(12, 12, 2022);

    emprestimo *testEmprestimo = new emprestimo(testDate, *testUser);
    emprestimo *testEmprestimo2 = new emprestimo(testDate2, *testUser2);

    livro *testBook = new livro(1, "Titulo", "Editora", 2019, "Autor", 10);
    livro *testBook1 = new livro(1, "TituloTest2", "Editora", 2019, "Autor", 10);
    periodico *testPeriodico = new periodico(3, "TituloPeriodicoTest", "Editora", 2022, "Junho", 2);

    _biblioteca.adicionarUsuario(testUser);
    _biblioteca.adicionarUsuario(testUser2);
    _biblioteca.adicionarEmprestimo(testEmprestimo);
    _biblioteca.adicionarEmprestimo(testEmprestimo2);
    _biblioteca.adicionarPublicacao(testBook);
    _biblioteca.adicionarPublicacao(testBook1);
    _biblioteca.adicionarPublicacao(testPeriodico);
    _biblioteca.adicionarItemAoEmprestimo(testEmprestimo, testBook);
    _biblioteca.adicionarItemAoEmprestimo(testEmprestimo, testBook1);
    _biblioteca.adicionarItemAoEmprestimo(testEmprestimo2, testBook1);
    _biblioteca.devolverItemEmprestimo(testEmprestimo2, testBook1);

    _biblioteca.gravarDados();
    _biblioteca.lerDados();
}

int main()
{
    try
    {

        biblioteca testBiblioteca;
        testAdicionarUsuario(testBiblioteca);
        testAdicionarPublicacao(testBiblioteca);
        testAdicionarEmprestimo(testBiblioteca);
        testAdicionarItemAoEmprestimo(testBiblioteca);
        testRemoverUsuario(testBiblioteca);
        testRemoverPublicacao(testBiblioteca);
        testRemoverEmprestimo(testBiblioteca);
        testBuscarPeloTitulo(testBiblioteca);
        testBuscarPeloAutor(testBiblioteca);
        testGravarDados(testBiblioteca);

        std::cout << "Todos os testes passaram" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}