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
	this->platformWindow.reset(IOPlatformWindow::CreateInstance());
}

IOWindow::~IOWindow() noexcept
{
	platformWindow->Close();
}

void IOWindow::Close() noexcept
{
	platformWindow->Close();
}

bool IOWindow::Create(std::string_view windowTitle, unsigned long windowWidth, unsigned long windowHeight) noexcept
{
	return platformWindow->Create(windowTitle, windowWidth, windowHeight);
}

void IOWindow::ProcessEvents() noexcept
{
	platformWindow->ProcessEvents();
}

void IOWindow::EnableRawMouseInput() noexcept
{
	platformWindow->EnableRawMouseInput();
}

void IOWindow::DisableRawMouseInput() noexcept
{
	platformWindow->DisableRawMouseInput();
}

void IOWindow::EnableMouseCursor() noexcept
{
	platformWindow->EnableMouseCursor();
}

void IOWindow::DisableMouseCursor() noexcept
{
	platformWindow->DisableMouseCursor();
}

void IOWindow::EnableAutorepeat() noexcept
{
	platformWindow->EnableAutorepeat();
}

void IOWindow::DisableAutorepeat() noexcept
{
	platformWindow->DisableAutorepeat();
}

void IOWindow::OnResize(IOWindowResizeCallbackFunction windowResizeCallbackFunction) noexcept
{
	platformWindow->OnResize(windowResizeCallbackFunction);
}

void IOWindow::OnMove(IOWindowMoveCallbackFunction windowMoveCallbackFunction) noexcept
{
	platformWindow->OnMove(windowMoveCallbackFunction);
}

void IOWindow::OnClose(IOWindowCloseCallbackFunction windowCloseCallbackFunction) noexcept
{
	platformWindow->OnClose(windowCloseCallbackFunction);
}

void IOWindow::OnKeyboardInput(IOKeyboardInputCallbackFunction keyboardInputCallbackFunction) noexcept
{
	platformWindow->OnKeyboardInput(keyboardInputCallbackFunction);
}

void IOWindow::OnMouseInput(IOMouseInputCallbackFunction mouseInputCallbackFunction) noexcept
{
	platformWindow->OnMouseInput(mouseInputCallbackFunction);
}

void IOWindow::OnMouseMove(IOMouseMoveCallbackFunction mouseMoveCallbackFunction) noexcept
{
	platformWindow->OnMouseMove(mouseMoveCallbackFunction);
}

void IOWindow::OnRawMouseMove(IORawMouseMoveCallbackFunction rawMouseMoveCallbackFunction) noexcept
{
	platformWindow->OnRawMouseMove(rawMouseMoveCallbackFunction);
}

void IOWindow::OnMouseEnter(IOMouseEnterCallbackFunction mouseEnterCallbackFunction) noexcept
{
	platformWindow->OnMouseEnter(mouseEnterCallbackFunction);
}

void IOWindow::OnMouseScroll(IOMouseScrollCallbackFunction mouseScrollCallbackFunction) noexcept
{
	platformWindow->OnMouseScroll(mouseScrollCallbackFunction);
}

bool IOWindow::CreateContext() noexcept
{
	return platformWindow->CreateContext();
}

bool IOWindow::DestroyContext() noexcept
{
	return platformWindow->DestroyContext();
}

void IOWindow::SwapBuffers() noexcept
{
	platformWindow->SwapBuffers();
}

void IOWindow::GetTitle(char *pWindowTitle) noexcept
{
	platformWindow->GetTitle(pWindowTitle);
}

void IOWindow::GetResolution(unsigned long *pWindowWidth, unsigned long *pWindowHeight) noexcept
{
	platformWindow->GetResolution(pWindowWidth, pWindowHeight);
}

void IOWindow::GetPosition(long *pWindowPosX, long *pWindowPosY) noexcept
{
	platformWindow->GetPosition(pWindowPosX, pWindowPosY);
}

std::shared_ptr<IOPlatformWindow> const& IOWindow::GetPlatformWindow() noexcept
{
	return this->platformWindow;
}