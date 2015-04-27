


int func(.......)
{
	if()
		return 0;
	if()
		return 1;
	else
		return 2;
}

int main()
{
	int ret;

	ret = func(.....)

	....;

	switch(ret)
	{
		case 0:
				;
			break;
		case 1:
				;
			break;
		case 2:
				;
			break;
		default:
			_exit(1);		// abort();
	}




	exit(0);
}












