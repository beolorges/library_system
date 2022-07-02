#include "interface.hpp"

// int emprestimo::proxNum = 0;

void interface::apresentarMenu()
{
    cout << "1 - Cadastrar usuario" << endl;
    cout << "2 - Cadastrar livro" << endl;
    cout << "3 - Cadastrar periodico" << endl;
    cout << "4 - Cadastrar emprestimo" << endl;
    cout << "5 - Adicionar item a um emprestimo" << endl;
    cout << "6 - Remover item de um emprestimo" << endl;
    cout << "7 - Devolver todos itens de um emprestimo" << endl;
    cout << "8 - Devolver item de um emprestimo" << endl;
    cout << "9 - Pesquisar publicações por título" << endl;
    cout << "10 - Pesquisar livros por autor" << endl;
    cout << "11 - Listar todas as publicacoes" << endl;
    cout << "12 - Listar todos os emprestimos" << endl;
    cout << "13 - Remover emprestimo" << endl;
    cout << "14 - Remover livro" << endl;
    cout << "15 - Remover periodico" << endl;
    cout << "16 - Remover usuario" << endl;
    cout << "17 - Sair" << endl;
}

void interface::cadastrarUsuario()
{
    string nome, cpf, telefone, email;
    cout << "Insira os dados do usuário:" << endl;
    cout << "Nome: ";
    getline(cin, nome);
    cout << "CPF: ";
    getline(cin, cpf);
    cout << "Telefone: ";
    getline(cin, telefone);
    cout << "Email: ";
    getline(cin, email);
    usuario *u = new usuario(nome, cpf, telefone, email);
    minhaBiblioteca.adicionarUsuario(u);
}

void interface::removerUsuario()
{
    string cpf;
    cout << "Insira o CPF do usuário a ser removido: ";
    getline(cin, cpf);
    minhaBiblioteca.removerUsuario(minhaBiblioteca.getUsuarioPeloCpf(cpf));
}

void interface::cadastrarLivro()
{
    string titulo, autores, editora;
    int codigoPublicacao, ano, qtdExemplares;
    cout << "Insira os dados do livro:" << endl;
    cout << "Titulo: ";
    getline(cin, titulo);
    cout << "Autores: ";
    getline(cin, autores);
    cout << "Editora: ";
    getline(cin, editora);
    cout << "Código Publicação: ";
    cin >> codigoPublicacao;
    cout << "Ano: ";
    cin >> ano;
    cout << "Quantidade de exemplares: ";
    cin >> qtdExemplares;

    livro *l = new livro(codigoPublicacao, titulo, editora, ano, autores, qtdExemplares);
    minhaBiblioteca.adicionarPublicacao(l);
}

void interface::cadastrarPeriodico()
{
    string titulo, editora, mes;
    int codigoPublicacao, numEdicao, ano;

    cout << "Insira os dados do periodico:" << endl;
    cout << "Titulo: ";
    getline(cin, titulo);
    cout << "Editora: ";
    getline(cin, editora);
    cout << "Mes: ";
    getline(cin, mes);
    cout << "Ano: ";
    cin >> ano;
    cout << "Numero de edição: ";
    cin >> numEdicao;
    cout << "Código Publicação: ";
    cin >> codigoPublicacao;

    periodico *p = new periodico(codigoPublicacao, titulo, editora, ano, mes, numEdicao);
    minhaBiblioteca.adicionarPublicacao(p);
}

void interface::removerLivro()
{
    int codigoPublicacao;
    cout << "Insira o código do livro a ser removido: ";
    cin >> codigoPublicacao;
    minhaBiblioteca.removerPublicacao(minhaBiblioteca.getPublicacaoPeloCodigo(codigoPublicacao));
}

void interface::removerPeriodico()
{
    int codigoPublicacao;
    cout << "Insira o código do periodico a ser removido: ";
    cin >> codigoPublicacao;
    minhaBiblioteca.removerPublicacao(minhaBiblioteca.getPublicacaoPeloCodigo(codigoPublicacao));
}

void interface::cadastrarEmprestimo()
{
    string cpf;
    cout << "Insira o CPF do usuário: ";
    getline(cin, cpf);
    usuario *u = minhaBiblioteca.getUsuarioPeloCpf(cpf);

    string data;
    cout << "Insira a data do emprestimo: ";
    getline(cin, data);
    Date d = Date(data);

    emprestimo *e = new emprestimo(d, u);
    minhaBiblioteca.adicionarEmprestimo(e);

    cout << "Emprestimo criado! Número do emprestimo é: " << e->getNumero() << endl;
    this->adicionarItem(e);
}

void interface::removerEmprestimo()
{
    int numero;
    cout << "Insira o número do emprestimo a ser removido: ";
    cin >> numero;
    minhaBiblioteca.excluirEmprestimo(minhaBiblioteca.getEmprestimoPeloCodigo(numero));

    cout << "Emprestimo número " << numero << " excluido com sucesso!" << endl;
}

void interface::adicionarItemAoEmprestimo()
{
    int numero;
    cout << "Insira o número do emprestimo: ";
    cin >> numero;
    emprestimo *e = minhaBiblioteca.getEmprestimoPeloCodigo(numero);

    this->adicionarItem(e);
}

void interface::removerItemDoEmprestimo()
{
    int numero;
    cout << "Insira o número do emprestimo: ";
    cin >> numero;
    emprestimo *e = minhaBiblioteca.getEmprestimoPeloCodigo(numero);

    this->removerItem(e);
}

void interface::devolverItemDoEmprestimo()
{
    int numero;
    cout << "Insira o número do emprestimo: ";
    cin >> numero;
    emprestimo *e = minhaBiblioteca.getEmprestimoPeloCodigo(numero);

    this->devolverItem(e);
}

void interface::devolverTodosItensDoEmprestimo()
{
    int numero;
    cout << "Insira o número do emprestimo: ";
    cin >> numero;
    emprestimo *e = minhaBiblioteca.getEmprestimoPeloCodigo(numero);

    e->devolverTodos();
    cout << "Todos os livros foram devolvidos com sucesso!" << endl;
}

void interface::devolverItem(emprestimo *e)
{
    cout << "Insira o código do livro a ser removido no emprestimo ou -1 para sair: ";
    int codigo;
    while (cin >> codigo)
    {
        if (codigo == -1)
            break;

        publicacao *p = minhaBiblioteca.getPublicacaoPeloCodigo(codigo);
        e->devolverLivro(dynamic_cast<livro *>(p));
        cout << p->getTitulo() << " devolvido com sucesso!" << endl;
        cout << "Insira o código do livro a ser removido no emprestimo ou -1 para sair: ";
    }
}

void interface::removerItem(emprestimo *e)
{
    cout << "Insira o código do livro a ser removido no emprestimo ou -1 para sair: ";
    int codigoPublicacao = 0;

    while (cin >> codigoPublicacao)
    {
        if (codigoPublicacao == -1)
            break;

        publicacao *p = minhaBiblioteca.getPublicacaoPeloCodigo(codigoPublicacao);
        e->excluirLivro(dynamic_cast<livro *>(p));
        cout << p->getTitulo() << " excluido com sucesso!" << endl;
        cout << "Insira o código do livro a ser removido no emprestimo ou -1 para sair: ";
    }
}

void interface::adicionarItem(emprestimo *e)
{
    cout << "Insira o código do livro a ser inserido no emprestimo ou -1 para sair: ";
    int codigoLivro = 0;
    while (cin >> codigoLivro)
    {
        if (codigoLivro == -1)
            break;

        publicacao *p = minhaBiblioteca.getPublicacaoPeloCodigo(codigoLivro);
        e->adicionarLivro(dynamic_cast<livro *>(p));

        cout << p->getTitulo() << " adicionado com sucesso!" << endl;
        cout << "Insira o código do livro a ser inserido no emprestimo ou -1 para sair: ";
    };
}

void interface::listarPublicacaoPorTitulo()
{
    string titulo;
    cout << "Insira o titulo da publicacao: ";
    getline(cin, titulo);
    vector<publicacao *> publicacoesPesquisadas = minhaBiblioteca.buscarPublicacaoPeloTitulo(titulo);

    cout << "Publicações: " << endl;
    for (auto p : publicacoesPesquisadas)
    {
        if (typeid(*p) == typeid(livro))
        {
            cout << "\tLivro:" << endl;
            cout << "\t\tTítulo: " << dynamic_cast<livro *>(p)->getTitulo() << endl;
            cout << "\t\tAutor: " << dynamic_cast<livro *>(p)->getAutores() << endl;
            cout << "\t\tEditora: " << dynamic_cast<livro *>(p)->getEditora() << endl;
            cout << "\t\tAno: " << dynamic_cast<livro *>(p)->getAno() << endl;
            cout << "\t\tCódigo: " << dynamic_cast<livro *>(p)->getCodPublicacao() << endl;
            cout << "\t\tQuantidade: " << dynamic_cast<livro *>(p)->getQtdExemplares() << endl;
            cout << "\t\t--------------------------------------------------------------" << endl;
        }
        else if (typeid(*p) == typeid(periodico))
        {
            cout << "\tPeriódico:" << endl;
            cout << "\t\tTítulo: " << dynamic_cast<periodico *>(p)->getTitulo() << endl;
            cout << "\t\tMês: " << dynamic_cast<periodico *>(p)->getMes() << endl;
            cout << "\t\tAno: " << dynamic_cast<periodico *>(p)->getAno() << endl;
            cout << "\t\tEditora: " << dynamic_cast<periodico *>(p)->getEditora() << endl;
            cout << "\t\tCódigo: " << dynamic_cast<periodico *>(p)->getCodPublicacao() << endl;
            cout << "\t\tNúmero Edição: " << dynamic_cast<periodico *>(p)->getNumEdicao() << endl;
            cout << "\t\t--------------------------------------------------------------" << endl;
        }
    }
}

void interface::listarLivroPorAutor()
{
    string autor;
    cout << "Insira o autor do livro: ";
    getline(cin, autor);
    vector<livro *> publicacoesPesquisadas = minhaBiblioteca.buscarLivroPeloAutor(autor);

    cout << "Livros:" << endl;
    for (auto p : publicacoesPesquisadas)
    {
        cout << "\tTítulo: " << p->getTitulo() << endl;
        cout << "\tAutor: " << p->getAutores() << endl;
        cout << "\tEditora: " << p->getEditora() << endl;
        cout << "\tAno: " << p->getAno() << endl;
        cout << "\tCódigo: " << p->getCodPublicacao() << endl;
        cout << "\tQuantidade: " << p->getQtdExemplares() << endl;
        cout << "\t--------------------------------------------------------------" << endl;
    }
}

void interface::listarPublicacoes()
{
    vector<publicacao *> publicacoes = minhaBiblioteca.getPublicacoes();

    cout << "Publicações: " << endl;
    for (auto p : publicacoes)
    {
        if (typeid(*p) == typeid(livro))
        {
            cout << "\tLivro:" << endl;
            cout << "\t\tTítulo: " << dynamic_cast<livro *>(p)->getTitulo() << endl;
            cout << "\t\tAutor: " << dynamic_cast<livro *>(p)->getAutores() << endl;
            cout << "\t\tEditora: " << dynamic_cast<livro *>(p)->getEditora() << endl;
            cout << "\t\tAno: " << dynamic_cast<livro *>(p)->getAno() << endl;
            cout << "\t\tCódigo: " << dynamic_cast<livro *>(p)->getCodPublicacao() << endl;
            cout << "\t\tQuantidade: " << dynamic_cast<livro *>(p)->getQtdExemplares() << endl;
            cout << "\t\t--------------------------------------------------------------" << endl;
        }
        else if (typeid(*p) == typeid(periodico))
        {
            cout << "\tPeriódico:" << endl;
            cout << "\t\tTítulo: " << dynamic_cast<periodico *>(p)->getTitulo() << endl;
            cout << "\t\tMês: " << dynamic_cast<periodico *>(p)->getMes() << endl;
            cout << "\t\tAno: " << dynamic_cast<periodico *>(p)->getAno() << endl;
            cout << "\t\tEditora: " << dynamic_cast<periodico *>(p)->getEditora() << endl;
            cout << "\t\tCódigo: " << dynamic_cast<periodico *>(p)->getCodPublicacao() << endl;
            cout << "\t\tNúmero Edição: " << dynamic_cast<periodico *>(p)->getNumEdicao() << endl;
            cout << "\t\t--------------------------------------------------------------" << endl;
        }
    }
}

void interface::listarEmprestimos()
{
    vector<emprestimo *> emprestimos = minhaBiblioteca.getEmprestimos();

    for (auto e : emprestimos)
    {
        cout << "Emprestimo:" << endl;
        cout << "\tCódigo: " << e->getNumero() << endl;
        cout << "\tData de Empréstimo: " << e->getDataEmprestimo() << endl;
        cout << "\tData prevista de Devolução: " << e->getDataPrevDevolucao() << endl;
        cout << "\tUsuário: " << e->getUsuario()->getNome() << endl;
        cout << "\tLivros:" << endl;
        for (auto l : e->getItens())
        {
            cout << "\t\tTítulo: " << l.getItem().getTitulo() << endl;
            cout << "\t\tAutor: " << l.getItem().getAutores() << endl;
            cout << "\t\tEditora: " << l.getItem().getEditora() << endl;
            cout << "\t\tAno: " << l.getItem().getAno() << endl;
            cout << "\t\tCódigo: " << l.getItem().getCodPublicacao() << endl;
            cout << "\t\tData Devolução" << e->getDataDevolucao(l.getPonteiroParaItem()) << endl;
            cout << "\t\t--------------------------------------------------------------" << endl;
        }
    }
}

void interface::main()
{
    int opcao;
    do
    {
        cout << "Bem-vindo ao sistema de biblioteca!" << endl;
        this->apresentarMenu();
        cout << "Digite a opção desejada: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            cadastrarUsuario();
            break;
        case 2:
            cadastrarLivro();
            break;
        case 3:
            cadastrarPeriodico();
            break;
        case 4:
            cadastrarEmprestimo();
            break;
        case 5:
            adicionarItemAoEmprestimo();
            break;
        case 6:
            removerItemDoEmprestimo();
            break;
        case 7:
            devolverTodosItensDoEmprestimo();
            break;
        case 8:
            devolverItemDoEmprestimo();
            break;
        case 9:
            listarPublicacaoPorTitulo();
            break;

        case 10:
            listarLivroPorAutor();
            break;

        case 11:
            listarPublicacoes();
            break;

        case 12:
            listarEmprestimos();
            break;

        case 13:
            removerEmprestimo();
            break;

        case 14:
            removerLivro();
            break;

        case 15:
            removerPeriodico();
            break;

        case 16:
            removerUsuario();
            break;

        case 17:
            break;
        default:
            cout << "Opção inválida!" << endl;
            break;
        }
    } while (opcao != 10);
}