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

#ifndef _IO_PLATFORM_WINDOW_H
#define _IO_PLATFORM_WINDOW_H

#include "IOConfig.h"

#include "IOWindowCallbacks.h"
#include "IOKeyboardMappings.h"
#include "IOKeyboardActions.h"
#include "IOMouseButtons.h"
#include "IOMouseActions.h"

#include <string_view>
#include <memory>

class IOPlatformWindow
{
public:
	IOPlatformWindow() = default;
	virtual ~IOPlatformWindow() noexcept = 0;

	static IOPlatformWindow* CreateInstance() noexcept;
	
	virtual bool Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept = 0;
	virtual void Close() noexcept = 0;

	virtual void ProcessEvents() noexcept = 0;

	virtual void EnableRawMouseInput() noexcept = 0;
	virtual void DisableRawMouseInput() noexcept = 0;

	virtual void EnableMouseCursor() noexcept = 0;
	virtual void DisableMouseCursor() noexcept = 0;

	virtual void EnableAutorepeat() noexcept = 0;
	virtual void DisableAutorepeat() noexcept = 0;

	void OnResize(IOWindowResizeCallbackFunction windowResizeCallbackFunction) noexcept;
	void OnMove(IOWindowMoveCallbackFunction windowMoveCallbackFunction) noexcept;
	void OnClose(IOWindowCloseCallbackFunction windowCloseCallbackFunction) noexcept;

	void OnKeyboardInput(IOKeyboardInputCallbackFunction keyboardInputCallbackFunction) noexcept;
	void OnMouseInput(IOMouseInputCallbackFunction mouseInputCallbackFunction) noexcept;
	void OnMouseMove(IOMouseMoveCallbackFunction mouseMoveCallbackFunction) noexcept;
	void OnRawMouseMove(IORawMouseMoveCallbackFunction rawMouseMoveCallbackFunction) noexcept;

	void OnMouseEnter(IOMouseEnterCallbackFunction mouseEnterCallbackFunction) noexcept;

	void OnMouseScroll(IOMouseScrollCallbackFunction mouseScrollCallbackFunction) noexcept;

	virtual bool CreateContext() noexcept = 0;
	virtual bool DestroyContext() noexcept = 0;
	virtual void SwapBuffers() noexcept = 0;

	virtual void GetTitle(char *pWindowTitle) noexcept = 0;
	virtual void GetResolution(unsigned long *pWindowScreenWidth, unsigned long *pWindowScreenHeight) noexcept = 0;
	virtual void GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept = 0;
protected:
	IOWindowResizeCallbackFunction resizeCallback;
	IOWindowMoveCallbackFunction moveCallback;
	IOWindowCloseCallbackFunction closeCallback;

	IOKeyboardInputCallbackFunction keyboardInputCallback;
	IOMouseInputCallbackFunction mouseInputCallback;
	IOMouseMoveCallbackFunction mouseMoveCallback;
	IORawMouseMoveCallbackFunction rawMouseMoveCallback;

	IOMouseEnterCallbackFunction mouseEnterCallback;

	IOMouseScrollCallbackFunction mouseScrollCallback;
};

#endif