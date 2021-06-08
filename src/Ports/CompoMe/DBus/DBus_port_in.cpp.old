#include "Ports/CompoMe/DBus/DBus_port_in.hpp"
#include "CompoMe/Log.hpp"

namespace CompoMe {

namespace DBus {

//! Default constructor
DBus_port_in::DBus_port_in() {}

//! Destructor
DBus_port_in::~DBus_port_in() {}

// Function IN ////////////////////////////////////////////////////////////////
bool DBus_port_in::connect_interface(CompoMe::String component_key,
                                     CompoMe::String interface_key,
                                     CompoMe::Interface &p_i) {

  if (p_i.get_caller_dbus() == nullptr) {
    C_WARNING("This interface is not a interface that provide a DBusCaller");
    return false;
  }

  return CompoMe::Core::CI_map_in::connect_interface(component_key,
                                                     interface_key, p_i);
}

bool DBus_port_in::is_connected_interface(CompoMe::String component_key,
                                          CompoMe::String interface_key) {
  return CompoMe::Core::CI_map_in::is_connected_interface(component_key,
                                                          interface_key);
}

bool DBus_port_in::is_connected_interface(CompoMe::Interface &p_i) {
  return CompoMe::Core::CI_map_in::is_connected_interface(p_i);
}

bool DBus_port_in::disconnect_interface(CompoMe::String component_key,
                                        CompoMe::String interface_key) {
  return CompoMe::Core::CI_map_in::disconnect_interface(component_key,
                                                        interface_key);
}

bool DBus_port_in::disconnect_interface(CompoMe::Interface &p_i) {
  return CompoMe::Core::CI_map_in::disconnect_interface(p_i);
}

CompoMe::Interface &DBus_port_in::get_interface(CompoMe::String component_key,
                                                CompoMe::String interface_key) {
  return CompoMe::Core::CI_map_in::get_interface(component_key, interface_key);
}

std::map<std::tuple<CompoMe::String, CompoMe::String>, CompoMe::Interface *>
DBus_port_in::get_interfaces_list() {
  return CompoMe::Core::CI_map_in::get_interfaces_list();
}

} // namespace DBus

} // namespace CompoMe
