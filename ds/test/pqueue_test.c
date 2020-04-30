

int Compare(const void* data_1, const void* data_2);

int main()
{
	return 1;
}

/*----------------------------------------------------------------------------*/
/*								HELPERS										  */
/*----------------------------------------------------------------------------*/
/*returns 0 when data2 == data1*/
static int CmpFunc(const void *data1, const void *data2)
{	
	return (!(data1 == data2));
}

