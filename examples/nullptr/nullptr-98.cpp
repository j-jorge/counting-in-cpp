#include <cstddef>

void foo(int) {}
void foo(int*) {}

int main(int argc, char** argv)
{
  foo(NULL);
  return 0;
}
