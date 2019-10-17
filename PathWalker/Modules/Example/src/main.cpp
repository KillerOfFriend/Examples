#include <iostream>

#include "PathWalker.h"

int main(int argc, char *argv[])
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
