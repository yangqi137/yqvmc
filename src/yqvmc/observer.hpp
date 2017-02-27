#ifndef YQVMC_OBSERVER_PLAIN_HPP
#define YQVMC_OBSERVER_PLAIN_HPP

#include "impl_/mean_and_error.hpp"
#include <iostream>

namespace yqvmc {
  template <class M,
  class ACC = impl_::MeanAndErrorAcc<typename M::result_type> >
  class PlainObserver {
  public:
    typedef M Measure;
    typedef typename M::result_type input_type;
    typedef ACC Accumulator;
    typedef typename Accumulator::result_type result_type;

    PlainObserver(std::string name, Measure& measure)
    : m_name(name), m_measure(measure) {}

    template <typename Conf>
    void measure(const Conf& conf, std::size_t stamp) {
      m_measure.measure(conf, stamp);
    }

    void closeBin(std::size_t iBin) {
      auto result = m_measure.result();
      m_acc(result);
      std::cout << m_name << ": " << result << std::endl;
    }

    void report() const {
      auto mean = m_acc.mean();
      auto error = m_acc.error();

      std::cout << m_name << " : " << mean
                << " +/- " << error
                << std::endl;
    }

    result_type mean() const { return m_acc.mean(); }
    result_type error() const { return m_acc.error(); }

  private:
    std::string m_name;
    Measure& m_measure;
    Accumulator m_acc;
  };

  template <class M>
  PlainObserver<M> MakePlainObserver(std::string name, M& m) {
    return PlainObserver<M>(name, m);
  }

  template <typename M>
  class EmptyObserver {
  public:
    typedef M Measure;
    EmptyObserver(Measure& measure) : m_measure(measure) {}

    template <typename Conf>
    void measure(const Conf& conf, std::size_t stamp) {
      m_measure.measure(conf, stamp);
    }

    void closeBin(std::size_t iBin) {}

  private:
    Measure& m_measure;
  };

  template <class M>
  EmptyObserver<M> MakeEmptyObserver(M& m) {
    return EmptyObserver<M>(m);
  }

}

#endif
