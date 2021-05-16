// This struct declares a type identical to T if and only if T is
// a float-like type. We are going to specialize it only for the
// valid types. For the other types, the missing type declaration
// in the struct will trigger a substitution failure.
template<typename T>
struct only_if_float_like;

template<>
struct only_if_float_like<float>
{
  typedef float type;
};

template<>
struct only_if_float_like<double>
{
  typedef double type;
};

template<typename T>
typename only_if_float_like<T>::type mix(T a, T b, T r)
{
  return r * a + (1 - r) * b;
}

