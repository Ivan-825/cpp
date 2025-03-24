#ifndef COLOR_CODES_H
#define COLOR_CODES_H

#ifdef _WIN32 // Check if the OS is Windows
    static inline const char* GREEN = "\033[32m";
    static inline const char* RED = "\033[31m";
    static inline const char* CYAN = "\033[36m";
    static inline const char* DEF = "\033[0m";
#else // For non-Windows OS (Linux, macOS, etc.)
    static inline const char* GREEN = "";
    static inline const char* RED = "";
    static inline const char* CYAN = "";
    static inline const char* DEF = "";
#endif

#endif // COLOR_CODES_H