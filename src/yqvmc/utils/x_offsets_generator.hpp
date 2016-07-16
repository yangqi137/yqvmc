#ifndef YQVMC_UTILITIES_X_OFFSETS_GENERATOR_HPP
#define YQVMC_UTILITIES_X_OFFSETS_GENERATOR_HPP

#include <vector>

namespace yqvmc { namespace utils {
    template <typename OFFSET_CAT>
    struct XOffsetsGenerator {
      typedef OFFSET_CAT OffsetCat;
      typedef typename OffsetCat::Offset Offset;
      typedef typename OffsetCat::Lattice Lattice;
      typedef typename OffsetCat::Vid Vid;

      static std::vector<Offset> generate(const Lattice& lattice) {
	Vid n = OffsetCat::dx_max(lattice);

	std::vector<Offset> offsets(n);
	for (Vid i=0; i<n; i++)
	  offsets[i] = {i+1, 0};

	return offsets;
      }
    };
  }
}

#endif
