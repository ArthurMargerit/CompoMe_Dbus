#include "Links/Dbus_client/Dbus_client.hpp"

//============================= object_name =============================
CompoMe::String Dbus_client::get_object_name() const {
  return this->object_name;
}

void Dbus_client::set_object_name(const CompoMe::String p_object_name) {
  this->object_name = p_object_name;
}

CompoMe::String &Dbus_client::a_object_name() { return this->object_name; }
//--------------------------------------------------------------------------
//============================= timeout =============================
i32 Dbus_client::get_timeout() const { return this->timeout; }

void Dbus_client::set_timeout(const i32 p_timeout) {
  this->timeout = p_timeout;
}

i32 &Dbus_client::a_timeout() { return this->timeout; }
//--------------------------------------------------------------------------
