#include "rtv1.h"

void		ft_lstback(t_list **alst, void const *content, size_t size)
{
	t_list		*lst;

	lst = *alst;
	if (!lst)
		*alst = ft_lstnew(content, size);
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = ft_lstnew(content, size);
	}
}
