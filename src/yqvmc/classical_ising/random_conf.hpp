#ifndef YQVMC_CI_RANDOM_ISING_CONFIGURATION_HPP
#define YQVMC_CI_RANDOM_ISING_CONFIGURATION_HPP

#include <vector>
#include <random>

namespace yqvmc { namespace ci {
  template <class RG>
  std::vector<bool> RandomConfiguration(unsigned n, RG& rg) {
    std::uniform_int_distribution<> dist01(0, 1);
    std::vector<bool> conf(n);
    for (unsigned i=0; i<n; i++)
      conf[i] = (dist01(rg) == 1);
    return conf;
  }
} }

#endif
