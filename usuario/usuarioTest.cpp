#include "usuario.hpp"
#include "../utils/Date.hpp"

void testGetName(usuario _usuario)
{
    if (_usuario.getNome() != "testName")
        throw std::runtime_error("The name of the user was not created correctly");
};

void testGetCpf(usuario _usuario)
{
    if (_usuario.getCpf() != "99999999999")
        throw std::runtime_error("The cpf of the user was not created correctly");
};

void testGetEndereco(usuario _usuario)
{
    if (_usuario.getEndereco() != "rua test")
        throw std::runtime_error("The endereco of the user was not created correctly");
};

void testGetFone(usuario _usuario)
{
    if (_usuario.getFone() != "24999999999")
        throw std::runtime_error("The fone of the user was not created correctly");
};

int main()
{
    usuario testUser("testName", "99999999999", "rua test", "24999999999");
    Date testDate;

    try
    {
        testGetName(testUser);
        testGetCpf(testUser);
        testGetEndereco(testUser);
        testGetFone(testUser);

        std::cout << "Todos os testes passaram" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
};