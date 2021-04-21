#include<cstdio>

constexpr int popcount(unsigned n)
{
  return (n == 0) ? 0 : ((n & 1) + popcount(n >> 1));
}

int main(int argc, char**)
{
  int array[popcount(45)];
  printf("%d\n", popcount(argc));
}
