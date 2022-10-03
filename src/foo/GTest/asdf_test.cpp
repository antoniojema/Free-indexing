#include <gtest/gtest.h>
#include "asdf.h"

TEST(asdf, asdf) {
    ASSERT_EQ(foo(-1), 1);
    ASSERT_EQ(foo(1), 1);
    ASSERT_EQ(foo(2), 4);
    ASSERT_EQ(foo(3), 9);
    ASSERT_EQ(foo(4), 16);
}
