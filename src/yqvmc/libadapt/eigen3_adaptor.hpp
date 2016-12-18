#ifndef YQVMC_EXTERNAL_LIBRARY_ADAPTOR_EIGEN3_HPP
#define YQVMC_EXTERNAL_LIBRARY_ADAPTOR_EIGEN3_HPP

#include <Eigen/Array>
#include "impl_/mean_and_error.hpp"

namespace yqvmc {
  namespace impl_ {
    template <typename Derived>
    struct MAETraits<Eigen::ArrayBase<Derived>, void> {
    public:
      typedef Eigen::ArrayBase<Derived> result_type;

      MeanAcc() : m_counter(0) { m_sum.setZero(); }

      void operator(const result_type& v) {
        if (m_sum.size() == 0)
          m_sum = v;
        else
          m_sum += v;
      }

      result_type mean() const { return m_sum / m_counter; }
      void reset() { m_sum.setZero(); m_counter = 0.; }

      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
      result_type m_sum;
      std::size_t m_counter;
    };
  }
}

#endif
