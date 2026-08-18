#include "pch.h"
#include "StaticLinkedList.h"
#include "ObjectPool.h"

TEST(StaticLinkedListTest, PushFront) {
	ObjectPool<int,10> pool;
    StaticLinkedList<int,10> list(pool);

    EXPECT_TRUE(list.push_front(10)); // 10
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.front(), 10);
    EXPECT_EQ(*list.back(), 10);

    EXPECT_TRUE(list.push_front(20)); // 20 10
    EXPECT_TRUE(list.push_front(30)); // 30 20 10

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(*list.front(), 30);
    EXPECT_EQ(*list.back(), 10);
}

TEST(StaticLinkedListTest, PushBack) {
	ObjectPool<int,10> pool;
    StaticLinkedList<int,10> list(pool);

    EXPECT_TRUE(list.push_back(10)); // 10
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(*list.front(), 10);
    EXPECT_EQ(*list.back(), 10);

    EXPECT_TRUE(list.push_back(20)); // 10 20
    EXPECT_TRUE(list.push_back(30)); // 10 20 30

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(*list.front(), 10);
    EXPECT_EQ(*list.back(), 30);

    list.push_front(5); // 5 10 20 30
    EXPECT_EQ(*list.front(), 5);
    EXPECT_EQ(*list.back(), 30);
}


TEST(StaticLinkedListTest, PopFront) {
	ObjectPool<int,10> pool;
   StaticLinkedList<int,10> list(pool);

    EXPECT_FALSE(list.pop_front());

    list.push_front(10); // 10
    EXPECT_EQ(*list.front(), *list.back());

    list.push_front(20); // 20 10
    list.push_back(30); // 20 10 30
    EXPECT_EQ(list.size(), 3);
    EXPECT_TRUE(list.pop_front()); // 10 30
    EXPECT_EQ(*list.front(), 10);

    EXPECT_TRUE(list.pop_front());
    EXPECT_TRUE(list.pop_front());
    EXPECT_FALSE(list.pop_front());
}

TEST(StaticLinkedListTest, PopBack) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_FALSE(list.pop_back());

	list.push_back(10);
	EXPECT_EQ(*list.front(), *list.back());

	list.push_back(20); // 10 20
	list.push_back(30); // 10 20 30
	list.push_front(40); // 40 10 20 30
	EXPECT_EQ(list.size(), 4);
	EXPECT_TRUE(list.pop_back()); // 40 10 20
	EXPECT_EQ(*list.back(), 20);

	EXPECT_TRUE(list.pop_back()); // 40 10
	EXPECT_TRUE(list.pop_back()); // 40
	EXPECT_TRUE(list.pop_back()); // null
	EXPECT_FALSE(list.pop_back());
}

TEST(StaticLinkedListTest, InsertByIndex) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_FALSE(list.insertByIndex(3, 30));
	EXPECT_TRUE(list.isEmpty());

	list.push_back(10); // 10
	list.push_back(20); // 10 20
	list.push_front(100); // 100 10 20
	EXPECT_EQ(list.find(10), 1);
	EXPECT_EQ(list.find(50), list.size());
	EXPECT_EQ(list.size(), 3);

	EXPECT_TRUE(list.insertByIndex(1, 40)); // 100 40 10 20
	EXPECT_NE(list.find(10), 1);
	EXPECT_EQ(list.find(10), 2);
	EXPECT_EQ(list.find(40), 1);

	EXPECT_TRUE(list.insertByIndex(0, 50)); // 50 100 40 10 20
	EXPECT_TRUE(list.insertByIndex(list.size(), 60)); // 50 100 40 10 20 60
	EXPECT_EQ(*list.back(), 60);
}

TEST(StaticLinkedListTest, EraseByIndex) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_FALSE(list.eraseByIndex(3));
	EXPECT_TRUE(list.isEmpty());

	list.push_back(10);
	EXPECT_FALSE(list.eraseByIndex(1));

	list.push_back(20); // 10 20
	list.push_front(50); // 50 10 20
	list.push_front(60); // 60 50 10 20 
	EXPECT_FALSE(list.eraseByIndex(list.size()));

	EXPECT_TRUE(list.eraseByIndex(2)); // 60 50 20
	EXPECT_EQ(list.find(20), 2);
	EXPECT_FALSE(list.exists(10));

	EXPECT_TRUE(list.eraseByIndex(list.size() - 1)); // 60 50
	EXPECT_TRUE(list.eraseByIndex(0)); // 50
}

TEST(StaticLinkedListTest, EraseByData) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_FALSE(list.eraseByData(10));

	list.push_back(10);
	EXPECT_FALSE(list.eraseByData(20));
	EXPECT_TRUE(list.eraseByData(10)); // null
	EXPECT_TRUE(list.isEmpty());

	list.push_back(40); // 40
	list.push_back(60); // 40 60
	list.push_front(20); // 20 40 60
	EXPECT_TRUE(list.eraseByData(40)); // 20 60
	EXPECT_FALSE(list.exists(40));
	EXPECT_FALSE(list.eraseByData(70));

	EXPECT_TRUE(list.eraseByData(60)); // 20
	EXPECT_EQ(*list.back(), 20);
}

TEST(StaticLinkedListTest, SizeAndEmpty) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_EQ(list.size(), 0);

	list.push_back(10);
	EXPECT_EQ(list.size(), 1);

	list.push_back(20);
	list.push_back(30); // 10 20 30
	EXPECT_EQ(list.size(), 3);

	list.pop_back();
	EXPECT_EQ(list.size(), 2);

	list.pop_back();
	list.pop_back();
	EXPECT_EQ(list.size(), 0);
	EXPECT_TRUE(list.isEmpty());

	EXPECT_EQ(list.front(), nullptr);
}

TEST(StaticLinkedListTest, Capacity) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_EQ(list.capacity(), 10);
	EXPECT_FALSE(list.isFull());

	for (int i = 0; i < 10; i++) {
		EXPECT_TRUE(list.push_back(i));
	}

	EXPECT_EQ(list.size(), 10);
	EXPECT_TRUE(list.isFull());

	EXPECT_FALSE(list.push_back(100));
	EXPECT_EQ(list.size(), 10);
}

TEST(StaticLinkedListTest, Front) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_EQ(list.front(), nullptr);

	list.push_back(10);
	list.push_back(20); // 10 20
	EXPECT_EQ(*list.front(), 10);

	list.push_front(5); // 5 10 20
	EXPECT_EQ(*list.front(), 5);

	list.pop_back(); // 5 10
	EXPECT_EQ(*list.front(), 5);

	list.pop_front(); // 10
	EXPECT_EQ(*list.front(), 10);

	list.pop_back();
	EXPECT_TRUE(list.isEmpty());
	EXPECT_EQ(list.front(), nullptr);

}

TEST(StaticLinkedListTest, Back) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_EQ(list.back(), nullptr);

	list.push_back(10); // 10
	EXPECT_EQ(*list.back(), 10);

	list.push_back(20);
	list.push_front(30); // 30 10 20
	EXPECT_EQ(*list.back(), 20);

	list.pop_back(); // 30 10
	list.pop_front(); // 10
	EXPECT_EQ(*list.back(), 10);

	list.pop_front();
	EXPECT_EQ(list.back(), nullptr);
	EXPECT_TRUE(list.isEmpty());
}

TEST(StaticLinkedListTest, Clear) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	list.push_back(10);
	list.clear();
	EXPECT_EQ(list.size(), 0);
	EXPECT_FALSE(list.exists(10));

	list.push_back(50);
	list.push_back(60);
	list.push_front(70);
	list.clear();
	EXPECT_TRUE(list.isEmpty());
	EXPECT_EQ(list.front(), nullptr);
	EXPECT_EQ(list.back(), nullptr);
}

TEST(StaticLinkedListTest, Exists) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_FALSE(list.exists(100));

	list.push_back(10);
	list.push_back(20);
	list.push_back(30); //  10 20 30
	EXPECT_TRUE(list.exists(10));
	EXPECT_TRUE(list.exists(20));
	EXPECT_TRUE(list.exists(30));

	list.pop_back(); // 10 20
	list.pop_front(); // 20


	EXPECT_TRUE(list.exists(20));
	EXPECT_FALSE(list.exists(10));
	EXPECT_FALSE(list.exists(30));

	list.clear();
	EXPECT_FALSE(list.exists(20));
}

TEST(StaticLinkedListTest, Find) {
	ObjectPool<int,10> pool;
	StaticLinkedList<int,10> list(pool);

	EXPECT_EQ(list.find(10), list.size());

	list.push_back(10);
	list.push_back(20); // 10 20
	list.push_front(30); // 30 10 20

	EXPECT_EQ(list.find(10), 1);
	EXPECT_EQ(list.find(30), 0);
	EXPECT_EQ(list.find(20), 2);

	list.pop_front(); // 10 20
	list.pop_back(); //  10
	EXPECT_EQ(list.find(10), 0);
	EXPECT_EQ(list.find(30), list.size());
	EXPECT_EQ(list.find(20), list.size());

	list.clear();
	EXPECT_EQ(list.find(10), list.size());
}

TEST(StaticLinkedListTest, Reverse) {
	ObjectPool<double,5> pool;
	StaticLinkedList<double,5> list(pool);

	list.push_back(10);
	list.push_back(20);
	list.push_back(30); // 10 20 30

	list.reverse(); // 30 20 10

	EXPECT_EQ(*list.front(), 30);
	EXPECT_EQ(*list.back(), 10);

	EXPECT_EQ(list.find(30), 0);
	EXPECT_EQ(list.find(20), 1);
	EXPECT_EQ(list.find(10), 2);
}

TEST(StaticLinkedListTest, ReuseFreedNode) {
	ObjectPool<double,3> pool;
	StaticLinkedList<double,3> list(pool);

	list.push_back(10);
	list.push_back(20);
	list.push_back(30); // 10 20 30

	EXPECT_TRUE(list.eraseByIndex(1)); // 10 30
	EXPECT_FALSE(list.exists(20));
	EXPECT_EQ(list.size(), 2);

	EXPECT_TRUE(list.push_back(40)); // 10 30 40

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(*list.front(), 10);
	EXPECT_EQ(*list.back(), 40);
	EXPECT_TRUE(list.exists(40));
}

TEST(StaticLinkedListTest, DifferentCapacity) {
	ObjectPool<int,3> pool;
	StaticLinkedList<int,3> list(pool);

	EXPECT_EQ(list.capacity(), 3);

	EXPECT_TRUE(list.push_back(10));
	EXPECT_TRUE(list.push_back(20));
	EXPECT_TRUE(list.push_back(30));

	EXPECT_TRUE(list.isFull());
	EXPECT_FALSE(list.push_back(40));
}