#pragma once

#include "Data/CompoMe_Dbus.hpp"
#include "Links/Link.hpp"

// other
#include "Interfaces/Function_dbus_recv.hpp"
#include "Interfaces/Return_dbus_send.hpp"

// TYPES

#include "Types/CompoMe/String.hpp"
// STRUCT

// PORT

#include "Ports/CompoMe/DBus/DBus_port_in.hpp"

class Dbus_server : public CompoMe::Link {
public:
  Dbus_server();
  virtual ~Dbus_server();

  void step() override;
  void main_connect() override;
  void main_disconnect() override;

  void introspection(CompoMe::Function_dbus_recv &,
                     CompoMe::Return_dbus_send &);
  // Get and set /////////////////////////////////////////////////////////////

  CompoMe::String get_object_name() const;
  void set_object_name(const CompoMe::String object_name);
  CompoMe::String &a_object_name();

  // Get Port /////////////////////////////////////////////////////////////

  CompoMe::DBus::DBus_port_in &get_bus();

public:
  // Function
  // ///////////////////////////////////////////////////////////////////

private:
  DBusConnection *conn;
  // DATA ////////////////////////////////////////////////////////////////////
  CompoMe::String object_name;

  // PORT ////////////////////////////////////////////////////////////////////
  CompoMe::DBus::DBus_port_in bus;
};
