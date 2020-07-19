#ifndef _IO_WINDOW_HANDLE
#define _IO_WINDOW_HANDLE

#include <Windows.h>
#include <string>

class IOWindowHandle
{
public:
	IOWindowHandle() noexcept;
	IOWindowHandle(const IOWindowHandle &other) = delete;
	IOWindowHandle(IOWindowHandle &&other) = delete;
	~IOWindowHandle() noexcept;

	bool MakeWindowHandle
	(
		DWORD extendedStyle,
		LPCSTR extendedClassName,
		LPCSTR title,
		int width,
		int height,
		HINSTANCE hInstance,
		LPVOID pParam
	) noexcept;
	void DestroyWindowHandle() noexcept;

	const HWND& GetWindowHandle() noexcept;

	IOWindowHandle& operator=(const IOWindowHandle &other) = delete;
	IOWindowHandle& operator=(IOWindowHandle&& other) = delete;
private:
	HWND hWnd;

	void DestroyAndSetWindowHandleNull() noexcept;

	static constexpr DWORD IO_WINDOW_STYLE = WS_OVERLAPPEDWINDOW;
	static constexpr DWORD IO_WINDOW_POSITION = CW_USEDEFAULT;
};

#endif