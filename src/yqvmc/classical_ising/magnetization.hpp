#ifndef YQVMC_CI_MAGNETIZATION_HPP
#define YQVMC_CI_MAGNETIZATION_HPP

#include <algorithm>
#include <cmath>

namespace yqvmc { namespace ci {
  struct Magnetization {
    typedef double value_type;
    template <typename Conf>
    value_type measure(const Conf& conf) {
      value_type m = 0.;
      for (bool s : conf) m += (s ? +1. : -1.);
      return std::abs(m / conf.size());
    }
  };
} }

#endif
