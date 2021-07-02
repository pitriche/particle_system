/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/02 17:50:26 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"
#include "All.hpp"

Event::Event(void) { }
Event::Event(const Event &) { }
Event::~Event(void) { }

void	Event::_keychange(SDL_Keycode kc)
{
	size_t	global_size[2] = {PARTICLES, 0};

	switch (kc)
	{
		case (SDLK_1):
			clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.init_sphere, 1,
				0, global_size, 0, 0, 0, 0);
			clFinish(all.cl.queue);
			break;
		case (SDLK_2):
			clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.init_disk, 1, 0,
				global_size, 0, 0, 0, 0);
			clFinish(all.cl.queue);
			break;
		case (SDLK_3):
			clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.init_cube_full,
				1, 0, global_size, 0, 0, 0, 0);
			clFinish(all.cl.queue);
			break;
		case (SDLK_4):
			clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.init_cube, 1, 0,
				global_size, 0, 0, 0, 0);
			clFinish(all.cl.queue);
			break;
		case (SDLK_PAGEUP):
			all.reference_length += 0.1f;
			glUniform1f(all.gl.uniform.reference_length, all.reference_length);
			break;
		case (SDLK_PAGEDOWN):
			all.reference_length -= 0.1f;
			all.reference_length = all.reference_length > 0.01f ?
			all.reference_length : 0.01f;
			glUniform1f(all.gl.uniform.reference_length, all.reference_length);
			break;
		case (SDLK_r):
			glUniform3f(all.gl.uniform.particle_color, 1.0f, 0.2f, 0.2f);
			break;
		case (SDLK_g):
			glUniform3f(all.gl.uniform.particle_color, 0.4f, 1.0f, 0.2f);
			break;
		case (SDLK_b):
			glUniform3f(all.gl.uniform.particle_color, 0.2f, 0.4f, 1.0f);
			break;
		case (SDLK_p):
			glUniform3f(all.gl.uniform.particle_color, 0.99f, 0.73f, 0.70f);
			break;
		case (SDLK_y):
			glUniform3f(all.gl.uniform.particle_color, 1.00f, 0.74f, 0.05f);
			break;
		case (SDLK_ESCAPE):
			exit(0);
			break;
	}
}

void	Event::update(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		// if (event.type == SDL_KEYDOWN && !event.key.repeat)
		if (event.type == SDL_KEYDOWN)
			this->_keychange(event.key.keysym.sym);
	}
}

void	Event::operator=(const Event &) { }
