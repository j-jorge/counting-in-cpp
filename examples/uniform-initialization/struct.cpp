#include <cstdio>
#include <utility>

struct foo_struct
{
  int a;
  int b;
};

struct foo_constructor
{
  foo_constructor(int v1, int v2)
    // Note that arguments and fields are swapped.
    : a(v2), b(v1)
  {}

  int a;
  int b;
};

struct foo_initializer_list
{
  foo_initializer_list(int v1, int v2)
    // Note that arguments and fields are still swapped.
    : a(v2), b(v1)
  {}

  // An initializer list allows to construct an object using an aggregate-like
  // syntax. We will come back to it in @\ref{initializer-list}@ :)
  foo_initializer_list(const std::initializer_list<int>& i)
    // Note that the fields are set to the same value.
    : a(*i.begin()),
      b(a)
  {}

  int a;
  int b;
};

template<typename Foo>
void build_foo(int x, int y)
{
  Foo foo{x, y};

  printf(".a=%d, .b=%d\n", foo.a, foo.b);
}

int main()
{
  build_foo<foo_struct>(24, 42);
  build_foo<foo_constructor>(24, 42);
  build_foo<foo_initializer_list>(24, 42);

  return 0;
}
