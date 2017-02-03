#include "Window.h"

namespace apenx
{
	namespace graphics
	{
		Window::Window(char * title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			if (!init())
			{
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}

			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW! Error code: " << glGetError() << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_Window)
			{
				std::cout << "Failed to create GLFW window! Error code: " << glGetError() << std::endl;
				return false;
			}

			glfwSetWindowUserPointer(m_Window, this);
			glfwMakeContextCurrent(m_Window);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW! Error code: " << glGetError() << std::endl;
				return false;
			}

			std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

			setCallbacks();

			return true;
		}

		void Window::setCallbacks()
		{
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			glfwSetWindowSizeCallback(m_Window, window_resize);
		}

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);

			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		bool Window::isKeyPressed(unsigned int keycode)
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}

		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);

			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		bool Window::isMouseButtonPressed(unsigned int button)
		{
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);

			win->m_MouseX = xpos;
			win->m_MouseY = ypos;
		}

		void Window::getMousePosition(double &x, double &y)
		{
			x = m_MouseX;
			y = m_MouseY;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() const
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		Window::~Window()
		{
			glfwTerminate();
		}
	}
}