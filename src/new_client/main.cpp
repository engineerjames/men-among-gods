#include <cstdio>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ConstantIdentifiers.h"

int so_login(unsigned char *buf) {
  //   unsigned int tmp, prio;
  //   unsigned char obuf[16];
  //   char xbuf[128];
  //   extern int race;
  //   static int capcnt;
  //   static char mod[256];

  //   if (buf[0] ==
  //       SERVER_MESSAGE_TYPES::SV_CHALLENGE) { // answer challenges at once
  //     // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: Login Part I");

  //     tmp = *(unsigned long *)(buf + 1);
  //     tmp = xcrypt(tmp);

  //     obuf[0] = CLIENT_MESSAGE_TYPES::CL_CHALLENGE;
  //     *(unsigned long *)(obuf + 1) = tmp;
  //     *(unsigned long *)(obuf + 5) = VERSION;
  //     *(unsigned long *)(obuf + 9) = race;
  //     send(sock, (char *)obuf, 16, 0);

  //     load_unique();

  //     obuf[0] = CLIENT_MESSAGE_TYPES::CL_CMD_UNIQUE;
  //     *(unsigned long *)(obuf + 1) = unique1;
  //     *(unsigned long *)(obuf + 5) = unique2;
  //     send(sock, (char *)obuf, 16, 0);

  //     capcnt = 0;

  //     return 0;
  //   }
  //   if (buf[0] ==
  //       SERVER_MESSAGE_TYPES::SV_NEWPLAYER) { // answer newplayer at once
  //     // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: Login as New Player OK");
  //     okey.usnr = *(unsigned long *)(buf + 1);
  //     okey.pass1 = *(unsigned long *)(buf + 5);
  //     okey.pass2 = *(unsigned long *)(buf + 9);
  //     ser_ver = *(unsigned char *)(buf + 13);
  //     ser_ver += (int)((*(unsigned char *)(buf + 14))) << 8;
  //     ser_ver += (int)((*(unsigned char *)(buf + 15))) << 16;
  //     save_options();
  //     return 1;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_LOGIN_OK) {
  //     ser_ver = *(unsigned long *)(buf + 1);
  //     // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: Login OK");
  //     return 1;
  //   }

  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_EXIT) {
  //     tmp = *(unsigned int *)(buf + 1);
  //     if (tmp < 1 || tmp > 14)
  //       sprintf(xbuf, "STATUS: Server demands exit:\nunknown reason");
  //     sprintf(xbuf, "STATUS: Server demands exit:\n%s", logout_reason[tmp]);
  //     // SetDlgItemText(hwnd, IDC_STATUS, xbuf);
  //     return -1;
  //   }

  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_CAP) {
  //     tmp = *(unsigned int *)(buf + 1);
  //     prio = *(unsigned int *)(buf + 5);
  //     capcnt++;
  //     sprintf(xbuf,
  //             "STATUS: Player limit reached. Your place in queue: %d.
  //             Priority: "
  //             "%d. Try: %d",
  //             tmp, prio, capcnt);
  //     // SetDlgItemText(hwnd, IDC_STATUS, xbuf);
  //     return 0;
  //   }

  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD1) {
  //     std::memcpy(mod, buf + 1, 15);
  //     return 0;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD2) {
  //     std::memcpy(mod + 15, buf + 1, 15);
  //     return 0;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD3) {
  //     std::memcpy(mod + 30, buf + 1, 15);
  //     return 0;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD4) {
  //     std::memcpy(mod + 45, buf + 1, 15);
  //     return 0;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD5) {
  //     std::memcpy(mod + 60, buf + 1, 15);
  //     return 0;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD6) {
  //     std::memcpy(mod + 75, buf + 1, 15);
  //     return 0;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD7) {
  //     std::memcpy(mod + 90, buf + 1, 15);
  //     return 0;
  //   }
  //   if (buf[0] == SERVER_MESSAGE_TYPES::SV_MOD8) {
  //     std::memcpy(mod + 105, buf + 1, 15);
  //     // SetDlgItemText(hwnd, IDC_MOD, mod);
  //     return 0;
  //   }

  return 0;
}

void so_connect() {
  unsigned char buf[16]{};

  sf::TcpSocket socket;
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
  do {
    std::size_t bytesReceived = 0;
    socket.receive(buf, sizeof(buf), bytesReceived);
    if (bytesReceived == 0) {
      std::cerr << "STATUS: ERROR: Server closed connection.\n";
      return;
    }

    std::cerr << "Exiting early.\n";
    return;

    // tmp = so_login(buf);
    // if (tmp == -1) {
    //   return;
    // }
  } while (true);//!tmp);

  //   do {
  //     if (xrecv(sock, buf, 16, 0) < 16) {
  //       // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: ERROR: Server closed
  //       // connection (2)."); so_status = 0;
  //       return;
  //     }
  //     tmp = so_login(buf);
  //     if (tmp == -1) {
  //       // so_status = 0;
  //       close(sock); // error condition
  //       return;
  //     }
  //   } while (!tmp);

  //   Sleep(500);

  //   ioctlsocket(sock, FIONBIO, (u_long *)&one);

  //   zs.zalloc = Z_NULL;
  //   zs.zfree = Z_NULL;
  //   zs.opaque = Z_NULL;
  //   if (inflateInit(&zs)) {
  //     // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: ERROR: Compressor
  //     failure.");
  //     // so_status = 0;
  //     return;
  //   }

  //   // EndDialog(hwnd, 0);

  return;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Essentially need to call void so_connect(HWND hwnd)
  std::cerr << "Connecting to men-among-gods Server." << std::endl;
  so_connect();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}