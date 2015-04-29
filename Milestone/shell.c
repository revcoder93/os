int view(char*);
int execute(char*);
// int remove(char*);
// int copy(char*);
// int dir(char*);
// int create(char*);
char* notFoundCommand = "Command not found\r\n\0";
char* viewCommand = "view\0";
char* executeCommand = "execute\0";
char* deleteCommand = "delete \0";
char* copyCommand = "copy \0";
char* dirCommand = "dir \0";
char* createCommand = "create \0";

void main() {
	char line[80];
	char buf[512];
	char fileBuf[13312];
	while(1)
	{
		interrupt(0x21, 0, "SHELL>\0", 0, 0);
		interrupt(0x21, 1, line, 0, 0);
		if (view(line) == 1)
		{
			interrupt(0x21, 3, line + 5, fileBuf, 0);
			interrupt(0x21, 0, fileBuf, 0, 0);
		}
		else if (execute(line) == 1)
		{
			interrupt(0x21, 4, line + 8, 0x2000, 0);
			//interrupt(0x21, 4,"shell\0",0x2000,0);
			interrupt(0x21, 5,0,0,0);
		}
		// else if (delete(line) == 1) {
		// interrupt(0x21, 7, line + 7, 0, 0);
		// }
		// else if (copy(line)==1)
		// {
		// 	// int i = 0;
		// 	// char file1[6];
		// 	// while(i<6)
		// 	// {
		// 	// 	file1[i] = line[5+i];
		// 	// 	i++;
		// 	// }
		// 	interrupt(0x21,3, line+5,fileBuf,0);
		// 	interrupt(0x21,,line + 12, fileBuf,);	
		// }

		// else if (dir(line)==1)
		// {
		// 	/* code */
		// }

		// else if (create(line)==1)
		// {
		// 	/* code */
		// }

		else
		{
			interrupt(0x21, 0, notFoundCommand, 0, 0);
		}
	}
	while(1){}
}

int view(char* input)
{
	int found = 1;
	int i = 0;
	while (i < 4)
	{
		if (input[i] != viewCommand[i])
		{
			found = 0;
			break;
		}
		i++;
	}
	return found;
}

int execute(char* input)
{
	int found = 1;
	int i = 0;
	while (i < 7)
	{
		if (input[i] != executeCommand[i])
		{
			found = 0;
			break;
		}
		i++;
	}
	return found;
}

// int dir(char* input)
// {
// 	int found = 1;
// 	int i = 0;
// 	while (i < 3)
// 	{
// 		if (input[i] != dirCommand[i])
// 		{
// 			found = 0;
// 			break;
// 		}
// 		i++;
// 	}
// 	return found;
// }

// int create(char* input)
// {
// 	int found = 1;
// 	int i = 0;
// 	while (i < 6)
// 	{
// 		if (input[i] != dirCommand[i])
// 		{
// 			found = 0;
// 			break;
// 		}
// 		i++;
// 	}
// 	return found;
// }

// int remove(char* input)
// {
// 	int found = 1;
// 	int i = 0;
// 	while(i < 6)
// 	{
// 		if(input[i] != deleteCommand[i]){
// 			found = 0;
// 			break;
// 		}
// 		i++;
// 	}
// 	return found;
// }
// int copy(char* input)
// {
// 	int found = 1;
// 	int i = 0;
// 	while(i < 4)
// 	{
// 		if(input[i] != copyCommand[i]){
// 			found = 0;
// 			break;
// 		}
// 		i++;
// 	}
// 	return found;
// }