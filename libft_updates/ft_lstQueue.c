#include "ft_lstQueue.h"

t_lstQ	ft_newlstQueue( void )
{
	t_lstQ newq;
	newq.head = NULL;
	newq.tail = NULL;
	return( newq );
}

void	dummy( void *content, size_t size )
{
	return;
}

void	ft_lstQ( t_lstQ *queue, void *content, size_t content_size )
{
	t_list *node;
	
	node = ft_lstnew( content, content_size );
	if (( queue -> head == NULL ) && ( queue -> tail == NULL ))
	{
		queue -> head = node;
		queue -> tail = node;
	}
	else
	{
		( queue -> tail ) -> next = node;
		queue -> tail = ( queue -> tail ) -> next;
	}
}

void	*ft_lstDQ( t_lstQ *queue )
{
	void *content;
	t_list *temp;
	
	if (( queue -> head ) == NULL )
		return( NULL );
	content = ( queue -> head ) -> content;
	temp = ( queue -> head ) -> next;
	ft_lstdelone( &( queue -> head ), &dummy );
	queue -> head = temp;
	if (( queue -> head ) == NULL )
		queue -> tail == NULL;
	return( content );
}

