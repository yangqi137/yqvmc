#ifndef YQVMC_IMPL_MEAN_AND_ERROR_TRAITS_HPP
#define YQVMC_IMPL_MEAN_AND_ERROR_TRAITS_HPP

#include <cmath>
#include <valarray>

namespace yqvmc {
  namespace impl_ {
    template <typename T, typename Enable = void>
    struct MeanAndErrorTraits; // General implementation not provided.

    template <typename T>
    struct MeanAndErrorTraits<T,
    typename std::enable_if<std::is_arithmetic<T>::value>::type> {
    public:
      typedef T input_type;
      typedef T sum_type;
      typedef typename std::conditional<std::is_integral<input_type>::value,
        double, input_type>::type result_type;

      static void set_zero(sum_type& x) { x = 0; }
      static void add_to(sum_type& x, input_type dx) { x += dx; }
      static input_type square(input_type x) { return x*x; }
      static result_type mean(sum_type x, std::size_t n) {
        return ((result_type) x) / ((result_type) n);
      }
      static result_type standard_error(result_type x2mean,
        result_type xmean, std::size_t n) {
        return std::sqrt((x2mean - xmean*xmean) / n);
      }
    };

    template <typename T>
    struct MeanAndErrorTraits<std::valarray<T> > {
      typedef T scalar_type;
      typedef std::valarray<scalar_type> input_type;
      typedef std::valarray<scalar_type> sum_type;
      typedef std::valarray<scalar_type> result_type;

      static void set_zero(sum_type& x) { 
        if (x.size() != 0) x=0.;
      }
      static void add_to(sum_type& x, const input_type& dx) {
        if (x.size() == 0) x = dx;
        else x += dx;
      }
      static input_type square(const input_type& x) { return x*x; }
      static result_type mean(const sum_type& x, std::size_t n) {
        return x / n;
      }
      static result_type standard_error(const result_type& x2mean,
        const result_type& xmean, std::size_t n) {
        return std::sqrt((x2mean - xmean*xmean) / n);
      }
    };

  }
}
#endif
