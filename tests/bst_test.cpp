#include "../lib/src/BST.cpp"

#include <gtest/gtest.h>

TEST(BSTAddTestSuit, AddBoolTest) {
    BinarySearchTree::BinarySearchTree<bool> bst;
    bst.insert(true);
    ASSERT_EQ(bst.contains(true), true);
}

TEST(BSTAddTestSuit, AddCharTest) {
    BinarySearchTree::BinarySearchTree<char> bst;
    char s = '5';
    bst.insert(s);
    ASSERT_EQ(bst.contains(s), true);
}

TEST(BSTAddTestSuit, AddIntTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    ASSERT_EQ(bst.contains(INT32_MAX), true);
}

TEST(BSTAddTestSuit, AddLongLongTest) {
    BinarySearchTree::BinarySearchTree<int64_t> bst;
    bst.insert(INT64_MAX);
    ASSERT_EQ(bst.contains(INT64_MAX), true);
}

TEST(BSTAddTestSuit, AddStringTest) {
    BinarySearchTree::BinarySearchTree<std::string> bst;
    std::string s = "Random string";
    bst.insert(s);
    ASSERT_EQ(bst.contains(s), true);
}

TEST(BSTAddTestSuit, AddMultipleIntTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    ASSERT_EQ(bst.contains(INT32_MAX), true);
    ASSERT_EQ(bst.contains(INT32_MIN), true);
    ASSERT_EQ(bst.contains(0), true);
    ASSERT_EQ(bst.contains(3101), true);
    ASSERT_EQ(bst.contains(-239), true);
    ASSERT_EQ(bst.contains(30), false);
}

TEST(BSTFunctionalityTestSuit, BSTNextTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    ASSERT_EQ(*bst.next(0)->key, 3101);
    ASSERT_EQ(*bst.next(-300)->key, -239);
}

TEST(BSTFunctionalityTestSuit, BSTPrevTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    ASSERT_EQ(*bst.prev(0)->key, -239);
    ASSERT_EQ(*bst.prev(-300)->key, INT32_MIN);
}

TEST(BSTFunctionalityTestSuit, BSTMinTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    ASSERT_EQ(*bst.minimum(0)->key, -239);
    ASSERT_EQ(*bst.minimum(3101)->key, 3101);
}

TEST(BSTFunctionalityTestSuit, BSTMaxTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    ASSERT_EQ(*bst.maximum(0)->key, 3101);
    ASSERT_EQ(*bst.maximum(3101)->key, 3101);
}

TEST(BSTFunctionalityTestSuit, BSTSingleEraseTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.erase(0);
    ASSERT_EQ(bst.contains(0), false);
}

TEST(BSTFunctionalityTestSuit, BSTMultipleEraseTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.erase(0);
    bst.erase(-239);
    bst.erase(INT32_MIN);
    ASSERT_EQ(bst.contains(0), false);
    ASSERT_EQ(bst.contains(-239), false);
    ASSERT_EQ(bst.contains(INT32_MIN), false);
}

TEST(BSTFunctionalityTestSuit, BSTPreorderTraversalTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    auto it = bst.getPreorder();
    int ans[5] = {0, -239, INT32_MIN, 3101, INT32_MAX};
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTPreorderTraversalInsertTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    bst.insert(-50);
    auto it = bst.getPreorder();
    int ans[6] = {0, -239, INT32_MIN, -50, 3101, INT32_MAX};
    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTPreorderTraversaleraseTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    bst.erase(-239);
    auto it = bst.getPreorder();
    int ans[4] = {0, INT32_MIN, 3101, INT32_MAX};
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTInorderTraversalTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    auto it = bst.getInorder();
    int ans[5] = {INT32_MIN, -239, 0, 3101, INT32_MAX};
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTInorderTraversalInsertTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    bst.insert(-50);
    auto it = bst.getInorder();
    int ans[6] = {INT32_MIN, -239, -50, 0, 3101, INT32_MAX};
    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTInorderTraversaleraseTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    bst.erase(-239);
    auto it = bst.getInorder();
    int ans[4] = {INT32_MIN, 0, 3101, INT32_MAX};
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTPostorderTraversalTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    auto it = bst.getPostorder();
    int ans[5] = {INT32_MIN, -239, INT32_MAX, 3101, 0};
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTPostorderTraversalInsertTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    bst.insert(-50);
    auto it = bst.getPostorder();
    int ans[6] = {INT32_MIN, -50, -239, INT32_MAX, 3101, 0};
    for (int i = 0; i < 6; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTPostorderTraversalEraseTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    bst.erase(-239);
    auto it = bst.getPostorder();
    int ans[4] = {INT32_MIN, INT32_MAX, 3101, 0};
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(ans[i], it->getValue(i));
    }
}

TEST(BSTFunctionalityTestSuit, BSTCopyConstructorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    BinarySearchTree::BinarySearchTree<int32_t> bst1(bst);

    auto pre = bst.begin(BinarySearchTree::PreorderTraversalTag());
    auto pre1 = bst1.begin(BinarySearchTree::PreorderTraversalTag());
    auto in = bst.begin(BinarySearchTree::InorderTraversalTag());
    auto in1 = bst1.begin(BinarySearchTree::InorderTraversalTag());
    auto post = bst.begin(BinarySearchTree::PostorderTraversalTag());
    auto post1 = bst1.begin(BinarySearchTree::PostorderTraversalTag());
    while (pre != bst.end(BinarySearchTree::PreorderTraversalTag()) &&
           pre1 != bst1.end(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(pre == pre1);
        ASSERT_TRUE(in == in1);
        ASSERT_TRUE(post == post1);
        pre++;
        pre1++;
        in++;
        in1++;
        post++;
        post1++;
    }
    auto rpre = bst.rbegin(BinarySearchTree::PreorderTraversalTag());
    auto rpre1 = bst1.rbegin(BinarySearchTree::PreorderTraversalTag());
    auto rin = bst.rbegin(BinarySearchTree::InorderTraversalTag());
    auto rin1 = bst1.rbegin(BinarySearchTree::InorderTraversalTag());
    auto rpost = bst.rbegin(BinarySearchTree::PostorderTraversalTag());
    auto rpost1 = bst1.rbegin(BinarySearchTree::PostorderTraversalTag());
    while (rpre != bst.rend(BinarySearchTree::PreorderTraversalTag()) &&
           rpre1 != bst1.rend(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(rpre == rpre1);
        ASSERT_TRUE(rin == rin1);
        ASSERT_TRUE(rpost == rpost1);
        rpre++;
        rpre1++;
        rin++;
        rin1++;
        rpost++;
        rpost1++;
    }
}

TEST(BSTFunctionalityTestSuit, BSTCopyAssignmentConstructorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    BinarySearchTree::BinarySearchTree<int32_t> bst1 = bst;

    auto pre = bst.begin(BinarySearchTree::PreorderTraversalTag());
    auto pre1 = bst1.begin(BinarySearchTree::PreorderTraversalTag());
    auto in = bst.begin(BinarySearchTree::InorderTraversalTag());
    auto in1 = bst1.begin(BinarySearchTree::InorderTraversalTag());
    auto post = bst.begin(BinarySearchTree::PostorderTraversalTag());
    auto post1 = bst1.begin(BinarySearchTree::PostorderTraversalTag());
    while (pre != bst.end(BinarySearchTree::PreorderTraversalTag()) &&
           pre1 != bst1.end(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(pre == pre1);
        ASSERT_TRUE(in == in1);
        ASSERT_TRUE(post == post1);
        pre++;
        pre1++;
        in++;
        in1++;
        post++;
        post1++;
    }
    auto rpre = bst.rbegin(BinarySearchTree::PreorderTraversalTag());
    auto rpre1 = bst1.rbegin(BinarySearchTree::PreorderTraversalTag());
    auto rin = bst.rbegin(BinarySearchTree::InorderTraversalTag());
    auto rin1 = bst1.rbegin(BinarySearchTree::InorderTraversalTag());
    auto rpost = bst.rbegin(BinarySearchTree::PostorderTraversalTag());
    auto rpost1 = bst1.rbegin(BinarySearchTree::PostorderTraversalTag());
    while (rpre != bst.rend(BinarySearchTree::PreorderTraversalTag()) &&
           rpre1 != bst1.rend(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(rpre == rpre1);
        ASSERT_TRUE(rin == rin1);
        ASSERT_TRUE(rpost == rpost1);
        rpre++;
        rpre1++;
        rin++;
        rin1++;
        rpost++;
        rpost1++;
    }
}

TEST(BSTFunctionalityTestSuit, BSTEmptyTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    ASSERT_TRUE(bst.empty());
    bst.insert(0);
    bst.insert(3101);
    bst.erase(0);
    bst.erase(3101);
    ASSERT_TRUE(bst.empty());
}

TEST(BSTFunctionalityTestSuit, BSTClearTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);
    bst.clear();
    ASSERT_TRUE(bst.empty());
}

TEST(BSTFunctionalityTestSuit, BSTEqualsTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    BinarySearchTree::BinarySearchTree<int32_t> bst1(bst);
    ASSERT_TRUE(bst == bst1);

    BinarySearchTree::BinarySearchTree<int32_t> bst2 = bst;
    ASSERT_TRUE(bst == bst2);

    BinarySearchTree::BinarySearchTree<int32_t> bst3;
    bst3.insert(0);
    bst3.insert(3101);
    bst3.insert(-239);
    bst3.insert(INT32_MAX);
    bst3.insert(INT32_MIN);
    ASSERT_TRUE(bst == bst3);
}

TEST(BSTFunctionalityTestSuit, BSTNotEqualsTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    BinarySearchTree::BinarySearchTree<int32_t> bst1(bst);
    bst1.erase(0);
    ASSERT_FALSE(bst == bst1);

    BinarySearchTree::BinarySearchTree<int32_t> bst2 = bst;
    bst2.erase(3101);
    ASSERT_FALSE(bst == bst2);

    BinarySearchTree::BinarySearchTree<int32_t> bst3;
    bst3.insert(0);
    bst3.insert(3101);
    bst3.insert(-239);
    bst3.insert(INT32_MAX);
    bst3.insert(INT32_MIN);
    bst3.insert(90302);
    ASSERT_FALSE(bst == bst3);
}

TEST(BSTFunctionalityTestSuit, BSTSwapTest) {
    BinarySearchTree::BinarySearchTree<int32_t> q;
    q.insert(1);
    q.insert(2);
    q.insert(3);
    q.insert(4);
    BinarySearchTree::BinarySearchTree<int32_t> w;
    w.insert(11);
    w.insert(12);
    w.insert(13);

    q.swap(w);
    int32_t qa[3] = {11, 12, 13};
    int i = 0;
    auto it = q.begin(BinarySearchTree::PreorderTraversalTag());
    while (it != q.end(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(*it++ == qa[i++]);
    }
    int32_t wa[4] = {1, 2, 3, 4};
    i = 0;
    it = w.begin(BinarySearchTree::PreorderTraversalTag());
    while (it != w.end(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(*it++ == wa[i++]);
    }

    swap(q, w);
    i = 0;
    it = q.begin(BinarySearchTree::PreorderTraversalTag());
    while (it != q.end(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(*it++ == wa[i++]);
    }
    i = 0;
    it = w.begin(BinarySearchTree::PreorderTraversalTag());
    while (it != w.end(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_TRUE(*it++ == qa[i++]);
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPrefixIncrementIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.begin(BinarySearchTree::PreorderTraversalTag());
    auto traversal = bst.getPreorder();
    for (int i = 0; i < traversal->getSize(); ++i) {
        ASSERT_EQ(traversal->getValue(i), *it);
        ++it;
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPostfixIncrementIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.begin(BinarySearchTree::PreorderTraversalTag());
    auto traversal = bst.getPreorder();
    for (int i = 0; i < traversal->getSize(); ++i) {
        ASSERT_EQ(traversal->getValue(i), *it);
        it++;
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPrefixDecrementIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.end(BinarySearchTree::PreorderTraversalTag());
    --it;
    auto traversal = bst.getPreorder();
    for (int i = traversal->getSize() - 1; i >= 0; --i) {
        ASSERT_EQ(traversal->getValue(i), *it);
        --it;
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPostfixDecrementIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.end(BinarySearchTree::PreorderTraversalTag());
    it--;
    auto traversal = bst.getPreorder();
    for (int i = traversal->getSize() - 1; i >= 0; --i) {
        ASSERT_EQ(traversal->getValue(i), *it);
        it--;
    }
}

TEST(BSTIteratorTestSuit, BSTInorderTraversalBeginIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.begin(BinarySearchTree::InorderTraversalTag());
    auto traversal = bst.getInorder();
    int i = 0;
    while (it != bst.end(BinarySearchTree::InorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i++), *it++);
    }
}

TEST(BSTIteratorTestSuit, BSTInorderTraversalEndIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.end(BinarySearchTree::InorderTraversalTag());
    --it;
    auto traversal = bst.getInorder();
    int i = 4;
    while (it != bst.begin(BinarySearchTree::InorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i--), *it--);
    }
}

TEST(BSTIteratorTestSuit, BSTPostorderTraversalBeginIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.begin(BinarySearchTree::PostorderTraversalTag());
    auto traversal = bst.getPostorder();
    for (int i = 0; i < traversal->getSize(); ++i) {
        ASSERT_EQ(traversal->getValue(i), *it);
        ++it;
    }
}

TEST(BSTIteratorTestSuit, BSTPostorderTraversalEndIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.end(BinarySearchTree::PostorderTraversalTag());
    --it;
    auto traversal = bst.getPostorder();
    int i = 4;
    while (it != bst.begin(BinarySearchTree::PostorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i--), *it--);
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPrefixIncrementReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rbegin(BinarySearchTree::PreorderTraversalTag());
    auto traversal = bst.getPreorder();
    int i = 4;
    while (it != bst.rend(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i--), *it);
        ++it;
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPostfixIncrementReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rbegin(BinarySearchTree::PreorderTraversalTag());
    auto traversal = bst.getPreorder();
    int i = 4;
    while (it != bst.rend(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i--), *it);
        it++;
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPrefixDecrementReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rend(BinarySearchTree::PreorderTraversalTag());
    --it;
    auto traversal = bst.getPreorder();
    int i = 0;
    while (it != bst.rbegin(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i++), *it);
        --it;
    }
}

TEST(BSTIteratorTestSuit, BSTPreorderTraversalPostfixDecrementReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rend(BinarySearchTree::PreorderTraversalTag());
    it--;
    auto traversal = bst.getPreorder();
    int i = 0;
    while (it != bst.rbegin(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i++), *it);
        it--;
    }
}

TEST(BSTIteratorTestSuit, BSTInorderTraversalBeginReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rbegin(BinarySearchTree::InorderTraversalTag());
    auto traversal = bst.getInorder();
    int i = 4;
    while (it != bst.rend(BinarySearchTree::InorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i--), *it);
        ++it;
    }
}

TEST(BSTIteratorTestSuit, BSTInorderTraversalEndReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rend(BinarySearchTree::InorderTraversalTag());
    --it;
    auto traversal = bst.getInorder();
    int i = 0;
    while (it != bst.rbegin(BinarySearchTree::InorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i++), *it);
        --it;
    }
}

TEST(BSTIteratorTestSuit, BSTPostorderTraversalBeginReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rbegin(BinarySearchTree::PostorderTraversalTag());
    auto traversal = bst.getPostorder();
    int i = 4;
    while (it != bst.rbegin(BinarySearchTree::PostorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i--), *it);
        ++it;
    }
}

TEST(BSTIteratorTestSuit, BSTPostorderTraversalEndReverseIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.rend(BinarySearchTree::PostorderTraversalTag());
    --it;
    auto traversal = bst.getPostorder();
    int i = 0;
    while (it != bst.rbegin(BinarySearchTree::PostorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i++), *it);
        --it;
    }
}

TEST(BSTIteratorTestSuit, BSTIteratorBidirectionalIteratorTest) {
    BinarySearchTree::BinarySearchTree<int32_t> bst;
    bst.insert(0);
    bst.insert(3101);
    bst.insert(-239);
    bst.insert(INT32_MAX);
    bst.insert(INT32_MIN);

    auto it = bst.begin(BinarySearchTree::PreorderTraversalTag());
    auto traversal = bst.getPreorder();
    int i = 0;
    while (it != bst.end(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i++), *it);
        it++;
    }
    --i;
    --it;
    while (it != bst.begin(BinarySearchTree::PreorderTraversalTag())) {
        ASSERT_EQ(traversal->getValue(i--), *it);
        --it;
    }
}