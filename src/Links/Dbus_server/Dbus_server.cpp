
#include "Links/Dbus_server/Dbus_server.hpp"
#include "CompoMe/Log.hpp"
#include "Interfaces/Function_dbus_recv.hpp"
#include "Interfaces/Interface.hpp"
#include "Interfaces/Return_dbus_send.hpp"

class Function_dbus_recv_i : public CompoMe::Function_dbus_recv {

  CompoMe::Serialization_context_import ctx;
  DBusMessage *msg;
  DBusMessageIter _it;
  bool r;

public:
  Function_dbus_recv_i(DBusMessage *p_msg) : msg(p_msg), r(true) {}
  void pull() override {}
  void end() override {}

  std::string get_function() override {
    return dbus_message_get_member(this->msg);
  }

  std::string get_path() { return dbus_message_get_path(this->msg); }
  std::string get_interface() { return dbus_message_get_interface(this->msg); }
  std::string get_signature() { return dbus_message_get_signature(this->msg); }

  DBusMessageIter &get_si() override {
    if (this->r == true) {
      dbus_message_iter_init(this->msg, &this->_it);
      this->r = false;
    }

    return _it;
  }

  CompoMe::Serialization_context_import &get_ctx() override {
    return this->ctx;
  }
};

class Return_dbus_send_i : public CompoMe::Return_dbus_send {
  CompoMe::Serialization_context_export ctx;
  DBusMessage *ret;
  DBusMessageIter _a_it;
  bool r;

public:
  Return_dbus_send_i(DBusMessage *p_ret) : ret(p_ret), r(true) {}

  void start() override {}
  void send() override {}

  DBusMessageIter &get_so() override {
    if (this->r) {
      dbus_message_iter_init_append(this->ret, &this->_a_it);
      this->r = false;
    }
    return _a_it;
  }

  CompoMe::Serialization_context_export &get_ctx() override { return ctx; }
  std::string get_signature() { return dbus_message_get_signature(this->ret); }
};

Dbus_server::Dbus_server() : CompoMe::Link() {}

Dbus_server::~Dbus_server() {}
#include <iostream>
void Dbus_server::step() {
  Link::step();
  dbus_connection_read_write(this->conn, 0);

  while (true) {
    DBusMessage *msg = dbus_connection_pop_message(this->conn);
    if (NULL == msg) {
      break;
    }
    DBusMessage *reply = dbus_message_new_method_return(msg);

    Function_dbus_recv_i msgr(msg);
    Return_dbus_send_i replyr(reply);

    if (msgr.get_interface() == "org.freedesktop.DBus.Introspectable") {
      C_INFO_TAG("dbus,server", "Instrospection of ", msgr.get_path());
      this->introspection(msgr, replyr);
    } else if (!this->connected(msgr.get_path(), msgr.get_interface())) {
      C_ERROR_TAG("dbus,server", "Not connected in the link... ",
                  msgr.get_path(), ":", msgr.get_interface(), ".",
                  msgr.get_member());

    } else {
      C_INFO_TAG("dbus,server", "call :", msgr.get_interface(), ".",
                 msgr.get_function(), "(", msgr.get_signature(), ")");
      this->get_caller(msgr.get_path(), msgr.get_interface())
          .call(msgr, replyr);

      C_INFO_TAG("dbus,server", "answer :", replyr.get_signature());
    }

    dbus_connection_send(this->conn, reply, NULL);
    dbus_connection_flush(this->conn);
    dbus_message_unref(msg);
    dbus_message_unref(reply);
  }
}

void Dbus_server::connect() {
  Link::connect();
  DBusError err;

  dbus_error_init(&err);
  this->conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

  if (dbus_error_is_set(&err)) {
    C_ERROR("Connection Error", err.message);
    dbus_error_free(&err);
    return;
  }

  if (NULL == this->conn) {
    C_ERROR("Connection Null");
    return;
  }

  dbus_bus_request_name(this->conn, this->get_object_name().str.c_str(),
                        DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
  if (dbus_error_is_set(&err)) {
    C_ERROR("Name Error", err.message);
    dbus_error_free(&err);
    return;
  }

  C_INFO("Dbus server Connecected");
}

void Dbus_server::disconnect() {
  Link::disconnect();
  dbus_connection_unref(this->conn);
  C_INFO("dbus connection is cut");
}

// Get and set /////////////////////////////////////////////////////////////

CompoMe::String Dbus_server::get_object_name() const {
  return this->object_name;
}

void Dbus_server::set_object_name(const CompoMe::String p_object_name) {
  this->object_name = p_object_name;
}

CompoMe::String &Dbus_server::a_object_name() { return this->object_name; }

void Dbus_server::introspection(Function_dbus_recv_i &msg,
                                Return_dbus_send_i &reply) {

  std::stringstream ss;
  ss << "<node>";
  ss << "<interface name=\"org.freedesktop.DBus.Introspectable\"><method "
        "name=\"Introspect\"><arg type=\"s\" name=\"xml_data\" "
        "direction=\"out\"/></method></interface>";
  for (auto &kv2 : this->a_c[msg.get_path()]) {
    ss << "\t<interface name=\"" << kv2.first << "\">";
    kv2.second->introspection(ss);
    ss << "</interface>\n";
  }

  for (auto &kv : this->a_c) {
    if (kv.first == msg.get_path()) {
      continue;
    }

    int p = kv.first.find(msg.get_path());
    if (p != std::string::npos) {
      ss << "<node name=\"" << kv.first.substr(msg.get_path().length())
         << "\"/>";
    }
  }
  ss << "</node>";
  std::string ts = ss.str();
  reply.get_so() << CompoMe::String(ts);
}
