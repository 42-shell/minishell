/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:11:45 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 20:22:22 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "util_flag.h"
#include "string_buffer.h"
#include "string_vector.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int	_match_continuable(const char **pattern, const char **name,
	const char **pattern_backup, const char **name_backup)
{
	if (**pattern == '/' && ((*pattern)[1] == '\0' || (*pattern)[1] == '/'))
	{
		(*pattern)++;
		return (1);
	}
	if (**pattern == '\001')
	{
		*pattern_backup = (*pattern)++;
		*name_backup = *name + 1;
		return (1);
	}
	else if (**pattern != '\0' && **name == **pattern)
	{
		(*pattern)++;
		(*name)++;
		return (1);
	}
	if (*name_backup && (*name)[-1] != '\0')
	{
		*pattern = *pattern_backup;
		*name = *name_backup;
		return (1);
	}
	return (0);
}

static int	_match(const char *pattern, const char *name)
{
	const char	*pattern_backup;
	const char	*name_backup;

	pattern_backup = NULL;
	name_backup = NULL;
	while (*pattern != '\0' || *name != '\0')
	{
		if (!_match_continuable(&pattern, &name, &pattern_backup, &name_backup))
			return (0);
	}
	return (1);
}

static t_file_flags	_flags(const char *pattern)
{
	size_t			last;
	t_file_flags	result;

	result = 0;
	if (ft_strlen(pattern) != 0)
	{
		last = 0;
		while (pattern[last + 1] != '\0')
			last++;
		if (pattern[last] == '/')
			set_flag(&result, FF_DIRECTORY);
		if (pattern[0] == '.')
			set_flag(&result, FF_HIDDEN);
	}
	return (result);
}

static char	*_entry_name(char *name, t_file_flags flags)
{
	t_str_buf	*buf;

	buf = str_append(NULL, name);
	if (has_flag(flags, FF_DIRECTORY))
		buf = str_append(buf, "/");
	return (str_dispose(buf));
}

char	**glob_to_strvec(const char *path, const char *pattern)
{
	DIR *const			dir = opendir(path);
	const t_file_flags	flags = _flags(pattern);
	struct dirent		*ent;
	t_str_vec			*vec;

	if (!dir)
		return (NULL);
	vec = NULL;
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (_match(pattern, ent->d_name))
		{
			if (has_flag(flags, FF_DIRECTORY) && ent->d_type != DT_DIR)
				continue ;
			if (has_flag(flags ^ _flags(ent->d_name), FF_HIDDEN))
				continue ;
			vec = strv_append(vec, _entry_name(ent->d_name, flags));
		}
	}
	closedir(dir);
	return (strv_dispose(vec));
}
