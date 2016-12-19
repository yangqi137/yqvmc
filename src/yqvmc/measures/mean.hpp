#ifndef YQVMC_MEASURES_SIMPLE_MEAN_HPP
#define YQVMC_MEASURES_SIMPLE_MEAN_HPP

#include "../impl_/mean.hpp"

namespace yqvmc {
  template <typename OP,
  typename MEANACC = impl_::MeanAcc<typename OP::result_type> >
  class Mean {
  public:
    typedef OP Op;
    typedef MEANACC MeanAccumulator;
    typedef typename MeanAccumulator::result_type result_type;
    Mean(Op& op) : m_op(op) {}

    template <typename Conf>
    void measure(const Conf& conf, std::size_t stamp) {
      m_acc(m_op(conf, stamp));
    }

    result_type result() {
      auto mean = m_acc.mean();
      m_acc.reset();
      return mean;
    }

  private:
    Op& m_op;
    MeanAccumulator m_acc;
  };

  template <typename Op>
  Mean<Op> MakeMeanMeasure(Op& op) { return Mean<Op>(op); }
}
#endif
