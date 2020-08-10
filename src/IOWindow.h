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

#ifndef _IO_WINDOW_H
#define _IO_WINDOW_H

#include "IOPlatformWindow.h"

class IOWindow
{
public:
	IOWindow() noexcept;
	IOWindow(const IOWindow &other) = delete;
	IOWindow(IOWindow &&other) = delete;
	~IOWindow() noexcept;

	bool Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept;
	void Close() noexcept;

	void ProcessEvents() noexcept;

	void EnableRawMouseInput() noexcept;
	void DisableRawMouseInput() noexcept;

	void EnableMouseCursor() noexcept;
	void DisableMouseCursor() noexcept;

	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;

	void OnResize(IOWindowResizeCallbackFunction windowResizeCallbackFunction) noexcept;
	void OnMove(IOWindowMoveCallbackFunction windowMoveCallbackFunction) noexcept;
	void OnClose(IOWindowCloseCallbackFunction windowCloseCallbackFunction) noexcept;

	void OnKeyboardInput(IOKeyboardInputCallbackFunction keyboardInputCallbackFunction) noexcept;
	void OnMouseInput(IOMouseInputCallbackFunction mouseInputCallbackFunction) noexcept;
	void OnMouseMove(IOMouseMoveCallbackFunction mouseMoveCallbackFunction) noexcept;
	void OnRawMouseMove(IORawMouseMoveCallbackFunction rawMouseMoveCallbackFunction) noexcept;

	void OnMouseEnter(IOMouseEnterCallbackFunction mouseEnterCallbackFunction) noexcept;

	void OnMouseScroll(IOMouseScrollCallbackFunction mouseScrollCallbackFunction) noexcept;

	bool CreateContext() noexcept;
	bool DestroyContext() noexcept;
	void SwapBuffers() noexcept;

	void GetTitle(char *pWindowTitle) noexcept;
	void GetResolution(unsigned long *pWindowWidth, unsigned long *pWindowHeight) noexcept;
	void GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept;

	IOWindow& operator=(const IOWindow &other) = delete;
	IOWindow& operator=(IOWindow &&other) = delete;

	std::shared_ptr<IOPlatformWindow> const& GetPlatformWindow() noexcept;
private:
	std::shared_ptr<IOPlatformWindow> platformWindow;
};

#endif