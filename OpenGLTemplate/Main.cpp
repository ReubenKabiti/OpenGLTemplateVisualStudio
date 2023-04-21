#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Mesh.h"
#include "Shader.h"
#include "BufferObject.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Framebuffers", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();
	const char* vss = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;"
		"void main()"
		"{"
		"	gl_Position = vec4(aPos, 1);"
		"}";

	const char* fss = "#version 330 core\n"
		"out vec4 color;"
		"void main()"
		"{"
		"	color = vec4(1, 0, 0, 1);"
		"}";

	Shader vs(GL_VERTEX_SHADER);
	Shader fs(GL_FRAGMENT_SHADER);

	vs.create(vss);
	fs.create(fss);

	std::shared_ptr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>();

	shaderProgram->create(vs, fs);
	shaderProgram->use();

	std::vector<float> vertices = {
		0, 0.5, 0,
		-0.5, -0.5, 0,
		0.5, -0.5, 0
	};

	std::vector<uint32_t> indices = {
		0, 1, 2
	};

	Mesh mesh;
	mesh.setShaderProgram(shaderProgram);
	mesh.setVertices(vertices);
	mesh.setIndices(indices);
	mesh.configure(0, 3, 12, 0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		mesh.render();
		glfwSwapBuffers(window);
	}

	return 0;
}