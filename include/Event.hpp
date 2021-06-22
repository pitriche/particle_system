/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:57:00 by pitriche          #+#    #+#             */
/*   Updated: 2021/03/20 22:38:29 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HPP
# define EVENT_HPP

# include <iostream>
# include <SDL.h>

/*
** Interface to event library
*/
struct Event
{
	public :
		Event(void);
		virtual ~Event(void);

		void	update(void);

	protected:
	private:
		void	_keychange(SDL_Keycode kc);

		Event(const Event &src);
		void	operator=(const Event &rhs);
};

#endif
