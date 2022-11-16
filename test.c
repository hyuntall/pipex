#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int a = access("./a.out", X_OK);
	printf("?? %d \n", a);
	return (1);
}