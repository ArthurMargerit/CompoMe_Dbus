#pragma once

#include "Links/Link.hpp"
#include "Links/Link_dbus.hpp"

// TYPES

#include "Types/CompoMe/String.hpp"
// STRUCT
class Function_dbus_recv_i;
class Return_dbus_send_i;

namespace CompoMe {
class Function_stream;
class Return_stream;
class Interface;
} // namespace CompoMe

#include "Data/CompoMe_Dbus.hpp"

class Dbus_server : public CompoMe::Link, public CompoMe::Link_dbus_in {
public:
  Dbus_server();
  virtual ~Dbus_server();

  void step() override;
  void connect() override;
  void disconnect() override;

  void introspection(Function_dbus_recv_i &, Return_dbus_send_i &);
  // Get and set /////////////////////////////////////////////////////////////

  virtual CompoMe::String get_object_name() const;
  virtual void set_object_name(const CompoMe::String object_name);
  CompoMe::String &a_object_name();

public:
  // Function
  // ///////////////////////////////////////////////////////////////////
private:
  DBusConnection *conn;
  // DATA ////////////////////////////////////////////////////////////////////

  CompoMe::String object_name;
};
