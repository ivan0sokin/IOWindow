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

#ifndef _IO_MOUSE_EVENT_H
#define _IO_MOUSE_EVENT_H

class IOMouseEvent
{
	friend class IOMouse;
public:
	enum class Type
	{
		LeftPressed,
		LeftReleased,
		RightPressed,
		RightReleased,
		WheelUp,
		WheelDown,
		Move,
		Enter,
		Leave
	};

	IOMouseEvent(Type type, long x, long y, bool isLeftPressed, bool isRightPressed) noexcept;
	~IOMouseEvent() = default;

	Type GetType() const noexcept;

	bool IsLeftPressed() const noexcept;
	bool IsRightPressed() const noexcept;

	long GetPosX() const noexcept;
	long GetPosY() const noexcept;
private:
	Type type;

	long x;
	long y;

	bool isLeftPressed;
	bool isRightPressed;
};

#endif