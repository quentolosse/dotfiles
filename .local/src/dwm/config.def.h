/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  	    = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static unsigned int snap      	    = 32;       /* snap pixel */
static int showbar   	 	    = 1;        /* 0 means no bar */
static int topbar	            = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 1;        /* 1 means shrink all the staired windows to the same size */
static char *fonts[]	            = { "monospace:size=10" };
static char dmenufont[]             = "monospace:size=10";
static unsigned int baralpha        = 0xd0;
static unsigned int borderalpha     = OPAQUE;
static char col_gray1[]       = "#222222";
static char col_gray2[]       = "#444444";
static char col_gray3[]       = "#bbbbbb";
static char col_gray4[]       = "#eeeeee";
static char col_cyan[]        = "#005577";
static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	"st", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	     instance    title    tags mask     isfloating   CenterThisWindow?     monitor */
	{ "st",              NULL,       NULL,    0,            0,     	     1,		           -1 },
	{ "Gimp",            NULL,       NULL,    0,            1,           0,                    -1 },
	{ "Firefox",         NULL,       NULL,    1 << 8,       0,           0,                    -1 },
};

/* layout(s) */
static float mfact     = 0.55;       /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;          /* number of clients in master area */
static int resizehints = 1;          /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
        { "III",      horizontal },
	{ "[S]",      stairs },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
               { "font",               STRING,  &font },
               { "dmenufont",          STRING,  &dmenufont },
               { "normbgcolor",        STRING,  &normbgcolor },
               { "normbordercolor",    STRING,  &normbordercolor },
               { "normfgcolor",        STRING,  &normfgcolor },
               { "selbgcolor",         STRING,  &selbgcolor },
               { "selbordercolor",     STRING,  &selbordercolor },
               { "selfgcolor",         STRING,  &selfgcolor },
               { "borderpx",           INTEGER, &borderpx },
               { "snap",                       INTEGER, &snap },
               { "showbar",            INTEGER, &showbar },
               { "topbar",             INTEGER, &topbar },
               { "nmaster",            INTEGER, &nmaster },
               { "resizehints",        INTEGER, &resizehints },
               { "mfact",                      FLOAT,   &mfact },
};



#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_q,	   view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,	                XK_z,      setlayout,      {.v = &layouts[7]} },
        { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      layoutscroll,   {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      layoutscroll,   {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_minus,                  5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_underscore,             7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

