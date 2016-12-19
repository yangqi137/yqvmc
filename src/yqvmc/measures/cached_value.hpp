#ifndef YQVMC_MEASURES_CACHED_VALUE_HPP
#define YQVMC_MEASURES_CACHED_VALUE_HPP

#include <cstddef>

namespace yqvmc {
  template <typename OP>
  class CachedValue {
  public:
    typedef OP Op;
    typedef typename Op::result_type result_type;

    CachedValue(Op& op, const value_type val = T())
    : m_op(op), m_value(val),
    m_stamp(0) {}

    template <typename Conf>
    result_type measure(const Conf& conf, std::size_t stamp = 0) {
      if (stamp != 0 && stamp == m_stamp)
        return m_value;
      else {
        m_value = m_op.measure(conf);
        m_stamp = stamp;
        return m_value;
      }
    }
  private:
    Op& m_op;
    T m_value;
    std::size_t m_stamp;
  };
}

#endif
