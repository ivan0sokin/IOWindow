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

#ifndef _IO_WIN32_WINDOW_H
#define _IO_WIN32_WINDOW_H

#include "IOPlatformWindow.h"

#ifndef _WIN32
class IOWin32Window : public IOPlatformWindow
{
public:
	IOWin32Window() noexcept = default;
	~IOWin32Window() noexcept override { return; };

	bool Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept override { return false; };
	void Close() noexcept override { return; };

	void ProcessEvents() noexcept override { return; };

	void EnableRawMouseInput() noexcept override { return; };
	void DisableRawMouseInput() noexcept override { return; };

	void EnableMouseCursor() noexcept override { return; };
	void DisableMouseCursor() noexcept override { return; };

	void EnableAutorepeat() noexcept override { return; };
	void DisableAutorepeat() noexcept override { return; };

	bool CreateContext() noexcept override { return false; };
	bool DestroyContext() noexcept override { return false; };
	void SwapBuffers() noexcept override { return; };

	void GetTitle(char *pWindowTitle) noexcept override { return; };
	void GetResolution(unsigned long *pWindowScreenWidth, unsigned long *pWindowScreenHeight) noexcept override { return; };
	void GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept override { return; };
};
#endif

#ifdef _WIN32

#include "IOWin32WindowHandle.h"
#include "IOWin32WindowExtendedClass.h"
#include "IOWin32WindowContext.h"
#include "IOWin32Cursor.h"

#include <vector>
#include <array>

class IOWin32Window : public IOPlatformWindow
{
public:
	IOWin32Window() noexcept;
	IOWin32Window(const IOWin32Window &other) = delete;
	IOWin32Window(IOWin32Window &&other) = delete;
	~IOWin32Window() noexcept override;

	bool Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept override;
	bool Close() noexcept override;

	void ProcessEvents() noexcept override;

	void EnableRawMouseInput() noexcept override;
	void DisableRawMouseInput() noexcept override;

	void EnableMouseCursor() noexcept override;
	void DisableMouseCursor() noexcept override;

	void EnableAutorepeat() noexcept override;
	void DisableAutorepeat() noexcept override;

	bool CreateContext() noexcept override;
	bool DestroyContext() noexcept override;
	void SwapBuffers() noexcept override;

	void GetTitle(char *pWindowTitle) noexcept override;
	void GetResolution(unsigned long *pWindowWidth, unsigned long *pWindowHeight) noexcept override;
	void GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept override;

	HWND GetWindowHandle() noexcept;
private:
	void FillKeyCodes() noexcept;

	static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static WPARAM MapLeftRightKeys(WPARAM wParam, LPARAM lParam) noexcept;
	bool IsCursorInScreenBounds(unsigned long cursorPosX, unsigned long cursorPosY) noexcept;
private:
	std::unique_ptr<IOWin32WindowExtendedClass> extendedClass;
	std::unique_ptr<IOWin32WindowHandle> handle;
	std::unique_ptr<IOWin32WindowContext> context;
	std::unique_ptr<IOWin32Cursor> cursor;

	bool isAutorepeatEnabled = false;

	std::array<unsigned, 256> keyCodes;
	std::vector<BYTE> rawBuffer;
};

#endif

#endif