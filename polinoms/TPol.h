// Copyright 2024 Mezhuev Maksim
#include "../lib_list/list.h"
#include "Parcer.h"
#include <string>

template<typename TKoef>
class TPolinom
{
    std::string name; // ��� ��������
    TList<TMonom<TKoef>> monoms; // ������ �������
    size_t k_cntofxes; // ���������� ����������
    size_t n_maxpower; // ������������ �������

public:
    TPolinom(size_t xes_count, size_t maxpower) :
        k_cntofxes(xes_count), n_maxpower(maxpower)
    {
        tryerr.wrong_pol_K(k_cntofxes);
        tryerr.wrong_pol_N(n_maxpower);
    }

    TPolinom(std::string pname, size_t xes_count, size_t maxpower) :
        name(pname), k_cntofxes(xes_count), n_maxpower(maxpower)
    {
        tryerr.wrong_pol_K(k_cntofxes);
        tryerr.wrong_pol_N(n_maxpower);
    }

    // ����� ��� ���������� ������ �� ������������
    void addMonomByCoefficient(TKoef koef)
    {
        TMonom<TKoef>* newMonom = new TMonom<TKoef>(koef, k_cntofxes, n_maxpower);
        monoms.pushBack(monoms.createNode(newMonom));
    }


    void addMonomByCopy(const TMonom<TKoef>& copy)
    {
        TMonom<TKoef>* newMonom = new TMonom<TKoef>(copy);
        monoms.pushBack(monoms.createNode(newMonom));
    }

    // ����� ��� ���������� �������� ���������� � ������� ������
    void fillPower(int xi, int power)
    {
        monoms.top()->fillPower(xi, power);
    }


    ~TPolinom()
    {
        monoms.~TList();
    }

    // ����� ��� ������ ���������� � ���������� ������ �� �������
    void printMonomInfo(int index)
    {
        monoms[index]->printInfo();
    }

    void printPolynomInfo()
    {
        std::cout << name
            << " k: " << k_cntofxes
            << " n: " << n_maxpower
            << std::endl;
    }

    // ����� ��� ������ ��������
    void printPolynom()
    {
        std::cout << name << "=";
        monoms.printMonoms();
        std::cout << std::endl;
    }


    TMonom<TKoef>* getMonom(size_t index)
    {
        return monoms[index];
    }

    size_t getMonomsSize() const
    {
        return monoms.getSize();
    }

    size_t getVariableCount() const
    {
        return k_cntofxes;
    }


    size_t getMaxPower() const
    {
        return n_maxpower;
    }


    std::string getName() const
    {
        return name;
    }


    void multiplyBy(int n)
    {
        for (size_t i = 0; i < monoms.getSize(); i++)
        {
            monoms[i]->multiplyBy(n);
        }
    }


    void multiplyBy(double n)
    {
        for (size_t i = 0; i < monoms.getSize(); i++)
        {
            monoms[i]->multiplyBy(n);
        }
    }

    // ����� ��� �������� ������������� ������ � �������� � ����������� ��� �������
    size_t checkToAdd(const TMonom<TKoef>& other)
    {
        for (size_t i = 0; i < monoms.getSize(); i++)
        {
            if ((*monoms[i]) == other)
            {
                return i;
            }
        }
        return static_cast<size_t>(-1); // ���������� ������������ �������� size_t, ���� ����� �� ������
    }
};