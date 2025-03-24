#ifndef COLOR_CODES_H
#define COLOR_CODES_H

#ifdef _WIN32
    static inline const char* GREEN = "\033[32m";
    static inline const char* RED = "\033[31m";
    static inline const char* CYAN = "\033[36m";
    static inline const char* DEF = "\033[0m";
#elif defined(__linux__) || defined(linux) || defined(__gnu_linux__)
    static inline const char* GREEN = "";
    static inline const char* RED = "";
    static inline const char* CYAN = "";
    static inline const char* DEF = "";
#elif defined(__APPLE__) && defined(__MACH__)
    static inline const char* GREEN = "";
    static inline const char* RED = "";
    static inline const char* CYAN = "";
    static inline const char* DEF = "";
#else
    static inline const char* GREEN = "";
    static inline const char* RED = "";
    static inline const char* CYAN = "";
    static inline const char* DEF = "";
#endif

#endif