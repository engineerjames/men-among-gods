#include <atomic>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ConstantIdentifiers.h"
#include "server_message_processing.h"

#include <zlib.h>


skilltab static_skilltab[50]={
	{0,     'C',    "Hand to Hand", "Fighting without weapons.",                    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{1,     'C',    "Karate",       "Fighting without weapons and doing damage.",   {AT_BRAVE,AT_AGIL,AT_STREN}},
	{2,     'C',    "Dagger",       "Fighting with daggers or similiar weapons.",   {AT_BRAVE,AT_AGIL,AT_INT}},
	{3,     'C',    "Sword",        "Fighting with swords or similiar weapons.",    {AT_BRAVE,AT_AGIL,AT_STREN}},
	{4,     'C',    "Axe",          "Fighting with axes or similiar weapons.",      {AT_BRAVE,AT_STREN,AT_STREN}},
	{5,     'C',    "Staff",        "Fighting with staffs or similiar weapons.",    {AT_AGIL,AT_STREN,AT_STREN}},
	{6,     'C',    "Two-Handed",   "Fighting with two-handed weapons.",            {AT_AGIL,AT_STREN,AT_STREN}},

	{7,     'G',    "Lock-Picking", "Opening doors without keys.",                  {AT_INT,AT_WILL,AT_AGIL}},
	{8,     'G',    "Stealth",      "Moving without being seen or heard.",          {AT_INT,AT_WILL,AT_AGIL}},
	{9,     'G',    "Perception",   "Seeing and hearing.",                          {AT_INT,AT_WILL,AT_AGIL}},

	{10,    'M',    "Swimming",     "Moving through water without drowning.",       {AT_INT,AT_WILL,AT_AGIL}},
	{11,    'R',    "Magic Shield", "Spell: Create a magic shield (Cost: 25 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},

	{12,    'G',    "Bartering",    "Getting good prices from merchants.",          {AT_BRAVE,AT_INT,AT_WILL}},
	{13,    'G',    "Repair",       "Repairing items.",                             {AT_INT,AT_WILL,AT_AGIL}},

	{14,    'R',    "Light",        "Spell: Create light (Cost: 5 Mana).",           {AT_BRAVE,AT_INT,AT_WILL}},
	{15,    'R',    "Recall",       "Spell: Teleport to temple (Cost: 15 Mana).",    {AT_BRAVE,AT_INT,AT_WILL}},
	{16,    'R',    "Guardian Angel","Spell: Avoid loss of HPs and items on death.", {AT_BRAVE,AT_INT,AT_WILL}},
	{17,    'R',    "Protection",   "Spell: Enhance Armor of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{18,    'R',    "Enhance Weapon","Spell: Enhance Weapon of target (Cost: 15 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{19,    'R',    "Stun",         "Spell: Make target motionless (Cost: 20 Mana).",   {AT_BRAVE,AT_INT,AT_WILL}},
	{20,    'R',    "Curse",        "Spell: Decrease attributes of target (Cost: 35 Mana).",  {AT_BRAVE,AT_INT,AT_WILL}},
	{21,    'R',    "Bless",        "Spell: Increase attributes of target (Cost: 35 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},
	{22,    'R',    "Identify",     "Spell: Read stats of item/character. (Cost: 25 Mana)",   {AT_BRAVE,AT_INT,AT_WILL}},

	{23,    'G',    "Resistance",   "Resist against magic.",                        {AT_INT,AT_WILL,AT_STREN}},

	{24,    'R',    "Blast",        "Spell: Inflict injuries to target (Cost: varies).", {AT_INT,AT_WILL,AT_STREN}},
	{25,    'R',    "Dispel Magic", "Spell: Removes curse magic from target (Cost: 25 Mana).", {AT_BRAVE,AT_INT,AT_WILL}},

	{26,    'R',    "Heal",         "Spell: Heal injuries (Cost: 25 Mana).",         {AT_BRAVE,AT_INT,AT_WILL}},
	{27,    'R',    "Ghost Companion","Spell: Create a ghost to attack an enemy.",    {AT_BRAVE,AT_INT,AT_WILL}},

	{28,    'B',    "Regenerate",   "Regenerate Hitpoints faster.",                 {AT_STREN,AT_STREN,AT_STREN}},
	{29,    'B',    "Rest",         "Regenerate Endurance faster.",                 {AT_AGIL,AT_AGIL,AT_AGIL}},
	{30,    'B',    "Meditate",     "Regenerate Mana faster.",                      {AT_INT,AT_WILL,AT_WILL}},

	{31,    'G',    "Sense Magic",  "Find out who casts what at you.",              {AT_BRAVE,AT_INT,AT_WILL}},
	{32,    'G',    "Immunity",     "Partial immunity against negative magic.",     {AT_BRAVE,AT_AGIL,AT_STREN}},
	{33,    'G',    "Surround Hit", "Hit all your enemies at once.",                {AT_BRAVE,AT_AGIL,AT_STREN}},
	{34,    'G',    "Concentrate",  "Reduces mana cost for all spells.",            {AT_WILL,AT_WILL,AT_WILL}},
	{35,    'G',    "Warcry",       "Frighten all enemies in hearing distance.",    {AT_BRAVE,AT_BRAVE,AT_STREN}},

	{36,   'Z',   "", "", {0,0,0,}},
	{37,   'Z',   "", "", {0,0,0,}},
	{38,   'Z',   "", "", {0,0,0,}},
	{39,   'Z',   "", "", {0,0,0,}},

	{40,   'Z',   "", "", {0,0,0,}},
	{41,   'Z',   "", "", {0,0,0,}},
	{42,   'Z',   "", "", {0,0,0,}},
	{43,   'Z',   "", "", {0,0,0,}},
	{44,   'Z',   "", "", {0,0,0,}},
	{45,   'Z',   "", "", {0,0,0,}},
	{46,   'Z',   "", "", {0,0,0,}},
	{47,   'Z',   "", "", {0,0,0,}},
	{48,   'Z',   "", "", {0,0,0,}},
	{49,   'Z',   "", "", {0,0,0,}}};

// Global data, needs refactoring
int           unique1 = 0;
int           unique2 = 0;
static int           ser_ver = 0;
key                  okey{};
static pdata         playerData{};
static sf::TcpSocket socket{};
static unsigned char tickbuf[TSIZE];
static int           ticksize     = 0; // amount of data in tickbuf
static int           tickstart    = 0; // start index to scan buffer for next tick
static int           ticksInQueue = 0;
int                  ctick        = 0;
static int           lastn        = 0;
std::atomic<bool>    stopRequested;
static z_stream_s    zs{};
cmap *               map;
skilltab *    playerSkillTab;
int load = 0;

// TODO: Why did I have to remove static for 'extern' in the other translation unit to pick
// up the definitions correctly?

static char secret[256] = {"\
Ifhjf64hH8sa,-#39ddj843tvxcv0434dvsdc40G#34Trefc349534Y5#34trecerr943\
5#erZt#eA534#5erFtw#Trwec,9345mwrxm gerte-534lMIZDN(/dn8sfn8&DBDB/D&s\
8efnsd897)DDzD'D'D''Dofs,t0943-rg-gdfg-gdf.t,e95.34u.5retfrh.wretv.56\
9v4#asf.59m(D)/ND/DDLD;gd+dsa,fw9r,x  OD(98snfsf"};

int sv_cmd(unsigned char *buf)
{

  if (buf[0] & static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETMAP))
    return sv_setmap(buf, buf[0] & ~static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETMAP));

  switch (buf[0])
  {
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_NAME1):
    sv_setchar_name1(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_NAME2):
    sv_setchar_name2(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_NAME3):
    sv_setchar_name3(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_MODE):
    sv_setchar_mode(buf);
    return 2;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_ATTRIB):
    sv_setchar_attrib(buf);
    return 8;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_SKILL):
    sv_setchar_skill(buf);
    return 8;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_HP):
    sv_setchar_hp(buf);
    return 13;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_ENDUR):
    sv_setchar_endur(buf);
    return 13;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_MANA):
    sv_setchar_mana(buf);
    return 13;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_AHP):
    sv_setchar_ahp(buf);
    return 3;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_AEND):
    sv_setchar_aend(buf);
    return 3;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_AMANA):
    sv_setchar_amana(buf);
    return 3;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_DIR):
    sv_setchar_dir(buf);
    return 2;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_PTS):
    sv_setchar_pts(buf);
    return 13;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_GOLD):
    sv_setchar_gold(buf);
    return 13;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_ITEM):
    sv_setchar_item(buf);
    return 9;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_WORN):
    sv_setchar_worn(buf);
    return 9;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_SPELL):
    sv_setchar_spell(buf);
    return 9;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETCHAR_OBJ):
    sv_setchar_obj(buf);
    return 5;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETMAP3):
    return sv_setmap3(buf, 26);
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETMAP4):
    return sv_setmap3(buf, 0);
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETMAP5):
    return sv_setmap3(buf, 2);
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETMAP6):
    return sv_setmap3(buf, 6);
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETORIGIN):
    sv_setorigin(buf);
    return 5;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_TICK):
    sv_tick(buf);
    return 2;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOG0):
    sv_log(buf, 0);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOG1):
    sv_log(buf, 1);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOG2):
    sv_log(buf, 2);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOG3):
    sv_log(buf, 3);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_RIGHT):
    sv_scroll_right(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_LEFT):
    sv_scroll_left(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_DOWN):
    sv_scroll_down(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_UP):
    sv_scroll_up(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_RIGHTDOWN):
    sv_scroll_rightdown(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_RIGHTUP):
    sv_scroll_rightup(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_LEFTDOWN):
    sv_scroll_leftdown(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SCROLL_LEFTUP):
    sv_scroll_leftup(buf);
    return 1;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOOK1):
    sv_look1(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOOK2):
    sv_look2(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOOK3):
    sv_look3(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOOK4):
    sv_look4(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOOK5):
    sv_look5(buf);
    break;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOOK6):
    sv_look6(buf);
    break;

  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_SETTARGET):
    sv_settarget(buf);
    return 13;

  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_PLAYSOUND):
    sv_playsound(buf);
    return 13;

  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_EXIT):
    sv_exit(buf);
    break;

  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_LOAD):
    sv_load(buf);
    return 5;

  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_UNIQUE):
    sv_unique(buf);
    return 9;
  case static_cast<unsigned char>(SERVER_MESSAGE_TYPES::SV_IGNORE):
    return sv_ignore(buf);

  default:
    std::cerr << "Unknown server message type!" << std::endl;
    return -1;
  }

  return 16;
}

int tick_do(void)
{
  int                  len   = 0;
  int                  idx   = 0;
  int                  ret   = 0;
  int                  csize = 0;
  int                  comp  = 0;
  static unsigned char buf[65536];
  static int           ctot = 1;
  static int           utot = 1;
  static int           t    = 0;
  static int           td   = 0;

  if (!t)
    t = time(NULL);

  len  = *(unsigned short *)(tickbuf);
  comp = len & 0x8000;
  len &= 0x7fff;
  ctot += len;
  if (len > ticksize)
    return 0;

  if (comp)
  {
    zs.next_in  = tickbuf + 2;
    zs.avail_in = len - 2;

    zs.next_out  = buf;
    zs.avail_out = 65536;

    ret = inflate(&zs, Z_SYNC_FLUSH);
    if (ret != Z_OK)
    {
      std::cerr << "uncompress error!" << std::endl;
      std::cerr << "Error code is: " << ret << std::endl;
    }

    if (zs.avail_in)
    {
      std::cerr << "uncompress: avail is " << zs.avail_in << std::endl;
    }

    csize = 65536 - zs.avail_out;
  }
  else
  {
    csize = len - 2;
    if (csize)
      memcpy(buf, tickbuf + 2, csize);
  }

  utot += csize;

  td = time(NULL) - t;
  if (!td)
    td = 1;

  lastn = -1; // reset sv_setmap
  ctick++;
  if (ctick > 19)
    ctick = 0;

  while (idx < csize)
  {
    ret = sv_cmd(buf + idx);
    if (ret == -1)
    {
      std::cerr << "Warning: syntax error in server data";
      exit(1);
    }
    idx += ret;
  }

  ticksize -= len;
  tickstart -= len;
  ticksInQueue--;

  if (ticksize)
    memmove(tickbuf, tickbuf + len, ticksize);

  // engine_tick();

  return 1;
}

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
    default:
      std::cerr << "Invalid state!" << std::endl;
      break;
    }

    socket.send(buf, sizeof(buf));
    state++;
  }
}

int so_login(unsigned char *buf)
{
  unsigned int  tmp{};
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
    tmp = *(unsigned int *)(buf + 1);
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
    std::size_t bytesReceived = 0;
    status                    = socket.receive(buf, sizeof(buf), bytesReceived);
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
  map = static_cast<cmap *>(calloc(MAPX * MAPY * sizeof(struct cmap), 1));

  for (int n = 0; n < MAPX * MAPY; n++)
  {
    map[n].ba_sprite = SPR_EMPTY;
  }

  playerSkillTab = static_cast<skilltab *>(malloc(sizeof(struct skilltab) * 50));
  for (int n = 0; n < 50; n++)
  {
    playerSkillTab[n]           = static_skilltab[n];
    playerSkillTab[n].attrib[0] = 1;
  }

  sf::RenderWindow window(sf::VideoMode(MODEX, MODEY), "Mercenaries of Astonia - New Client");
  window.setFramerateLimit(60);

  stopRequested.store(false);

  // Start networking thread
  std::thread networkThread{[]() {
    std::cerr << "Connecting to men-among-gods Server." << std::endl;
    so_connect();
    std::cerr << "Connected to server: " << socket.getRemoteAddress() << ":" << socket.getRemotePort() << std::endl;
    send_opt();

    socket.setBlocking(false);

    std::size_t tickCount = 0;

    while (!stopRequested.load())
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));

      unsigned char buf[16]{};
      buf[0]                     = (unsigned char)CLIENT_MESSAGE_TYPES::CL_CMD_CTICK;
      *(unsigned int *)(buf + 1) = tickCount++;

      std::size_t        dataSent{};
      sf::Socket::Status status = socket.send(buf, sizeof(buf), dataSent);

      std::cerr << "Sending CL_CMD_CTICK: " << tickCount << " with status: " << status << std::endl;

      unsigned char      inputBuffer[1024]{};
      std::size_t        received{};
      sf::Socket::Status recStatus = socket.receive(inputBuffer, sizeof(inputBuffer), received);

      // Copy bytes into tickbuffer
      std::memcpy(tickbuf + ticksize, inputBuffer, received);
      ticksize += received;

      if (ticksize >= tickstart + 2)
      {
        int tmp = *(unsigned short *)(tickbuf + tickstart);
        tmp &= 0x7fff;
        if (tmp < 2)
        {
          std::cerr << "Transmission corrupt!" << std::endl;
        }

        tickstart += tmp;
        ticksInQueue++;
      }

      std::cerr << "Received " << received << " bytes with status: " << recStatus << std::endl;
      std::cerr << "Ticksize now: " << ticksize << std::endl;
      std::cerr << "ticksInQueue: " << ticksInQueue << std::endl;
      tick_do();
    }
  }};

  networkThread.detach();

  // Need to implement log_system_data()
  // Also, look at rec_player and send_player--these are the main I/O pathways to the client
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    // window.draw(ourstuff);
    window.display();
  }

  stopRequested.store(true);

  return 0;
}