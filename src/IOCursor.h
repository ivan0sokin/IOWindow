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

#ifndef _IO_CURSOR_H
#define _IO_CURSOR_H

#include <Windows.h>

class IOCursor
{
	friend class IOWindow;
public:
	IOCursor() = default;
	IOCursor(HWND windowHandle) noexcept;
	IOCursor(IOCursor const &other);
	~IOCursor() = default;

	IOCursor& operator=(IOCursor const &other) noexcept;

	void Enable() noexcept;
	void Disable() noexcept;
	bool IsEnabled() const noexcept;
private:
	bool isEnabled = true;

	HWND windowHandle;

	void Show() noexcept;
	void Hide() noexcept;
	void Confine() noexcept;
	void Free() noexcept;
};

#endif