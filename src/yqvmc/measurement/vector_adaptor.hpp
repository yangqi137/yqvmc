#ifndef YQVMC_MEASURES_VECTOR_ADAPTOR_HPP
#define YQVMC_MEASURES_VECTOR_ADAPTOR_HPP

#include <vector>

namespace yqvmc {
  template <class OPERATOR_T>
  class VectorAdaptor {
  public:
    typedef OPERATOR_T Operator;

  public:
    VectorAdaptor(Operator f_)
    : f(f_) {}

    template <typename C>
    void measure(const C& conf) {
      v.push_back(f.measure(conf));
    }

    const std::vector<double>& data() const { return v; }

  private:
    Operator f;
    std::vector<double> v;
  };

  template <class Op>
  VectorAdaptor<Op> MakeVectorAdaptor(Op f) { return VectorAdaptor<Op>(f); }
}

#endif
