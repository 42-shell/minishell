# minishell
### <i>As beautiful as a shell</i>

* The objective of this project is for you to create a simple shell.
* Yes, your little bash or zsh. You will learn a lot about processes and file descriptors.

<br><br>

## 0. General
* You should [download readline library](http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz) and place it upper minishell dir.
* In readline dir, Make sure `configure`, and `make`

## 1. Features
* Not interpret `\` `;`
* Use [readline](https://tiswww.case.edu/php/chet/readline/rltop.html) library
* Redirections `>` `>>` `<` `<<`
* Pipe `|`
* Priorities `&&` `||`
* Wildcard `*` for the current working directory
* Environment variables
* Signal `ctrl-C` `ctrl-D` `ctrl-\`
* Implement Builtins `echo` `cd` `pwd` `export` `unset` `env` `exit`

## 2. Overview
* [Parser](https://github.com/42-shell/minishell/wiki/1.-Parser)
* [Expander](https://github.com/42-shell/minishell/wiki/2.-Expander)
* [Executer](https://github.com/42-shell/minishell/wiki/3.-Executer)
* [Builtins](https://github.com/42-shell/minishell/wiki/4.-Builtins)
* [Module](https://github.com/42-shell/minishell/wiki/5.-Module)

## 3. Reference
* [Reference List](https://github.com/42-shell/minishell/wiki/Reference)

<br><br>

**Created by [jkong](https://profile.intra.42.fr/users/jkong) and [yongmkim](https://profile.intra.42.fr/users/yongmkim)**
