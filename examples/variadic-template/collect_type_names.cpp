#include <typeinfo>
#include <string>

template<typename... T>
void collect_type_names()
{
  const char* names[] = {typeid(T).name()...};

  for (const char* name : names)
    printf("%s\n", name);
}

int main()
{
  collect_type_names<int, float, std::string>();

  return 0;
}
