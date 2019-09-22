// Copyright 2019 IliaNekleenov <neiluha@mail.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <stdexcept>
#include <utility>

class counter {
  std::atomic<int> count;

 public:
  counter();
  explicit counter(int c);
  void increase();
  void decrease();
  bool operator==(const int& a) const;
  int get() const;
};

template <typename T>
class SharedPtr {
  counter* c_ptr;
  T* data;

 public:
  SharedPtr() {
    c_ptr = nullptr;
    data = nullptr;
  }
  explicit SharedPtr(T* p) {
    c_ptr = new counter(1);
    data = p;
  }
  SharedPtr(const SharedPtr& r) {
    c_ptr = r.c_ptr;
    if (r) c_ptr->increase();
    data = r.data;
  }
  SharedPtr(const SharedPtr&& r) {
    c_ptr = r.c_ptr;
    if (r) c_ptr->increase();
    data = r.data;
  }
  auto operator=(const SharedPtr& r) -> SharedPtr<T>& {
    if (*this) {
      c_ptr->decrease();
      if (*c_ptr == 0) {
        delete c_ptr;
        delete data;
      }
    }
    c_ptr = r.c_ptr;
    data = r.data;
  }
  auto operator=(SharedPtr&& r) -> SharedPtr& {
    if (*this) {
      c_ptr->decrease();
      if (*c_ptr == 0) {
        delete c_ptr;
        delete data;
      }
    }
    c_ptr = r.c_ptr;
    data = r.data;
  }

  operator bool() const { return !(data == nullptr); }
  auto operator*() const -> T& {
    if (!*this) {
      throw std::logic_error("attempt to get value of nullptr");
    }
    return *data;
  }

  auto operator-> () const -> T* { return data; }
  auto get() -> T* { return data; }

  void reset() {
    if (!*this) return;
    c_ptr->decrease();
    if (*c_ptr == 0) {
      delete c_ptr;
      delete data;
    }
    c_ptr = nullptr;
    data = nullptr;
  }
  void reset(T* ptr) {
    if (*this) {
      c_ptr->decrease();
      if (*c_ptr == 0) {
        delete c_ptr;
        delete data;
      }
    }
    c_ptr = new counter(1);
    data = ptr;
  }
  void swap(SharedPtr& r) {
    if (data == r.data) return;
    auto buf = r;
    r = *this;
    *this = buf;
  }
  auto use_count() const -> size_t {
    if (!*this) return 0;
    return static_cast<size_t>(c_ptr->get());
  }
};

#endif  // INCLUDE_HEADER_HPP_
