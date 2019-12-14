#include "libft.h"

t_list *mergeList( t_list *a, t_list *b, int (*cmp)( void*, void* ))
{
	t_list *result;

	result = NULL;
	if ( a == NULL || b == NULL )
		return( ( a == NULL ) ? b : a );
	if ( cmp( a -> content, b -> content ))
	{
		result = b;
		result -> next = mergeList( a, b -> next, cmp);
	}
	else
	{
		result = a;
		result -> next = mergeList( a -> next, b, cmp);
	}
	return( result );
}

void	splitlst( t_list *source, t_list **front, t_list **back )
{
	t_list *first;
	t_list *second;
	if ( source == NULL || source -> next == NULL )
	{
		*front = source;
		*back = NULL;
		return;
	}
	first = source;
	second = source -> next;
	while ( second != NULL )
	{
		second = second -> next;
		if ( second != NULL )
		{
			first = first -> next;
			second = second -> next;
		}
	}
	*front = source;
	*back = first -> next;
	first -> next = NULL;
}
	
void	lstMergeSort( t_list **node, int (*cmp)(void*, void*))
{
	t_list *a;
	t_list *b;

	if(  *node == NULL || (*node) -> next == NULL)
		return;
	splitlst( *node, &a, &b );
	lstMergeSort(&a, cmp);
	lstMergeSort(&b, cmp);
	*node = mergeList(a, b, cmp);
}
