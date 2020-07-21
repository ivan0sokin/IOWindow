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

#include "IOKeyboard.h"

bool IOKeyboard::IsEventBufferEmpty() const noexcept
{
	return eventBuffer.empty();
}

std::optional<IOKeyboardEvent> IOKeyboard::ReadKeyboardEvent() noexcept
{
	if (!eventBuffer.empty())
	{
		IOKeyboardEvent keyboardEvent = eventBuffer.front();
		eventBuffer.pop();
		return keyboardEvent;
	}

	return std::nullopt;
}

bool IOKeyboard::IsKeyPressed(unsigned char key) const noexcept
{
	return keyStates[static_cast<size_t>(key)];
}

void IOKeyboard::EnableAutorepeat() noexcept
{
	autorepeat = true;
}

void IOKeyboard::DisableAutorepeat() noexcept
{
	autorepeat = false;
}

bool IOKeyboard::IsAutorepeatEnabled() const noexcept
{
	return this->autorepeat;
}

void IOKeyboard::OnKeyPressed(unsigned char key) noexcept
{
	this->PushEvent(IOKeyboardEvent(IOKeyboardEvent::Type::Pressed, key));
}

void IOKeyboard::OnKeyReleased(unsigned char key) noexcept
{
	this->PushEvent(IOKeyboardEvent(IOKeyboardEvent::Type::Released, key));
}

void IOKeyboard::PushEvent(IOKeyboardEvent const &event) noexcept
{
	keyStates[static_cast<size_t>(event.GetKey())] = event.IsPressed();

	eventBuffer.push(event);
	this->TrimEventBuffer();
}

void IOKeyboard::TrimEventBuffer() noexcept
{
	while (eventBuffer.size() > IOKeyboard::MAX_BUFFER_SIZE)
	{
		eventBuffer.pop();
	}
}

void IOKeyboard::ClearKeyStates() noexcept
{
	keyStates.reset();
}