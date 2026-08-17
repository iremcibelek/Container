#include "pch.h"
#include "StaticQueue.h"

TEST(StaticQueueTest, Push) {
	StaticQueue<int, 6> q;

	EXPECT_TRUE(q.push(10));
	EXPECT_TRUE(q.push(20));

	EXPECT_EQ(q.size(), 2);
	EXPECT_EQ(*q.front(), 10);
	EXPECT_EQ(*q.back(), 20);
}

TEST(StaticQueueTest, PushWhenFull) {
	StaticQueue<int, 2> q;

	EXPECT_TRUE(q.push(10));
	EXPECT_TRUE(q.push(20));
	EXPECT_FALSE(q.push(30));

	EXPECT_EQ(q.size(), 2);
	EXPECT_TRUE(q.full());
	EXPECT_EQ(*q.front(), 10);
	EXPECT_EQ(*q.back(), 20);
}

TEST(StaticQueueTest, Pop) {
	StaticQueue<int, 6> q;

	q.push(10);
	q.push(20);
	q.push(30);

	EXPECT_EQ(*q.front(), 10);
	EXPECT_EQ(q.size(), 3);

	EXPECT_TRUE(q.pop());
	EXPECT_EQ(*q.front(), 20);
	EXPECT_EQ(q.size(), 2);
}

TEST(StaticQueueTest, PopWhenEmpty) {
	StaticQueue<int, 2> q;

	EXPECT_FALSE(q.pop());
	EXPECT_TRUE(q.empty());
}

TEST(StaticQueueTest, Size) {
	StaticQueue<int, 2> q;

	EXPECT_EQ(q.size(), 0);

	q.push(10);
	EXPECT_EQ(q.size(), 1);

	q.push(20);
	EXPECT_EQ(q.size(), 2);

	EXPECT_FALSE(q.push(30));
	EXPECT_EQ(q.size(), 2);
	EXPECT_TRUE(q.full());

	q.pop();
	EXPECT_EQ(q.size(), 1);
}

TEST(StaticQueueTest, Capacity) {
	StaticQueue<int, 2> q;
	StaticQueue<int, 6> q2;

	EXPECT_EQ(q.capacity(), 2);
	EXPECT_EQ(q2.capacity(), 6);
}

TEST(StaticQueueTest, Empty) {
	StaticQueue<int, 2> q;

	EXPECT_TRUE(q.empty());

	q.push(10);
	EXPECT_FALSE(q.empty());

	q.pop();
	EXPECT_TRUE(q.empty());
}

TEST(StaticQueueTest, Full) {
	StaticQueue<int, 2> q;

	EXPECT_FALSE(q.full());

	q.push(10);
	q.push(20);
	EXPECT_TRUE(q.full());

	q.pop();
	EXPECT_FALSE(q.full());
}

TEST(StaticQueueTest, Front) {
	StaticQueue<int, 2> q;

	EXPECT_EQ(q.front(), nullptr);

	q.push(10);
	q.push(20);

	ASSERT_NE(q.front(), nullptr);
	EXPECT_EQ(*q.front(), 10);

	q.pop();
	EXPECT_EQ(*q.front(), 20);

	q.push(30);
	EXPECT_EQ(*q.front(), 20);
}

TEST(StaticQueueTest, Back) {
	StaticQueue<int, 2> q;

	EXPECT_EQ(q.back(), nullptr);

	q.push(10);

	ASSERT_NE(q.back(), nullptr);
	EXPECT_EQ(*q.back(), 10);

	q.push(20);
	EXPECT_EQ(*q.back(), 20);

	q.pop();
	EXPECT_EQ(*q.back(), 20);
}

TEST(StaticQueueTest, Clear) {
	StaticQueue<int, 2> q;

	q.push(10);
	q.push(20);
	EXPECT_EQ(q.size(), 2);

	q.clear();
	EXPECT_EQ(q.size(), 0);
	EXPECT_TRUE(q.empty());
	EXPECT_EQ(q.front(), nullptr);
	EXPECT_EQ(q.back(), nullptr);
}

TEST(StaticQueueTest, Circular) {
	StaticQueue<int, 3> q;

	q.push(10);
	q.push(20);
	q.push(30);

	EXPECT_TRUE(q.full()); // 10 20 30 
	EXPECT_EQ(*q.front(), 10);
	EXPECT_EQ(*q.back(), 30);

	q.pop(); // 20 30
	EXPECT_EQ(*q.front(), 20);
	EXPECT_EQ(*q.back(), 30);

	q.push(40); // 20 30 40
	EXPECT_EQ(*q.front(),20);
	EXPECT_EQ(*q.back(), 40);

	EXPECT_FALSE(q.push(50)); // 20 30 40 
	EXPECT_TRUE(q.full());

	q.pop();
	q.pop();
	EXPECT_FALSE(q.full());
	EXPECT_EQ(q.size(), 1);

	EXPECT_EQ(*q.front(), *q.back()); // 40

	q.push(50);
	q.push(60); // 40 50 60

	EXPECT_EQ(*q.front(), 40);
	EXPECT_EQ(*q.back(), 60);
}

TEST(StaticQueueTest, Exists) {
	StaticQueue<int, 2> q;

	EXPECT_FALSE(q.exists(20));

	q.push(10);
	q.push(20);
	EXPECT_FALSE(q.push(30));

	EXPECT_TRUE(q.exists(10));
	EXPECT_TRUE(q.exists(20));
	EXPECT_FALSE(q.exists(30));
}

TEST(StaticQueueTest, ExistsCircular) {
	StaticQueue<int, 3> q;

	q.push(10);
	q.push(20);
	q.push(30);
	EXPECT_FALSE(q.push(40)); // 10 20 30
	EXPECT_TRUE(q.exists(30));
	EXPECT_FALSE(q.exists(40));

	q.pop();
	q.pop(); // 30
	q.push(40);
	q.push(50); // 30 40 50

	EXPECT_FALSE(q.exists(20));
	EXPECT_TRUE(q.exists(30));
	EXPECT_TRUE(q.exists(40));
	EXPECT_TRUE(q.exists(50));
}

TEST(StaticQueueTest, Find) {
	StaticQueue<int, 2> q;

	q.push(10);
	q.push(20);
	EXPECT_FALSE(q.push(30)); // 10 20

	EXPECT_EQ(q.find(10), 0);
	EXPECT_EQ(q.find(20), 1);

	q.pop(); // 20
	EXPECT_EQ(q.find(10), q.capacity());
	EXPECT_EQ(q.find(100), q.capacity());
}

TEST(StaticQueueTest, FindCircular) {
	StaticQueue<int, 3> q;

	q.push(10);
	q.push(20);
	q.push(30);
	EXPECT_FALSE(q.push(40)); // 10 20 30

	EXPECT_EQ(q.find(40), q.capacity());
	EXPECT_EQ(q.find(30), 2);

	q.pop(); // 20 30
	q.pop(); // 30
	q.push(40); // 30 40
	q.push(50); // 30 40 50

	EXPECT_EQ(q.find(10), q.capacity());
	EXPECT_EQ(q.find(40), 1);
	EXPECT_EQ(q.find(50), 2);
}