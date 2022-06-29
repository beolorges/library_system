#include "periodico.hpp"
#include <cstring>

void testGetTitulo(periodico _periodico)
{
    if (_periodico.getTitulo() != "testTitle")
        throw std::runtime_error("The title was not created correctly");
}

void testGetEditora(periodico _periodico)
{
    if (_periodico.getEditora() != "testEditora")
        throw std::runtime_error("The editora was not created correctly");
}

void testGetAno(periodico _periodico)
{
    if (_periodico.getAno() != 2222)
        throw std::runtime_error("The year was not created correctly");
}

void testGetMes(periodico _periodico)
{
    if (_periodico.getMes() != "testMonth")
        throw std::runtime_error("The month was not created correctly");
}

void testGetNumEdicao(periodico _periodico)
{
    if (_periodico.getNumEdicao() != 1)
        throw std::runtime_error("The number of edition was not created correctly");
}

int main()
{
    try
    {
        periodico periodicoTest(10, "testTitle", "testEditora", 2222, "testMonth", 1);
        testGetTitulo(periodicoTest);
        testGetEditora(periodicoTest);
        testGetAno(periodicoTest);
        testGetMes(periodicoTest);
        testGetNumEdicao(periodicoTest);

        std::cout << "Todos os testes passaram" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}