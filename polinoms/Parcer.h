#pragma once
#include <iostream>
#include <vector>
#include <string>

// Function to extract the polynomial body from a given string
std::string take_pol_body(const std::string& str)
{

    size_t ind = str.find_first_of('=');
    std::string ret = "";
    for (size_t i = ind + 1; i < str.size(); i++)
    {
        ret += str[i];
    }
    ret += '+';
    return ret;
}

class expect
{
public:
    expect() = default;

    // Function to check the validity of monom power
    void wrong_monom_Power(int pow, int max)
    {
        if (pow < 0 || pow > max)
        {
            std::cerr << "wrong monom power";
            exit(101);
        }
    }

    // Function to check the validity of monom Xi
    void wrong_monom_Xi(int xi, int xmax)
    {
        if (xi <= 0 || xi > xmax)
        {
            std::cerr << "wrong monom Xi";
            exit(102);
        }
    }

    // Function to check the validity of polynomial variable count
    void wrong_pol_K(int k)
    {
        if (k < 0)
        {
            std::cerr << "pol wrong number of vars";
            exit(202);
        }
    }

    // Function to check the validity of polynomial variable count and return a boolean
    bool check_pol_K(int k)
    {
        if (k < 0)
        {
            std::cerr << "pol wrong number of vars" << std::endl;
            return true;
        }
        return false;
    }

    // Function to check the validity of polynomial power
    void wrong_pol_N(int n)
    {
        if (n < 0)
        {
            std::cerr << "pol power < 0";
            exit(201);
        }
    }

    // Function to check the validity of polynomial power and return a boolean
    bool check_pol_N(int n)
    {
        if (n < 0)
        {
            std::cerr << "pol power < 0" << std::endl;
            return true;
        }
        return false;
    }

    // Function to check the validity of the type character
    bool type_check(char c)
    {
        if (c == 'i' || c == 'd')
        {
            return false;
        }
        std::cerr << "wrong type ?: " << c << std::endl;
        return true;
    }

    // Function to check for unexpected symbols in polynomial name
    bool unexpect_sbl_for_pol_name(char s)
    {
        std::string check = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_";
        for (char i : check)
        {
            if (i == s)
            {
                return false;
            }
        }
        std::cerr << "wrong polinom name ?:" << s;
        return true;
    }

    // Function to report unexpected symbols in polynomial body with a marker
    bool bodyparcer_unexpsym(char s, size_t locate)
    {
        for (size_t i = 0; i < locate; i++)
        {
            std::cerr << " ";
        }
        std::cerr << "^ - unexpected symbol for polinom: " << s << std::endl;
        return true;
    }

    // State machine to parse polynomial body
    bool bodyparcer_state(char s, short* state, short* todo, size_t locate)
    {
        std::string numbers = "1234567890";

        switch (*state)
        {
        case 0:
            if (s == 'x')
            {
                *state = 1;
                *todo = 1;
                return false;
            }
            if (numbers.find(s) != std::string::npos)
            {
                *state = 2;
                *todo = 2;
                return false;
            }
            return bodyparcer_unexpsym(s, locate);

        case 1:
            if (numbers.find(s) != std::string::npos)
            {
                *state = 3;
                *todo = 3;
                return false;
            }
            return bodyparcer_unexpsym(s, locate);

        case 2:
            if (s == 'x')
            {
                *state = 1;
                *todo = 5;
                return false;
            }
            if (s == '.')
            {
                *state = 5;
                *todo = 4;
                return false;
            }
            if (s == '+')
            {
                *state = 0;
                *todo = 9;
                return false;
            }
            if (numbers.find(s) != std::string::npos)
            {
                *state = 2;
                *todo = 4;
                return false;
            }
            return bodyparcer_unexpsym(s, locate);

        case 3:
            if (s == '^')
            {
                *state = 4;
                *todo = -1;
                return false;
            }
            if (s == '+')
            {
                *state = 0;
                *todo = 7;
                return false;
            }
            if (s == 'x')
            {
                *state = 1;
                *todo = 7;
                return false;
            }
            return bodyparcer_unexpsym(s, locate);

        case 4:
            if (s == '+')
            {
                *state = 0;
                *todo = 8;
                return false;
            }
            if (s == 'x')
            {
                *state = 1;
                *todo = 8;
                return false;
            }
            if (numbers.find(s) != std::string::npos)
            {
                *state = 4;
                *todo = 6;
                return false;
            }
            return bodyparcer_unexpsym(s, locate);

        case 5:
            if (s == 'x')
            {
                *state = 1;
                *todo = 5;
                return false;
            }
            if (s == '+')
            {
                *state = 0;
                *todo = 9;
                return false;
            }
            if (numbers.find(s) != std::string::npos)
            {
                *state = 5;
                *todo = 4;
                return false;
            }
            return bodyparcer_unexpsym(s, locate);

        default:
            std::cerr << "unknown parser state";
            exit(999);
        }
    }

    // Function to check if the polynomial name exists in the given namespace
    bool PolNameSpaceCheck(const std::vector<std::string>& Polnamespace, const std::string& name)
    {
        for (const std::string& i : Polnamespace)
        {
            if (name == i)
            {
                return true;
            }
        }
        return false;
    }

    ~EXPECT() = default;
};