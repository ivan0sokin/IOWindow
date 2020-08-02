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

#include "IOPlatformWindow.h"
#include "IOWin32Window.h"
#include "IOLinuxWindow.h"

IOPlatformWindow::~IOPlatformWindow() noexcept
{
	return;
}

IOPlatformWindow* IOPlatformWindow::CreateInstance() noexcept
{
	IOConfig config = IOConfig();

	switch (config.GetPlatform())
	{
	case IOConfig::Platform::Windows:
		return new IOWin32Window();
	case IOConfig::Platform::Linux:
		return new IOLinuxWindow();
	default:
		return nullptr;
	}
}

void IOPlatformWindow::OnResize(IOWindowResizeCallbackFunction windowResizeCallbackFunction) noexcept
{
	resizeCallback = windowResizeCallbackFunction;
}

void IOPlatformWindow::OnMove(IOWindowMoveCallbackFunction windowMoveCallbackFunction) noexcept
{
	moveCallback = windowMoveCallbackFunction;
}

void IOPlatformWindow::OnClose(IOWindowCloseCallbackFunction windowCloseCallbackFunction) noexcept
{
	closeCallback = windowCloseCallbackFunction;
}

void IOPlatformWindow::OnKeyboardInput(IOKeyboardInputCallbackFunction keyboardInputCallbackFunction) noexcept
{
	keyboardInputCallback = keyboardInputCallbackFunction;
}

void IOPlatformWindow::OnMouseInput(IOMouseInputCallbackFunction mouseInputCallbackFunction) noexcept
{
	mouseInputCallback = mouseInputCallbackFunction;
}

void IOPlatformWindow::OnMouseMove(IOMouseMoveCallbackFunction mouseMoveCallbackFunction) noexcept
{
	mouseMoveCallback = mouseMoveCallbackFunction;
}

void IOPlatformWindow::OnRawMouseMove(IORawMouseMoveCallbackFunction rawMouseMoveCallbackFunction) noexcept
{
	rawMouseMoveCallback = rawMouseMoveCallbackFunction;
}

void IOPlatformWindow::OnMouseEnter(IOMouseEnterCallbackFunction mouseEnterCallbackFunction) noexcept
{
	mouseEnterCallback = mouseEnterCallbackFunction;
}

void IOPlatformWindow::OnMouseScroll(IOMouseScrollCallbackFunction mouseScrollCallbackFunction) noexcept
{
	mouseScrollCallback = mouseScrollCallbackFunction;
}