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

#include "IOWindowExtendedClass.h"
#include "IOWindowHandle.h"
#include "IOInput.h"

#include <cassert>

class IOWindow
{
public:
	IOWindow() noexcept;
	IOWindow(const IOWindow &other) = delete;
	IOWindow(IOWindow &&other) = delete;
	~IOWindow() noexcept;

	IOWindow& operator=(const IOWindow &other) = delete;
	IOWindow& operator=(IOWindow &&other) = delete;

	bool MakeWindow(std::string_view windowTitle, unsigned long screenWidth, unsigned long screenHeight) noexcept;
	void CloseWindow() noexcept;
	
	void EnableMouseCursor() noexcept;
	void DisableMouseCursor() noexcept;
	bool IsMouseCursorEnabled() const noexcept;

	bool ShouldBeClosed() const noexcept;
	void PollWindowMessages() noexcept;

	void SetKeyboardInput(std::shared_ptr<IOKeyboard> const &keyboardInput) noexcept;
	void SetMouseInput(std::shared_ptr<IOMouse> const &mouseInput) noexcept;

	void EnableRawMouseInput() noexcept;
	void DisableRawMouseInput() noexcept;

	void GetWindowTitle(char *pWindowTitle) noexcept;
	void GetWindowScreenResolution(unsigned long *pWindowScreenWidth, unsigned long *pWindowScreenHeight) noexcept;
	void GetWindowPosition(long *pWindowPosX, long *pWindowPosY) noexcept;

	void SetWindowTitle(std::string_view windowTitle) noexcept;

	HWND GetWindowHandle() const noexcept;
	HINSTANCE GetWindowInstanceHandle() const noexcept;

	std::string const& GetLastError() noexcept;
private:
	std::unique_ptr<IOWindowExtendedClass> extendedClass;
	std::unique_ptr<IOWindowHandle> handle;
	std::unique_ptr<IOInput> input;

	bool shouldBeClosed = false;
	bool isMouseCursorEnabled = true;

	std::string lastError;

	void ShowMouseCursor() noexcept;
	void HideMouseCursor() noexcept;
	void ConfineMouseCursor() noexcept;
	void FreeMouseCursor() noexcept;

	static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static WPARAM MapLeftRightKeys(WPARAM wParam, LPARAM lParam) noexcept;
	bool IsCursorInScreenBounds(unsigned long cursorPosX, unsigned long cursorPosY) noexcept;
};

#endif