#include <gtest/gtest.h>
#include "stack.h"
#include "queue.h"

TEST(StackTest, PushAndPop)
{
    ssuds::stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
    s.pop();

    EXPECT_TRUE(s.empty());
}

TEST(StackTest, SizeAndEmpty)
{
    ssuds::stack<int> s;

    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.empty());

    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.size(), 3);
    EXPECT_FALSE(s.empty());

    s.pop();
    EXPECT_EQ(s.size(), 2);
    EXPECT_FALSE(s.empty());
    s.pop();
    EXPECT_EQ(s.size(), 1);
    EXPECT_FALSE(s.empty());
    s.pop();
    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.empty());
}

TEST(QueueTest, EnqueueAndDequeue)
{
    ssuds::queue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    EXPECT_EQ(q.head(), 1);
    q.dequeue();
    EXPECT_EQ(q.head(), 2);
    q.dequeue();
    EXPECT_EQ(q.head(), 3);
    q.dequeue();

    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, SizeAndEmpty)
{
    ssuds::queue<int> q;

    EXPECT_EQ(q.size(), 0);
    EXPECT_TRUE(q.empty());

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    EXPECT_EQ(q.size(), 3);
    EXPECT_FALSE(q.empty());

    q.dequeue();
    EXPECT_EQ(q.size(), 2);
    EXPECT_FALSE(q.empty());
    q.dequeue();
    EXPECT_EQ(q.size(), 1);
    EXPECT_FALSE(q.empty());
    q.dequeue();
    EXPECT_EQ(q.size(), 0);
    EXPECT_TRUE(q.empty());
}