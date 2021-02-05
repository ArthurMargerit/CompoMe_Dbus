#include "Types/Set.hpp"

#include <dbus/dbus.h>
// DBus Message

template <typename T>
DBusMessageIter &operator<<(DBusMessageIter &os, const Set<T> &pt) {
  // TODO
  return os;
}

template <typename T>
DBusMessageIter &operator>>(DBusMessageIter &is, Set<T> &pt) {
  // TODO
  return is;
}
