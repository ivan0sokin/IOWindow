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

#ifndef _IO_MOUSE_H
#define _IO_MOUSE_H

#include <queue>
#include <optional>

#include "IOMouseEvent.h"
#include "IOMouseRaw.hpp"

class IOMouse
{
	friend class IOWindow;
public:
	IOMouse() = default;
	IOMouse(IOMouse const &other) = delete;
	~IOMouse() = default;

	long GetMousePosX() const noexcept;
	long GetMousePosY() const noexcept;

	std::optional<IOMouseEvent> ReadMouseEvent() noexcept;
	std::optional<IOMouseRaw> ReadMouseRaw() noexcept;

	bool IsInWindow() const noexcept;
	bool IsLeftPressed() const noexcept;
	bool IsRightPressed() const noexcept;
	bool IsEventBufferEmpty() const noexcept;
	bool IsRawBufferEmpty() const noexcept;
private:
	static constexpr size_t MAX_BUFFER_SIZE = static_cast<size_t>(16);
	static constexpr short _WHEEL_DELTA = static_cast<short>(120);

	long x;
	long y;
	bool isLeftPressed = false;
	bool isRightPressed = false;
	bool isInWindow = false;
	short wheelDeltaCarry = 0;
	bool isRawEnabled = false;
	std::queue<IOMouseEvent> eventBuffer;
	std::queue<IOMouseRaw> rawBuffer;

	void OnMouseMove(long x, long y) noexcept;
	void OnRawMouseMove(long dx, long dy) noexcept;
	void OnMouseEnter() noexcept;
	void OnMouseLeave() noexcept;
	void OnLeftPressed() noexcept;
	void OnLeftReleased() noexcept;
	void OnRightPressed() noexcept;
	void OnRightReleased() noexcept;
	void OnWheelUp() noexcept;
	void OnWheelDown() noexcept;
	void OnWheelDelta(short delta) noexcept;

	void PushEventBuffer(IOMouseEvent const &event) noexcept;
	void PushRawBuffer(IOMouseRaw const &rawMove) noexcept;

	void TrimEventBuffer() noexcept;
	void TrimRawBuffer() noexcept;
};

#endif