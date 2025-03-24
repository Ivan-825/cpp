#ifndef IVANS_U_TESTER_H
#define IVANS_U_TESTER_H

#include <iostream>
#include <type_traits>
#include <string>

#include "console_colors.hh"

class Tester {
private:
    static inline bool init = false;
    
    static inline int all = 0;
    static inline int succ = 0;
    static inline int current = 0;

    

    Tester() {
        init = true;
        std::cout << CYAN << "\nTesting Framework by Ivan\n\n" << DEF;
    }

    ~Tester() {
        if (succ == all) {
            std::cout << GREEN << "\n\n[ALL " << CYAN << succ << GREEN << " tests run successfully!]\n" << DEF;
        }
        else {
            std::cout << RED << "\n\n[Out of " << CYAN << all << RED << " tests " << CYAN << succ << RED << " run successfully!]\n" << DEF;
        }
    }

    template<typename T, typename D>

    static void assertArrays(const T& t, const D& d) {
        bool success = true;
        std::string err = "\n";
        try {
            if (not (std::is_array<T>() && std::is_array<D>())) throw std::invalid_argument("   Illegal comparison between array and non array!");
        } catch (const std::exception& e) {
            err += e.what();
            //err += "\n";
            success = false;
        }
        
        if (not std::is_same_v<std::remove_all_extents<T>, std::remove_all_extents<D>> && success) {
            if (not (std::is_arithmetic<std::remove_all_extents_t<T>>())
                    || not (std::is_arithmetic<std::remove_all_extents_t<D>>())) {
                    
                    success = false;
                    err += "    Arrays are of uncomparable types!";
                }
            //throw std::invalid_argument("Illegal comparison: arrays are not of same types!");
        }
        int lent = sizeof(t) / sizeof(t[0]);
        int lend = sizeof(d) / sizeof(d[0]);

        if (lent != lend && success) {
            err += ("   The two arrays differ in length!: Length of first array is[" +
                std::to_string(lent) + "] and the length of second array is [" + std::to_string(lend) + "].");
            success = false;
        }

        all++;
        current++;

        if (success) {
            for (int i = 0; i < lent; i++) {
                if (t[i] != d[i]) {
                    success = false;
                    err += "    Excepted: '" + std::to_string(t[i]) +
                        "', but actual was: '" + std::to_string(d[i]) + "'  At index:[" + std::to_string(i)
                        + "]\n";
                }
            }
        }
        
        if (success) {
            std::cout << GREEN << "[+] " << DEF << "(" << CYAN << current << DEF << ")" << GREEN << " Case Passed!\n" << DEF;
            succ++;
        }
        else {
            std::cout << RED << "[-] " << DEF << "(" << CYAN << current << DEF << ")" << RED << " Case Failed! Reason: " << DEF << err << "\n";
        }
    }

    template<typename T, typename D>

    static void assertPrims(const T& t, const D& d) {
        all++;
        current++;
        bool success;
        const char* error;
        try {
            (t == d) ? success = true : throw std::runtime_error("Excepted " + std::to_string(t) + " but actual was " + std::to_string(d));
        }
        catch (const std::exception& e) {
            success = false;
            error = e.what();
        }

        if (success) {
            std::cout << GREEN << "[+] " << DEF << "(" << CYAN << current << DEF << ")" << GREEN << " Case Passed!\n" << DEF;
            succ++;
        }
        else {
            std::cout << RED << "[-] " << DEF << "(" << CYAN << current << DEF << ")" << RED << " Case Failed! Reason: " << DEF << error << "\n";
        }
    }

public:



    template<typename T, typename D>

    static void assertEquals(const T& t, const D& d) {
        if (!init) static Tester tester; //

        if constexpr(std::is_array<T>() || std::is_array<D>()){
            assertArrays(t, d);
        }
        else {
            assertPrims(t, d);
        }
        
    }
};

template<typename T, typename D>
inline void assertEquals(const T& t, const D& d) {
    Tester::assertEquals(t, d);
}

#endif
