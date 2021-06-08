#pragma once

#include "Data/CompoMe_Dbus.hpp"

#include "Links/Link.hpp"

// TYPES

#include "Types/CompoMe/String.hpp"

#include "Types/i32.hpp"
// STRUCT

// PORT

#include "Ports/CompoMe/DBus/DBus_port_out.hpp"

class Dbus_client : public CompoMe::Link {
public:
  Dbus_client();
  virtual ~Dbus_client();

  void step() override;
  void main_connect() override;
  void main_disconnect() override;

  // Get and set /////////////////////////////////////////////////////////////

  CompoMe::String get_object_name() const;
  void set_object_name(const CompoMe::String object_name);
  CompoMe::String &a_object_name();
  i32 get_timeout() const;
  void set_timeout(const i32 timeout);
  i32 &a_timeout();

  // Get Port /////////////////////////////////////////////////////////////

  CompoMe::DBus::DBus_port_out &get_bus();

public:
  // Function
  // ///////////////////////////////////////////////////////////////////

private:
  // DATA ////////////////////////////////////////////////////////////////////
  CompoMe::String object_name;
  i32 timeout;

  // PORT ////////////////////////////////////////////////////////////////////
  CompoMe::DBus::DBus_port_out bus;

  // other
  DBusConnection *conn;
  using T_FS_FAKE =
      std::tuple<CompoMe::Function_dbus_send *, CompoMe::Fake_dbus *>;
  std::map<CompoMe::Require_helper *, T_FS_FAKE> function_dbus;
};
