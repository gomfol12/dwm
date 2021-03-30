/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static int gappx     = 2;                 /* gaps between windows */
static unsigned int snap      = 16;       /* snap pixel */
static unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static unsigned int systrayspacing = 2;   /* systray spacing */
static int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static int showsystray        = 1;     /* 0 means no systray */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static int focusonwheel       = 0;
static char font-1[]            = "monospace:size=10";
static char font-2[]            = "";
static char font-3[]            = "";
static const char *fonts[]          = { font-1, font-2, font-3 };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* staticstatus */
static int statmonval = 0;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static char tagsalt-1[] = { "1" };
static char tagsalt-2[] = { "2" };
static char tagsalt-3[] = { "3" };
static char tagsalt-4[] = { "4" };
static char tagsalt-5[] = { "5" };
static char tagsalt-6[] = { "6" };
static char tagsalt-7[] = { "7" };
static char tagsalt-8[] = { "8" };
static char tagsalt-9[] = { "9" };
static const char *tagsalt[] = { tagsalt-1, tagsalt-2, tagsalt-3, tagsalt-4, tagsalt-5, tagsalt-6, tagsalt-7, tagsalt-8, tagsalt-9 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating canfocus   monitor */
	{ "stalonetray", NULL,    NULL,       0,            1,         0,         -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int decorhints  = 1;    /* 1 means respect decoration hints */

#include "fibonacci.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",     dwindle },	/* first entry is default */
 	{ "[@]",      spiral },
	{ "[]=",      tile },    	
	{ "[M]",      monocle },
	{ "###",	  gaplessgrid },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font-1",             STRING,  &font-1 },
		{ "font-2",             STRING,  &font-2 },
		{ "font-3",             STRING,  &font-3 },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "gappx",          	INTEGER, &gappx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "user_bh",          	INTEGER, &user_bh },
		{ "focusonwheel",       INTEGER, &focusonwheel },
		{ "statmonval",			INTEGER, &statmonval },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "decorhints",       	INTEGER, &decorhints},
		{ "mfact",      	 	FLOAT,   &mfact },
		{ "systraypinning"		INTEGER, &systraypinning },
		{ "systrayonleft"		INTEGER, &systrayonleft},
		{ "systrayspacing"		INTEGER, &systrayspacing},
		{ "systraypinningfailfirst" INTEGER, &systraypinningfailfirst},
		{ "showsystray"			INTEGER, &showsystray},
		{ "tagsalt-1"			STRING, &tagsalt-1},
		{ "tagsalt-2"			STRING, &tagsalt-2},
		{ "tagsalt-3"			STRING, &tagsalt-3},
		{ "tagsalt-4"			STRING, &tagsalt-4},
		{ "tagsalt-5"			STRING, &tagsalt-5},
		{ "tagsalt-6"			STRING, &tagsalt-6},
		{ "tagsalt-7"			STRING, &tagsalt-7},
		{ "tagsalt-8"			STRING, &tagsalt-8},
		{ "tagsalt-9"			STRING, &tagsalt-9},
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_t,      spawn,      SHCMD("st") },
	{ MODKEY,                       XK_y,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,						XK_g,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_b,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,						XK_o,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,						XK_f,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_w,	   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_e,	   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_w,	   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_e,	   tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_a,      togglealttag,   {0} },
	{ MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
	{ MODKEY|ControlMask,           XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -2 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +2 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 2  } },
	{ MODKEY,                       XK_n,	   switchcol,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_z,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
