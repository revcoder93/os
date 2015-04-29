int view(char* input);
int execute(char* input);
char* notFoundCommand = "Command not found\r\n\0";
char* viewCommand = "view\0";
char* executeCommand = "execute\0";
void main() {
	char line[80];
	char buf[512];	
	char fileBuf[13312];

	while(1){
		interrupt(0x21, 0, "SHELL>\0", 0, 0);
		interrupt(0x21, 1, line, 0, 0);
		if (view(line) == 1) {
			interrupt(0x21, 3, line + 5, fileBuf, 0);
			interrupt(0x21, 0, fileBuf, 0, 0);
		} else if (execute(line) == 1) {
			interrupt(0x21, 4, line + 8, 0x2000, 0);
		} else {
			interrupt(0x21, 0, notFoundCommand, 0, 0);
		}
	}

	while(1){}
}

int view(char* input) {
	 
	 int found = 1;
	 int i = 0;
	 while (i < 4) {
	 	if (input[i] != viewCommand[i]) {
	 		found = 0;
	 		break;
	 	}
	 	i++;
	 }
	 return found;
}

int execute(char* input) {
	 
	 int found = 1;
	 int i = 0;
	 while (i < 7) {
	 	if (input[i] != executeCommand[i]) {
	 		found = 0;
	 		break;
	 	}
	 	i++;
	 }
	 return found;
}