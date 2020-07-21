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

#include "IOMouse.h"

long IOMouse::GetMousePosX() const noexcept
{
	return this->x;
}

long IOMouse::GetMousePosY() const noexcept
{
	return this->y;
}

std::optional<IOMouseEvent> IOMouse::ReadMouseEvent() noexcept
{
	if (!eventBuffer.empty())
	{
		IOMouseEvent event = eventBuffer.front();
		eventBuffer.pop();
		return event;
	}

	return std::nullopt;
}

std::optional<IOMouseRaw> IOMouse::ReadMouseRaw() noexcept
{
	if (!rawBuffer.empty())
	{
		IOMouseRaw rawMove = rawBuffer.front();
		rawBuffer.pop();
		return rawMove;
	}

	return std::nullopt;
}

bool IOMouse::IsInWindow() const noexcept
{
	return this->isInWindow;
}

bool IOMouse::IsLeftPressed() const noexcept
{
	return this->isLeftPressed;
}

bool IOMouse::IsRightPressed() const noexcept
{
	return this->isRightPressed;
}

bool IOMouse::IsEventBufferEmpty() const noexcept
{
	return eventBuffer.empty();
}

bool IOMouse::IsRawBufferEmpty() const noexcept
{
	return rawBuffer.empty();
}

void IOMouse::EnableRawInput() noexcept
{
	isRawEnabled = true;
}

void IOMouse::DisableRawInput() noexcept
{
	isRawEnabled = false;
}

bool IOMouse::IsRawInputEnabled() const noexcept
{
	return this->isRawEnabled;
}

void IOMouse::OnMouseMove(long x, long y) noexcept
{
	this->x = x;
	this->y = y;

	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::Move, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnRawMouseMove(long dx, long dy) noexcept
{
	this->PushRawBuffer(IOMouseRaw(dx, dy));
}

void IOMouse::OnMouseEnter() noexcept
{
	isInWindow = true;

	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::Enter, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnMouseLeave() noexcept
{
	isInWindow = false;

	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::Leave, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnLeftPressed() noexcept
{
	isLeftPressed = true;

	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::LeftPressed, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnLeftReleased() noexcept
{
	isLeftPressed = false;

	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::LeftReleased, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnRightPressed() noexcept
{
	isRightPressed = true;

	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::RightPressed, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnRightReleased() noexcept
{
	isRightPressed = false;

	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::RightReleased, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnWheelUp() noexcept
{
	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::WheelUp, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnWheelDown() noexcept
{
	this->PushEventBuffer(IOMouseEvent(IOMouseEvent::Type::WheelDown, x, y, isLeftPressed, isRightPressed));
}

void IOMouse::OnWheelDelta(short delta) noexcept
{
	wheelDeltaCarry += delta;

	while (wheelDeltaCarry >= IOMouse::_WHEEL_DELTA)
	{
		this->wheelDeltaCarry -= IOMouse::_WHEEL_DELTA;
		this->OnWheelUp();
	}
	while (wheelDeltaCarry <= -IOMouse::_WHEEL_DELTA)
	{
		this->wheelDeltaCarry += IOMouse::_WHEEL_DELTA;
		this->OnWheelDown();
	}
}

void IOMouse::PushEventBuffer(IOMouseEvent const &event) noexcept
{
	eventBuffer.push(event);
	this->TrimEventBuffer();
}

void IOMouse::PushRawBuffer(IOMouseRaw const &rawMove) noexcept
{
	rawBuffer.push(rawMove);
	this->TrimRawBuffer();
}

void IOMouse::TrimEventBuffer() noexcept
{
	while (eventBuffer.size() > IOMouse::MAX_BUFFER_SIZE)
	{
		eventBuffer.pop();
	}
}

void IOMouse::TrimRawBuffer() noexcept
{
	while (rawBuffer.size() > IOMouse::MAX_BUFFER_SIZE)
	{
		rawBuffer.pop();
	}
}