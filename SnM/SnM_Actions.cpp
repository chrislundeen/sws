/******************************************************************************
/ SnM_Actions.cpp
/
/ Copyright (c) 2009-2010 Tim Payne (SWS), JF B�dague
/ http://www.standingwaterstudios.com/reaper
/
/ Permission is hereby granted, free of charge, to any person obtaining a copy
/ of this software and associated documentation files (the "Software"), to deal
/ in the Software without restriction, including without limitation the rights to
/ use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
/ of the Software, and to permit persons to whom the Software is furnished to
/ do so, subject to the following conditions:
/ 
/ The above copyright notice and this permission notice shall be included in all
/ copies or substantial portions of the Software.
/ 
/ THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
/ EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
/ OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
/ NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
/ HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/ WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/ FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
/ OTHER DEALINGS IN THE SOFTWARE.
/
******************************************************************************/

#include "stdafx.h"
#include "SnM_Actions.h"

static COMMAND_T g_commandTable[] = 
{
	// be carefull!!!! 
	// S&M functions expect "SWS/S&M: " in their titles (removed from undo messages, too long)

	// Sends, receives & cue buss ----------------------------------------------
	{ { DEFACCEL, "SWS/S&M: Create cue buss track from track selection, Pre-Fader (Post-FX)" }, "S&M_SENDS1", cueTrack, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Create cue buss track from track selection, Post-Fader (Post-Pan)" }, "S&M_SENDS2", cueTrack, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Create cue buss track from track selection, Pre-FX" }, "S&M_SENDS3", cueTrack, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Open cue buss window" }, "S&M_SENDS4", cueTrackPrompt, NULL, },
	{ { DEFACCEL, "SWS/S&M: Create cue buss track from track selection" }, "S&M_CUEBUS", cueTrack, NULL, -1},

	{ { DEFACCEL, "SWS/S&M: Remove receives from selected track(s)" }, "S&M_SENDS5", removeReceives, NULL, },
	{ { DEFACCEL, "SWS/S&M: Remove sends from selected track(s)" }, "S&M_SENDS6", removeSends, NULL, },
	{ { DEFACCEL, "SWS/S&M: Remove routing from selected track(s)" }, "S&M_SENDS7", removeRouting, NULL, },

	{ { DEFACCEL, "SWS/S&M: Copy tracks (with routing)" }, "S&M_COPYSNDRCV1", copyWithIOs, NULL, },
	{ { DEFACCEL, "SWS/S&M: Paste items or tracks with routing" }, "S&M_PASTSNDRCV1", pasteWithIOs, NULL, },
	{ { DEFACCEL, "SWS/S&M: Cut tracks (with routing)" }, "S&M_CUTSNDRCV1", cutWithIOs, NULL, },

	{ { DEFACCEL, "SWS/S&M: Copy selected track(s) routings" }, "S&M_COPYSNDRCV2", copyRoutings, NULL, },
	{ { DEFACCEL, "SWS/S&M: Paste routings to selected track(s)" }, "S&M_PASTSNDRCV2", pasteRoutings, NULL, },
	{ { DEFACCEL, "SWS/S&M: Cut selected track(s) routings" }, "S&M_CUTSNDRCV2", cutRoutings, NULL, },

	{ { DEFACCEL, "SWS/S&M: Copy selected track(s) sends" }, "S&M_COPYSNDRCV3", copySends, NULL, },
	{ { DEFACCEL, "SWS/S&M: Paste sends to selected track(s)" }, "S&M_PASTSNDRCV3", pasteSends, NULL, },
	{ { DEFACCEL, "SWS/S&M: Cut selected track(s) sends" }, "S&M_CUTSNDRCV3", cutSends, NULL, },

	{ { DEFACCEL, "SWS/S&M: Copy selected track(s) receives" }, "S&M_COPYSNDRCV4", copyReceives, NULL, },
	{ { DEFACCEL, "SWS/S&M: Paste receives to selected track(s)" }, "S&M_PASTSNDRCV4", pasteReceives, NULL, },
	{ { DEFACCEL, "SWS/S&M: Cut selected track(s) receives" }, "S&M_CUTSNDRCV4", cutReceives, NULL, },


	// Windows ----------------------------------------------------------------
#ifdef _WIN32
	{ { DEFACCEL, "SWS/S&M: Close all routing window(s)" }, "S&M_WNCLS1", closeAllRoutingWindows, NULL, },
	{ { DEFACCEL, "SWS/S&M: Close all envelope window(s)" }, "S&M_WNCLS2", closeAllEnvWindows, NULL, },
	{ { DEFACCEL, "SWS/S&M: Toggle show all routing window(s)" }, "S&M_WNTGL1", toggleAllRoutingWindows, NULL, },
	{ { DEFACCEL, "SWS/S&M: Toggle show all envelope window(s)" }, "S&M_WNTGL2", toggleAllEnvWindows, NULL, },
#endif
	{ { DEFACCEL, "SWS/S&M: Close all floating FX windows" }, "S&M_WNCLS3", closeAllFXWindows, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Close all FX chain windows" }, "S&M_WNCLS4", closeAllFXChainsWindows, NULL, },
	{ { DEFACCEL, "SWS/S&M: Close all floating FX windows for selected track(s)" }, "S&M_WNCLS5", closeAllFXWindows, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Close all floating FX windows, except focused one" }, "S&M_WNCLS6", closeAllFXWindowsExceptFocused, NULL, },
	{ { DEFACCEL, "SWS/S&M: Show all floating FX windows (!)" }, "S&M_WNTSHW1", showAllFXWindows, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Show all FX chain windows (!)" }, "S&M_WNTSHW2", showAllFXChainsWindows, NULL, },
	{ { DEFACCEL, "SWS/S&M: Show all floating FX windows for selected track(s)" }, "S&M_WNTSHW3", showAllFXWindows, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Toggle show all floating FX windows (!)" }, "S&M_WNTGL3", toggleAllFXWindows, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Toggle show all FX chain windows (!)" }, "S&M_WNTGL4", toggleAllFXChainsWindows, NULL, },	
	{ { DEFACCEL, "SWS/S&M: Toggle show all floating FX windows for selected track(s)" }, "S&M_WNTGL5", toggleAllFXWindows, NULL, 1},

	{ { DEFACCEL, "SWS/S&M: Show previous floating FX window (and hide others) for selected track(s)" }, "S&M_WNONLY1", floatOnlyFXWnd, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Show next floating FX window (and hide others) for selected track(s)" }, "S&M_WNONLY2", floatOnlyFXWnd, NULL, 1},

	{ { DEFACCEL, "SWS/S&M: Focus previous floating FX window for selected track(s)" }, "S&M_WNFOCUS1", focusNextPreviousSelTracksFXWnd, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Focus next floating FX window for selected track(s)" }, "S&M_WNFOCUS2", focusNextPreviousSelTracksFXWnd, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Focus previous floating FX window" }, "S&M_WNFOCUS3", focusNextPreviousAllTracksFXWnd, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Focus next floating FX window" }, "S&M_WNFOCUS4", focusNextPreviousAllTracksFXWnd, NULL, 1},

	{ { DEFACCEL, "SWS/S&M: Focus main window" }, "S&M_WNMAIN", setMainWindowActive, NULL, },

	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 1) for selected track(s)" }, "S&M_SHOWFXCHAIN1", showFXChain, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 2) for selected track(s)" }, "S&M_SHOWFXCHAIN2", showFXChain, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 3) for selected track(s)" }, "S&M_SHOWFXCHAIN3", showFXChain, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 4) for selected track(s)" }, "S&M_SHOWFXCHAIN4", showFXChain, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 5) for selected track(s)" }, "S&M_SHOWFXCHAIN5", showFXChain, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 6) for selected track(s)" }, "S&M_SHOWFXCHAIN6", showFXChain, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 7) for selected track(s)" }, "S&M_SHOWFXCHAIN7", showFXChain, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (FX 8) for selected track(s)" }, "S&M_SHOWFXCHAIN8", showFXChain, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Show FX chain (selected FX) for selected track(s)" }, "S&M_SHOWFXCHAINSEL", showFXChain, NULL, -1},

	{ { DEFACCEL, "SWS/S&M: Hide FX chain for selected track(s)" }, "S&M_HIDEFXCHAIN", hideFXChain, NULL, },
	{ { DEFACCEL, "SWS/S&M: Toggle show FX chain for selected track(s)" }, "S&M_TOGLFXCHAIN", toggleFXChain, NULL, },

	{ { DEFACCEL, "SWS/S&M: Float FX 1 window for selected track(s)" }, "S&M_FLOATFX1", floatFX, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Float FX 2 window for selected track(s)" }, "S&M_FLOATFX2", floatFX, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Float FX 3 window for selected track(s)" }, "S&M_FLOATFX3", floatFX, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Float FX 4 window for selected track(s)" }, "S&M_FLOATFX4", floatFX, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Float FX 5 window for selected track(s)" }, "S&M_FLOATFX5", floatFX, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Float FX 6 window for selected track(s)" }, "S&M_FLOATFX6", floatFX, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Float FX 7 window for selected track(s)" }, "S&M_FLOATFX7", floatFX, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Float FX 8 window for selected track(s)" }, "S&M_FLOATFX8", floatFX, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Float selected FX window for selected track(s)" }, "S&M_FLOATFXSEL", floatFX, NULL, -1},

	{ { DEFACCEL, "SWS/S&M: Un-float FX 1 window for selected track(s)" }, "S&M_UNFLOATFX1", unfloatFX, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Un-float FX 2 window for selected track(s)" }, "S&M_UNFLOATFX2", unfloatFX, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Un-float FX 3 window for selected track(s)" }, "S&M_UNFLOATFX3", unfloatFX, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Un-float FX 4 window for selected track(s)" }, "S&M_UNFLOATFX4", unfloatFX, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Un-float FX 5 window for selected track(s)" }, "S&M_UNFLOATFX5", unfloatFX, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Un-float FX 6 window for selected track(s)" }, "S&M_UNFLOATFX6", unfloatFX, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Un-float FX 7 window for selected track(s)" }, "S&M_UNFLOATFX7", unfloatFX, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Un-float FX 8 window for selected track(s)" }, "S&M_UNFLOATFX8", unfloatFX, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Un-float selected FX window for selected track(s)" }, "S&M_UNFLOATFXSEL", unfloatFX, NULL, -1},

	{ { DEFACCEL, "SWS/S&M: Toggle float FX 1 window for selected track(s)" }, "S&M_TOGLFLOATFX1", toggleFloatFX, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Toggle float FX 2 window for selected track(s)" }, "S&M_TOGLFLOATFX2", toggleFloatFX, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Toggle float FX 3 window for selected track(s)" }, "S&M_TOGLFLOATFX3", toggleFloatFX, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Toggle float FX 4 window for selected track(s)" }, "S&M_TOGLFLOATFX4", toggleFloatFX, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Toggle float FX 5 window for selected track(s)" }, "S&M_TOGLFLOATFX5", toggleFloatFX, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Toggle float FX 6 window for selected track(s)" }, "S&M_TOGLFLOATFX6", toggleFloatFX, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Toggle float FX 7 window for selected track(s)" }, "S&M_TOGLFLOATFX7", toggleFloatFX, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Toggle float FX 8 window for selected track(s)" }, "S&M_TOGLFLOATFX8", toggleFloatFX, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Toggle float selected FX window for selected track(s)" }, "S&M_TOGLFLOATFXSEL", toggleFloatFX, NULL, -1},


	// Track FX selection -----------------------------------------------------
	{ { DEFACCEL, "SWS/S&M: Select previous FX (cycling) for selected track(s)" }, "S&M_SELFXPREV", selectFX, NULL, -2},
	{ { DEFACCEL, "SWS/S&M: Select next FX (cycling) for selected track(s)" }, "S&M_SELFXNEXT", selectFX, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Select FX 1 for selected track(s)" }, "S&M_SELFX1", selectFX, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Select FX 2 for selected track(s)" }, "S&M_SELFX2", selectFX, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Select FX 3 for selected track(s)" }, "S&M_SELFX3", selectFX, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Select FX 4 for selected track(s)" }, "S&M_SELFX4", selectFX, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Select FX 5 for selected track(s)" }, "S&M_SELFX5", selectFX, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Select FX 6 for selected track(s)" }, "S&M_SELFX6", selectFX, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Select FX 7 for selected track(s)" }, "S&M_SELFX7", selectFX, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Select FX 8 for selected track(s)" }, "S&M_SELFX8", selectFX, NULL, 7},


	// Track FX online/offline & bypass/unbypass ------------------------------
	{ { DEFACCEL, "SWS/S&M: Toggle FX 1 online/offline for selected track(s)" }, "S&M_FXOFF1", toggleFXOfflineSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 2 online/offline for selected track(s)" }, "S&M_FXOFF2", toggleFXOfflineSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 3 online/offline for selected track(s)" }, "S&M_FXOFF3", toggleFXOfflineSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 4 online/offline for selected track(s)" }, "S&M_FXOFF4", toggleFXOfflineSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 5 online/offline for selected track(s)" }, "S&M_FXOFF5", toggleFXOfflineSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 6 online/offline for selected track(s)" }, "S&M_FXOFF6", toggleFXOfflineSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 7 online/offline for selected track(s)" }, "S&M_FXOFF7", toggleFXOfflineSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 8 online/offline for selected track(s)" }, "S&M_FXOFF8", toggleFXOfflineSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Toggle last FX online/offline for selected track(s)" }, "S&M_FXOFFLAST", toggleFXOfflineSelectedTracks, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Toggle selected FX online/offline for selected track(s)" }, "S&M_FXOFFSEL", toggleFXOfflineSelectedTracks, NULL, 0},

	{ { DEFACCEL, "SWS/S&M: Set FX 1 online for selected track(s)" }, "S&M_FXOFF_SETON1", setFXOnlineSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Set FX 2 online for selected track(s)" }, "S&M_FXOFF_SETON2", setFXOnlineSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Set FX 3 online for selected track(s)" }, "S&M_FXOFF_SETON3", setFXOnlineSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Set FX 4 online for selected track(s)" }, "S&M_FXOFF_SETON4", setFXOnlineSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Set FX 5 online for selected track(s)" }, "S&M_FXOFF_SETON5", setFXOnlineSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Set FX 6 online for selected track(s)" }, "S&M_FXOFF_SETON6", setFXOnlineSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Set FX 7 online for selected track(s)" }, "S&M_FXOFF_SETON7", setFXOnlineSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Set FX 8 online for selected track(s)" }, "S&M_FXOFF_SETON8", setFXOnlineSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Set last FX online for selected track(s)" }, "S&M_FXOFF_SETONLAST", setFXOnlineSelectedTracks, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Set selected FX online for selected track(s)" }, "S&M_FXOFF_SETONSEL", setFXOnlineSelectedTracks, NULL, 0},

	{ { DEFACCEL, "SWS/S&M: Set FX 1 offline for selected track(s)" }, "S&M_FXOFF_SETOFF1", setFXOfflineSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Set FX 2 offline for selected track(s)" }, "S&M_FXOFF_SETOFF2", setFXOfflineSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Set FX 3 offline for selected track(s)" }, "S&M_FXOFF_SETOFF3", setFXOfflineSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Set FX 4 offline for selected track(s)" }, "S&M_FXOFF_SETOFF4", setFXOfflineSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Set FX 5 offline for selected track(s)" }, "S&M_FXOFF_SETOFF5", setFXOfflineSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Set FX 6 offline for selected track(s)" }, "S&M_FXOFF_SETOFF6", setFXOfflineSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Set FX 7 offline for selected track(s)" }, "S&M_FXOFF_SETOFF7", setFXOfflineSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Set FX 8 offline for selected track(s)" }, "S&M_FXOFF_SETOFF8", setFXOfflineSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Set last FX offline for selected track(s)" }, "S&M_FXOFF_SETOFFLAST", setFXOfflineSelectedTracks, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Set selected FX offline for selected track(s)" }, "S&M_FXOFF_SETOFFSEL", setFXOfflineSelectedTracks, NULL, 0},

	{ { DEFACCEL, "SWS/S&M: Toggle all FXs online/offline for selected track(s)" }, "S&M_FXOFFALL", toggleAllFXsOfflineSelectedTracks, NULL, },

	{ { DEFACCEL, "SWS/S&M: Toggle FX 1 bypass for selected track(s)" }, "S&M_FXBYP1", toggleFXBypassSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 2 bypass for selected track(s)" }, "S&M_FXBYP2", toggleFXBypassSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 3 bypass for selected track(s)" }, "S&M_FXBYP3", toggleFXBypassSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 4 bypass for selected track(s)" }, "S&M_FXBYP4", toggleFXBypassSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 5 bypass for selected track(s)" }, "S&M_FXBYP5", toggleFXBypassSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 6 bypass for selected track(s)" }, "S&M_FXBYP6", toggleFXBypassSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 7 bypass for selected track(s)" }, "S&M_FXBYP7", toggleFXBypassSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Toggle FX 8 bypass for selected track(s)" }, "S&M_FXBYP8", toggleFXBypassSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Toggle last FX bypass for selected track(s)" }, "S&M_FXBYPLAST", toggleFXBypassSelectedTracks, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Toggle selected FX bypass for selected track(s)" }, "S&M_FXBYPSEL", toggleFXBypassSelectedTracks, NULL, 0},
	
	{ { DEFACCEL, "SWS/S&M: Bypass FX 1 for selected track(s)" }, "S&M_FXBYP_SETON1", setFXBypassSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Bypass FX 2 for selected track(s)" }, "S&M_FXBYP_SETON2", setFXBypassSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Bypass FX 3 for selected track(s)" }, "S&M_FXBYP_SETON3", setFXBypassSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Bypass FX 4 for selected track(s)" }, "S&M_FXBYP_SETON4", setFXBypassSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Bypass FX 5 for selected track(s)" }, "S&M_FXBYP_SETON5", setFXBypassSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Bypass FX 6 for selected track(s)" }, "S&M_FXBYP_SETON6", setFXBypassSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Bypass FX 7 for selected track(s)" }, "S&M_FXBYP_SETON7", setFXBypassSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Bypass FX 8 for selected track(s)" }, "S&M_FXBYP_SETON8", setFXBypassSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Bypass last FX bypass for selected track(s)" }, "S&M_FXBYP_SETONLAST", setFXBypassSelectedTracks, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Bypass selected FX bypass for selected track(s)" }, "S&M_FXBYP_SETONSEL", setFXBypassSelectedTracks, NULL, 0},
	
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 1 for selected track(s)" }, "S&M_FXBYP_SETOFF1", setFXUnbypassSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 2 for selected track(s)" }, "S&M_FXBYP_SETOFF2", setFXUnbypassSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 3 for selected track(s)" }, "S&M_FXBYP_SETOFF3", setFXUnbypassSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 4 for selected track(s)" }, "S&M_FXBYP_SETOFF4", setFXUnbypassSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 5 for selected track(s)" }, "S&M_FXBYP_SETOFF5", setFXUnbypassSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 6 for selected track(s)" }, "S&M_FXBYP_SETOFF6", setFXUnbypassSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 7 for selected track(s)" }, "S&M_FXBYP_SETOFF7", setFXUnbypassSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Unbypass FX 8 for selected track(s)" }, "S&M_FXBYP_SETOFF8", setFXUnbypassSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Unbypass last FX for selected track(s)" }, "S&M_FXBYP_SETOFFLAST", setFXUnbypassSelectedTracks, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Unbypass selected FX for selected track(s)" }, "S&M_FXBYP_SETOFFSEL", setFXUnbypassSelectedTracks, NULL, 0},
	
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs bypass for selected track(s)" }, "S&M_FXBYPALL", toggleAllFXsBypassSelectedTracks, NULL, },

	{ { DEFACCEL, "SWS/S&M: Bypass all FXs for selected track(s)" }, "S&M_FXBYPALL2", setAllFXsBypassSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Unbypass all FXs for selected track(s)" }, "S&M_FXBYPALL3", setAllFXsBypassSelectedTracks, NULL, 0},
	// ..related online/offline actions natively implemented

	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 1) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT1", toggleExceptFXOfflineSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 2) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT2", toggleExceptFXOfflineSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 3) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT3", toggleExceptFXOfflineSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 4) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT4", toggleExceptFXOfflineSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 5) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT5", toggleExceptFXOfflineSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 6) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT6", toggleExceptFXOfflineSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 7) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT7", toggleExceptFXOfflineSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 8) online/offline for selected track(s)" }, "S&M_FXOFFEXCPT8", toggleExceptFXOfflineSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except selected) online/offline for selected track(s)" }, "S&M_FXOFFEXCPTSEL", toggleExceptFXOfflineSelectedTracks, NULL, 0},

	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 1) bypass for selected track(s)" }, "S&M_FXBYPEXCPT1", toggleExceptFXBypassSelectedTracks, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 2) bypass for selected track(s)" }, "S&M_FXBYPEXCPT2", toggleExceptFXBypassSelectedTracks, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 3) bypass for selected track(s)" }, "S&M_FXBYPEXCPT3", toggleExceptFXBypassSelectedTracks, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 4) bypass for selected track(s)" }, "S&M_FXBYPEXCPT4", toggleExceptFXBypassSelectedTracks, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 5) bypass for selected track(s)" }, "S&M_FXBYPEXCPT5", toggleExceptFXBypassSelectedTracks, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 6) bypass for selected track(s)" }, "S&M_FXBYPEXCPT6", toggleExceptFXBypassSelectedTracks, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 7) bypass for selected track(s)" }, "S&M_FXBYPEXCPT7", toggleExceptFXBypassSelectedTracks, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except 8) bypass for selected track(s)" }, "S&M_FXBYPEXCPT8", toggleExceptFXBypassSelectedTracks, NULL, 8},
	{ { DEFACCEL, "SWS/S&M: Toggle all FXs (except selected) bypass for selected track(s)" }, "S&M_FXBYPEXCPTSEL", toggleExceptFXBypassSelectedTracks, NULL, 0},


	// FX Chains (items & tracks) ---------------------------------------------
	{ { DEFACCEL, "SWS/S&M: Open FX chains window" }, "S&M_SHOWFXCHAINSLOTS", OpenFXChainList, NULL, },
	{ { DEFACCEL, "SWS/S&M: Clear FX chain slot..." }, "S&M_CLRFXCHAINSLOT", clearFXChainSlotPrompt, NULL, },
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 1" }, "S&M_TAKEFXCHAIN1", loadPasteTakeFXChain, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 2" }, "S&M_TAKEFXCHAIN2", loadPasteTakeFXChain, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 3" }, "S&M_TAKEFXCHAIN3", loadPasteTakeFXChain, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 4" }, "S&M_TAKEFXCHAIN4", loadPasteTakeFXChain, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 5" }, "S&M_TAKEFXCHAIN5", loadPasteTakeFXChain, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 6" }, "S&M_TAKEFXCHAIN6", loadPasteTakeFXChain, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 7" }, "S&M_TAKEFXCHAIN7", loadPasteTakeFXChain, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), slot 8" }, "S&M_TAKEFXCHAIN8", loadPasteTakeFXChain, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), prompt for slot" }, "S&M_TAKEFXCHAINp1", loadPasteTakeFXChain, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected item(s), all takes, prompt for slot" }, "S&M_TAKEFXCHAINp2", loadPasteAllTakesFXChain, NULL, -1},

	{ { DEFACCEL, "SWS/S&M: Copy FX chain from selected item" }, "S&M_COPYFXCHAIN1", copyTakeFXChain, NULL, }, 
	{ { DEFACCEL, "SWS/S&M: Cut FX chain from selected item" }, "S&M_COPYFXCHAIN2", cutTakeFXChain, NULL, }, 
	{ { DEFACCEL, "SWS/S&M: Paste FX chain to selected item(s)" }, "S&M_COPYFXCHAIN3", pasteTakeFXChain, NULL, }, 
	{ { DEFACCEL, "SWS/S&M: Paste FX chain to selected item(s), all takes" }, "S&M_COPYFXCHAIN4", pasteAllTakesFXChain, NULL, }, 
	{ { DEFACCEL, "SWS/S&M: Copy FX chain from selected track" }, "S&M_COPYFXCHAIN5", copyTrackFXChain, NULL, }, 
	{ { DEFACCEL, "SWS/S&M: Cut FX chain from selected track" }, "S&M_COPYFXCHAIN6", cutTrackFXChain, NULL, }, 
	{ { DEFACCEL, "SWS/S&M: Paste FX chain to selected track(s)" }, "S&M_COPYFXCHAIN7", pasteTrackFXChain, NULL, }, 

	{ { DEFACCEL, "SWS/S&M: Clear FX chain for selected item(s)" },  "S&M_CLRFXCHAIN1", clearActiveTakeFXChain, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Clear FX chain for selected item(s), all takes" },  "S&M_CLRFXCHAIN2", clearAllTakesFXChain, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Clear FX chain for selected track(s)" }, "S&M_CLRFXCHAIN3", clearTrackFXChain, NULL, 0},

	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 1" }, "S&M_TRACKFXCHAIN1", loadPasteTrackFXChain, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 2" }, "S&M_TRACKFXCHAIN2", loadPasteTrackFXChain, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 3" }, "S&M_TRACKFXCHAIN3", loadPasteTrackFXChain, NULL, 2},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 4" }, "S&M_TRACKFXCHAIN4", loadPasteTrackFXChain, NULL, 3},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 5" }, "S&M_TRACKFXCHAIN5", loadPasteTrackFXChain, NULL, 4},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 6" }, "S&M_TRACKFXCHAIN6", loadPasteTrackFXChain, NULL, 5},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 7" }, "S&M_TRACKFXCHAIN7", loadPasteTrackFXChain, NULL, 6},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), slot 8" }, "S&M_TRACKFXCHAIN8", loadPasteTrackFXChain, NULL, 7},
	{ { DEFACCEL, "SWS/S&M: Load/Apply FX chain to selected track(s), prompt for slot" }, "S&M_TRACKFXCHAINp1", loadPasteTrackFXChain, NULL, -1},
	
	
	// Takes ------------------------------------------------------------------
	{ { DEFACCEL, "SWS/S&M: Takes - Clear active take(s)/item(s)" }, "S&M_CLRTAKE1", clearTake, NULL, },
	{ { DEFACCEL, "SWS/S&M: Takes - Build lane(s) for selected track(s)" }, "S&M_LANETAKE1", buildLanes, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Takes - Select lane from selected item" }, "S&M_LANETAKE2", selectTakeLane, NULL, },
	{ { DEFACCEL, "SWS/S&M: Takes - Build lane(s) for selected items(s)" }, "S&M_LANETAKE3", buildLanes, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Takes - Remove empty source take/item(s) among selected item(s)" }, "S&M_DELEMPTYTAKE", removeEmptyTakes, NULL, },
	{ { DEFACCEL, "SWS/S&M: Takes - Remove empty MIDI take/item(s) among selected item(s)" }, "S&M_DELEMPTYTAKE2", removeEmptyMidiTakes, NULL, },
	{ { DEFACCEL, "SWS/S&M: Takes - Remove ALL empty take/item(s) among selected item(s)" }, "S&M_DELEMPTYTAKE3", removeAllEmptyTakes, NULL, },
	{ { DEFACCEL, "SWS/S&M: Takes - Move all up (cycling) in selected item(s)" }, "S&M_MOVETAKE1", moveTakes, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Takes - Move all down (cycling) in selected item(s)" }, "S&M_MOVETAKE2", moveTakes, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Takes - Move active up (cycling) in selected item(s)" }, "S&M_MOVETAKE3", moveActiveTake, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Takes - Move active down (cycling) in selected item(s)" }, "S&M_MOVETAKE4", moveActiveTake, NULL, 1},

	{ { DEFACCEL, "SWS/S&M: Split MIDI or Audio at prior zero crossing" }, "S&M_SPLIT1", splitMidiAudio, NULL, },

	{ { DEFACCEL, "SWS/S&M: Show take volume enveloppe" }, "S&M_TAKEENV1", showHideTakeVolEnvelope, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Show take pan enveloppe" }, "S&M_TAKEENV2", showHideTakePanEnvelope, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Show take mute enveloppe" }, "S&M_TAKEENV3", showHideTakeMuteEnvelope, NULL, 1},
	{ { DEFACCEL, "SWS/S&M: Hide take volume enveloppe" }, "S&M_TAKEENV4", showHideTakeVolEnvelope, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Hide take pan enveloppe" }, "S&M_TAKEENV5", showHideTakePanEnvelope, NULL, 0},
	{ { DEFACCEL, "SWS/S&M: Hide take mute enveloppe" }, "S&M_TAKEENV6", showHideTakeMuteEnvelope, NULL, 0},
/*exist natively
	{ { DEFACCEL, "SWS/S&M: Toggle show take volume enveloppe" }, "S&M_TAKEENV7", showHideTakeVolEnvelope, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Toggle show take pan enveloppe" }, "S&M_TAKEENV8", showHideTakePanEnvelope, NULL, -1},
	{ { DEFACCEL, "SWS/S&M: Toggle show take mute enveloppe" }, "S&M_TAKEENV9", showHideTakeMuteEnvelope, NULL, -1},
*/

	// Experimental, misc., deprecated, etc.. ---------------------------------
//	{ { DEFACCEL, "SWS/S&M: Move track (1 -> 4)" }, "S&M_TMP1", moveTest, NULL, },
//	{ { DEFACCEL, "SWS/S&M: Select items by name" }, "S&M_ITM1", selectItemsByNamePrompt, NULL, },
//	{ { DEFACCEL, "SWS/S&M: test -> Padre show take volume enveloppe" }, "S&M_TMP1", ShowTakeEnvPadreTest, NULL, 0},
//	{ { DEFACCEL, "SWS/S&M: test -> Padre show take pan enveloppe" }, "S&M_TMP2", ShowTakeEnvPadreTest, NULL, 1},
//	{ { DEFACCEL, "SWS/S&M: test -> Padre show take mute enveloppe" }, "S&M_TMP3", ShowTakeEnvPadreTest, NULL, 2},

	{ {}, LAST_COMMAND, }, // Denote end of table
};

int SnMActionsInit()
{
	FXChainListInit();
	return SWSRegisterCommands(g_commandTable);
}


///////////////////////////////////////////////////////////////////////////////
// GUIs
///////////////////////////////////////////////////////////////////////////////

// one for lazy guys
void SNM_ShowConsoleMsg(const char* _title, const char* _msg) 
{
		ShowConsoleMsg(""); //clear
		ShowConsoleMsg(_msg);
#ifdef _WIN32
		// a little hack..
		HWND w = FindWindow(NULL, "ReaScript console output");
		if (w != NULL)
			SetWindowTextA(w, _title);
#endif
}

void fillHWoutDropDown(HWND _hwnd, int _idc)
{
	int x=0, x0=0;
	char buffer[BUFFER_SIZE] = "<None>";
	x0 = SendDlgItemMessage(_hwnd,_idc,CB_ADDSTRING,0,(LPARAM)buffer);
	SendDlgItemMessage(_hwnd,_idc,CB_SETITEMDATA,x0,0);
	
	// get mono outputs
	WDL_PtrList<WDL_String> monos;
	int monoIdx=0;
	while (GetOutputChannelName(monoIdx))
	{
		monos.Add(new WDL_String(GetOutputChannelName(monoIdx)));
		monoIdx++;
	}

	// add stereo outputs
	WDL_PtrList<WDL_String> stereos;
	if (monoIdx)
	{
		for(int i=0; i < (monoIdx-1); i++)
		{
			WDL_String* hw = new WDL_String();
			hw->SetFormatted(256, "%s / %s", monos.Get(i)->Get(), monos.Get(i+1)->Get());
			stereos.Add(hw);
		}
	}

	// fill dropdown
	for(int i=0; i < stereos.GetSize(); i++)
	{
		x = SendDlgItemMessage(_hwnd,_idc,CB_ADDSTRING,0,(LPARAM)stereos.Get(i)->Get());
		SendDlgItemMessage(_hwnd,_idc,CB_SETITEMDATA,x,i+1); // +1 for <none>
	}
	for(int i=0; i < monos.GetSize(); i++)
	{
		x = SendDlgItemMessage(_hwnd,_idc,CB_ADDSTRING,0,(LPARAM)monos.Get(i)->Get());
		SendDlgItemMessage(_hwnd,_idc,CB_SETITEMDATA,x,i+1); // +1 for <none>
	}

//	SendDlgItemMessage(_hwnd,_idc,CB_SETCURSEL,x0,0);
	monos.Empty(true);
	stereos.Empty(true);
}

WDL_DLGRET CueBusDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	const char cWndPosKey[] = "CueBus Window Pos";

	switch(Message)
	{
        case WM_INITDIALOG :
		{
			char busName[BUFFER_SIZE] = "";
			char trTemplatePath[BUFFER_SIZE] = "";
			int reaType, userType, soloGrp, hwOuts[8];
			bool trTemplate,showRouting, sendToMaster;
			readCueBusIniFile(busName, &reaType, &trTemplate, trTemplatePath, &showRouting, &soloGrp, &sendToMaster, hwOuts);
			userType = GetComboSendIdxType(reaType);
			SetDlgItemText(hwnd,IDC_SNM_CUEBUS_NAME,busName);

			int x=0;
			for(int i=1; i<4; i++)
			{
				x = SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_TYPE,CB_ADDSTRING,0,(LPARAM)GetSendTypeStr(i));
				SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_TYPE,CB_SETITEMDATA,x,i);
				if (i==userType) SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_TYPE,CB_SETCURSEL,x,0);
			}

			for(int i=0; i < (MAX_TRACK_GROUPS+1); i++)
			{
				char buffer[BUFFER_SIZE] = "<None>";
				if (i) sprintf(buffer, "%d", i);
				x = SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_SOLOGRP,CB_ADDSTRING,0,(LPARAM)buffer);
				SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_SOLOGRP,CB_SETITEMDATA,x,i);
				if (i==soloGrp) SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_SOLOGRP,CB_SETCURSEL,x,0);
			}

			CheckDlgButton(hwnd, IDC_CHECK3, trTemplate);
			SetDlgItemText(hwnd,IDC_SNM_CUEBUS_TEMPLATE,trTemplatePath);

			CheckDlgButton(hwnd, IDC_CHECK1, sendToMaster);
			CheckDlgButton(hwnd, IDC_CHECK2, showRouting);

			for(int i=0; i < SNM_MAX_HW_OUTS; i++) 
			{
				fillHWoutDropDown(hwnd,IDC_SNM_CUEBUS_HWOUT1+i);
				SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_HWOUT1+i,CB_SETCURSEL,hwOuts[i],0);
			}

			RestoreWindowPos(hwnd, cWndPosKey, false);
			SetFocus(GetDlgItem(hwnd, IDC_SNM_CUEBUS_NAME));
			PostMessage(hwnd, WM_COMMAND, IDC_CHECK3, 0); // enable//disable state
			return 0;
		}
		break;

		case WM_COMMAND :
		{
            switch(LOWORD(wParam))
            {
                case IDOK:
				case IDC_SAVE:
				{
					char cueBusName[BUFFER_SIZE];
					GetDlgItemText(hwnd,IDC_SNM_CUEBUS_NAME,cueBusName,BUFFER_SIZE);

					int userType = 2, reaType;
					int combo = SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_TYPE,CB_GETCURSEL,0,0);
					if(combo != CB_ERR)
						userType = combo+1;
					switch(userType)
					{
						case 1: reaType=0; break;
						case 2: reaType=3; break;
						case 3: reaType=1; break;
						default: break;
					}

					int soloGrp = MAX_TRACK_GROUPS;
					combo = SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_SOLOGRP,CB_GETCURSEL,0,0);
					if(combo != CB_ERR) soloGrp = combo;
					
					int sendToMaster = IsDlgButtonChecked(hwnd, IDC_CHECK1);
					int showRouting = IsDlgButtonChecked(hwnd, IDC_CHECK2);
					int trTemplate = IsDlgButtonChecked(hwnd, IDC_CHECK3);

					char trTemplatePath[BUFFER_SIZE];
					GetDlgItemText(hwnd,IDC_SNM_CUEBUS_TEMPLATE,trTemplatePath,BUFFER_SIZE);

					int hwOuts[SNM_MAX_HW_OUTS];
					for (int i=0; i<SNM_MAX_HW_OUTS; i++)
					{
						hwOuts[i] = SendDlgItemMessage(hwnd,IDC_SNM_CUEBUS_HWOUT1+i,CB_GETCURSEL,0,0);
						if(hwOuts[i] == CB_ERR)	hwOuts[i] = 0;
					}

					// *** Create cue buss ***
					if (LOWORD(wParam) == IDC_SAVE ||
						cueTrack(cueBusName, reaType, "Create cue buss",
							(showRouting == 1), soloGrp, 
							trTemplate ? trTemplatePath : NULL, 
							(sendToMaster == 1), hwOuts))
					{
						saveCueBusIniFile(cueBusName, reaType, (trTemplate == 1), trTemplatePath, (showRouting == 1), soloGrp, (sendToMaster == 1), hwOuts);
					}
					return 0;
				}
				break;

				case IDCANCEL:
				{
					ShowWindow(hwnd, SW_HIDE);
					return 0;
				}
				break;

				case IDC_FILES:
				{
					char currentPath[BUFFER_SIZE];
					GetDlgItemText(hwnd,IDC_SNM_CUEBUS_TEMPLATE,currentPath,BUFFER_SIZE);
					char* filename = BrowseForFiles("Load track template", currentPath, NULL, false, "REAPER Track Template (*.RTrackTemplate)\0*.RTrackTemplate\0");
					if (filename)
					{
						SetDlgItemText(hwnd,IDC_SNM_CUEBUS_TEMPLATE,filename);
						free(filename);
					}
				}
				break;

				case IDC_CHECK3:
				{
					bool templateEnable = (IsDlgButtonChecked(hwnd, IDC_CHECK3) == 1);
					EnableWindow(GetDlgItem(hwnd, IDC_SNM_CUEBUS_TEMPLATE), templateEnable);
					EnableWindow(GetDlgItem(hwnd, IDC_FILES), templateEnable);
					EnableWindow(GetDlgItem(hwnd, IDC_SNM_CUEBUS_NAME), !templateEnable);
					for(int k=0; k < SNM_MAX_HW_OUTS ; k++)
						EnableWindow(GetDlgItem(hwnd, IDC_SNM_CUEBUS_HWOUT1+k), !templateEnable);
					EnableWindow(GetDlgItem(hwnd, IDC_CHECK1), !templateEnable);
					SetFocus(GetDlgItem(hwnd, templateEnable ? IDC_SNM_CUEBUS_TEMPLATE : IDC_SNM_CUEBUS_NAME));
				}
				break;
				
				default:
					break;
			}
		}
		break;

		case WM_DESTROY:
			SaveWindowPos(hwnd, cWndPosKey);
			break; 

		default:
			break;
	}

	return 0;
}
