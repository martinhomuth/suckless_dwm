/* See LICENSE file for copyright and license details. */

#define INHIBIT_COLOR_FONTS 0

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating
						   windows by default */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows
						   selected monitor, >0: pin
						   systray to monitor X */
static const unsigned int systrayspacing = 7;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display
						   systray on the first monitor,
						   False: display systray on the
						   last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when
						   there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"monospace:size=10", "Hack:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true",
};
static const char dmenufont[]       = "monospace:size=10";
static const char normbgcolor[]           = "#282828";
static const char normbordercolor[]       = "#504945";
static const char normfgcolor[]           = "#ebdbb2";
static const char selfgcolor[]            = "#282828";
static const char selbordercolor[]        = "#d79921";
static const char selbgcolor[]            = "#d79921";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags-mask     isfloating isterminal
       noswallow monitor */
    {"Gimp", NULL, NULL, 0, 1, 0, 0, -1},
    {"Firefox", NULL, NULL, 1, 0, 0, -1, -1},
    {"qutebrowser", NULL, NULL, 1, 0, 0, -1, -1},
    {"KeePassXC", NULL, NULL, 0, 1, 0, 0, -1},
    {NULL, NULL, "Android Emulator - Pixel_3a_API_30:5554", 0, 1, 0, 0, -1},
    {NULL, NULL, "Welcome to Android Studio", 0, 1, 0, 0, -1},
    {NULL, NULL, "Android Studio Setup Wizard", 0, 1, 0, 0, -1},
    {NULL, "seafile-applet", NULL, 0, 1, 0, 0, -1},
    {NULL, NULL, "Authentication required", 0, 1, 0, 0, -1},
    {NULL, NULL, "Unlock Keyring", 0, 1, 0, 0, -1},
    {NULL, NULL, "calendar-edit:", 0, 1, 0, 0, -1},
    {"St", NULL, NULL, 0, 0, 1, 0, -1},
    {"xterm-256color", NULL, NULL, 0, 0, 1, 1, -1},
    {"xterm", NULL, NULL, 0, 0, 1, 1, -1},
    {NULL, "xterm", NULL, 0, 0, 1, 1, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1},
    {NULL, NULL, "Android Virtual Device Manager", 0, 1, 0, 0, -1},
    {NULL, NULL, "eGroupWare [Kalender - Hinzufügen] - Mozilla Firefox", 0, 1,
     0, 0, -1},
    {NULL, "Msgcompose", NULL, 0, 1, 0, 0, -1},
    {"Steam", NULL, NULL, 0, 0, 0, 1, -1},
    {"Calendar", NULL, NULL, 0, 1, 0, 0, -1},
    {"Pavucontrol", NULL, NULL, 0, 1, 0, 0, -1},
    {"Spotify", NULL, NULL, 16, 0, 0, 0, 1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "horizgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "###",      horizgrid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[] = { "qutebrowser", NULL };
static const char *explorercmd[] = { "thunar", NULL };
static const char scratchpadname[] = "emacs-scratchpad";
static const char *scratchpadcmd[] = { "emacs", "-T", scratchpadname, NULL };
static const char *vpnmenucmd[] = { "vpnmenu", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function          argument */
	{ MODKEY,                       XK_d,      spawn,            {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,            {.v = termcmd } },
	{ MODKEY,                       XK_o,      togglescratch,    {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      spawn,            {.v = browsercmd } },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_h,      setmfact,         {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,         {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,         {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,         {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,         {.f =  0.00} },
	{ MODKEY,                       XK_p,      incnmaster,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_p,      incnmaster,       {.i = -1 } },
	{ MODKEY,                       XK_f,      togglefullscr,    {0} },
	{ MODKEY,                       XK_Return, zoom,             {0} },
	{ MODKEY,                       XK_Tab,    view,             {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,       {0} },
	{ MODKEY,                       XK_F1,     setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                       XK_F2,     setlayout,        {.v = &layouts[1]} },
	{ MODKEY,                       XK_F3,     setlayout,        {.v = &layouts[2]} },
	{ MODKEY,                       XK_F4,     setlayout,        {.v = &layouts[3]} },
	{ MODKEY,                       XK_F5,     setlayout,        {.v = &layouts[4]} },
	{ MODKEY,                       XK_F6,     setlayout,        {.v = &layouts[5]} },
	{ MODKEY,                       XK_F7,     setlayout,        {.v = &layouts[6]} },
	{ MODKEY,                       XK_F8,     setlayout,        {.v = &layouts[7]} },
	{ MODKEY,                       XK_space,  setlayout,        {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,   {0} },
	{ MODKEY,                       XK_0,      view,             {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,              {.ui = ~0 } },
	{ MODKEY,                       XK_q,      focusmon,         {.i = -1 } },
	{ MODKEY,                       XK_w,      focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,           {.i = +1 } },
	{ MODKEY,                       XK_e,      spawn,            {.v = explorercmd } },
	TAGKEYS(                        XK_1,                        0)
	TAGKEYS(                        XK_2,                        1)
	TAGKEYS(                        XK_3,                        2)
	TAGKEYS(                        XK_4,                        3)
	TAGKEYS(                        XK_5,                        4)
	TAGKEYS(                        XK_6,                        5)
	TAGKEYS(                        XK_7,                        6)
	TAGKEYS(                        XK_8,                        7)
	TAGKEYS(                        XK_9,                        8)
        { MODKEY|ShiftMask,             XK_r,      self_restart,     {0} },
	{ MODKEY|ControlMask,           XK_q,      quit,             {0} },
	{ MODKEY,                       XK_v,      spawn,            {.v = vpnmenucmd } },
	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
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
