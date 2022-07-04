#include "user.hpp"
#include "../date/date.hpp"

int testDate()
{
    User user("João", "123456789", "Rua 1", "123456789");
    user.returnAllBooks(Date(2, 7, 2022));

    Date date("10/10/2022");
    cout << date.toString() << endl;

    cout << user.getPenalizationDate().toString() << endl;

    return 0;
}