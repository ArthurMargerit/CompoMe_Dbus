#include "Types/Vec.hpp"
#include "CompoMe_DBus.hpp"
#include <dbus/dbus.h>

// DBus Message
template <typename E> struct dbus_type_cls<Vec<E>> {
  static std::string sig() { return "a" + dbus_type_cls<E>::sig();}
};

template <typename T>
DBusMessageIter &operator<<(DBusMessageIter &os, const Vec<T> &pt) {
  DBusMessageIter sub_os;

  dbus_message_iter_open_container(&os, DBUS_TYPE_ARRAY,
                                   dbus_type_cls<T>::sig().c_str(), &sub_os);
  for (unsigned int i = 0; i < pt.size(); ++i) {
    sub_os << pt[i];
  }
  dbus_message_iter_close_container(&os, &sub_os);

  return os;
}

template <typename T>
DBusMessageIter &operator>>(DBusMessageIter &is, Vec<T> &pt) {
  int len = dbus_message_iter_get_element_count(&is);

  DBusMessageIter sub_is;
  dbus_message_iter_recurse(&is, &sub_is);

  for (int i = 0; i < len; ++i) {
    T a;
    sub_is >> a;
    pt.push_back(a);
  }

  dbus_message_iter_next(&is);
  return is;
}
