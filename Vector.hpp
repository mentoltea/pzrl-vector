/*
COPYRIGHT AGOEV TAMERLAN KMBO-05-23
*/

#ifndef _MY_Vector_
#define _MY_Vector_

#include <cstring>
#include <tuple>
#include <iostream>

using T=double;
//template<typename T>
//template<int>


class Vector {
    T *_data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    float koef = 2;
    int start_capacity = 10;
public:
    Vector() = default;
    explicit Vector(const Vector &v);
    Vector(Vector v, size_t size);
    Vector(T* array, size_t size, float coef = 2.0f);
    Vector(const T* array, const size_t size, float coef = 2.0f);
    Vector(Vector&& other);
    //friend Vector::Vector(Vector&& other);
    ~Vector();

    T& operator[] (size_t index);
    const T& operator[](size_t index) const;
    void operator+ (Vector v);
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    //friend Vector& Vector::operator=(Vector&& other);
    bool operator==(const Vector& other);
    bool operator!=(const Vector& other);

    void addBack(const T& value);
    void addFront(const T& value);
    void pushBack(const T& value);
    void pushFront(const T& value);

    void insert(const T& value, size_t index);
    void insert(const T* values, size_t size, size_t index);
    void insert(const Vector& Vector, size_t index);

    void pop();
    void pop(size_t index);
    void popBack();
    void popFront();

    //drops everything after elems_remain element(including)
    void drop(size_t elems_remain);
    void shrink();
    void shrinkToFit();
    //erases count elements after pos(excluding)
    void erase(size_t pos, size_t count=1);
    //erases from begin(including) to end(excluding)
    void eraseBetween(size_t begin, size_t end);

    bool in(T value) const;
    //find index (error if not in the Vectortor)
    size_t find(T value) const;
    //find index. returns tuple<size_t, bool> - index and if found
    std::tuple<size_t, bool> infind(T value) const;
    //limits capacity with cap
    void reserve(size_t cap);
    bool empty() const;


    size_t capacity() const;
    size_t size() const;
    T* array() const;

    class Iterator
    {
        T* _ptr;
    public:
        explicit Iterator(T* ptr);
    
        T& operator*();
    
        const T& operator*() const;
    
        T* operator->();
    
        const T* operator->() const;
    
        Iterator operator++();
    
        Iterator operator++(int);

        Iterator operator--();

        Iterator operator--(int);

        Iterator operator+(int i);
        Iterator operator-(int i);
        Iterator operator+=(int i);
        Iterator operator-=(int i);
    
        bool operator==(const Iterator& other) const;
    
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();

    void print();
};




#endif