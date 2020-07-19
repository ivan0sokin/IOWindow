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