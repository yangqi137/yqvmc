#ifndef YQVMC_ENGINE_THE_ENGINE_HPP
#define YQVMC_ENGINE_THE_ENGINE_HPP

#include <tuple>

namespace yqvmc {
  class Engine {
  public:
    std::size_t warmup;
    std::size_t skip;
    std::size_t n;

  public:
    template <typename Configuration, 
	      typename Walker,
	      typename RG,
	      typename... Measures>
    void run(Configuration& conf, Walker& walker, 
	     RG& g, Measures&... measures) const {
      if (warmup>0)
          for (std::size_t i=0; i<warmup; i++)
              walker.walk(conf, g);

      for (std::size_t i=0; i<n; i++) {
          measure(conf, measures...);
          walker.walk(conf, g);
		  
          if (skip>0)
              for (std::size_t j=0; j<skip; j++)
                  walker.walk(conf, g);
      }
    }

    template <typename Configuration, 
	      typename Walker1,
	      typename Walker2,
	      typename RG,
	      typename... Measures>
    void run_warmupWalker(Configuration& conf, 
			  Walker1& walker1, Walker2& walker2,
			  RG& g, Measures&... measures) const {
      if (warmup>0)
          for (std::size_t i=0; i<warmup; i++)
              walker1.walk(conf, g);

      for (std::size_t i=0; i<n; i++) {
          measure(conf, measures...);
          walker2.walk(conf, g);
		  
          if (skip>0)
              for (std::size_t j=0; j<skip; j++)
                  walker2.walk(conf, g);
      }
    }

  private:
    template <typename Configuration>
    static void measure(const Configuration& conf) {}
    template <typename Configuration, typename Measure,
	      typename... OtherMeasures>
    static void measure(const Configuration& conf, Measure& m,
		   OtherMeasures&... otherMeasures) {
      m.measure(conf);
      measure(conf, otherMeasures...);
    }
  };

}

#endif
