/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:29:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/07/07 15:28:16 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "All.hpp"
#include "Defines.hpp"
#include "Utils.hpp"

All	all;
static void	set_cursor(void)
{
	int		mousex;
	int		mousey;

	SDL_GetMouseState(&mousex, &mousey);

	/* set cursor for OpenCL */
	all.data.cursor[0] = (mousex * 2 - WIN_SIZEX) / (float)WIN_SIZEY;
	all.data.cursor[1] = (WIN_SIZEY - mousey * 2) / (float)WIN_SIZEY;
	all.data.cursor[2] = 0.0;

	/* set cursor for OpenGL */
	glUniform3f(all.gl.uniform.cursor_position,
		(mousex * 2 - WIN_SIZEX) / (float)WIN_SIZEY,
		(WIN_SIZEY - mousey * 2) / (float)WIN_SIZEY, 0.0);
}



static void	loop(void)
{
	size_t		global_size[2];
	std::string	tmp;
	
	if (all.cursor_update)
		set_cursor();
	
	/* enqueue kernel operations */
	clEnqueueWriteBuffer(all.cl.queue, all.cl.buffer_data, CL_TRUE, 0,
		sizeof(cl_data), (void *)&all.data, 0, 0, 0);
	global_size[0] = PARTICLES;
	global_size[1] = 0;
	clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.update_speed, 1, 0,
		global_size, 0, 0, 0, 0);

	global_size[0] = PARTICLES * 3;
	clEnqueueNDRangeKernel(all.cl.queue, all.cl.kernel.update_position, 1, 0,
		global_size, 0, 0, 0, 0);

	/* Wait for finish - sync with GPU */
	clFinish(all.cl.queue);

	all.event.update();
	all.disp.update();
	all.time.update();
	tmp = WIN_TITLE " - ";
	tmp += all.time.fps_average();
	SDL_SetWindowTitle(all.disp.window, tmp.c_str());
}

int			main(void)
{
	if ((unsigned long)PARTICLES > 25000000)
		Utils::error_quit("Nope");
	all.init();
		set_cursor();

	clFinish(all.cl.queue);
	while (1)
		loop();
	return (0);
}
