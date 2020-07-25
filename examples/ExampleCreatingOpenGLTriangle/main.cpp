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

#include <IOWindow/IOWindow.h>

#pragma comment(lib, "opengl32.lib")
#include <gl/GL.h>

int main()
{
	IOWindow window = IOWindow();

	if (!window.MakeWindow("4th example", 500ul, 500ul))
	{
		printf("%s\n", window.GetLastError().c_str());
		exit(-1);
	}
	
	if (!window.CreateContext())
	{
		printf("%s\n", window.GetLastError().c_str());
		exit(-1);
	}

	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	while (!window.ShouldBeClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		window.PollWindowMessages();

		glBegin(GL_TRIANGLES);
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-0.5f, -0.5f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f( 0.0f,  0.5f);

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f( 0.5f,  -0.5f);
		}
		glEnd();

		window.SwapBuffers();
	}

	window.DestroyContext();
	window.CloseWindow();
	return 0;
}