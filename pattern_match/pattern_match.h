/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:14:38 by yongmkim          #+#    #+#             */
/*   Updated: 2022/06/04 23:51:01 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERN_MATCH_H
# define PATTERN_MATCH_H

# include <stddef.h>

# define PATH_MAX 1024

enum e_file_type
{
	PM_DIRECTORY = 4,
	PM_FILE = 8,
};

enum e_pattern_match_flag
{
	PM_EOF = -1,
	PM_WORD = 0,
	PM_ASTERISK = '*',
	PM_SLASH = '/',
};

typedef struct s_check_done
{
	size_t		l_name_pos;
	size_t		l_pm_pos;
	size_t		r_pm_pos;
	int			return_value;
	char		cut_char;
	size_t		cut_pos;
}				t_check_done;

typedef struct s_pattern_flag
{
	int		l_type;
	int		r_type;
}			t_pattern_flag;

typedef struct s_patttern_info
{
	char			*pwd;
	char			**pattern_split;
	int				all;
	size_t			malloc_size;
	size_t			split_size;
	size_t			split_text_cnt;
	size_t			pm_pos;
	char			**pm_interleaving;
	t_pattern_flag	pm_flag;
	t_check_done	pm_check;
}					t_pattern_info;

/*
** Pattern_match function
*/
char	**ft_pattern_match(char *pattern);
int		check_pattern(t_pattern_info *info, char *name, int file_type);
void	count_split_size(t_pattern_info *info);
int		check_dot_dot(char *name, int type);
char	*ft_get_pwd(void);

/*
** libft
*/
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t cnt, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);

#endif
