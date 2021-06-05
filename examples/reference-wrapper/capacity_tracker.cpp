#include <algorithm>
#include <cstdio>
#include <functional>

struct capacity_tracker
{
  // Decrease the capacity by the given value if it is not too much. Returns
  // false if the capacity has been decreased, true otherwise.
  //
  // Yes, the meaning of the return value is crap. It is just for the example,
  // so it matches the expectations of std::find() below. Don't do that at home.
  bool operator()(int value)
  {
    if (capacity < value)
      return true;

    capacity -= value;
    return false;
  }

  int capacity;
};

int main()
{
  capacity_tracker tracker = { 10 };
  const int values[] = { 3, 1, 2, 4, 5, 8, 6, 7 };

  // Decrease the capacity by the given values until the capacity becomes lower
  // than the value. The capacity is decreased along the way and thus reflects
  // the final value at the end.
  //
  // Even though the returned value is correct, the final capacity in the
  // tracker will be incorrect. Indeed, it is copied in the call to
  // std::find_if(), so any change has no impact on the local variable.
  const int* overflow = std::find_if(values, values + 8, tracker);

  printf
    ("remaining capacity: %d, overflow with %d\n", tracker.capacity, *overflow);

  // This one will work correctly, because a reference to the tracker is passed
  // to std::find_if.
  overflow = std::find_if(values, values + 8, std::ref(tracker));

  printf
    ("remaining capacity: %d, overflow with %d\n", tracker.capacity, *overflow);

  return 0;
}
