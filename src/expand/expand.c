/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:16:09 by vdecleir          #+#    #+#             */
/*   Updated: 2024/05/14 15:29:20 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

int	check_v_env(char *str)
{
	printf("entre check_v_env\n");
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i]== '$')
			return (1);
		i++;
	}
	return (0);
}

void	env_str(char *str)
{
	printf("entre env_str\n");
	//int	j = 0;
	//check le nb de "$"
	//while (i < nb$)
	//	if (compter le nb de quotes(str) == changer)
	//		j = realloc et replace(str, j)		//le j sera la position a partir de ou recommencer a check
	//	i++

	return;
}

int		check_quotes(char *str)
{
	printf("entre check_quotes\n");
	return (0);
}

void	transform_str(char *str)
{
	
	printf("entre transform_str\n");
	return;
}

/*
int	expander(t_data *data)
{
	t_parser exp;
	int	i;

	exp = data->first_parser;
	i = 0;
	while (exp->next)
	{
		i = 0;
		while(exp->cmd[i])
		{
			if (check_v_env(exp->cmd[i]) == 1)		//ici je check si y a un ou plusieur $			ok?
				env_str(exp->cmd[i]);				//ici je check dabord les quotes autour du $..., [si c'est bon, [si le $....(jusqu'a != lettre) existe, je le remplace]]sinon je change pas.
			if(check_quotes(exp->cmd[i]) == 1)		//ici je check si il reste des quotes
				transform_str(exp->cmd[i]);			//ici je tej les quotes que je peu tej
			i++;
		}
	}
	return (0);
}
*/


/*
CHECK SI $			=======check_v_env

SI $, CHECK QUTOTES,
SI DOUBLE OU RIEN, REMPLACER PAR ENV OU RIEN SI PAS DANS ENV
SI SIMPLE, JUSTE RETIRER LES SIMPLE QUOTES

SI PAS DE $



??????????????????????????????????
?????? ECHO $$USER le chiffre
?????? ECHO $$$$USER le chiffre 2 fois 

*/



/*----MAIN DE TEST-----*/

int main()
{
	int i = 0;

	char	*str = malloc(sizeof(char) * 100);

	str = "t$est";

	if(check_v_env(str) == 1)		//ici je check si y a un ou plusieur $			ok?
		env_str(str);				//ici je check dabord les quotes autour du $..., [si c'est bon, [si le $....(jusqu'a != lettre) existe, je le remplace]]sinon je change pas.
	if(check_quotes(str) == 1)		//ici je check si il reste des quotes
		transform_str(str);			//ici je tej les quotes que je peu tej
	
	printf("\nstr finale : %s\n",str);
}