/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfarm <bfarm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:56:55 by bfarm             #+#    #+#             */
/*   Updated: 2022/08/20 19:13:13 by bfarm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h> 
//printf
//perror, strerror -- system error messages

# include <readline/readline.h>
//readline

# include <readline/history.h>
//rl_clear_history, rl_on_new_line,
//rl_replace_line, rl_redisplay, add_history

# include <stdlib.h>
//malloc 
//free 
//exit
//getenv -- get value of key in env

# include <fcntl.h>
//open

# include <unistd.h>
//write
//read
//close
//access
//fork
//getcwd -- get working directory pathname
//chdir -- change current working directory
//unlink --remove directory entry
//execve -- execute a file
//dup, dup2 -- duplicate an existing file descriptor
//pipe -- create descriptor pair for interprocess communication
//ttyname, isatty, ttyslot -- get name of associated terminal (tty) from fd

# include <signal.h>
//signal
//sigaction
//kill

# include <sys/stat.h>
//stat, lstat, fstat -- get file status

# include <sys/wait.h>

# include <dirent.h>
// opendir
//readdir
//closedir

# include <termios.h>
//tcgetattr, tcsetattr -- manipulating the termios structure

# include <curses.h> 
# include <term.h> 
//tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs -->
// --> direct curses interface to the terminfo capability database
#endif