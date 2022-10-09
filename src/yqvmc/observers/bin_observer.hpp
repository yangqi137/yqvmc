#ifndef YQVMC_OBSERVER_PLAIN_HPP
#define YQVMC_OBSERVER_PLAIN_HPP

// #include "impl_/mean_and_error.hpp"
#include <iostream>

namespace yqvmc {
  template <class M>
  class BinObserver {
  public:
    typedef M Measure;
    typedef typename M::result_type input_type;

    BinObserver(std::string name, Measure& measure,
                std::ostream& sout = std::cout)
    : m_name(name), m_measure(measure), m_sout(sout) {}

    template <typename Conf>
    void measure(const Conf& conf, std::size_t stamp) {
      m_measure.measure(conf, stamp);
    }

    void closeBin(std::size_t iBin) {
      auto result = m_measure.result();
      m_data.push_back(result);
      m_sout << m_name << ": " << result << std::endl;
    }

    template <typename T>
    void set_data(T& root) const {
      root[m_name] = m_data;
    }

    const std::vector<input_type>& data() const {
      return m_data;
    }

  private:
    std::string m_name;
    Measure& m_measure;
    std::ostream& m_sout;
    std::vector<input_type> m_data;
  };

  template <class M>
  BinObserver<M> MakeBinObserver(std::string name, M& m, std::ostream& sout = std::cout) {
    return BinObserver<M>(name, m, sout);
  }

}

#endif
