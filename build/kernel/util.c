

void memory_copy(char *source, char *dest, int nbytes)
{
	int i;

	i = 0;
	while (i < nbytes)
	{
		*(dest + i) = *(source + i);
		i++;
	}
}

void int_to_ascii(int n, char str[])
{
	int i, sign;
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do 
	{
		str[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < n) str[i++] = '-';
	str[i] = '\0';
}
