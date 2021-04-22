constexpr int count(unsigned n)
{
  return (n == 0) ? 0 : 1 + count(n - 1);
}

void foo()
{
  int array[count(900)];
  (void)array;
}
