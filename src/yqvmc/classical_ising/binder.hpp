#ifndef YQVMC_CI_BINDER_HPP
#define YQVMC_CI_BINDER_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace yqvmc { namespace ci {
  class BinderCumulant {
  public:
    BinderCumulant() {}
    typedef double result_type;

    template <typename C>
    void measure(const C& conf, std::size_t stamp) {
      double m = 0.;
      for (bool spin : conf)
        m += spin ? +1. : -1.;
      m_acc(m);
    }

    result_type result() {
      double m4 = boost::accumulators::moment<4>(m_acc);
      double m2 = boost::accumulators::moment<2>(m_acc);
      return 1. - m4/3./m2/m2;
    }

  private:
    boost::accumulators::accumulator_set<double,
      boost::accumulators::stats<
        boost::accumulators::tag::moment<2>,
        boost::accumulators::tag::moment<4>
      >
    > m_acc;
  };
} }
#endif
