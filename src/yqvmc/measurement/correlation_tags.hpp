#ifndef YQVMC_MEASURES_CORRELATION_TAGS_HPP
#define YQVMC_MEASURES_CORRELATION_TAGS_HPP

namespace yqvmc {
  struct CorrOpTag {};
  struct TwoPointCorrOpTag : public CorrOpTag {};
  struct OffsetCorrOpTag : public CorrOpTag {};
}

#endif
