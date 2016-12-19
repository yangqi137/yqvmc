#ifndef YQVMC_EXTERNAL_LIBRARY_ADAPTOR_EIGEN3_HPP
#define YQVMC_EXTERNAL_LIBRARY_ADAPTOR_EIGEN3_HPP

#include <Eigen/Core>
#include "../impl_/mae_traits.hpp"

namespace yqvmc {
  namespace impl_ {
    template <typename S_, int R_, int C_, int O_, int MR_, int MC_>
    struct MeanAndErrorTraits<Eigen::Array<S_, R_, C_, O_, MR_, MC_>, void> {
    public:
      typedef Eigen::Array<S_, R_, C_, O_, MR_, MC_> input_type;
      typedef typename input_type::Scalar Scalar;
      typedef typename std::conditional<input_type::ColsAtCompileTime == 1,
        Eigen::Array<Scalar, Eigen::Dynamic, 1>,
        Eigen::Array<Scalar, Eigen::Dynamic, Eigen::Dynamic> >::type sum_type;
      typedef sum_type result_type;

      static void set_zero(sum_type& x) { x.setZero(); }
      static void add_to(sum_type& x, const input_type& dx) {
        if (x.size() == 0)
          x = dx;
        else
          x += dx;
      }
      static input_type square(const input_type& x) { return x*x; }
      static result_type mean(const sum_type& x, std::size_t n) {
        return x/n;
      }
      static result_type standard_error(const result_type& x2mean,
        const result_type& xmean, std::size_t n) {
        return ((x2mean - xmean*xmean) / n).sqrt();
      }
    };
  }
}

#endif
