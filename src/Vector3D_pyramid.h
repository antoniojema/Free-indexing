#pragma once

#include "Vector2D.h"

template <class T>
class Vector3D_pyramid
{
private:
    Vector2D<T>* arr;
    int arr_lim[3][2];
    int arr_size[3];
    bool allocated;

public:
    Vector3D_pyramid();
    ~Vector3D_pyramid();

    bool allocate(int x0, int y0, int z0, int x1, int y1, int z1);
    bool deallocate();
    
    void all(T value);

    bool isAllocated() { return allocated; };
    int size(int xyz) { return arr_size[xyz]; }
    int sizeX() { return arr_size[0]; }
    int sizeY() { return arr_size[1]; }
    int sizeZ() { return arr_size[2]; }
    int lim(int xyz, int lu) { return arr_lim[xyz][lu]; }
    int XL() { return arr_lim[0][0]; }
    int XU() { return arr_lim[0][1]; }
    int YL() { return arr_lim[1][0]; }
    int YU() { return arr_lim[1][1]; }
    int ZL() { return arr_lim[2][0]; }
    int ZU() { return arr_lim[2][1]; }

    Vector2D<T>& operator [](int i);
    Vector3D_pyramid<T>& operator= (T value);
};

template <class T>
Vector3D_pyramid<T>::Vector3D_pyramid()
{
    arr_lim[0][0] = 0; arr_lim[0][1] = 0; arr_size[0] = 0;
    arr_lim[1][0] = 0; arr_lim[1][1] = 0; arr_size[1] = 0;
    arr_lim[2][0] = 0; arr_lim[2][1] = 0; arr_size[2] = 0;
    allocated = false;
}

template <class T>
Vector3D_pyramid<T>::~Vector3D_pyramid()
{
    if (allocated) {
        arr_lim[0][0] = 0; arr_lim[0][1] = 0; arr_size[0] = 0;
        arr_lim[1][0] = 0; arr_lim[1][1] = 0; arr_size[1] = 0;
        arr_lim[2][0] = 0; arr_lim[2][1] = 0; arr_size[2] = 0;
        for (int i = 0; i < arr_size[0]; i++)
        {
            arr[i].deallocate();
        }
        delete[] arr;
        allocated = false;
    }
}

template <class T>
bool Vector3D_pyramid<T>::allocate(int x0, int y0, int z0, int x1, int y1, int z1)
{
    if (not(allocated))
    {
        if (x1 >= x0 && y1 >= y0 && z1 >= z0)
        {
            arr_lim[0][0] = x0; arr_lim[0][1] = x1; arr_size[0] = x1 - x0;
            arr_lim[1][0] = y0; arr_lim[1][1] = y1; arr_size[1] = y1 - y0;
            arr_lim[2][0] = z0; arr_lim[2][1] = z1; arr_size[2] = z1 - z0;
            arr = new Vector2D<T>[x1 - x0];
            for (int i = 0; i < arr_size[0]; i++)
            {
                arr[i].allocate(y0, z0, y1, z1);
            }
            allocated = true;
            return true;
        }
    }
    return false;
}

template <class T>
bool Vector3D_pyramid<T>::deallocate()
{
    if (allocated)
    {
        arr_lim[0][0] = 0; arr_lim[0][1] = 0; arr_size[0] = 0;
        arr_lim[1][0] = 0; arr_lim[1][1] = 0; arr_size[1] = 0;
        arr_lim[2][0] = 0; arr_lim[2][1] = 0; arr_size[2] = 0;
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
void Vector3D_pyramid<T>::all(T value)
{
    if (allocated)
    {
        for (int i = 0; i < arr_size[0]; i++) {
        for (int j = 0; j < arr_size[1]; j++) {
        for (int k = 0; k < arr_size[2]; k++) {
            arr[i].arr[j].arr[k] = value;
        }
        }
        }
    }
}

template <class T>
inline Vector2D<T>& Vector3D_pyramid<T>::operator [](int i)
{
    return *(arr + i - arr_lim[0][0]);
}

template <class T>
Vector3D_pyramid<T>& Vector3D_pyramid<T>::operator= (T value)
{
    (*this).all(value);
    return *this;
}