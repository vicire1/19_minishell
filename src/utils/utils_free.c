#include "../../include/minishell.h"

void	free_env(t_data *data)
{
    t_env *current;
    t_env *temp;

    current = data->first_env;
    if (data->first_env)
    {
        while (current->next)
        {
            free(current->env_str);
            temp = current;
            current = current->next;
            free(temp);
        }
        free(current->env_str);
        free(current);
    }
    return ;
}

void	free_exp(t_data *data)
{
	// if (data->expa->first_part) // pb avec le free_two !!!
	// {
	// 	printf("FREEEEE CK \n");
	// 	free(data->expa->first_part);
	// }
	// if (data->expa->sec_part)
	// 	free(data->expa->sec_part);
	// if (data->expa->third_part)
	// 	free(data->expa->third_part);
	// if (data->expa->tmp_val)
	// 	free(data->expa->tmp_val);
	// if (data->expa->tmp)
	// 	free(data->expa->tmp);
	// if (data->expa)
	// 	free(data->expa);
	(void)data;
	return ;
}

void	free_two(void *first, void *sec)
{
	free(first);
	first = NULL;
	free(sec);
	sec = NULL;
	return ;
}
