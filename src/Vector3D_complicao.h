#pragma once

template <class T>
class Vector3D_complicao {
public:
    T ***arr, ***arr_lvl0, ***arr_lvl1, ***arr_lvl2;
    int l[3][2]; // limits [xyz] [lu]
    int s[3];    // size [xyz]
    bool allocated;

    Vector3D_complicao();
    ~Vector3D_complicao();

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

    T**& operator [](int ind);
    Vector3D_complicao<T>& operator= (T value);
};

template <class T>
Vector3D_complicao<T>::Vector3D_complicao()
{
    l[0][0] = 0; l[0][1] = 0; s[0] = 0;
    l[1][0] = 0; l[1][1] = 0; s[1] = 0;
    l[2][0] = 0; l[2][1] = 0; s[2] = 0;
    arr      = NULL;
    arr_lvl0 = NULL;
    arr_lvl1 = NULL;
    arr_lvl2 = NULL;
    allocated = false;
}

template <class T>
Vector3D_complicao<T>::~Vector3D_complicao()
{
    (*this).deallocate();
}

template <class T>
bool Vector3D_complicao<T>::allocate(int x0, int y0, int z0, int x1, int y1, int z1)
{
    if (not (allocated))
    {
        if (x1 >= x0 && y1 >= y0 && z1 >= z0)
        {
            l[0][0] = x0; l[0][1] = x1; s[0] = x1 - x0;
            l[1][0] = y0; l[1][1] = y1; s[1] = y1 - y0;
            l[2][0] = z0; l[2][1] = z1; s[2] = z1 - z0;

            arr_lvl2 = new T**[s[0]];
            for (int i = 0; i < s[0]; i++) {
                arr_lvl2[i] = new T*[s[1]];
                for (int j = 0; j < s[1]; j++) {
                    arr_lvl2[i][j] = new T[s[2]];
                }
            }

            arr_lvl1 = new T**[s[0]];
            for (int i = 0; i < s[0]; i++) {
                arr_lvl1[i] = new T*[s[1]];
                for (int j = 0; j < s[1]; j++) {
                    arr_lvl1[i][j] = arr_lvl2[i][j] - z0;
                }
            }

            arr_lvl0 = new T**[s[0]];
            for (int i = 0; i < s[0]; i++) {
                arr_lvl0[i] = arr_lvl1[i] - y0;
            }

            arr = arr_lvl0 - x0;
            
            allocated = true;
            return true;
        }
    }
    return false;
}

template <class T>
bool Vector3D_complicao<T>::deallocate()
{
    if (allocated)
    {
        delete [] arr_lvl0;

        for (int i = 0; i < s[0]; i++) {
            delete [] arr_lvl1[i];
        }
        delete [] arr_lvl1;

        for (int i = 0; i < s[0]; i++) {
            for (int j = 0; j < s[1]; j++) {
                delete [] arr_lvl2[i][j];
            }
            delete [] arr_lvl2[i];
        }
        delete [] arr_lvl2;

        arr      = NULL;
        arr_lvl0 = NULL;
        arr_lvl1 = NULL;
        arr_lvl2 = NULL;
        
        allocated = false;
        return true;
    }
    return false;
}

template <class T>
void Vector3D_complicao<T>::all(T value)
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
inline T**& Vector3D_complicao<T>::operator [](int ind)
{
    return *(arr + ind);
}

template <class T>
Vector3D_complicao<T>& Vector3D_complicao<T>::operator= (T value)
{
    (*this).all(value);
    return *this;
}