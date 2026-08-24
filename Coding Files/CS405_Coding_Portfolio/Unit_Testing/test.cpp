#include <gtest/gtest.h>

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <vector>

class Environment : public ::testing::Environment
{
public:
    ~Environment() override = default;

    void SetUp() override
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    void TearDown() override {}
};

class CollectionTest : public ::testing::Test
{
protected:
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    {
        collection = std::make_unique<std::vector<int>>();
    }

    void TearDown() override
    {
        collection->clear();
        collection.reset();
    }

    void add_entries(int count)
    {
        assert(count > 0);
        for (int i = 0; i < count; ++i)
        {
            collection->push_back(rand() % 100);
        }
    }
};

TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    ASSERT_TRUE(collection);
    ASSERT_NE(collection.get(), nullptr);
}

TEST_F(CollectionTest, IsEmptyOnCreate)
{
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0u);
}

// The starter file included an AlwaysFail test for demonstration.
// It is left disabled so the completed test suite can pass.
/*
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}
*/

TEST_F(CollectionTest, CanAddToEmptyVector)
{
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0u);

    add_entries(1);

    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 1u);
}

TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 5u);
}

TEST_F(CollectionTest, MaxSizeIsAtLeastSize)
{
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(4);
    EXPECT_EQ(collection->size(), 5u);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(5);
    EXPECT_EQ(collection->size(), 10u);
    EXPECT_GE(collection->max_size(), collection->size());
}

TEST_F(CollectionTest, CapacityIsAtLeastSize)
{
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(4);
    EXPECT_EQ(collection->size(), 5u);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(5);
    EXPECT_EQ(collection->size(), 10u);
    EXPECT_GE(collection->capacity(), collection->size());
}

TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    add_entries(2);
    collection->resize(8);

    EXPECT_EQ(collection->size(), 8u);
}

TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    add_entries(10);
    collection->resize(4);

    EXPECT_EQ(collection->size(), 4u);
}

TEST_F(CollectionTest, ResizeToZeroEmptiesCollection)
{
    add_entries(5);
    collection->resize(0);

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0u);
}

TEST_F(CollectionTest, ClearErasesCollection)
{
    add_entries(5);
    collection->clear();

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0u);
}

TEST_F(CollectionTest, EraseRangeErasesCollection)
{
    add_entries(5);
    collection->erase(collection->begin(), collection->end());

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0u);
}

TEST_F(CollectionTest, ReserveIncreasesCapacityButNotSize)
{
    const auto original_size = collection->size();
    collection->reserve(50);

    EXPECT_GE(collection->capacity(), 50u);
    EXPECT_EQ(collection->size(), original_size);
}

TEST_F(CollectionTest, OutOfRangeThrows)
{
    add_entries(3);
    EXPECT_THROW(collection->at(3), std::out_of_range);
}

// Student-created positive test.
TEST_F(CollectionTest, PushBackStoresExpectedValue)
{
    collection->push_back(42);

    ASSERT_EQ(collection->size(), 1u);
    EXPECT_EQ(collection->at(0), 42);
}

// Student-created negative test.
TEST_F(CollectionTest, EmptyVectorAtThrows)
{
    ASSERT_TRUE(collection->empty());
    EXPECT_THROW(collection->at(0), std::out_of_range);
}
