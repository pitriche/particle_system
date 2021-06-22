/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:57:00 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/22 14:00:42 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_HPP
# define DISPLAY_HPP

# include <iostream>
# include <SDL.h>

/*
** Interface to the graphic library
*/
struct Display
{
	public :
		Display(void);
		virtual ~Display(void);

		SDL_Window		*window;
		SDL_GLContext	gl_context;

		unsigned	res_x;
		unsigned	res_y;

		void	init(void);
		void	update(void);

	protected:
	private:
		Display(const Display &);
		void	operator=(const Display &);
};

#endif
