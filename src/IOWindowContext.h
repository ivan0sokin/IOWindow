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

#ifndef _IO_WINDOW_OPENGL_CONTEXT_H
#define _IO_WINDOW_OPENGL_CONTEXT_H

#pragma comment(lib, "opengl32.lib")

#include <Windows.h>

class IOWindowContext
{
public:
	IOWindowContext() noexcept;
	IOWindowContext(HWND hWnd) noexcept;
	IOWindowContext(IOWindowContext const &other) noexcept;
	IOWindowContext(IOWindowContext &&other) noexcept;
	~IOWindowContext() noexcept;

	bool CreateOpenGLContext() noexcept;
	bool DestroyOpenGLContext() noexcept;

	void SwapBuffers() noexcept;

	IOWindowContext& operator=(IOWindowContext const &other) noexcept;
	IOWindowContext& operator=(IOWindowContext &&other) noexcept;
private:
	HWND hWnd;

	bool SetPixelFormat() noexcept;
};

#endif