/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:26 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 13:15:27 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	sz;
	size_t	i;

	i = 0;
	sz = nmemb * size;
	if ((sz == 0) || sz / nmemb != size)
	{
		tab = malloc(0);
		return (tab);
	}
	tab = malloc(sz);
	if (!tab)
		return (NULL);
	while (i < sz)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}
