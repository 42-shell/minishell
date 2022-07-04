# **minishell**
**Created by [jkong](https://profile.intra.42.fr/users/jkong) and [yongmkim](https://profile.intra.42.fr/users/yongmkim)**

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
