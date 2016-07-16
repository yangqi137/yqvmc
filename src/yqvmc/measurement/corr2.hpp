#ifndef YQVMC_MEASUREMENT_ADAPTORS_CORRELATION_2OPERATOR_HPP
#define YQVMC_MEASUREMENT_ADAPTORS_CORRELATION_2OPERATOR_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>

namespace yqvmc {
  template <typename OP1, typename OP2>
  class Corr2Adaptor {
  public:
    typedef OP1 Op1;
    typedef OP2 Op2;

    Corr2Adaptor(const Op1 f1_, const Op2 f2_)
      : f1(f1_), f2(f2_) {}

    template <typename C>
      void measure(const C& c) {
      double v1 = f1.measure(c), v2 = f2.measure(c);
      acc1(v1); acc2(v2);
      acc12(v1*v2);
    }

    double mean1() const {
      return boost::accumulators::mean(acc1);
    }
    
    double error1() const {
      return std::sqrt(boost::accumulators::variance(acc1)/
		       (boost::accumulators::count(acc12)-1));
    }

    double mean2() const {
      return boost::accumulators::mean(acc2);
    }
    
    double error2() const {
      return std::sqrt(boost::accumulators::variance(acc2)/
		       (boost::accumulators::count(acc12)-1));
    }

    double mean12() const {
      return boost::accumulators::mean(acc12)
	- mean1() * mean2();
    }
    
    double error12() const {
      double v12 = mean12();
      double v1=boost::accumulators::variance(acc1);
      double v2=boost::accumulators::variance(acc2);
      double n = boost::accumulators::count(acc12);
      return std::sqrt((v12*v12+v1*v2)/(n-1));
    }


  private:
    Op1 f1;
    Op2 f2;
    typedef boost::accumulators::tag::mean tag_mean;
    typedef boost::accumulators::tag::variance tag_var;
    typedef boost::accumulators::tag::count tag_count;
    typedef boost::accumulators::stats<tag_mean, tag_var> stats;
    typedef boost::accumulators::stats<tag_mean, tag_count> stats2;
    boost::accumulators::accumulator_set<double, stats> acc1;
    boost::accumulators::accumulator_set<double, stats> acc2;
    boost::accumulators::accumulator_set<double, stats2> acc12;
  };

  template <typename T1, typename T2>
  Corr2Adaptor<T1, T2> MakeCorr2Adaptor(T1 t1, T2 t2) {
    return Corr2Adaptor<T1, T2>(t1, t2);
  }
}

#endif
