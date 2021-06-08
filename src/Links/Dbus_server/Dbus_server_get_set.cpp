#include "Links/Dbus_server/Dbus_server.hpp"

//============================= object_name =============================
CompoMe::String Dbus_server::get_object_name() const {
  return this->object_name;
}

void Dbus_server::set_object_name(const CompoMe::String p_object_name) {
  this->object_name = p_object_name;
}

CompoMe::String &Dbus_server::a_object_name() { return this->object_name; }
//--------------------------------------------------------------------------
