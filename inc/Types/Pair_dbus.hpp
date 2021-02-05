#include "CompoMe_DBus.hpp"
#include "Types/Pair.hpp"
#include <dbus/dbus.h>

// DBus Message
template <typename F, typename S> struct dbus_type_cls<Pair<F, S>> {
  static std::string sig() {
    return "(" + dbus_type_cls<F>::sig() + dbus_type_cls<S>::sig() + ")";
  }
};

template <typename F, typename S>
DBusMessageIter &operator<<(DBusMessageIter &os, const Pair<F, S> &pt) {
  DBusMessageIter sub_os;
  dbus_message_iter_open_container(&os, DBUS_TYPE_STRUCT, NULL, &sub_os);
  sub_os << pt.first;
  sub_os << pt.second;
  dbus_message_iter_close_container(&os, &sub_os);

  return os;
}

template <typename F, typename S>
DBusMessageIter &operator>>(DBusMessageIter &is, Pair<F, S> &pt) {
  DBusMessageIter sub_is;
  dbus_message_iter_recurse(&is, &sub_is);
  sub_is >> pt.first;
  sub_is >> pt.second;
  dbus_message_iter_next(&is);
  return is;
}
