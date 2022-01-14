#ifndef SERVER_MESSAGE_PROCESSING_H
#define SERVER_MESSAGE_PROCESSING_H

void sv_setchar_name1(unsigned char *buf);
void sv_setchar_name2(unsigned char *buf);
void sv_setchar_name3(unsigned char *buf);
void sv_setchar_mode(unsigned char *buf);
void sv_setchar_hp(unsigned char *buf);
void sv_setchar_endur(unsigned char *buf);
void sv_setchar_mana(unsigned char *buf);
void sv_setchar_attrib(unsigned char *buf);
void sv_setchar_skill(unsigned char *buf);
void sv_setchar_ahp(unsigned char *buf);
void sv_setchar_aend(unsigned char *buf);
void sv_setchar_amana(unsigned char *buf);
void sv_setchar_dir(unsigned char *buf);
void sv_setchar_pts(unsigned char *buf);
void sv_setchar_gold(unsigned char *buf);
void sv_setchar_item(unsigned char *buf);
void sv_setchar_worn(unsigned char *buf);
void sv_setchar_spell(unsigned char *buf);
void sv_setchar_obj(unsigned char *buf);
int  sv_setmap(unsigned char *buf, int off);
int  sv_setmap3(unsigned char *buf, int cnt);
void sv_setorigin(unsigned char *buf);
void sv_tick(unsigned char *buf);
void sv_log(unsigned char *buf, int font);
void sv_scroll_right(unsigned char *buf);
void sv_scroll_left(unsigned char *buf);
void sv_scroll_down(unsigned char *buf);
void sv_scroll_up(unsigned char *buf);
void sv_scroll_leftup(unsigned char *buf);
void sv_scroll_leftdown(unsigned char *buf);
void sv_scroll_rightup(unsigned char *buf);
void sv_scroll_rightdown(unsigned char *buf);
void sv_look1(unsigned char *buf);
void sv_look2(unsigned char *buf);
void sv_look3(unsigned char *buf);
void sv_look4(unsigned char *buf);
void sv_look5(unsigned char *buf);
void sv_look6(unsigned char *buf);
void sv_settarget(unsigned char *buf);
void sv_playsound(unsigned char *buf);
void sv_exit(unsigned char *buf);
void sv_load(unsigned char *buf);
void sv_unique(unsigned char *buf);
int  sv_ignore(unsigned char *buf);
int  skill_cmp(const void *a, const void *b);

#endif // SERVER_MESSAGE_PROCESSING_H