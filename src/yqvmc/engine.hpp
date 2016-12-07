#ifndef YQVMC_ENGINE_THE_ENGINE_HPP
#define YQVMC_ENGINE_THE_ENGINE_HPP

#include <tuple>

namespace yqvmc {
  class Engine {
  public:
    std::size_t m_warmup;
    std::size_t m_skip;
    std::size_t m_binsize;
    std::size_t m_nbins;

  public:
    template <typename Configuration,
	      typename Walker,
	      typename RG,
        typename BinCollector,
	      typename... Measures>
    void run(Configuration& conf, Walker& walker, RG& g,
             BinCollector& binCol, Measures&... measures) const {
      if (m_warmup>0)
          for (std::size_t i=0; i<m_warmup; i++)
              walker.walk(conf, g);

      for (std::size_t ibin = 0; ibin < m_nbins; ibin++) {
        for (std::size_t i = 0; i < m_binsize; i++) {
          measure(conf, i, measures...);
          walker.walk(conf, g);
          if (m_skip > 0)
            for (std::size_t j=0; j < m_skip; j++)
              walker.walk(conf, g);
        }
        binCol.collect(ibin);
      }
    }

  private:
    template <typename Configuration>
    static void measure(const Configuration& conf, std::size_t stamp) {}
    template <typename Configuration, typename Measure,
	      typename... OtherMeasures>
    static void measure(const Configuration& conf, std::size_t stamp,
       Measure& m, OtherMeasures&... otherMeasures) {
      m.measure(conf, stamp);
      measure(conf, stamp, otherMeasures...);
    }
  };

}

#endif
