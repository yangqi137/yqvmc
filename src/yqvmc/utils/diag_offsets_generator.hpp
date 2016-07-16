#ifndef YQVMC_UTILITIES_X_OFFSETS_GENERATOR_HPP
#define YQVMC_UTILITIES_X_OFFSETS_GENERATOR_HPP

#include <vector>
#include <algorithm>

namespace yqvmc { namespace utils {
    template <typename OFFSET_CAT>
    struct DiagOffsetsGenerator {
      typedef OFFSET_CAT OffsetCat;
      typedef typename OffsetCat::Offset Offset;
      typedef typename OffsetCat::Lattice Lattice;
      typedef typename OffsetCat::Vid Vid;

      static std::vector<Offset> generate(const Lattice& lattice) {
	Vid dx = OffsetCat::dx_max(lattice);
	Vid dy = OffsetCat::dy_max(lattice);
	Vid n = std::min(dx, dy);

	std::vector<Offset> offsets(n);
	for (Vid i=0; i<n; i++) {
	  //offsets[i] = {i+1, i+1};
	  offsets[i].dx = i+1;
	  offsets[i].dy = i+1;
	}

	return offsets;
      }
    };
  }
}

#endif
