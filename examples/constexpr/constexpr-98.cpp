#include<cstdio>

template<unsigned N>
struct popcount_t;

template<>
struct popcount_t<0>
{
  enum { value = 0 };
};

template<unsigned N>
struct popcount_t
{
  enum
    {
      value =
        (N == 0)
        ? 0
        : ((N & 1) + popcount_t<N >> 1>::value)
    };
};

int popcount(unsigned n)
{
  return (n == 0) ? 0 : ((n & 1) + popcount(n >> 1));
}

int main(int argc, char**)
{
  int array[popcount_t<45>::value];
  printf("%d\n", popcount(argc));
}
