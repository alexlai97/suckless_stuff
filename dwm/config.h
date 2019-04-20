/* See LICENSE file for copyright and license details. */

/* appearance */
// static const char selbordercolor[]  = "#005577";
// static const char selbgcolor[]      = "#005577";
// static const char selfgcolor[]      = "#eeeeee";
// static const char urgbordercolor[]  = "#ff0000";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=13" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

#include "./colors.h"
//static const char *colors[][3]      = {
//	/*               fg         bg         border   */
//	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
//};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title       tags mask     isfloating   monitor */
	{ "Oblogout",  NULL,       NULL,       0,            1,           -1 },
  { "Sublime",   NULL,       NULL,       1 << 1,       1,           -1 },
  { "st",        NULL,     "ranger",     1 << 2,       1,           -1 },
  { "Thunar",    NULL,       NULL,       1 << 2,       1,           -1 },
  //{ "tabbed",    NULL,       "zathura",  1 << 2,       0,           -1 }, // FIXME
  { "Zathura",   NULL,       NULL,       1 << 2,       0,           -1 }, 
	{ "Firefox",   NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Chromium",  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "tor",       NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Vimb",      NULL,       NULL,       1 << 3,       0,           -1 },
	//{ "tabbed",   "surf",      NULL,       1 << 3,       0,           -1 }, //FIXME
	{ "mpv",       NULL,       NULL,       1 << 4,       1,           -1 },
	//{ "st ",       NULL,    "ncmpcpp",     1 << 4,       1,           -1 }, //FIXME
	{ "Signal",    NULL,       NULL,       1 << 5,       0,           -1 },
	{ "weixin",    NULL,       NULL,       1 << 5,       0,           -1 },
	{ "kingsforum",NULL,       NULL,       1 << 5,       0,           -1 },
	{ "messenger", NULL,       NULL,       1 << 5,       0,           -1 },
  { "habitica",  NULL,       NULL,       1 << 6,       1,           -1 },
  { "Citra",  NULL,       NULL,       1 << 6,       1,           -1 },
  { "Fluorine",  NULL,       NULL,       1 << 6,       1,           -1 },
  { "Technic",  NULL,       NULL,       1 << 6,       1,           -1 },
  { "Minecraft",  NULL,       NULL,       1 << 6,       1,           -1 },
	{ "VirtualBox",NULL,       NULL,       1 << 7,       0,           -1 },
	{ "Zim",       NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */

	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *rofiruncmd[] = { "/home/alex/.scripts/zsh_rofi","-show","run", NULL };
static const char *extendedrofiruncmd[] = { "/home/alex/.scripts/dmenu_extended_run", NULL };
static const char *timercmd[] = { "/home/alex/.scripts/timer" , NULL };
static const char *dmenuextendedruncmd[] = { "/home/alex/.scripts/dmenu_extended_run", NULL };
static const char *termcmd[]  = { "/home/alex/bin/st", NULL };
static const char *runfirefoxcmd[]  = { "/home/alex/.scripts/firefox", NULL };
static const char *runthunarcmd[]  = { "thunar", NULL };
//static const char *runzimcmd[]  = { "zim", NULL };
static const char *runzathuracmd[]  = { "/home/alex/bin/tabbed", "-c","zathura","-e", NULL };
static const char *runvimbcmd[]  = { "/home/alex/bin/tabbed","-c","vimb","-e", NULL };
static const char *runsurfcmd[]  = { "surf-open.sh", NULL };
static const char *termtmuxcmd[]  = { "/home/alex/bin/st", "-e", "tmux", NULL };
static const char *termhtopcmd[]  = { "/home/alex/bin/st", "-e", /* "set_color_with", */ "htop", NULL };
static const char *termrangercmd[]  = { "/home/alex/bin/st", "-e", /* "set_color_with", */ "ranger", NULL };
static const char *termncmpcppcmd[]  = { "/home/alex/bin/st", "-e", /* "set_color_with", */ "ncmpcpp", NULL };
static const char *keyboardledoncmd[]  = { "xset","led","3", NULL };
static const char *keyboardledoffcmd[] = { "xset","-led","3", NULL };
static const char *runoblogoutcmd[] = { "oblogout", NULL}; 
static const char *touchpadtoggle[] = { "toggletouchpad.sh", NULL};
static const char *audioraisevolume[] = { "pactl","set-sink-volume","0","+5%", NULL};
static const char *audiolowervolume[] = { "pactl","set-sink-volume","0","-5%", NULL};
static const char *audiomute[] = { "pactl","set-sink-mute","0","toggle", NULL};
static const char *monbrightnessup[] = { "xbacklight","-inc","5", NULL};
static const char *monbrightnessdown[] = { "xbacklight","-dec","5", NULL};
static const char *audiotoggleplaypause[] = { "mpc", "toggle", NULL};
static const char *audiostop[] = { "mpc", "stop", NULL};
static const char *audionext[] = { "mpc", "next", NULL};
static const char *audioprev[] = { "mpc", "prev", NULL};
static const char *screenshotcmd[] = { "/home/alex/.scripts/screenshot.sh", NULL };
static const char *runscreenshotrootcmd[] = { "/home/alex/.scripts/screenshot.sh", "root", NULL };
static const char *runscreenshotwindowcmd[] = { "/home/alex/.scripts/screenshot.sh", "window", NULL };
static const char *rundynamicwallpapercmd[] = { "/home/alex/.scripts/dynamicwallpaper", NULL };
static const char *runshowweathercmd[] = { "/home/alex/.scripts/weather", "show", NULL };
static const char *runrightclickemenu[] = { "/home/alex/.scripts/rightclickmenu", NULL };
/* static const char *runkillwindowcmd[] = { "xkill", NULL }; does not work */
/* static const char *runsimplelockcmd[] = { "slock", NULL }; */



static Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY|ShiftMask,             XK_Page_Down,spawn,        {.v = runoblogoutcmd} },
  { MODKEY|Mod1Mask,              XK_h,      spawn,          {.v = termhtopcmd} },
  { MODKEY|Mod1Mask,              XK_r,      spawn,          {.v = termrangercmd} },
  { MODKEY|Mod1Mask,              XK_n,      spawn,          {.v = termncmpcppcmd} },
  { MODKEY|Mod1Mask,              XK_t,      spawn,          {.v = runthunarcmd} },
  { MODKEY|Mod1Mask,              XK_f,      spawn,          {.v = runfirefoxcmd} },
	{ MODKEY|Mod1Mask,              XK_z,      spawn,          {.v = runzathuracmd} },
	{ MODKEY|Mod1Mask,              XK_v,      spawn,          {.v = runvimbcmd} },
	{ MODKEY|Mod1Mask,              XK_s,      spawn,          {.v = runsurfcmd} },
	//{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd} },
	{ MODKEY,                       XK_d,      spawn,          {.v = rofiruncmd} },
  { MODKEY,                       XK_w,      spawn,          {.v = dmenuextendedruncmd} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termtmuxcmd } },
	{ 0,                            XK_Scroll_Lock, spawn,     {.v = keyboardledoncmd } },
	{ ShiftMask,                    XK_Scroll_Lock, spawn,     {.v = keyboardledoffcmd } },
  // 'xmodmap -pk' can search keysyms
  { 0,                            0x1008ffa9,spawn,          {.v = touchpadtoggle } },
  { 0,                            0x1008ff13,spawn,          {.v = audioraisevolume } },
  { 0,                            0x1008ff12,spawn,          {.v = audiomute } },
  { 0,                            0x1008ff11,spawn,          {.v = audiolowervolume } },
  { 0,                            0x1008ff02,spawn,          {.v = monbrightnessup } },
  { 0,                            0x1008ff03,spawn,          {.v = monbrightnessdown } },
  { 0,                            0x1008ff14,spawn,          {.v = audiotoggleplaypause } },
  { 0,                            0x1008ff15,spawn,          {.v = audiostop } },
  { 0,                            0x1008ff16,spawn,          {.v = audioprev } },
  { 0,                            0x1008ff17,spawn,          {.v = audionext } },
  { 0,       /* power off button */0x1008ff2a,spawn,          {.v = runoblogoutcmd } },
  { ShiftMask,                    XK_Print,  spawn,           {.v = runscreenshotrootcmd } },
  { 0,                            XK_Print,  spawn,           {.v = runscreenshotwindowcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_c,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Escape,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button2,        spawn,          {.v = screenshotcmd } },
	{ ClkWinTitle,          Mod1Mask,       Button2,        spawn,          {.v = rundynamicwallpapercmd } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = extendedrofiruncmd } },
	/* { ClkStatusText,        MODKEY,         Button2,        spawn,         {.v = runkillwindowcmd } }, */
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = runoblogoutcmd } },
	/* { ClkStatusText,        MODKEY,         Button3,        spawn,         {.v = runsimplelockcmd } }, */
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = runrightclickemenu } },
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          {.v = runshowweathercmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        spawn,          { .v = termcmd } },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


