#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <stdio.h>

#define NO_ERR 0
#define ERR_OPENDISPLAY 1
#define ERR_GETSTATE 2
#define ERR_GETKBD 3


int main(int argc, char *argv[])
{
int err = NO_ERR;
Display *display;
XkbDescPtr keyboard;
XkbStateRec state;

if (!(display = XOpenDisplay(NULL))) {err = ERR_OPENDISPLAY; goto  err_open;}
if (XkbGetState(display, XkbUseCoreKbd, &state)) {err = ERR_GETSTATE; goto err_get_state;}
if (!(keyboard = XkbGetKeyboard(display,XkbAllComponentsMask,XkbUseCoreKbd))) {err = ERR_GETKBD; goto err_get_keyboard;}
printf("%s\n",XGetAtomName(display,keyboard->names->groups[state.locked_group]));
XkbFreeKeyboard(keyboard,XkbAllComponentsMask,1);
goto clean_exit;
err_get_keyboard:
err_get_state:
XCloseDisplay(display);
err_open: 
clean_exit:
return err;
}
