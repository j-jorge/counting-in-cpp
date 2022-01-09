#include<cstdio>

constexpr int popcount(unsigned n)
{
  int result = 0;

  for (; n != 0; n >>= 1)
    if ((n & 1) != 0)
      ++result;

  return result;
}

int main(int argc, char**)
{
  int array[popcount(45)];
  printf("%d\n", popcount(argc));

  return 0;
}
