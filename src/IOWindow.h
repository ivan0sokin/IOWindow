#ifndef _IO_WINDOW_H
#define _IO_WINDOW_H

#include "IOWindowExtendedClass.h"
#include "IOWindowHandle.h"

#include "IOKeyboard.h"

#include <string>
#include <memory>

class IOWindow
{
public:
	IOWindow() noexcept;
	IOWindow(const IOWindow &other) = delete;
	IOWindow(IOWindow &&other) = delete;
	~IOWindow() noexcept;

	IOWindow& operator=(const IOWindow &other) = delete;
	IOWindow& operator=(IOWindow &&other) = delete;

	bool MakeWindow(std::string_view windowTitle, unsigned long screenWidth, unsigned long screenHeight) noexcept;
	void CloseWindow() noexcept;
	
	bool ShouldBeClosed() const noexcept;
	void PollWindowMessages() noexcept;

	void SetKeyboardInput(std::shared_ptr<IOKeyboard> &keyboardInput) noexcept;

	void GetWindowTitle(char *pWindowTitle) noexcept;
	void GetWindowScreenResolution(unsigned long *pWindowScreenWidth, unsigned long *pWindowScreenHeight) noexcept;
	void GetWindowPosition(long *pWindowPosX, long *pWindowPosY) noexcept;


	const std::string& GetLastError() const noexcept;
private:
	std::unique_ptr<IOWindowExtendedClass> extendedClass;
	std::unique_ptr<IOWindowHandle> handle;

	std::shared_ptr<IOKeyboard> keyboard;

	bool shouldBeClosed = false;

	std::string lastError;

	static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	static WPARAM MapLeftRightKeys(WPARAM wParam, LPARAM lParam) noexcept;
	bool IsCursorInScreenBounds(unsigned long cursorPosX, unsigned long cursorPosY) noexcept;
};

#endif