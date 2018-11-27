/* Example using strtol by TechOnTheNet.com */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, const char * argv[])
{
	/* Define temporary variables */
	char value[] = " 123A";
	char *eptr;
	int result;


	/* Convert the provided value to a decimal long */
	result = strtol(value, &eptr, 10);

	/* If the result is 0, test for an error */
	if (result <= 0 || *eptr != '\0')
	{
		printf("\n Error occured !!\n");
		if(*eptr != '\0')
		{
			printf("\n Invalid string \n");
		}

		/* If a conversion error occurred, display a message and exit */
		if (errno == EINVAL)
		{
			printf("Conversion error occurred: %d\n", errno);
			exit(0);
		}

		/* If the value provided was out of range, display a warning message */
		if (errno == ERANGE)
			printf("The value provided was out of range\n");
	}

	/* Display the converted result */
	printf("%d decimal\n", result);

	/* Copy a hexadecimal value into the variable */
	strcpy(value, "0x19e");

	/* Convert the provided value to a decimal long */
	result = strtol(value, &eptr, 16);

	/* If the result is 0, test for an error */
	if (result == 0)
	{
		/* If a conversion error occurred, display a message and exit */
		if (errno == EINVAL)
		{
			printf("Conversion error occurred: %d\n", errno);
			exit(0);
		}

		/* If the value provided was out of range, display a warning message */
		if (errno == ERANGE)
			printf("The value provided was out of range\n");
	}

	/* Display the converted result */
	printf("%x hexadecimal\n", result);

	return 0;
}
