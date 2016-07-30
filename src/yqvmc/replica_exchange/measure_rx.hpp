#ifndef YQVMC_RX_MEASURE_RX_HPP
#define YQVMC_RX_MEASURE_RX_HPP

namespace yqvmc {
  template <typename MEASURE_VEC>
  class MeasureRx {
  public:
    typedef MEASURE_VEC MeasureVec;
    MeasureRx(MeasureVec& measures)
    : m_measures(measures) {}

  public:
    template <typename ConfVec>
    void measure(ConfVec& confs) {
      auto ci = confs.begin();
      for (auto mi = m_measures.begin(); mi != m_measures.end(); mi++, ci++)
        mi->measure(*ci);
    }

  private:
    MeasureVec& m_measures;
  };

  template <typename M>
  MeasureRx<M> MakeMeasureRx(M& m) { return MeasureRx<M>(m); }
}
#endif
