#include "emprestimo.hpp"
#include "../usuario/usuario.hpp"
#include "../utils/date.hpp"

int emprestimo::proxNum = 0;

void testCreation(emprestimo _emprestimo)
{
    if (_emprestimo.getNumber() != 1)
        throw std::runtime_error("The number of the first emprestimo should be 1");

    if (_emprestimo.getUser().getNome() != "testName")
        throw std::runtime_error("The user was not created correctly");
}

int main()
{
    usuario testUser("testName", "99999999999", "rua test", "24999999999");
    date testDate;
    emprestimo testEmprestimo(testDate, testUser);

    try
    {
        testCreation(testEmprestimo);

        std::cout << "Todos os testes passaram" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}