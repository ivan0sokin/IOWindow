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
	this->handle = std::make_unique<IOLinuxWindowHandle>();

	this->FillKeyCodes();
}

void IOLinuxWindow::FillKeyCodes() noexcept
{
	memset(keyCodes.data(), IO_KEY_UNKNOWN, keyCodes.size());

	keyCodes[0x09] = IO_KEY_ESCAPE;
	keyCodes[0x0A] = IO_KEY_1;
	keyCodes[0x0B] = IO_KEY_2;
	keyCodes[0x0C] = IO_KEY_3;
	keyCodes[0x0D] = IO_KEY_4;
	keyCodes[0x0E] = IO_KEY_5;
	keyCodes[0x0F] = IO_KEY_6;
	keyCodes[0x10] = IO_KEY_7;
	keyCodes[0x11] = IO_KEY_8;
	keyCodes[0x12] = IO_KEY_9;
	keyCodes[0x13] = IO_KEY_0;
	keyCodes[0x14] = IO_KEY_MINUS;
	keyCodes[0x15] = IO_KEY_EQUAL;
	keyCodes[0x16] = IO_KEY_BACKSPACE;
	keyCodes[0x17] = IO_KEY_TAB;
	keyCodes[0x18] = IO_KEY_Q;
	keyCodes[0x19] = IO_KEY_W;
	keyCodes[0x1A] = IO_KEY_E;
	keyCodes[0x1B] = IO_KEY_R;
	keyCodes[0x1C] = IO_KEY_T;
	keyCodes[0x1D] = IO_KEY_Y;
	keyCodes[0x1E] = IO_KEY_U;
	keyCodes[0x1F] = IO_KEY_I;
	keyCodes[0x20] = IO_KEY_O;
	keyCodes[0x21] = IO_KEY_P;
	keyCodes[0x22] = IO_KEY_LEFT_BRACKET;
	keyCodes[0x23] = IO_KEY_RIGHT_BRACKET;
	keyCodes[0x24] = IO_KEY_ENTER;
	keyCodes[0x25] = IO_KEY_LEFT_CTRL;
	keyCodes[0x26] = IO_KEY_A;
	keyCodes[0x27] = IO_KEY_S;
	keyCodes[0x28] = IO_KEY_D;
	keyCodes[0x29] = IO_KEY_F;
	keyCodes[0x2A] = IO_KEY_G;
	keyCodes[0x2B] = IO_KEY_H;
	keyCodes[0x2C] = IO_KEY_J;
	keyCodes[0x2D] = IO_KEY_K;
	keyCodes[0x2E] = IO_KEY_L;
	keyCodes[0x2F] = IO_KEY_SEMICOLON;
	keyCodes[0x30] = IO_KEY_APOSTROPHE;
	keyCodes[0x31] = IO_KEY_GRAVE_ACCENT;
	keyCodes[0x32] = IO_KEY_LEFT_SHIFT;
	keyCodes[0x33] = IO_KEY_BACKSLASH;
	keyCodes[0x34] = IO_KEY_Z;
	keyCodes[0x35] = IO_KEY_X;
	keyCodes[0x36] = IO_KEY_C;
	keyCodes[0x37] = IO_KEY_V;
	keyCodes[0x38] = IO_KEY_B;
	keyCodes[0x39] = IO_KEY_N;
	keyCodes[0x3A] = IO_KEY_M;
	keyCodes[0x3B] = IO_KEY_COMMA;
	keyCodes[0x3C] = IO_KEY_PERIOD;
	keyCodes[0x3D] = IO_KEY_SLASH;
	keyCodes[0x3E] = IO_KEY_RIGHT_SHIFT;
	keyCodes[0x3F] = IO_KEY_NUMPAD_MULTIPLY;
	keyCodes[0x40] = IO_KEY_LEFT_ALT;
	keyCodes[0x41] = IO_KEY_SPACE;
	keyCodes[0x42] = IO_KEY_CAPSLOCK;
	keyCodes[0x43] = IO_KEY_F1;
	keyCodes[0x44] = IO_KEY_F2;
	keyCodes[0x45] = IO_KEY_F3;
	keyCodes[0x46] = IO_KEY_F4;
	keyCodes[0x47] = IO_KEY_F5;
	keyCodes[0x48] = IO_KEY_F6;
	keyCodes[0x49] = IO_KEY_F7;
	keyCodes[0x4A] = IO_KEY_F8;
	keyCodes[0x4B] = IO_KEY_F9;
	keyCodes[0x4C] = IO_KEY_F10;
	keyCodes[0x4D] = IO_KEY_NUMLOCK;
	keyCodes[0x4F] = IO_KEY_NUMPAD_7;
	keyCodes[0x50] = IO_KEY_NUMPAD_8;
	keyCodes[0x51] = IO_KEY_NUMPAD_9;
	keyCodes[0x52] = IO_KEY_NUMPAD_SUBTRACT;
	keyCodes[0x53] = IO_KEY_NUMPAD_4;
	keyCodes[0x54] = IO_KEY_NUMPAD_5;
	keyCodes[0x55] = IO_KEY_NUMPAD_6;
	keyCodes[0x56] = IO_KEY_NUMPAD_ADD;
	keyCodes[0x57] = IO_KEY_NUMPAD_1;
	keyCodes[0x58] = IO_KEY_NUMPAD_2;
	keyCodes[0x59] = IO_KEY_NUMPAD_3;
	keyCodes[0x5A] = IO_KEY_NUMPAD_0;
	keyCodes[0x5B] = IO_KEY_NUMPAD_DECIMAL;
	keyCodes[0x5F] = IO_KEY_F11;
	keyCodes[0x60] = IO_KEY_F12;
	keyCodes[0x68] = IO_KEY_NUMPAD_ENTER;
	keyCodes[0x69] = IO_KEY_RIGHT_CTRL;
	keyCodes[0x6A] = IO_KEY_NUMPAD_DIVIDE;
	keyCodes[0x6B] = IO_KEY_PRINTSCREEN;
	keyCodes[0x6C] = IO_KEY_RIGHT_ALT;
	keyCodes[0x6F] = IO_KEY_UP_ARROW;
	keyCodes[0x71] = IO_KEY_LEFT_ARROW;
	keyCodes[0x72] = IO_KEY_RIGHT_ARROW;
	keyCodes[0x74] = IO_KEY_DOWN_ARROW;
	keyCodes[0x76] = IO_KEY_INSERT;
	keyCodes[0x77] = IO_KEY_DELETE;
	keyCodes[0x79] = IO_KEY_VOLUME_MUTE;
	keyCodes[0x7A] = IO_KEY_VOLUME_DOWN;
	keyCodes[0x7B] = IO_KEY_VOLUME_UP;
	keyCodes[0xAC] = IO_KEY_PAUSE;
}

IOLinuxWindow::~IOLinuxWindow() noexcept
{
	this->Close();
}

void IOLinuxWindow::Close() noexcept
{
	handle->Destroy();
}

bool IOLinuxWindow::Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept
{
	return handle->Create(windowTitle, windowWidth, windowHeight);
}

void IOLinuxWindow::ProcessEvents() noexcept
{
	XEvent event;
	while (XPending(handle->GetDisplayHandle()) != 0)
	{
		XNextEvent(handle->GetDisplayHandle(), &event);
		
		this->DispatchEvent(&event);
	}
}

void IOLinuxWindow::DispatchEvent(XEvent const *event) noexcept
{
	switch (event->type)
	{
		case KeyPress:
		{
			unsigned scanCode = event->xkey.keycode;
			if (keyboardInputCallback)
				keyboardInputCallback(keyCodes[scanCode], scanCode, IO_KEY_PRESS);

			break;
		}
		case KeyRelease:
		{
			unsigned scanCode = event->xkey.keycode;
			if (keyboardInputCallback)
				keyboardInputCallback(keyCodes[scanCode], scanCode, IO_KEY_RELEASE);

			break;	
		}
		default:
			break;
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
	// XWindowAttributes attributes = {};
	// XGetWindowAttributes(display, window, &attributes);

	// if (pWindowScreenWidth != nullptr)
	// 	*pWindowScreenWidth = static_cast<unsigned long>(attributes.width);
	// if (pWindowScreenHeight != nullptr)
	// 	*pWindowScreenHeight = static_cast<unsigned long>(attributes.height);
}

void IOLinuxWindow::GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept
{
	// int x, y;
	// Window trash;
	// XTranslateCoordinates(display, window, rootWindow, 0, 0, &x, &y, &trash);

	// if (pWindowPosX != nullptr)
	// 	*pWindowPosX = static_cast<long>(x);
	// if (pWindowPosY != nullptr)
	// 	*pWindowPosY = static_cast<long>(y);
}


Window IOLinuxWindow::GetWindowHandle() const noexcept
{
	return handle->GetWindowHandle();
}

Display* IOLinuxWindow::GetDisplayHandle() const noexcept
{
	return handle->GetDisplayHandle();
}
#endif