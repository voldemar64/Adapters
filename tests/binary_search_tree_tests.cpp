#include <gtest/gtest.h>
#include "lib/BinarySearchTree.h"

TEST(BinarySearchTreeTest, begin) {
    BinarySearchTree<int> bst;
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    auto it = bst.begin<InOrder>();
    EXPECT_EQ(*it, 1);
}

TEST(BinarySearchTreeTest, end) {
    BinarySearchTree<int> bst;
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    auto it = bst.end<InOrder>();
    --it;
    EXPECT_EQ(*it, 3);
}

TEST(BinarySearchTreeTest, erase_element) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    EXPECT_EQ(bst.erase(5), 0);
}

TEST(BinarySearchTreeTest, count) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(5);
    EXPECT_EQ(bst.count(5), 1);
}


TEST(BinarySearchTreeTest, Merge_Trees) {
    BinarySearchTree<int> bst1, bst2;
    bst1.insert(2);
    bst1.insert(1);
    bst1.insert(3);
    bst2.insert(5);
    bst2.insert(6);
    bst2.insert(4);
    bst1.merge(bst2);
    EXPECT_TRUE(bst1.exists(3) && bst1.exists(6));
}


TEST(BinarySearchTreeTest, MaxSize) {
    BinarySearchTree<int> bst;
    EXPECT_GT(bst.max_size(), 0);
}

TEST(BinarySearchTreeTest, GetAllocator) {
    BinarySearchTree<int> bst;
    auto allocator = bst.get_allocator();
    auto ptr = allocator.allocate(1);
    ASSERT_NE(ptr, nullptr);
    allocator.construct(ptr, 1);
    EXPECT_EQ(*ptr, 1);
    allocator.destroy(ptr);
    allocator.deallocate(ptr, 1);
}

TEST(BinarySearchTreeTest, InOrderTraversal) {
    BinarySearchTree<int> bst;
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    std::vector<int> values;
    std::vector<int> ans = {1, 2, 3};

    for(auto it = bst.begin<InOrder>(); it != bst.end<InOrder>(); ++it) {
        values.push_back(*it);
    }

    EXPECT_EQ(values, ans);
}

