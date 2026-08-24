#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

TEST(BoundsTest, ValidIndex)
{
    std::vector<int> v{10, 20, 30};
    EXPECT_EQ(v.at(1), 20);
}

TEST(BoundsTest, LastValidIndex)
{
    std::vector<int> v{10, 20, 30};
    EXPECT_EQ(v.at(v.size() - 1), 30);
}

TEST(BoundsTest, SizeIndexThrows)
{
    std::vector<int> v{10, 20, 30};
    EXPECT_THROW(v.at(v.size()), std::out_of_range);
}

TEST(BoundsTest, LargeIndexThrows)
{
    std::vector<int> v{10, 20, 30};
    EXPECT_THROW(v.at(1000), std::out_of_range);
}

TEST(BoundsTest, EmptyVectorThrows)
{
    std::vector<int> v;
    EXPECT_THROW(v.at(0), std::out_of_range);
}
