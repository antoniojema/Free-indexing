#pragma once

#include "Vector1D.h"

template <class T>
class Vector2D
{
public:
    Vector1D<T> *arr;
    int arr_lim[2][2];
    int arr_size[2];
    bool allocated;

    Vector2D();
    ~Vector2D();

    bool allocate(int x0, int y0, int x1, int y1);
    bool deallocate();

    bool isAllocated() { return allocated; };
    int sizeX() { return arr_size[0]; }
    int sizeY() { return arr_size[1]; }
    int XL() { return arr_lim[0][0]; }
    int XU() { return arr_lim[0][1]; }
    int YL() { return arr_lim[1][0]; }
    int YU() { return arr_lim[1][1]; }

    Vector1D<T>& operator [](int i);
};

template <class T>
Vector2D<T>::Vector2D()
{
    arr_lim[0][0] = 0; arr_lim[0][1] = 0; arr_size[0] = 0;
    arr_lim[1][0] = 0; arr_lim[1][1] = 0; arr_size[1] = 0;
    allocated = false;
}

template <class T>
Vector2D<T>::~Vector2D()
{
    if (allocated) {
        arr_lim[0][0] = 0; arr_lim[0][1] = 0; arr_size[0] = 0;
        arr_lim[1][0] = 0; arr_lim[1][1] = 0; arr_size[1] = 0;
        for (int i = 0; i < arr_size[0]; i++)
        {
            arr[i].deallocate();
        }
        delete[] arr;
        allocated = false;
    }
}

template <class T>
bool Vector2D<T>::allocate(int x0, int y0, int x1, int y1)
{
    if (not(allocated))
    {
        if (x1 >= x0 && y1 >= y0)
        {
            arr_lim[0][0] = x0; arr_lim[0][1] = x1; arr_size[0] = x1-x0;
            arr_lim[1][0] = y0; arr_lim[1][1] = y1; arr_size[1] = y1-y0;
            arr = new Vector1D<T>[x1-x0];
            for (int i = 0; i < arr_size[0]; i++)
            {
                arr[i].allocate(y0, y1);
            }
            allocated = true;
            return true;
        }
    }
    return false;
}

template <class T>
bool Vector2D<T>::deallocate()
{
    if (allocated)
    {
        arr_lim[0][0] = 0; arr_lim[0][1] = 0; arr_size[0] = 0;
        arr_lim[1][0] = 0; arr_lim[1][1] = 0; arr_size[1] = 0;
        for (int i = 0; i < arr_size[0]; i++)
        {
            arr[i].deallocate();
        }
        delete[] arr;
        allocated = false;
        return true;
    }
    return false;
}

template <class T>
inline Vector1D<T>& Vector2D<T>::operator [](int i)
{
    return *(arr + i - arr_lim[0][0]);
}