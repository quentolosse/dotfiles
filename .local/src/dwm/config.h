/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 25;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Eww";    /* Alternate bar class name */
static const char *altbarcmd        = "echo tkt"; /* "eww open bar"; */ /* Alternate bar launch command */
static const int vertpad            = 15;       /* vertical padding of bar */
static const int sidepad            = 15;       /* horizontal padding of bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 15;        /* vertical padding for statusbar */
static const unsigned int colorfultitle  = 0;  /* 0 means title use SchemeTitle and SchemeTitleFloat */
static const unsigned int colorfultag    = 1;  /* 0 means use SchemeSel for selected tag */
static const unsigned int stairpx   = 20;       /* depth of the stairs layout */
static const int stairdirection     = 1;        /* 0: left-aligned, 1: right-aligned */
static const int stairsamesize      = 1;        /* 1 means shrink all the staired windows to the same size */
static const char *fonts[] = {
        "JetBrains Mono:pixelsize=12:style=bold",
        "JetBrainsMono NFM:style=Regular:pixelsize=24",
};
// static char *fonts[]          = { "monospace:size=10", "JetBrainsMono NFM:style=Regular:pixelsize=10:antialias=true:autohint=true"  };
static const char dmenufont[]       = "monospace:size=10";
static unsigned int baralpha        = 0xd0;
static unsigned int borderalpha     = OPAQUE;

static char col_bg[]          = "#222222";
static char col_fg[]          = "#444444";
static char col_border[]      = "#666666";

static char col_tag[]    = "#BD93F9";

static char col_black[]       = "#2a303c";
static char col_gray3[]       = "#606672";
static char col_green[]       = "#50FA7B";  // layout indicator

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
               { "background",         STRING,  &col_bg },
               { "foreground",         STRING,  &col_fg },
               { "border",	       STRING,  &col_border },
		// TODO : autres couleurs pour tags 
};


static char *colors[][3]      = {
	/*               fg           bg         border   */
	[SchemeNorm]   = { col_fg,     col_bg, 	  col_bg },
	[SchemeSel]    = { col_fg,     col_border,col_border },
	[SchemeTag]    = { col_gray3,  col_black, col_black },
    	[SchemeTag1]   = { col_tag,    col_black, col_black },
    	[SchemeTag2]   = { col_tag,    col_black, col_black },
    	[SchemeTag3]   = { col_tag,    col_black, col_black },
    	[SchemeTag4]   = { col_tag,    col_black, col_black },
    	[SchemeTag5]   = { col_tag,    col_black, col_black },
	[SchemeTag6]   = { col_tag,    col_black, col_black },
	[SchemeLayout] = { col_green,  col_black, col_black },
};

static const char *const autostart[] = {
//	"st", NULL,
//	"dwm-suscribe > /tmp/dwm.log &", NULL,
	NULL /* terminate */
};

/* tagging */
static char *tags[] = {"", "", "󰙯", "", "󰊴", "󰑊"};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const int tagschemes[] = { SchemeTag1, SchemeTag2, SchemeTag3,
                                  SchemeTag4, SchemeTag5, SchemeTag6 };

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	     instance    title    tags mask     isfloating   CenterThisWindow?     monitor */
//	{ "st",              NULL,       NULL,    0,            0,     	     1,		           -1 },
	{ "Gimp",            NULL,       NULL,    0,            1,           0,                    -1 },
	{ "Firefox",         NULL,       NULL,    1 << 3,       0,           0,                    -1 },
	{ "dash", 	     NULL,       NULL,    0,            1,           0,                     0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
        { "III",      horizontal },
	{ "[S]",      stairs },
        { "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "st", NULL };
static const char *dmenucmd[] = {"", NULL};
static const char *layoutmenu_cmd = "layoutmenu.sh";
static const char scratchpadname[] = "Terminal";
static const char *scratchtermcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
//	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,     	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return, togglescratch,  {.v = scratchtermcmd} },
//	{ MODKEY,                       XK_twosuperior,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_comma,  setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_semicolon,setmfact,       {.f = +0.05} },
//	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,	                XK_h,      movestack,      {.i = +1 } },
	{ MODKEY,	                XK_l,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_space , zoom,           {0} },
//	{ MODKEY,                       XK_q,	   view,           {0} },
	{ MODKEY, 		        XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_KP_End,        setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_KP_Down,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_KP_Page_Down,  setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_KP_Left,       setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_KP_Begin,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_KP_Right,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,	                XK_KP_Home,       setlayout,      {.v = &layouts[6]} },
	{ MODKEY,	                XK_KP_Up,         setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_KP_Page_Up,    setlayout,      {.v = &layouts[8]} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
//	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
//	{ MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
//	{ MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_j,  	   focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,	   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,	   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h, 	   tagmon,         {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_h,      layoutscroll,   {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_l,      layoutscroll,   {.i = +1 } },
//	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
//	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,			XK_BackSpace,	spawn,	   {.v = (const char*[]){ "rofi", "-show", "pwm", NULL } } },
	{ MODKEY,	                XK_f,      spawn,	   {.v = (const char*[]){ "rofi", "-show", NULL } } },
        { MODKEY,                       XK_d,      spawn,          {.v = (const char*[]){ "rofi", "-show", "drun", NULL } } },	
	{ MODKEY ^ MODKEY,              XK_Print,  spawn,          {.v = (const char*[]){ "flameshot", "gui", NULL} } }, 
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
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,	        {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,	        {0} },
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
