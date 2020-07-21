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
	this->input = std::make_unique<IOInput>();
}

IOWindow::~IOWindow() noexcept
{
	this->CloseWindow();
}

void IOWindow::CloseWindow() noexcept
{
	this->EnableMouseCursor();

	handle->DestroyWindowHandle();
	extendedClass->DestroyWindowClassEx();
}

void IOWindow::EnableMouseCursor() noexcept
{
	isMouseCursorEnabled = true;

	this->ShowMouseCursor();
	this->FreeMouseCursor();
}

void IOWindow::DisableMouseCursor() noexcept
{
	isMouseCursorEnabled = false;

	this->HideMouseCursor();
	this->ConfineMouseCursor();
}

void IOWindow::ShowMouseCursor() noexcept
{
	while (ShowCursor(TRUE) < 0);
}

void IOWindow::HideMouseCursor() noexcept
{
	while (ShowCursor(FALSE) >= 0);
}

void IOWindow::ConfineMouseCursor() noexcept
{
	RECT screenRect;
	GetClientRect(handle->GetWindowHandle(), &screenRect);
	MapWindowPoints(handle->GetWindowHandle(), nullptr, reinterpret_cast<POINT*>(&screenRect), 2);
	ClipCursor(&screenRect);
}

void IOWindow::FreeMouseCursor() noexcept
{
	ClipCursor(nullptr);
}

bool IOWindow::IsMouseCursorEnabled() const noexcept
{
	return this->isMouseCursorEnabled;
}

bool IOWindow::MakeWindow(std::string_view windowTitle, unsigned long screenWidth, unsigned long screenHeight) noexcept
{
	if (!extendedClass->MakeWindowClassEx(IOWindow::WndProcSetup))
	{
		lastError = "[IOWindow]: Failed to make IOWindowClassEx";
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
		lastError = "[IOWindow]: Failed to make IOWindowHandle";
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

void IOWindow::SetKeyboardInput(std::shared_ptr<IOKeyboard> const &keyboardInput) noexcept
{
	input->SetKeyboardInput(keyboardInput);
}

void IOWindow::SetMouseInput(std::shared_ptr<IOMouse> const &mouseInput) noexcept
{
	input->SetMouseInput(mouseInput);
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
			if (!input->HasKeyboard())
				break;

			input->GetKeyboard()->ClearKeyStates();

			break;
		}
		case WM_ACTIVATE:
		{
			if (!this->IsMouseCursorEnabled())
			{
				if (wParam & WA_ACTIVE)
				{
					this->ConfineMouseCursor();
					this->HideMouseCursor();
				}
				else
				{
					this->FreeMouseCursor();
					this->ShowMouseCursor();
				}
			}

			break;
		}
		case WM_KEYDOWN:
		{
			if (!input->HasKeyboard())
				break;
			
			case WM_SYSKEYDOWN:
			{
				if (!(lParam & 0x40000000) || input->GetKeyboard()->IsAutorepeatEnabled())
				{
					wParam = IOWindow::MapLeftRightKeys(wParam, lParam);
					input->GetKeyboard()->OnKeyPressed(static_cast<unsigned char>(wParam));
				}
			}

			break;
		}
		case WM_KEYUP:
		{
			if (!input->HasKeyboard())
				break;

			case WM_SYSKEYUP:
			{
				wParam = IOWindow::MapLeftRightKeys(wParam, lParam);
				input->GetKeyboard()->OnKeyReleased(static_cast<unsigned char>(wParam));
			}

			break;
		}
		case WM_MOUSEMOVE:
		{
			if (!input->HasMouse())
				break;

			if (!this->IsMouseCursorEnabled())
			{
				if (input->GetMouse()->IsInWindow())
				{
					SetCapture(hWnd);
					input->GetMouse()->OnMouseEnter();

					this->ShowMouseCursor();
				}
			}

			const POINTS mouseCursorPosition = MAKEPOINTS(lParam);
			if (this->IsCursorInScreenBounds(mouseCursorPosition.x, mouseCursorPosition.y))
			{
				input->GetMouse()->OnMouseMove(mouseCursorPosition.x, mouseCursorPosition.y);
				if (!input->GetMouse()->IsInWindow())
				{
					SetCapture(hWnd);
					input->GetMouse()->OnMouseEnter();
				}
			}
			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					input->GetMouse()->OnMouseMove(mouseCursorPosition.x, mouseCursorPosition.y);
				}
				else
				{
					ReleaseCapture();
					input->GetMouse()->OnMouseLeave();
				}
			}

			break;
		}
		case WM_LBUTTONDOWN:
		{
			if (!input->HasMouse())
				break;

			SetForegroundWindow(hWnd);

			if (!this->IsMouseCursorEnabled())
			{
				this->ConfineMouseCursor();
				this->HideMouseCursor();
			}

			input->GetMouse()->OnLeftPressed();

			break;
		}
		case WM_LBUTTONUP:
		{
			if (!input->HasMouse())
				break;

			input->GetMouse()->OnLeftReleased();

			const POINTS mosueCursorPosition = MAKEPOINTS(lParam);
			if (!this->IsCursorInScreenBounds(mosueCursorPosition.x, mosueCursorPosition.y))
			{
				ReleaseCapture();
				input->GetMouse()->OnMouseLeave();
			}

			break;
		}
		case WM_RBUTTONDOWN:
		{
			if (!input->HasMouse())
				break;

			input->GetMouse()->OnRightPressed();

			break;
		}
		case WM_RBUTTONUP:
		{
			if (!input->HasMouse())
				break;

			input->GetMouse()->OnRightReleased();

			POINTS mouseCursorPosition = MAKEPOINTS(lParam);
			if (!this->IsCursorInScreenBounds(mouseCursorPosition.x, mouseCursorPosition.y))
			{
				ReleaseCapture();
				input->GetMouse()->OnMouseLeave();
			}

			break;
		}
		case WM_MOUSEWHEEL:
		{
			if (!input->HasMouse())
				break;

			short wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			input->GetMouse()->OnWheelDelta(wheelDelta);

			break;
		}
		case WM_INPUT:
		{
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	return 0;
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
		if (GetWindowText(handle->GetWindowHandle(), pWindowTitle, static_cast<int>(titleLength) + 1) == 0)
			lastError = "[IOWindow]: Failed to get window title";
	}
}

void IOWindow::GetWindowScreenResolution(unsigned long *pWindowScreenWidth, unsigned long *pWindowScreenHeight) noexcept
{
	RECT screenRect;
	if (!GetClientRect(handle->GetWindowHandle(), &screenRect))
	{
		lastError = "[IOWindow]: Failed to get screen resolution";
		return;
	}
	
	if (pWindowScreenWidth != nullptr)
		*pWindowScreenWidth = screenRect.right;
	if (pWindowScreenHeight != nullptr)
		*pWindowScreenHeight = screenRect.bottom;
}

void IOWindow::GetWindowPosition(long *pWindowPosX, long *pWindowPosY) noexcept
{
	RECT windowRect;
	if (!GetWindowRect(handle->GetWindowHandle(), &windowRect))
	{
		lastError = "[IOWindow]: Failed to get window position";
		return;
	}

	if (pWindowPosX != nullptr)
		*pWindowPosX = windowRect.left;
	if (pWindowPosY != nullptr)
		*pWindowPosY = windowRect.top;
}

void IOWindow::SetWindowTitle(std::string_view windowTitle) noexcept
{
	if (!SetWindowText(handle->GetWindowHandle(), windowTitle.data()))
		lastError = "[IOWindow]: Failed to change window title";
}

std::string const& IOWindow::GetLastError() noexcept
{
	return this->lastError;
}