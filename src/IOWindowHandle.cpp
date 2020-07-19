#include "IOWindowHandle.h"

IOWindowHandle::IOWindowHandle() noexcept
{
	this->hWnd = nullptr;
}

IOWindowHandle::~IOWindowHandle() noexcept
{
	this->DestroyWindowHandle();
}

void IOWindowHandle::DestroyWindowHandle() noexcept
{
	this->DestroyAndSetWindowHandleNull();
}

void IOWindowHandle::DestroyAndSetWindowHandleNull() noexcept
{
	if (hWnd != nullptr)
	{
		DestroyWindow(hWnd);
		hWnd = nullptr;
	}
}

bool IOWindowHandle::MakeWindowHandle(DWORD extendedStyle, LPCSTR extendedClassName, LPCSTR title, int width, int height, HINSTANCE hInstance, LPVOID pParam) noexcept
{
	RECT windowRect =
	{
		0, 0,
		width, height
	};
	AdjustWindowRect(&windowRect, IO_WINDOW_STYLE, FALSE);

	hWnd = CreateWindowEx
	(
		extendedStyle,
		extendedClassName,
		title,
		IO_WINDOW_STYLE,
		IO_WINDOW_POSITION,
		IO_WINDOW_POSITION,
		windowRect.right,
		windowRect.bottom,
		nullptr,
		nullptr,
		hInstance,
		pParam
	);

	if (hWnd == nullptr)
		return false;

	return true;
}

const HWND& IOWindowHandle::GetWindowHandle() noexcept
{
	return this->hWnd;
}