// Copyright 2024 Mezhuev Maksim

#include "../lib_list/list.h"

template<typename TKey, typename TValue>
struct Pair {
    TKey key;
    TValue Val;
};

template<typename TKey, typename TValue>
class ITable {
    Pair<TKey, TValue> pair;
public:
    virtual void pushback(TKey K, TValue V) = 0;
    virtual void printtable() = 0;
    virtual Pair<TKey, TValue> popup() = 0;
    virtual void replace(TKey K, TValue NewV) = 0;
};

template<typename TKey, typename TValue>
class UnorderedTable : public ITable<TKey, TValue> {
private:
    TList<Pair<TKey, TValue>> list;  // ���������� std::list ��� �������� ���������

public:
    UnorderedTable() {}

    void pushback(TKey K, TValue V) override {
        Pair<TKey, TValue> p;
        p.key = K;
        p.Val = V;
        list.push_back(p);  // ��������� ������� � ����� ������
    }

    Pair<TKey, TValue> popup() override {
        if (list.empty()) {
            throw std::out_of_range("List is empty");
        }
        Pair<TKey, TValue> p = list.back();  // �������� ��������� �������
        list.pop_back();  // ������� ��������� �������
        return p;
    }

    void replace(TKey K, TValue NewV) override {
        for (auto& p : list) {
            if (p.key == K) {
                p.Val = NewV;  // �������� ��������
                return;
            }
        }
    }

    void printtable() const override {
        for (const auto& p : list) {
            std::cout << "Key: " << p.key << ", Value: " << p.Val << std::endl;
        }
    }
};

template<typename TKey, typename TValue>
class UnorderedTableOnArray : public ITable<TKey, TValue> {
private:
    size_t size;
    size_t located;
    Pair<TKey, TValue>* parr;

public:
    UnorderedTableOnArray(size_t s_) : size(s_), located(0) {
        if (s_ <= 0) {
            size = 1;
        }
        else {
            size = s_;
        }
        parr = new Pair<TKey, TValue>[size];  // ������� ������ ���
    }

    ~UnorderedTableOnArray() {
        delete[] parr;  // ����������� ������
    }

    void pushback(TKey K, TValue V) override {
        if (located == size) {
            throw std::out_of_range("Array is full");
        }
        Pair<TKey, TValue> p;
        p.key = K;
        p.Val = V;
        parr[located++] = p;  // ��������� ������� � ����������� �������
    }

    Pair<TKey, TValue> popup() override {
        if (located == 0) {
            throw std::out_of_range("Array is empty");
        }
        return parr[--located];  // ��������� ������� � ���������� ��������� �������
    }

    void replace(TKey K, TValue NewV) override {
        for (size_t i = 0; i < located; ++i) {
            if (parr[i].key == K) {
                parr[i].Val = NewV;  // �������� ��������
                return;
            }
        }
    }

    void printtable() const override {
        for (size_t i = 0; i < located; ++i) {
            std::cout << "Key: " << parr[i].key << ", Value: " << parr[i].Val << std::endl;
        }
    }
};