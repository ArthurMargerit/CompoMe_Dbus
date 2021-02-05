#include "Types/Array.hpp"
#include "CompoMe_DBus.hpp"
#include <dbus/dbus.h>

// DBus Message
template <typename E,unsigned long NB> struct dbus_type_cls<Array<E,NB>> {
  static std::string sig() { return "a" + dbus_type_cls<E>::sig();}
};

template <typename DATA, unsigned long int NB>
DBusMessageIter &operator<<(DBusMessageIter &os, const Array<DATA, NB> &pt) {
  DBusMessageIter sub_os;

  dbus_message_iter_open_container(&os, DBUS_TYPE_ARRAY,
                                   dbus_type_cls<DATA>::sig().c_str(), &sub_os);
  for (unsigned int i = 0; i < NB; ++i) {
    sub_os << pt[i];
  }
  dbus_message_iter_close_container(&os, &sub_os);

  return os;
}

template <typename DATA, unsigned long int NB>
DBusMessageIter &operator>>(DBusMessageIter &is, Array<DATA, NB> &pt) {
  int len = dbus_message_iter_get_element_count(&is);
  if (len != NB) {
    return is;
  }

  DBusMessageIter sub_is;
  dbus_message_iter_recurse(&is, &sub_is);

  for (unsigned long int i = 0; i < NB; ++i) {
    sub_is >> pt[i];
  }

  dbus_message_iter_next(&is);
  return is;
}
