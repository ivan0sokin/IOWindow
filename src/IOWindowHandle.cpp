/*
	MIT License

	Copyright (c) 2020 x4kkk3r

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "IOWindowHandle.h"

IOWindowHandle::IOWindowHandle() noexcept
{
	this->hWnd = nullptr;
}

IOWindowHandle::~IOWindowHandle() noexcept
{
	this->Destroy();
}

bool IOWindowHandle::Destroy() noexcept
{
	if (!DestroyWindow(hWnd))
		return false;

	return true;
}

bool IOWindowHandle::Create(DWORD extendedStyle, std::string_view extendedClassName, std::string_view title, unsigned long width, unsigned long height, void *pParam) noexcept
{
	RECT windowRect =
	{
		0, 0,
		static_cast<long>(width), static_cast<long>(height)
	};
	AdjustWindowRect(&windowRect, IO_WINDOW_STYLE, FALSE);
	
	hWnd = CreateWindowEx
	(
		extendedStyle,
		extendedClassName.data(),
		title.data(),
		IO_WINDOW_STYLE,
		IO_WINDOW_POSITION,
		IO_WINDOW_POSITION,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		GetModuleHandle(nullptr),
		pParam
	);

	if (hWnd == nullptr)
		return false;

	return true;
}

HWND IOWindowHandle::GetWindowHandle() const noexcept
{
	return this->hWnd;
}