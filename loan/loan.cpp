#include "loan.hpp"

Loan::Loan(User *user, Date expectReturnDate)
{
    if (user->isPenalized())
        throw runtime_error("Usuário está com pendências, só poderá pegar livro novamente dia " + user->getPenalizationDate().toString());

    this->user = user;
    this->expectReturnDate = expectReturnDate;
    this->loanDate.setToday();
    this->number = ++nextNumber;
}

void Loan::addBook(LoanItem *loanItem)
{
    if (this->user->isPenalized())
        throw runtime_error("Usuário está com pendências, só poderá pegar livro novamente dia " + this->user->getPenalizationDate().toString());

    loanItem->getBook()->loanCopy();
    loanItems.push_back(loanItem);
}

void Loan::excludeBook(LoanItem *loanItem)
{

    for (int i = 0; i < loanItems.size(); i++)
    {
        if (loanItems[i]->getBook()->getCode() == loanItem->getBook()->getCode())
        {
            loanItem->getBook()->returnCopy();
            loanItems.erase(loanItems.begin() + i);
            return;
        }
    }
    throw runtime_error("Livro não encontrado no empréstimo para ser excluído");
}

void Loan::returnBook(LoanItem *_loanItem)
{
    for (auto loanItem : loanItems)
        if (loanItem->getBook()->getCode() == _loanItem->getBook()->getCode())
        {
            loanItem->setLoanEndDate();
            loanItem->getBook()->returnCopy();

            for (auto loanItem : loanItems)
            {
                if (!loanItem->isReturned())
                    return;
            }

            this->user->returnAllBooks(this->expectReturnDate);
            return;
        }

    throw runtime_error("Livro não encontrado no empréstimo para ser devolvido");
}

void Loan::returnAll()
{
    for (auto loanItem : loanItems)
    {
        loanItem->setLoanEndDate();
        loanItem->getBook()->returnCopy();
    }

    this->user->returnAllBooks(this->expectReturnDate);
}

bool Loan::isActive() const
{
    for (auto loanItem : loanItems)
    {
        if (!loanItem->isReturned())
            return true;
    }
    return false;
}