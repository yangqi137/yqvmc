#ifndef YQVMC_IMPL_MEAN_AND_ERROR_ACCUMULATOR_HPP
#define YQVMC_IMPL_MEAN_AND_ERROR_ACCUMULATOR_HPP

#include "mean.hpp"
#include <cmath>

namespace yqvmc {
  namespace impl_ {
    template <typename T>
    class MeanAndErrorAcc<T> {
    public:
      typedef T input_type;
      typedef typename Traits::result_type result_type;

      MeanAndErrorAcc() {}

      void operator(input_type x) {
        m_mean(x);
        m_x2mean(Traits::square(x));
      }

      result_type mean() const { return m_mean.mean(); }
      result_type error() const {
        result_type n = m_mean.count();
        result_type xmean = m_mean.mean();
        return Traits::standard_error(m_x2mean.mean(), xmean, n);
      }
      std::size_t count() const { return m_mean.count(); }
      void reset() { return m_mean.reset(); }

    private:
      Mean<result_type> m_mean;
      Mean<result_type> m_x2mean;
    };
  }
}

#endif
