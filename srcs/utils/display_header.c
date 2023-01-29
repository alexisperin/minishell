/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperin <aperin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:25:12 by aperin            #+#    #+#             */
/*   Updated: 2023/01/28 15:25:52 by aperin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_header(void)
{
	printf("%s/* *************************************************************\
************* */\n\
/*                                                                            \
*/\n\
/*                                                        :::      ::::::::   \
*/\n\
/*   Minishell                                          :+:      :+:    :+:   \
*/\n\
/*                                                    +:+ +:+         +:+     \
*/\n\
/*   By: aperin & aburnott                          +#+  +:+       +#+        \
*/\n\
/*                                                +#+#+#+#+#+   +#+           \
*/\n\
/*                                                     #+#    #+#             \
*/\n\
/*   As beautiful as a shell                          ###   ########.fr       \
*/\n\
/*                                                                            \
*/\n\
/* ************************************************************************** \
*/%s\n", MAG, NRM);
}