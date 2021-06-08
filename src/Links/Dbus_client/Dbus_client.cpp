#include "Links/Dbus_client/Dbus_client.hpp"
#include "CompoMe/Log.hpp"
#include "Interfaces/Fake_dbus.hpp"
#include "Interfaces/Function_dbus_send.hpp"
#include "Interfaces/Interface.hpp"
#include "Interfaces/Return_dbus_recv.hpp"

class Return_dbus_recv_i : public CompoMe::Return_dbus_recv {
  DBusMessageIter si;
  bool r;

public:
  DBusPendingCall *p;
  DBusMessage *msg;

  void pull() override {
    dbus_pending_call_block(this->p);
    this->msg = dbus_pending_call_steal_reply(this->p);
    dbus_pending_call_unref(this->p);
    this->r = true;
  }

  void end() override { dbus_message_unref(this->msg); }

  DBusMessageIter &get_si() override {
    if (this->r) {
      dbus_message_iter_init(this->msg, &this->si);
      this->r = false;
    }
    return si;
  }
};

class Function_dbus_send_i : public CompoMe::Function_dbus_send {
private:
  DBusMessage *msg;
  DBusConnection *connection;
  DBusMessageIter _a_it;

  bool reset;
  Return_dbus_recv_i rs;

  std::string dest;
  std::string path;
  std::string interface;

public:
  Return_dbus_recv_i &get_rs() { return rs; }

  void set_interface(const std::string interface) {
    this->interface = interface;
  }
  void set_path(const std::string path) { this->path = path; }
  void set_dest(const std::string dest) { this->dest = dest; }
  void set_function(std::string str) override {
    dbus_message_set_member(this->msg, str.c_str());
  }

  Function_dbus_send_i(DBusConnection *p_connection)
      : connection(p_connection), rs() {}

  virtual ~Function_dbus_send_i() {}

  DBusMessageIter &get_so() override {
    if (this->reset) {
      dbus_message_iter_init_append(this->msg, &this->_a_it);
      this->reset = false;
    }

    return this->_a_it;
  }

  void start() override {
    this->msg =
        dbus_message_new_method_call(this->dest.c_str(), this->path.c_str(),
                                     this->interface.c_str(), "NON_SET");
    this->reset = true;
  }

  void send() override {
    dbus_connection_send_with_reply(this->connection, this->msg, &this->rs.p,
                                    -1);
    dbus_message_unref(this->msg);
  }
};

Dbus_client::Dbus_client() : CompoMe::Link(), conn(nullptr) {}

Dbus_client::~Dbus_client() {}

void Dbus_client::step() { Link::step(); }

void Dbus_client::main_connect() {
  Link::main_connect();

  // if (this->conn != nullptr) {
  //   C_WARNING("already connnected");
  // }

  // DBusError err;
  // dbus_error_init(&err);

  // this->conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
  // if (dbus_error_is_set(&err)) {
  //   C_ERROR("Connection Error:", err.message);
  //   dbus_error_free(&err);
  //   return;
  // }

  // if (nullptr == this->conn) {
  //   C_ERROR("Connection Error: nullptr == ", this->conn);
  //   return;
  // }

  // int ret =
  //     dbus_bus_request_name(this->conn, this->get_object_name().str.c_str(),
  //                           DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
  // if (dbus_error_is_set(&err)) {
  //   C_ERROR("Name Error:", err.message);
  //   dbus_error_free(&err);
  //   return;
  // }

  // for (auto &i_f : this->a_f) {
  //   if (!i_f.first->connected()) {
  //     this->connect(*i_f.first);
  //   }
  // }

  // C_INFO("Dbus Client Connected");
}

void Dbus_client::main_disconnect() {
  Link::main_disconnect();
  // for (auto &i_f : this->a_f) {
  //   if (i_f.first->connected()) {
  //     this->disconnect(*i_f.first);
  //   }
  // }

  // if (this->conn != nullptr) {
  //   dbus_connection_unref(this->conn);
  //   this->conn = nullptr;
  // } else {
  //   C_WARNING("Already disconnected");
  // }
}

// void Dbus_client::connect(CompoMe::Require_helper &p_i) {
//   if (this->conn == nullptr) {
//     C_INFO("Connection to external is put in waiting list");
//     return;
//   }

//   auto data = this->a_f[&p_i];

//   Function_dbus_send_i *fs = new Function_dbus_send_i(this->conn);
//   fs->set_dest(std::get<0>(data));
//   fs->set_path(std::get<1>(data));
//   fs->set_interface(std::get<2>(data));

//   auto fake = p_i.fake_dbus_it(*fs, fs->get_rs());
//   T_FS_FAKE t;
//   std::get<0>(t) = fs;
//   std::get<1>(t) = fake;
//   this->function_dbus[&p_i] = t;
// }

// void Dbus_client::disconnect(CompoMe::Require_helper &p_i) {
//   auto t = this->function_dbus[&p_i];
//   p_i.disconnect_it();
//   delete std::get<0>(t);
//   delete std::get<1>(t);
//   this->function_dbus.erase(&p_i);
// }
