#include <cstdio>
#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ConstantIdentifiers.h"

namespace {
// Global data, needs refactoring
static int unique1 = 0;
static int unique2 = 0;
static int ser_ver = 0;
static key okey{};
static sf::TcpSocket socket{};
static unsigned char tickbuf[TSIZE];
static int ticksize = 0;  // amount of data in tickbuf
static int tickstart = 0; // start index to scan buffer for next tick
} // namespace

static void save_unique() {
  // Do nothing for now
}

static void load_unique() {
  // Do nothing for now
}

static char secret[256] = {"\
Ifhjf64hH8sa,-#39ddj843tvxcv0434dvsdc40G#34Trefc349534Y5#34trecerr943\
5#erZt#eA534#5erFtw#Trwec,9345mwrxm gerte-534lMIZDN(/dn8sfn8&DBDB/D&s\
8efnsd897)DDzD'D'D''Dofs,t0943-rg-gdfg-gdf.t,e95.34u.5retfrh.wretv.56\
9v4#asf.59m(D)/ND/DDLD;gd+dsa,fw9r,x  OD(98snfsf"};

unsigned int xcrypt(unsigned int val) {
  unsigned int res = 0;

  res += (unsigned int)(secret[val & 255]);
  res += (unsigned int)(secret[(val >> 8) & 255]) << 8;
  res += (unsigned int)(secret[(val >> 16) & 255]) << 16;
  res += (unsigned int)(secret[(val >> 24) & 255]) << 24;

  res ^= 0x5a7ce52e;

  return res;
}

int so_login(unsigned char *buf) {
  unsigned int tmp{};
  unsigned int prio{};
  unsigned char obuf[16]{};

  static int capcnt{};
  static char mod[256]{};

  if (buf[0] ==
      static_cast<unsigned char>(
          SERVER_MESSAGE_TYPES::SV_CHALLENGE)) { // answer challenges at once
    // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: Login Part I");

    tmp = *(unsigned long *)(buf + 1);
    tmp = xcrypt(tmp);

    obuf[0] = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_CHALLENGE);
    *(unsigned long *)(obuf + 1) = tmp;
    *(unsigned long *)(obuf + 5) = VERSION;
    *(unsigned long *)(obuf + 9) = 1;
    std::cerr << "Sending CL_CHALLENGE...\n";
    socket.send(obuf, sizeof(obuf));

    load_unique();

    obuf[0] = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_CMD_UNIQUE);
    *(unsigned long *)(obuf + 1) = unique1;
    *(unsigned long *)(obuf + 5) = unique2;
    std::cerr << "Sending CL_CMD_UNIQUE...\n";
    socket.send(obuf, sizeof(obuf));

    capcnt = 0;

    return 0;
  }
  if (buf[0] ==
      static_cast<unsigned char>(
          SERVER_MESSAGE_TYPES::SV_NEWPLAYER)) { // answer newplayer at once
    okey.usnr = *(unsigned long *)(buf + 1);     // Unique player ID
    okey.pass1 = *(unsigned long *)(buf + 5);
    okey.pass2 = *(unsigned long *)(buf + 9);
    ser_ver = *(unsigned char *)(buf + 13);
    ser_ver += (int)((*(unsigned char *)(buf + 14))) << 8;
    ser_ver += (int)((*(unsigned char *)(buf + 15))) << 16;
    std::cerr << "Server Response: SV_NEWPLAYER...\n";
    std::cerr << "received usnr:" << okey.usnr << std::endl;
    std::cerr << "received pass1:" << okey.pass1 << std::endl;
    std::cerr << "received pass2:" << okey.pass2 << std::endl;
    return 1;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOGIN_OK)) {
    ser_ver = *(unsigned long *)(buf + 1);
    std::cerr << "Server Response: LOGIN OK...\n";
    return 1;
  }

  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_EXIT)) {
    tmp = *(unsigned int *)(buf + 1);
    if (tmp < 1 || tmp > 14) {
      // std::cerr << "STATUS: Server demands exit:\nunknown reason";
    }
    std::cerr << "STATUS: Server demands exit.\n";

    return -1;
  }

  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_CAP)) {
    tmp = *(unsigned int *)(buf + 1);
    prio = *(unsigned int *)(buf + 5);
    capcnt++;
    std::cerr << "STATUS: Player limit reached. You're in queue.\n";
    return 0;
  }

  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD1)) {
    std::memcpy(mod, buf + 1, 15);
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD2)) {
    std::memcpy(mod + 15, buf + 1, 15);
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD3)) {
    std::memcpy(mod + 30, buf + 1, 15);
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD4)) {
    std::memcpy(mod + 45, buf + 1, 15);
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD5)) {
    std::memcpy(mod + 60, buf + 1, 15);
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD6)) {
    std::memcpy(mod + 75, buf + 1, 15);
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD7)) {
    std::memcpy(mod + 90, buf + 1, 15);
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD8)) {
    std::memcpy(mod + 105, buf + 1, 15);
    return 0;
  }

  return 0;
}

void so_connect() {
  unsigned char buf[16]{};

  sf::Socket::Status status = socket.connect(MHOST, MHOST_PORT);
  if (status != sf::Socket::Done) {
    std::cerr << "Error connecting to host." << std::endl;
    return;
  }

  // Send password infomation
  // Hard-code an empty password for now, but no need to send it
  // since the legacy code just sent a 0-initialized byte buffer if
  // the password was empty... I think.

  std::cerr << "Sending initial password...\n";
  const std::string myEmptyPassword = "";
  buf[0] = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_PASSWD);
  socket.send(buf, sizeof(buf));

  // Assume we're creating a new character each time.
  // Normally you'd need to send the 'key' structure (username, pass1, pass2,
  // etc.)
  std::cerr << "Sending new login request...\n";
  buf[0] = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_NEWLOGIN);
  socket.send(buf, sizeof(buf));

  std::cerr << "Waiting for receipt of information...\n";
  int tmp = 0;
  do {
    std::size_t bytesReceived = 0;
    socket.receive(buf, sizeof(buf), bytesReceived);
    if (bytesReceived == 0) {
      std::cerr << "STATUS: ERROR: Server closed connection.\n";
      return;
    }

    tmp = so_login(buf);
    if (tmp == -1) {
      return;
    }
  } while (!tmp);

  return;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Essentially need to call void so_connect(HWND hwnd)
  std::cerr << "Connecting to men-among-gods Server." << std::endl;
  so_connect();
  std::cerr << "Connected to server: " << socket.getRemoteAddress() << ":"
            << socket.getRemotePort() << std::endl;

  // After we initialize the connection, set the socket to non-blocking I/O
  socket.setBlocking(false);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Check to see if we have data from the server available
    std::size_t bytesReceived = 0;
    socket.receive(tickbuf, ticksize, bytesReceived);

    if (bytesReceived != 0)
    {
      std::cerr << "Received data from the server: " << tickbuf[0] << std::endl;
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}