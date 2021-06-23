/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:14:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/23 18:41:08 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* MacOS is the worst thing this earth had the disgrace to bear */
#define GL_SILENCE_DEPRECATION

#include "OpenGL.hpp"
#include "Defines.hpp"
#include "Utils.hpp"
#include "All.hpp" // ///////////////////////////////////////////////////////////

OpenGL::OpenGL(void) : window(0), glcontext(0), vao(0), vbo(0) { }

_Uniform::_Uniform(void) : particle_color(0), cursor_position(0),
	reference_length(0) { }
_Attribute::_Attribute(void) : position_vertex(0) { }
_Shader::_Shader(void) : vertex(0), fragment(0), program(0) { }

/* ########################################################################## */

void	OpenGL::_init_vao(void)
{
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	printf("VAO: [%d/1]\t", this->vao);
}


void	OpenGL::_init_vbo(void)
{
	static float temporary_data[1000000*3]; ////////////////
	for (unsigned i = 0; i < 3000000; i += 3)
	{
		/* circle */
		// float rad = (i / 15000.0f) * M_PI;
		// temporary_data[i + 0] = sin(rad);
		// temporary_data[i + 1] = cos(rad);
		// temporary_data[i + 2] = -1.0;

		/* full square */
		// temporary_data[i + 0] = rand() / (float)INT32_MAX;
		// temporary_data[i + 1] = rand() / (float)INT32_MAX;
		// temporary_data[i + 0] = temporary_data[i + 0] * 2 - 1.0f;
		// temporary_data[i + 1] = temporary_data[i + 1] * 2 - 1.0f;
		// temporary_data[i + 2] = -1.0;

		/* sphere */
		float	latitude, longitude;
		longitude = (rand() / (float)INT32_MAX) * (float)M_PI * 2;
		latitude = (rand() / (float)INT32_MAX) * (float)M_PI;
		temporary_data[i + 0] = sin(longitude) * sin(latitude);
		temporary_data[i + 1] = cos(longitude) * sin(latitude);
		temporary_data[i + 2] = cos(latitude);
	}
	all.temporary_data = temporary_data;

	glGenBuffers(1, &this->vbo);
	printf("VBO: [%d/1]\t", this->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 1000000*3*4, temporary_data,
	 	GL_STATIC_DRAW);
}

/* ########################################################################## */

static GLuint compile_shader(const char *filename, GLenum type)
{
	GLuint		shader;
	const char	*code;
	GLint		status;
	char		buffer[512];

	code = Utils::read_file(filename);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, 0);

	/* compiling */
	glCompileShader(shader);
	
	/* error checking */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		printf("[%s] shader compilation failed: [%d/1]\n", filename, status);
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		printf("Compilation log:\n%s\n", buffer);
		exit(0);
	}
	free((void *)code);
	return (shader);
}

void	OpenGL::_init_shader(void)
{
	this->shader.vertex = compile_shader("shader/vertex_shader.glsl",
		GL_VERTEX_SHADER);
	this->shader.fragment = compile_shader("shader/fragment_shader.glsl",
		GL_FRAGMENT_SHADER);

	/* create shader program and attach shaders */
	this->shader.program = glCreateProgram();
	printf("Program: [%d/3]\n", this->shader.program);
	glAttachShader(this->shader.program, this->shader.vertex);
	glAttachShader(this->shader.program, this->shader.fragment);
	glBindFragDataLocation(this->shader.program, 0, "outColor");

	/* link and use shader program */
	glLinkProgram(this->shader.program);
	glUseProgram(this->shader.program);
}

/* ########################################################################## */

void	OpenGL::_init_attribute(void)
{
	this->attribute.position_vertex =
	(GLuint)glGetAttribLocation(this->shader.program, "position_vertex");
	glVertexAttribPointer(this->attribute.position_vertex, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 3, (void *)(0));
	glEnableVertexAttribArray(this->attribute.position_vertex);
}

void	OpenGL::_init_uniform(void)
{
	this->uniform.particle_color = glGetUniformLocation(this->shader.program,
		"particle_color");
	glUniform3f(this->uniform.particle_color, 1.0f, 0.2f, 0.1f);

	this->uniform.cursor_position = glGetUniformLocation(this->shader.program,
		"cursor_position");
	glUniform3f(this->uniform.cursor_position, 0.0, 1.0, -1.0);

	this->uniform.reference_length = glGetUniformLocation(this->shader.program,
		"reference_length");
	glUniform1f(this->uniform.reference_length, 1.5);

	this->uniform.screen_ratio = glGetUniformLocation(this->shader.program,
		"screen_ratio");
	glUniform1f(this->uniform.screen_ratio, WIN_SIZEX / (float)WIN_SIZEY);
}

/* ########################################################################## */

void	OpenGL::init(SDL_Window *window)
{
	/* create OpenGL context */
	this->glcontext = SDL_GL_CreateContext(window);

	printf("Supported OpenGL version: %s\nUsing OpenGL %d.%d\n\n",
		glGetString(GL_VERSION), OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR);

	this->_init_vao();
	this->_init_vbo();
	this->_init_shader();
	this->_init_attribute();
	this->_init_uniform();

	glEnable(GL_DEPTH_TEST); // maybe

}
