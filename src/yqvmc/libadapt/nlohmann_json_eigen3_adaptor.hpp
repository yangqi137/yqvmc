#ifndef YQVMC_NLOHMANN_JSON_EIGEN3_ADAPTOR_HPP
#define YQVMC_NLOHMANN_JSON_EIGEN3_ADAPTOR_HPP

#include <Eigen/Dense>

namespace nlohmann {
    //template <typename Derived>
    //struct adl_serializer<EigenBase<Derived>> {
    //};
    template <>
    struct adl_serializer<Eigen::ArrayXd> {
      static void to_json(json& j, const Eigen::ArrayXd& vec) {
        for (unsigned i = 0; i < vec.size(); i++) {
          j[i] = vec[i];
        }
      }

      static void from_json(const json& j, Eigen::ArrayXd& vec) {
        vec.resize(j.size());
        for (unsigned i = 0; i < j.size(); i++) {
          vec[i] = j[i];
        }
      }

      static void to_json(json& j, const Eigen::ArrayXXd& vec) {
      }

      static void from_json(const json& j, Eigen::ArrayXXd& vec) {
      }

    };
}

#endif
