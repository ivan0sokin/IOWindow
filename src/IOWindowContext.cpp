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

#include "IOWindowContext.h"

IOWindowContext::IOWindowContext() noexcept
{
	this->hWnd = nullptr;
}

IOWindowContext::IOWindowContext(HWND hWnd) noexcept
{
	this->hWnd = hWnd;
}

IOWindowContext::IOWindowContext(IOWindowContext const &other) noexcept
{
	this->hWnd = other.hWnd;
}

IOWindowContext::IOWindowContext(IOWindowContext &&other) noexcept
{
	this->hWnd = other.hWnd;
	other.hWnd = nullptr;
}

IOWindowContext& IOWindowContext::operator=(IOWindowContext const &other) noexcept
{
	if (this == &other)
		return *this;

	this->hWnd = other.hWnd;

	return *this;
}

IOWindowContext& IOWindowContext::operator=(IOWindowContext &&other) noexcept
{
	if (this == &other)
		return *this;

	this->hWnd = other.hWnd;
	other.hWnd = nullptr;

	return *this;
}

IOWindowContext::~IOWindowContext() noexcept
{
	this->DestroyOpenGLContext();
}

bool IOWindowContext::DestroyOpenGLContext() noexcept
{
	wglMakeCurrent(nullptr, nullptr);
	ReleaseDC(hWnd, GetDC(hWnd));

	if (!wglDeleteContext(wglGetCurrentContext()))
		return false;

	return true;
}

bool IOWindowContext::CreateOpenGLContext() noexcept
{
	if (!this->SetPixelFormat())
		return false;

	HDC deviceContextHandle = GetDC(hWnd);
	HGLRC renderingContextHandle = wglCreateContext(deviceContextHandle);
	if (renderingContextHandle == nullptr)
		return false;

	if (!wglMakeCurrent(deviceContextHandle, renderingContextHandle))
		return false;

	return true;
}

void IOWindowContext::SwapBuffers() noexcept
{
	::SwapBuffers(GetDC(hWnd));
}

bool IOWindowContext::SetPixelFormat() noexcept
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	ZeroMemory(&pixelFormatDescriptor, sizeof(PIXELFORMATDESCRIPTOR));

	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.cColorBits = 32;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.cStencilBits = 8;

	HDC deviceContextHandle = GetDC(hWnd);
	int pixelFormat = ChoosePixelFormat(deviceContextHandle, &pixelFormatDescriptor);
	if (pixelFormat == 0)
		return false;
	
	if (!::SetPixelFormat(deviceContextHandle, pixelFormat, &pixelFormatDescriptor))
		return false;

	return true;
}