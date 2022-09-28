#include <gtest/gtest.h>
#include <array>
#include <string>
#include "globaldef.h"
#include "box.h"


TEST(box, constructor_1)
{
    Box <int, 3> box1;
    Box <int, 3> box2   (std::array<int,3>{0,0,0}, std::array<int,3>{1,1,1});

    std::array<int,3> res;
    res = {0,0,0};
    GTEST_ASSERT_EQ(box2.i, res);
    GTEST_ASSERT_EQ(box2.bounds[0], res);
    res = {1,1, 1};
    GTEST_ASSERT_EQ(box2.e, res);
    GTEST_ASSERT_EQ(box2.bounds[1], res);

    box2.i = {10,11,12};
    GTEST_ASSERT_EQ(box2.e, res);
    GTEST_ASSERT_EQ(box2.bounds[1], res);
    res = {10,11,12};
    GTEST_ASSERT_EQ(box2.i, res);
    GTEST_ASSERT_EQ(box2.bounds[0], res);

    box2.e = {100,101,102};
    res = {10,11,12};
    GTEST_ASSERT_EQ(box2.i, res);
    GTEST_ASSERT_EQ(box2.bounds[0], res);
    res = {100,101, 102};
    GTEST_ASSERT_EQ(box2.e, res);
    GTEST_ASSERT_EQ(box2.bounds[1], res);

    box2.bounds = {std::array<int,3>{0,0,0}, std::array<int,3>{1,1,1}};
    res = {0,0,0};
    GTEST_ASSERT_EQ(box2.i, res);
    GTEST_ASSERT_EQ(box2.bounds[0], res);
    res = {1,1, 1};
    GTEST_ASSERT_EQ(box2.e, res);
    GTEST_ASSERT_EQ(box2.bounds[1], res);
}

TEST(box, constructor_copy)
{
    Box <int, 3> box = {std::array<int,3>{10,10,10},std::array<int,3>{2,0,-5}};
    Box <int, 3> box1 (box);
    std::array<int,3> res;
    res = {10,10,10};
    GTEST_ASSERT_EQ(box1.i, res);
    GTEST_ASSERT_EQ(box1.bounds[0], res);
    res = {2,0,-5};
    GTEST_ASSERT_EQ(box1.e, res);
    GTEST_ASSERT_EQ(box1.bounds[1], res);

    box.i = {-1,-1,-5};
    box.e = {-1,-1,-5};
    res = {10,10,10};
    GTEST_ASSERT_EQ(box1.i, res);
    GTEST_ASSERT_EQ(box1.bounds[0], res);
    res = {2,0,-5};
    GTEST_ASSERT_EQ(box1.e, res);
    GTEST_ASSERT_EQ(box1.bounds[1], res);

    box.bounds = {std::array<int,3>{-1,-1,-5}, std::array<int,3>{3,200,100}};
    res = {10,10,10};
    GTEST_ASSERT_EQ(box1.i, res);
    GTEST_ASSERT_EQ(box1.bounds[0], res);
    res = {2,0,-5};
    GTEST_ASSERT_EQ(box1.e, res);
    GTEST_ASSERT_EQ(box1.bounds[1], res);
}

TEST(box, copy_operator)
{
    Box <int, 3> box = {std::array<int,3>{10,10,10},std::array<int,3>{2,0,-5}};
    Box <int, 3> box1;
    box1=box;
    std::array<int,3> res;
    res = {10,10,10};
    GTEST_ASSERT_EQ(box1.i, res);
    GTEST_ASSERT_EQ(box1.bounds[0], res);
    res = {2,0,-5};
    GTEST_ASSERT_EQ(box1.e, res);
    GTEST_ASSERT_EQ(box1.bounds[1], res);

    box.i = {-1,-1,-5};
    box.e = {-1,-1,-5};
    res = {10,10,10};
    GTEST_ASSERT_EQ(box1.i, res);
    GTEST_ASSERT_EQ(box1.bounds[0], res);
    res = {2,0,-5};
    GTEST_ASSERT_EQ(box1.e, res);
    GTEST_ASSERT_EQ(box1.bounds[1], res);

    box.bounds = {std::array<int,3>{-1,-1,-5}, std::array<int,3>{3,200,100}};
    res = {10,10,10};
    GTEST_ASSERT_EQ(box1.i, res);
    GTEST_ASSERT_EQ(box1.bounds[0], res);
    res = {2,0,-5};
    GTEST_ASSERT_EQ(box1.e, res);
    GTEST_ASSERT_EQ(box1.bounds[1], res);
}

TEST(box,  topology)
{
    {
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{0,0,0}};
    auto [dir,topo] = box.Topology();
    GTEST_ASSERT_EQ(dir , Dir::none );
    EXPECT_EQ(topo, TopoElem::none);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{1,1,1}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::none );
    EXPECT_EQ(topo, TopoElem::vol);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{1,1,0}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::z );
    EXPECT_EQ(topo, TopoElem::surf);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{1,0,1}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::y );
    EXPECT_EQ(topo, TopoElem::surf);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{0,1,1}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::x );
    EXPECT_EQ(topo, TopoElem::surf);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{0,0,1}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::z );
    EXPECT_EQ(topo, TopoElem::lin);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{0,1,0}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::y );
    EXPECT_EQ(topo, TopoElem::lin);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{1,0,0}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::x );
    EXPECT_EQ(topo, TopoElem::lin);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{11,0,0}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::x );
    EXPECT_EQ(topo, TopoElem::lin);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{0,9,0}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::y );
    EXPECT_EQ(topo, TopoElem::lin);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{0,0,8}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::z );
    EXPECT_EQ(topo, TopoElem::lin);
    }{
    Box <int, 3> box = {std::array<int,3>{0,0,0},std::array<int,3>{0,1,8}};
    auto [dir,topo] = box.Topology();
    EXPECT_EQ(dir , Dir::x );
    EXPECT_EQ(topo, TopoElem::surf);
    }
}

TEST(box,  Padding)
{
    {
    Box <int, 3> box = {std::array<int,3>{0,1,2},std::array<int,3>{0,1,2}};
    box.addPadding(2);
    std::array<int,3> res;
    res = {-2,-1,0};
    EXPECT_EQ(box.i,res);
    res = {2,3,4};
    EXPECT_EQ(box.e,res);
    box.addPadding(-2);
    res = {0,1,2};
    EXPECT_EQ(box.i,res);
    EXPECT_EQ(box.e,res);
    }{
    Box <int, 3> box = {std::array<int,3>{0,1,2},std::array<int,3>{0,1,2}};
    box.addPadding({0,1,10});
    std::array<int,3> res;
    res = {0,0,-8};
    EXPECT_EQ(box.i,res);
    res = {0,2,12};
    EXPECT_EQ(box.e,res);
    }
}

TEST(box,  subset_superset)
{
    Box <int, 3> box1 = {{1,2,3},{4,5,6}};
    Box <int, 3> box2 = {{0,-1,-2},{10,12,8}};
    Box <int, 3> box3 = {{0,0,0},{2,2,2}};

    GTEST_ASSERT_TRUE(box1.isSubsetOf  (box1));
    GTEST_ASSERT_TRUE(box2.isSubsetOf  (box2));
    GTEST_ASSERT_TRUE(box3.isSubsetOf  (box3));
    GTEST_ASSERT_TRUE(box1.isSupersetOf(box1));
    GTEST_ASSERT_TRUE(box2.isSupersetOf(box2));
    GTEST_ASSERT_TRUE(box3.isSupersetOf(box3));

    GTEST_ASSERT_TRUE (box1.isSubsetOf  (box2));
    GTEST_ASSERT_FALSE(box1.isSupersetOf(box2));
    GTEST_ASSERT_FALSE(box2.isSubsetOf  (box1));
    GTEST_ASSERT_TRUE (box2.isSupersetOf(box1));

    GTEST_ASSERT_FALSE(box1.isSubsetOf  (box3));
    GTEST_ASSERT_FALSE(box1.isSupersetOf(box3));
    GTEST_ASSERT_FALSE(box3.isSubsetOf  (box1));
    GTEST_ASSERT_FALSE(box3.isSupersetOf(box1));

    GTEST_ASSERT_FALSE(box2.isSubsetOf  (box3));
    GTEST_ASSERT_TRUE (box2.isSupersetOf(box3));
    GTEST_ASSERT_TRUE (box3.isSubsetOf  (box2));
    GTEST_ASSERT_FALSE(box3.isSupersetOf(box2));
}

TEST(box, operator_less) {
    GTEST_ASSERT_FALSE((Box<int, 3>({5,4,3},{2,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_TRUE ((Box<int, 3>({4,4,3},{2,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_FALSE((Box<int, 3>({5,4,3},{2,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_TRUE ((Box<int, 3>({5,3,3},{2,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_FALSE((Box<int, 3>({6,3,3},{2,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_TRUE ((Box<int, 3>({5,4,2},{2,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_FALSE((Box<int, 3>({5,5,2},{2,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_TRUE ((Box<int, 3>({5,4,3},{1,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_FALSE((Box<int, 3>({5,4,4},{1,1, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_TRUE ((Box<int, 3>({5,4,3},{2,0, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_FALSE((Box<int, 3>({5,4,3},{3,0, 0})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_TRUE ((Box<int, 3>({5,4,3},{2,1,-1})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
    GTEST_ASSERT_FALSE((Box<int, 3>({5,4,3},{2,2,-1})) < (Box<int, 3>{{5,4,3},{2,1,0}}));
}
