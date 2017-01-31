#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

namespace apenx
{
	namespace graphics
	{
#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

		class Window
		{
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_MOUSE_BUTTONS];
			double m_MouseX, m_MouseY;

		public:
			Window(char *name, int width, int height);
			~Window();
			bool closed() const;
			void clear() const;
			void update() const;

			bool isKeyPressed(unsigned int keycode);
			bool isMouseButtonPressed(unsigned int button);
			void getMousePosition(double &x, double &y);

			inline int getWidth()
			{
				return m_Width;
			}
			inline int getHeight()
			{
				return m_Height;
			}
			inline GLFWwindow *getGLFWWindow()
			{
				return m_Window;
			}
		private:
			bool init();
			void setCallbacks();

			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void window_resize(GLFWwindow *window, int width, int height);
			friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}