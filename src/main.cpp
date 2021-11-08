#include "NDArray.h"
#include "typedef.h"
#include <iostream>

int main() {
    NDArray<real_t, 3> arr1 {{0,-1, 1}, {10, 9, 12}};
    arr1.resize({0,-1, 1}, {10, 9, 12});
    arr1.rebound({0,-1, 1}, {10, 9, 12});
    
    //lim_t i0 = -5;
    //lim_t i1 = 10;
    //size_t size = (size_t) (i1-i0);
    //
    //NDArray<real_t, 1> arr {i0, i1};
    //auto& vec = arr.getVector();

    //real_t f = 0;
    //for (auto& e : arr) {
    //    e = f;
    //    f += 0.45;
    //}
    //
    //arr.push_back(13.45);
    //arr.emplace_back(23.54);
    //i1 += 2;
    //size += 2;

    //std::cout << (arr.lim0() == i0  ) << std::endl;
    //std::cout << (arr.lim1() == i1  ) << std::endl;
    //std::cout << (arr.size() == size) << std::endl;
    //std::cout << std::endl;

    //std::cout << "NDArray:" << std::endl;
    //for (auto& e : arr) {
    //   std::cout << e << std::endl;
    //}
    //std::cout << std::endl;
    //
    //std::cout << "Vector:" << std::endl;
    //for (auto& e : vec) {
    //   std::cout << e << std::endl;
    //}
    //std::cout << std::endl;

    //std::cout << "NDArray (element-wise):" << std::endl;
    //for (lim_t i = i0; i < i1; i++) {
    //   std::cout << arr[i] << std::endl;
    //}
    //std::cout << std::endl;
    //
    //std::cout << "Vector (element-wise):" << std::endl;
    //for (size_t i = 0; i < size; i++) {
    //   std::cout << vec[i] << std::endl;
    //}
    //std::cout << std::endl;
    //
    //i0 = -2;
    //i1 = 4;
    //size = (size_t) (i1-i0);
    //arr.rebound(i0, i1);

    //std::cout << (arr.lim0() == i0  ) << std::endl;
    //std::cout << (arr.lim1() == i1  ) << std::endl;
    //std::cout << (arr.size() == size) << std::endl;
    //std::cout << std::endl;

    //std::cout << "NDArray:" << std::endl;
    //for (auto& e : arr) {
    //   std::cout << e << std::endl;
    //}
    //std::cout << std::endl;
    //
    //std::cout << "Vector:" << std::endl;
    //for (auto& e : vec) {
    //   std::cout << e << std::endl;
    //}
    //std::cout << std::endl;

    //std::cout << "NDArray (element-wise):" << std::endl;
    //for (lim_t i = i0; i < i1; i++) {
    //   std::cout << arr[i] << std::endl;
    //}
    //std::cout << std::endl;
    //
    //std::cout << "Vector (element-wise):" << std::endl;
    //for (size_t i = 0; i < size; i++) {
    //   std::cout << vec[i] << std::endl;
    //}
    //std::cout << std::endl;

}
