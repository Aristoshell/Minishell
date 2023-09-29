
#include "../../header/libft.h"

t_list	*ft_lstnew(void *contenu)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	newlist->content = contenu;
	newlist->next = NULL;
	return (newlist);
}
