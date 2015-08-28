int strlen(char *x){
	int k = 0;
	while (x[k++]);
	return k;
}
char strcpy(char *x, char *y){
	char *a;
	char *z;
	while ((*(a++) = *(x++)));
	while ((*(z++) = *(y++)));
	x = z;
	return *a;
}
void strncpy(char *x, char *y, int k)
{
	int i = 0;
	while (i++ < k)
	{
		x[i] = y[i];
	}
}
char strcat(char *x, char *y)
{
	int k = 0;
	int a = 0;
	while (x[k++]);
	k--;
	while (x[k++] = y[a++]);
}
char strncat(char *x, char *y, int k)
{
	int j = 0;
	int a = 0;
	while (x[j++]);
	j--;
	while ((a++) < k)
	{
		x[j] = y[a];
	}
}

