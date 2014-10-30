int main(int argc, char **argv)
{
	int fd;
	unsigned char key_val;
	int ret;
	
	struct pollfd fds[1];

	fd = open("/dev/buttons", O_RDWR);
	
	if(fd < 0)
	printf("can't open!\n");

	fds[0].fd = fd; 
	fds[0].events = POLLIN ; //select the event is POLLIN, also is /dev/buttons has button
	
	while(1)
	{
		ret = poll(fds,1,5000);

		if(ret == 0)
			printf("time out\n");
		else	
		{
			read(fd,&eky_val,1);
			printf("key_val=Ox%x\n",key_val);
			 printf("key_val = 0x%x\n", key_val);
		}	
	}

	return 0;
}
