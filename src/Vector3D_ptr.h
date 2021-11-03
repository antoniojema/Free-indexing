#pragma once

#include "Vector_ptr.h"

template <class T>
struct Vector3D_ptr {
private:
    Vector_ptr<Vector_ptr<Vector_ptr<T>>> arr;
    int l[3][2]; // lim
    int s[3];    // size
    bool allocated;

public:
    Vector3D_ptr();
    ~Vector3D_ptr();

    bool allocate(int x0, int y0, int z0, int x1, int y1, int z1);
    bool deallocate();
    
    void all(T value);

    bool isAllocated() { return allocated; };
    int size(int xyz) { return s[xyz]; };
    int sizeX() { return s[0]; };
    int sizeY() { return s[1]; };
    int sizeZ() { return s[2]; };
    int lim(int xyz, int lu) { return l[xyz][lu]; };
    int XL() { return l[0][0]; };
    int XU() { return l[0][1]; };
    int YL() { return l[1][0]; };
    int YU() { return l[1][1]; };
    int ZL() { return l[2][0]; };
    int ZU() { return l[2][1]; };

    Vector_ptr<Vector_ptr<T>>& operator [](int ind);
    Vector3D_ptr<T>& operator= (T value);
};

template <class T>
Vector3D_ptr<T>::Vector3D_ptr()
{
    l[0][0] = 0; l[0][1] = 0; s[0] = 0;
    l[1][0] = 0; l[1][1] = 0; s[1] = 0;
    l[2][0] = 0; l[2][1] = 0; s[2] = 0;
    allocated = false;
}

template <class T>
Vector3D_ptr<T>::~Vector3D_ptr()
{
    (*this).deallocate();
}

template <class T>
bool Vector3D_ptr<T>::allocate(int x0, int y0, int z0, int x1, int y1, int z1)
{
    if (not (allocated))
    {
        if (x1 >= x0 && y1 >= y0 && z1 >= z0)
        {
            l[0][0] = x0; l[0][1] = x1; s[0] = x1 - x0;
            l[1][0] = y0; l[1][1] = y1; s[1] = y1 - y0;
            l[2][0] = z0; l[2][1] = z1; s[2] = z1 - z0;
            arr.allocate(x0, x1);
            for (int i = x0; i < x1; i++)
            {
                arr[i].allocate(y0, y1);
                for (int j = y0; j < y1; j++)
                {
                    arr[i][j].allocate(z0, z1);
                }
            }
            allocated = true;
            return true;
        }
    }
    return false;
}

template <class T>
bool Vector3D_ptr<T>::deallocate()
{
    if (allocated)
    {
        for (int i = l[0][0]; i < l[0][1]; i++)
        {
            for (int j = l[1][0]; j < l[1][1]; j++)
            {
                arr[i][j].deallocate();
            }
            arr[i].deallocate();
        }
        arr.deallocate();
        l[0][0] = 0; l[0][1] = 0; s[0] = 0;
        l[1][0] = 0; l[1][1] = 0; s[1] = 0;
        l[2][0] = 0; l[2][1] = 0; s[2] = 0;
        allocated = false;
        return true;
    }
    return false;
}

template <class T>
void Vector3D_ptr<T>::all(T value)
{
    if (allocated)
    {
        for (int i = l[0][0]; i < l[0][1]; i++) {
        for (int j = l[1][0]; j < l[1][1]; j++) {
        for (int k = l[2][0]; k < l[2][1]; k++) {
            arr[i][j][k] = value;
        }
        }
        }
    }
}

template <class T>
inline Vector_ptr<Vector_ptr<T>>& Vector3D_ptr<T>::operator [](int ind)
{
    return arr[ind];
}

template <class T>
Vector3D_ptr<T>& Vector3D_ptr<T>::operator= (T value)
{
    (*this).all(value);
    return *this;
}