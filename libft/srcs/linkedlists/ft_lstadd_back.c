
#include "../../header/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst != NULL)
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
	else
		*lst = new ;
}
