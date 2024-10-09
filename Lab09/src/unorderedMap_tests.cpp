#include <gtest/gtest.h>
#include <unorderedMap.h>

TEST(UnorderedMapTest, InsertAndRetrieve) {
    ssuds::UnorderedMap<std::string, int> map;

    map["key1"] = 10;
    map["key2"] = 20;
    map["key3"] = 30;

    EXPECT_EQ(map["key1"], 10);
    EXPECT_EQ(map["key2"], 20);
    EXPECT_EQ(map["key3"], 30);
}

TEST(UnorderedMapTest, Remove) {
    ssuds::UnorderedMap<std::string, int> map;

    map["key1"] = 10;
    map["key2"] = 20;
    map["key3"] = 30;

    map.remove("key2");

    EXPECT_EQ(map.size(), 2);
    EXPECT_EQ(map.capacity(), 10);
    EXPECT_EQ(map["key1"], 10);
    EXPECT_EQ(map["key2"], 0);
    EXPECT_EQ(map["key3"], 30);
}

TEST(UnorderedMapTest, Resize) {
    ssuds::UnorderedMap<std::string, int> map;

    for (int i = 0; i < 20; ++i) {
        map[std::to_string(i)] = i;
    }

    EXPECT_EQ(map.size(), 20);
    EXPECT_GE(map.capacity(), 20);

    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(map[std::to_string(i)], i);
    }
}

TEST(UnorderedMapTest, OstreamOperator) {
    ssuds::UnorderedMap<std::string, int> map;

    map["key1"] = 10;
    map["key2"] = 20;
    map["key3"] = 30;

    std::ostringstream oss;
    oss << map;

    EXPECT_EQ(oss.str(), "{key1:10, key2:20, key3:30}");
}

TEST(UnorderedMapIteratorTest, IteratorTest) {
    ssuds::UnorderedMap<std::string, int> map;
    map["John"] = 25;
    map["Alice"] = 30;
    map["Bob"] = 40;
    map["Emma"] = 35;

    int count = 0;
    for (auto it = map.begin(); it != map.end(); ++it) {
        ++count;
        ASSERT_NE(it, map.end());
    }
    ASSERT_EQ(count, map.size());
}

TEST(UnorderedMapFindTest, FindTest) {
    ssuds::UnorderedMap<std::string, int> map;
    map["John"] = 25;
    map["Alice"] = 30;
    map["Bob"] = 40;
    map["Emma"] = 35;

    auto it = map.find("Bob");
    ASSERT_NE(it, map.end()); 
    ASSERT_EQ((*it).second, 40); 

    it = map.find("Lucas");
    ASSERT_EQ(it, map.end()); 
}