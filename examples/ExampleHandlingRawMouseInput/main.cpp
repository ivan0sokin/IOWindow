#include <IOWindow/IOWindow.h>

int main()
{
	IOWindow window = IOWindow();

	if (!window.MakeWindow("2nd example", 500ul, 500ul))
	{
		printf("%s\n", window.GetLastError().c_str());
		exit(-1);
	}

	auto mouse = std::make_shared<IOMouse>();
	window.SetMouseInput(mouse);
	window.EnableRawMouseInput();

	while (!window.ShouldBeClosed())
	{
		window.PollWindowMessages();

		while (auto rawMouseMove = mouse->ReadMouseRaw())
		{
			SomeCameraClass.OnMouseMove(rawMouseMove.value().dx, rawMouseMove.value().dy);
		}

		/* or you can use this:

		while (!mouse->IsRawBufferEmpty())
		{
			IOMouseRaw rawMouseMove = IOMouseRaw(mouse->ReadMouseRaw().value());

			SomeCameraClass.OnMouseMove(rawMouseMove.dx, rawMouseMove.dy);
		}

		*/
	}

	window.CloseWindow();
	return 0;
}