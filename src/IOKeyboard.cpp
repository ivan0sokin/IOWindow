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

IOKeyboard::IOEvent::IOEvent(Type type, unsigned char key) noexcept
{
	this->type = type;
	this->key = key;
}

IOKeyboard::IOEvent::IOEvent(const IOEvent &event) noexcept
{
	this->type = event.type;
	this->key = event.key;
}

bool IOKeyboard::IOEvent::IsPressed() const noexcept
{
	return type == Type::Pressed;
}

bool IOKeyboard::IOEvent::IsReleased() const noexcept
{
	return type == Type::Released;
}

unsigned char IOKeyboard::IOEvent::GetKey() const noexcept
{
	return this->key;
}

void IOKeyboard::OnKeyPressed(unsigned char key) noexcept
{
	this->PushEvent(std::forward<IOEvent::Type>(IOEvent::Type::Pressed), std::forward<unsigned char>(key));
}

void IOKeyboard::OnKeyReleased(unsigned char key) noexcept
{
	this->PushEvent(std::forward<IOEvent::Type>(IOEvent::Type::Released), std::forward<unsigned char>(key));
}

void IOKeyboard::PushEvent(IOEvent::Type &&type, unsigned char &&key) noexcept
{
	keyStates[static_cast<size_t>(key)] = (type == IOEvent::Type::Pressed);

	eventBuffer.emplace(type, key);
	this->TrimEventBuffer();
}

void IOKeyboard::TrimEventBuffer() noexcept
{
	while (eventBuffer.size() > MAX_BUFFER_SIZE)
	{
		eventBuffer.pop();
	}
}

void IOKeyboard::ClearKeyStates() noexcept
{
	keyStates.reset();
}

bool IOKeyboard::IsEventBufferEmpty() const noexcept
{
	return eventBuffer.empty();
}

std::optional<IOKeyboard::IOEvent> IOKeyboard::ReadKeyboardEvent() noexcept
{
	if (!eventBuffer.empty())
	{
		IOEvent keyboardEvent = this->eventBuffer.front();
		this->eventBuffer.pop();
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