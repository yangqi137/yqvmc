#ifndef YQVMC_MEASURES_X_DIRECTION_CORRELATION_HPP
#define YQVMC_MEASURES_X_DIRECTION_CORRELATION_HPP

#include "../utils/x_offsets_generator.hpp"
#include "offsets_corr.hpp"

namespace yqvmc {

  template <class OP, class OFFSET_CAT>
  using XCorr = 
    OffsetsCorrMAEAdaptor<OffsetsCorr<OP, OFFSET_CAT>,
			  utils::XOffsetsGenerator<OFFSET_CAT> >;

}

#endif
