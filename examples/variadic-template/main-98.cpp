#include "dispatcher-98.hpp"

// Some functions that will be called by our dispatcher
void on_event();
void also_on_event();
void on_message(const char* message);
void also_on_message(const char* message);
void on_long_message(const char* message_1, const char* message_2);
void also_on_long_message(const char* message_1, const char* message_2);

int main()
{
  // A dispatcher with no arguments and two scheduled functions.
  dispatcher<> zero;
  zero.queue(&on_event);
  zero.queue(&also_on_event);

  // A dispatcher with one argument and two scheduled functions.
  dispatcher<const char*> one;
  one.queue(&on_message);
  one.queue(&also_on_message);

  // A dispatcher with two argument and two scheduled functions.
  dispatcher<const char*, const char*> two;
  two.queue(&on_long_message);
  two.queue(&also_on_long_message);

  // Now we trigger the calls with the given arguments.
  zero.dispatch();
  one.dispatch("hello");
  two.dispatch("hello", "world");

  return 0;
}
