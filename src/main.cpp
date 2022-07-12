#include "NDVector.h"
#include "NDArray.h"
#include "typedef.h"
#include <iostream>

#include <array>

int main() {
    NDArray<real_t, 1> arr = {-3,2};
    arr = -4.3;

    NDVector<real_t, 1> vec = {-3,2};
    vec = 1.1;

    NDArray<double, 3> arr2 = {{-3,2,3},{2,3,4}};
    arr = -4.3;

    NDVector<char, 3> vec2 = {{-3,-1,-3},{2,1,3}};
    vec2 = 1;
    vec2[-1][0][2] = 0;

    auto asdf  = arr2.operator[](-3);
    auto asdf2 = arr2[-3];

    std::cout << std::endl;


    //NDVector<real_t, 3> arr1 {{0,-1, 1}, {10, 9, 12}};
    //arr1.resize({0,-1, 1}, {10, 9, 12});
    //arr1.rebound({0,-1, 1}, {10, 9, 12});
    //
    //std::deque<int> a, b;
    //a.swap(b);
    //
    //NDVector<int, 1> v1, v2;
    //v1.resize(-5 ,5);

    //for (auto& e : v1) {
    //    e;
    //}

    //NDArray<real_t, 2> a1 {{-4, -3}, {0, 2}};
    //NDArray<real_t, 2> a2 {{5, 2}};

    //a1 = 3.5;
    //a2 = -7.3;

    //for (auto& e : a1){
    //    for (auto& ee : e)
    //        std::cout << ee << std::endl;
    //    std::cout << std::endl;
    //}
    //std::cout << std::endl;

    //for (auto& e : a2){
    //    for (auto& ee : e)
    //        std::cout << ee << std::endl;
    //    std::cout << std::endl;
    //}
    //std::cout << std::endl;
    

    //ssize_t i0 = -5;
    //ssize_t i1 = 10;
    //size_t size = (size_t) (i1-i0);
    //
    //NDVector<real_t, 1> arr {i0, i1};
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

    //std::cout << "NDVector:" << std::endl;
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

    //std::cout << "NDVector (element-wise):" << std::endl;
    //for (ssize_t i = i0; i < i1; i++) {
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

    //std::cout << "NDVector:" << std::endl;
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

    //std::cout << "NDVector (element-wise):" << std::endl;
    //for (ssize_t i = i0; i < i1; i++) {
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
