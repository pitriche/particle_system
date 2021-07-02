/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/02 17:42:21 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "All.hpp"
#include "Defines.hpp"

All	all;
static void	set_cursor(void)
{
	int		mousex;
	int		mousey;
	float	cursor[3];

	SDL_GetMouseState(&mousex, &mousey);
	cursor[0] = (mousex * 2 - WIN_SIZEX) / (float)WIN_SIZEY;
	cursor[1] = (WIN_SIZEY - mousey * 2) / (float)WIN_SIZEY;
	cursor[2] = 0.0;
	clEnqueueWriteBuffer(all.cl.queue, all.cl.buffer_cursor, CL_TRUE, 0,
		3 * sizeof(float), (void *)cursor, 0, 0, 0);
}

static void	loop(void)
{
	size_t	global_size[2] = {PARTICLES, 0};

	set_cursor();

	/* enqueue kernel operations */
	clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.update_speed, 1, 0,
		global_size, 0, 0, 0, 0);

	global_size[0] = PARTICLES * 3;
	clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.update_position, 1, 0,
		global_size, 0, 0, 0, 0);

	/* retrive data */
	// clEnqueueReadBuffer(all.cl.queue, all.cl.buffer_pos, CL_TRUE, 0,
	// 	PARTICLES * 3 * sizeof(float), (void *)all.temporary_data, 0, 0, 0);

	/* Wait for finish - sync with GPU */
	clFinish(all.cl.queue);

	// glBufferData(GL_ARRAY_BUFFER, PARTICLES*3*4, all.temporary_data,
	// 	GL_STATIC_DRAW);


	all.event.update();
	all.disp.update();
	all.time.update();
	if (all.time.elapsed_frame() % 10 == 0)
	{
		std::string	tmp;

		tmp = WIN_TITLE " - ";
		tmp += all.time.fps_average();
		SDL_SetWindowTitle(all.disp.window, tmp.c_str());
	}
}

int			main(void)
{
	all.temporary_data = new float[PARTICLES * 3];
	all.init();

	size_t	global_size[2] = {PARTICLES, 0};
	clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.init_cube, 1, 0,
		global_size, 0, 0, 0, 0);
	clFinish(all.cl.queue);

	while (1)
		loop();
	return (0);
}
