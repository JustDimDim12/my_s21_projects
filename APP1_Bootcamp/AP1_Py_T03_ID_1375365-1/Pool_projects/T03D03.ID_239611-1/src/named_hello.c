#include <stdio.h>

int main() {
	int name;
	
	if (scanf("%d", &name) != 1) {
		return 1;
	}
	printf("Hello, %d!\n", name);

	return 0;
}
