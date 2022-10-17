#ifndef YQVMC_NLOHMANN_JSON_ADAPTOR_HPP
#define YQVMC_NLOHMANN_JSON_ADAPTOR_HPP

#include <nlohmann/json.hpp>
#include "../engine.hpp"
#include "../observer.hpp"

namespace yqvmc {
  void from_json(const nlohmann::json& j, Engine& engine) {
    engine.m_warmup = j.at("warmup").get<std::size_t>();
    engine.m_skip = j.at("skip").get<std::size_t>();
    engine.m_binsize = j.at("binsize").get<std::size_t>();
    engine.m_nbins = j.at("nbins").get<std::size_t>();
  }

  template <class RG>
  RG loadRandomGenerator(const nlohmann::json& j) {
    auto p = j.find("random_seed");
    if (p != j.end())
      return RG(p->get<typename RG::result_type>());
    else
      return RG();
  }

}

#endif
