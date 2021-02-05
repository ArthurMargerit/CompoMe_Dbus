#pragma once

#include "Links/Link.hpp"
#include "Links/Link_dbus.hpp"

namespace CompoMe {
class Function_stream;
class Return_stream;
class Interface;
} // namespace CompoMe

#include "Data/CompoMe_Dbus.hpp"

class Dbus_client : public CompoMe::Link, public CompoMe::Link_dbus_out {
public:
  Dbus_client();
  virtual ~Dbus_client();

  void step() override;
  void connect() override;
  void disconnect() override;

  // Get and set /////////////////////////////////////////////////////////////

  virtual CompoMe::String get_object_name() const;
  virtual void set_object_name(const CompoMe::String object_name);
  virtual i32 get_timeout() const;
  virtual void set_timeout(const i32 timeout);
  void connect(CompoMe::Require_helper &p_i) override;
  void disconnect(CompoMe::Require_helper &p_i) override;

private:
  // DATA ////////////////////////////////////////////////////////////////////

  CompoMe::String object_name;

  i32 timeout;
  std::map<CompoMe::Require_helper *, CompoMe::Function_dbus_send *>
      function_dbus;
  DBus::Connection::pointer co;
  DBus::Dispatcher::pointer di;
};
