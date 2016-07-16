#ifndef YQVMC_UTILITIES_PROPERTY_TREE_PUT_VECTOR_HPP
#define YQVMC_UTILITIES_PROPERTY_TREE_PUT_VECTOR_HPP

#include <boost/property_tree/ptree.hpp>

namespace yqvmc { namespace utils {
    template <typename V>
    boost::property_tree::ptree PTreeOfVector(const V& vector) {
      namespace pt = boost::property_tree;
      pt::ptree node;
      for (auto t : vector) {
	pt::ptree ntemp;
	ntemp.put_value(t);
	node.push_back(std::make_pair("", ntemp));
      }

      return node;
    }
  }
}

#endif
