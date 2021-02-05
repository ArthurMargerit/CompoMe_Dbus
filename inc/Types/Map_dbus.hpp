#include "CompoMe_DBus.hpp"
#include "Types/Map.hpp"
#include <dbus/dbus.h>

// DBus Message

template <typename K, typename V> struct dbus_type_cls<Map<K, V>> {
  static std::string sig() {
    return "a{" + dbus_type_cls<K>::sig() + dbus_type_cls<V>::sig() + "}";
  }
};

template <typename K, typename V>
DBusMessageIter &operator<<(DBusMessageIter &os, const Map<K, V> &pt) {
  DBusMessageIter sub_os, sub_sub_os;
  std::string sig =
      "{" + dbus_type_cls<K>::sig() + dbus_type_cls<V>::sig() + "}";
  dbus_message_iter_open_container(&os, DBUS_TYPE_ARRAY, sig.c_str(), &sub_os);
  for (auto &a : pt) {
    dbus_message_iter_open_container(&sub_os, DBUS_TYPE_DICT_ENTRY, NULL,
                                     &sub_sub_os);
    sub_sub_os << a.first;
    sub_sub_os << a.second;
    dbus_message_iter_close_container(&sub_os, &sub_sub_os);
  }
  dbus_message_iter_close_container(&os, &sub_os);
  return os;
}

template <typename K, typename V>
DBusMessageIter &operator>>(DBusMessageIter &is, Map<K, V> &pt) {

  int len = dbus_message_iter_get_element_count(&is);
  DBusMessageIter sub_is, sub_sub_is;
  dbus_message_iter_recurse(&is, &sub_is);
  for (int i = 0; i < len; ++i) {
    dbus_message_iter_recurse(&sub_is, &sub_sub_is);
    K k1;
    V v1;

    sub_sub_is >> k1;
    sub_sub_is >> v1;

    pt[k1] = v1;
    dbus_message_iter_next(&sub_is);
  }

  dbus_message_iter_next(&is);
  return is;
}
