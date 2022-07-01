#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "../usuario/usuario.hpp"
#include "../publicacao/livro.hpp"
#include "../publicacao/periodico.hpp"
#include "../emprestimo/emprestimo.hpp"
#include "../emprestimo/itemEmprestimo.hpp"

/**
 * @brief Classe que representa uma biblioteca.
 */

class biblioteca
{
private:
    vector<usuario *> usuarios;
    vector<publicacao *> publicacoes;
    vector<emprestimo *> emprestimos;
    usuario *getUsuarioPeloCpf(const string) const;

public:
    biblioteca(){};
    ~biblioteca(){};

    inline void adicionarUsuario(usuario *_usuario) { this->usuarios.push_back(_usuario); };
    inline void adicionarPublicacao(publicacao *_publicacao) { this->publicacoes.push_back(_publicacao); };
    inline void adicionarEmprestimo(emprestimo *_emprestimo) { this->emprestimos.push_back(_emprestimo); };
    inline void adicionarItemAoEmprestimo(emprestimo *_emprestimo, livro *_livro) { _emprestimo->adicionarLivro(_livro); };
    void removerUsuario(usuario *_usuario);
    void removerPublicacao(publicacao *_publicacao);
    inline void removerItemDoEmprestimo(emprestimo *_emprestimo, livro *_livro) { _emprestimo->excluirLivro(_livro); };

    inline void excluirEmprestimo(emprestimo *_emprestimo) { this->emprestimos.erase(find(this->emprestimos.begin(), this->emprestimos.end(), _emprestimo)); };
    inline void devolverItemEmprestimo(emprestimo *_emprestimo, livro *_livro) { _emprestimo->devolverLivro(_livro); };
    inline void devolverEmprestimo(emprestimo *_emprestimo) { _emprestimo->devolverTodos(); };

    vector<publicacao *> buscarPublicacaoPeloTitulo(string);
    vector<livro *> buscarLivroPeloAutor(string);

    inline vector<usuario *> getUsuarios() { return this->usuarios; };
    inline vector<publicacao *> getPublicacoes() { return this->publicacoes; };
    inline vector<emprestimo *> getEmprestimos() { return this->emprestimos; };
    bool existeEmprestimoParaUsuario(usuario *_usuario);
    bool existeEmprestimoParaLivro(livro *_livro);

    void gravarDados();
    void lerDados();
};

void biblioteca::removerPublicacao(publicacao *_publicacao)
{
    if (typeid(*_publicacao).hash_code() == typeid(livro).hash_code())
        if (existeEmprestimoParaLivro((livro *)_publicacao))
            throw "Não é possível excluir um livro que possui emprestimos.";

    publicacoes.erase(find(publicacoes.begin(), publicacoes.end(), _publicacao));
}

bool biblioteca::existeEmprestimoParaUsuario(usuario *_usuario)
{
    for (auto &emprestimo : emprestimos)
    {
        if (emprestimo->getUsuario() == _usuario)
            return true;
    }
    return false;
}

bool biblioteca::existeEmprestimoParaLivro(livro *livro)
{
    for (auto &emprestimo : emprestimos)
    {
        for (auto &item : emprestimo->getItens())
            if (item.getPonteiroParaItem() == livro)
                return true;
    }
    return false;
}

void biblioteca::removerUsuario(usuario *_usuario)
{
    if (existeEmprestimoParaUsuario(_usuario))
        throw runtime_error("Não é possível excluir um usuário com empréstimos.");

    usuarios.erase(find(usuarios.begin(), usuarios.end(), _usuario));
}

/**
 * @brief Busca publicações que contenham o termo passado por parâmetro no título
 *
 * @param _titulo
 * @return vector<publicacao *>
 */
vector<publicacao *> biblioteca::buscarPublicacaoPeloTitulo(string _titulo)
{
    vector<publicacao *> publicacoesComTituloPesquisado;
    vector<publicacao *>::iterator it = this->publicacoes.begin();
    while (it != this->publicacoes.end())
    {
        if ((*it)->getTitulo().find(_titulo) != std::string::npos)
            publicacoesComTituloPesquisado.push_back(*it);

        it++;
    }

    if (publicacoesComTituloPesquisado.size() == 0)
        throw runtime_error("Não existem livros com o título pesquisado");

    return publicacoesComTituloPesquisado;
}

/**
 * @brief Busca livros que contenham o termo passado por parâmetro no autor
 *
 * @param _autor
 * @return vector<livro *>
 */

vector<livro *> biblioteca::buscarLivroPeloAutor(string _autor)
{

    vector<livro *> vectorLivros;
    vector<livro *> livrosComAutorPesquisado;
    vector<publicacao *>::iterator it = this->publicacoes.begin();

    while (it != this->publicacoes.end())
    {
        if (typeid(**it).hash_code() != typeid(periodico).hash_code())
            vectorLivros.push_back(dynamic_cast<livro *>(*it));

        it++;
    }

    vector<livro *>::iterator itLivro = vectorLivros.begin();

    while (itLivro != vectorLivros.end())
    {
        if ((*itLivro)->getAutores().find(_autor) != std::string::npos)
            livrosComAutorPesquisado.push_back(*itLivro);

        itLivro++;
    }

    if (livrosComAutorPesquisado.size() == 0)
        throw runtime_error("Não existem livros com o autor pesquisado");

    return livrosComAutorPesquisado;
}

usuario *biblioteca::getUsuarioPeloCpf(const string _cpf) const
{
    vector<usuario *>::const_iterator it = this->usuarios.begin();
    while (it != this->usuarios.end())
    {
        if ((*it)->getCpf() == _cpf)
            return *it;
        it++;
    }
    throw runtime_error("Usuário não encontrado");
}

/**
 * @brief Grava todos os dados atuais da biblioteca em um arquivo txt
 *
 *
 */

void biblioteca::gravarDados()
{
    ofstream arquivo;
    arquivo.open("biblioteca.txt");
    if (arquivo.is_open())
    {
        arquivo << "Usuários:" << endl;
        for (int i = 0; i < usuarios.size(); i++)
        {
            arquivo << "\tNome: " << usuarios[i]->getNome() << endl;
            arquivo << "\tCPF: " << usuarios[i]->getCpf() << endl;
            arquivo << "\tTelefone: " << usuarios[i]->getFone() << endl;
            arquivo << "\tEndereço: " << usuarios[i]->getEndereco() << endl;
            arquivo << "\tData penalização: " << usuarios[i]->getDataPenalizacao() << endl;
            arquivo << "\t----------------------------------------------------------------------------" << endl;
        }
        arquivo << "--------------------------------------------------------------------------------" << endl;
        arquivo << "\nPublicações:" << endl;
        for (int i = 0; i < publicacoes.size(); i++)
        {
            if (typeid(*publicacoes[i]).hash_code() == typeid(livro).hash_code())
            {
                arquivo << "\tLivro:" << endl;
                arquivo << "\t\tTitulo: " << dynamic_cast<livro *>(publicacoes[i])->getTitulo() << endl;
                arquivo << "\t\tAutor: " << dynamic_cast<livro *>(publicacoes[i])->getAutores() << endl;
                arquivo << "\t\tEditora: " << dynamic_cast<livro *>(publicacoes[i])->getEditora() << endl;
                arquivo << "\t\tAno: " << dynamic_cast<livro *>(publicacoes[i])->getAno() << endl;
                arquivo << "\t\tCódigo da Publicação: " << dynamic_cast<livro *>(publicacoes[i])->getCodPublicacao() << endl;
                arquivo << "\t\tQuantidade de exemplares disponíveis: " << dynamic_cast<livro *>(publicacoes[i])->getQtdExemplares() << endl;
                arquivo << "\t----------------------------------------------------------------------------" << endl;
            }
            else if (typeid(*publicacoes[i]).hash_code() == typeid(periodico).hash_code())
            {
                arquivo << "\tPeriódico:" << endl;
                arquivo << "\t\tTitulo: " << dynamic_cast<periodico *>(publicacoes[i])->getTitulo() << endl;
                arquivo << "\t\tEditora: " << dynamic_cast<periodico *>(publicacoes[i])->getEditora() << endl;
                arquivo << "\t\tAno: " << dynamic_cast<periodico *>(publicacoes[i])->getAno() << endl;
                arquivo << "\t\tMes: " << dynamic_cast<periodico *>(publicacoes[i])->getMes() << endl;
                arquivo << "\t\tNúmero da edição: " << dynamic_cast<periodico *>(publicacoes[i])->getNumEdicao() << endl;
                arquivo << "\t\tCódigo da Publicação: " << dynamic_cast<periodico *>(publicacoes[i])->getCodPublicacao() << endl;
                arquivo << "\t----------------------------------------------------------------------------" << endl;
            }
        }
        arquivo << "--------------------------------------------------------------------------------" << endl;
        arquivo << "\nEmpréstimos:" << endl;
        for (int i = 0; i < emprestimos.size(); i++)
        {
            arquivo << "\tUsuário: " << endl;
            arquivo << "\t\tCPF: " << emprestimos[i]->getUsuario()->getCpf() << endl;
            arquivo << "\t\tNome: " << emprestimos[i]->getUsuario()->getNome() << endl;
            arquivo << "\t\tTelefone: " << emprestimos[i]->getUsuario()->getFone() << endl;
            arquivo << "\t\tEndereço: " << emprestimos[i]->getUsuario()->getEndereco() << endl;
            arquivo << "\t\tData penalização: " << emprestimos[i]->getUsuario()->getDataPenalizacao() << endl;
            arquivo << "\t----------------------------------------------------------------------------" << endl
                    << endl;

            arquivo << "\tDados emprestimo: " << endl;
            arquivo << "\t\tNúmero do emprestimo: " << emprestimos[i]->getNumero() << endl;
            arquivo << "\t\tData de empréstimo: " << emprestimos[i]->getDataEmprestimo() << endl;
            arquivo << "\t\tData Prevista de devolução: " << emprestimos[i]->getDataPrevDevolucao() << endl;
            arquivo << "\t----------------------------------------------------------------------------" << endl
                    << endl;

            arquivo << "\tItens do emprestimo: " << endl;
            for (int j = 0; j < emprestimos[i]->getItens().size(); j++)
            {
                arquivo << "\t\tCódigo: " << emprestimos[i]->getItens()[j].getItem().getCodPublicacao();
                arquivo << "\t\tTítulo: " << emprestimos[i]->getItens()[j].getItem().getTitulo();
                if (emprestimos[i]->livroFoiDevolvido(emprestimos[i]->getItens()[j].getPonteiroParaItem()))
                    arquivo << "\t\tDevolução: " << emprestimos[i]->getDataDevolucao(emprestimos[i]->getItens()[j].getPonteiroParaItem()) << endl;

                else
                    arquivo << "\t\tDevolução: Não devolvido" << endl;
            }
            arquivo << "\t----------------------------------------------------------------------------" << endl;
        }
        arquivo << "--------------------------------------------------------------------------------" << endl;
    }
}

void biblioteca::lerDados()
{
    string primaryLine = "--------------------------------------------------------------------------------";
    string secondaryLine = "\t----------------------------------------------------------------------------";
    string delimiter = ":";

    ifstream arquivo;
    arquivo.open("biblioteca.txt");
    if (arquivo.is_open())
    {
        string linha;
        while (getline(arquivo, linha))
        {
            if (linha == "Usuários:")
            {
                while (getline(arquivo, linha))
                {
                    usuario *userData = new usuario();
                    map<string, string> dados;
                    if (linha == primaryLine)
                        break;

                    while (true)
                    {
                        if (linha == secondaryLine)
                            break;

                        string token = linha.substr(linha.find("\t") + 1, linha.find(delimiter) - 1);
                        string value = linha.substr(linha.find(delimiter) + 2, linha.find('\n'));

                        dados[token] = value;

                        getline(arquivo, linha);
                    }

                    userData->setDados(dados);
                    this->adicionarUsuario(userData);
                }
            }
            else if (linha == "Publicações:")
            {
                while (getline(arquivo, linha))
                {
                    map<string, string> dados;
                    if (linha == primaryLine)
                        break;

                    if (linha == "Livro:")
                    {
                        livro *livroData = new livro();
                        while (getline(arquivo, linha))
                        {
                            if (linha == secondaryLine)
                                break;

                            string token = linha.substr(linha.find("\t") + 1, linha.find(delimiter) - 1);
                            string value = linha.substr(linha.find(delimiter) + 2, linha.find('\n'));

                            dados[token] = value;
                        }
                        livroData->setDados(dados);
                        this->adicionarPublicacao(livroData);
                    }
                    else if (linha == "Periódico:")
                    {
                        periodico *periodicoData = new periodico();
                        while (getline(arquivo, linha))
                        {
                            if (linha == secondaryLine)
                                break;

                            string token = linha.substr(linha.find("\t") + 1, linha.find(delimiter) - 1);
                            string value = linha.substr(linha.find(delimiter) + 2, linha.find('\n'));

                            dados[token] = value;
                        }
                        periodicoData->setDados(dados);
                        this->adicionarPublicacao(periodicoData);
                    }
                }
            }
            else if (linha == "Empréstimos:")
            {
                while (getline(arquivo, linha))
                {
                    string cpfData;
                    Date dateData;

                    if (linha == "Usuário:")
                    {
                        while (getline(arquivo, linha))
                        {
                            if (linha == secondaryLine)
                                break;

                            string token = linha.substr(linha.find("\t") + 1, linha.find(delimiter) - 1);
                            string value = linha.substr(linha.find(delimiter) + 2, linha.find('\n'));

                            if (token == "CPF")
                                cpfData = value;
                        }
                    }

                    if (linha == "Dados emprestimo:")
                    {
                        while (getline(arquivo, linha))
                        {
                            if (linha == secondaryLine)
                                break;

                            string token = linha.substr(linha.find("\t") + 1, linha.find(delimiter) - 1);
                            string value = linha.substr(linha.find(delimiter) + 2, linha.find('\n'));

                            if (token == "Data Prevista de devolução")
                                dateData = Date(value);
                        }
                    }

                    usuario *userData = this->getUsuarioPeloCpf(cpfData);

                    emprestimo *empData = new emprestimo(dateData, userData);

                    if (linha == "Itens do emprestimo:")
                    {
                        while (getline(arquivo, linha))
                        {
                            if (linha == secondaryLine)
                                break;

                            /*IMPLEMENTAR AQUI*/
                        }
                    }
                }
            }
        }
    }
}
#endif