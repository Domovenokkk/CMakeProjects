#include <iostream>
#include <stdexcept>
#include "../lib_list/list.h"

// ���������� ��������� Pair
template<typename TKey, typename TValue>
struct Pair {
    TKey key;
    TValue Val;

    // �������� ������������
    Pair<TKey, TValue>& operator=(const Pair<TKey, TValue>& other) {
        if (this != &other) {
            key = other.key;
            Val = other.Val;
        }
        return *this;
    }

    // �������� ���������
    bool operator==(const Pair<TKey, TValue>& other) const {
        return key == other.key;
    }
};

// ���������� ��������� ITable
template<typename TKey, typename TValue>
class ITable {
public:
    virtual void pushback(TKey K, TValue V) = 0;
    virtual void printtable() const = 0;
    virtual Pair<TKey, TValue> popback() = 0;
    virtual void replace(TKey K, TValue NewV) = 0;
    virtual void remove(TKey K) = 0;
    virtual ~ITable() = default;
};

// ���������� ����� UnorderedTable
template<typename TKey, typename TValue>
class UnorderedTable : public ITable<TKey, TValue> {
private:
    TList<Pair<TKey, TValue>> list;

public:
    UnorderedTable() {}

    // �������� ������������
    UnorderedTable<TKey, TValue>& operator=(const UnorderedTable<TKey, TValue>& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    // ���������� �������� � �������
    void pushback(TKey K, TValue V) override {
        for (const auto& p : list) {
            if (p.key == K) {
                throw std::invalid_argument("Key already exists in the table");
            }
        }
        Pair<TKey, TValue> p;
        p.key = K;
        p.Val = V;
        list.push_back(p);
    }

    // ���������� ���������� �������� �� �������
    Pair<TKey, TValue> popback() override {
        if (list.empty()) {
            throw std::out_of_range("List is empty");
        }
        Pair<TKey, TValue> p = list.back();
        list.pop_back();
        return p;
    }

    // ������ �������� �������� �� �����
    void replace(TKey K, TValue NewV) override {
        for (auto& p : list) {
            if (p.key == K) {
                p.Val = NewV;
                return;
            }
        }
    }

    // �������� �������� �� �����
    void remove(TKey K) override {
        auto it = list.begin();
        while (it != list.end()) {
            if (it->key == K) {
                list.erase(it);
                return;
            }
            ++it;
        }
    }

    // ������ ����������� �������
    void printtable() const override {
        for (const auto& p : list) {
            std::cout << "Key: " << p.key << ", Value: " << p.Val << std::endl;
        }
    }
};

// ���������� ����� UnorderedTableOnArray
template<typename TKey, typename TValue>
class UnorderedTableOnArray : public ITable<TKey, TValue> {
private:
    size_t size;  // ������ �������
    size_t located;  // ������� ������ ������������ ��������
    Pair<TKey, TValue>* parr;  // ��������� �� ������ ���

public:
    // �����������
    UnorderedTableOnArray(size_t s_) : size(s_), located(0) {
        if (s_ <= 0) {
            size = 1;
        }
        else {
            size = s_;
        }
        parr = new Pair<TKey, TValue>[size];
    }

    // ����������� �����������
    UnorderedTableOnArray(const UnorderedTableOnArray<TKey, TValue>& other)
        : size(other.size), located(other.located) {
        parr = new Pair<TKey, TValue>[size];
        for (size_t i = 0; i < located; ++i) {
            parr[i] = other.parr[i];
        }
    }

    // ����������
    ~UnorderedTableOnArray() {
        delete[] parr;
    }

    // �������� ������������
    UnorderedTableOnArray<TKey, TValue>& operator=(const UnorderedTableOnArray<TKey, TValue>& other) {
        if (this != &other) {
            delete[] parr;

            size = other.size;
            located = other.located;
            parr = new Pair<TKey, TValue>[size];
            for (size_t i = 0; i < located; ++i) {
                parr[i] = other.parr[i];
            }
        }
        return *this;
    }

    // ���������� �������� � �������
    void pushback(TKey K, TValue V) override {
        for (size_t i = 0; i < located; ++i) {
            if (parr[i].key == K) {
                throw std::invalid_argument("Key already exists in the table");
            }
        }
        if (located == size) {
            throw std::out_of_range("Array is full");
        }
        Pair<TKey, TValue> p;
        p.key = K;
        p.Val = V;
        parr[located++] = p;
    }

    // ���������� ���������� �������� �� �������
    Pair<TKey, TValue> popback() override {
        if (located == 0) {
            throw std::out_of_range("Array is empty");
        }
        return parr[--located];
    }

    // ������ �������� �������� �� �����
    void replace(TKey K, TValue NewV) override {
        for (size_t i = 0; i < located; ++i) {
            if (parr[i].key == K) {
                parr[i].Val = NewV;
                return;
            }
        }
    }

    // �������� �������� �� �����
    void remove(TKey K) override {
        for (size_t i = 0; i < located; ++i) {
            if (parr[i].key == K) {
                for (size_t j = i; j < located - 1; ++j) {
                    parr[j] = parr[j + 1];
                }
                --located;
                return;
            }
        }
    }

    // ������ ����������� �������
    void printtable() const override {
        for (size_t i = 0; i < located; ++i) {
            std::cout << "Key: " << parr[i].key << ", Value: " << parr[i].Val << std::endl;
        }
    }
};
