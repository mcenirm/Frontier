
/*� copyright 1991-96 UserLand Software, Inc. All Rights Reserved.*/


#include <AppleEvents.h>


#define applemenu 128 
#define aboutitem 1 

#define filemenu 129
#define quititem 1

MenuHandle happlemenu, hfilemenu; 

WindowPtr mainwindow = nil;

Str255 windowmessage; 

Boolean flexitmainloop = false; 

Boolean flcurrentlyactive = true;


/*
7/19/94 dmb: Updated for Univeral Headers / PowerPC
*/



static void initMacintosh (void) {

	/*
	the magic stuff that every Macintosh application needs to do 
	before doing anything else.
	*/

	short i;
		
	MaxApplZone ();
	
	for (i = 0; i < 10; i++) 
		MoreMasters ();
	
	InitGraf (&qd.thePort);
	
	InitFonts ();
	
	FlushEvents (everyEvent, 0);
	
	InitWindows ();
	
	InitMenus ();
	
	TEInit ();
	
	InitDialogs (0L);
	
	InitCursor ();
	
	for (i = 0; i < 5; i++) { /*register with Multifinder*/
		
		EventRecord ev;
		
		EventAvail (everyEvent, &ev); /*see TN180 -- splash screen*/
		} /*for*/
	} /*initMacintosh*/


static void initAppMenus (void) {
	
	happlemenu = GetMenu (applemenu); 
	
	AddResMenu (happlemenu, 'DRVR'); 
	
	InsertMenu (happlemenu, 0); 
	
	hfilemenu = GetMenu (filemenu); 
	
	InsertMenu (hfilemenu, 0);
	
	DrawMenuBar ();
	} /*initAppMenus*/


static Boolean initMainWindow (void) {
	
	mainwindow = GetNewWindow (128, nil, (WindowPtr) -1);
	
	if (mainwindow == nil)
		return (false);
	
	ShowWindow (mainwindow);
	
	return (true);
	} /*initMainWindow*/


static void ellipsize (Str255 s, short width) {

	/*
	if the string fits inside the given number of pixels, fine -- do nothing
	and return.
	
	if not, return a string that does fit, with ellipses representing the 
	deleted characters.  ellipses are generated by pressing option-semicolon.
	*/
	
	char len;
	short newwidth;
	
	if ((newwidth = StringWidth (s)) <= width) /*nothing to do, the string fits*/
		return;
	
	len = s [0]; /* current length in characters*/
	
	width -= CharWidth ('�'); /* subtract width of ellipses*/
		
	do { /*until it fits (or we run out of characters)*/
	
		newwidth -= CharWidth (s [len]);
		
		--len;
	} while ((newwidth > width) && (len != 0));
	
	++len; /*make room for the ellipses*/
	
	s [len] = '�'; 
	
	s [0] = (char) len;
	} /*ellipsize*/


static void centerString (Rect r, Str255 s) {
	
	/*
	draw the string in the current font, size and style, centered inside
	the indicated rectangle.
	*/
	
	short rh = r.bottom - r.top;
	short rw = r.right - r.left;
	short h, v;
	FontInfo fi;
	
	GetFontInfo (&fi);
	
	ellipsize (s, rw); /*make sure it fits inside the rectangle, width-wise*/
	
	h = r.left + ((rw - StringWidth (s)) / 2);
	
	v = r.top + ((rh - (fi.ascent + fi.descent)) / 2) + fi.ascent;
	
	MoveTo (h, v);
	
	ClipRect (&r);
	
	DrawString (s);
	} /*centerString*/


static void setFontSizeStyle (short fontnum, short fontsize, short fontstyle) {

	TextFont (fontnum);
	
	TextSize (fontsize);
	
	TextFace (fontstyle);
	} /*setFontSizeStyle*/
	
	
static void updateMainWindow (void) {
	
	Rect r;
	Str255 s;
	
	r = (*mainwindow).portRect;
	
	EraseRect (&r);
	
	setFontSizeStyle (helvetica, 18, bold);
	
	centerString (r, windowmessage);
	
	NumToString (FreeMem () / 1024, s);
	
	MoveTo (r.left + 3, r.bottom - 3);
	
	setFontSizeStyle (geneva, 9, 0);
	
	DrawString (s);
	
	DrawString ("\pK");
	} /*updateMainWindow*/
	
	
static void handleUpdate (EventRecord *ev) {
	
	WindowPtr w;
	
	w = (WindowPtr) (*ev).message;
	
	BeginUpdate (w);
	
	SetPort (w);
	
	updateMainWindow ();
	
	EndUpdate (w);
	} /*handleUpdate*/


static void handleDrag (EventRecord *ev, WindowPtr w) {
	
	Rect r;

	r = qd.screenBits.bounds; 
	
	r.top = r.top + GetMBarHeight (); 
	
	InsetRect (&r, 4, 4);
	
	DragWindow (w, (*ev).where, &r);
	} /*handleDrag*/


static void handleMenu (long codeword) {
	
	short idmenu, iditem;
	
	iditem = LoWord (codeword);
	
	idmenu = HiWord (codeword);
	
	switch (idmenu) {
	
		case applemenu: 
			switch (iditem) {
				
				case aboutitem:
					Alert (262, nil);
					
					break;
			
				default: {
					Str255 s;
					
					GetItem (happlemenu, iditem, s);
					
					OpenDeskAcc (s);
					
					break;
					}
				} /*switch*/
			
			break; /*apple menu*/

		case filemenu: 
			switch (iditem) {
				
				case quititem:
					flexitmainloop = true;
					
					break;
				} /*switch*/
			
			break; /*file menu*/
			
		} /*switch*/
		
	exit:
	
	HiliteMenu (0);
	} /*handleMenu*/


static void handleMouse (EventRecord *ev) {

	WindowPtr w;
	
	switch (FindWindow ((*ev).where, &w)) {
	
		case inMenuBar: 
			handleMenu (MenuSelect ((*ev).where)); 
			
			break;
		
		case inSysWindow:
			SystemClick (ev, w); 
			
			break;
		
		case inDrag:
			handleDrag (ev, w);
			
			break;
		} /*switch*/
	} /*handleMouse*/


static void handleEvent (EventRecord *ev) { 
	
	switch ((*ev).what) {
	
		case keyDown: case autoKey: 
			if ((*ev).modifiers & cmdKey)
				handleMenu (MenuKey ((*ev).message & charCodeMask)); 
			
			break;
			
		case mouseDown:
			handleMouse (ev);
			
			break;
		
		case updateEvt:
			handleUpdate (ev);
			
			break;
		
		case osEvt:
			flcurrentlyactive = ((*ev).message & resumeFlag) != 0;
			
			break;
		
		case kHighLevelEvent:
			AEProcessAppleEvent (ev);
			
			break;
		} /*switch*/
	} /*handleEvent*/


static void AEReturnError (AppleEvent *reply, OSErr errornum, Str255 errorstring) {
	
	AEPutParamPtr (reply, keyErrorNumber, typeShortInteger, (Ptr) &errornum, sizeof (errornum));
		
	AEPutParamPtr (reply, keyErrorString, typeChar, (Ptr) &errorstring [1], errorstring [0]);
	} /*AEReturnError*/
	
		
static pascal OSErr openAppEvent (const AppleEvent *event, AppleEvent *reply, long refcon) {
	
	return (noErr);
	} /*openAppEvent*/


static pascal OSErr openDocEvent (const AppleEvent *event, AppleEvent *reply, long refcon) {
	
	return (noErr);
	} /*openDocEvent*/
	
		
static pascal OSErr printEvent (const AppleEvent *event, AppleEvent *reply, long refcon) {
	
	return (noErr);
	} /*printEvent*/
	
	
static pascal OSErr setMessageEvent (const AppleEvent *event, AppleEvent *reply, long refcon) {

	AEDesc result;
	OSErr ec;
	long len;
	
	ec = AEGetParamDesc (event, keyDirectObject, typeChar, &result);
	
	if (ec != noErr) {
		
		AEReturnError (reply, ec, "\pThe setmessage event requires a text parameter.");
		
		return (false);
		}
		
	len = GetHandleSize (result.dataHandle);
	
	if (len > 255) /*it must fit in a Str255*/
		len = 255;
		
	windowmessage [0] = len; /*set the length of the string*/
	
	BlockMove (*result.dataHandle, &windowmessage [1], len);
	
	AEDisposeDesc (&result);
	
	SetPort (mainwindow);
	
	InvalRect (&(*mainwindow).portRect);
	
	/*convert the string to a number, return it to the client*/ {
		
		long num;
		
		StringToNum (windowmessage, &num);
		
		AEPutParamPtr (reply, keyDirectObject, typeLongInteger, (Ptr) &num, sizeof (num));
		}
	
	return (noErr);
	} /*setMessageEvent*/
	
	
static pascal OSErr quitEvent (const AppleEvent *event, AppleEvent *reply, long refcon) {
	
	flexitmainloop = true;
	
	return (noErr);
	} /*quitEvent*/
	
	
static Boolean installhandlers (void) {

	if (AEInstallEventHandler ('SERV', 'DISP', NewAEEventHandlerProc (setMessageEvent), 0, false) != noErr)
		return (false);
	
	if (AEInstallEventHandler (kCoreEventClass, kAEOpenApplication, NewAEEventHandlerProc (openAppEvent), 0, false) != noErr)
		return (false);
	
	if (AEInstallEventHandler (kCoreEventClass, kAEOpenDocuments, NewAEEventHandlerProc (openDocEvent), 0, false) != noErr)
		return (false);
	
	if (AEInstallEventHandler (kCoreEventClass, kAEPrintDocuments, NewAEEventHandlerProc (printEvent), 0, false) != noErr)
		return (false);
	
	if (AEInstallEventHandler (kCoreEventClass, kAEQuitApplication, NewAEEventHandlerProc (quitEvent), 0, false) != noErr)
		return (false);
	
	return (true);
	} /*installhandlers*/
	

void main (void) {
	
	EventRecord ev;
	
	initMacintosh ();
	
	if (!installhandlers ()) {
	
		Alert (261, nil); /*couldn't install Apple Event handlers*/
		
		return;
		}
	
	initAppMenus ();
	
	initMainWindow ();
	
	while (!flexitmainloop) {
		
		WaitNextEvent (everyEvent, &ev, 1, nil);
		
		handleEvent (&ev);
		} /*while*/
	} /*main*/




