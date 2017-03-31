#include "shared_menu.h"

grafeex::menu::shared::shared(const hwnd_type &target, option options)
	: object((options == option::system) ? ::GetSystemMenu(target, FALSE) : ::GetMenu(target)){}

grafeex::menu::shared::~shared(){}
