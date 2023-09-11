#include "config.h" // IWYU pragma: keep

#include "CommandScreen.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Macros.h"
#include "Panel.h"
#include "ProvideCurses.h"


static void CommandScreen_scan(InfoScreen* this) {
   Panel* panel = this->display;
   int idx = MAXIMUM(Panel_getSelectedIndex(panel), 0);
   Panel_prune(panel);

   panel->rawStr=Process_getCommand(this->process);

   Panel_setSelected(panel, idx);
}

static void CommandScreen_draw(InfoScreen* this) {
   InfoScreen_drawTitled(this,"Command of process %d",Process_getPid(this->process));
}

const InfoScreenClass CommandScreen_class = {
   .super = {
      .extends = Class(Object),
      .delete = CommandScreen_delete
   },
   .scan = CommandScreen_scan,
   .draw = CommandScreen_draw
};

CommandScreen* CommandScreen_new(Process* process) {
   CRT_setMouse(0);CommandScreen*this=AllocThis(CommandScreen);
   return (CommandScreen*) InfoScreen_init(&this->super, process, NULL, LINES - 2, " ");
}

void CommandScreen_delete(Object* this) {
   free(InfoScreen_done((InfoScreen*)this));
   CRT_setMouse(1);
}
