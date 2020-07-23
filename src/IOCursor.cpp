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

#include "IOCursor.h"

IOCursor::IOCursor(HWND windowHandle) noexcept
{
	this->windowHandle = windowHandle;
}

IOCursor::IOCursor(IOCursor const &other)
{
	this->windowHandle = other.windowHandle;
	this->isCursorEnabled = other.isCursorEnabled;
}

IOCursor& IOCursor::operator=(IOCursor const & other) noexcept
{
	this->windowHandle = other.windowHandle;
	this->isCursorEnabled = other.isCursorEnabled;

	return *this;
}

void IOCursor::EnableCursor() noexcept
{
	isCursorEnabled = true;

	this->ShowMouseCursor();
	this->FreeMouseCursor();
}

void IOCursor::DisableCursor() noexcept
{
	isCursorEnabled = false;

	this->HideMouseCursor();
	this->ConfineMouseCursor();
}

bool IOCursor::IsCursorEnabled() const noexcept
{
	return this->isCursorEnabled;
}

void IOCursor::ShowMouseCursor() noexcept
{
	while (ShowCursor(TRUE) < 0);
}

void IOCursor::HideMouseCursor() noexcept
{
	while (ShowCursor(FALSE) >= 0);
}

void IOCursor::ConfineMouseCursor() noexcept
{
	RECT screenRect;
	GetClientRect(windowHandle, &screenRect);
	MapWindowPoints(windowHandle, nullptr, reinterpret_cast<POINT*>(&screenRect), 2);
	ClipCursor(&screenRect);
}

void IOCursor::FreeMouseCursor() noexcept
{
	ClipCursor(nullptr);
}