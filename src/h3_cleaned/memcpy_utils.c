/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 23:34:19 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/06 18:47:18 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Copy bit-by-bit from src to dst for length bytes.
 */
void	*ft_memcpy(void *dst, const void *src, size_t length)
{
	size_t				i;
	unsigned char		*dst_uc;
	const unsigned char	*src_uc;

	if (!length)
		return (dst);
	dst_uc = (unsigned char *) dst;
	src_uc = (const unsigned char *) src;
	i = 0;
	while (i < length)
	{
		dst_uc[i] = src_uc[i];
		i++;
	}
	return (dst);
}

/**
 * Copy words-by-words from src to dst for length bytes.
 */
void	*ft_memcpy_by_words(void *dst, const void *src, size_t len)
{
	size_t			i;
	size_t			word_count;
	size_t			*dst_word;
	const size_t	*src_word;
	size_t			remaining_bytes;	

	word_count = len / sizeof(size_t);
	dst_word = (size_t *) dst;
	src_word = (const size_t *) src;
	i = -1;
	while (++i < word_count)
		dst_word[i] = src_word[i];
	remaining_bytes = len % sizeof(size_t);
	if (remaining_bytes > 0)
	{
		ft_memcpy((unsigned char *)dst + (word_count * sizeof(size_t)), \
			(const unsigned char *)src + (word_count * sizeof(size_t)), \
			remaining_bytes);
	}
	return (dst);
}
