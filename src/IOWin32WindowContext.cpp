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

#include "IOWin32WindowContext.h"

IOWin32WindowContext::IOWin32WindowContext() noexcept
{
	this->windowHandle = nullptr;
}

IOWin32WindowContext::IOWin32WindowContext(HWND hWnd) noexcept
{
	this->windowHandle = hWnd;
}

IOWin32WindowContext::IOWin32WindowContext(IOWin32WindowContext const &other) noexcept
{
	this->windowHandle = other.windowHandle;
}

IOWin32WindowContext::IOWin32WindowContext(IOWin32WindowContext &&other) noexcept
{
	this->windowHandle = other.windowHandle;
	other.windowHandle = nullptr;
}

IOWin32WindowContext& IOWin32WindowContext::operator=(IOWin32WindowContext const &other) noexcept
{
	if (this == &other)
		return *this;

	this->windowHandle = other.windowHandle;

	return *this;
}

IOWin32WindowContext& IOWin32WindowContext::operator=(IOWin32WindowContext &&other) noexcept
{
	if (this == &other)
		return *this;

	this->windowHandle = other.windowHandle;
	other.windowHandle = nullptr;

	return *this;
}

IOWin32WindowContext::~IOWin32WindowContext() noexcept
{
	this->Destroy();
}

bool IOWin32WindowContext::Destroy() noexcept
{
	if (renderingContextHandle == nullptr)
		return false;

	if (!this->Release())
		return false;

	if (ReleaseDC(windowHandle, GetDC(windowHandle)) != 1)
		return false;

	return wglDeleteContext(renderingContextHandle);
}

bool IOWin32WindowContext::Release() noexcept
{
	HDC deviceContextHandle = GetDC(windowHandle);
	if (deviceContextHandle == nullptr)
		return false;

	return wglMakeCurrent(deviceContextHandle, nullptr);
}

bool IOWin32WindowContext::Create() noexcept
{
	if (!this->SetPixelFormat())
		return false;

	HDC deviceContextHandle = GetDC(windowHandle);

	renderingContextHandle = wglCreateContext(deviceContextHandle);
	if (renderingContextHandle == nullptr)
		return false;

	return wglMakeCurrent(deviceContextHandle, renderingContextHandle);
}

bool IOWin32WindowContext::MakeCurrent() noexcept
{
	HDC deviceContextHandle = GetDC(windowHandle);
	if (deviceContextHandle == nullptr)
		return false;

	if (renderingContextHandle == nullptr)
		return false;

	return wglMakeCurrent(deviceContextHandle, renderingContextHandle);
}

void IOWin32WindowContext::SwapBuffers() noexcept
{
	::SwapBuffers(GetDC(windowHandle));
}

bool IOWin32WindowContext::SetPixelFormat() noexcept
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	ZeroMemory(&pixelFormatDescriptor, sizeof(PIXELFORMATDESCRIPTOR));

	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.cColorBits = 32;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cStencilBits = 8;

	HDC deviceContextHandle = GetDC(windowHandle);
	if (deviceContextHandle == nullptr)
		return false;

	int pixelFormat = ChoosePixelFormat(deviceContextHandle, &pixelFormatDescriptor);
	if (pixelFormat == 0)
		return false;
	
	if (!::SetPixelFormat(deviceContextHandle, pixelFormat, &pixelFormatDescriptor))
		return false;

	return true;
}