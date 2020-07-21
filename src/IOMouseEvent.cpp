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

#include "IOMouseEvent.h"

IOMouseEvent::IOMouseEvent(Type type, long x, long y, bool isLeftPressed, bool isRightPressed) noexcept
{
	this->type = type;
	this->x = x;
	this->y = y;
	this->isLeftPressed = isLeftPressed;
	this->isRightPressed = isRightPressed;
}

IOMouseEvent::Type IOMouseEvent::GetType() const noexcept
{
	return this->type;
}

bool IOMouseEvent::IsLeftPressed() const noexcept
{
	return this->isLeftPressed;
}

bool IOMouseEvent::IsRightPressed() const noexcept
{
	return this->isRightPressed;
}

long IOMouseEvent::GetPosX() const noexcept
{
	return this->x;
}

long IOMouseEvent::GetPosY() const noexcept
{
	return this->y;
}