#include "readWrite.h"
#include "common.h"

int main(int argc, char const *argv[])
{
	char str[20];
	readline2(STDIN_FILENO, str, 20);
	fprintf(stdout, "%s\n", str);
	return 0;
}