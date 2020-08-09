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

#ifndef _IO_WIN32_WINDOW_CLASS_EX
#define _IO_WIN32_WINDOW_CLASS_EX

#ifdef _WIN32
#include <Windows.h>

class IOWin32WindowExtendedClass
{
public:
	IOWin32WindowExtendedClass() = default;
	IOWin32WindowExtendedClass(const IOWin32WindowExtendedClass &other) = delete;
	IOWin32WindowExtendedClass(IOWin32WindowExtendedClass &&other) = delete;
	~IOWin32WindowExtendedClass() noexcept;

	IOWin32WindowExtendedClass& operator=(const IOWin32WindowExtendedClass &other) = delete;
	IOWin32WindowExtendedClass& operator=(IOWin32WindowExtendedClass &&other) = delete;

	bool Create(WNDPROC WndProc) noexcept;
	bool Destroy() noexcept;

	char const* GetWindowClassExName() const noexcept;
private:
	static constexpr char const* IO_WINDOW_CLASS_EX_NAME = "IOWin32WindowExtendedClass";
};
#endif

#endif