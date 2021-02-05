#include "CompoMe_DBus.hpp"
#include "Types/CompoMe/String.hpp"
#include <dbus/dbus.h>

template <> struct dbus_type_cls<std::string> {
  static std::string sig() { return std::string(DBUS_TYPE_STRING_AS_STRING); }
};

// DBus Message
DBusMessageIter &operator<<(DBusMessageIter &os, const std::string &pt) {
  const char *x = pt.c_str();
  if (false == dbus_message_iter_append_basic(&os, dbus_type<std::string>(), &x)) {
    throw "Not enough memory";
  }

  return os;
}

DBusMessageIter &operator>>(DBusMessageIter &is, std::string &pt) {
  if (dbus_message_iter_get_arg_type(&is) != dbus_type<std::string>()) {
    return is;
  }

  DBusBasicValue value;
  dbus_message_iter_get_basic(&is, &value);
  dbus_message_iter_next(&is);

  pt = std::string(value.str);
  return is;
}


template <> struct dbus_type_cls<CompoMe::String_d> {
  static std::string sig() { return std::string(DBUS_TYPE_STRING_AS_STRING); }
};

// DBus Message
DBusMessageIter &operator<<(DBusMessageIter &os, const CompoMe::String &pt) {
  const char *x = pt.str.c_str();
  if (false == dbus_message_iter_append_basic(&os, dbus_type<CompoMe::String>(), &x)) {
    throw "Not enough memory";
  }

  return os;
}

DBusMessageIter &operator>>(DBusMessageIter &is, CompoMe::String &pt) {
  if (dbus_message_iter_get_arg_type(&is) != dbus_type<CompoMe::String>()) {
    return is;
  }

  DBusBasicValue value;
  dbus_message_iter_get_basic(&is, &value);
  dbus_message_iter_next(&is);

  pt = CompoMe::String(value.str);
  return is;
}


