/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 5;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 0;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Source Code Pro Medium:size=12", "Iosevka Nerd Font:size=12" };
static const char dmenufont[]       = "Source Code Pro Medium:size=12";

/* colorscheme */
static const char norm_fg[] = "#d2e9f0";
static const char norm_bg[] = "#0b0d0a";
static const char norm_border[] = "#93a3a8";

static const char sel_fg[] = "#d2e9f0";
static const char sel_bg[] = "#9D9A5D";
static const char sel_border[] = "#d2e9f0";

/* default colors */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg, norm_bg, norm_border },
	[SchemeSel]  = { sel_fg, sel_bg,  sel_border  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "漣" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Alacritty",  NULL,       NULL,       1,            0,           -1 },
    { "Viewnior",   NULL,       NULL,       1,            1,           -1 },
	{ "firefox",    NULL,       NULL,       2,            0,           -1 },
    { "discord",    NULL,       NULL,       2,            0,           -1 },
    { "Thunar",     NULL,       NULL,       1 << 2,       0,           -1 },
    { "Pcmanfm",    NULL,       NULL,       1 << 2,       0,           -1 },
    { "Geany",      NULL,       NULL,       1 << 3,       0,           -1 },
    { "Code",       NULL,       NULL,       1 << 3,       0,           -1 },
    { "Gimp-2.10",  NULL,       NULL,       1 << 4,       0,           -1 },
    { "kdenlive",   NULL,       NULL,       1 << 4,       0,           -1 },
    { "Spotify",    NULL,       NULL,       1 << 5,       0,           -1 },
    { "Lxappearance",           NULL,       NULL,         1 << 6,       0            -1 },
    { "Xfce4-settings-manager", NULL,       NULL,         1 << 6,       0,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "10", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", "#0b0d0a", "-nf", "#d2e9f0", "-sb", "#93a3a8", "-sf", "#d2e9f0", "-p", "Run Command:", NULL };
static const char *j4dmenu[]  = { "j4-dmenu-desktop", "--no-generic", "--term='alacritty'", "--dmenu=dmenu -p 'Run App:' -c -i -l 10 -nb '#0b0d0a' -nf '#d2e9f0' -sb '#93a3a8' -sf '#d2e9f0' -fn 'Source Code Pro Medium:size=12'", NULL };
static const char *termcmd[]  = { "alacritty", "--config-file=/home/kungger/.dwm/alacritty/alacritty.yml", "-e", "fish", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *lockscreen[] = { "./.dwm/scripts/lock", NULL };
static const char *editconfigs[] = { "./.dwm/scripts/dmedit-configs", NULL };
static const char *quicklinks[] = { "./.dwm/scripts/dmquick-links", NULL };
static const char *rangercmd[] = { "alacritty", "-e", "ranger", NULL };
static const char *thunarcmd[] = { "thunar", NULL };

/* volume controls */
static const char *upvol[]   = { "volume-up", NULL };
static const char *downvol[] = { "volume-down", NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
    { 0,                            XF86XK_AudioMute, spawn, {.v = mutevol } },
  /*{ MODKEY,                       XK_equal, spawn, {.v = upvol } },
    { MODKEY,                       XK_minus, spawn, {.v = downvol } },
    { MODKEY,                       XK_0, spawn, {.v = mutevol } }, */
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = thunarcmd } },
    { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = rangercmd } },
    { ALTKEY,                       XK_l,      spawn,          {.v = quicklinks } },
    { ALTKEY,                       XK_e,      spawn,          {.v = editconfigs } },
    { ControlMask|ALTKEY,           XK_l,      spawn,          {.v = lockscreen } },
    { ALTKEY,                       XK_F1,     spawn,          {.v = j4dmenu } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  /*{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  /*{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } }, */ 
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
  /*TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)*/
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

