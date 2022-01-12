#include <cstdio>
#include <cstring>
#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ConstantIdentifiers.h"

namespace
{
// Global data, needs refactoring
static int           unique1 = 0;
static int           unique2 = 0;
static int           ser_ver = 0;
static key           okey{};
static pdata         playerData{};
static sf::TcpSocket socket{};
static unsigned char tickbuf[TSIZE];
static int           ticksize  = 0; // amount of data in tickbuf
static int           tickstart = 0; // start index to scan buffer for next tick
} // namespace

static void save_unique()
{
  // Do nothing for now
}

static void load_unique()
{
  // Do nothing for now
}

static char secret[256] = {"\
Ifhjf64hH8sa,-#39ddj843tvxcv0434dvsdc40G#34Trefc349534Y5#34trecerr943\
5#erZt#eA534#5erFtw#Trwec,9345mwrxm gerte-534lMIZDN(/dn8sfn8&DBDB/D&s\
8efnsd897)DDzD'D'D''Dofs,t0943-rg-gdfg-gdf.t,e95.34u.5retfrh.wretv.56\
9v4#asf.59m(D)/ND/DDLD;gd+dsa,fw9r,x  OD(98snfsf"};

unsigned int xcrypt(unsigned int val)
{
  unsigned int res = 0;

  res += (unsigned int)(secret[val & 255]);
  res += (unsigned int)(secret[(val >> 8) & 255]) << 8;
  res += (unsigned int)(secret[(val >> 16) & 255]) << 16;
  res += (unsigned int)(secret[(val >> 24) & 255]) << 24;

  res ^= 0x5a7ce52e;

  return res;
}

void send_opt()
{
  static int    state = 0;
  unsigned char buf[16]{};
  int           n{};

  playerData.changed = 1;

  while (playerData.changed == 1)
  {

    buf[0] = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_CMD_SETUSER);

    switch (state)
    {
    case 0:
      buf[1] = 0;
      buf[2] = 0;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.cname[n];
      }
      std::cerr << "Transfering user data...";
      break;
    case 1:
      buf[1] = 0;
      buf[2] = 13;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.cname[n + 13];
      }
      break;
    case 2:
      buf[1] = 0;
      buf[2] = 26;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.cname[n + 26];
      }
      break;
    case 3:
      buf[1] = 0;
      buf[2] = 39;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.cname[n + 39];
      }
      break;
    case 4:
      buf[1] = 0;
      buf[2] = 52;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.cname[n + 52];
      }
      break;
    case 5:
      buf[1] = 0;
      buf[2] = 65;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.cname[n + 65];
      }
      break;

    case 6:
      buf[1] = 1;
      buf[2] = 0;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n];
      }
      break;
    case 7:
      buf[1] = 1;
      buf[2] = 13;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 13];
      }
      break;
    case 8:
      buf[1] = 1;
      buf[2] = 26;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 26];
      }
      break;
    case 9:
      buf[1] = 1;
      buf[2] = 39;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 39];
      }
      break;
    case 10:
      buf[1] = 1;
      buf[2] = 52;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 52];
      }
      break;
    case 11:
      buf[1] = 1;
      buf[2] = 65;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 65];
      }
      break;

    case 12:
      buf[1] = 2;
      buf[2] = 0;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 78];
      }
      break;
    case 13:
      buf[1] = 2;
      buf[2] = 13;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 91];
      }
      break;
    case 14:
      buf[1] = 2;
      buf[2] = 26;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 104];
      }
      break;
    case 15:
      buf[1] = 2;
      buf[2] = 39;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 117];
      }
      break;
    case 16:
      buf[1] = 2;
      buf[2] = 52;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 130];
      }
      break;
    case 17:
      buf[1] = 2;
      buf[2] = 65;
      for (n = 0; n < 13; n++)
      {
        buf[n + 3] = playerData.desc[n + 143];
      }
      playerData.changed = 0;
      std::cerr << "Transfer done.\n";
      break;
    }

    socket.send(buf, sizeof(buf));
    state++;
  }
}

int so_login(unsigned char *buf)
{
  unsigned int  tmp{};
  unsigned int  prio{};
  unsigned char obuf[16]{};

  static int  capcnt{};
  static char mod[256]{};

  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_CHALLENGE))
  { // answer challenges at once
    // SetDlgItemText(hwnd, IDC_STATUS, "STATUS: Login Part I");

    tmp = *(unsigned long *)(buf + 1);
    tmp = xcrypt(tmp);

    obuf[0]                      = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_CHALLENGE);
    *(unsigned long *)(obuf + 1) = tmp;
    *(unsigned long *)(obuf + 5) = VERSION;
    *(unsigned long *)(obuf + 9) = 1;
    std::cerr << "Sending CL_CHALLENGE...\n";
    socket.send(obuf, sizeof(obuf));

    load_unique();

    obuf[0]                      = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_CMD_UNIQUE);
    *(unsigned long *)(obuf + 1) = unique1;
    *(unsigned long *)(obuf + 5) = unique2;
    std::cerr << "Sending CL_CMD_UNIQUE...\n";
    socket.send(obuf, sizeof(obuf));

    capcnt = 0;

    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_NEWPLAYER))
  {                                           // answer newplayer at once
    okey.usnr  = *(unsigned long *)(buf + 1); // Unique player ID
    okey.pass1 = *(unsigned long *)(buf + 5);
    okey.pass2 = *(unsigned long *)(buf + 9);
    ser_ver    = *(unsigned char *)(buf + 13);
    ser_ver += (int)((*(unsigned char *)(buf + 14))) << 8;
    ser_ver += (int)((*(unsigned char *)(buf + 15))) << 16;
    std::cerr << "Server Response: SV_NEWPLAYER...\n";
    std::cerr << "received usnr:" << okey.usnr << std::endl;
    std::cerr << "received pass1:" << okey.pass1 << std::endl;
    std::cerr << "received pass2:" << okey.pass2 << std::endl;
    return 1;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOGIN_OK))
  {
    ser_ver = *(unsigned long *)(buf + 1);
    std::cerr << "Server Response: LOGIN OK...\n";
    return 1;
  }

  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_EXIT))
  {
    tmp = *(unsigned int *)(buf + 1);
    if (tmp < 1 || tmp > 14)
    {
      // std::cerr << "STATUS: Server demands exit:\nunknown reason";
    }
    std::cerr << "STATUS: Server demands exit.\n";

    return -1;
  }

  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_CAP))
  {
    tmp  = *(unsigned int *)(buf + 1);
    prio = *(unsigned int *)(buf + 5);
    capcnt++;
    std::cerr << "STATUS: Player limit reached. You're in queue.\n";
    return 0;
  }

  // Message of the Day Processing
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD1))
  {
    std::memcpy(mod, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD1...\n";
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD2))
  {
    std::memcpy(mod + 15, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD2...\n";
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD3))
  {
    std::memcpy(mod + 30, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD3...\n";
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD4))
  {
    std::memcpy(mod + 45, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD4...\n";
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD5))
  {
    std::memcpy(mod + 60, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD5...\n";
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD6))
  {
    std::memcpy(mod + 75, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD6...\n";
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD7))
  {
    std::memcpy(mod + 90, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD7...\n";
    return 0;
  }
  if (buf[0] == static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_MOD8))
  {
    std::memcpy(mod + 105, buf + 1, 15);
    std::cerr << "Server Response: SV_MOD8...\n";
    std::cerr << mod << std::endl;
    return 0;
  }

  return 0;
}

void so_connect()
{
  unsigned char buf[16]{};

  sf::Socket::Status status = socket.connect(MHOST, MHOST_PORT);
  if (status != sf::Socket::Done)
  {
    std::cerr << "Error connecting to host." << std::endl;
    return;
  }

  // Send password infomation
  // Hard-code an empty password for now, but no need to send it
  // since the legacy code just sent a 0-initialized byte buffer if
  // the password was empty... I think.

  std::cerr << "Sending initial password...\n";
  const std::string myEmptyPassword = "";
  buf[0]                            = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_PASSWD);
  socket.send(buf, sizeof(buf));

  // Assume we're creating a new character each time.
  // Normally you'd need to send the 'key' structure (username, pass1, pass2,
  // etc.)
  std::cerr << "Sending new login request...\n";
  buf[0] = static_cast<unsigned char>(CLIENT_MESSAGE_TYPES::CL_NEWLOGIN);
  socket.send(buf, sizeof(buf));

  std::cerr << "Waiting for receipt of information...\n";
  int tmp = 0;
  do
  {
    std::size_t        bytesReceived = 0;
    sf::Socket::Status status        = socket.receive(buf, sizeof(buf), bytesReceived);
    if (bytesReceived == 0 || status == sf::Socket::Status::Disconnected)
    {
      std::cerr << "STATUS: ERROR: Server closed connection.\n";
      return;
    }
    else
    {
      std::cerr << "Receieved data from the server: " << bytesReceived << " bytes." << std::endl;
    }

    tmp = so_login(buf);
    if (tmp == -1)
    {
      std::cerr << "Error logging in!" << std::endl;
      socket.disconnect();
      return;
    }
  } while (!tmp);

  return;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(MODEX, MODEY), "Mercenaries of Astonia - New Client");
  window.setFramerateLimit(60);

  // Essentially need to call void so_connect(HWND hwnd)
  std::cerr << "Connecting to men-among-gods Server." << std::endl;
  so_connect();
  std::cerr << "Connected to server: " << socket.getRemoteAddress() << ":" << socket.getRemotePort() << std::endl;

  send_opt();

  // After we initialize the connection, set the socket to non-blocking I/O
  socket.setBlocking(false);

  sf::Uint64 frameCount = 0;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // Check to see if we have data from the server available
    std::size_t        bytesReceived = 0;
    sf::Socket::Status status        = socket.receive(tickbuf, ticksize, bytesReceived);

    if (bytesReceived != 0)
    {
      std::cerr << "Received data from the server: " << tickbuf[0] << std::endl;
    }

    window.clear();
    // window.draw(ourstuff);
    window.display();

    // This is essentially our 'keep-alive' message to the server.  Otherwise we
    // get a protocol-level timeout after a minute or so.  Why is this even a
    // good idea?
    frameCount++;

    if (frameCount % 60 == 0)
    {
      unsigned char buf[16]{};
      buf[0]                     = (unsigned char)CLIENT_MESSAGE_TYPES::CL_CMD_CTICK;
      *(unsigned int *)(buf + 1) = frameCount;

      std::cerr << "Sending CL_CMD_CTICK: " << frameCount << " with status: " << status << std::endl;

      std::cerr << socket.getLocalPort() << std::endl;

      std::size_t dataSent{};
      status = socket.send(buf, sizeof(buf), dataSent);
    }
  }

  return 0;
}