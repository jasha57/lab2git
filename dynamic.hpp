#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP 1

#include <memory.h>
#include <stdlib.h>
#include <algorithm>

template<typename T>
class DynamicArray {
public:
    DynamicArray(T*, int);
    DynamicArray(int);
    DynamicArray();
    DynamicArray(const DynamicArray<T> &);
    ~DynamicArray();
    T Get(int) const;
    int GetSize() const;
    void Set(int,T);
    void Resize(int);
    void Prepend(T item);
    void InsertAt(int,T);
    DynamicArray<T> * Concat(DynamicArray<T> *);
    DynamicArray<T> * Getsubarray(int, int);
private:
    T* mass;
    int len;
    int cap;
};


template<typename T>
DynamicArray<T>::DynamicArray(T* item,int count){
    if(item == nullptr) {
        mass = nullptr;
        len = 0;
        cap = 0;
    }else {
        mass = new T[count];
        len = count;
        cap = count;
        memcpy(mass, item, count*sizeof(T));
    }

    #ifdef DEBUG 
        std::cerr << "Generate Object type DynamicArray<T> with constructor (T**, size)" << mass << " " << len << " " << cap << std::endl;
        std::cerr << "Type of T" << typeid(mass[0]).name() << std::endl;
    #endif
}

template<typename T>
DynamicArray<T>::DynamicArray(){
    mass = nullptr;
    len = 0;
    cap = 0;

    #ifdef DEBUG 
        std::cerr << "Generate Object type DynamicArray<T> with constructor ()" << mass << " " << len << " " << cap << std::endl;
        T x;
        std::cerr << "Type of T" << typeid(x).name() << std::endl;
        x.~T();
    #endif
}

template<typename T>
DynamicArray<T>::DynamicArray(int size){
    if(size == 0) {
        throw "Not array creative";
    }
    mass = new T[size];
    len = size;
    cap = size;

    #ifdef DEBUG 
        std::cerr << "Generate Object type DynamicArray<T> with constructor (size)" << mass << " " << len << " " << cap << std::endl;
        std::cerr << "Type of T" << typeid(mass[0]).name() <<std::endl;
    #endif
}

template<typename T>
DynamicArray<T>::~DynamicArray(){
    if(mass != nullptr){

        #ifdef DEBUG 
            std::cerr << "Destroy Object type DynamicArray<T>" << mass << " " << len << " " << cap << std::endl;
            std::cerr << "Type of T" << typeid(mass[0]).name() << std::endl;
        #endif

        delete[] mass;
        mass = nullptr;
    }

}
template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &arr){
    mass = new T[arr.cap];
    cap = arr.cap;
    len = arr.len;
    memcpy(mass, arr.mass, len * sizeof(T));

    #ifdef DEBUG 
        std::cerr << "Generate copy Object type DynamicArray<T>" << arr.mass << " " << mass << " " << len << " " << cap << std::endl;
        std::cerr << "Type of T" << typeid(mass[0]).name() <<std::endl;
    #endif
}

template<typename T>
T DynamicArray<T>::Get(int ind) const{
    if(ind >= len || ind < 0){
        throw "IndexOutOfRange";
    }
    return mass[ind];
}

template<typename T>
int DynamicArray<T>::GetSize() const{
    return len;
}

template<typename T>
void DynamicArray<T>::Set(int ind, T item) {
    if(ind >= len || ind < 0){
        throw "IndexOutOfRange";
    }
    mass[ind] = item;
}

template<typename T>
void DynamicArray<T>::Resize(int newSize) {
    if(len == 0){
        int size = newSize;
        mass = new T[size];
        cap = size;
    }else if(newSize > cap) {
        int size = std::max<int>(2 * len, newSize);
        T* newdata = new T[size];
        memcpy(newdata, mass, len * sizeof(T));
        delete [] mass;
        mass = newdata;
        cap = size;
    }
    len = newSize;
}
template<typename T>
void DynamicArray<T>::Prepend(T item) {
    if(GetSize() == 0) {
        Resize(1);
        mass[0] = item;
    } else {
        Resize(GetSize() + 1);
        memmove(mass + 1, mass, (len - 1) * sizeof(T));
        mass[0] = item;
    }
}

template<typename T>
void DynamicArray<T>::InsertAt(int ind,T item) {
    if(ind == GetSize()) {
        Resize(GetSize() + 1);
        Set(GetSize() - 1, item);
    } else if (ind > GetSize() || ind < 0){
        throw "IndexOutOfRange";
    }else {
        Resize(GetSize() + 1);
        memmove(mass + ind + 1, mass + ind, (GetSize() - ind - 1) * sizeof(T));
        Set(ind, item);
    }
}
template<typename T>
DynamicArray<T> * DynamicArray<T>::Concat(DynamicArray<T> * list){
    Resize(GetSize() + list->GetSize());
    memcpy(mass + GetSize(), list->mass, list->GetSize() * sizeof(T));
    return this;
}
template<typename T>
DynamicArray<T> * DynamicArray<T>::Getsubarray(int start , int end){
    if(start < 0 or start >= len or end >= len or end < 0 or start > end) {
        throw "IndexOutOfRange";
        return nullptr;
    }
    DynamicArray<T> * res = new DynamicArray<T>();
    res->mass = mass + start;
    res-> len = end - start + 1;
    res->cap = end - start + 1;
    return res;

}

#endif