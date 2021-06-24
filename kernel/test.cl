kernel void	test_add(global int *data)
{
	int id = get_global_id(0);
	data[id]++;
}
