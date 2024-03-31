/*
COPYRIGHT AGOEV TAMERLAN KMBO-05-23
*/

#include "Vector.hpp"

template<typename T>
T min(T a, T b) {
    if (a>b) return b;
    return a;
}



Vector::Vector(const Vector &v) {
    if (v.size()!=0) {
        _data = new T[v.size()];
        std::memcpy(_data, v.array(), v.size()*sizeof(T));
        _size = v.size(); _capacity = v.size();
    }
}


Vector::Vector(Vector v, size_t size) {
    if (v.size()!=0) {
        _data = new T[min(size, v.size())];
        std::memcpy(_data, v.array(), min(size, v.size())*sizeof(T));
        _size = min(size, v.size()); _capacity = min(size, v.size());
    }
}

Vector::Vector(T* array, size_t size_in, float coef) {
    koef = coef;
    if (size_in != 0) {
        _size = size_in; _capacity = size_in;
        _data = new T[_capacity];
        std::memcpy(_data, array, sizeof(T)*_size);
    }
}

Vector::Vector(const T* array, const size_t size_in, float coef) {
    koef = coef;
    if (size_in != 0) {
        _size = size_in; _capacity = size_in;
        _data = new T[_capacity];
        std::memcpy(_data, array, sizeof(T)*_size);
    }
}


Vector::Vector(Vector &&other) {
    _data = other.array();
    _size = other.size();
    _capacity = other.capacity();
    other._data = nullptr; other._size=0; other._capacity=0;
}


Vector::~Vector() {
    if (_data!=nullptr) {delete[] _data; _data=nullptr;}
}






T& Vector::operator[] (size_t index) {
    if (_size==0) throw std::invalid_argument("Vector is empty");
    if (index>=_size) throw std::invalid_argument("Index out of range");
    if (_data==nullptr) throw std::invalid_argument("Vector is empty");
    return _data[index];
}

const T& Vector::operator[](size_t index) const {
    if (_size==0) throw std::invalid_argument("Vector is empty");
    if (index>=_size) throw std::invalid_argument("Index out of range");
    if (_data==nullptr) throw std::invalid_argument("Vector is empty");
    return (_data[index]);
}


void Vector::operator+ (Vector v) {
    if (_data==nullptr) {
        _data=v.array();
        return;
    }
    if (v.array()==nullptr) {
        return;
    }
    T* buff = new T[_capacity+v.capacity()];
    std::memcpy(buff, _data, _size*sizeof(T));
    std::memcpy(buff+_size, v.array(), v.size()*sizeof(T));
    
    delete[] _data;
    _data = buff;
    _size += v.size();
    _capacity += v.capacity();
}


Vector& Vector::operator=(const Vector& other) {
    if (*this != other) {
        if (_data!=nullptr) {delete[] _data;_data = nullptr;}
        if (other.size()!=0) {
            _data = new T[other.size()];
            std::memcpy(_data, other.array(), other.size()*sizeof(T));
        }
        _size = other.size(); _capacity = other.size();
    } //else {std::cout << "SELFASSIGNEMENT COPY\n";}
    return *this;
}


Vector& Vector::operator=(Vector&& other) {
    if (*this!=other) {
        if (_data!=nullptr) {delete[] _data;}
        _data = other.array();
        _size = other.size();
        _capacity = other.capacity();
        other._data = nullptr; other._size=0; other._capacity=0;
    } //else {std::cout << "SELFASSIGNEMENT MOVE\n";}
    return *this;
}


bool Vector::operator==(const Vector& other) {
    if (_size!=other.size()) return false;
    for (size_t i=0; i<_size; i++) {
        if (_data[i] != other[i]) return false;
    }
    return true;
}


bool Vector::operator!=(const Vector& other) {
    return !(*this==other);
}




void Vector::addBack (const T& value) {
    if (_capacity==0) {
        _data = new T[(size_t)koef];
        _data[0] = value;
        _size=1; 
        _capacity = (size_t)koef;
        return;
    }

    if (_size < _capacity) {
        _data[_size] = value; _size++; return;
    }

    size_t cap_new = _capacity*koef;
    T* buff = new T[cap_new];
    std::memcpy(buff, _data, _size*sizeof(T));

    delete[] _data;
    _data = buff;
    _data[_size] = value;
    _size++; _capacity=cap_new;
    return;
}


void Vector::addFront (const T& value) {
    if (_capacity==0) {
        _data = new T[(size_t)koef];
        _data[0] = value;
        _size=1; 
        _capacity = (size_t)koef;
        return;
    }

    if (_size < _capacity) {
        std::memcpy(_data+1, _data, _size*(sizeof(T)));
        _data[0] = value; _size++; return;
    }

    size_t cap_new = _capacity*koef;
    T* buff = new T[cap_new];
    std::memcpy(buff+1, _data, _size*sizeof(T));

    delete[] _data;
    _data = buff;
    _data[0] = value;
    _size++; _capacity=cap_new;
    return;
}

void Vector::pushBack (const T& value) {
    //std::cout << start_capacity << " " << koef << " " << _size << " " << _capacity << "\n";
    addBack(value);
    //std::cout << start_capacity << " " << koef << " "<< _size << " " << _capacity << "\n\n";
}


void Vector::pushFront (const T& value) {
    addFront(value);
}

void Vector::insert (const T& value, size_t index) {
    if (_capacity==0) {
        _data = new T[index+1];
        _data[index] = value;
        _size = index+1; _capacity=index+1;
        return;
    }
    if (index>_size) throw std::invalid_argument("Index out of range");
    

    if (_size == _capacity) {
        size_t cap_new = (size_t) _capacity*koef + 1;
        T* buff = new T[cap_new];
        std::memcpy(buff, _data, _size*sizeof(T));
        delete[] _data;
        _data = buff; _capacity = cap_new;
    }
    std::memcpy(_data+index+1, _data+index, (_size-index)*sizeof(T));
    _data[index] = value;
    _size++;
}


void Vector::insert (const T* values, size_t size, size_t index) {
    if (size==0) return;

    if (_capacity==0) {
        _data = new T[size+index];
        std::memcpy(_data+index, values, size*sizeof(T));
        _size = size+index; _capacity=size+index;
        return;
    }
    if (index>_size) throw std::invalid_argument("Index out of range");
    
    if (_size+size > _capacity) {
        T* buff = new T[_size+size];
        std::memcpy(buff, _data, index*sizeof(T));
        std::memcpy(buff+index, values, size*sizeof(T));
        std::memcpy(buff+index+size, _data+index, (_size-index)*sizeof(T));
        delete[] _data;
        _data = buff;
        _size = _size+size; _capacity=_size+size;
        return;
    }

    std::memcpy(_data+index+size, _data+index, (_size-index)*sizeof(T));
    std::memcpy(_data+index, values, size*sizeof(T));
    _size += size;
}


void Vector::insert (const Vector& Vectortor, size_t index) {
    if (Vectortor.size()==0) return;

    if (_capacity==0) {
        _data = new T[Vectortor.capacity()+index];
        std::memcpy(_data+index, Vectortor.array(), Vectortor.size()*sizeof(T));
        _size = Vectortor.size()+index; _capacity = Vectortor.capacity()+index;
    }
    if (index>_size) throw std::invalid_argument("Index out of range");

    if (_size + Vectortor.size() > _capacity) {
        T* buff = new T[_size+Vectortor.size()];
        std::memcpy(buff, _data, index*sizeof(T));
        std::memcpy(buff+index, Vectortor.array(), Vectortor.size()*sizeof(T));
        std::memcpy(buff+index+Vectortor.size(), _data+index, (_size-index)*sizeof(T));
        delete[] _data;
        _data = buff;
        _size = _size+Vectortor.size(); _capacity=_size+Vectortor.size();
        return;
    }

    std::memcpy(_data+index+Vectortor.size(), _data+index, (_size-index)*sizeof(T));
    std::memcpy(_data+index, Vectortor.array(), Vectortor.size()*sizeof(T));
    _size += Vectortor.size();
}




void Vector::pop() {
    pop(_size-1);
}


void Vector::pop(size_t index) {
    if (_size==0) throw std::runtime_error("Vector is empty");
    if (index>=_size) throw std::invalid_argument("Index out of range");
    if (_size!=1) std::memcpy(_data+index, _data+index+1, (_size-index-1)*sizeof(T));
    _size--;
}


void Vector::popBack() {pop(_size-1);}


void Vector::popFront() {pop(0);}



void Vector::drop(size_t elems_remain) {
    if (elems_remain>_capacity) throw std::invalid_argument("Index out of range");

    size_t cap_new = elems_remain;
    T* buff;
    if (elems_remain==0) {
        buff=nullptr;
    } else {
        buff = new T[cap_new];
        std::memcpy(buff, _data, min(_size, elems_remain)*sizeof(T));
    }
    
    delete[] _data;
    _data = buff; _capacity = cap_new; _size = min(_size, elems_remain);
}


void Vector::shrink() {
    if (_data!=nullptr && _size!=0) {
        T* buff = new T[_size];
        std::memcpy(buff, _data, _size*sizeof(T));
        delete[] _data;
        _data = buff;
        _capacity = _size;
    }
}

void Vector::shrinkToFit() {
    shrink();
}



void Vector::erase(size_t index, size_t count) {
    if (_capacity==0 || _size==0 || count==0) return;
    if (count+index>_size) {
        _size = index; return;
    }

    std::memcpy(_data+index, _data+index+count, (_size-index-count)*sizeof(T));
    _size-=count;
}


void Vector::eraseBetween(size_t begin, size_t end) {
    if (_capacity==0 || _size==0) return;
    if (begin>=_size || begin>=end) return;//throw std::invalid_argument("Index out of range");
    if (end>=_size) {
        _size = begin+1; return;
    }

    std::memcpy(_data+begin, _data+end, (_size-end)*sizeof(T));
    _size -= end-begin;
}


bool Vector::in(T value) const {
    if (_capacity==0 || _size==0) return false;
    for (size_t i=0; i<_size; i++) {
        if (_data[i]==value) return true;
    }
    return false;
}


size_t Vector::find(T value) const {
    if (_capacity==0 || _size==0) throw std::runtime_error("Vectortor is empty");
    for (size_t i=0; i<_size; i++) {
        if (_data[i]==value) return i;
    }
    throw std::runtime_error("Value not in Vectortor");
}


std::tuple<size_t, bool> Vector::infind(T value) const {
    if (_capacity==0 || _size==0) return {0, false};
    for (size_t i=0; i<_size; i++) {
        if (_data[i]==value) return {i, true};
    }
    return {_size-1, false};
}


void Vector::reserve(size_t cap) {
    if (_capacity>=cap) return;
    if (_capacity==0) {
        _data = new T[cap];
        _capacity = cap;
        return;
    }
    if (cap == 0) {
        delete[] _data;
        _capacity = 0; _size = 0; _data = nullptr;
        return;
    }

    T* buff = new T[cap];
    std::memcpy(buff, _data, min(_size, cap)*sizeof(T));
    delete[] _data;
    _capacity = cap; _size = min(_size, cap); _data = buff;
}

bool Vector::empty() const {return (_size==0);}

size_t Vector::capacity() const {return _capacity;}


size_t Vector::size() const {return _size;}


T* Vector::array() const {return _data;}


Vector::Iterator::Iterator(T* ptr) {
    _ptr = ptr;
}


T& Vector::Iterator::operator*() {return *_ptr;}


const T& Vector::Iterator::operator*() const {return *_ptr;}


T* Vector::Iterator::operator->() {return _ptr;}


const T* Vector::Iterator::operator->() const {return _ptr;}


typename Vector::Iterator Vector::Iterator::operator++() {
    ++_ptr;
    return *this;
}


typename Vector::Iterator Vector::Iterator::operator++(int) {
    _ptr++;
    return *this;
}

typename Vector::Iterator Vector::Iterator::operator--() {
    Iterator p(_ptr-1);
    return p;
}


typename Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator p(_ptr-1);
    return p;
}


typename Vector::Iterator Vector::Iterator::operator+(int i) {
    Iterator p(_ptr+i);
    return p;
}

typename Vector::Iterator Vector::Iterator::operator-(int i) {
    Iterator p(_ptr-i);
    return p;
}

typename Vector::Iterator Vector::Iterator::operator+=(int i) {
    _ptr += i;
    return *this;
}

typename Vector::Iterator Vector::Iterator::operator-=(int i) {
    _ptr -= i;
    return *this;
}




bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return (_ptr==other.operator->());
}


bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return (_ptr!=other.operator->());
}

typename Vector::Iterator Vector::begin() {return Iterator(_data);}


typename Vector::Iterator Vector::end() {return Iterator(_data+_size);}



void Vector::print() {
    for (size_t i=0; i<_size; i++) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl;
}