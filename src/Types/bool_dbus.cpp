#include "Types/bool.hpp"

#include "CompoMe_DBus.hpp"
#include <dbus/dbus.h>

// DBus Message
template <> struct dbus_type_cls<bool> {
  static std::string sig() { return std::string(DBUS_TYPE_BOOLEAN_AS_STRING); }
};


DBusMessageIter &operator<<(DBusMessageIter &os, const bool &pt) {
  // dbus need conversion to their own type
  dbus_bool_t r_pt = pt;

  if (false == dbus_message_iter_append_basic(&os, dbus_type<bool>(), &r_pt)) {
    throw "Not enough memory";
  }

  return os;
}

DBusMessageIter &operator>>(DBusMessageIter &is, bool &pt) {

  if (dbus_message_iter_get_arg_type(&is) != dbus_type<bool>()) {
    return is;
  }

  dbus_bool_t r_pt = false;
  dbus_message_iter_get_basic(&is, &r_pt);
  dbus_message_iter_next(&is);
  pt = (bool) r_pt;

  return is;
}
