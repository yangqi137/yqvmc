#ifndef YQVMC_MEASURES_OFFSETS_CORRELATION_MEAN_AND_ERROR_HPP
#define YQVMC_MEASURES_OFFSETS_CORRELATION_MEAN_AND_ERROR_HPP

#include "mean_and_error_array.hpp"

namespace yqvmc {
  template <class OP, class OFFSETS_GEN>
  class OffsetsCorrMAEAdaptor {
  public:
    typedef OP Operator;
    typedef OFFSETS_GEN OffsetsGenerator;

    typedef typename OffsetsGenerator::OffsetCat OffsetCat;
    typedef typename OffsetCat::Lattice Lattice;

    typedef typename Operator::value_type value_type;

  public:
    OffsetsCorrMAEAdaptor(const Lattice& lattice)
      : adaptor(Operator(OffsetsGenerator::generate(lattice), lattice)) {}

    template <typename C>
    void measure(const C& conf) { adaptor.measure(conf); }

    std::size_t size() const { return adaptor.size(); }
    value_type mean(std::size_t i) const { return adaptor.mean(i); }
    value_type error(std::size_t i) const { return adaptor.error(i); }

  private:
    MeanAndErrorArrayAdaptor<Operator> adaptor;

  };

}

#endif
