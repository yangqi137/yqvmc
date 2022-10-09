#ifndef YQVMC_SEQUENTIAL_WALKER_HPP
#define YQVMC_SEQUENTIAL_WALKER_HPP

namespace yqvmc {
  template <typename... UPDATE_LIST>
  class SequentialWalker {
  public:
    typedef std::tuple<UPDATE_LIST&...> UpdateList;
    typedef SequentialWalker<UPDATE_LIST...> SelfType;
  public:
    SequentialWalker(UPDATE_LIST&... updates_)
      : updates(std::tie(updates_...)) {}

    template <typename Conf, typename RG>
    void walk(Conf& conf, RG& rg) const {
      applyUpdate<0>(conf, rg);
    }

  private:
    template <std::size_t I, typename C, typename RG>
    typename std::enable_if<(I==sizeof...(UPDATE_LIST)), void>::type
    applyUpdate(C& c, RG& rg) const { }

    template <std::size_t I, typename C, typename RG>
    typename std::enable_if<(I<sizeof...(UPDATE_LIST)), void>::type
    applyUpdate(C& c, RG& rg) const {
      std::get<I>(updates).update(c, rg);
      applyUpdate<I+1>(c, rg);
    }

  private:
    UpdateList updates;
  };

  template <typename... UL>
  SequentialWalker<UL...> MakeSequentialWalker(UL&... updates) {
    return SequentialWalker<UL...>(updates...);
  }
}

#endif