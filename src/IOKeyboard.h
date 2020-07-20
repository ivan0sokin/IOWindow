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

#ifndef _IO_KEYBOARD_H
#define _IO_KEYBOARD_H

#include <queue>
#include <bitset>
#include <optional>

#include "IOKeyboardMappings.h"

class IOKeyboard
{
	friend class IOWindow;
public:
	class IOEvent
	{
	public:
		enum class Type
		{
			Pressed,
			Released
		};

		IOEvent(Type type, unsigned char key) noexcept;
		IOEvent(const IOEvent& event) noexcept;

		bool IsPressed() const noexcept;
		bool IsReleased() const noexcept;
		unsigned char GetKey() const noexcept;
	private:
		Type type;
		unsigned char key;
	};

	IOKeyboard() = default;
	IOKeyboard(const IOKeyboard& keyboard) = delete;

	bool IsEventBufferEmpty() const noexcept;

	std::optional<IOEvent> ReadKeyboardEvent() noexcept;
	bool IsKeyPressed(unsigned char key) const noexcept;

	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool IsAutorepeatEnabled() const noexcept;
private:
	static constexpr size_t NUM_KEYS = static_cast<size_t>(256);
	static constexpr size_t MAX_BUFFER_SIZE = static_cast<size_t>(16);

	std::queue<IOEvent> eventBuffer;
	std::bitset<NUM_KEYS> keyStates;
	bool autorepeat = false;

	void OnKeyPressed(unsigned char key) noexcept;
	void OnKeyReleased(unsigned char key) noexcept;

	void ClearKeyStates() noexcept;

	void PushEvent(IOEvent::Type &&type, unsigned char &&key) noexcept;
	void TrimEventBuffer() noexcept;
};

#endif