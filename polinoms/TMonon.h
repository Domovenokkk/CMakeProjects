// Copyright 2024 Mezhuev Maksim
#include "../lib_list/list.h"
#include "Parcer.h"
#include <string>

template<typename TKoef>
class TMonom
{
    TKoef koef; // ����������� ������
    int* x_powers; // ������ �������� ����������
    size_t k_cntofxes; // ���������� ����������
    size_t n_maxpower; // ������������ �������

public:
    // ����������� � �����������
    TMonom(TKoef koef_, size_t k, size_t n) :
        koef(koef_), k_cntofxes(k), n_maxpower(n)
    {
        x_powers = new int[k_cntofxes];
        for (size_t i = 0; i < k_cntofxes; i++) x_powers[i] = 0;
    }

    // ����������� �����������
    TMonom(const TMonom& copy)
    {
        koef = copy.koef;
        k_cntofxes = copy.k_cntofxes;
        n_maxpower = copy.n_maxpower;
        x_powers = new int[k_cntofxes];
        for (size_t i = 0; i < k_cntofxes; i++)
        {
            x_powers[i] = copy.x_powers[i];
        }
    }

    // ����� ��� ���������� �������� ����������
    void FillPower(int xi, int power)
    {
        tryerr.wrong_monom_Power(power, n_maxpower); // �������� ������������ �������
        tryerr.wrong_monom_Xi(xi, k_cntofxes); // �������� ������������ ������ ����������
        x_powers[--xi] = power; // ������ �������, ������ ���������� ����������� �� 1
    }

    // ����������
    ~TMonom()
    {
        delete[] x_powers;
    }


    friend std::ostream& operator<<(std::ostream& os, const TMonom<TKoef>& dt)
    {
        os << dt.koef;
        for (size_t i = 0; i < dt.k_cntofxes; i++)
        {
            if (dt.x_powers[i] != 0)
            {
                os << "x" << i + 1;
                if (dt.x_powers[i] != 1) os << "^" << dt.x_powers[i];
            }
        }
        return os;
    }

    void PrintINFO()
    {
        std::cout << "koef: " << koef << std::endl;
        for (size_t i = 0; i < k_cntofxes; i++)
        {
            std::cout << i + 1 << ">X^ " << x_powers[i] << std::endl;
        }
    }

    // ����� ��� ������ ������
    void PrintMonom(bool plus)
    {
        if (koef != 1) std::cout << koef;
        for (size_t i = 0; i < k_cntofxes; i++)
        {
            if (x_powers[i] != 0)
            {
                std::cout << "x" << i + 1;
                if (x_powers[i] != 1) std::cout << "^" << x_powers[i];
            }
        }
        if (plus) std::cout << "+";
    }

    TKoef getKoef() const
    {
        return koef;
    }

    void Mul(int n)
    {
        koef = koef * n;
    }

    void Mul(double n)
    {
        koef = koef * n;
    }


    bool operator==(const TMonom& other) const
    {
        for (size_t i = 0; i < k_cntofxes; i++)
        {
            if (x_powers[i] != other.x_powers[i]) return false;
        }
        return true;
    }

    void addKoef(TKoef other)
    {
        koef = koef + other;
    }
};

template<typename TKoef>
std::ostream& operator<<(std::ostream& os, const TMonom<TKoef>& dt)
{
    os << koef;
    for (int i = 0; i < k_cntofxes; i++)
    {
        if (x_powers[i] != 0)
        {
            os << "x^" << x_powers[i];
        }
    }
    return os;
}