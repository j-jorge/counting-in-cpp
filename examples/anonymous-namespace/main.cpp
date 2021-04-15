#include <cstdio>

struct foo
{
  foo(int i)
  {
    printf("main.cpp %d\n", i);
  }
};

void build_foo(int i);

int main(int argc, char** argv)
{
  build_foo(argc);
  foo f(argc);
}
