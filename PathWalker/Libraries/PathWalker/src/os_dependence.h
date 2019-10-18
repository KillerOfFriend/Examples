#ifndef OS_DEPENDENCE_H
#define OS_DEPENDENCE_H

#ifdef _WIN32
    #include <Windows.h>
    #define ENCODINGSETUP(inEncode) { SetConsoleCP(inEncode); SetConsoleOutputCP(inEncode); }
#elif __linux__
    #define CP_UTF8
    #define ENCODINGSETUP(inEncode) {}
#endif

#endif // OS_DEPENDENCE_H
