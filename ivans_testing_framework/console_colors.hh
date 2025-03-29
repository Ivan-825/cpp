#ifndef COLOR_CODES_H
#define COLOR_CODES_H

#ifdef _WIN32
    const char* GREEN = "\033[32m";
    const char* RED = "\033[31m";
    const char* CYAN = "\033[36m";
    const char* DEF = "\033[0m";
#elif defined(__linux__) || defined(linux) || defined(__gnu_linux__)
    const char* GREEN = "\033[32m";
    const char* RED = "\033[31m";
    const char* CYAN = "\033[36m";
    const char* DEF = "\033[0m";
#elif defined(__APPLE__) && defined(__MACH__)
    const char* GREEN = "";
    const char* RED = "";
    const char* CYAN = "";
    const char* DEF = "";
#else
    const char* GREEN = "";
    const char* RED = "";
    const char* CYAN = "";
    const char* DEF = "";
#endif

#endif