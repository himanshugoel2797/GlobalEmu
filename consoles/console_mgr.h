#ifndef _CONSOLE_MGR_H_
#define _CONSOLE_MGR_H_

typedef enum {
        NES = 1
} CONSOLES;

int console_mgr_initialize(CONSOLES c);
int console_mgr_loadProgram(const char *fname);
int console_mgr_start();

#endif
