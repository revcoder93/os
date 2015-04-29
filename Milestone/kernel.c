void printString(char*);
void readString(char*);
void readSector(char*, int);
// void writeSector(char*, int);
void readFile(char* filename, char* buffer);
// void deleteFile(char* name);
// void writeFile(char* name, char* buffer, int secNum);
void executeProgram(char* name, int segment);
void terminate();
void handleInterrupt21(int,int,int,int);
int mod(int,int);
int div(int,int);
void main ()
{
// 	int i=0;
// 	char buffer1[13312];
// 	char buffer2[13312];
// 	//char line[80];
	// char buffer[512];
	// char buffer[13312];
	// printString("Hello World \0");
// 	//printString("Enter a line: \0");
// 	//readString(line);
// 	//printString(line);
// 	//readSector(buffer, 30);
// 	//printString(buffer);
	makeInterrupt21();
// 	//interrupt(0x21,1,line,0,0);
	// interrupt(0x21,0,"Hello World \0",0,0);
// 	//interrupt(0x21,0,line,0,0);
// 	//interrupt(0x21,0,0,0,0);
	// interrupt(0x21, 3, "messag\0", buffer, 0);
	// interrupt(0x21, 0, buffer, 0, 0);
// 	//interrupt(0x21, 4, "tstpr2\0", 0x2000, 0);
	interrupt(0x21, 4, "shell\0", 0x2000, 0);
// 	interrupt(0x21, 7, "messag\0", 0, 0);
// 	interrupt(0x21, 3, "messag\0", buffer, 0);
// 	interrupt(0x21, 0, buffer, 0, 0);
// buffer2[0]='h'; buffer2[1]='e'; buffer2[2]='l'; buffer2[3]='l';
// buffer2[4]='o';
// for(i=5; i<13312; i++) buffer2[i]=0x0;
// makeInterrupt21();
// interrupt(0x21,8, "testW\0", buffer2, 1);
// interrupt(0x21,3, "testW\0", buffer1, 0); 
// interrupt(0x21,0, buffer1, 0, 0);
	while(1){}
}

void printString(char* input)
{
	while (*input != 0)
	{
		char x = *input;
		interrupt(0x10, 0xE*256+x, 0, 0, 0);
		input++;
	}
}

void readString(char* input)
{
	int start = input;
	int x = 0;
	while(x != 0xd)
	{
		if (x == 0x8)
		{
			if(start<x)
			{
				interrupt(0x10, 0xE*256+0x0, 0, 0, 0);
				interrupt(0x10, 0xE*256+0x8, 0, 0, 0);
			}
		}
		x = interrupt(0x16,0,0,0,0);
		interrupt(0x10, 0xE*256+x, 0, 0, 0);
		*input = x;
		input++;
		
	}
	*input = 0xa;
	input++;
	*input = 0x0;
	interrupt(0x10, 0xE*256+0xa, 0, 0, 0);
}

void readSector(char* buffer, int sector)
{
	int c = div(sector , 18);
	int CL = mod(sector, 18) + 1;
	int DH = mod(c, 2);
	int CH = div(sector, 36);
	interrupt(0x13,2*256+1,buffer,CH*256+CL,DH*256+0);
}
// void writeSector(char* buffer, int sector)
// {
// 	int c = div(sector , 18);
// 	int CL = mod(sector, 18) + 1;
// 	int DH = mod(c, 2);
// 	int CH = div(sector, 36);
// 	interrupt(0x13,3*256+1,buffer,CH*256+CL,DH*256+0);
// }
void readFile(char* filename, char* buffer)
{
	char sectorChar;
	int sectorInt;
	int size = sizeof(filename);
	int spaceInDirectory = 0;
	int sectors = 0;
	int i = 0;
	int j = 0;
	int equal = 1;
	char directoryBuffer[512];
	char directoryEntry[32];
	char message[6];

	readSector(directoryBuffer, 2);
	//Loop through the 16 entries we have to check if the file exists.
	while (i < 512) {
		equal = 1;

		while (j < 6) {
			if (directoryBuffer[i+j] != filename[j]) {
				equal = 0;
				break;
			}
			j++;
		}
		if(equal == 1) {
			spaceInDirectory = i;
			break;
		}
		j=0;
		i += 32;
	}
	//If file not found.
	if (i == 512 || equal == 0) {
		return;
	} 
	//Loop to count the sectors the file consumes.
	while(directoryBuffer[spaceInDirectory + 6 + sectors] != 0) {
		sectors += 1;
	}
	j=0;
	//Loop to load data from the sectors to the buffer.
	while( j < sectors) {
		sectorChar = directoryBuffer[i + 6 + j];
		sectorInt = (int)sectorChar;
		readSector(buffer, sectorInt);
		j++;
		buffer +=512;
	}

}
// void deleteFile(char* name)
// {
// 	char directoryBuffer[512];
// 	char map[512];
// 	int i = 0;
// 	int j = 0;
// 	int spaceInDirectory = 0;
// 	int sectors = 0;
// 	int equal = 1;
// 	int sectorNum = 0;
// 	readSector(map,1);
// 	readSector(directoryBuffer, 2);

// 	while (i < 512) {
// 		equal = 1;

// 		while (j < 6) {
// 			if (directoryBuffer[i+j] != name[j]) {
// 				equal = 0;
// 				break;
// 			}
// 			j++;
// 		}
// 		if(equal == 1) {
// 			spaceInDirectory = i;
// 			break;
// 		}
// 		j=0;
// 		i += 32;
// 	}

// 	if (i == 512 || equal == 0) {
// 		return;
// 	}
// 	while(directoryBuffer[spaceInDirectory + 6 + sectors] != 0) {
// 		sectors += 1;
// 	}
// 	directoryBuffer[i + 1] = 0;
// 	j = 0;
// 	while(j < sectors){
// 		sectorNum = (int)directoryBuffer[i + 6 + j];
// 		map[sectorNum + 1] = 0;
// 		j++;
// 	}
// 	writeSector(map,1);
// 	writeSector(directoryBuffer,2);
// }
// void writeFile(char* name, char* buffer, int secNum)
// {
// 	char directoryBuffer[512];
// 	char map[512];
// 	int i = 0;
// 	int j = 0;
// 	int pos = 0;
// 	int sectors = 0;
// 	readSector(map,1);
// 	readSector(directoryBuffer,2);
// 	//Loop through the directory buffer to check for an empty entry.
// 	while (i < 512) {
// 			if (directoryBuffer[i] == 0) {
// 				break;
// 			}
// 		i += 32;
// 	}
// 	if(i == 512){
// 		printString("Error 404 : Space not found.");
// 		return;
// 	}
// 	//Copy the name of the file to the directory buffer.
// 	while(j < 6){
// 		directoryBuffer[i+j] = name[j];
// 		j++;
// 	}
// 	//Update the directory and map with the new data.
// 	j = 0;
// 	pos = i;
// 	while(j < 512){
// 		if(map[j] == 0){
// 			if(sectors <= secNum){
// 			map[j] = 0xFF;
// 			directoryBuffer[pos + 6] = j;
// 			writeSector(buffer,j);
// 			sectors++;
// 			pos++;
// 			}
// 		}
// 	}
// 	if(sectors != secNum){
// 		printString("Error 404 : Space not found.");
// 	}
// 	//Fill the remaining positons with 0s.
// 	while(pos < i+32){
// 		directoryBuffer[pos] = 0;
// 		pos++;
// 	}
// 	writeSector(map,1);
// 	writeSector(directoryBuffer,2);
// }
void executeProgram(char* name, int segment)
{
	char buffer[1000];
	int address = 0x0000;
	int i=0;
	char c;

	readFile(name, buffer);

	while (i < 1000) {
		c = buffer[i];
		putInMemory(segment, address, c);
		address += 0x0001;
		i++;
	}

	launchProgram(segment);

}
void terminate() 
{
	interrupt(0x21, 6, "shell\0", 0x2000, 0);
}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
	if (ax == 0)
	{
		char *x = bx;
		printString(bx);
	}
	if(ax==1)
	{
		readString(bx);
	}
	if (ax==2)
	{
		readSector(bx,cx);
	}
	if (ax == 3)
	{
		readFile(bx,cx);
	}
	if (ax == 4)
	{
		executeProgram(bx,cx);
	}
	if (ax == 5)
	{
		terminate();
	}

	// if (ax == 6)
	// {
	// 	writeSector(bx,cx);
	// }
	// if (ax == 7)
	// {
	// 	deleteFile(bx);
	// }
	// if (ax == 8)
	// {
	// 	writeFile(bx, cx, dx);
	// }
	if (ax >= 9)
	{
		printString("Error! check your AX!!!!!!!!");
	}
}

int mod(int a, int b)
{
	int i =0;
	for (; b <= a; i++)
	{
		a = a-b;
	}
	return a;
}

int div(int a, int b)
{
	int i =0;
	for (; b <= a; i++)
	{
		a = a-b;
	}
	return i;
}