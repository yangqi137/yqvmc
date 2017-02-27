#ifndef GUPDATE_LOCAL_UPDATE_HPP
#define GUPDATE_LOCAL_UPDATE_HPP

#include <random>
#include <cmath>

namespace yqvmc { namespace ci {

template <typename Model>
class LocalUpdate {
public:
  typedef typename Model::size_type size_type;
  LocalUpdate(const Model& model)
  : m_model(model), m_vdist(0, model.latticeSize()-1),
    m_dist01(0., 1.) {}

  template <typename Conf, typename RG>
  void walk(Conf& conf, RG& rg) {
    for (std::size_t i = 0; i < conf.size(); i++) { // Repeat N trails in one step
      auto v0 = m_vdist(rg);
      auto de = m_model.localEnergyDiff(conf, v0);

      if (de < 0 || m_dist01(rg) < std::exp(-de)) //accepting
        conf[v0] = !conf[v0];
    }
  }

private:
  const Model& m_model;
  std::uniform_int_distribution<size_type> m_vdist;
  std::uniform_real_distribution<> m_dist01;
};

template <typename M>
LocalUpdate<M> MakeLocalUpdate(const M& m) {
  return LocalUpdate<M>(m);
}
}}

#endif
