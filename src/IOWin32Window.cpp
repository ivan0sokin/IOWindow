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

#include "IOWin32Window.h"

#ifdef _WIN32
IOWin32Window::IOWin32Window() noexcept
{
	this->extendedClass = std::make_unique<IOWin32WindowExtendedClass>();
	this->handle = std::make_unique<IOWin32WindowHandle>();
	this->context = std::make_unique<IOWin32WindowContext>(handle->GetWindowHandle());

	this->FillKeyCodes();
}

void IOWin32Window::FillKeyCodes() noexcept
{
	memset(keyCodes.data(), IO_KEY_UNKNOWN, sizeof(unsigned char) * keyCodes.size());

	keyCodes[0x08] = IO_KEY_BACKSPACE;
	keyCodes[0x09] = IO_KEY_TAB;
	keyCodes[0x0D] = IO_KEY_ENTER;
	keyCodes[0x10] = IO_KEY_SHIFT;
	keyCodes[0x11] = IO_KEY_CTRL;
	keyCodes[0x12] = IO_KEY_ALT;
	keyCodes[0x13] = IO_KEY_PAUSE;
	keyCodes[0x14] = IO_KEY_CAPSLOCK;
	keyCodes[0x1B] = IO_KEY_ESCAPE;
	keyCodes[0x20] = IO_KEY_SPACE;
	keyCodes[0x21] = IO_KEY_PAGEUP;
	keyCodes[0x22] = IO_KEY_PAGEDOWN;
	keyCodes[0x23] = IO_KEY_END;
	keyCodes[0x24] = IO_KEY_HOME;
	keyCodes[0x25] = IO_KEY_LEFTARROW;
	keyCodes[0x26] = IO_KEY_UPARROW;
	keyCodes[0x27] = IO_KEY_RIGHTARROW;
	keyCodes[0x28] = IO_KEY_DOWNARROW;
	keyCodes[0x2C] = IO_KEY_PRINTSCREEN;
	keyCodes[0x2D] = IO_KEY_INSERT;
	keyCodes[0x2E] = IO_KEY_DELETE;
	keyCodes[0x30] = IO_KEY_0;
	keyCodes[0x31] = IO_KEY_1;
	keyCodes[0x32] = IO_KEY_2;
	keyCodes[0x33] = IO_KEY_3;
	keyCodes[0x34] = IO_KEY_4;
	keyCodes[0x35] = IO_KEY_5;
	keyCodes[0x36] = IO_KEY_6;
	keyCodes[0x37] = IO_KEY_7;
	keyCodes[0x38] = IO_KEY_8;
	keyCodes[0x39] = IO_KEY_9;
	keyCodes[0x41] = IO_KEY_A;
	keyCodes[0x42] = IO_KEY_B;
	keyCodes[0x43] = IO_KEY_C;
	keyCodes[0x44] = IO_KEY_D;
	keyCodes[0x45] = IO_KEY_E;
	keyCodes[0x46] = IO_KEY_F;
	keyCodes[0x47] = IO_KEY_G;
	keyCodes[0x48] = IO_KEY_H;
	keyCodes[0x49] = IO_KEY_I;
	keyCodes[0x4A] = IO_KEY_J;
	keyCodes[0x4B] = IO_KEY_K;
	keyCodes[0x4C] = IO_KEY_L;
	keyCodes[0x4D] = IO_KEY_M;
	keyCodes[0x4E] = IO_KEY_N;
	keyCodes[0x4F] = IO_KEY_O;
	keyCodes[0x50] = IO_KEY_P;
	keyCodes[0x51] = IO_KEY_Q;
	keyCodes[0x52] = IO_KEY_R;
	keyCodes[0x53] = IO_KEY_S;
	keyCodes[0x54] = IO_KEY_T;
	keyCodes[0x55] = IO_KEY_U;
	keyCodes[0x56] = IO_KEY_V;
	keyCodes[0x57] = IO_KEY_W;
	keyCodes[0x58] = IO_KEY_X;
	keyCodes[0x59] = IO_KEY_Y;
	keyCodes[0x5A] = IO_KEY_Z;
	keyCodes[0x60] = IO_KEY_NUMPAD_0;
	keyCodes[0x61] = IO_KEY_NUMPAD_1;
	keyCodes[0x62] = IO_KEY_NUMPAD_2;
	keyCodes[0x63] = IO_KEY_NUMPAD_3;
	keyCodes[0x64] = IO_KEY_NUMPAD_4;
	keyCodes[0x65] = IO_KEY_NUMPAD_5;
	keyCodes[0x66] = IO_KEY_NUMPAD_6;
	keyCodes[0x67] = IO_KEY_NUMPAD_7;
	keyCodes[0x68] = IO_KEY_NUMPAD_8;
	keyCodes[0x69] = IO_KEY_NUMPAD_9;
	keyCodes[0x6A] = IO_KEY_NUMPAD_MULTIPLY;
	keyCodes[0x6B] = IO_KEY_NUMPAD_ADD;
	keyCodes[0x6D] = IO_KEY_NUMPAD_SUBTRACT;
	keyCodes[0x6E] = IO_KEY_NUMPAD_DECIMAL;
	keyCodes[0x6F] = IO_KEY_NUMPAD_DIVIDE;
	keyCodes[0x70] = IO_KEY_F1;
	keyCodes[0x71] = IO_KEY_F2;
	keyCodes[0x72] = IO_KEY_F3;
	keyCodes[0x73] = IO_KEY_F4;
	keyCodes[0x74] = IO_KEY_F5;
	keyCodes[0x75] = IO_KEY_F6;
	keyCodes[0x76] = IO_KEY_F7;
	keyCodes[0x77] = IO_KEY_F8;
	keyCodes[0x78] = IO_KEY_F9;
	keyCodes[0x79] = IO_KEY_F10;
	keyCodes[0x7A] = IO_KEY_F11;
	keyCodes[0x7B] = IO_KEY_F12;
	keyCodes[0x7C] = IO_KEY_F13;
	keyCodes[0x7D] = IO_KEY_F14;
	keyCodes[0x7E] = IO_KEY_F15;
	keyCodes[0x7F] = IO_KEY_F16;
	keyCodes[0x80] = IO_KEY_F17;
	keyCodes[0x81] = IO_KEY_F18;
	keyCodes[0x82] = IO_KEY_F19;
	keyCodes[0x83] = IO_KEY_F20;
	keyCodes[0x84] = IO_KEY_F21;
	keyCodes[0x85] = IO_KEY_F22;
	keyCodes[0x86] = IO_KEY_F23;
	keyCodes[0x87] = IO_KEY_F24;
	keyCodes[0x90] = IO_KEY_NUMLOCK;
	keyCodes[0x91] = IO_KEY_SCRLOCK;
	keyCodes[0x92] = IO_KEY_NUMPAD_EQUAL;
	keyCodes[0xA0] = IO_KEY_LEFTSHIFT;
	keyCodes[0xA1] = IO_KEY_RIGHTSHIFT;
	keyCodes[0xA2] = IO_KEY_LEFTCTRL;
	keyCodes[0xA3] = IO_KEY_RIGHTCTRL;
	keyCodes[0xA4] = IO_KEY_LEFTALT;
	keyCodes[0xA5] = IO_KEY_RIGHTALT;
	keyCodes[0xAD] = IO_KEY_VOLUME_MUTE;
	keyCodes[0xAE] = IO_KEY_VOLUME_DOWN;
	keyCodes[0xAF] = IO_KEY_VOLUME_UP;
	keyCodes[0xBA] = IO_KEY_SEMICOLON;
	keyCodes[0xBB] = IO_KEY_PLUS;
	keyCodes[0xBC] = IO_KEY_COMMA;
	keyCodes[0xBD] = IO_KEY_MINUS;
	keyCodes[0xBE] = IO_KEY_PERIOD;
	keyCodes[0xBF] = IO_KEY_SLASH;
	keyCodes[0xC0] = IO_KEY_GRAVE_ACCENT;
	keyCodes[0xDB] = IO_KEY_LEFT_BRACKET;
	keyCodes[0xDC] = IO_KEY_BACKSLASH;
	keyCodes[0xDD] = IO_KEY_RIGHT_BRACKET;
	keyCodes[0xDE] = IO_KEY_APOSTROPHE;
}

IOWin32Window::~IOWin32Window() noexcept
{
	this->Close();
}

bool IOWin32Window::Close() noexcept
{
	if (!handle->Destroy())
		return false;

	if (!extendedClass->Destroy())
		return false;

	return true;
}

bool IOWin32Window::Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept
{
	if (!extendedClass->Create(IOWin32Window::WndProcSetup))
		return false;

	if (!handle->Create
	(
		0,
		extendedClass->GetWindowClassExName(),
		windowTitle,
		windowWidth,
		windowHeight,
		this
	))
		return false;

	cursor = std::make_unique<IOWin32Cursor>(handle->GetWindowHandle());

	ShowWindow(handle->GetWindowHandle(), SW_SHOWDEFAULT);

	return true;
}

void IOWin32Window::ProcessEvents() noexcept
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void IOWin32Window::EnableRawMouseInput() noexcept
{
	RAWINPUTDEVICE rawMouseInput;
	rawMouseInput.usUsagePage = 0x01;
	rawMouseInput.usUsage = 0x02;
	rawMouseInput.dwFlags = 0;
	rawMouseInput.hwndTarget = handle->GetWindowHandle();

	RegisterRawInputDevices(&rawMouseInput, 1, sizeof(RAWINPUTDEVICE));
}

void IOWin32Window::DisableRawMouseInput() noexcept
{
	RAWINPUTDEVICE rawMouseInput;
	rawMouseInput.usUsagePage = 0x01;
	rawMouseInput.usUsage = 0x02;
	rawMouseInput.dwFlags = RIDEV_REMOVE;
	rawMouseInput.hwndTarget = nullptr;

	RegisterRawInputDevices(&rawMouseInput, 1, sizeof(RAWINPUTDEVICE));
}

void IOWin32Window::EnableMouseCursor() noexcept
{
	cursor->Enable();
}

void IOWin32Window::DisableMouseCursor() noexcept
{
	cursor->Disable();
}

void IOWin32Window::EnableAutorepeat() noexcept
{
	isAutorepeatEnabled = true;
}

void IOWin32Window::DisableAutorepeat() noexcept
{
	isAutorepeatEnabled = false;
}

bool IOWin32Window::CreateContext() noexcept
{
	return context->Create();
}

bool IOWin32Window::DestroyContext() noexcept
{
	return context->Destroy();
}

void IOWin32Window::SwapBuffers() noexcept
{
	context->SwapBuffers();
}

void IOWin32Window::GetTitle(char *pWindowTitle) noexcept
{
	if (pWindowTitle != nullptr)
	{
		size_t titleLength = static_cast<size_t>(GetWindowTextLength(handle->GetWindowHandle()));
		GetWindowText(handle->GetWindowHandle(), pWindowTitle, static_cast<int>(titleLength) + 1);
	}
}

void IOWin32Window::GetResolution(unsigned long *pWindowWidth, unsigned long *pWindowHeight) noexcept
{
	RECT rect;
	GetClientRect(handle->GetWindowHandle(), &rect);

	if (pWindowWidth != nullptr)
		*pWindowWidth = rect.right;
	if (pWindowHeight != nullptr)
		*pWindowHeight = rect.bottom;
}

void IOWin32Window::GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept
{
	RECT rect;
	GetClientRect(handle->GetWindowHandle(), &rect);

	if (pWindowPosX != nullptr)
	{
		ClientToScreen(handle->GetWindowHandle(), reinterpret_cast<POINT*>(&rect.left));
		*pWindowPosX = rect.left;
	}
	if (pWindowPosY != nullptr)
	{
		ClientToScreen(handle->GetWindowHandle(), reinterpret_cast<POINT*>(&rect.top));
		*pWindowPosY = rect.top;
	}
}

HWND IOWin32Window::GetWindowHandle() noexcept
{
	return handle->GetWindowHandle();
}

LRESULT IOWin32Window::WndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (uMsg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		IOWin32Window* const pWnd = static_cast<IOWin32Window*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&IOWin32Window::WndProcThunk));

		return pWnd->WndProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT IOWin32Window::WndProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	IOWin32Window* const pWnd = reinterpret_cast<IOWin32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->WndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT IOWin32Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			if (!closeCallback)
				break;

			closeCallback();

			break;
		}
		case WM_ACTIVATE:
		{
			if (!cursor->IsEnabled())
			{
				if (wParam & WA_ACTIVE)
				{
					cursor->Confine();
					cursor->Hide();
				}
				else
				{
					cursor->Free();
					cursor->Show();
				}
			}

			break;
		}
		case WM_SIZE:
		{
			if (!resizeCallback)
				break;

			short width = LOWORD(lParam);
			short height = HIWORD(lParam);

			resizeCallback(static_cast<unsigned long>(width), static_cast<unsigned long>(height));

			break;
		}
		case WM_MOVE:
		{
			if (!moveCallback)
				break;

			short x = LOWORD(lParam);
			short y = HIWORD(lParam);

			moveCallback(static_cast<long>(x), static_cast<long>(y));

			break;
		}
		case WM_KEYDOWN:
		{
			if (!keyboardInputCallback)
				break;

			case WM_SYSKEYDOWN:
			{
				if (!(lParam & 0x40000000) || isAutorepeatEnabled)
				{
					keyboardInputCallback(keyCodes[static_cast<size_t>(wParam)], static_cast<unsigned>(wParam), IO_KEY_PRESS);

					if (wParam == 0x10 || wParam == 0x11 || wParam == 0x12)
					{
						wParam = MapLeftRightKeys(wParam, lParam);
						keyboardInputCallback(keyCodes[static_cast<size_t>(wParam)], static_cast<unsigned>(wParam), IO_KEY_PRESS);
					}
				}
			}

			break;
		}
		case WM_KEYUP:
		{
			if (!keyboardInputCallback)
				break;

			case WM_SYSKEYUP:
			{
				keyboardInputCallback(keyCodes[static_cast<size_t>(wParam)], static_cast<unsigned>(wParam), IO_KEY_RELEASE);

				if (wParam == 0x10 || wParam == 0x11 || wParam == 0x12)
				{
					wParam = MapLeftRightKeys(wParam, lParam);
					keyboardInputCallback(keyCodes[static_cast<size_t>(wParam)], static_cast<unsigned>(wParam), IO_KEY_RELEASE);
				}
			}

			break;
		}
		case WM_LBUTTONDOWN:
		{
			if (!mouseInputCallback)
				break;

			SetForegroundWindow(hWnd);

			if (!cursor->IsEnabled())
			{
				cursor->Confine();
				cursor->Hide();
			}

			mouseInputCallback(IO_MOUSE_BUTTON_1, IO_MOUSE_BUTTON_PRESS);

			break;
		}
		case WM_LBUTTONUP:
		{
			if (!mouseInputCallback)
				break;

			mouseInputCallback(IO_MOUSE_BUTTON_1, IO_MOUSE_BUTTON_RELEASE);

			if (!mouseEnterCallback)
				break;

			POINTS const mouseCursorPosition = MAKEPOINTS(lParam);
			if (!this->IsCursorInScreenBounds(mouseCursorPosition.x, mouseCursorPosition.y))
			{
				ReleaseCapture();
				mouseEnterCallback(IO_MOUSE_LEAVE);
			}

			break;
		}
		case WM_RBUTTONDOWN:
		{
			if (!mouseInputCallback)
				break;

			mouseInputCallback(IO_MOUSE_BUTTON_2, IO_MOUSE_BUTTON_PRESS);

			break;
		}
		case WM_RBUTTONUP:
		{
			if (!mouseInputCallback)
				break;

			mouseInputCallback(IO_MOUSE_BUTTON_2, IO_MOUSE_BUTTON_RELEASE);

			if (!mouseEnterCallback)
				break;

			POINTS mouseCursorPosition = MAKEPOINTS(lParam);
			if (!this->IsCursorInScreenBounds(mouseCursorPosition.x, mouseCursorPosition.y))
			{
				ReleaseCapture();
				mouseEnterCallback(IO_MOUSE_LEAVE);
			}

			break;
		}
		case WM_MBUTTONDOWN:
		{
			if (!mouseInputCallback)
				break;

			mouseInputCallback(IO_MOUSE_BUTTON_3, IO_MOUSE_BUTTON_PRESS);

			break;
		}
		case WM_MBUTTONUP:
		{
			if (!mouseInputCallback)
				break;

			mouseInputCallback(IO_MOUSE_BUTTON_3, IO_MOUSE_BUTTON_RELEASE);

			if (!mouseEnterCallback)
				break;

			POINTS mouseCursorPosition = MAKEPOINTS(lParam);
			if (!this->IsCursorInScreenBounds(mouseCursorPosition.x, mouseCursorPosition.y))
			{
				ReleaseCapture();
				mouseEnterCallback(IO_MOUSE_LEAVE);
			}

			break;
		}
		case WM_XBUTTONDOWN:
		{
			if (!mouseInputCallback)
				break;
			
			unsigned button = IO_MOUSE_BUTTON_3 + static_cast<unsigned>(GET_XBUTTON_WPARAM(wParam));
			mouseInputCallback(button, IO_MOUSE_BUTTON_PRESS);

			break;
		}
		case WM_XBUTTONUP:
		{
			if (!mouseInputCallback)
				break;

			unsigned button = IO_MOUSE_BUTTON_3 + static_cast<unsigned>(GET_XBUTTON_WPARAM(wParam));
			mouseInputCallback(button, IO_MOUSE_BUTTON_PRESS);

			if (!mouseEnterCallback)
				break;

			POINTS mouseCursorPosition = MAKEPOINTS(lParam);
			if (!this->IsCursorInScreenBounds(mouseCursorPosition.x, mouseCursorPosition.y))
			{
				ReleaseCapture();
				mouseEnterCallback(IO_MOUSE_LEAVE);
			}

			break;
		}
		case WM_MOUSEMOVE:
		{
			if (!mouseMoveCallback)
				break;

			const POINTS mouseCursorPosition = MAKEPOINTS(lParam);

			/*if (!cursor->IsEnabled())
			{
				if (input->GetMouse()->IsInWindow())
				{
					SetCapture(hWnd);
					input->GetMouse()->OnMouseEnter();

					cursor->Hide();
				}
			}
		
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
			}*/

			break;
		}
		case WM_MOUSEWHEEL:
		{
			if (!mouseScrollCallback)
				break;

			short scrollDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			double offset = scrollDelta / static_cast<double>(WHEEL_DELTA);

			mouseScrollCallback(offset);

			break;
		}
		case WM_MOUSELEAVE:
		{
			if (!mouseEnterCallback)
				break;

			mouseEnterCallback(IO_MOUSE_LEAVE);

			break;
		}
		case WM_INPUT:
		{
			if (!rawMouseMoveCallback)
				break;

			unsigned int size = 0;
			if (GetRawInputData
			(
				reinterpret_cast<HRAWINPUT>(lParam),
				RID_INPUT,
				nullptr,
				&size,
				sizeof(RAWINPUTHEADER)) == -1
			)
				break;

			rawBuffer.clear();
			rawBuffer.resize(size);

			if (GetRawInputData
			(
				reinterpret_cast<HRAWINPUT>(lParam),
				RID_INPUT,
				rawBuffer.data(),
				&size,
				sizeof(RAWINPUTHEADER)) != size
			)
				break;

			RAWINPUT const &rawInput = reinterpret_cast<RAWINPUT const&>(*rawBuffer.data());

			if (rawInput.header.dwType == RIM_TYPEMOUSE && (rawInput.data.mouse.lLastX != 0l || rawInput.data.mouse.lLastY != 0l))
				rawMouseMoveCallback(rawInput.data.mouse.lLastX, rawInput.data.mouse.lLastY);

			break;
		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

WPARAM IOWin32Window::MapLeftRightKeys(WPARAM wParam, LPARAM lParam) noexcept
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

bool IOWin32Window::IsCursorInScreenBounds(unsigned long cursorPosX, unsigned long cursorPosY) noexcept
{
	unsigned long width, height;
	this->GetResolution(&width, &height);

	return
	(
		(
			cursorPosX >= 0 && cursorPosX <= width &&
			cursorPosY >= 0 && cursorPosY <= height
		) ? true : false
	);
}
#endif