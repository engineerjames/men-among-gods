#include "server_message_processing.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "ConstantIdentifiers.h"

// TODO: Review this file completely for commented out sections of code.

static cplayer   pl{};
extern key       okey;
extern cmap *    map;
extern int       ctick;
static look      tmplook;
extern int       unique1;
extern int       unique2;
extern skilltab *playerSkillTab;
extern int       load;

int skill_cmp(const void *a, const void *b)
{
  const skilltab *c, *d;
  int             m1, m2;

  c = static_cast<const skilltab *>(a);
  d = static_cast<const skilltab *>(b);

  m1 = c->nr;
  m2 = d->nr;

  if (m1 == 99 && m2 != 99)
    return 1;
  if (m2 == 99 && m1 != 99)
    return -1;

  if (pl.skill[m1][0] == 0 && pl.skill[m2][0] != 0)
    return 1;
  if (pl.skill[m2][0] == 0 && pl.skill[m1][0] != 0)
    return -1;

  if (c->sortkey > d->sortkey)
    return 1;
  if (c->sortkey < d->sortkey)
    return -1;

  return strcmp(c->name, d->name);
}

const char *logout_reason[] = {
    "unknown",                                                                              // 0
    "Client failed challenge.",                                                             // 1
    "Client was idle too long.",                                                            // 2
    "No room to drop character.",                                                           // 3
    "Invalid parameters.",                                                                  // 4
    "Character already active or no player character.",                                     // 5
    "Invalid password.",                                                                    // 6
    "Client too slow.",                                                                     // 7
    "Receive failure.",                                                                     // 8
    "Server is being shutdown.",                                                            // 9
    "You entered a Tavern.",                                                                // 10
    "Client version too old. Update needed.",                                               // 11
    "Aborting on user request.",                                                            // 12
    "this should never show up",                                                            // 13
    "You have been banned for an hour. Enhance your social behaviour before you come back." // 14
};

void sv_setchar_name1(unsigned char *buf) { std::memcpy(pl.name, buf + 1, 15); }

void sv_setchar_name2(unsigned char *buf) { std::memcpy(pl.name + 15, buf + 1, 15); }

void sv_setchar_name3(unsigned char *buf)
{
  std::memcpy(pl.name + 30, buf + 1, 10);
  strcpy(okey.name, pl.name);
  okey.race = *(unsigned long *)(buf + 11);
  // save_options();
}

void sv_setchar_mode(unsigned char *buf) { pl.mode = buf[1]; }

void sv_setchar_hp(unsigned char *buf)
{
  pl.hp[0] = *(unsigned short *)(buf + 1);
  pl.hp[1] = *(unsigned short *)(buf + 3);
  pl.hp[2] = *(unsigned short *)(buf + 5);
  pl.hp[3] = *(unsigned short *)(buf + 7);
  pl.hp[4] = *(unsigned short *)(buf + 9);
  pl.hp[5] = *(unsigned short *)(buf + 11);
}

void sv_setchar_endur(unsigned char *buf)
{
  pl.end[0] = *(short int *)(buf + 1);
  pl.end[1] = *(short int *)(buf + 3);
  pl.end[2] = *(short int *)(buf + 5);
  pl.end[3] = *(short int *)(buf + 7);
  pl.end[4] = *(short int *)(buf + 9);
  pl.end[5] = *(short int *)(buf + 11);
}

void sv_setchar_mana(unsigned char *buf)
{
  pl.mana[0] = *(short int *)(buf + 1);
  pl.mana[1] = *(short int *)(buf + 3);
  pl.mana[2] = *(short int *)(buf + 5);
  pl.mana[3] = *(short int *)(buf + 7);
  pl.mana[4] = *(short int *)(buf + 9);
  pl.mana[5] = *(short int *)(buf + 11);
}

void sv_setchar_attrib(unsigned char *buf)
{
  int n;

  n = buf[1];
  if (n < 0 || n > 4)
    return;

  pl.attrib[n][0] = buf[2];
  pl.attrib[n][1] = buf[3];
  pl.attrib[n][2] = buf[4];
  pl.attrib[n][3] = buf[5];
  pl.attrib[n][4] = buf[6];
  pl.attrib[n][5] = buf[7];
}

void sv_setchar_skill(unsigned char *buf)
{
  int n;
  n = buf[1];
  if (n < 0 || n > 49)
    return;

  pl.skill[n][0] = buf[2];
  pl.skill[n][1] = buf[3];
  pl.skill[n][2] = buf[4];
  pl.skill[n][3] = buf[5];
  pl.skill[n][4] = buf[6];
  pl.skill[n][5] = buf[7];

  // TODO: Re-evaluate this
  qsort(playerSkillTab, 50, sizeof(skilltab), skill_cmp);
}

void sv_setchar_ahp(unsigned char *buf) { pl.a_hp = *(unsigned short *)(buf + 1); }

void sv_setchar_aend(unsigned char *buf) { pl.a_end = *(unsigned short *)(buf + 1); }

void sv_setchar_amana(unsigned char *buf) { pl.a_mana = *(unsigned short *)(buf + 1); }

void sv_setchar_dir(unsigned char *buf) { pl.dir = *(unsigned char *)(buf + 1); }

void sv_setchar_pts(unsigned char *buf)
{
  pl.points     = *(unsigned long *)(buf + 1);
  pl.points_tot = *(unsigned long *)(buf + 5);
  pl.kindred    = *(unsigned long *)(buf + 9);
}

void sv_setchar_gold(unsigned char *buf)
{
  pl.gold   = *(unsigned long *)(buf + 1);
  pl.armor  = *(unsigned long *)(buf + 5);
  pl.weapon = *(unsigned long *)(buf + 9);
}

void sv_setchar_item(unsigned char *buf)
{
  int n;

  n = *(unsigned long *)(buf + 1);
  if (n < 0 || n > 39)
  {
    std::cerr << "Invalid setchar item" << std::endl;
  }
  pl.item[n]   = *(short int *)(buf + 5);
  pl.item_p[n] = *(short int *)(buf + 7);
}

void sv_setchar_worn(unsigned char *buf)
{
  int n;

  n = *(unsigned long *)(buf + 1);
  if (n < 0 || n > 19)
  {
    std::cerr << "Invalid setchar worn" << std::endl;
  }
  pl.worn[n]   = *(short int *)(buf + 5);
  pl.worn_p[n] = *(short int *)(buf + 7);
}

void sv_setchar_spell(unsigned char *buf)
{
  int n;

  n = *(unsigned long *)(buf + 1);
  if (n < 0 || n > 19)
  {
    std::cerr << "Invalid setchar spell" << std::endl;
  }
  pl.spell[n]  = *(short int *)(buf + 5);
  pl.active[n] = *(short int *)(buf + 7);
}

void sv_setchar_obj(unsigned char *buf)
{
  pl.citem   = *(short int *)(buf + 1);
  pl.citem_p = *(short int *)(buf + 3);
}

static int lastn = 0;

int sv_setmap(unsigned char *buf, int off)
{
  int        n, p;
  static int cnt[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  if (off)
  {
    n = lastn + off;
    p = 2;
  }
  else
  {
    n = *(unsigned short *)(buf + 2);
    p = 4;
  }

  if (n < 0 || n >= TILEX * TILEY)
  {
    std::cerr << "corrupt setmap!" << std::endl;
    return -1;
  }

  lastn = n;
  if (!buf[1])
  {
    std::cerr << "Warning: no flags in setmap!" << std::endl;
    return -1;
  }

  if (buf[1] & 1)
  {
    map[n].ba_sprite = *(unsigned short *)(buf + p);
    p += 2;
    cnt[0]++;
  }
  if (buf[1] & 2)
  {
    map[n].flags = *(unsigned int *)(buf + p);
    p += 4;
    cnt[1]++;
  }
  if (buf[1] & 4)
  {
    map[n].flags2 = *(unsigned int *)(buf + p);
    p += 4;
    cnt[2]++;
  }
  if (buf[1] & 8)
  {
    map[n].it_sprite = *(unsigned short *)(buf + p);
    p += 2;
    cnt[3]++;
  }
  if (buf[1] & 16)
  {
    map[n].it_status = *(unsigned char *)(buf + p);
    p += 1;
    cnt[4]++;
  }
  if (buf[1] & 32)
  {
    map[n].ch_sprite = *(unsigned short *)(buf + p);
    p += 2;
    map[n].ch_status = *(unsigned char *)(buf + p);
    p += 1;
    map[n].ch_stat_off = *(unsigned char *)(buf + p);
    p += 1;
    cnt[5]++;
  }
  if (buf[1] & 64)
  {
    map[n].ch_nr = *(unsigned short *)(buf + p);
    p += 2;
    map[n].ch_id = *(unsigned short *)(buf + p);
    p += 2;
    map[n].ch_speed = *(unsigned char *)(buf + p);
    p += 1;
    cnt[6]++;
  }
  if (buf[1] & 128)
  {
    map[n].ch_proz = *(unsigned char *)(buf + p);
    p += 1;
    cnt[7]++;
  }
  return p;
}

int sv_setmap3(unsigned char *buf, int cnt)
{
  int           n, m, p;
  unsigned char tmp;

  n   = (*(unsigned short *)(buf + 1)) & 2047;
  tmp = (*(unsigned short *)(buf + 1)) >> 12;
  if (n < 0 || n >= TILEX * TILEY)
  {
    std::cerr << "corrupt setmap3!" << std::endl;
    return -1;
  }

  map[n].light = tmp;

  for (m = n + 2, p = 3; m < n + cnt + 2; m += 2, p++)
  {
    if (m < TILEX * TILEY)
    {
      tmp = *(unsigned char *)(buf + p);

      map[m].light     = (unsigned char)(tmp & 15);
      map[m - 1].light = (unsigned char)(tmp >> 4);
    }
  }

  return p;
}

void sv_setorigin(unsigned char *buf)
{
  int x, y, xp, yp, n;

  xp = *(short *)(buf + 1);
  yp = *(short *)(buf + 3);

  for (y = n = 0; y < TILEY; y++)
  {
    for (x = 0; x < TILEX; x++, n++)
    {
      map[n].x = (unsigned short)(x + xp);
      map[n].y = (unsigned short)(y + yp);
    }
  }
}

void sv_tick(unsigned char *buf) { ctick = *(unsigned char *)(buf + 1); }

void sv_log(unsigned char *buf, int)
{
  static char text[512];
  static int  cnt = 0;
  int         n;

  std::memcpy(text + cnt, buf + 1, 15);

  for (n = cnt; n < cnt + 15; n++)
    if (text[n] == 10)
    {
      text[n] = 0;
      std::cerr << text << std::endl;
      cnt = 0;
      return;
    }
  cnt += 15;

  if (cnt > 500)
  {
    std::cerr << "sv_log(): cnt too big!" << std::endl;

    text[cnt] = 0;
    std::cerr << text << std::endl;
    cnt = 0;
  }
}

void sv_scroll_right(unsigned char *) { memmove(map, map + 1, sizeof(struct cmap) * (TILEX * TILEY - 1)); }

void sv_scroll_left(unsigned char *) { memmove(map + 1, map, sizeof(struct cmap) * (TILEX * TILEY - 1)); }

void sv_scroll_down(unsigned char *) { memmove(map, map + TILEX, sizeof(struct cmap) * (TILEX * TILEY - TILEX)); }

void sv_scroll_up(unsigned char *) { memmove(map + TILEX, map, sizeof(struct cmap) * (TILEX * TILEY - TILEX)); }

void sv_scroll_leftup(unsigned char *) { memmove(map + TILEX + 1, map, sizeof(struct cmap) * (TILEX * TILEY - TILEX - 1)); }

void sv_scroll_leftdown(unsigned char *) { memmove(map, map + TILEX - 1, sizeof(struct cmap) * (TILEX * TILEY - TILEX + 1)); }

void sv_scroll_rightup(unsigned char *) { memmove(map + TILEX - 1, map, sizeof(struct cmap) * (TILEX * TILEY - TILEX + 1)); }

void sv_scroll_rightdown(unsigned char *) { memmove(map, map + TILEX + 1, sizeof(struct cmap) * (TILEX * TILEY - TILEX - 1)); }

void sv_look1(unsigned char *buf)
{
  tmplook.worn[0]  = *(unsigned short *)(buf + 1);
  tmplook.worn[2]  = *(unsigned short *)(buf + 3);
  tmplook.worn[3]  = *(unsigned short *)(buf + 5);
  tmplook.worn[5]  = *(unsigned short *)(buf + 7);
  tmplook.worn[6]  = *(unsigned short *)(buf + 9);
  tmplook.worn[7]  = *(unsigned short *)(buf + 11);
  tmplook.worn[8]  = *(unsigned short *)(buf + 13);
  tmplook.autoflag = *(unsigned char *)(buf + 15);
}

void sv_look2(unsigned char *buf)
{
  tmplook.worn[9]  = *(unsigned short *)(buf + 1);  // 1 2
  tmplook.sprite   = *(unsigned short *)(buf + 3);  // 3 4
  tmplook.points   = *(unsigned int *)(buf + 5);    // 5 6 7 8
  tmplook.hp       = *(unsigned int *)(buf + 9);    // 9 10 11 12
  tmplook.worn[10] = *(unsigned short *)(buf + 13); // 13 14
}

void sv_look3(unsigned char *buf)
{
  tmplook.end    = *(unsigned short *)(buf + 1);
  tmplook.a_hp   = *(unsigned short *)(buf + 3);
  tmplook.a_end  = *(unsigned short *)(buf + 5);
  tmplook.nr     = *(unsigned short *)(buf + 7);
  tmplook.id     = *(unsigned short *)(buf + 9);
  tmplook.mana   = *(unsigned short *)(buf + 11);
  tmplook.a_mana = *(unsigned short *)(buf + 13);
}

void sv_look4(unsigned char *buf)
{
  tmplook.worn[1]  = *(unsigned short *)(buf + 1);
  tmplook.worn[4]  = *(unsigned short *)(buf + 3);
  tmplook.extended = buf[5];
  tmplook.pl_price = *(unsigned int *)(buf + 6);
  tmplook.worn[11] = *(unsigned short *)(buf + 10);
  tmplook.worn[12] = *(unsigned short *)(buf + 12);
  tmplook.worn[13] = *(unsigned short *)(buf + 14);
}

void sv_look5(unsigned char *buf)
{
  int n;

  for (n = 0; n < 15; n++)
    tmplook.name[n] = buf[n + 1];
  tmplook.name[15] = 0;

  if (!tmplook.extended)
  {
    if (!tmplook.autoflag)
    {
      // show_look  = 1;
      // look       = tmplook;
      // look_timer = 10 * TICKS;
    }
    // add_look(tmplook.nr, tmplook.name, tmplook.id);
  }
}

void sv_look6(unsigned char *buf)
{
  int n, s;

  s = buf[1];

  for (n = s; n < std::min(62, s + 2); n++)
  {
    tmplook.item[n]  = *(unsigned short *)(buf + 2 + (n - s) * 6);
    tmplook.price[n] = *(unsigned int *)(buf + 4 + (n - s) * 6);
  }
  if (n == 62)
  {
    // show_shop = 1;
    // shop      = tmplook;
  }
}

void sv_settarget(unsigned char *buf)
{
  pl.attack_cn    = *(unsigned short *)(buf + 1);
  pl.goto_x       = *(unsigned short *)(buf + 3);
  pl.goto_y       = *(unsigned short *)(buf + 5);
  pl.misc_action  = *(unsigned short *)(buf + 7);
  pl.misc_target1 = *(unsigned short *)(buf + 9);
  pl.misc_target2 = *(unsigned short *)(buf + 11);
}

void sv_playsound(unsigned char *buf)
{
  int  nr, vol, pan;
  char name[80];

  nr  = *(unsigned int *)(buf + 1);
  vol = *(int *)(buf + 5);
  pan = *(int *)(buf + 9);

  (void)vol;
  (void)pan;
  sprintf(name, "sfx\\%d.wav", nr);
  // play_sound(name, vol, -pan); // add flag to reverse channels!!
}

void sv_exit(unsigned char *buf)
{
  int reason;

  reason = *(unsigned int *)(buf + 1);

  if (reason < 1 || reason > 12)
  {
    std::cerr << "EXIT: Reason unknown." << std::endl;
  }
  else
  {
    std::cerr << "EXIT: " << logout_reason[reason] << std::endl;
  }
  // do_exit = 1;
}

void sv_load(unsigned char *buf)
{
  extern int load;

  load = *(unsigned int *)(buf + 1);
}

void sv_unique(unsigned char *buf)
{
  // extern int load;

  unique1 = *(unsigned int *)(buf + 1);
  unique2 = *(unsigned int *)(buf + 5);
  // save_unique();
}

int sv_ignore(unsigned char *buf)
{
  int        size, d;
  static int cnt = 0, got = 0, start = 0;

  size = *(unsigned int *)(buf + 1);
  got += size;

  if (!start)
  {
    start = time(NULL);
  }

  if (cnt++ > 16)
  {
    cnt = 0;
    d   = time(NULL) - start;
    if (d == 0)
    {
      d = 1;
    }
  }

  return size;
}