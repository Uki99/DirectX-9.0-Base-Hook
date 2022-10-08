#pragma once

#include <pch.h>
#include <base.h>
#include <icons.h>
#include <imguipp/imguipp.h>

#define WINDOW_NAME  "Default Window Name"
#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 430

namespace Settings
{
	extern int tab;
}

namespace GUI
{
	void SetTheme(void);     // ImGUI theme
	void Render(void); // Menu
	void ExecuteInterfaceLogic(void);  // GUI Logic
}