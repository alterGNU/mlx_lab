/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagrondi <lagrondi.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:14:44 by lagrondi          #+#    #+#             */
/*   Updated: 2026/01/24 06:21:43 by lagrondi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Frees memory and sets the pointer to NULL.
 *
 * @param ptr		: void **add_ptr to free (not the pointer itself)
 * @return			: always returns NULL
 * @warning			: Must pass the address of pointer, not pointer itself
 * @example			: ft_free((void **)&str); // str is now NULL
 * @see				: ft_calloc, malloc, free
 */
void	*ft_free(void	**ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

/**
 * Create a new string which is a duplicate of the string s.
 *
 * Allocates memory for a new string and copies the entire source
 * string into it. The caller must free the returned pointer.
 *
 * @param src      : The string to duplicate (can be NULL)
 * @return         : Pointer to new string, or NULL on allocation failure
 * @note           : Caller responsible for freeing returned pointer
 * @example        : ft_strdup("test")-->"test"
 * @see            : ft_calloc, ft_strlen, ft_memcpy
 */
char	*ft_strdup(const char *src)
{
	char	*res;
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	res = (char *) malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/**
 * Allocates memory for an array and initializes it to zero.
 *
 * Unlike malloc, this function initializes all allocated bytes to 0.
 * Includes overflow protection to prevent integer overflow in size calculation.
 *
 * @param nb		: size_t, number of elements to allocate
 * @param n			: size_t, size in bytes of each element
 * @return			: SUCCESS:void *ptr, FAILURE:NULL
 * @note			: Returns NULL if nb * n would exceed INT_MAX
 * @note			: Returns NULL if malloc fails
 * @warning			: Caller must free the returned pointer with free() or ft_free()
 * @example			: int *arr = ft_calloc(10, sizeof(int)); // allocate 10 ints
 * @example			: char *str = ft_calloc(256, 1); // allocate 256 bytes
 * @see				: malloc, free, ft_free, ft_memset
 */
void	*ft_calloc(size_t nb, size_t n)
{
	void			*res;
	unsigned char	*ch;
	size_t			int_max;
	size_t			size;
	size_t			i;

	int_max = ((unsigned int) ~0 >> 1);
	size = nb * n;
	if (size && (nb >= int_max || n >= int_max))
		return (NULL);
	res = malloc(size);
	if (!res)
		return (NULL);
	ch = (unsigned char *)res;
	i = 0;
	while (i < size)
		ch[i++] = 0;
	return (res);
}

/**
 * Fills memory with a constant byte value.
 *
 * Sets every byte in the memory area of size <length> to the value <value>.
 * Useful for initializing memory blocks with a pattern or clearing bytes.
 * The function operates byte-by-byte regardless of the data type being filled.
 *
 * @param pt		: void *, pointer to the memory area to fill
 * @param value		: int, byte value (typically 0-255) to fill with
 * @param length	: size_t, number of bytes to fill
 * @return			: void *, returns the pointer 'pt' unchanged
 * @note			: <value' is implicitly converted to unsigned char
 * @warning			: No NULL ptr check --> SEGFAULT if passed
 * @example			: int arr[10]; ft_memset(arr, 0, sizeof(arr));
 * @example			: char buf[256]; ft_memset(buf, -1, 256);
 * @see				: ft_bzero, ft_memcpy, ft_memmove
 */
void	*ft_memset(void *pt, int value, size_t length)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *) pt;
	i = 0;
	while (i < length)
		str[i++] = (unsigned char) value;
	return (pt);
}

/**
 * Compare two strings <s1>, <s2> lexicographically up to <length> bytes.
 *
 * Compares the first n bytes of s1 and s2. Returns a negative value
 * if s1 is less than s2, 0 if equal, or positive if s1 is greater.
 *
 * @param s1       : First string to compare (can be NULL)
 * @param s2       : Second string to compare (can be NULL)
 * @param length   : Maximum number of bytes to compare
 * @return         : Difference between first differing bytes
 * @example        : ft_strncmp("abc", "abd", 2)-->0
 * @example        : ft_strncmp("abc", "abd", 3)-->negative value
 * @example        : ft_strncmp("b", "a", 1)-->positive value
 */
int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	size_t	i;

	i = 0;
	if (!length)
		return (i);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < length - 1)
		i++;
	return ((int)(((unsigned char)(s1[i])) - ((unsigned char)(s2[i]))));
}
