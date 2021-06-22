/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/22 13:59:30 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Display.hpp"
#include "All.hpp"

#include "Defines.hpp"
#include <OpenGL/gl3.h>

Display::Display(void) : window(0) { }
Display::Display(const Display &) { }
Display::~Display(void) { }

void	Display::init(void)
{
	this->res_x = 1920;
	this->res_y = 1080;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(0);

	/* init OpenGL context, version 4.1 (adapt version to OS supported) */
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,
			OPENGL_VERSION_MAJOR) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,
			OPENGL_VERSION_MINOR) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) < 0)
		exit(0);

	/* create window */
	if (!(this->window = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
				WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_OPENGL)))
		exit(0);

	/* create OpenGL context */
	this->gl_context = SDL_GL_CreateContext(this->window);

	printf("Supported OpenGL version: %s\nUsing OpenGL %d.%d\n\n",
		glGetString(GL_VERSION), OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR);

	// init_vao(al);
	// init_shader(al);
	// init_attribute(al);
	// init_uniform(al);
	// init_texture(al);

	glEnable(GL_DEPTH_TEST); // maybe
}

void	Display::update(void)
{
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// glDrawElements(GL_TRIANGLES, (GLsizei)al->data.element_size /
	// 	(GLsizei)sizeof(float), GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(this->window);
}

void	Display::operator=(const Display &) { }
