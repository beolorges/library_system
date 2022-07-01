#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "../utils/Date.hpp"
#include <iostream>
#include <map>
using namespace std;

class usuario
{
private:
    string nome;
    string cpf;
    string endereco;
    string fone;
    Date dataPenalizacao;

public:
    usuario() : dataPenalizacao(){};
    usuario(const string _nome, const string _cpf, const string _endereco, const string _fone) : nome(_nome), cpf(_cpf), endereco(_endereco), fone(_fone), dataPenalizacao(){};
    ~usuario(){};

    string getNome() const { return this->nome; };
    string getCpf() const { return this->cpf; };
    string getEndereco() const { return this->endereco; };
    string getFone() const { return this->fone; };

    void setDados(map<string, string> dados);

    void setNome(const string _nome) { this->nome = _nome; };
    void setCpf(const string _cpf) { this->cpf = _cpf; };
    void setEndereco(const string _endereco) { this->endereco = _endereco; };
    void setFone(const string _fone) { this->fone = _fone; };

    Date getDataPenalizacao() const { return this->dataPenalizacao; };
    void setDataPenalizacao(const Date _dataPenalizacao) { this->dataPenalizacao = _dataPenalizacao; };
};

/**
 * @brief Seta todos os dados de um usuário
 *
 * @param _nome
 * @param _cpf
 * @param _endereco
 * @param _fone
 */

void usuario::setDados(map<string, string> dados)
{
    this->setNome(dados["Nome"]);
    this->setCpf(dados["CPF"]);
    this->setFone(dados["Telefone"]);
    this->setEndereco(dados["Endereço"]);
};

#endif