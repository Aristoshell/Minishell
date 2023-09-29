
#include "../../header/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*anne;
	t_list	*marc;

	anne = NULL;
	while (lst != NULL)
	{
		marc = ft_lstnew(f(lst->content));
		if (!marc)
		{
			ft_lstclear(&anne, del);
			return (NULL);
		}
		ft_lstadd_back(&anne, marc);
		lst = lst->next;
	}
	return (anne);
}
