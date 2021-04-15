#include <cstdio>

namespace
{
  struct foo
  {
    foo(int i)
    {
      printf("foo.cpp %d\n", i);
    }
  };
}

void build_foo(int i)
{
  foo f(i);
}
