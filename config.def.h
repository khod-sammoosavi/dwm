/* See LICENSE file for copyright and license details. */

/* appearance */
static const char buttonbar[]         = "󰣇";
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const int user_bh              = 35;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const unsigned int baralpha    = 130;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int gappx       = 8;        /* gaps between windows */
static const unsigned int borderpx    = 1;        /* border pixel of windows */
static const unsigned int snap        = 32;       /* snap pixel */

static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* fonts */
static const char monospace[]       = "Source Code Pro:size=11.5:style=Medium:autohint=true";
static const char nerdfont[]        = "SymbolsNerdFont-Regular:size=11.5:style=Medium:autohint=true";
static const char persian_arabic_font[]        = "Vazirmatn:size=11.5:style=Medium:autohint=true";
static const char *fonts[]          = { monospace ,persian_arabic_font , nerdfont };

/* theme */
static const char black[]       = "#000000";
static const char white[]       = "#ffffff";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { white,     black,     black },
	[SchemeSel]  = { white,     black,     white },
};

/* tagging */
static const char *tags[] = { "dev", "web", "sys", "doc", "chat", "media" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	{  "Gromit-mpx",      NULL,       NULL,       0,            1,           0 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
#include "movestack.c"
#include "layouts.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[B]",      bstack },
	{ ">B>",      bstackhoriz },
	{ "[C]",      centeredmaster },
	{ ">C>",      centeredfloatingmaster },
	{ "[D]",      deck },
 	{ "[F]",      spiral },
 	{ ">F>",      dwindle },
	{ "[G]",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *spotdark[] = { "rofi", "-show", "drun", "-theme", "/usr/share/dwm/launcher/spotdark.rasi", NULL };
static const char *power[]    = { "sh", "/usr/share/dwm/power/power.sh", NULL };
static const char *upvol[]    = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",     NULL };
static const char *downvol[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",     NULL };
 
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = spotdark } },
	{ MODKEY,                       XK_x,      spawn,          {.v = power } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ ALTKEY,                       XK_Down,   spawn, 	       {.v = downvol } },
	{ ALTKEY,                       XK_Up,     spawn,      	   {.v = upvol   } },
	{ MODKEY|ShiftMask,             XK_t,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_h,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      focusstack,     {.f = +1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.f = -1 } },
	{ MODKEY|ShiftMask,             XK_s,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_v,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,           		        XK_Up,     setcfact,       {.f = +0.25} },
	{ MODKEY,  	                    XK_Down,   setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_b,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[6]} },
  { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[10]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} }, // refresh or reload dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,		        0,	          	Button1,      	spawn,		      {.v = spotdark } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

