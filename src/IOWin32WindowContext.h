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

#ifndef _IO_WIN32_WINDOW_CONTEXT_H
#define _IO_WIN32_WINDOW_CONTEXT_H

#pragma comment(lib, "opengl32.lib")

#include <Windows.h>

class IOWin32WindowContext
{
public:
	IOWin32WindowContext() noexcept;
	IOWin32WindowContext(HWND hWnd) noexcept;
	IOWin32WindowContext(IOWin32WindowContext const &other) noexcept;
	IOWin32WindowContext(IOWin32WindowContext &&other) noexcept;
	~IOWin32WindowContext() noexcept;

	bool Create() noexcept;
	bool Destroy() noexcept;

	bool MakeCurrent() noexcept;
	bool Release() noexcept;

	void SwapBuffers() noexcept;

	IOWin32WindowContext& operator=(IOWin32WindowContext const &other) noexcept;
	IOWin32WindowContext& operator=(IOWin32WindowContext &&other) noexcept;
private:
	HWND windowHandle;
	HGLRC renderingContextHandle;

	bool SetPixelFormat() noexcept;
};

#endif