#ifndef LOAN_HPP
#define LOAN_HPP

#include "../date/date.hpp"
#include "../user/user.hpp"
#include "loanItem.hpp"

#include <string>
#include <algorithm>
#include <vector>
#include "loanItem.hpp"

using namespace std;

class Loan
{
private:
    int number;
    Date loanDate;
    Date expectReturnDate;
    User *user;
    vector<LoanItem *> loanItems;
    static int nextNumber;

public:
    Loan(User *user, string expectReturnDate, string loanDate, int number) : user(user), loanDate(loanDate), expectReturnDate(expectReturnDate), number(number){};
    Loan(User *, Date);
    ~Loan(){};

    void addBook(LoanItem *);
    void excludeBook(LoanItem *);
    void returnBook(LoanItem *);
    void returnAll();

    bool isActive() const;

    inline int getNumber() const { return this->number; };
    inline User *getUser() const { return this->user; };
    inline Date getLoanDate() const { return this->loanDate; };
    inline Date getExpectReturnDate() const { return this->expectReturnDate; };
    inline vector<LoanItem *> getLoanItems() const { return this->loanItems; };
};

#endif