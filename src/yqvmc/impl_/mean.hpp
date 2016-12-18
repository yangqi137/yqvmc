#ifndef YQVMC_IMPL_MEAN_HPP
#define YQVMC_IMPL_MEAN_HPP

#include <cstddef>

namespace yqvmc {
  namespace impl_ {
    template <typename T, typename Enable = void>
    class MeanAcc; // General implementation not provided.

    template <typename T>
    class MeanAcc<T,
    typename std::enable_if<std::is_arithmetic<T>::value>::type> {
    public:
      typedef T input_type;
      typedef typename std::conditional<std::is_integral<input_type>::value,
        double, input_type>::type result_type;

      MeanAcc() : m_sum(0), m_counter(0) {}

      void operator (input_type v) { m_sum += v; m_counter++; }
      result_type mean() const {
        return ((result_type)m_sum) / m_counter;
      }

      std::size_t count() const { return m_counter; }

      void reset() { m_sum = 0; m_counter = 0;}

    private:
      input_type m_sum;
      std::size_t m_counter;

    };

  }
}

#endif
