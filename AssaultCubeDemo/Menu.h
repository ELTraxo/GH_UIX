#pragma once
#include "includes.h"

class Menu
{
	NativeWindowPtr pOverlay;
	WindowPtr pMenu;
public:
	Menu(NativeWindowPtr pOverlay);
	~Menu();
	void Create();
	WindowPtr GetWindowPtr();
	void Toggle();
};

