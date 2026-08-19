#include "pch.h"
#include "BinarySearchTree.h"
#include "PoolBST.h"

TEST(BinarySearchTreeTest, InitialState) {
    PoolBST<int, 10> pool;
    BinarySearchTree<int, 10> tree(pool);

    EXPECT_TRUE(tree.isEmpty());
    EXPECT_FALSE(tree.isFull());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.capacity(), 10);
    EXPECT_EQ(tree.min(), nullptr);
    EXPECT_EQ(tree.max(), nullptr);
}

TEST(BinarySearchTreeTest, InsertAndDuplicate) {
    PoolBST<int, 10> pool;
    BinarySearchTree<int, 10> tree(pool);

    EXPECT_TRUE(tree.insert(50));
    EXPECT_TRUE(tree.insert(30));
    EXPECT_TRUE(tree.insert(70));

    // Duplicate eleman eklenemez
    EXPECT_FALSE(tree.insert(50));
    EXPECT_FALSE(tree.insert(30));

    EXPECT_EQ(tree.size(), 3);
    EXPECT_FALSE(tree.isEmpty());
}

TEST(BinarySearchTreeTest, MinAndMaxExists) {
    PoolBST<int, 10> pool;
    BinarySearchTree<int, 10> tree(pool);

    // tree bos
    EXPECT_EQ(tree.max(), nullptr);
    EXPECT_EQ(tree.min(), nullptr);

    // tek eleman
    EXPECT_TRUE(tree.insert(10));
    EXPECT_EQ(tree.min(), tree.max());
    ASSERT_NE(tree.min(), nullptr);
    EXPECT_EQ(*tree.min(), 10);
    EXPECT_EQ(tree.size(), 1);

    // cok eleman
    tree.insert(20);
    tree.insert(40);
    tree.insert(100);
    tree.insert(5);
    EXPECT_FALSE(tree.insert(100));
    EXPECT_EQ(tree.size(), 5);

    EXPECT_EQ(*tree.min(), 5);
    EXPECT_EQ(*tree.max(), 100);

    EXPECT_TRUE(tree.exists(5));
    EXPECT_TRUE(tree.exists(10));
    EXPECT_TRUE(tree.exists(100));
    EXPECT_TRUE(tree.exists(40));
    EXPECT_TRUE(tree.exists(20));
}

TEST(BinarySearchTreeTest, CapacityLimit) {
    PoolBST<int, 3> pool;
    BinarySearchTree<int, 3> tree(pool);

    EXPECT_TRUE(tree.insert(10));
    EXPECT_TRUE(tree.insert(20));
    EXPECT_TRUE(tree.insert(30));
    EXPECT_TRUE(tree.isFull());

    EXPECT_FALSE(tree.insert(30));
    EXPECT_EQ(tree.size(), 3);

    // Kapasite doldu, eklenemez
    EXPECT_FALSE(tree.insert(40));
    EXPECT_EQ(tree.size(), 3);

    // Bir eleman silinince tekrar yer açýlmalý
    EXPECT_TRUE(tree.erase(20));
    EXPECT_FALSE(tree.isFull());
    EXPECT_EQ(tree.size(), 2);

    // Açýlan yere yeni eleman ekleme
    EXPECT_TRUE(tree.insert(40));
    EXPECT_TRUE(tree.isFull());
    EXPECT_EQ(tree.size(), 3);
}

TEST(BinarySearchTreeTest, EraseCases) {
    PoolBST<int, 10> pool;
    BinarySearchTree<int, 10> tree(pool);

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20); // leaf
    tree.insert(60); // leaf
    tree.insert(80); // leaf

    EXPECT_FALSE(tree.erase(100));
    EXPECT_EQ(tree.size(), 6);

    // Leaf Node erase
    EXPECT_TRUE(tree.erase(60));
    EXPECT_FALSE(tree.exists(60));
    EXPECT_EQ(tree.size(), 5);

    // One Child Node Erase
    EXPECT_TRUE(tree.erase(30));
    EXPECT_FALSE(tree.exists(30));
    EXPECT_TRUE(tree.exists(20)); 
    EXPECT_EQ(tree.size(), 4);

    // Double Child
    EXPECT_TRUE(tree.erase(50));
    EXPECT_FALSE(tree.exists(50));
    EXPECT_TRUE(tree.exists(20));
    EXPECT_TRUE(tree.exists(70));
    EXPECT_TRUE(tree.exists(80));
    EXPECT_EQ(tree.size(), 3);
}


TEST(BinarySearchTreeTest, ClearAndReusePool) {
    PoolBST<int, 3> pool;
    BinarySearchTree<int, 3> tree(pool);

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    EXPECT_TRUE(tree.isFull());

    tree.clear();
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.min(), nullptr);

    EXPECT_TRUE(tree.insert(10));
    EXPECT_TRUE(tree.insert(20));
    EXPECT_TRUE(tree.insert(30));
    EXPECT_TRUE(tree.isFull());
}