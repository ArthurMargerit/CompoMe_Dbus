#include "Ports/CompoMe/DBus/DBus_port_out.hpp"

namespace CompoMe {

namespace DBus {

//! Default constructor
DBus_port_out::DBus_port_out() {}

//! Destructor
DBus_port_out::~DBus_port_out() {}

// Function OUT ////////////////////////////////////////////////////////////////
bool DBus_port_out::connect_require(CompoMe::String dest_key,
                                    CompoMe::String component_key,
                                    CompoMe::String interface_key,
                                    CompoMe::Require_helper &p_r) {
  return CompoMe::Core::DCI_map_out::connect_require(dest_key, component_key,
                                                     interface_key, p_r);
}

bool DBus_port_out::is_connected_require(CompoMe::String dest_key,
                                         CompoMe::String component_key,
                                         CompoMe::String interface_key) {
  return CompoMe::Core::DCI_map_out::is_connected_require(
      dest_key, component_key, interface_key);
}

bool DBus_port_out::is_connected_require(CompoMe::Require_helper &p_i) {
  return CompoMe::Core::DCI_map_out::is_connected_require(p_i);
}

bool DBus_port_out::disconnect_require(CompoMe::String dest_key,
                                       CompoMe::String component_key,
                                       CompoMe::String interface_key) {
  return CompoMe::Core::DCI_map_out::disconnect_require(dest_key, component_key,
                                                        interface_key);
}

bool DBus_port_out::disconnect_require(CompoMe::Require_helper &p_r) {
  return CompoMe::Core::DCI_map_out::disconnect_require(p_r);
}

CompoMe::Require_helper &
DBus_port_out::get_require(CompoMe::String dest_key,
                           CompoMe::String component_key,
                           CompoMe::String interface_key) {
  return CompoMe::Core::DCI_map_out::get_require(dest_key, component_key,
                                                 interface_key);
}

std::map<std::tuple<CompoMe::String, CompoMe::String, CompoMe::String>,
         CompoMe::Require_helper *>
DBus_port_out::get_require_list() {
  return CompoMe::Core::DCI_map_out::get_require_list();
}

} // namespace DBus

} // namespace CompoMe
