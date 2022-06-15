/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/06/15 18:19:05 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

size_t  ft_strlen(const char *s);

int read_safe(int fd, void *buf, size_t len)
{
    size_t  off;
    ssize_t res;
    off = 0;
    while (off < len)
    {
        res = read(fd, buf + off, len - off);
        if (res < 0)
            exit(EXIT_FAILURE);
        if (res == 0)
            return (0);
        off += res;
    }
    return (1);
}

void    write_safe(int fd, const void *buf, size_t len)
{
    size_t  off;
    ssize_t res;
    off = 0;
    while (off < len)
    {
        res = write(fd, buf + off, len - off);
        if (res < 0)
            exit(EXIT_FAILURE);
        off += res;
    }
}

void    putstr_safe(const char *str)
{
    write_safe(STDOUT_FILENO, str, ft_strlen(str));
}

void    putnbr_safe(int n)
{
    const int       sign = n < 0;
    char            buf[11];
    const size_t    count = sizeof(buf) / sizeof(*buf);
    size_t          i;
    i = count;
    if (!n)
        buf[--i] = '0';
    while (n)
    {
        buf[--i] = '0' + (1 - (sign << 1)) * (n % 10);
        n /= 10;
    }
    if (sign)
        buf[--i] = '-';
    write_safe(STDOUT_FILENO, buf + i, count - i);
}

void    puterr_safe(const char *str)
{
    write_safe(STDERR_FILENO, str, ft_strlen(str));
}
