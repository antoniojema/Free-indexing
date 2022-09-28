#include <gtest/gtest.h>
#include "NDArray.h"
#include "NDVector.h"


TEST(NDArrVec, NDVector) {
    std::array<ssize_t, 3> lim0 {-2, -1, -3};
    std::array<ssize_t, 3> lim1 { 2,  1,  4};
    NDVector<real_t, 3> vec{lim0, lim1};
    
    for (size_t xyz = 0; xyz < 3; xyz++){
        ASSERT_EQ(vec.lim0(xyz), lim0[xyz]);
        ASSERT_EQ(vec.lim1(xyz), lim1[xyz]);
        ASSERT_EQ(vec.size(xyz), lim1[xyz]-lim0[xyz]);
    }

    real_t a = 0.;
    for (auto& v : vec){
    for (auto& vv : v) {
    for (auto& e : vv) {
        e = a;
        a += 0.25;
    }}}

    a = 0.;
    for (ssize_t i = lim0[0]; i < lim1[0]; i++) {
    for (ssize_t j = lim0[1]; j < lim1[1]; j++) {
    for (ssize_t k = lim0[2]; k < lim1[2]; k++) {
        ASSERT_NEAR(vec[i][j][k], a, 1e-07);
        a += 0.25;
    }}}

    vec.reboundFirstIndex({0,0,0});

    for (size_t xyz = 0; xyz < 3; xyz++){
        ASSERT_EQ(vec.lim0(xyz), 0);
        ASSERT_EQ(vec.lim1(xyz), lim1[xyz]-lim0[xyz]);
        ASSERT_EQ(vec.size(xyz), lim1[xyz]-lim0[xyz]);
    }
    
    a = 0.;
    for (ssize_t i = 0; i < lim1[0] - lim0[0]; i++) {
    for (ssize_t j = 0; j < lim1[1] - lim0[1]; j++) {
    for (ssize_t k = 0; k < lim1[2] - lim0[2]; k++) {
        ASSERT_NEAR(vec[i][j][k], a, 1e-07);
        a += 0.25;
    }}}
}

TEST(NDArrVec, NDArray) {
    std::array<ssize_t, 3> lim0 {-2, -1, -3};
    std::array<ssize_t, 3> lim1 { 2,  1,  4};
    NDArray<real_t, 3> vec{lim0, lim1};
    
    for (size_t xyz = 0; xyz < 3; xyz++){
        ASSERT_EQ(vec.lim0(xyz), lim0[xyz]);
        ASSERT_EQ(vec.lim1(xyz), lim1[xyz]);
        ASSERT_EQ(vec.size(xyz), lim1[xyz]-lim0[xyz]);
    }

    real_t a = 0.;
    for (auto& v : vec){
    for (auto& vv : v) {
    for (auto& e : vv) {
        e = a;
        a += 0.25;
    }}}

    a = 0.;
    for (ssize_t i = lim0[0]; i < lim1[0]; i++) {
    for (ssize_t j = lim0[1]; j < lim1[1]; j++) {
    for (ssize_t k = lim0[2]; k < lim1[2]; k++) {
        ASSERT_NEAR(vec[i][j][k], a, 1e-07);
        a += 0.25;
    }}}

    vec.reset({0,0,0}, {4, 2, 7});

    for (size_t xyz = 0; xyz < 3; xyz++){
        ASSERT_EQ(vec.lim0(xyz), 0);
        ASSERT_EQ(vec.lim1(xyz), lim1[xyz]-lim0[xyz]);
        ASSERT_EQ(vec.size(xyz), lim1[xyz]-lim0[xyz]);
    }
    
    a = 0.;
    for (ssize_t i = 0; i < lim1[0] - lim0[0]; i++) {
    for (ssize_t j = 0; j < lim1[1] - lim0[1]; j++) {
    for (ssize_t k = 0; k < lim1[2] - lim0[2]; k++) {
        ASSERT_NEAR(vec[i][j][k], a, 1e-07);
        a += 0.25;
    }}}
}
