#include "pch.h"
#include "base.h"

DWORD WINAPI MainThread(LPVOID lpThreadParameter)
{
	Base::Data::hModule = (HMODULE)lpThreadParameter;
	Base::Init();

#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitle("DEBUG");
#endif

	return TRUE;
}

DWORD WINAPI ExitThread(LPVOID lpThreadParameter)
{
	if (!Base::Data::Detached)
	{
#ifdef _DEBUG
		fclose((FILE*)stdin);
		fclose((FILE*)stdout);
		FreeConsole();
		PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
#endif

		Base::Data::Detached = true;
		FreeLibraryAndExitThread(Base::Data::hModule, TRUE);
	}

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			if (!Base::Data::Detached)
				CreateThread(nullptr, 0, ExitThread, hModule, 0, nullptr);
			break;
		}
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		default:
			break;
	}

	return TRUE;
}