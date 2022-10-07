#ifndef YQVMC_UPDATES_WOLFF_HPP
#define YQVMC_UPDATES_WOLFF_HPP

#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include <cassert>
#include <iostream>

namespace yqvmc { namespace ci {
  template <typename MODEL>
  class WolffUpdate {
  public:
    typedef MODEL Model;
    typedef typename Model::size_type size_type;

  public:
    WolffUpdate(const Model& model)
      : m_model(model),
	      m_visited(model.lattice_size()),
	      m_vdist(0, model.lattice_size()-1),
	      m_dist01(0., 1.) {
      m_cluster.reserve(model.lattice_size());
    }

    template <typename Conf, typename RG>
    void walk(Conf& conf, RG& rg) {
      std::fill(m_visited.begin(), m_visited.end(), false);
      assert(m_cluster.empty());
      auto v0 = m_vdist(rg);
      m_cluster.push_back(v0);
      m_visited[v0] = true;
      conf[v0] = !conf[v0];
      do {
        auto vi = m_cluster.back(); m_cluster.pop_back();
        auto edges = m_model.edges_of_vertex(vi);
        for (auto edge : edges) {
          auto vj = std::get<0>(edge);
          auto jij = std::get<1>(edge);
          double sisj = (conf[vi] == conf[vj]) ? +1 : -1;
          if (m_visited[vj] == false &&
            m_dist01(rg) > std::exp(2*jij*sisj) ) {
              m_cluster.push_back(vj);
              m_visited[vj] = true;
              conf[vj] = !conf[vj];
            }
          }
      } while (!m_cluster.empty());
    }

  private:
    const Model& m_model;
    std::vector<bool> m_visited;
    std::vector<size_type> m_cluster;
    std::uniform_int_distribution<size_type> m_vdist;
    std::uniform_real_distribution<> m_dist01;
  };

  template <class M>
  WolffUpdate<M> MakeWolffUpdate(const M& m) {
    return WolffUpdate<M>(m);
  }
} }

#endif
