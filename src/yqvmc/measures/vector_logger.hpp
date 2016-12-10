#ifndef YQVMC_MEASURES_VECTOR_LOGGER_HPP
#define YQVMC_MEASURES_VECTOR_LOGGER_HPP

#include <vector>

namespace yqvmc {
  template <typename OP>
  class VectorLogger {
  public:
    typedef OP Op;
    typedef typename Op::result_type value_type;
    typedef const std::vector<value_type>& result_type;

    VectorLogger(Op& op) : m_op(op) {}

    template <typename Conf>
    void measure(const Conf& conf, std::size_t stamp) {
      m_data.push_back(m_op.measure(conf, stamp));
    }
    result_type result() const { return m_data; }

  private:
    Op& m_op;
    std::vector<value_type> m_data;
  };
}

#endif
