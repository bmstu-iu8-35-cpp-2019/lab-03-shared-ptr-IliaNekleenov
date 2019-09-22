// Copyright 2019 IliaNekleenov <neiluha@mail.ru>

#include <gtest/gtest.h>

#include <header.hpp>

TEST(SHARED_PTR, init) {
  SharedPtr<int> ptr;
  EXPECT_FALSE(ptr);
  EXPECT_EQ(ptr.use_count(), 0);
  // EXPECT_THROW(*ptr, std::logic_error("attempt to get value of nullptr"));
  int* value = new int(5);
  SharedPtr<int> p(value);
  EXPECT_EQ(p.use_count(), 1);
  EXPECT_EQ(*p, 5);
  EXPECT_TRUE(p);
  SharedPtr<int> p1(p);
  EXPECT_EQ(p.use_count(), p1.use_count());
  EXPECT_EQ(p.use_count(), 2);
  EXPECT_EQ(*p1, 5);
  EXPECT_TRUE(p1);
}

TEST(SHARED_PTR, assign) {
  int* value = new int(8);
  SharedPtr<int> p(value);
  int* anoth_val = new int(2);
  SharedPtr<int> p1(anoth_val);
  p = p1;
  EXPECT_EQ(p.use_count(), p1.use_count());
  EXPECT_EQ(p.use_count(), 2);
  EXPECT_EQ(*p1, *p);
  EXPECT_TRUE(p1);
}

TEST(SHARED_PTR, test_of_reset) {
  int* value = new int(3);
  SharedPtr<int> p(value);
  SharedPtr<int> p1(p);
  EXPECT_EQ(p.use_count(), 2);
  p.reset();
  EXPECT_FALSE(p);
  EXPECT_EQ(p.use_count(), 0);
  EXPECT_EQ(p1.use_count(), 1);
  int* val = new int(10);
  p1.reset(val);
  EXPECT_EQ(p1.use_count(), 1);
  EXPECT_EQ(*p1, 10);
}

TEST(SHARED_PTR, test_of_swap) {
  int* value = new int(3);
  SharedPtr<int> p(value);
  int* val = new int(10);
  SharedPtr<int> p1(val);
  p1.swap(p);
  EXPECT_EQ(p1.use_count(), 1);
  EXPECT_EQ(p.use_count(), 1);
  EXPECT_EQ(*p1, 3);
  EXPECT_EQ(*p, 10);
}
