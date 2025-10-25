
#ifdef __SWITCH__

#include <switch.h>
#include <unistd.h>
#include <cstdio>
#include <SDL.h>

static int s_nxlinkSock = -1;

static void nxlinkInit() {
	if (R_FAILED(socketInitializeDefault()))
		return;

	s_nxlinkSock = nxlinkStdio();
	if (s_nxlinkSock >= 0)
		printf("nxlink activated...\n");
	else
		socketExit();
}

static void nxlinkExit() {
	if (s_nxlinkSock >= 0) {
		close(s_nxlinkSock);
		socketExit();
		s_nxlinkSock = -1;
	}
}

extern "C" void userAppInit() {
	nxlinkInit();
	romfsInit();

	SDL_SetHint(SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS, "1");
}

extern "C" void userAppExit() {
	romfsExit();
	nxlinkExit();
}

#endif
