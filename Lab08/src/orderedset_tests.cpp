#include <gtest/gtest.h>
#include <orderedset.h>

TEST(OrderedSetTest, InsertionAndSize) 
{
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(2);
    orderedSet.insert(4);

    EXPECT_EQ(5, orderedSet.size());
    EXPECT_TRUE(orderedSet.contains(5));
    EXPECT_TRUE(orderedSet.contains(3));
    EXPECT_TRUE(orderedSet.contains(7));
    EXPECT_TRUE(orderedSet.contains(2));
    EXPECT_TRUE(orderedSet.contains(4));
}

TEST(OrderedSetTest, Clearing) 
{
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(2);
    orderedSet.insert(4);

    orderedSet.clear();
    EXPECT_EQ(0, orderedSet.size());
    EXPECT_FALSE(orderedSet.contains(5));
    EXPECT_FALSE(orderedSet.contains(3));
    EXPECT_FALSE(orderedSet.contains(7));
    EXPECT_FALSE(orderedSet.contains(2));
    EXPECT_FALSE(orderedSet.contains(4));
}

TEST(OrderedSetTest, Rebalancing) 
{
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(2);
    orderedSet.insert(4);
    orderedSet.insert(6);
    orderedSet.insert(8);
    orderedSet.insert(9);

    orderedSet.rebalance();

    EXPECT_EQ(8, orderedSet.size());
    EXPECT_EQ(4, orderedSet.get_height()); 
}

TEST(OrderedSetTest, ContainmentCheck) 
{
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(2);
    orderedSet.insert(4);

    EXPECT_TRUE(orderedSet.contains(3));
    EXPECT_FALSE(orderedSet.contains(6));
}

TEST(OrderedSetTest, EraseLeafNode) {
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);

    bool result = orderedSet.erase(3);

    EXPECT_TRUE(result);
    EXPECT_EQ(2, orderedSet.size());
    EXPECT_FALSE(orderedSet.contains(3));
}

TEST(OrderedSetTest, EraseNodeWithSingleChild) {
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(4);

    bool result = orderedSet.erase(3);

    EXPECT_TRUE(result);
    EXPECT_EQ(3, orderedSet.size());
    EXPECT_FALSE(orderedSet.contains(3));
}

TEST(OrderedSetTest, EraseNodeWithTwoChildren) {
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(4);
    orderedSet.insert(6);

    bool result = orderedSet.erase(3);

    EXPECT_TRUE(result); 
    EXPECT_EQ(4, orderedSet.size()); 
    EXPECT_FALSE(orderedSet.contains(3)); 
}

TEST(OrderedSetTest, TreeStringEmptyTree) {
    ssuds::OrderedSet<int> orderedSet;
    ASSERT_EQ(orderedSet.tree_string(), "Tree is empty.");
}

TEST(OrderedSetTest, TreeStringNonEmptyTree) {
    ssuds::OrderedSet<int> orderedSet;
    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(2);
    orderedSet.insert(4);
    orderedSet.insert(6);
    orderedSet.insert(8);
    orderedSet.insert(1);
    orderedSet.insert(9);

    std::string expectedTreeString =
        "    5 L:3 R:7\n"
        "    3 L:2 R:4    7 L:6 R:8\n"
        "    2 L:1 R:-    4 L:- R:-    6 L:- R:-    8 L:- R:9\n"
        "    1 L:- R:-    9 L:- R:-\n";

    ASSERT_EQ(orderedSet.tree_string(), expectedTreeString);
}
