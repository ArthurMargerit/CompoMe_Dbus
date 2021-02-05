#pragma once

#include <string>
// cls
template <typename T> struct dbus_type_cls{ static std::string sig();};

template <typename T> char dbus_type(){return dbus_type_cls<T>::sig()[0];}
template <typename T> const char *dbus_type_as_string(){return dbus_type_cls<T>::sig().c_str();}
