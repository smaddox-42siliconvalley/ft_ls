#include "directory_info.h"
#include "ft_lstQueue.h"

int	cmp_mtim( void *a, void *b)
{
	struct timespec one;
	struct timespec two;

	one = (((t_dir_info*)a) -> status).st_mtim;
	two = (((t_dir_info*)b) -> status).st_mtim;
	if(one.tv_sec == two.tv_sec)
	{
		if(one.tv_nsec == two.tv_nsec)
			return(0);
		else
			return((one.tv_nsec < two.tv_nsec));
	}
	else
		return((one.tv_sec < two.tv_sec));
}

int	cmp_str( void *a, void *b)
{
	char	*str1;
	char	*str2;
	int	t;

	str1 = (((t_dir_info*)a)->print_name);
	str2 = (((t_dir_info*)b)->print_name);
	t = ft_strcmp( str1, str2);
	return(((t > 0) ? 1 : 0));
}

int	cmp_file( void *a, void *b)
{
	int t;
	t_dir_info *one;
	t_dir_info *two;

	one = (t_dir_info*)a;
	two = (t_dir_info*)b;
	if(one->status.st_mode == two->status.st_mode)
	{
		t = ft_strcmp(one->path, two->path);
		return((( t > 0 ) ? 1 : 0));
	}
	return(((S_ISDIR(one->status.st_mode) ? 1 : 0)));
}

int	checkfornull( void *data )
{
	t_list *this;

	this = (t_list*)data;
	return(((this->content == NULL) ? 1 : 0));
}

int	checkpathend( char *str )
{
	int len;

	len = ft_strlen(str);
	return(((str[len-1] == '/') ? 1 : 0));
}
