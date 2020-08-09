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

#include "IOLinuxWindow.h"

#ifdef __linux__
IOLinuxWindow::IOLinuxWindow() noexcept
{
	
}

IOLinuxWindow::~IOLinuxWindow() noexcept
{
	this->Close();
}

bool IOLinuxWindow::Close() noexcept
{
	if (window)
	{
		XUnmapWindow(display, window);
		XDestroyWindow(display, window);
		window = static_cast<Window>(0ul);
	}

	if (display != nullptr)
	{
		XCloseDisplay(display);
		display = nullptr;
	}

	return true;
}

bool IOLinuxWindow::Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept
{
	display = XOpenDisplay(nullptr);
	if (display == nullptr)
		return false;

	currentScreen = DefaultScreen(display);

	unsigned long blackPixel = BlackPixel(display, currentScreen);
	unsigned long whitePixel = WhitePixel(display, currentScreen);
	
	screen = ScreenOfDisplay(display, currentScreen);
	
	int x = (screen->width - windowWidth) / 2;
	int y = (screen->height - windowHeight) / 2;

	rootWindow = RootWindow(display, currentScreen);
	window = XCreateSimpleWindow(display, rootWindow, x, y, static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight), 0, whitePixel, blackPixel);
	if (!window)
		return false;

	XStoreName(display, window, windowTitle.data());
	XSetIconName(display, window, windowTitle.data());

	XMapWindow(display, window);

	return true;
}

void IOLinuxWindow::ProcessEvents() noexcept
{
	XEvent event;
	while (XPending(display) != 0)
	{
		XNextEvent(display, &event);
	}
}

void IOLinuxWindow::EnableRawMouseInput() noexcept
{
	return;
}
void IOLinuxWindow::DisableRawMouseInput() noexcept
{
	return;
}

void IOLinuxWindow::EnableMouseCursor() noexcept
{
	return;
}
void IOLinuxWindow::DisableMouseCursor() noexcept
{
	return;
}

void IOLinuxWindow::EnableAutorepeat() noexcept
{
	return;
}
void IOLinuxWindow::DisableAutorepeat() noexcept
{
	return;
}

bool IOLinuxWindow::CreateContext() noexcept
{
	return false;
}
bool IOLinuxWindow::DestroyContext() noexcept
{
	return false;
}
void IOLinuxWindow::SwapBuffers() noexcept
{
	return;
}

void IOLinuxWindow::GetTitle(char *pWindowTitle) noexcept
{
	return;
}

void IOLinuxWindow::GetResolution(unsigned long *pWindowScreenWidth, unsigned long *pWindowScreenHeight) noexcept
{
	XWindowAttributes attributes = {};
	XGetWindowAttributes(display, window, &attributes);

	if (pWindowScreenWidth != nullptr)
		*pWindowScreenWidth = static_cast<unsigned long>(attributes.width);
	if (pWindowScreenHeight != nullptr)
		*pWindowScreenHeight = static_cast<unsigned long>(attributes.height);
}

void IOLinuxWindow::GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept
{
	int x, y;
	Window trash;
	XTranslateCoordinates(display, window, rootWindow, 0, 0, &x, &y, &trash);

	if (pWindowPosX != nullptr)
		*pWindowPosX = static_cast<long>(x);
	if (pWindowPosY != nullptr)
		*pWindowPosY = static_cast<long>(y);
}

#endif