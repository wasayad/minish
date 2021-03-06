/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 14:23:01 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:23:22 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strdel(char *str)
{
	ft_memdel((void *)&str);
}
