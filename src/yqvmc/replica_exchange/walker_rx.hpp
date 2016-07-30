#ifndef YQVMC_RX_WALKER_RX_HPP
#define YQVMC_RX_WALKER_RX_HPP

//#include <cassert>

namespace yqvmc {
  template <typename WALKER_VEC, typename SWAPPER_VEC>
  class WalkerRx {
  public:
    typedef WALKER_VEC WalkerVec;
    typedef SWAPPER_VEC SwapperVec;

    WalkerRx(WalkerVec& walkers, SwapperVec& swappers, std::size_t rxsteps)
    : m_walkers(walkers), m_swappers(swappers), m_rxsteps(rxsteps), m_counter(0) {}

    template <typename ConfVec, typename RG>
    void walk(ConfVec& confs, RG& rg) {
      //assert(confs.size() == m_walkers.size());
      if (m_counter != m_rxsteps) {
        auto ci = confs.begin();
        for (auto wi = m_walkers.begin(); wi != m_walkers.end(); wi++, ci++)
          wi->walk(*ci, rg);
        m_counter++;
      }
      else {
        auto ci = confs.begin();
        for (auto si = m_swappers.begin(); si != m_swappers.end(); si++, ci++)
          si->swap(*ci, *std::next(ci), rg);
        m_counter = 0;
      }
    }

  private:
    WalkerVec& m_walkers;
    SwapperVec& m_swappers;
    std::size_t m_rxsteps;
    std::size_t m_counter;
  };

  template <typename W, typename S>
  WalkerRx<W, S> MakeWalkerRx(W& w, S& s, std::size_t rxsteps) {
    return WalkerRx<W, S>(w, s, rxsteps);
  }
}
#endif
