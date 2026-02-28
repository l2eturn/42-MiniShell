/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 03:22:11 by slimvutt          #+#    #+#             */
/*   Updated: 2025/09/07 03:22:11 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//------------------------------------------------
# include <stdlib.h>
# include <unistd.h>
//------------------------------------------------
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
//------------------------------------------------
# ifndef FD_MAX
#  define FD_MAX 4242
# endif
//------------------------------------------------
char	*get_next_line(int fd);
char	*get_store(int fd, char *store);
char	*get_aline(char *store);
//------------------------------------------------
void	*ft_calloc_gnl(size_t nmemb, size_t size);
size_t	ft_strlen_gnl(char *s);
int		ft_strchr_gnl(char *s, char c);
char	*ft_strjoin_gnl(char *s1, char *s2);
//------------------------------------------------
#endif
