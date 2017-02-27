#ifndef YQVMC_MEASURES_TRANSFORMED_MEAN_HPP
#define YQVMC_MEASURES_TRANSFORMED_MEAN_HPP

#include "../impl_/mean.hpp"

namespace yqvmc {
  template <typename OP,
  typename MEANACC = impl_::MeanAcc<typename OP::result_type> >
  class TransformedMean {
  public:
    typedef OP Op;
    typedef MEANACC MeanAccumulator;
    typedef typename MeanAccumulator::result_type result_type;
    typedef std::function<result_type (result_type)> FuncType;
    TransformedMean(Op& op, const FuncType& func)
    : m_op(op), m_func(func) {}

    template <typename Conf>
    void measure(const Conf& conf, std::size_t stamp) {
      m_acc(m_func(m_op(conf, stamp)));
    }

    result_type result() {
      auto mean = m_acc.mean();
      m_acc.reset();
      return mean;
    }

  private:
    Op& m_op;
    FuncType m_func;
    MeanAccumulator m_acc;
  };

  template <typename Op, typename F>
  TransformedMean<Op> MakeTransformedMeanMeasure(Op& op, const F& f) {
    return TransformedMean<Op>(op, f);
  }
}
#endif
