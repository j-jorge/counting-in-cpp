#include <cstdio>

// This is a variable, whose value depends upon a template argument.
template<unsigned N>
unsigned popcount = N % 2 + popcount<(N >> 1)>;

// The variable can be specialized too!
template<>
unsigned popcount<0> = 0;

int main()
{
  // Here we can use a variable to represent a value. Much more clear.
  printf("%d\n", popcount<24>);
}
