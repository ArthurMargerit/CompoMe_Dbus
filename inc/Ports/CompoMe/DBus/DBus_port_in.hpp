#pragma once

#include "Ports/CompoMe/Core/CI_map_in.hpp"

// TYPES

// d.D_NAME

#include "Types/CompoMe/String.hpp"

// STRUCT

namespace CompoMe {

namespace DBus {

class DBus_port_in : public CompoMe::Core::CI_map_in {
public:
  //! Default constructor
  DBus_port_in();

  //! Destructor
  virtual ~DBus_port_in() noexcept;

  // FUNCTION_IN //////////////////////////////////////////////////////////////
  virtual bool connect_interface(CompoMe::String component_key,
                                 CompoMe::String interface_key,
                                 CompoMe::Interface &p_i);

  virtual CompoMe::Interface &get_interface(CompoMe::String component_key,
                                            CompoMe::String interface_key);

  std::map<std::tuple<CompoMe::String, CompoMe::String>, CompoMe::Interface *>
  get_interfaces_list();

  virtual bool is_connected_interface(CompoMe::Interface &p_i);
  virtual bool is_connected_interface(CompoMe::String component_key,
                                      CompoMe::String interface_key);

  virtual bool disconnect_interface(CompoMe::String component_key,
                                    CompoMe::String interface_key);
  virtual bool disconnect_interface(CompoMe::Interface &p_i);

  // FUNCTION /////////////////////////////////////////////////////////////////

  // GET/SET //////////////////////////////////////////////////////////////////

private:
  // YOU PRIVATE DATA//////////////////////////////////////////////////////////

  //---------------------------------------------------------------------------
};

} // namespace DBus

} // namespace CompoMe
