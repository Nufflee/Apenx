#include "Shader.h"

namespace apenx
{
	namespace graphics
	{
		Shader::Shader(const char *vertexpath, const char *fragmentpath)
			: m_VertexPath(vertexpath), m_FragmentPath(fragmentpath)
		{
			m_ShaderID = load();
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexSourceString = utils::FileUtils::read_file(m_VertexPath);
			std::string fragmentSoruceString = utils::FileUtils::read_file(m_FragmentPath);
			const char *vertexSource = vertexSourceString.c_str();
			const char *fragmentSource = fragmentSoruceString.c_str();

			glShaderSource(vertex, 1, &vertexSource, NULL);
			glCompileShader(vertex);

			GLint result;

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);

				return 0;
			}

			glShaderSource(fragment, 1, &fragmentSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);

				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar *name)
		{
			if (!m_Enabled)
			{
				std::cout << "Shader is not enabled!" << std::endl;
				return -1;
			}

			return glGetUniformLocation(getShaderID(), name);
		}

		void Shader::setUniform1f(const GLchar *name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}
		void Shader::setUniform1i(const GLchar *name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}
		void Shader::setUniform2f(const GLchar *name, glm::vec2 &vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}
		void Shader::setUniform3f(const GLchar *name, glm::vec3 &vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}
		void Shader::setUniform3f(const GLchar *name, glm::vec4 &vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}
		void Shader::setUnifromMat4(const GLchar *name, const glm::mat4 &matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void Shader::enable()
		{
			glUseProgram(m_ShaderID);
			m_Enabled = true;
		}

		void Shader::disable()
		{
			glUseProgram(0);
			m_Enabled = false;
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}
	}
}