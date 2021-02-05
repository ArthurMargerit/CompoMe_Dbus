#pragma once

#include "Links/Link.hpp"
#include "Links/Link_dbus.hpp"

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

  // Get and set /////////////////////////////////////////////////////////////

  virtual CompoMe::String get_object_name() const;
  virtual void set_object_name(const CompoMe::String object_name);
private:
  // DATA ////////////////////////////////////////////////////////////////////

  CompoMe::String object_name;

  DBus::Connection::pointer conn;
  void introspection(DBus::CallMessage::pointer msg,
                     DBus::ReturnMessage::pointer reply);
};
