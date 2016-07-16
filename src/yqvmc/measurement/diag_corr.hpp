#ifndef YQVMC_MEASURES_DIAGONAL_DIRECTION_CORRELATION_HPP
#define YQVMC_MEASURES_DIAGONAL_DIRECTION_CORRELATION_HPP

#include "../utils/diag_offsets_generator.hpp"
#include "offsets_corr.hpp"
#include "offsets_corr_mae.hpp"

namespace yqvmc {

  template <class OP, class OFFSET_CAT>
  using DiagCorr = 
    OffsetsCorrMAEAdaptor<OffsetsCorr<OP, OFFSET_CAT>,
			  utils::DiagOffsetsGenerator<OFFSET_CAT> >;

}

#endif
