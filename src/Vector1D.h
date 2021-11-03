#pragma once

template <class T>
class Vector1D {
public:
    T* arr;
    int arr_lim[2];
    int arr_size;
    bool allocated;

    Vector1D();
    ~Vector1D();
    
    bool allocate(int id0, int id1);
    bool deallocate();
    
    bool isAllocated() { return allocated; }
    int size() { return arr_size; }
    int L() { return arr_lim[0]; }
    int U() { return arr_lim[1]; }
    
    T &operator [](int i);
};

template <class T>
Vector1D<T>::Vector1D()
{
    arr_lim[0] = 0;
    arr_lim[1] = 0;
    arr_size = 0;
    allocated = false;
}

template <class T>
Vector1D<T>::~Vector1D()
{
    if (allocated) {
        delete[] arr;
        arr_lim[0] = 0;
        arr_lim[1] = 0;
        arr_size = 0;
        allocated = false;
    }
}

template <class T>
bool Vector1D<T>::allocate(int id0, int id1)
{
    if (not(allocated))
    {
        if (id1 >= id0)
        {
            arr = new T[id1-id0];
            arr_lim[0] = id0;
            arr_lim[1] = id1;
            arr_size = id1-id0;
            allocated = true;
            return true;
        }
    }
    return false;
}

template <class T>
bool Vector1D<T>::deallocate()
{
    if (allocated)
    {
        delete [] arr;
        arr_lim[0] = 0;
        arr_lim[1] = 0;
        arr_size = 0;
        allocated = false;
        return true;
    }
    return false;
}

template <class T>
inline T& Vector1D<T>::operator [](int i)
{
    return *(arr + i - arr_lim[0]);
}