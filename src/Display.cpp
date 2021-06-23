/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/23 17:38:39 by pitriche         ###   ########.fr       */
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

	/* This is out of place, i have no way around */
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
}

void	Display::update(void)
{
	int mousex;
	int mousey;

	/* clear screen */
	glClearColor(0.2f, 0.1f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* set mouse location for fragment shader */
	SDL_GetMouseState(&mousex, &mousey);
	glUniform3f(all.gl.uniform.cursor_position,
		(mousex * 2 - WIN_SIZEX) / (float)WIN_SIZEY,
		(WIN_SIZEY - mousey * 2) / (float)WIN_SIZEY, 0.0);


	/* e x p a n d */
	// for (unsigned i = 0; i < 3000000; i += 3)
	// {
	// 	all.temporary_data[i + 0] *= 1.001f;
	// 	all.temporary_data[i + 2] *= 1.001f;
	// }
	// glBufferData(GL_ARRAY_BUFFER, 1000000*3*4, all.temporary_data,
	//  	GL_STATIC_DRAW);



	/* draw particles from VBO and wait for finish */
	glDrawArrays(GL_POINTS, 0, 1000000);
	glFinish();

	SDL_GL_SwapWindow(this->window);
}

void	Display::operator=(const Display &) { }
