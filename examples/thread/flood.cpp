#include <cstdio>
#include <mutex>
#include <thread>

struct flood_state
{
  int counter;
  std::mutex mutex;
};

int main()
{
  flood_state state;
  state.counter = 0;

  // std::thread's constructor takes the function to be executed in the thread
  // as its argument. Here we use a lambda @\aref{sec:lambda}@.
  std::thread increase
    ([&state]() -> void
     {
       while (true)
         {
           // Wait until the mutex is available and lock it.  std::unique_lock
           // automatically unlocks it when going out of scope. Good old RAII.
           const std::unique_lock<std::mutex> lock(state.mutex);
           ++state.counter;
         }
     });
  std::thread decrease
    ([&state]() -> void
     {
       while (true)
         {
           int counter;

           {
             // We limit the scope of the lock to the access to the shared
             // state.
             std::unique_lock<std::mutex> lock(state.mutex);
             counter = state.counter;
             state.counter -= 2;
           }

           // This is executed after the release of the mutex, so the state can
           // be accessed while printing.
           printf("%d\n", counter);
         }
     });

  // std::thread::join() wait until the thread is over (which will not happen in
  // our case as nothing breaks outside the infinite loops.
  increase.join();
  decrease.join();
}
