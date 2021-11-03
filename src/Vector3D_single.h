#pragma once

struct indices_single {
    int i, j, k;
};

template <class T>
class Vector3D_single {
private:
    T* arr;
    int lim[3][2];
    int size[3], size12;
    bool allocated;

public:
    Vector3D_single();
    ~Vector3D_single();

    bool allocate(int x0, int y0, int z0, int x1, int y1, int z1);
    bool deallocate();
    
    void all(T value);

    bool isAllocated() { return allocated; };
    int sizeX() { return size[0]; };
    int sizeY() { return size[1]; };
    int sizeZ() { return size[2]; };
    int XL() { return lim[0][0]; };
    int XU() { return lim[0][1]; };
    int YL() { return lim[1][0]; };
    int YU() { return lim[1][1]; };
    int ZL() { return lim[2][0]; };
    int ZU() { return lim[2][1]; };

    T& operator [](indices_single ind);
    T& operator ()(int i, int j, int k) {
        return *(arr + (i - lim[0][0]) * size12 +
                       (j - lim[1][0]) * size[2] +
                       (k - lim[2][0]));
    };
    Vector3D_single<T>& operator= (T value);
};

template <class T>
Vector3D_single<T>::Vector3D_single()
{
    lim[0][0] = 0; lim[0][1] = 0; size[0] = 0;
    lim[1][0] = 0; lim[1][1] = 0; size[1] = 0;
    lim[2][0] = 0; lim[2][1] = 0; size[2] = 0;
    size12 = 0;
    allocated = false;
}

template <class T>
Vector3D_single<T>::~Vector3D_single()
{
    if (allocated)
    {
        lim[0][0] = 0; lim[0][1] = 0; size[0] = 0;
        lim[1][0] = 0; lim[1][1] = 0; size[1] = 0;
        lim[2][0] = 0; lim[2][1] = 0; size[2] = 0;
        size12 = 0;
        delete[] arr;
        allocated = false;
    }
}

template <class T>
bool Vector3D_single<T>::allocate(int x0, int y0, int z0, int x1, int y1, int z1)
{
    if (not (allocated))
    {
        if (x1 >= x0 && y1 >= y0 && z1 >= z0)
        {
            lim[0][0] = x0; lim[0][1] = x1; size[0] = x1 - x0;
            lim[1][0] = y0; lim[1][1] = y1; size[1] = y1 - y0;
            lim[2][0] = z0; lim[2][1] = z1; size[2] = z1 - z0;
            size12 = size[1]*size[2];
            arr = new T[(long int)((x1-x0)*(y1-y0)*(z1-z0))];
            allocated = true;
            return true;
        }
    }
    return false;
}

template <class T>
bool Vector3D_single<T>::deallocate()
{
    if (allocated)
    {
        lim[0][0] = 0; lim[0][1] = 0; size[0] = 0;
        lim[1][0] = 0; lim[1][1] = 0; size[1] = 0;
        lim[2][0] = 0; lim[2][1] = 0; size[2] = 0;
        size12 = 0;
        delete[] arr;
        allocated = false;
        return true;
    }
    return false;
}

template <class T>
void Vector3D_single<T>::all(T value)
{
    if (allocated)
    {
        for (int i = 0; i < size[0]; i++) {
        for (int j = 0; j < size[1]; j++) {
        for (int k = 0; k < size[2]; k++) {
            arr [ (i) * size12 +
                  (j) * size[2] +
                  (k)
                ] = value;
        }
        }
        }
    }
}

template <class T>
inline T& Vector3D_single<T>::operator [](indices_single ind)
{
    return arr
    [
        (ind.i - lim[0][0]) * size12 +
        (ind.j - lim[1][0]) * size[2] +
        (ind.k - lim[2][0]) 
    ];
}

//template <class T>
//inline T& Vector3D_single<T>::operator ()(int i, int j, int k)
//{
//    //return arr
//    //    [
//    //        (i - lim[0][0]) * size12 +
//    //        (j - lim[1][0]) * size[2] +
//    //        (k - lim[2][0])
//    //    ];
//    return *(arr + (i - lim[0][0]) * size12
//                 + (j - lim[1][0]) * size[2]
//                 + (k - lim[2][0])
//            );
//}

template <class T>
Vector3D_single<T>& Vector3D_single<T>::operator= (T value)
{
    (*this).all(value);
    return *this;
}