/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidrissi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:33:46 by aidrissi          #+#    #+#             */
/*   Updated: 2019/12/25 16:26:52 by aidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

#define BUFFER_SIZE 1000

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_chr(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_return(char **ch, int n, int fd, char **line);
int		get_next_line(int fd, char **line);

#endif
