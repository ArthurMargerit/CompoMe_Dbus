#include "Types/float.hpp"

#include "CompoMe_DBus.hpp"
#include <dbus/dbus.h>

template <> struct dbus_type_cls<float> {
  static std::string sig() { return std::string(DBUS_TYPE_DOUBLE_AS_STRING); }
};

// DBus Message
DBusMessageIter &operator<<(DBusMessageIter &os, const float &pt) {
  double r_pt = (double)pt;
  if (false == dbus_message_iter_append_basic(&os, dbus_type<float>(), &r_pt)) {
    throw "Not enough memory";
  }

  return os;
}

DBusMessageIter &operator>>(DBusMessageIter &is, float &pt) {

  if (dbus_message_iter_get_arg_type(&is) != dbus_type<float>()) {
    throw "wrong type";
    return is;
  }

  double r_pt;
  dbus_message_iter_get_basic(&is, &r_pt);
  dbus_message_iter_next(&is);
  pt = (float)r_pt;

  return is;
}
