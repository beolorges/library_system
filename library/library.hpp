#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "../user/user.hpp"
#include "../publication/publication.hpp"
#include "../publication/book.hpp"
#include "../publication/periodical.hpp"
#include "../date/date.hpp"
#include "../loan/loan.hpp"
#include "../loan/loanItem.hpp"

using namespace std;

class Library
{
private:
    vector<Publication *> publications;
    vector<Loan *> loans;
    vector<User *> users;

    bool thisUserHasLoan(const User *);
    bool isThisBookLoaned(const Book *);
    bool isThisCPFAlreadyRegistered(const string);
    bool isThisCodeAlreadyRegistered(const int);

    map<int, map<string, string>> fillData(const vector<Publication *> publications) const;

    vector<Publication *> getPublicationByTitle(const string) const;
    vector<Publication *> getBookByAuthor(const string) const;
    vector<Publication *> getAllPublications() const { return publications; };

public:
    Library(){};
    ~Library(){};

    void userRegistration(User *user);
    void userExclude(const User *);

    void publicationRegistration(Publication *publication);

    void publicationExclude(Publication *);
    map<int, map<string, string>> publicationSearchByTitle(const string) const;
    map<int, map<string, string>> publicationSearchByAuthor(const string) const;
    map<int, map<string, string>> publicationList() const;

    int loanRegistration(Loan *loan);
    int loanExclude(Loan *);
    string loanAddBook(Loan *, LoanItem *);
    string loanExcludeBook(Loan *, LoanItem *);
    string loanReturnBook(Loan *, LoanItem *);
    int loanReturnAll(Loan *);
    pair<vector<map<string, string>>, map<int, vector<map<string, string>>>> loanList() const;

    Loan *getLoan(const int) const;
    User *getUser(const string) const;
    Book *getBook(const int) const;
    Periodical *getPeriodical(const int) const;

    void readFromFile();
    void writeToFile();
};

#endif