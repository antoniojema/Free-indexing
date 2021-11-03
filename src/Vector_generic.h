#pragma once
#include <vector>

namespace ugr{
template <typename T, int N> class Vector {
protected:
    Vector<T, N-1> *arr, *arr_rebounded;
    int lim[N][2];
public:
    void allocate(int lim0[N], int lim1[N]) {
        for (int i = 0; i < N; i++) {
            lim[i][0] = lim0[i];
            lim[i][1] = lim1[i];
        }
        arr = new Vector<T,N-1>[lim[0][1]-lim[0][0]];
        arr_rebounded = arr - lim[0][0];
        
        int below_lim0[N-1], below_lim1[N-1];
        for (int i = 0; i < N-1; i++){
            below_lim0[i] = lim0[i+1];
            below_lim1[i] = lim1[i+1];
        }
        for (int i = 0; i < lim[0][1]-lim[0][0]; i++){
            (arr[i]).allocate(below_lim0, below_lim1);
        }
    }
    
    void allocate(const std::vector<int>& lim0, const std::vector<int>& lim1) {
        for (int i = 0; i < N; i++) {
            lim[i][0] = lim0[i];
            lim[i][1] = lim1[i];
        }
        arr = new Vector<T,N-1>[lim[0][1]-lim[0][0]];
        arr_rebounded = arr - lim[0][0];
        
        int below_lim0[N-1], below_lim1[N-1];
        for (int i = 0; i < N-1; i++){
            below_lim0[i] = lim0[i+1];
            below_lim1[i] = lim1[i+1];
        }
        for (int i = 0; i < lim[0][1]-lim[0][0]; i++){
            (arr[i]).allocate(below_lim0, below_lim1);
        }
    }

    void deallocate() {
        for (int i = 0; i < lim[0][1]-lim[0][0]; i++){
            (arr[i]).deallocate();
        }
        delete [] arr;
    }

    void all(T value) {
        for (int i = lim[0][0]; i < lim[0][1]; i++) {
            arr_rebounded[i].all(value);
        }
    }

    Vector<T,N>& operator= (T value)
    {
        this -> all(value);
        return *this;
    }

    inline Vector<T, (N>1)?(N-1):1>& operator [] (int i){
        return arr_rebounded[i];
    }
};

template <typename T> class Vector<T, 1>{
protected:
    T *arr, *arr_rebounded;
    int lim[2];
public:
    void allocate(int lim0, int lim1) {
        lim[0] = lim0;
        lim[1] = lim1;
        arr = new T[lim[1]-lim[0]];
        arr_rebounded = arr - lim[0];
    }
    void allocate(const std::vector<int>& lim0, const std::vector<int>& lim1) {
        this->allocate(lim0[0], lim1[0]);
    }

    void allocate(int lim0[1], int lim1[1]) {
        this->allocate(lim0[0], lim1[0]);
    }

    void deallocate() {
        delete [] arr;
    }

    void all(T value) {
        for (int i = lim[0]; i < lim[0]; i++) {
            arr_rebounded[i] = value;
        }
    }

    Vector<T,1>& operator= (T value)
    {
        this -> all(value);
        return *this;
    }

    inline T& operator [] (int i){
        return arr_rebounded[i];
    }
};
}