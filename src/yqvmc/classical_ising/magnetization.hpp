#ifndef YQVMC_CI_MAGNETIZATION_HPP
#define YQVMC_CI_MAGNETIZATION_HPP

#include <algorithm>
#include <cmath>
#include <limits>

namespace yqvmc { namespace ci {
  struct Magnetization {
    typedef double result_type;

    template <typename Conf>
    result_type operator()(const Conf& conf, std::size_t stamp = 0) {
      result_type m = 0.;
      for (bool s : conf) m += (s ? +1. : -1.);
      return std::abs(m / conf.size());
    }
  };
} }

#endif
