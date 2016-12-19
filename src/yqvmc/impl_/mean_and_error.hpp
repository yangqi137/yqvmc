#ifndef YQVMC_IMPL_MEAN_AND_ERROR_ACCUMULATOR_HPP
#define YQVMC_IMPL_MEAN_AND_ERROR_ACCUMULATOR_HPP

#include "mean.hpp"
#include <cmath>

namespace yqvmc {
  namespace impl_ {
    template <typename T, typename TRAITS = MeanAndErrorTraits<T> >
    class MeanAndErrorAcc {
    public:
      typedef T input_type;
      typedef TRAITS Traits;
      typedef typename Traits::result_type result_type;

      MeanAndErrorAcc() {}

      void operator ()(input_type x) {
        m_mean(x);
        m_x2mean(Traits::square(x));
      }

      result_type mean() const { return m_mean.mean(); }
      result_type error() const {
        auto n = m_mean.count();
        return Traits::standard_error(m_x2mean.mean(), m_mean.mean(), n);
      }
      std::size_t count() const { return m_mean.count(); }
      void reset() { m_mean.reset(); m_x2mean.reset(); }

    private:
      MeanAcc<input_type, Traits> m_mean;
      MeanAcc<input_type, Traits> m_x2mean;
    };
  }
}

#endif
