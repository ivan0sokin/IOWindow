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