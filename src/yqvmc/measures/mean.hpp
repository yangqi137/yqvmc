#ifndef YQVMC_MEASURES_SIMPLE_MEAN_HPP
#define YQVMC_MEASURES_SIMPLE_MEAN_HPP

#include "impl_/mean.hpp"

namespace yqvmc {
  template <typename OP, MEANACC = impl_::MeanAcc<typename OP::result_type> >
  class Mean {
  public:
    typedef OP Op;
    typedef MEANACC MeanAccumulator;
    typedef typename MeanAccumulator::result_type result_type;
    Mean(Op& op) : m_op(op) {}

    template <typename Conf>
    void measure(const Conf& conf, std::size_t stamp) {
      m_mean(m_op.measure(conf, stamp));
      m_counter++;
    }

    result_type result() {
      auto mean = m_mean.mean();
      m_mean.reset();
      return mean;
    }

  private:
    Op& m_op;
    MeanAccumulator m_mean;
  };
}
#endif
