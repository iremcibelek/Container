#include "pch.h"
#include "StaticVector.h"


// --------------------------------------------------
// push_back()
// --------------------------------------------------

TEST(StaticVectorTest, PushBack)
{
    StaticVector<int, 6> vec;

    EXPECT_TRUE(vec.push_back(10));
    EXPECT_TRUE(vec.push_back(20));

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
}


// --------------------------------------------------
// push_back() - kapasite dolunca
// --------------------------------------------------

TEST(StaticVectorTest, PushBackWhenFull)
{
    StaticVector<int, 2> vec;

    EXPECT_TRUE(vec.push_back(10));
    EXPECT_TRUE(vec.push_back(20));

    EXPECT_FALSE(vec.push_back(30));

    EXPECT_EQ(vec.size(), 2);
    EXPECT_TRUE(vec.full());
}


// --------------------------------------------------
// pop_back()
// --------------------------------------------------

TEST(StaticVectorTest, PopBack)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);
    vec.push_back(20);

    EXPECT_TRUE(vec.pop_back());

    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 10);
}


// --------------------------------------------------
// pop_back() - boþ vector
// --------------------------------------------------

TEST(StaticVectorTest, PopBackEmpty)
{
    StaticVector<int, 2> vec;

    EXPECT_FALSE(vec.pop_back());
    EXPECT_EQ(vec.size(), 0);
}


// --------------------------------------------------
// operator[]
// --------------------------------------------------

TEST(StaticVectorTest, IndexOperator)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);
    vec.push_back(20);

    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
}


// --------------------------------------------------
// at()
// --------------------------------------------------

TEST(StaticVectorTest, At)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);

    EXPECT_NE(vec.at(0), nullptr);
    EXPECT_EQ(*vec.at(0), 10);
}


// at() - geçersiz index
TEST(StaticVectorTest, AtInvalidIndex)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);

    EXPECT_EQ(vec.at(1), nullptr);
    EXPECT_EQ(vec.at(100), nullptr);
}


// --------------------------------------------------
// size()
// --------------------------------------------------

TEST(StaticVectorTest, Size)
{
    StaticVector<int, 6> vec;

    EXPECT_EQ(vec.size(), 0);

    vec.push_back(10);
    EXPECT_EQ(vec.size(), 1);

    vec.push_back(20);
    EXPECT_EQ(vec.size(), 2);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
}


// --------------------------------------------------
// capacity()
// --------------------------------------------------

TEST(StaticVectorTest, Capacity)
{
    StaticVector<int, 2> vec;

    EXPECT_EQ(vec.capacity(),2);
}


// --------------------------------------------------
// empty()
// --------------------------------------------------

TEST(StaticVectorTest, Empty)
{
    StaticVector<int, 6> vec;

    EXPECT_TRUE(vec.empty());

    vec.push_back(10);

    EXPECT_FALSE(vec.empty());

    vec.pop_back();

    EXPECT_TRUE(vec.empty());
}


// --------------------------------------------------
// full()
// --------------------------------------------------

TEST(StaticVectorTest, Full)
{
    StaticVector<int, 2> vec;

    EXPECT_FALSE(vec.full());

    vec.push_back(10);
    EXPECT_FALSE(vec.full());

    vec.push_back(20);
    EXPECT_TRUE(vec.full());

    vec.pop_back();
    EXPECT_FALSE(vec.full());
}


// --------------------------------------------------
// front()
// --------------------------------------------------

TEST(StaticVectorTest, Front)
{
    StaticVector<int, 2> vec;

    EXPECT_EQ(vec.front(), nullptr);

    //vec.push_back(10);
    //vec.push_back(20);
    //ASSERT_NE(vec.front(), nullptr);

    vec.push_back(10);
    vec.push_back(20);

    EXPECT_EQ(*vec.front(), 10);
}


// --------------------------------------------------
// back()
// --------------------------------------------------

TEST(StaticVectorTest, Back)
{
    StaticVector<int, 6> vec;

    EXPECT_EQ(vec.back(), nullptr);

    vec.push_back(10);
    vec.push_back(20);

    ASSERT_NE(vec.back(), nullptr);
    EXPECT_EQ(*vec.back(), 20);
}


// --------------------------------------------------
// clear()
// --------------------------------------------------

TEST(StaticVectorTest, Clear)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);
    vec.push_back(20);

    EXPECT_EQ(vec.size(), 2);

    vec.clear();

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}


// --------------------------------------------------
// exists()
// --------------------------------------------------

TEST(StaticVectorTest, Exists)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);
    vec.push_back(20);

    EXPECT_TRUE(vec.exists(10));
    EXPECT_TRUE(vec.exists(20));
    EXPECT_FALSE(vec.exists(30));
}


// --------------------------------------------------
// find()
// --------------------------------------------------

TEST(StaticVectorTest, Find)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);
    vec.push_back(20);

    int* result = vec.find(20);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, 20);

    EXPECT_EQ(vec.find(30), nullptr);
}


// --------------------------------------------------
// eraseByIndex()
// --------------------------------------------------

TEST(StaticVectorTest, EraseByIndex)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    EXPECT_TRUE(vec.eraseByIndex(1));

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 30);
}


// eraseByIndex() - geçersiz index
TEST(StaticVectorTest, EraseByIndexInvalidIndex)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);

    EXPECT_FALSE(vec.eraseByIndex(1));
    EXPECT_EQ(vec.size(), 1);
}


// --------------------------------------------------
// insertByIndex()
// --------------------------------------------------

TEST(StaticVectorTest, InsertByIndex)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);
    vec.push_back(30);

    EXPECT_TRUE(vec.insertByIndex(1, 20));

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);

    EXPECT_TRUE(vec.insertByIndex(3, 40));
    EXPECT_EQ(vec[3], 40);
}


// insertByIndex() - geçersiz index
TEST(StaticVectorTest, InsertByIndexInvalidIndex)
{
    StaticVector<int, 6> vec;

    vec.push_back(10);

    EXPECT_FALSE(vec.insertByIndex(5, 20));
    EXPECT_EQ(vec.size(), 1);
}


// insertByIndex() - vector full
TEST(StaticVectorTest, InsertByIndexWhenFull)
{
    StaticVector<int, 2> vec;

    vec.push_back(10);
    vec.push_back(20);

    EXPECT_FALSE(vec.insertByIndex(1, 15));

    EXPECT_EQ(vec.size(), 2);
}

// print() void tipinde ve return ile deger dondurmedigi icin
// karsýlastýrma yapýlamaz ve test'i yazýlamaz.
// std::string seklinde yazýlmýs olsaydý return'u olacagý icin testi yazýlabilirdi.

TEST(StaticVectorTest, aaa)
{
    StaticVector<int, 2> vec;

    vec.push_back(10);
    vec.push_back(20);

    int a = 3;
    
    EXPECT_EQ(vec[1], 20);

    std::cout << "a";
}