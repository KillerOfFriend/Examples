#ifdef _WIN32
#    if defined(PATHWALKER_EXPORTS)
#        define PATHWALKER_LIB __declspec(dllexport)
#    else
#        define PATHWALKER_LIB __declspec(dllimport)
#    endif // PATHWALKER_EXPORTS
#else
#    define PATHWALKER_LIB
#endif // __WINT32
