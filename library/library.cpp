#include "library.hpp"

int Loan::nextNumber = 0;

void Library::userRegistration(User *user)
{
    if (isThisCPFAlreadyRegistered(user->getCpf()))
        throw runtime_error("CPF já cadastrado");

    users.push_back(user);
}

void Library::userExclude(const User *user)
{
    if (thisUserHasLoan(user))
        throw runtime_error("O usuário possui emprestimos ativos");

    for (auto loan : loans)
    {
        if (loan->getUser() == user)
            loanExclude(loan);
    }

    for (int i = 0; i < users.size(); i++)
        if (users[i] == user)
        {
            users.erase(users.begin() + i);
            return;
        }
}

void Library::publicationExclude(Publication *publication)
{
    if (typeid(*publication).hash_code() == typeid(Book).hash_code())
        if (isThisBookLoaned(static_cast<Book *>(publication)))
            throw runtime_error("O livro possui empréstimos ativos");

    for (int i = 0; i < publications.size(); i++)
        if (publications[i] == publication)
        {
            publications.erase(publications.begin() + i);
            return;
        }
}

map<int, map<string, string>> Library::fillData(const vector<Publication *> publications) const
{
    map<int, map<string, string>> publicationsData;

    for (auto publication : publications)
    {
        for (auto data : publication->getData())
        {
            publicationsData[publication->getCode()][data.first] = data.second;
        }

        for (auto additionalData : publication->getAdditionalData())
        {
            publicationsData[publication->getCode()][additionalData.first] = additionalData.second;
        }
    }

    return publicationsData;
}

map<int, map<string, string>> Library::publicationList() const
{
    return fillData(getAllPublications());
}

map<int, map<string, string>> Library::publicationSearchByTitle(const string title) const
{
    vector<Publication *> publicationList = getPublicationByTitle(title);

    map<int, map<string, string>> publicationsData = fillData(publicationList);

    return publicationsData;
}

map<int, map<string, string>> Library::publicationSearchByAuthor(const string author) const
{
    vector<Publication *> bookList = getBookByAuthor(author);

    map<int, map<string, string>> publicationsData = fillData(bookList);

    return publicationsData;
}

int Library::loanRegistration(Loan *loan)
{
    loans.push_back(loan);
    return loan->getNumber();
}

int Library::loanExclude(Loan *loan)
{
    for (int i = 0; i < loans.size(); i++)
        if (loans[i] == loan)
        {
            loans.erase(loans.begin() + i);
            return loan->getNumber();
        }

    throw runtime_error("Empréstimo não encontrado");
}

string Library::loanAddBook(Loan *loan, LoanItem *loanItem)
{
    if (loanItem->getBook()->getNumberOfCopies() == 0)
        throw runtime_error("Livro sem exemplares");

    loan->addBook(loanItem);
    return loanItem->getBook()->getTitle();
}

string Library::loanExcludeBook(Loan *loan, LoanItem *loanItem)
{
    loan->excludeBook(loanItem);
    return loanItem->getBook()->getTitle();
}

string Library::loanReturnBook(Loan *loan, LoanItem *loanItem)
{
    loan->returnBook(loanItem);
    return loanItem->getBook()->getTitle();
}

int Library::loanReturnAll(Loan *loan)
{
    loan->returnAll();
    return loan->getNumber();
}

Loan *Library::getLoan(const int number) const
{
    for (auto loan : loans)
        if (loan->getNumber() == number)
            return loan;

    throw runtime_error("Empréstimo não encontrado");
}

User *Library::getUser(const string CPF) const
{
    for (auto user : users)
        if (user->getCpf() == CPF)
            return user;

    throw runtime_error("Usuário não encontrado");
}

Book *Library::getBook(const int code) const
{
    for (auto publication : publications)
    {
        if (typeid(*publication).hash_code() == typeid(Book).hash_code())
            if ((publication)->getCode() == code)
                return static_cast<Book *>(publication);
    }

    throw runtime_error("Livro não encontrado");
}

Periodical *Library::getPeriodical(const int code) const
{
    for (auto publication : publications)
        if (typeid(*publication).hash_code() == typeid(Periodical).hash_code())
            if (publication->getCode() == code)
                return static_cast<Periodical *>(publication);

    throw runtime_error("Periódico não encontrado");
}

pair<vector<map<string, string>>, map<int, vector<map<string, string>>>> Library::loanList() const
{
    vector<map<string, string>> loanList;
    map<int, vector<map<string, string>>> loanItemList;
    for (auto loan : loans)
    {
        map<string, string> loanData;
        loanData["number"] = to_string(loan->getNumber());
        loanData["userCpf"] = loan->getUser()->getCpf();
        loanData["userName"] = loan->getUser()->getName();
        loanData["loanDate"] = loan->getLoanDate().toString();
        loanData["expectReturnDate"] = loan->getExpectReturnDate().toString();
        loanList.push_back(loanData);

        vector<map<string, string>> loanItemVector;
        for (auto loanItem : loan->getLoanItems())
        {
            map<string, string> loanItemData;
            loanItemData["code"] = to_string(loanItem->getBook()->getCode());
            loanItemData["title"] = loanItem->getBook()->getTitle();
            loanItemData["publisher"] = loanItem->getBook()->getPublisher();
            loanItemData["year"] = to_string(loanItem->getBook()->getYear());
            loanItemData["author"] = loanItem->getBook()->getAuthor();
            loanItemData["numberOfCopies"] = to_string(loanItem->getBook()->getNumberOfCopies());

            loanItemVector.push_back(loanItemData);
        }
        loanItemList[loan->getNumber()] = loanItemVector;
    }

    return pair<vector<map<string, string>>, map<int, vector<map<string, string>>>>(loanList, loanItemList);
}

bool Library::thisUserHasLoan(const User *user)
{
    for (auto loan : loans)
        if (loan->getUser() == user)
            if (loan->isActive())
                return true;

    return false;
}

bool Library::isThisCPFAlreadyRegistered(const string CPF)
{
    for (auto user : users)
        if (user->getCpf() == CPF)
            return true;

    return false;
}

bool Library::isThisBookLoaned(const Book *book)
{
    for (auto loan : loans)
        if (loan->isActive())
            for (auto loanItem : loan->getLoanItems())
                if (loanItem->getBook() == book)
                    return true;

    return false;
}

bool Library::isThisCodeAlreadyRegistered(const int code)
{
    for (auto publication : publications)
        if (publication->getCode() == code)
            return true;

    return false;
}

void Library::publicationRegistration(Publication *publication)
{
    if (isThisCodeAlreadyRegistered(publication->getCode()))
        throw runtime_error("Código já cadastrado");

    publications.push_back(publication);
}

vector<Publication *> Library::getBookByAuthor(const string author) const
{
    vector<Publication *> bookList;
    for (int i = 0; i < publications.size(); i++)
        if (typeid(*publications[i]).hash_code() == typeid(Book).hash_code())
            if (static_cast<Book *>(publications[i])->getAuthor().find(author) != string::npos)
                bookList.push_back((publications[i]));

    return bookList;
}

vector<Publication *> Library::getPublicationByTitle(const string title) const
{
    vector<Publication *> publicationList;
    for (int i = 0; i < publications.size(); i++)
        if (publications[i]->getTitle().find(title) != string::npos)
            publicationList.push_back(publications[i]);

    return publicationList;
}

void Library::writeToFile()
{
    ofstream file;
    file.open("library.txt");
    if (!file.is_open())
        throw runtime_error("Erro ao abrir arquivo");

    file << "Usuários: " << endl;
    for (auto user : users)
    {
        file << "CPF: " << user->getCpf() << endl;
        file << "Nome: " << user->getName() << endl;
        file << "Data de Penalização: " << user->getPenalizationDate().toString() << endl;
        file << "Endereço: " << user->getAddress() << endl;
        file << "Telefone: " << user->getPhone() << endl;
    }

    file << "Publicações:" << endl;
    for (auto publication : publications)
    {
        file << "Código da Publicação: " << publication->getCode() << "; Título: " << publication->getTitle() << "; Editora: " << publication->getPublisher() << "; Ano: " << publication->getYear();

        if (typeid(*publication).hash_code() == typeid(Book).hash_code())
        {
            file << "; Autor: " << static_cast<Book *>(publication)->getAuthor() << "; Número de Cópias: " << static_cast<Book *>(publication)->getNumberOfCopies() << endl;
        }
        else if (typeid(*publication).hash_code() == typeid(Periodical).hash_code())
        {
            file << "; Mês: " << static_cast<Periodical *>(publication)->getMonth() << "; Número da edição: " << static_cast<Periodical *>(publication)->getNumberOfEdition() << endl;
        }
    }

    file << "Empréstimos: " << endl;
    for (auto loan : loans)
    {
        file << "Código do Empréstimo: " << loan->getNumber() << "; CPF do usuário: " << loan->getUser()->getCpf() << "; Nome do Usuário: " << loan->getUser()->getName() << "; Data de Empréstimo: " << loan->getLoanDate().toString() << "; Data Prevista de Devolução: " << loan->getExpectReturnDate().toString() << endl;

        file << "Itens do Empréstimo: " << endl;
        for (auto loanItem : loan->getLoanItems())
        {
            file << "Código do livro: " << loanItem->getBook()->getCode() << "; Nome do livro:  " << loanItem->getBook()->getTitle();
            loanItem->isReturned() ? file << "; Status: devolvido dia " + loanItem->getLoanEndDate().toString() : file << "; Status: não devolvido";
            file << ";" << endl;
        }
    }
}

void Library::readFromFile()
{
    ifstream file;
    file.open("library.txt");
    if (!file.is_open())
        throw runtime_error("Erro ao abrir arquivo");

    string line;
    while (getline(file, line))
    {
        if (line.find("Usuários:") != string::npos)
        {
            while (getline(file, line))
            {
                if (line.find("CPF:") != string::npos)
                {
                    string cpf = line.substr(line.find("CPF: ") + 5);
                    getline(file, line);
                    string name = line.substr(line.find("Nome: ") + 6);
                    getline(file, line);
                    string penalizationDate = line.substr(line.find("Data de Penalização: ") + 23);
                    getline(file, line);
                    string address = line.substr(line.find("Endereço: ") + 11);
                    getline(file, line);
                    string phone = line.substr(line.find("Telefone: ") + 10);
                    users.push_back(new User(name, cpf, address, phone, penalizationDate));
                }
                else
                    break;
            }
        }
        if (line.find("Publicações:") != string::npos)
        {
            while (getline(file, line))
            {
                if (line.find("Código da Publicação:") != string::npos)
                {
                    string code = line.substr(line.find("Código da Publicação: ") + 25, line.find(";") - 25);
                    line.erase(0, line.find(";") + 1);
                    string title = line.substr(line.find("Título: ") + 9, line.find(";") - 10);
                    line.erase(0, line.find(";") + 1);
                    string publisher = line.substr(line.find("Editora: ") + 9, line.find(";") - 10);
                    line.erase(0, line.find(";") + 1);
                    string year = line.substr(line.find("Ano: ") + 5, line.find(";") - 6);
                    getline(file, line);
                    cout << code << endl;
                    cout << title << endl;
                    cout << publisher << endl;
                    cout << year << endl;

                    if (line.find("Autor") != string::npos)
                    {
                        string author = line.substr(line.find("Autor: ") + 7, line.find(";") - 7);
                        line.erase(0, line.find(";") + 1);
                        string numberOfCopies = line.substr(line.find("Cópias: ") + 9, line.find(";") - 10);
                        cout << author << endl;
                        cout << numberOfCopies << endl;

                        publications.push_back(new Book(stoi(code), title, publisher, stoi(year), author, stoi(numberOfCopies)));
                    }
                    else
                    {
                        string month = line.substr(line.find("Mês:") + 4, line.find(";") - 4);
                        line.erase(0, line.find(";") + 1);
                        string numberOfEdition = line.substr(line.find("Edição: ") + 10, line.find(";") - 11);
                        cout << month << endl;
                        cout << numberOfEdition << endl;
                        publications.push_back(new Periodical(stoi(code), title, publisher, stoi(year), month, stoi(numberOfEdition)));
                    }
                }
            }
        }
        if (line.find("Empréstimos:") != string::npos)
        {
            while (getline(file, line))
            {
                if (line.find("Código do Empréstimo:") != string::npos)
                {
                    string number = line.substr(line.find("Código do Empréstimo:") + 19, line.find(";"));
                    string cpf = line.substr(line.find("CPF do usuário:") + 16, line.find(";"));
                    string name = line.substr(line.find("Nome do Usuário:") + 14, line.find(";"));
                    string loanDate = line.substr(line.find("Data de Empréstimo:") + 18, line.find(";"));
                    string expectReturnDate = line.substr(line.find("Data Prevista de Devolução:") + 26, line.find(";"));
                    this->loanRegistration(new Loan(this->getUser(cpf), expectReturnDate, loanDate, stoi(number)));
                }
                else
                    break;
            }
        }
        if (line.find("Itens do Empréstimo:") != string::npos)
        {
            while (getline(file, line))
            {
                if (line.find("Código do livro:") != string::npos)
                {
                    string bookCode = line.substr(line.find("Código do livro:") + 15, line.find(";"));
                    string bookTitle = line.substr(line.find("Nome do livro:") + 12, line.find(";"));
                    string loanEndDateStatus = line.substr(line.find("Status:") + 7, line.find(";"));
                    if (loanEndDateStatus.find("devolvido") != string::npos)
                    {
                        string loanEndDate = line.substr(line.find("dia ") + 4, line.find(";"));
                        loans.back()->addBook(new LoanItem(this->getBook(stoi(bookCode)), loanEndDate));
                    }
                    else
                        loans.back()->addBook(new LoanItem(this->getBook((stoi(bookCode)))));
                }
                else
                    break;
            }
        }
    }
}
