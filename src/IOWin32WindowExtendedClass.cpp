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

#include "IOWin32WindowExtendedClass.h"

#ifdef _WIN32
IOWin32WindowExtendedClass::~IOWin32WindowExtendedClass() noexcept
{
	this->Destroy();
}

void IOWin32WindowExtendedClass::Destroy() noexcept
{
	UnregisterClass(IO_WINDOW_CLASS_EX_NAME, GetModuleHandle(nullptr));
}

bool IOWin32WindowExtendedClass::Create(WNDPROC WndProc) noexcept
{
	WNDCLASSEX windowClassEx;
	ZeroMemory(&windowClassEx, sizeof(WNDCLASSEX));

	windowClassEx.cbSize = sizeof(WNDCLASSEX);
	windowClassEx.style = CS_OWNDC;
	windowClassEx.lpfnWndProc = WndProc;
	windowClassEx.cbClsExtra = 0;
	windowClassEx.cbWndExtra = 0;
	windowClassEx.hInstance = GetModuleHandle(nullptr);
	windowClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClassEx.hbrBackground = nullptr;
	windowClassEx.lpszMenuName = nullptr;
	windowClassEx.lpszClassName = IO_WINDOW_CLASS_EX_NAME;
	windowClassEx.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&windowClassEx))
		return false;

	return true;
}

char const* IOWin32WindowExtendedClass::GetWindowClassExName() const noexcept
{
	return this->IO_WINDOW_CLASS_EX_NAME;
}
#endif