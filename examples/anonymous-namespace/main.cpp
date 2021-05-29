#include <cstdio>

struct system
{
  system()
  {
    printf("main system\n");
  }
};

void init_sound_system();

int main()
{
  init_sound_system();
  system main_system;
}
