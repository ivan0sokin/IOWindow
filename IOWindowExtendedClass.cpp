#include "IOWindowExtendedClass.h"

IOWindowExtendedClass::IOWindowExtendedClass() noexcept
{
	this->hInstance = GetModuleHandle(nullptr);
	this->name = IO_WINDOW_CLASS_EX_NAME;
}

IOWindowExtendedClass::~IOWindowExtendedClass() noexcept
{
	this->DestroyWindowClassEx();
}

void IOWindowExtendedClass::DestroyWindowClassEx() noexcept
{
	this->UnregisterClassExAndSetInstanceHandleNull();
}

void IOWindowExtendedClass::UnregisterClassExAndSetInstanceHandleNull() noexcept
{
	if (hInstance != nullptr)
	{
		UnregisterClass(name, hInstance);
		hInstance = nullptr;
	}
}

bool IOWindowExtendedClass::MakeWindowClassEx(WNDPROC WndProc) noexcept
{
	WNDCLASSEX windowClassEx;
	ZeroMemory(&windowClassEx, sizeof(WNDCLASSEX));

	windowClassEx.cbSize = sizeof(WNDCLASSEX);
	windowClassEx.style = CS_OWNDC;
	windowClassEx.lpfnWndProc = WndProc;
	windowClassEx.cbClsExtra = 0;
	windowClassEx.cbWndExtra = 0;
	windowClassEx.hInstance = hInstance;
	windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClassEx.hbrBackground = nullptr;
	windowClassEx.lpszMenuName = nullptr;
	windowClassEx.lpszClassName = name;
	windowClassEx.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&windowClassEx))
		return false;

	return true;
}

const HINSTANCE& IOWindowExtendedClass::GetWindowInstanceHandle() const noexcept
{
	return this->hInstance;
}

LPCSTR IOWindowExtendedClass::GetWindowClassExName() const noexcept
{
	return this->name;
}