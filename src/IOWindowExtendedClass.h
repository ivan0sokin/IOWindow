#ifndef _IO_WINDOW_CLASS_EX
#define _IO_WINDOW_CLASS_EX

#include <Windows.h>

class IOWindowExtendedClass
{
public:
	IOWindowExtendedClass() noexcept;
	IOWindowExtendedClass(const IOWindowExtendedClass &other) = delete;
	IOWindowExtendedClass(IOWindowExtendedClass &&other) = delete;
	~IOWindowExtendedClass() noexcept;

	IOWindowExtendedClass& operator=(const IOWindowExtendedClass &other) = delete;
	IOWindowExtendedClass& operator=(IOWindowExtendedClass &&other) = delete;

	bool MakeWindowClassEx(WNDPROC WndProc) noexcept;
	void DestroyWindowClassEx() noexcept;

	const HINSTANCE& GetWindowInstanceHandle() const noexcept;
	LPCSTR GetWindowClassExName() const noexcept;
private:
	HINSTANCE hInstance;
	LPCSTR name;

	void UnregisterClassExAndSetInstanceHandleNull() noexcept;

	static constexpr LPCSTR IO_WINDOW_CLASS_EX_NAME = "IOWindowExtendedClass";
};

#endif