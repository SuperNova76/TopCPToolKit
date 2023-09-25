#ifndef TOPSPANET_SPANET_ENUMS_H
#define TOPSPANET_SPANET_ENUMS_H

#include <map>
#include <sstream>

namespace top {
  namespace SpaNetEnums {

    enum Topology {
      TtbarLjets,
      TtbarLjetsNu
    };

    static const std::map<std::string, Topology> strToTopology {
      {"TtbarLjets", TtbarLjets },
      {"TtbarLjetsNu", TtbarLjetsNu}
    };

    template <class T> std::string printEnumOptions(const std::map<std::string, T> &availOpts) {
      std::stringstream sstream;
      for (const auto& elem : availOpts) {
        sstream << elem.first << " ";
      }
      return sstream.str();
    }

  } // namespace SpaNetEnums
} // namespace top

#endif
