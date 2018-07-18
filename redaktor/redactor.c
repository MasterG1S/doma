#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

void sig_winch(int signo)
{
struct winsize size;
ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
resizeterm(size.ws_row, size.ws_col);
}

int main(int argc, char ** argv)
{
WINDOW * wnd;
WINDOW * subwnd;

initscr();
keypad(stdscr, true);
signal(SIGWINCH, sig_winch);
cbreak();
noecho();
curs_set(1);
struct winsize size;
ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
wnd = newwin(0, 0, 30,5);
//wmove(wnd,0,5);
attron(A_BOLD);

//char **v = (char **)calloc(size.ws_row, sizeof(char));
//int i;
//for(i = 0; i < size.ws_col; i++)
//{
//    v[i] = (char *)calloc(size.ws_col, sizeof(char));
//}

int wi=0;
int he=0;





/*bool ex = false;
    while ( !ex )
        {
                int ch = getch();
                
                        switch ( ch )
                                {
                                        case ERR:
                                                    printw("Please, press any key...\n"); //Если нажатия не было, напоминаем пользователю, что надо нажать клавишу
                                                                break;
                                                                        case 259: //Выходим из программы, если была нажата F2
                                                                                    ex = true;
                                                                                                break;
                                                                                                        default:  //Если всё нормально, выводим код нажатой клавиши
                                                                                                                    printw("Code of pressed key is %d\n", ch);
                                                                                                            	    move(0,0);
                                                                                                                                break;
                                                                                                                                        }
                                                                                                                                        
                                                                                                                                                refresh(); //Выводим на настоящий экран
                                                                                                                                                
                                                                                                                                                    }
*/




while(1)
{
    int c=getch();
    switch(c)
    {
    case 330:
	return 0;
    case 260:
	wi--;
	move(he,wi);
	break;
    case 259:
	he--;
	move(he,wi);
	break;
    case 261:
	wi++;
	move(he,wi);
	break;
    case 258:
	he++;
	move(he,wi);
	break;
    case 269:
	{FILE *fp;
	char name[]="ncurses.s";
	    if(fp = fopen(name, "w+b")!=NULL) 
	    {
		putwin(stdscr,fp);
	    }
	    else printf("Не удалось открыть файл");
	    
	    fclose(fp);
	    return 0;
	break;}
    case 270:
	{FILE *fp;
	char name[]="ncurses.s";
	    if(fp = fopen(name, "r")!=NULL) 
	    {
		stdscr=getwin(fp); refresh();
	    }
	    else printf("Не удалось открыть файл");
	    
	    fclose(fp);
	    return 0;
	break;}
    case 271:
	{return 0;}
    default:
	if(c>=32&&c<=126)
	{
	    printw("%c",c);
	    wi++;
	    //v[wi][he]=c;
	    refresh();
	}
	break;
    }
}
delwin(wnd);
endwin();
exit(EXIT_SUCCESS);
}
