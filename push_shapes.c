#include "rtv1.h"

void		ft_lstback(t_list **alst, void const *content, size_t size)
{
	t_list		*lst;
	t_list		*new_elem;

	lst = *alst;
	if (!(new_elem = ft_lstnew(content, size)))
		return ;
//	printf("lst %ld\n", sizeof(new_elem->content));
//	printf("size %ld\n", size);
	while (lst->next)
	{
		lst = lst->next;
	}
	lst->next = new_elem;
	new_elem->next = NULL;
}
