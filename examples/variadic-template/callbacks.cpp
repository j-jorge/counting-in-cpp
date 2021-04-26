#include <cstdio>

void on_event()
{
  printf("on_event\n");
}

void also_on_event()
{
  printf("also_on_event\n");
}

void on_message(const char* message)
{
  printf("on_message: %s\n", message);
}

void also_on_message(const char* message)
{
  printf("also_on_message: %s\n", message);
}

void on_long_message(const char* message_1, const char* message_2)
{
  printf("on_long_message: %s, %s\n", message_1, message_2);
}

void also_on_long_message(const char* message_1, const char* message_2)
{
  printf("also_on_long_message: %s, %s\n", message_1, message_2);
}
