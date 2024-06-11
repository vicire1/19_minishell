#include "../../include/minishell.h"

void	replace_env_init(t_data *data, t_lexer *exp, int j, t_expander *expa)
{
	expa->val_len = 0;
	expa->tmp_val = in_env(data, data->first_env, exp->token_str + j + 1);
	expa->n_len = size_env_doll(exp->token_str + j + 1);
	if (expa->tmp_val)
	{
		expa->val_len = size_env_value(expa->tmp_val);
		expa->n_len = size_env_name(expa->tmp_val);
	}
	expa->tmp = ft_strdup(exp->token_str, data);
}

void	replace_env(t_data *data, t_lexer *exp, int j, t_expander *expa)
{
	replace_env_init(data, exp, j, expa);
	expa->first_part = ft_substr(expa->tmp, 0, j, data);
	expa->sec_part = ft_substr(expa->tmp_val, expa->n_len, expa->val_len, data);
	if (expa->sec_part)
		expa->third_part = ft_substr(expa->tmp, j + expa->n_len,
				ft_strlen(expa->tmp), data);
	else
		expa->third_part = ft_substr(expa->tmp, j + expa->n_len + 1,
				ft_strlen(expa->tmp), data);
	free_two(exp->token_str, expa->tmp);
	expa->tmp = ft_strjoin(expa->first_part, expa->sec_part, data);
	if (expa->tmp)
		exp->token_str = ft_strjoin(expa->tmp, expa->third_part, data);
	else
		exp->token_str = ft_strjoin(expa->first_part, expa->third_part, data);
	// free_two(expa->first_part, expa->third_part); //aautre solution
	// printf("AV %s\n", expa->first_part);
	// free(expa->first_part);
	// printf("AP\n");
	// expa->first_part = NULL;
	free(expa->tmp);
	expa->tmp = NULL;
}
