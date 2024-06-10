#include "../../include/minishell.h"

void	free_exp(t_data *data)
{
	if (data->expa->first_part)
		free(data->expa->first_part);
	if (data->expa->sec_part)
		free(data->expa->sec_part);
	if (data->expa->third_part)
		free(data->expa->third_part);
	if (data->expa->tmp_val)
		free(data->expa->tmp_val);
	if (data->expa->tmp)
		free(data->expa->tmp);
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
