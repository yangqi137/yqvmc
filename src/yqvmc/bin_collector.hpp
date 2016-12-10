#ifndef YQVMC_BIN_COLLECTOR_PLAIN_HPP
#define YQVMC_BIN_COLLECTOR_PLAIN_HPP

#include <tuple>
#include <iostream>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>

namespace yqvmc {
  template <class M, typename EnableCompositeResult = void>
  class BinCollectorPlain {
  public:
    typedef M Measure;
    typedef typename M::result_type result_type;

    BinCollectorPlain(std::string name, Measure& measure)
    : m_name(name), m_measure(measure) {}

    void collect(std::size_t iBin) {
      auto result = m_measure.result();
      m_acc(result);
      m_acc2(result * result);
      std::cout << m_name << ": " << result << std::endl;
    }

    void report() const {
      auto sum = boost::accumulators::sum(m_acc);
      auto sum2 = boost::accumulators::sum(m_acc2);
      double count = boost::accumulators::count(m_acc);
      auto mean = sum / count;
      auto error = sum2 / count - mean*mean;
      std::cout << m_name << " : " << mean
                << " +/- " << error
                << std::endl;
    }

  private:
    std::string m_name;
    Measure& m_measure;
    typedef boost::accumulators::tag::sum tag_sum;
    typedef boost::accumulators::tag::count tag_count;
    typedef boost::accumulators::stats<tag_sum, tag_count> stats;
    boost::accumulators::accumulator_set<result_type, stats> m_acc;
    boost::accumulators::accumulator_set<result_type, stats> m_acc2;
  };

  struct BinCollectorEmpty {
    void collect(std::size_t iBin) {}
  };

}

#endif
