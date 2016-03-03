#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_PASSWD_LEN 20

int main(void)
{
	struct termios term, oldterm;
	int i;
	char pass[MAX_PASSWD_LEN+1], ch, echo = '*';
	write(STDOUT_FILENO, "\nPassword? ", 11);
	tcgetattr(STDIN_FILENO, &oldterm);
	term = oldterm;
	term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
        char backspace = '\b', space = ' ';
	i=0;
	while (i < MAX_PASSWD_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
		if(ch != 127){
			pass[i++] = ch;
			write(STDOUT_FILENO, &echo, 1);
		}
		else if(i > 0){
			write(STDOUT_FILENO, &backspace, 1);
			write(STDOUT_FILENO, &space, 1);
			write(STDOUT_FILENO, &backspace, 1);
			i--;
		}
	}
	pass[i] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
	write(STDOUT_FILENO, "\n\nPassword: ", 12);
	write(STDOUT_FILENO, pass, strlen(pass));
	write(STDOUT_FILENO, "\n", 1);
	return 0;
}

