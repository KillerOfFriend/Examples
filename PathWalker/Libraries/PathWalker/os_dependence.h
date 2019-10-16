#ifndef OS_DEPENDENCE_H
#define OS_DEPENDENCE_H

#include <string>

// Выбираем размер смвола строки
#ifdef _WIN32
    typedef std::wstring TString; // Двухбайтная кодировка UTF16
#elif __linux__
    typedef std::string TString; // Однобайтная кодировка UTF8
#endif

#endif // OS_DEPENDENCE_H
