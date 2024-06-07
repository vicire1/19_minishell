#include "../../include/minishell.h"

void	print_expand(t_data *data)
{
	t_lexer	*temp;

	temp = data->first;
	while (temp->next)
	{
		printf("----------------------\n");
		printf("***EXPANDER***\n");
		printf("Pos : %i\n", temp->pos);
		printf("string : %s\n", temp->token_str);
		printf("----------------------\n");
		temp = temp->next;
	}
	printf("----------------------\n");
	printf("***EXPANDER***\n");
	printf("Pos : %i\n", temp->pos);
	printf("string : %s\n", temp->token_str);
	printf("----------------------\n");
}

char	*in_env(t_data *data, t_env *env, char *str)
{
	int		i;
	char	*tempo;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	tempo = ft_substr(str, 0, i, data);
	if (!tempo)
	{
		free(tempo);
		return (0);
	}
	while (env->next)
	{
		if (env_cmp(tempo, env->env_str))
		{
			free(tempo);
			return (env->env_str);
		}
		env = env->next;
	}
	free(tempo);
	return (NULL);
}

int	valid_quotes_env(t_data *data, t_lexer *exp)
{
	int	j;

	j = 0;
	while (exp->token_str[j])
	{
		if (exp->token_str[j] == '$' && ft_isalnum(exp->token_str[j + 1]))
		{
			if (check_quotes(exp, j, 0))
				replace_env(data, exp, j, data->expa);
		}
		j++;
	}
	return (0);
}

int	expander(t_data *data)
{
	t_lexer	*exp;

	exp = data->first;
	data->expa = malloc(sizeof(t_expander));
	while (exp->next)
	{
		if (check_v_env(exp->token_str))
			valid_quotes_env(data, exp);
		delete_quotes(data, exp);
		exp = exp->next;
	}
	if (check_v_env(exp->token_str))
		valid_quotes_env(data, exp);
	delete_quotes(data, exp);
	print_expand(data);
	free(data->expa);
	return (0);
}
