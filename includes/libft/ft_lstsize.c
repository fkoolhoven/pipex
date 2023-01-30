/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:50:54 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/10/31 21:51:47 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*search;
	int		count;

	search = lst;
	if (lst == NULL)
		return (0);
	count = 1;
	while (search->next != '\0')
	{
		search = search->next;
		count++;
	}
	return (count);
}
