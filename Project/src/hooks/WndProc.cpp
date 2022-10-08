#include <pch.h>
#include <base.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
		Data::WmKeys[wParam] = uMsg;
    
	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
			case Data::Keys::ToggleMenu:
			{
				Data::ShowMenu = !Data::ShowMenu;
				ImGuiIO& io = ImGui::GetIO();

				// Draw cursor in cases where it is not available.
				if (Data::ShowMenu)
				{
					io.MouseDrawCursor = true;
				}
				else
				{
					io.MouseDrawCursor = false;
				}

				break;
			}
			case Data::Keys::DetachDll:
			{
				Data::ToDetach = true;
				break;
			}
		}
	}
	
	// If menu is to be shown pass controlls to the gui and ignore the main process window input commands.
	if (Data::ShowMenu)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

		return true;
	}

	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}