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

#include "IOWin32Cursor.h"

IOWin32Cursor::IOWin32Cursor(HWND windowHandle) noexcept
{
	this->windowHandle = windowHandle;
}

IOWin32Cursor::IOWin32Cursor(IOWin32Cursor const &other)
{
	this->windowHandle = other.windowHandle;
	this->isEnabled = other.isEnabled;
}

IOWin32Cursor& IOWin32Cursor::operator=(IOWin32Cursor const &other) noexcept
{
	this->windowHandle = other.windowHandle;
	this->isEnabled = other.isEnabled;

	return *this;
}

void IOWin32Cursor::Enable() noexcept
{
	isEnabled = true;

	this->Show();
	this->Free();
}

void IOWin32Cursor::Disable() noexcept
{
	isEnabled = false;

	this->Hide();
	this->Confine();
}

bool IOWin32Cursor::IsEnabled() const noexcept
{
	return this->isEnabled;
}

void IOWin32Cursor::Show() noexcept
{
	while (ShowCursor(TRUE) < 0);
}

void IOWin32Cursor::Hide() noexcept
{
	while (ShowCursor(FALSE) >= 0);
}

void IOWin32Cursor::Confine() noexcept
{
	RECT screenRect;
	GetClientRect(windowHandle, &screenRect);
	MapWindowPoints(windowHandle, nullptr, reinterpret_cast<POINT*>(&screenRect), 2);
	ClipCursor(&screenRect);
}

void IOWin32Cursor::Free() noexcept
{
	ClipCursor(nullptr);
}