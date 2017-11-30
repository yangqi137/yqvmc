#ifndef YQVMC_MPI_ENGINE_HPP
#define YQVMC_MPI_ENGINE_HPP

#include <mpi.h>
#include <tuple>

namespace yqvmc {
  class MPIEngine {
  public:
    std::size_t m_warmup;
    std::size_t m_skip;
    std::size_t m_binsize;
    std::size_t m_nbins;

  public:
    template <typename Configuration,
	      typename Walker,
	      typename RG,
	      typename... Observers>
    void run(Configuration& conf, Walker& walker, RG& g,
             Observers&... observers) const {
      int myrank;
      int worldSize;
      MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
      MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

      if (m_warmup>0)
          for (std::size_t i=0; i<m_warmup; i++)
              walker.walk(conf, g);

      while (true) {

        // Compute one bin.
        for (std::size_t i = 0; i < m_binsize; i++) {
          measure(conf, i+1, observers...);
          walker.walk(conf, g);
          if (m_skip > 0)
            for (std::size_t j=0; j < m_skip; j++)
              walker.walk(conf, g);
        }
        closeBin(ibin, observers...);

        if (myrank == 0) {
          // Checking new bins.

        }
        else {
          // Send new bin.
          // Check if we quit.          
        }

      }
    }

  private:
    template <typename Configuration>
    static void measure(const Configuration& conf, std::size_t stamp) {}
    template <typename Configuration, typename Observer,
	      typename... OtherObservers>
    static void measure(const Configuration& conf, std::size_t stamp,
       Observer& o, OtherObservers&... otherObservers) {
      o.measure(conf, stamp);
      measure(conf, stamp, otherObservers...);
    }

    static void closeBin(std::size_t ibin) {}
    template <typename Observer, typename... OtherObservers>
    static void closeBin(std::size_t ibin, Observer& o,
      OtherObservers&... otherObservers) {
      o.closeBin(ibin);
      closeBin(ibin, otherObservers...);
    }
  };

}

#endif
