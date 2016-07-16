#ifndef YQVMC_MEASURES_MEAN_AND_ERROR_ADAPTOR_HPP
#define YQVMC_MEASURES_MEAN_AND_ERROR_ADAPTOR_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>

namespace yqvmc {
  template <class OPERATOR_T>
  class MeanAndErrorAdaptor {
  public:
    typedef OPERATOR_T Operator;

  public:
    MeanAndErrorAdaptor(Operator f_)
      : f(f_) {}

    template <typename C>
    void measure(const C& conf) {
      acc(f.measure(conf));
    }

    double mean() const {
      return boost::accumulators::mean(acc);
    }
    
    double error() const {
      return boost::accumulators::error_of<tag_mean>(acc);
    }

  private:
    Operator f;
    typedef boost::accumulators::tag::mean tag_mean;
    typedef boost::accumulators::tag::error_of<tag_mean> tag_error;
    typedef boost::accumulators::stats<tag_mean, tag_error> stats;
    boost::accumulators::accumulator_set<double, stats> acc;
  };

  template <class Op>
  MeanAndErrorAdaptor<Op> MakeMeanAndErrorAdaptor(Op f) {
    return MeanAndErrorAdaptor<Op>(f);
  }
}

#endif
