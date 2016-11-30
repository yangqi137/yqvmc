#ifndef YQVMC_MEASURES_MEAN_AND_ERROR_VECTOR_ADAPTOR_HPP
#define YQVMC_MEASURES_MEAN_AND_ERROR_VECTOR_ADAPTOR_HPP

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>

#include <vector>
#include <algorithm>

namespace yqvmc {
  template <class OPERATOR_T>
  class MeanAndErrorVectorAdaptor {
  public:
    typedef OPERATOR_T Operator;
    typedef typename Operator::value_type value_type;

  public:
    MeanAndErrorVectorAdaptor(Operator f)
      : m_f(f), m_acc(f.size()) {}

    template <typename C>
    void measure(const C& conf) {
      auto x = f.measure(conf);
      std::size_t n = size();
      for (std::size_t i=0; i<n; i++)
        m_acc[i](x[i]);
    }

    std::size_t size() const { return m_acc.size(); }

    value_type mean(std::size_t i) const {
      return boost::accumulators::mean(m_acc[i]);
    }

    std::vector<value_type> mean() const {
      std::vector<value_type> vec(size());
      std::transform(m_acc.begin(), m_acc.end(), vec.begin(),
        boost::accumulators::mean);
      return vec;
    }

    value_type error(std::size_t i) const {
      return boost::accumulators::error_of<tag_mean>(m_acc[i]);
    }

    std::vector<value_type> error() const {
      std::vector<value_type> vec(size());
      std::transform(m_acc.begin(), m_acc.end(), vec.begin(),
        boost::accumulators::error_of<tag_mean>);
      return vec;
    }

  private:
    Operator m_f;
    typedef boost::accumulators::tag::mean tag_mean;
    typedef boost::accumulators::tag::error_of<tag_mean> tag_error;
    typedef boost::accumulators::stats<tag_mean, tag_error> stats;
    typedef boost::accumulators::accumulator_set<value_type, stats> aset;

    std::vector<aset> m_acc;
  };

  template <class Op>
  MeanAndErrorVectorAdaptor<Op> MakeMeanAndErrorVectorAdaptor(Op f) {
    return MeanAndErrorVectorAdaptor<Op>(f);
  }
}

#endif
