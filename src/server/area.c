/*************************************************************************

This file is part of 'Mercenaries of Astonia v2'
Copyright (c) 1997-2001 Daniel Brockhaus (joker@astonia.com)
All rights reserved.

**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "server.h"

struct area {
        int x1,y1;
        int x2,y2;
        char *name;
        int flag;       // 0=in, 1=the, 2=on, 3=at
};

struct area area[]={
        {481,407,       633,596,        "Aston",                        0}, // 0
        {497,205,       537,233,        "Lizard Temple",                1}, // 1
        {480,234,       634,405,        "Strange Forest",               1}, // 2
        {840,0,         1024,157,       "Underground I",                0}, // 3
        {491,504,       520,520,        "Temple of Skua",               1}, // 4
        {520,524,       529,534,        "Leather Armor Shop",           1}, // 5
        {539,525,       548,532,        "Jamil's House",                0}, // 6
        {545,536,       564,548,        "Temple of the Purple One",     1}, // 7
        {499,539,       528,550,        "Thieves House I",              1}, // 8
        { 20, 20,        49, 69,        "Thieves House I",              1}, // 9
        {499,525,       514,538,        "Thieves House II",             1}, // 10
        {532,439,       536,550,        "Temple Street",                2}, // 11
        {532,551,       578,555,        "Rose Street",                  2}, // 12
        {538,559,       575,588,        "Cursed Tomb",                  1}, // 13
        {574,496,       578,550,        "Castle Way",                   2}, // 14
        {588,530,       623,554,        "Haunted Castle",               1}, // 15
        {562,525,       570,531,        "Inga's House",                 0}, // 16
        {582,519,       587,524,        "Jefferson's House",            0}, // 17
        {582,510,       591,514,        "Steel Armor Shop",             1}, // 18
        {554,509,       570,520,        "Joe's House",                  0}, // 19
        {582,498,       588,505,        "Bronze Armor Shop",            1}, // 20
        {569,468,       582,487,        "Damor's Magic Shop",           0}, // 21
        {558,481,       567,487,        "Brunhild's Shop",              0}, // 22
        {555,499,       563,504,        "Sirjan's House",               0}, // 23
        {541,499,       549,503,        "Cloth Armor Shop",             1}, // 24
        {540,479,       553,487,        "Weapon Shop",                  1}, // 25
        {507,482,       514,487,        "Tavern of the Blue Ogre",      1}, // 26
        {515,436,       522,444,        "Bank",                         1}, // 27
        {540,442,       546,451,        "Cirrus' House",                0}, // 28
        {521,450,       528,459,        "Serena's House",               0}, // 29
        {540,456,       564,474,        "Magic Maze",                   1}, // 30
        {512,465,       528,471,        "Steven's House",               0}, // 31
        {519,477,       527,484,        "Golden Armor Shop",            1}, // 32
        {537,434,       616,438,        "New Street",                   2}, // 33
        {559,442,       565,448,        "Gordon's House",               0}, // 34
        {571,442,       577,448,        "Nasir's House",                0}, // 35
        {582,442,       610,462,        "Templar Outlaws",              3}, // 36
        {614,434,       618,495,        "South End",                    2}, // 37
        {590,467,       610,488,        "Skeleton Lord",                3}, // 38
        {537,491,       613,495,        "Merchant's Way",               2}, // 39
        {593,498,       601,505,        "Ingrid's House",               0}, // 40
        {501,400,       526,432,        "Abandoned Kwai Clan Hall",     1}, // 41
        {500,558,       525,590,        "Abandoned Gorn Clan Hall",     1}, // 42
        {493,448,       519,476,        "Arena",                        1}, // 43
        {411,331,       478,394,        "Black Stronghold",             1}, // 44
        {561,410,       604,430,        "Dungeon of Doors",             1}, // 45
        {125,57,        197,131,        "Random Dungeon",               1}, // 46
        {411,460,       479,529,        "Mine, 1st Level",              1}, // 47
        {771, 20,       839, 89,        "Mine, 2nd Level",              1}, // 48
        {700, 20,       768, 89,        "Mine, 3rd Level",              1}, // 49
        { 52, 52,       105,104,        "Labyrinth, Grolm Gorge",       1}, // 50
        { 58,158,       154,212,        "Labyrinth, Lizard Gorge",      1}, // 51
        { 30,236,       151,307,        "Labyrinth, Spellcaster Gorge", 1}, // 52
        { 25,330,       110,375,        "Labyrinth, Knight Gorge",      1}, // 53
        { 16,385,       119,455,        "Labyrinth, Undead Gorge",      1}, // 54
        { 16,459,        56,487,        "Labyrinth, Undead Gorge",      1}, // 55
        { 16,489,        81,529,        "Labyrinth, Light&Dark Gorge",  1}, // 56
        { 16,529,        81,591,        "Labyrinth, Water Gorge",       1}, // 57
        { 16,593,        37,602,        "Labyrinth, Final Entry",       1}, // 58 
        { 16,602,        48,608,        "Labyrinth, Final Preparations",1}, // 59
        { 38,593,        48,602,        "Labyrinth, Final Test",        1}, // 60
        { 49,593,        80,608,        "Labyrinth, Final Reward",      1}, // 61
        { 15,611,       126,703,        "Labyrinth, Forest Gorge",      1}, // 62
        {112,703,       126,708,        "Labyrinth, Forest Gorge",      1}, // 63
        { 15,704,        66,724,        "Labyrinth, Riddle Gorge",      1}, // 64
        { 15,724,        48,804,        "Labyrinth, Riddle Gorge",      1}, // 65
        { 15,804,        37,812,        "Labyrinth, Riddle Gorge",      1}, // 66
        {210,300,       410,600,        "Pentagram Quest",              1}, // 67
        {330,246,       408,299,        "Ice Pentagram Quest",          1}, // 68
        {822,176,      1020,333,        "Underground II",               1}, // 69
        {792,796,       813,811,        "Elysium",                      1}, // 70
        {367,227,       410,244,        "Gargoyle's Nest",              1}, // 71
        {410,227,       480,329,        "Gargoyle's Nest",              1}, // 72
        {  1,  1,        20, 20,        "Aston",                        0}, // 73
	{622,466,       629,477,        "Astonian Inn",                 1}, // 74
	{630,466,       633,481,        "Astonian Inn",                 1}, // 75
	{ 61,122,        65,131,        "Astonian Inn",                 1}, // 76
	{ 53,118,        60,124,        "Astonian Inn",                 1}, // 77
	{ 36,106,        52,141,        "Astonian Inn",                 1}, // 78
	{ 29,137,        38,144,        "Astonian Inn",                 1}, // 79
	{578,566,       633,596,        "Memorial Park",                1}, // 80 
	{820,158,       851,161,        "Staffers Corner",              1}, // 81
	{807,151,       819,168,        "Staffers Corner",              1}, // 82
	{793,146,       805,156,        "Staffers Corner",              1}, // 83
	{799,158,       805,168,        "Staffers Corner",              1}, // 84
	{794,163,       798,165,        "Staffers Corner",              1}, // 85
	{632,240,       647,257,        "Tower I",                  1},     // 86 
	{822,337,       837,352,        "Tower II",                  1},    // 87
	{822,354,       837,367,        "Tower III",                  1},   // 88
	{822,369,       837,384,        "Tower IV",                  1},    // 89
	{822,386,       837,401,        "Tower V",                  1},     // 90
	{854,338,       870,353,        "Tower VI",                  1},    // 91
	{854,355,       870,368,        "Tower VII",                  1},   // 92
	{854,370,       870,384,        "Tower VIII",                  1},  // 93
	{854,386,       870,401,        "Tower IX",                  1},    // 94
	{854,403,       870,419,        "Tower X",                  1},     // 95
	{854,422,       870,437,        "Tower XI",                  1},    // 96
	{851,440,       869,459,        "Tower XII",                  1},   // 97
	{849,463,       866,478,        "Tower XIII",                  1},  // 98
	{848,479,       866,495,        "Tower XIV",                  1},   // 99
	{847,498,       863,522,        "Tower XV",                  1},    // 100
	{842,514,       846,522,        "Tower XV",                  1},    // 101
	{839,523,       863,545,        "Tower XVI",                  1},   // 102
	{839,546,       855,564,        "Tower XVI",                  1},   // 103
	{839,570,       858,590,        "Tower XVII",                  1},  // 104
	{839,594,       858,613,        "Tower XVIII",                  1}, // 105
	{839,616,       858,635,        "Tower XIX",                  1},   // 106
	{841,639,       855,657,        "Tower XX",                  1},    // 107
	{839,658,       857,683,        "Tower XX",                  1},    // 108
	{836,684,       860,694,        "Tower XX",                  1},    // 109
	{411,436,       476,456,        "Pentagram Quest",              1}, // 110 
	{597,600,       619,619,        "Aston Hall",              	0}, // 111
	{529,198,	537,204,        "Lizard Temple Shrine",         1}, // 112
	{321,294,	327,300,        "Ice Pents Shrine",         	1}, // 113
	{529,198,	537,204,        "Lizard Temple Shrine",         1}, // 114
        {577,597,	596,628,	"Aston Hall",			1}, // 115
	{597,620,	619,628,	"Aston Hall",			1}, // 116
	{620,597,	633,628,	"Aston Hall",			1}, // 117
	{597,597,	619,599,	"Aston Hall",			1}, // 118
	{836,151,	846,154,	"Underground I",		1}, // 119
	{479,360,	479,363,        "Black Stronghold",             1}, // 120
	{634,466,	639,477,	"Astonian Inn",			1}, // 121
	{532,406,	536,406,        "Aston",             		0}, // 122
        {469,457,	473,459,	"Pentagram Quest",		1}  // 123

};

int isInPentagramQuest( int cn )
{
  if ( cn < 1 || cn >= MAXCHARS )
    return 0;

  int n[ 5 ] = { 67, 68, 110, 113, 123 }; // Index of pentagram quest

  for ( int i = 0; i < 5; ++i )
  {
    if ( ch[ cn ].x >= area[ n[ i ] ].x1 && ch[ cn ].y >= area[ n[ i ] ].y1 && ch[ cn ].x <= area[ n[ i ] ].x2 &&
         ch[ cn ].y <= area[ n[ i ] ].y2 )
    {
      return 1;
    }
  }

  return 0;
}

// return a description of the area character cn is in
char *get_area(int cn,int verbose)
{
        int n,flag=0;
        static char buf[512];

        buf[0]=0;

        if (cn<1 || cn>=MAXCHARS) return buf;

        for (n=0; n<sizeof(area)/sizeof(area[0]); n++) {
                if (ch[cn].x>=area[n].x1 && ch[cn].y>=area[n].y1 &&
                    ch[cn].x<=area[n].x2 && ch[cn].y<=area[n].y2) {
                        if (verbose) {
                                if (!flag) {
                                        strcat(buf,"In "); flag=1;
                                } else strcat(buf,", in ");
                                if (area[n].flag==1) strcat(buf,"the ");
                                else if (area[n].flag==2) strcat(buf,"on ");
                                else if (area[n].flag==3) strcat(buf,"at ");
                                strcat(buf,area[n].name);
                        } else {
                                if (!flag) flag=1;
                                else strcat(buf,", ");
                                strcat(buf,area[n].name);
                        }
                }
        }

        return buf;
}

//return the area description for x,y
char *get_area_m(int x,int y,int verbose)
{
        int n,flag=0;
        static char buf[512];

        buf[0]=0;

        for (n=0; n<sizeof(area)/sizeof(area[0]); n++) {
                if (x>=area[n].x1 && y>=area[n].y1 &&
                    x<=area[n].x2 && y<=area[n].y2) {
                        if (verbose) {
                                if (!flag) {
                                        strcat(buf,"in "); flag=1;
                                } else strcat(buf,", in ");
                                if (area[n].flag==1) strcat(buf,"the ");
                                else if (area[n].flag==2) strcat(buf,"on ");
                                else if (area[n].flag==3) strcat(buf,"at ");
                                strcat(buf,area[n].name);
                        } else {
                                if (!flag) flag=1;
                                else strcat(buf,", ");
                                strcat(buf,area[n].name);
                        }
                }
        }

        return buf;
}
