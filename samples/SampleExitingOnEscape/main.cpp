#include "IOWindow.h"

int main()
{
	IOWindow wnd = IOWindow();

	if (!wnd.MakeWindow("MyTitle", 500u, 500u))
	{
		std::cerr << wnd.GetLastError() << '\n';
		return 0;
	}

	auto keyboard = std::make_shared<IOKeyboard>();

	wnd.SetKeyboardInput(keyboard);

	while (!wnd.ShouldBeClosed())
	{
		wnd.PollWindowMessages();

		if (keyboard->IsKeyPressed(IO_KEY_ESCAPE))
		{
			wnd.CloseWindow();
			return 0;
		}
	}

	wnd.CloseWindow();
	return 0;
}