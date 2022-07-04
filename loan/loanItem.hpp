#ifndef LOANITEM_HPP
#define LOANITEM_HPP

#include "../date/date.hpp"
#include "../publication/book.hpp"

class LoanItem
{
private:
    Book *book;
    Date loanEndDate;

public:
    LoanItem(Book *book, string loanEndDate) : book(book), loanEndDate(loanEndDate){};
    LoanItem(Book *book) : book(book), loanEndDate(Date(0)){};
    ~LoanItem(){};

    inline Book *getBook() const { return book; };
    inline Date getLoanEndDate() const { return loanEndDate; };

    void setLoanEndDate() { this->loanEndDate.setToday(); };
    bool isReturned() const { return loanEndDate != Date(0); };
};

#endif