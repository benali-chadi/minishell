/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:23:53 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/11 18:20:34 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

int		ft_printf(const char *s, ...);
int		num_int(int n);
int		num_hex(unsigned int n);
char	*ft_hextoa(unsigned int n, int x);
char	*ft_addrtoa(size_t n, int x);
void	ft_putunnbr_fd(unsigned int ui, int fd);
void	ft_printchar(va_list ap, int k, int con);
void	ft_printint(va_list ap, int k, int k2, int con);
void	ft_printun(va_list ap, int k, int k2, int con);
void	ft_printstr(va_list ap, int k, int k2, int con);
void	ft_printhex_x(va_list ap, int k, int k2, int con);
void	ft_printhex_bigx(va_list ap, int k, int k2, int con);
void	ft_printstr_mns(va_list ap, int k, int k2, int con);
void	ft_printaddr(va_list ap, int k, int con);
void	ft_printper(int k, int con);

#endif
