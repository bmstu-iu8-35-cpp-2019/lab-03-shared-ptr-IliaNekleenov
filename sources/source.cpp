// Copyright 2019 IliaNekleenov <neiluha@mail.ru>

#include <header.hpp>

counter::counter() : count(0) {}
counter::counter(int c) : count(c) {}
void counter::increase() { count++; }
void counter::decrease() {
  if (count > 0) {
    count--;
  } else {
    throw std::logic_error("decreasing of zero-count");
  }
}
bool counter::operator==(const int& a) const { return (count == a); }
int counter::get() const { return static_cast<int>(count); }
