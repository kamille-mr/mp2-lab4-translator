// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector {

protected:

    size_t sz;
    T* pMem;

public:

    TDynamicVector(size_t size = 1) : sz(size) {

        if (sz == 0) {

            throw "Vector size should be greater than zero";
        }
        if (sz > MAX_VECTOR_SIZE) {

            throw "error";
        }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }

    TDynamicVector(T* arr, size_t s) : sz(s) {

        if (sz == 0) {

            throw "Vector size should be greater than zero";
        }
        if (sz > MAX_VECTOR_SIZE) {

            throw "error";
        }
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) {

        this->sz = v.sz;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++) {

            pMem[i] = v.pMem[i];
        }
    }

    TDynamicVector(TDynamicVector&& v) noexcept {

        this->pMem = v.pMem;
        v.pMem = nullptr;
        this->sz = v.sz;
        v.sz = 0;
    }

    ~TDynamicVector() {

        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v) {

        if (this == &v) {

            return *this;
        }
        this->sz = v.sz;
        delete[] this->pMem;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++) {

            pMem[i] = v.pMem[i];
        }
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept {

        if (this == &v) {

            return *this;
        }
        delete[] pMem;
        this->pMem = v.pMem;
        v.pMem = nullptr;
        this->sz = v.sz;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept { 

        return sz;
    }

    // индексация
    T& operator[](size_t ind) {

        if (ind < 0 || ind >= sz){

            throw "error";
        }
        return pMem[ind]; 
       
    }

    const T& operator[](size_t ind) const {

        if (ind < 0 || ind >= sz) {

            throw "error";
        }
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind) {

        if (ind < 0 || ind >= sz) {

            throw "error";
        }
        return pMem[ind];
    }

    const T& at(size_t ind) const {

        if (ind < 0 || ind >= sz) {

            throw "error";
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept {

        if (this == &v) {

            return true;
        }
        if (sz != v.sz) {

            return false;
        }
        for (int i = 0; i < sz; i++) {

            if (pMem[i] != v.pMem[i]) {

                return false;
            }
        }
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept {

        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val) {

        TDynamicVector res(*this);
        for (int i = 0; i < sz; i++) {


            res.pMem[i] = res.pMem[i] + val;
        }
        return res;
    }

    TDynamicVector operator-(T val) {

        TDynamicVector res(this->sz);
        for (int i = 0; i < sz; i++) {

            res[i] = pMem[i] - val;
        }
        return res;
    }

    TDynamicVector operator*(T val) {

        TDynamicVector res(this->sz);
        for (int i = 0; i < sz; i++) {

            res[i] = pMem[i] * val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) {

        if (sz == v.sz) {

            TDynamicVector res(this->sz);
            for (int i = 0; i < sz; i++) {

                res.pMem[i] = pMem[i] + v.pMem[i];
            }
            return res;
        }
        else {

            throw "error";
        }
    }

    TDynamicVector operator-(const TDynamicVector& v) {

        if (sz == v.sz) {

            TDynamicVector<T> res(this->sz);
            for (int i = 0; i < sz; i++) {

                res.pMem[i] = pMem[i] - v.pMem[i];
            }
            return res;
        }
        else {

            throw "error";
        }
    }

    T operator*(const TDynamicVector& v) {

        if (sz == v.sz) {

            T res = pMem[0] * v.pMem[0];
            for (int i = 1; i < sz; i++) {

                res = res + pMem[i] * v.pMem[i];
            }
            return res;
        }
        else {

            throw "error";
        }
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {

        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v) {

        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {

        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {

    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {

        if (sz < MAX_MATRIX_SIZE) {

            for (size_t i = 0; i < sz; i++) {

                pMem[i] = TDynamicVector<T>(sz);
            }
        }
        else {

            throw "error";
        }
    }

    size_t size() {

        return sz;
    }
    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept {//!!!!!!!

        if (this == &m) {

            return true;
        }
        if (sz!= m.sz) {

            return false;
        }
        for (int i = 0; i < sz; i++) {

            if (pMem[i] != m.pMem[i]) {

                return false;
            }
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val) {

        TDynamicMatrix res(*this);
        for (int i = 0; i < sz; i++) {

            res.pMem[i] = pMem[i] * val;
        }
        return res;

    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {

        TDynamicMatrix res(*this);
        for (int i = 0; i < sz; i++) {

            res.pMem[i] = pMem[i] * v.pMem[i];
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) {

        if (sz == m.sz) {

            TDynamicMatrix res(*this);
            for (int i = 0; i < sz; i++) {

                res.pMem[i] = pMem[i] + m.pMem[i];
            }
            return res;
        }
        else {

            throw "error";
        }
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m) {

        if (sz == m.sz) {

            TDynamicMatrix res(*this);
            for (int i = 0; i < sz; i++) {

                res.pMem[i] = pMem[i] - m.pMem[i];
            }
            return res;
        }
        else {

            throw "error";
        }
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) {

        if (sz == m.sz) {

            TDynamicMatrix res(*this);
            for (int i = 0; i < sz; i++) {

                res.pMem[i] = pMem[i] * m.pMem[i];
            }
            return res;
        }
        else {

            throw "error";
        }
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v) {

        for (size_t i = 0; i < v.sz; i++)
            cin >> v.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {

        for (size_t i = 0; i < v.sz; i++)
            cout << v.pMem[i] << "\n";
        return ostr;
    }
};

#endif