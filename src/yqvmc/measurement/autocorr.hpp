#ifndef YQVMC_MEASUREMENT_AUTOCORRELATION_HPP
#define YQVMC_MEASUREMENT_AUTOCORRELATION_HPP

#include <vector>
#include <boost/circular_buffer.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
//#include <iostream>
namespace yqvmc {
  template <typename OP>
  class AutocorrAdaptor {
  public:
    typedef OP Operator;
    typedef typename Operator::value_type value_type;

    AutocorrAdaptor(const Operator& op, unsigned size)
    : m_op(op), m_buffer(size), m_accumulators(size) {}

    template <typename Conf>
    void measure(const Conf& conf) {
      value_type v = m_op.measure(conf);
      m_buffer.push_back(v);
      m_meanAcc(v);

      std::size_t n = m_buffer.size();
      for (std::size_t i = 0; i < n; i++)
        m_accumulators[i](m_buffer[0] * m_buffer[i]);
    }

    value_type mean() const {
      return boost::accumulators::mean(m_meanAcc);
    }

    value_type tau() const {
      using boost::accumulators::mean;
      value_type mm2 = mean(m_meanAcc); mm2 *= mm2;
      //std::cout<<mm2;
      value_type c0 = mean(m_accumulators[0]) - mm2;
      value_type sum = c0;
      for (std::size_t i = 1; i < m_accumulators.size(); i++) {
        sum += mean(m_accumulators[i])-mm2;
      }
      return sum / c0;
    }

    std::vector<value_type> autocorr() const {
      using boost::accumulators::mean;
      value_type mm2 = mean(m_meanAcc); mm2 *= mm2;
      //std::cerr<<mm2;
      auto n = m_accumulators.size();
      std::vector<value_type> ac(n);
      for (std::size_t i = 0; i < n; i++)
        ac[i] = mean(m_accumulators[i]) - mm2;
      return ac;
    }

  private:
    Operator m_op;
    boost::circular_buffer<value_type> m_buffer;
    typedef boost::accumulators::tag::mean tag_mean;
    typedef boost::accumulators::stats<tag_mean> stats;
    typedef boost::accumulators::accumulator_set<value_type, stats> Accumulator;
    std::vector<Accumulator> m_accumulators;
    Accumulator m_meanAcc;
  };

  template <typename O>
  AutocorrAdaptor<O> MakeAutocorrAdaptor(const O& op, unsigned n) {
    return AutocorrAdaptor<O>(op, n);
  }
}

#endif
