#include "../../include/minishell.h"

int	check_len_exit_s(void)
{
	int	cp;
	int	ret;

	ret = 1;
	cp = g_exit_s;
	while (cp > 10)
	{
		ret ++;
		cp = cp/10;
	}
	return (ret);
}

void	replace_env_init(t_data *data, t_lexer *exp, int j, t_expander *expa)
{
	expa->tmp_val = NULL;
	expa->val_len = 0;
	expa->n_len = size_env_doll(exp->token_str + j + 1);

	if (in_env(data, data->first_env, exp->token_str + j + 1, expa))
	{
		if (expa->exit_check == 1)
		{
			expa->val_len = check_len_exit_s();
			expa->n_len = 2;
			expa->exit_check = 0;
		}
		else
		{
			expa->val_len = size_env_value(expa->tmp_val);
			expa->n_len = size_env_name(expa->tmp_val);
		}
	}
	expa->tmp = ft_strdup(exp->token_str, data);
}

void	free_replace_env(t_expander *expa)
{
	if (expa->tmp)
		free(expa->tmp);
	if (expa->first_part)
		free(expa->first_part);
	if (expa->sec_part)
		free(expa->sec_part);
	if (expa->third_part)
		free(expa->third_part);
	if (expa->tmp_val)
		free(expa->tmp_val);
	return ;
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
	free(exp->token_str);
	free(expa->tmp);
	expa->tmp = NULL;
	expa->tmp = ft_strjoin(expa->first_part, expa->sec_part, data);
	// printf("TMP %s \n", expa->tmp);
	if (expa->tmp)
		exp->token_str = ft_strjoin(expa->tmp, expa->third_part, data);
	else
		exp->token_str = ft_strjoin(expa->first_part, expa->third_part, data);
	free_replace_env(expa);
	return ;
}
