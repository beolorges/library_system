#include "user.hpp"

void User::returnAllBooks(Date expectedReturnDate)
{
    int daysToAdd = 0;
    if (Date().getToday() > expectedReturnDate)

        daysToAdd = (Date().getToday() - expectedReturnDate) * 3;

    this->penalizationDate += daysToAdd;
}
