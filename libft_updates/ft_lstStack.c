#include "libft.h"

void	ft_lstPush( t_list **alst, void const *content, size_t content_size )
{
	ft_lstadd( alst, ft_lstnew( content, content_size ) );
}

void	dummy_del( void *content, size_t size )
{
	return;
}

void	*ft_lstPop( t_list **alst)
{
	void *temp;
	t_list *node;
	
	if ( *alst == NULL )
		return( NULL );
	node = ( *alst ) -> next;
	temp = (*alst) -> content;
	ft_lstdelone( alst, &dummy_del ); 
	*alst = node;
	return( temp );
}
