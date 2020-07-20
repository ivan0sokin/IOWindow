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

#include "IOWindow.h"

IOWindow::IOWindow() noexcept
{
	this->extendedClass = std::make_unique<IOWindowExtendedClass>();
	this->handle = std::make_unique<IOWindowHandle>();
}

IOWindow::~IOWindow() noexcept
{
	this->CloseWindow();
}

void IOWindow::CloseWindow() noexcept
{
	handle->DestroyWindowHandle();
	extendedClass->DestroyWindowClassEx();
}

bool IOWindow::MakeWindow(std::string_view windowTitle, unsigned long screenWidth, unsigned long screenHeight) noexcept
{
	if (!extendedClass->MakeWindowClassEx(IOWindow::WndProcSetup))
	{
		lastError = "[IOWindow.cpp]: Failed to make IOWindowClassEx";
		return false;
	}
	
	if (!handle->MakeWindowHandle
	(
		0,
		extendedClass->GetWindowClassExName(),
		windowTitle,
		screenWidth,
		screenHeight,
		extendedClass->GetWindowInstanceHandle(),
		this
	))
	{
		lastError = "[IOWindow.cpp]: Failed to make IOWindowHandle";
		return false;
	}

	ShowWindow(handle->GetWindowHandle(), SW_SHOWDEFAULT);

	return true;
}

bool IOWindow::ShouldBeClosed() const noexcept
{
	return this->shouldBeClosed;
}

void IOWindow::PollWindowMessages() noexcept
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			shouldBeClosed = true;
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void IOWindow::SetKeyboardInput(std::shared_ptr<IOKeyboard>& keyboardInput) noexcept
{
	keyboard = keyboardInput;
}

LRESULT IOWindow::WndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (uMsg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		IOWindow* const pWnd = static_cast<IOWindow*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&IOWindow::WndProcThunk));

		return pWnd->WndProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT IOWindow::WndProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	IOWindow* const pWnd = reinterpret_cast<IOWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->WndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT IOWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_KILLFOCUS:
		{
			if (keyboard == nullptr)
				break;

			keyboard->ClearKeyStates();

			break;
		}
		case WM_KEYDOWN:
		{
			if (keyboard == nullptr)
				break;
			
			case WM_SYSKEYDOWN:
			{
				if (!(lParam & 0x40000000) || keyboard->IsAutorepeatEnabled())
				{
					wParam = IOWindow::MapLeftRightKeys(wParam, lParam);
					keyboard->OnKeyPressed(static_cast<unsigned char>(wParam));
				}
			}

			break;
		}
		case WM_KEYUP:
		{
			if (keyboard == nullptr)
				break;

			case WM_SYSKEYUP:
			{
				wParam = IOWindow::MapLeftRightKeys(wParam, lParam);
				keyboard->OnKeyReleased(static_cast<unsigned char>(wParam));
			}

			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

WPARAM IOWindow::MapLeftRightKeys(WPARAM wParam, LPARAM lParam) noexcept
{
	switch (wParam)
	{
		case 0x10:
		{
			UINT scancode = (lParam & 0x00ff0000) >> 16;
			return MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
		}
		case 0x11:
		{
			bool extendedFlag = (lParam & 0x01000000) != 0;
			return extendedFlag ? 0xA3 : 0xA2;
		}
		case 0x12:
		{
			bool extendedFlag = (lParam & 0x01000000) != 0;
			return extendedFlag ? 0xA5 : 0xA4;
		}
	}

	return wParam;
}

bool IOWindow::IsCursorInScreenBounds(unsigned long cursorPosX, unsigned long cursorPosY) noexcept
{
	unsigned long screenWidth, screenHeight;
	this->GetWindowScreenResolution(&screenWidth, &screenHeight);

	return
	(
		(
			cursorPosX >= 0 && cursorPosX <= screenWidth &&
			cursorPosY >= 0 && cursorPosY <= screenHeight
		) ? true : false
	);
}

void IOWindow::GetWindowTitle(char *pWindowTitle) noexcept
{
	if (pWindowTitle != nullptr)
	{
		size_t titleLength = static_cast<size_t>(GetWindowTextLength(handle->GetWindowHandle()));
		GetWindowText(handle->GetWindowHandle(), pWindowTitle, static_cast<int>(titleLength) + 1);
	}
}

void IOWindow::GetWindowScreenResolution(unsigned long *pWindowScreenWidth, unsigned long *pWindowScreenHeight) noexcept
{
	RECT screenRect;
	GetClientRect(handle->GetWindowHandle(), &screenRect);
	
	if (pWindowScreenWidth != nullptr)
		*pWindowScreenWidth = screenRect.right;
	if (pWindowScreenHeight != nullptr)
		*pWindowScreenHeight = screenRect.bottom;
}

void IOWindow::GetWindowPosition(long *pWindowPosX, long *pWindowPosY) noexcept
{
	RECT windowRect;
	GetWindowRect(handle->GetWindowHandle(), &windowRect);

	if (pWindowPosX != nullptr)
		*pWindowPosX = windowRect.left;
	if (pWindowPosY != nullptr)
		*pWindowPosY = windowRect.top;
}

void IOWindow::SetWindowTitle(std::string_view windowTitle) noexcept
{
	if (SetWindowText(handle->GetWindowHandle(), windowTitle.data()) == 0)
		lastError = "IOWindow: failed to change window title";
}

std::string const& IOWindow::GetLastError() noexcept
{
	return this->lastError;
}