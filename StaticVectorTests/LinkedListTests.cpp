#include "pch.h"
#include "LinkedList.h"

TEST(LinkedListTest, PushFront) {
	LinkedList<int> list;

	list.push_front(10); 
	EXPECT_EQ(*list.front(), 10);

	list.push_front(20); 
	list.push_front(30); // 30 20 10
	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(*list.front(),30);

	list.pop_front(); // 20 10
	EXPECT_EQ(*list.front(), 20);
}

TEST(LinkedListTest, PushBack) {
	LinkedList<int> list;

	list.push_back(10); // 10
	EXPECT_EQ(*list.back(),10);

	list.push_back(20);
	list.push_back(30);
	list.push_front(5); // 5 10 20 30
	EXPECT_EQ(*list.back(), 30);

	list.pop_back(); // 5 10 20
	EXPECT_EQ(*list.back(), 20);
}

TEST(LinkedListTest, PopFront) {
	LinkedList<int> list;

	EXPECT_FALSE(list.pop_front());

	list.push_front(10); // 10
	EXPECT_EQ(*list.front(), *list.back());

	list.push_front(20); // 20 10
	list.push_back(30); // 20 10 30
	EXPECT_EQ(list.size(), 3);
	EXPECT_TRUE(list.pop_front()); // 10 30
	EXPECT_EQ(*list.front(),10);

	EXPECT_TRUE(list.pop_front());
	EXPECT_TRUE(list.pop_front());
	EXPECT_FALSE(list.pop_front());
}

TEST(LinkedListTest, PopBack) {
	LinkedList<int> list;

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

TEST(LinkedListTest, InsertByIndex) {
	LinkedList<int> list;

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

TEST(LinkedListTest, EraseByIndex) {
	LinkedList<int> list;

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

TEST(LinkedListTest, EraseByData) {
	LinkedList<int> list;

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

TEST(LinkedListTests, SizeAndEmpty) {
	LinkedList<int> list;

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

TEST(LinkedListTest, Front) {
	LinkedList<int> list;

	EXPECT_EQ(list.front(), nullptr);

	list.push_back(10);
	list.push_back(20); // 10 20
	EXPECT_EQ(*list.front(), 10);

	list.push_front(5); // 5 10 20
	EXPECT_EQ(*list.front(), 5);

	list.pop_back(); // 5 10
	EXPECT_EQ(*list.front(), 5);

	list.pop_front(); // 10
	EXPECT_EQ(*list.front(),10);

	list.pop_back();
	EXPECT_TRUE(list.isEmpty());
	EXPECT_EQ(list.front(), nullptr);

}

TEST(LinkedListTest, Back) {
	LinkedList<int> list;

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

TEST(LinkedListTest, Clear) {
	LinkedList<int> list;

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

TEST(LinkedListTest, Exists) {
	LinkedList<int> list;

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

TEST(LinkedListTest, Find) {
	LinkedList<int> list;

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

TEST(LinkedListTest, Reverse) {
	LinkedList<int> list;

	list.push_back(10);
	list.push_back(20);
	list.push_back(30); // 10 20 30
	EXPECT_EQ(*list.front(), 10);
	EXPECT_EQ(*list.back(), 30);

	list.reverse(); // 30 20 10
	EXPECT_EQ(*list.front(), 30);
	EXPECT_EQ(*list.back(), 10);
}