#include <IOWindow/IOWindow.h>

int main()
{
	IOWindow window = IOWindow();

	if (!window.MakeWindow("1st example", 500ul, 500ul))
	{
		printf("%s\n", window.GetLastError().c_str());
		exit(-1);
	}

	auto keyboard = std::make_shared<IOKeyboard>();

	window.SetKeyboardInput(keyboard);

	while (!window.ShouldBeClosed())
	{
		window.PollWindowMessages();

		if (keyboard->IsKeyPressed(IO_KEY_ESCAPE))
		{
			window.CloseWindow();
			return 0;
		}
	}

	window.CloseWindow();
	return 0;
}