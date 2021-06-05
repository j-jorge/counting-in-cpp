void foo(int) {}
void foo(int*) {}

int main(int argc, char** argv)
{
  foo(nullptr);

  return 0;
}
