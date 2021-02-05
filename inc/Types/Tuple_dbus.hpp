#include "Types/Tuple.hpp"

#include <dbus/dbus.h>
// DBus Message
namespace {
template <typename CLS, typename... Args> struct T {
  static std::string t_sig() {
    return dbus_type_cls<CLS>::sig() + T<Args...>::t_sig();
  };
};
template <typename CLS> struct T<CLS> {
  static std::string t_sig() { return dbus_type_cls<CLS>::sig(); };
};

// printer of tuple ////////////////////////////////////////////////////////
template <typename T> struct tuple_dbus_print {
public:
  template <unsigned int n, unsigned int l> struct ts {
  public:
    static void st(DBusMessageIter &os, const T &p) {
      os << std::get<n>(p);
      ts<n + 1, l>::st(os, p);
    }
  };
  template <unsigned int n> struct ts<n, n> {
  public:
    static void st(DBusMessageIter &os, const T &p) { os << std::get<n>(p); }
  };
  static void print(DBusMessageIter &os, const T &p) {
    ts<0, std::tuple_size<T>::value - 1>::st(os, p);
  }
};
template <> struct tuple_dbus_print<std::tuple<>> {
  static void print(DBusMessageIter &os, const std::tuple<> &p) {}
};

// READER of tuple ////////////////////////////////////////////////////////
template <typename T> struct tuple_dbus_reader {
public:
  template <unsigned int n, unsigned int l> struct ts {
  public:
    static void st(DBusMessageIter &is, T &p) {
      is >> std::get<n>(p);
      ts<n + 1, l>::st(is, p);
    }
  };
  template <unsigned int n> struct ts<n, n> {
  public:
    static void st(DBusMessageIter &is, T &p) { is >> std::get<n>(p); }
  };
  static void read(DBusMessageIter &is, T &p) {
    ts<0, std::tuple_size<T>::value - 1>::st(is, p);
  }
};

template <> struct tuple_dbus_reader<std::tuple<>> {
  static void read(DBusMessageIter &is, std::tuple<> &p) {}
};
} // Namespace

template <typename... Args> struct dbus_type_cls<Tuple<Args...>> {
  static std::string sig() { return "(" + T<Args...>::t_sig() + ")"; }
};

template <typename... Args>
DBusMessageIter &operator<<(DBusMessageIter &os, const Tuple<Args...> &pt) {
  DBusMessageIter sub_os;
  dbus_message_iter_open_container(&os, DBUS_TYPE_STRUCT, NULL, &sub_os);
  tuple_dbus_print<Tuple<Args...>>::print(sub_os, pt);
  dbus_message_iter_close_container(&os, &sub_os);
  return os;
}

template <typename... Args>
DBusMessageIter &operator>>(DBusMessageIter &is, Tuple<Args...> &pt) {
  DBusMessageIter sub_is;
  dbus_message_iter_recurse(&is, &sub_is);
  tuple_dbus_reader<Tuple<Args...>>::read(sub_is, pt);
  dbus_message_iter_next(&is);
  return is;
}
