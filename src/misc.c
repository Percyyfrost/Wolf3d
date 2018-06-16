int		abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	swap(int *n1, int *n2)
{
	int temp;

	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}
