#include "../../include/minishell.h"

void	free_env(t_data *data)
{
    t_env *current;
    t_env *temp;

    current = data->first_env;
    while (current)
    {
        free(current->name);
        free(current->value);
        temp = current;
        current = current->next;
        free(temp);
    }
    return ;
}

int free_all(t_data *data, char *str, int esc)
{
    if (str)
        ft_printf_fd(2, "%s\n", str);
    free_lex(data);
    free_pars(data);
    if (esc)
    {
        free_env(data);
        exit (exit_s);
    }
    return (0);
}