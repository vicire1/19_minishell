/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdecleir <vdecleir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:59:08 by lbirloue          #+#    #+#             */
/*   Updated: 2024/06/10 16:18:11 by vdecleir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int free_lex(t_data *data)
{
    t_lexer *current;
    t_lexer *temp;

    current = data->first;
    if (data->first)
    {
        while (current->next)
        {
            free(current->token_str);
            temp = current;
            current = current->next;
            free(temp);
        }
        free(current->token_str);
        free(current);
    }
    return (0);
}
