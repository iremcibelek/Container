#include "pch.h"
#include "RedBlackTree.h" 

TEST(RedBlackTreeTest,Insert ) {
	PoolRBT<int, 5> pool;
	RedBlackTree<int, 5> tree(pool);

    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.size(), 0);

    EXPECT_TRUE(tree.insert(20));
    EXPECT_TRUE(tree.insert(10));
    EXPECT_TRUE(tree.insert(30));

    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.size(), 3);

    EXPECT_TRUE(tree.exists(20));
    EXPECT_TRUE(tree.exists(10));
    EXPECT_TRUE(tree.exists(30));
    EXPECT_FALSE(tree.exists(100));
}

TEST(RedBlackTreeTest, RootColor) {
    PoolRBT<int, 5> pool;
    RedBlackTree<int, 5> tree(pool);

    auto* root = tree.getRoot();
    EXPECT_EQ(root, nullptr);

    tree.insert(30);
    root = tree.getRoot();

    EXPECT_EQ(root->data, 30);
    EXPECT_EQ(root->color, B);

    tree.insert(10);
    tree.insert(50);
    root = tree.getRoot();
    EXPECT_EQ(root->color, B);
    EXPECT_EQ(root->left->color, R);
    EXPECT_EQ(root->right->color, R);

    tree.erase(30);
    EXPECT_FALSE(tree.exists(30));
    root = tree.getRoot(); // 10
    EXPECT_EQ(root->color, B);
    EXPECT_EQ(root->left->color, R);
    EXPECT_EQ(root->right, nullptr);
}

TEST(RedBlackTreeTest, Erase) {
    PoolRBT<int, 5> pool;
    RedBlackTree<int, 5> tree(pool);

    EXPECT_TRUE(tree.isEmpty());

    auto* root = tree.getRoot();
    EXPECT_FALSE(tree.erase(10));
    EXPECT_EQ(root, nullptr);

    tree.insert(10);
    tree.insert(30);
    tree.insert(40);
    root = tree.getRoot(); // 30
    EXPECT_EQ(root->left->color, R);
    EXPECT_EQ(root->right->color, R);

    tree.insert(50);
    EXPECT_EQ(tree.size(), 4);
    EXPECT_EQ(root->left->left, nullptr);
    EXPECT_EQ(root->right->right->data, 50);
    EXPECT_EQ(root->right->color, B);
    EXPECT_EQ(root->left->color, B);
    EXPECT_EQ(root->right->right->color, R);

    EXPECT_FALSE(tree.insert(30));
    tree.insert(5);
    EXPECT_TRUE(tree.isFull());
    EXPECT_FALSE(tree.insert(60));
    EXPECT_EQ(root->left->left->color, R);
    EXPECT_EQ(root->left->left->data, 5);

    tree.erase(30);
    EXPECT_FALSE(tree.exists(30));
    EXPECT_EQ(tree.size(), 4);
    root = tree.getRoot(); // 40
    EXPECT_EQ(tree.size(), 4);
    EXPECT_EQ(root->right->color, B);
    EXPECT_EQ(root->right->data, 50);

    tree.erase(10);
    EXPECT_EQ(tree.size(), 3);
    EXPECT_EQ(root->data, 40);
    EXPECT_EQ(root->left->data, 5);
    EXPECT_EQ(root->right->data, 50);
    EXPECT_EQ(root->left->color, B);

    tree.insert(10);
    EXPECT_FALSE(tree.insert(10));
    EXPECT_EQ(root->left->right->color, R);
    EXPECT_EQ(root->left->right->data, 10);
}

TEST(RedBlackTreeTest, MinMax) {
    PoolRBT<int, 5> pool;
    RedBlackTree<int, 5> tree(pool);

    EXPECT_EQ(tree.min(), nullptr);
    EXPECT_EQ(tree.max(), nullptr);

    tree.insert(30);
    EXPECT_EQ(*tree.min(), 30);
    EXPECT_EQ(*tree.max(), 30);

    tree.insert(20);
    tree.insert(40);
    tree.insert(25);
    EXPECT_EQ(*tree.min(), 20);
    EXPECT_EQ(*tree.max(),40);
}

TEST(RedBlackTreeTest, Clear) {
    PoolRBT<int, 5> pool;
    RedBlackTree<int, 5> tree(pool);

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    EXPECT_FALSE(tree.insert(50));
    EXPECT_FALSE(tree.insert(60));
    EXPECT_TRUE(tree.isFull());

    tree.clear();
    EXPECT_TRUE(tree.isEmpty());

    EXPECT_TRUE(tree.insert(50));
    EXPECT_TRUE(tree.insert(100));
}