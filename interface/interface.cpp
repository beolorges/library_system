#include "interface.hpp"

void Interface::menuPrint() const
{
    cout << "1 - Cadastrar usuário" << endl;
    cout << "2 - Cadastrar livro" << endl;
    cout << "3 - Cadastrar periódico" << endl;
    cout << "4 - Cadastrar empréstimo" << endl;
    cout << "5 - Entrar em um empréstimo" << endl;
    cout << "6 - Pesquisar publicações por título" << endl;
    cout << "7 - Pesquisar livros por autor" << endl;
    cout << "8 - Listar todas as publicações" << endl;
    cout << "9 - Listar todos os empréstimos" << endl;
    cout << "10 - Remover empréstimo" << endl;
    cout << "11 - Remover livro" << endl;
    cout << "12 - Remover periódico" << endl;
    cout << "13 - Remover usuário" << endl;
    cout << "14 - Sair" << endl;
}

void Interface::userRegistration()
{
    string name;
    string cpf;
    string address;
    string phone;

    cout << "Nome: ";
    getline(cin, name);
    cout << "CPF: ";
    getline(cin, cpf);
    cout << "Endereço: ";
    getline(cin, address);
    cout << "Telefone: ";
    getline(cin, phone);

    myLibrary.userRegistration(new User(name, cpf, address, phone));
    cout << "Usuário cadastrado com sucesso!" << endl;
    cout << "Bem vindo ao sistema de biblioteca, " << name << "!" << endl;
}

void Interface::userExclude()
{
    string cpf;

    cout << "Insira o CPF do usuário: ";
    getline(cin, cpf);

    myLibrary.userExclude(myLibrary.getUser(cpf));
    cout << "Usuário excluído com sucesso!" << endl;
}

/**
 * @brief Coleta os dados gerais de uma publicação e retorna um map com os dados
 *
 * @return map<string, string>
 */

map<string, string> Interface::publicationRegistration()
{
    map<string, string> publicationData;
    string publicationCode;
    string title;
    string publisher;
    string year;

    cout << "Código de publicação: ";
    getline(cin, publicationCode);
    cout << "Título: ";
    getline(cin, title);
    cout << "Editora: ";
    getline(cin, publisher);
    cout << "Ano: ";
    getline(cin, year);

    publicationData["publicationCode"] = publicationCode;
    publicationData["title"] = title;
    publicationData["publisher"] = publisher;
    publicationData["year"] = year;

    return publicationData;
}

void Interface::bookRegistration()
{
    map<string, string> publicationData = publicationRegistration();
    string author;
    int quantity;

    cout << "Autor: ";
    getline(cin, author);
    cout << "Quantidade: ";
    if (!(cin >> quantity))
        throw runtime_error("Carácter inválido");

    myLibrary.publicationRegistration(new Book(publicationData, author, quantity));
    cout << publicationData["title"] << " cadastrado com sucesso!" << endl;
}

void Interface::bookExclude()
{
    int publicationCode;

    cout << "Insira o código de publicação do livro a ser excluído: ";
    if (!(cin >> publicationCode))
        throw runtime_error("Carácter inválido");

    myLibrary.publicationExclude(myLibrary.getBook(publicationCode));
    cout << "Livro excluído com sucesso!" << endl;
}

void Interface::periodicalRegistration()
{
    map<string, string> publicationData = publicationRegistration();
    string month;
    int editionNumber;

    cout << "Mês: ";
    getline(cin, month);
    cout << "Número da Edição: ";
    if (!(cin >> editionNumber))
        throw runtime_error("Carácter inválido");

    myLibrary.publicationRegistration(new Periodical(publicationData, month, editionNumber));
    cout << publicationData["title"] << " cadastrado com sucesso!" << endl;
}

void Interface::periodicalExclude()
{
    int publicationCode;

    cout << "Insira o código de publicação do periódico a ser excluído: ";
    if (!(cin >> publicationCode))
        throw runtime_error("Carácter inválido");

    myLibrary.publicationExclude(myLibrary.getPeriodical(publicationCode));
    cout << "Periódico excluído com sucesso!" << endl;
}

map<int, map<string, string>> Interface::publicationSearchByTitle() const
{
    string title;

    cout << "Insira o título a ser pesquisado: ";
    getline(cin, title);

    return myLibrary.publicationSearchByTitle(title);
}

map<int, map<string, string>> Interface::publicationSearchByAuthor() const
{
    string author;

    cout << "Insira o autor a ser pesquisado: ";
    getline(cin, author);

    return myLibrary.publicationSearchByAuthor(author);
}

map<int, map<string, string>> Interface::publicationSearchAll() const
{
    return myLibrary.publicationList();
}

void Interface::publicationPrint(map<int, map<string, string>> publicationData) const
{
    map<int, map<string, string>>::iterator it = publicationData.begin();
    while (it != publicationData.end())
    {
        cout << "Código de publicação: " << publicationData[it->first]["publicationCode"] << endl;
        cout << "Título: " << publicationData[it->first]["title"] << endl;
        cout << "Editora: " << publicationData[it->first]["publisher"] << endl;
        cout << "Ano: " << publicationData[it->first]["year"] << endl;

        if (publicationData[it->first]["type"] == "Book")
        {
            cout << "Autor: " << publicationData[it->first]["author"] << endl;
            cout << "Quantidade de cópias: " << publicationData[it->first]["numberOfCopies"] << endl;
        }
        else
        {
            cout << "Mês: " << publicationData[it->first]["month"] << endl;
            cout << "Número da Edição: " << publicationData[it->first]["numberOfEdition"] << endl;
        }

        it++;
    }
}

Loan *Interface::loanRegistration()
{
    string userCPF;
    string date;

    cout << "CPF do usuário: ";
    getline(cin, userCPF);

    cout << "Data prevista de devolução: ";
    getline(cin, date);

    Loan *loan = new Loan(myLibrary.getUser(userCPF), date);
    int loanNumber = myLibrary.loanRegistration(loan);
    cout << "Emprestimo número: " << loanNumber << endl;

    return loan;
}

Loan *Interface::loanByLoanNumber()
{
    int loanNumber;

    cout << "Insira o número do empréstimo: ";
    if (!(cin >> loanNumber))
        throw runtime_error("Carácter inválido");

    Loan *thisLoan = myLibrary.getLoan(loanNumber);

    return thisLoan;
}

void Interface::loanOptions(Loan *thisLoan)
{
    if (thisLoan == nullptr)
        throw runtime_error("Empréstimo não encontrado");

    int option;
    do
    {
        try
        {
            this->loanMenuPrint();
            if (cin >> option)
            {
                switch (option)
                {
                case 1:
                    this->loanAddBook(thisLoan);
                    break;

                case 2:
                    this->loanExcludeBook(thisLoan);
                    break;

                case 3:
                    this->loanReturnBook(thisLoan);
                    break;

                case 4:
                    this->loanReturnAll(thisLoan);
                    break;

                case 5:
                    break;

                default:
                    cout << "Digite uma opção válida!" << endl;
                    break;
                }
            }
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                throw runtime_error("Carácter inválido");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

    } while (option != 5);
}

void Interface::loanMenuPrint()
{
    cout << "1 - Adicionar livro ao empréstimo" << endl;
    cout << "2 - Remover livro do empréstimo" << endl;
    cout << "3 - Devolver livro do empréstimo" << endl;
    cout << "4 - Devolver todos os livros do empréstimo" << endl;
    cout << "5 - Voltar ao menu principal" << endl;
}

void Interface::loanAddBook(Loan *thisLoan)
{
    int publicationCode;

    cout << "Insira o código de publicação do livro: ";
    if (!(cin >> publicationCode))
        throw runtime_error("Carácter inválido");

    string name = myLibrary.loanAddBook(thisLoan, new LoanItem(myLibrary.getBook(publicationCode)));

    cout << name << " adicionado ao empréstimo!" << endl;
}

void Interface::loanExcludeBook(Loan *thisLoan)
{
    int publicationCode;

    cout << "Insira o código de publicação do livro: ";
    if (!(cin >> publicationCode))
        throw runtime_error("Carácter inválido");

    string name = myLibrary.loanExcludeBook(thisLoan, new LoanItem(myLibrary.getBook(publicationCode)));

    cout << name << " removido do empréstimo!" << endl;
}

void Interface::loanReturnBook(Loan *thisLoan)
{
    int publicationCode;

    cout << "Insira o código de publicação do livro: ";
    if (!(cin >> publicationCode))
        throw runtime_error("Carácter inválido");

    string name = myLibrary.loanReturnBook(thisLoan, new LoanItem(myLibrary.getBook(publicationCode)));

    cout << name << " devolvido com sucesso!" << endl;
}

void Interface::loanReturnAll(Loan *thisLoan)
{
    int loanNumber = myLibrary.loanReturnAll(thisLoan);
    cout << "Empréstimo número " << loanNumber << " devolvido com sucesso!" << endl;
}

void Interface::loanExclude(Loan *thisLoan)
{
    int loanNumber = myLibrary.loanExclude(thisLoan);
    cout << "Empréstimo número " << loanNumber << " excluído com sucesso!" << endl;
}

void Interface::loanPrint() const
{
    pair<vector<map<string, string>>, map<int, vector<map<string, string>>>> loanData = myLibrary.loanList();

    for (map<string, string> loan : loanData.first)
    {
        cout << "Número do empréstimo: " << loan["number"] << endl;
        cout << "Nome do usuário: " << loan["userName"] << endl;
        cout << "CPF do usuário: " << loan["userCpf"] << endl;
        cout << "Data de Emprestimo: " << loan["loanDate"] << endl;
        cout << "Data prevista de devolução: " << loan["expectReturnDate"] << endl;
        cout << "Livros do empréstimo:" << endl;

        for (map<string, string> book : loanData.second[stoi(loan["number"])])
        {
            cout << "Código: " << book["code"] << endl;
            cout << "Título: " << book["title"] << endl;
            cout << "Autor: " << book["author"] << endl;
            cout << "Editora: " << book["publisher"] << endl;
            cout << "Ano: " << book["year"] << endl;
        }
    }
}

void Interface::main()
{
    int option;
    do
    {
        try
        {
            this->menuPrint();
            if (cin >> option)
            {
                cin.ignore();
                switch (option)
                {
                case 1:
                    userRegistration();
                    break;

                case 2:
                    bookRegistration();
                    break;

                case 3:
                    periodicalRegistration();
                    break;

                case 4:
                    loanOptions(loanRegistration());
                    break;

                case 5:
                    loanOptions(loanByLoanNumber());
                    break;

                case 6:
                    publicationPrint(publicationSearchByTitle());
                    break;

                case 7:
                    publicationPrint(publicationSearchByAuthor());
                    break;

                case 8:
                    publicationPrint(publicationSearchAll());
                    break;

                case 9:
                    loanPrint();
                    break;

                case 10:
                    loanExclude(loanByLoanNumber());
                    break;

                case 11:
                    bookExclude();
                    break;

                case 12:
                    periodicalExclude();
                    break;

                case 13:
                    userExclude();
                    break;

                case 14:
                    break;

                default:
                    cout << "Opção inválida!" << endl;
                    break;
                }
            }
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                throw runtime_error("Carácter inválido");
            }
        }
        catch (const std::exception &e)
        {
            if (e.what() == "stoi")
                cout << "Digite um número válido para o código de publicação e ano!" << endl;
            else
                std::cerr << e.what() << '\n';
        }
    } while (option != 14);
}