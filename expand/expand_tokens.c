/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/31 14:26:23 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*find_var(char *str, t_hash_table *env);

char *remove_and_expand_quotes(char *token, t_hash_table *env, int stat)
{
    int i = 0, len = safe_strlen(token);
    int quote = 0;
    int final_len = 0;

    // FIRST PASS: calculate needed length
    while (i < len)
    {
        if (!quote && (token[i] == '\'' || token[i] == '"'))
        {
            quote = token[i++];
            continue;
        }
        else if (quote && token[i] == quote)
        {
            quote = 0;
            i++;
            continue;
        }
        if (token[i] == '$' && token[i + 1] && quote != '\'')
        {
            if (token[i + 1] == '?')
            {
                char *status = ft_itoa(stat);
                final_len += safe_strlen(status);
                free(status);
                i += 2;
            }
            else
            {
                char *env_val = find_var(token + i + 1, env);
                final_len += safe_strlen(env_val);
                i++; // Skip $
                while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
                    i++;
            }
            continue;
        }
        final_len++;
        i++;
    }

    // Allocate exact memory (+1 for null-terminator)
    char *result = malloc(final_len + 1);

    // SECOND PASS: build the actual result
    i = 0;
    int j = 0;
    quote = 0;
    while (i < len)
    {
        if (!quote && (token[i] == '\'' || token[i] == '"'))
        {
            quote = token[i++];
            continue;
        }
        else if (quote && token[i] == quote)
        {
            quote = 0;
            i++;
            continue;
        }
        if (token[i] == '$' && token[i + 1] && quote != '\'')
        {
            if (token[i + 1] == '?')
            {
                char *status = ft_itoa(stat);
                int slen = safe_strlen(status);
                ft_memmove(result + j, status, slen);
                j += slen;
                free(status);
                i += 2;
            }
            else
            {
                char *env_val = find_var(token + i + 1, env);
                int elen = safe_strlen(env_val);
                ft_memmove(result + j, env_val, elen);
                j += elen;
                i++; // Skip $
                while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
                    i++;
            }
            continue;
        }
        result[j++] = token[i++];
    }
    result[j] = '\0';

    return result;
}


void expand_tokens(t_tokens **tokens, t_hash_table *env, int stat)
{
    t_tokens *tmp = *tokens;

    while (tmp->type != NEWL)
    {
        char *new_token = remove_and_expand_quotes(tmp->token, env, stat);
        free(tmp->token);
        tmp->token = new_token;
        tmp = tmp->next;
    }
}
