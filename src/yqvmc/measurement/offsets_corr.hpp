#ifndef YQVMC_MEASURES_OFFSETS_CORRELATION_HPP
#define YQVMC_MEASURES_OFFSETS_CORRELATION_HPP

#include <memory>

namespace yqvmc {
  template <class OP, class OFFSET_CAT>
  class OffsetsCorr {
  public:
    typedef OP Operator;
    typedef typename Operator::value_type value_type;
    typedef OFFSET_CAT OffsetCat;
    typedef OffsetsCorr<OP, OFFSET_CAT> self_type;
    typedef typename OffsetCat::LatticeCat LatticeCat;
    typedef typename OffsetCat::Offset Offset;
    typedef typename OffsetCat::Lattice Lattice;
    typedef typename OffsetCat::Vertex Vertex;
    typedef typename OffsetCat::Vid Vid;
  public:
    OffsetsCorr(const std::vector<Offset>& offsets,
		const Lattice& lattice)
      : ops(offsets.size()),
	results(new value_type[offsets.size()]) {
      std::size_t n = offsets.size();
      Vid N = LatticeCat::count(lattice);
      ops.resize(n);
      
      for (std::size_t d=0; d<n; d++) {
	ops[d].reserve(N);
	for (Vid i=0; i<N; i++) {
	  Vertex v = LatticeCat::vertex(i, lattice);
	  OffsetCat::shift(v, offsets[d], lattice);
	  Vid j = LatticeCat::vid(v, lattice);
	  ops[d].push_back(Operator(i, j, lattice));
	}
      }
    }

    OffsetsCorr(const self_type& other)
      : ops(other.ops), results(new value_type[other.size()]) {}
      
    std::size_t size() const { return ops.size(); }
      
    template <typename C>
    const value_type *measure(const C& conf) {
      std::size_t n = size();
      for (std::size_t i=0; i<n; i++) {
	results[i] = 0;
	for (Operator& op : ops[i])
	  results[i] += op.measure(conf);
	results[i] /= ops[i].size();
      }
      return results.get();
    }

  private:
    std::vector<std::vector<Operator> > ops;
    std::unique_ptr<value_type[]> results;
  };

}

#endif
