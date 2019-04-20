static const char norm_fg[] = "#c7c7c6";
static const char norm_bg[] = "#221f1e";
static const char norm_border[] = "#4980ba";

static const char sel_fg[] = "#8ea8b7";
static const char sel_bg[] = "#bbb9b5";
static const char sel_border[] = "#fffffe";

static const char urg_fg[] = "#221f1e";
static const char urg_bg[] = "#fffffe";
static const char urg_border[] = "#f4c6b1";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
