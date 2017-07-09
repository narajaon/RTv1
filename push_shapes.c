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

void		free_list(t_list **shape)
{
	t_list		*list;

	list = *shape;
	while (list)
	{
		free(list->content);
		list = list->next;
	}
	(*shape) ? free(*shape) : 0;
}
