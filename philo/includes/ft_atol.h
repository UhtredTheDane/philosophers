/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:37:41 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/12 20:38:27 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ATOL_H
# define FT_ATOL_H

# include <stddef.h>
# include <limits.h>

int		ft_isdigit(int c);
long	ft_atol(const char *nptr);
#endif
