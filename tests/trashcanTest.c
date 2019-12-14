
#include "../inc/trashcan.h"
#include "../inc/ft_printf.h"
#include <stdio.h>
#include <string.h>

int main( void )
{
	char *temp = (char*)trashmalloc(sizeof(char) * 11);
	printf("\nmain: %p\n\n", temp );
	char *this = "hello world";
	strcpy(temp, this);
	printf("\nmain: %p\n\n", temp );
	ft_printf("%s\n", temp);
	//garbage_day();
	return(0);
}
