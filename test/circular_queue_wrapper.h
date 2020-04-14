#include <stdexcept>
#include <string>
extern "C" {
#include "circular_queue.h"
}

using namespace std;

using uint = unsigned int;

class cant_add_more_exception : public runtime_error {
public:
  cant_add_more_exception(string s) : runtime_error(s) {}
};

template <typename T> class CircularStackWrapper {
  struct circular_queue cs;

  static inline void code_check(int err_code) {
    switch (err_code) {
    case 0:
      return;
    case 2:
      throw cant_add_more_exception("Cant add more elements");
      break;
    default:
      throw runtime_error("Error while pushing element, code = " +
                          to_string(err_code));
    }
  }

public:
  CircularStackWrapper(uint capacity) {
    init_circular_queue(&cs, capacity, sizeof(T));
  }

  ~CircularStackWrapper() { clean_circular_queue(&cs); }

  void push(T &element) {
    code_check(push_circular_queue(&cs, (char *)&element));
  }
  void push(T &&element) { push(element); }

  T pop_back() {
    T result;
    code_check(pop_back_circular_queue(&cs, (char *)&result));
    return result;
  }

  T pop_front() {
    T result;
    code_check(pop_front_circular_queue(&cs, (char *)&result));
    return result;
  }

  T front_copy() {
    T result;
    code_check(front_circular_queue(&cs, (char *)&result));
    return result;
  }

  T back_copy() {
    T result;
    code_check(back_circular_queue(&cs, (char *)&result));
    return result;
  }

  T &front() {
    T *result;
    code_check(front_reference_circular_queue(&cs, (char **)&result));
    return *result;
  }

  T &back() {
    T *result;
    code_check(back_reference_circular_queue(&cs, (char **)&result));
    return *result;
  }

  uint size() {
    uint result;
    code_check(size_circular_queue(&cs, &result));
    return result;
  }

  bool empty() {
    int result;
    code_check(empty_circular_queue(&cs, &result));
    return (bool)result;
  }

  bool full() {
    int result;
    code_check(full_circular_queue(&cs, &result));
    return (bool)result;
  }

  uint capacity() { return cs.capacity; }
};
