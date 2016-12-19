#ifndef YQVMC_IMPL_MEAN_HPP
#define YQVMC_IMPL_MEAN_HPP

#include "mae_traits.hpp"
#include <cstddef>

namespace yqvmc {
  namespace impl_ {
    template <typename T, typename TRAITS = MeanAndErrorTraits<T> >
    class MeanAcc {
    public:
      typedef T input_type;
      typedef TRAITS Traits;
      typedef typename Traits::sum_type sum_type;
      typedef typename Traits::result_type result_type;

      MeanAcc() { reset(); }

      void operator() (input_type v) {
        Traits::add_to(m_sum, v);
        m_counter++;
      }

      result_type mean() const {
        return Traits::mean(m_sum, m_counter);
      }

      std::size_t count() const { return m_counter; }

      void reset() { Traits::set_zero(m_sum); m_counter = 0;}

    private:
      sum_type m_sum;
      std::size_t m_counter;

    };

  }
}

#endif
