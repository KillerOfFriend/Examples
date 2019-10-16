#include <iostream>

#include "PathWalker.h"

int main()
{
    TString Path;
    TPathWalker PathWalker(Path);

    if (!PathWalker.isValid())
        std::cout << "Не удалось считать файл лаберинта!" << std::endl;
    else
    {

    }

    return 0;
}
