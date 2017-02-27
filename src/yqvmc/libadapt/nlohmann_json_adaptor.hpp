#ifndef YQVMC_NLOHMANN_JSON_ADAPTOR_HPP
#define YQVMC_NLOHMANN_JSON_ADAPTOR_HPP

#include <json.hpp>
#include "../engine.hpp"
#include "../observer.hpp"

namespace yqvmc {
  void from_json(const nlohmann::json& j, Engine& engine) {
    engine.m_warmup = j["warmup"].get<std::size_t>();
    engine.m_skip = j["skip"].get<std::size_t>();
    engine.m_binsize = j["binsize"].get<std::size_t>();
    engine.m_nbins = j["nbins"].get<std::size_t>();
  }

  template <class M, class A>
  void to_json(nlohmann::json& j, const PlainObserver<M, A>& observer) {
    j["mean"] = observer.mean();
    j["error"] = observer.error();
  }
}

#endif
