#include <cstdio>

template<unsigned N>
struct popcount;

template<>
struct popcount<0>
{
  static constexpr unsigned value = 0;
};

template<unsigned N>
struct popcount
{
  static constexpr unsigned value = N % 2 + popcount<(N >> 1)>::value;
};

int main()
{
  // In order to actually do the computation, we have to instantiate
  // a type and get the value declared inside this type.
  printf("%d\n", popcount<24>::value);
}
