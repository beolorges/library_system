#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "../library/library.hpp"
#include "../publication/publication.hpp"
#include "../publication/book.hpp"
#include "../publication/periodical.hpp"
#include "../date/date.hpp"
#include "../loan/loan.hpp"
#include "../loan/loanItem.hpp"
#include "../user/user.hpp"

using namespace std;

class Interface
{
private:
    Library myLibrary;

    void menuPrint() const;

    /*----------------------------------------- User ------------------------------------------*/
    void userRegistration();
    void userExclude();

    /*-------------------------------------- Publication --------------------------------------*/
    map<string, string> publicationRegistration();
    void bookRegistration();
    void bookExclude();

    void periodicalRegistration();
    void periodicalExclude();

    map<int, map<string, string>> publicationSearchByTitle() const;
    map<int, map<string, string>> publicationSearchByAuthor() const;
    map<int, map<string, string>> publicationSearchAll() const;
    void publicationPrint(map<int, map<string, string>>) const;

    /*----------------------------------------- Loan ------------------------------------------*/
    Loan *loanRegistration();
    Loan *loanByLoanNumber();
    void loanMenuPrint();
    void loanOptions(Loan *);
    void loanAddBook(Loan *);
    void loanExcludeBook(Loan *);
    void loanReturnBook(Loan *);
    void loanReturnAll(Loan *);
    void loanExclude(Loan *);
    void loanPrint() const;

public:
    Interface(){};
    Interface(Library l) : myLibrary(l){};
    ~Interface(){};

    void main();
};

#endif