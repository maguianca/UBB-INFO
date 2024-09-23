#include<stdio.h>
int main()
{
	int n, s = 0,x;
	printf("introduceti n:");
	scanf_s("%d",&n);
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &x);
		s = s + x;
	}
	printf("suma este:");
	printf("%d", s);

	return 0;
}