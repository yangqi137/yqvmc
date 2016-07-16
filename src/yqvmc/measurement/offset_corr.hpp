#ifndef YQVMC_MEASURES_OFFSET_CORRELATION_HPP
#define YQVMC_MEASURES_OFFSET_CORRELATION_HPP

#error This file is depricated!

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/error_of_mean.hpp>

#include <vector>
#include <algorithm>

namespace yqvmc {
  template <class OP, class LATTICE_CAT, class OFFSET_CAT>
  class OffsetCorr {
  public:
    typedef OP Operator;
    typedef typename Operator::value_type value_type;
    typedef typename Operator::Configuration Configuration;
    typedef LATTICE_CAT LatticeCat;
    typedef OFFSET_CAT OffsetCat;
    typedef typename OffsetCat::Offset Offset;
    typedef typename Operator::Lattice Lattice;
    typedef typename Operator::Vid Vid;
  public:
    OffsetCorr(Offset offset, const Lattice& lattice_) {
      typedef typename OffsetCat::Vertex Vertex;

      Vid N = LatticeCat::count(lattice_);
      ops.reserve(N);

      for (Vid i=0; i<N; i++) {
	Vertex v = LatticeCat::vertex(i, lattice_);
	OffsetCat::shift(v, offset, lattice_);
	Vid j = LatticeCat::vid(v, lattice_);
	ops.push_back(Operator(i, j, lattice_));
      }
    }

    value_type measure(const Configuration& conf) {
      value_type corr = 0;
      for (const auto& op : ops)
	corr += op.measure(conf);
      corr /= ops.size();
      return corr;
    }

  private:
    std::vector<Operator> ops;    
  };
}

#endif
