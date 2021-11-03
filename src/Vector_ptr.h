#pragma once

template <class T>
struct Vector_ptr {
private:
    // Attributes
    T* arr;
    T* arr_rebounded;
    int lim[2];
    int size;
    bool allocated;
public:
    // Methods
    Vector_ptr();
    ~Vector_ptr();
    
    bool allocate(int i0, int i1);
    bool deallocate();
    
    T &operator [](int i);
};

template <class T>
Vector_ptr<T>::Vector_ptr()
{
    lim[0] = 0;
    lim[1] = 0;
    size = 0;
    allocated = false;
}

template <class T>
Vector_ptr<T>::~Vector_ptr()
{
    (*this).deallocate();
}

template <class T>
bool Vector_ptr<T>::allocate(int i0, int i1)
{
    if (not(allocated))
    {
        if (i1 >= i0)
        {
            arr = new T[i1-i0];
            lim[0] = i0;
            lim[1] = i1;
            size = i1-i0;
            allocated = true;
            arr_rebounded = arr - i0;
            return true;
        }
    }
    return false;
}

template <class T>
bool Vector_ptr<T>::deallocate()
{
    if (allocated)
    {
        delete [] arr;
        arr = NULL;
        arr_rebounded = NULL;
        lim[0] = 0;
        lim[1] = 0;
        size = 0;
        allocated = false;
        return true;
    }
    return false;
}

template <class T>
inline T& Vector_ptr<T>::operator [](int i)
{
    return arr_rebounded[i];
}