#ifndef DM_MENUS_H
#define DM_MENUS_H

#include "dm.h"

namespace DM {

class MenuMan {
	DMEngine *_vm;
public:
	bool _shouldRefreshActionArea; // @ G0508_B_RefreshActionArea
	bool _actionAreaContainsIcons; // @ G0509_B_ActionAreaContainsIcons
	MenuMan(DMEngine *vm);
	void clearActingChampion(); // @ F0388_MENUS_ClearActingChampion

	void drawMovementArrows();
};

}

#endif // !DM_MENUS_H
