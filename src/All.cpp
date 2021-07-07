/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   All.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/07 15:58:24 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"
#include "Defines.hpp"

All::All(void) { }
All::All(const All &) { }
All::~All(void) { }

void	All::init(void)
{
	size_t	global_size[2];
	
	all.reference_length = 1.0;
	all.cursor_update = true;
	all.data.mass = 1;
	this->disp.init();
	this->gl.init(this->disp.window);
	this->cl.init(this->gl.vbo);
	this->time.set_fps(BASE_FPS);
	
	/* init particles position */
	glBufferData(GL_ARRAY_BUFFER, PARTICLES * 3 * 4, 0, GL_STATIC_DRAW);
	global_size[0] = PARTICLES;
	global_size[1] = 0;
	clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.init_disk, 1, 0,
		global_size, 0, 0, 0, 0);
	clFinish(all.cl.queue);
}

void	All::operator=(const All &) { }
