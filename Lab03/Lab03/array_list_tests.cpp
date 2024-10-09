#include <gtest\gtest.h>
#include <array_list.h>

#define DO_ARRAY_LIST_TESTS 1
#if DO_ARRAY_LIST_TESTS

// Test some foundational things like
// size, append and []
TEST(ArrayListTests, BasicTest)
{
	ssuds::ArrayList<int> s;
	EXPECT_EQ(s.size(), 0);		// If this fails, mark it and continue
	s.append(15);
	ASSERT_EQ(s.size(), 1);		// If this fails, mark it and stop this test
	EXPECT_EQ(s[0], 15);
}

// We can also make a test FIXTURE like this
class ArrayListFixture : public testing::Test
{
protected:
	void Setup() override
	{
		s1.append(15);
		s1.append(16);
		s1.append(17);
		s2.append("abc");
		s2.append("def");
	}


	ssuds::ArrayList<int> s1;
	ssuds::ArrayList<std::string> s2;
};

TEST_F(ArrayListFixture, AnotherTest)
{
	EXPECT_EQ(s1.size(), 3);
}

TEST_ERRORS(ArrayListTests, ErrorCases)
{
	ssuds::ArrayList<int> emptyList;
	EXPECT_THROW(emptyList.remove(0), std::out_of_range);

	ssuds::ArrayList<int> list;
	EXPECT_THROW(list.insert(42, 1), std::out_of_range);
}
#endif
