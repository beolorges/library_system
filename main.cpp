#include "interface/interface.hpp"
int main()
{
    interface *minhaInterface = new interface();

    minhaInterface->main();
    delete minhaInterface;
    return 0;
}