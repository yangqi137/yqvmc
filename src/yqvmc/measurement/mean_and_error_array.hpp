#ifndef YQVMC_MEASURES_MEAN_AND_ERROR_ARRAY_ADAPTOR_HPP
#define YQVMC_MEASURES_MEAN_AND_ERROR_ARRAY_ADAPTOR_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>

namespace yqvmc {
  template <class OPERATOR_T>
  class MeanAndErrorArrayAdaptor {
  public:
    typedef OPERATOR_T Operator;
    typedef typename Operator::value_type value_type;

  public:
    MeanAndErrorArrayAdaptor(Operator f_)
      : f(f_), acc(f.size()) {}

    template <typename C>
    void measure(const C& conf) {
      const value_type *x = f.measure(conf);
      std::size_t n = size();
      for (std::size_t i=0; i<n; i++)
	acc[i](x[i]);
    }

    std::size_t size() const { return acc.size(); }

    value_type mean(std::size_t i) const {
      return boost::accumulators::mean(acc[i]);
    }
    
    value_type error(std::size_t i) const {
      return boost::accumulators::error_of<tag_mean>(acc[i]);
    }

  private:
    Operator f;
    typedef boost::accumulators::tag::mean tag_mean;
    typedef boost::accumulators::tag::error_of<tag_mean> tag_error;
    typedef boost::accumulators::stats<tag_mean, tag_error> stats;
    typedef boost::accumulators::accumulator_set<value_type, stats> aset;

    std::vector<aset> acc;
  };

  template <class Op>
  MeanAndErrorArrayAdaptor<Op> MakeMeanAndErrorArrayAdaptor(Op f) {
    return MeanAndErrorArrayAdaptor<Op>(f);
  }
}

#endif
