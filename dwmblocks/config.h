//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"🎼 ",	"sb-music",			10,				10},
	{"🤖 ",	"sb-tasks",			10,				10},
	{"",	"sb-mailbox",			10,				12},
	{"",	"sb-torrent",			10,				11},
	{"",	"volume",			10,				10},
	{"🕒 ", "date '+%H:%M %p %a %d %b %Y'",					5,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;

