/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:49:42 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/10/31 17:46:50 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node_ptr;

	node_ptr = (t_list *)malloc(sizeof(t_list));
	if (node_ptr == NULL)
		return (NULL);
	node_ptr->next = NULL;
	node_ptr->content = content;
	return (node_ptr);
}
