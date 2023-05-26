#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <term.h>
#include <signal.h>
#include <termios.h>

typedef enum _ {RED = 1 , BLACK , GREEN , YELLOW, BLUE , CYAN , WHITE , MAGENTA} colour_t;		//User defined variable - colour_t
// Function prototype of the function for the colours to be used to add colour to the whitespaces.
void red() ; 
void black() ; 
void green() ; 
void yellow() ; 
void blue() ; 
void cyan() ; 
void white() ; 
void magenta() ; 
void reset();
// Function prototype of the function for the colours to be added to the text date.
void red1();
void black1();
void green1();
void yellow1();
void blue1();
void cyan1();
void white1();
void magenta1() ;
// Function prototype of the function to handle the keyboard interrupt
void signalhandle(int );
// Function prototype of the function used to move the cursor to print the numbers in one line.
void space(int , int);
// Function prototype of the function to place the time in the right place on the screen
void down();
void up();
// Function prototype of the function to give each colour the user defined variables
void printcol(colour_t);			// The function for colouring whitespaces
void datecol(colour_t);				// The function for colouring the date
// Function prototype of the function that prints the numbers
void zero(int , int );
void one (int , int);
void two (int , int);
void three (int , int);
void four (int , int);
void five (int , int);
void six(int , int);
void seven (int , int);
void eight(int , int);
void nine(int , int);
void colon(int , int);
// Function prototype of the function that chooses which number to print the numbers in as the time changes
void number(char , int , int);
// Function prototype of the function used to print the time in bold string numbers
void colour(char str[] , int , int);
// Function prototype to hide the ^c character
void restore(void);

struct termios saved;

int main (int argc, char** argv) {								// The main program begins here

        colour_t a;										// A variable of type colour_t, used to handle user input colours
        // Command line arguments when the number of arguments are one or three (For colours mainly)
        if (argc != 2 ){

                if (argc == 3){									// If a colour is given in the command line argument
                if ( strcmp (argv[2] , "red") == 0 && strcmp(argv[1] , "-c") == 0){
                        a = RED;
                } else if (strcmp (argv[2] , "black") == 0  && strcmp(argv[1] , "-c") == 0){
                        a = BLACK;
                } else if (strcmp (argv[2] , "green") == 0  && strcmp(argv[1] , "-c") == 0){
                        a = GREEN;
                } else if (strcmp (argv[2] , "yellow") == 0  && strcmp(argv[1] , "-c") == 0){
                        a = YELLOW;
                } else if (strcmp (argv[2] , "blue") == 0  && strcmp(argv[1] , "-c") == 0){
                        a = BLUE;
                } else if (strcmp (argv[2] , "cyan") == 0  && strcmp(argv[1] , "-c") == 0){
                        a = CYAN;
                } else if (strcmp (argv[2] , "white") == 0  && strcmp(argv[1] , "-c") == 0){
                        a = WHITE;
                } else if (strcmp (argv[2] , "magenta") == 0 && strcmp(argv[1] , "-c") == 0){
                        a = MAGENTA;
                } else if (strcmp (argv[1] , "-h") == 0){						// If the -h flag is given with other arguments
			printf("usage : clock -h %32s\nusage : clock -c <color> %31s\n<color-black|red|green|yellow|blue|magenta|cyan|white> supported colors\n", "quick help on cmd", "print clock with a color");
			return 0;									// Terminate main()
		} else if (!strcmp (argv[1] , "-c") == 0 && (strcmp (argv[1] , "-h") == 1 ||  !strcmp(argv[2] , "red")== 0 || !strcmp(argv[2] , "black")== 0 || !strcmp(argv[2] , "green")== 0 || !strcmp(argv[2] , "yellow")== 0 || !strcmp(argv[2] , "blue")== 0 || !strcmp(argv[2] , "cyan")== 0 || !strcmp(argv[2] , "white")== 0  || !strcmp(argv[2] , "magenta")== 0) ) {			// If the colour is given with a flag other than -c
			printf("Invalid use of arguments.\nusage : clock -h %32s\nusage : clock -c <color> %31s\n", "quick help on cmd", "print clock with a color");
			return 0;									// Terminate main()
		
		}else if (!strcmp (argv[1] , "-c") == 0 ||strcmp (argv[1] , "-h") == 1 ||  !strcmp(argv[2] , "red")== 0 || !strcmp(argv[2] , "black")== 0 || !strcmp(argv[2] , "green")== 0 || !strcmp(argv[2] , "yellow")== 0 || !strcmp(argv[2] , "blue")== 0 || !strcmp(argv[2] , "cyan")== 0 || !strcmp(argv[2] , "white")== 0  || !strcmp(argv[2] , "magenta")== 0){			// If a colour that is not supported is given
                        printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", argv[2]);
                        return 0;									// Terminate main()
		}

                }else if (argc == 1){								// If no colour is specified
                        a = WHITE;								// The default colours black and  white
		} else{										// If more than 3 command line arguments			
			
			int i;
			int j;
			for (i = 1 ; i < argc ; ++i){
				j = i + 1;
				if ( strcmp (argv[j] , "red") == 0 && strcmp(argv[i] , "-c") == 0){
                        a = RED;
			break;	
                } else if (strcmp (argv[j] , "black") == 0  && strcmp(argv[i] , "-c") == 0){
                        a = BLACK;
			break;
                } else if (strcmp (argv[j] , "green") == 0  && strcmp(argv[i] , "-c") == 0){
                        a = GREEN;
			break;
                } else if (strcmp (argv[j] , "yellow") == 0  && strcmp(argv[i] , "-c") == 0){
                        a = YELLOW;
			break;
                } else if (strcmp (argv[j] , "blue") == 0  && strcmp(argv[i] , "-c") == 0){
                        a = BLUE;
			break;
                } else if (strcmp (argv[j] , "cyan") == 0  && strcmp(argv[i] , "-c") == 0){
                        a = CYAN;
			break;
                } else if (strcmp (argv[j] , "white") == 0  && strcmp(argv[i] , "-c") == 0){
                        a = WHITE;
			break;
                } else if (strcmp (argv[j] , "magenta") == 0 && strcmp(argv[i] , "-c") == 0){
                        a = MAGENTA;
			break;
		} 
			}
		}                                                                            //End of command line argument handling for 1 or 3 user inputs
		

        signal(SIGINT , signalhandle);								// Function to respond to the key board interrupt
	
	// Hide the ^C characters afte key board interrupt
        struct termios attributes;								

        tcgetattr(STDIN_FILENO, &saved);
        atexit(restore);

        tcgetattr(STDIN_FILENO, &attributes);
        attributes.c_lflag &= ~ ECHO;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
        // End of hiding the ^c characters

        printf("\e[?25l");									// Hide the cursor 
        // To get the current system time
	time_t current_time;									// To get the current time
        struct tm * time_info;
        char timeString[9];  									// space for "HH:MM:SS\0" (time string)
	// To get the current date
	time_t T = time(NULL);

        struct tm tm = *localtime(&T);

        int day = tm.tm_mday ,  month = tm.tm_mon+1, year = tm.tm_year+1900;                    // Declare variables of type int to display the day, month and year
	//Start the clock
        clock_t begin = clock();								// Start the clock
        time(&current_time);									// Get the current time
        time_info = localtime(&current_time);

        strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);			// Store the time as a string
        system("clear");									// Clear the screen before printing starts
        colour( timeString , 8, a);								// Call the function that prints the current time according to the input colour
        datecol(a);										// Call the function to add the input colour to the date
        printf("%02d-%02d-%02d \n", year , month , day);					// Print the date
        printf("\033[20A");									// Move the cursor back to the top (where it starts printing) so that the new time prints over the past time

	// Keep printing the time every second until a key board interruprt is found
        while(1){
		
                if ((clock() - begin)/CLOCKS_PER_SEC >= 1){					// Print the time every second
                	time(&current_time);							// Check the time 
                	time_info = localtime(&current_time);					
                	strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);	// Format the time as a string
			time_t T = time(NULL);
                	struct tm tm = *localtime(&T);						// Check the time for the date
                	day = tm.tm_mday ,  month = tm.tm_mon+1, year = tm.tm_year+1900;        // Update the day, month and year
               		colour( timeString , 8, a);						// Call the function that prints the current time according to the input colour
                	datecol(a);								// Call the function to add the input colour to the date
                	printf("%02d-%02d-%02d \n", year , month , day);			// Pint the date
                        printf("\033[20A");							// Move the cursor back to the top (where it starts printing) so that the new time prints over the past time
                	begin = clock();							// Check the time now
                }

        }
        } else if (argc == 2){										// If 2 command line argumets
                
                // "-h" is a command line argument
                if ( strcmp(argv[1] , "-h") == 0){
                                printf("usage : clock -h %32s\nusage : clock -c <color> %31s\n<color-black|red|green|yellow|blue|magenta|cyan|white> supported colors\n", "quick help on cmd", "print clock with a color");
                // For any other argument entered (Errors)
                }else {
				printf("Invalid use of arguments.\nusage : clock -h %32s\nusage : clock -c <color> %31s\n", "quick help on cmd", "print clock with a color");
                }
    	} 
	return 0;										// Terminate the main function
}												// End of main function

// Function declerations for change in colour of the output of the whitespaces
void red(){
        printf("\033[;41m");
}

void black(){
        printf("\033[;40m");
}

void green(){
        printf("\033[10;42m");
}

void yellow(){
        printf("\033[10;43m");
}

void blue(){
        printf("\033[;44m");
}

void cyan(){
        printf("\033[10;46m");
}

void white(){
        printf("\033[10;47m");
}

void magenta(){
        printf("\033[10;45m");
}

void reset(){
        printf("\033[0;m");
}

// Function declaration for change in colour of the output of the date
void red1(){
        printf("\033[;31m");
}

void black1(){
        printf("\033[;30m");
}

void green1(){
        printf("\033[;32m");
}

void yellow1(){
        printf("\033[;33m");
}

void blue1(){
        printf("\033[;34m");
}

void cyan1(){
        printf("\033[;36m");
}

void white1(){
        printf("\033[;37m");
}

void magenta1(){
        printf("\033[;35m");
}

// Function declaration for key board interupt
void signalhandle (int sig){
        reset();
	printf("\e[?25h");
	system("clear");
        exit(0);

}

// Function declaration to move the cursor to print the numbers of the clock in one line
void space(int n , int row){						// Int n to store the value of which digit (Ex: 1st , 2nd , etc) , int row to store the row of the digit, as there need not be vertical positioning for the first row of the digit
		if (n == 1){						// Cursor position after the first number
        		if (row != 1){
                                printf("\033[8C");
                        }
                }else if (n==2){
                        if (row != 1){
                                printf("\033[16C");
                        }
                } else if (n == 3){
                        if (row != 1){
                                printf("\033[20C");
                        }
                } else if (n == 4){
                        if (row != 1){
                                printf("\033[27C");
                        }
                } else if (n == 5){
                        if (row != 1){
                                printf("\033[35C");
                        }
                } else if (n ==6){
                        if (row != 1){
                                printf("\033[39C");
                        }
                } else if (n == 7){
                        if (row != 1){
                                printf("\033[46C");
                        }
                } else if (n == 0){
			if (row != 1){
				printf("\033[1C");
			}
		}

}
// 2 Function declarations to to place the time in the right place
void down(){
	printf("\033[1B");
}
void up(){
	printf("\033[1A");
}

// Function declaration to give the time the colour entered
void printcol(colour_t  n){			// Parameter of type colour_t
	
	if (n == RED){				// RED, BLACK, GREEN, etc are user defined variables - enum 
		red();
	}else if (n==BLACK){
		black();
	} else if (n==GREEN){
		green();
	} else if (n == YELLOW){
		yellow();
	} else if (n == BLUE){
		blue();
	} else if (n == CYAN){
		cyan();
	} else if (n == WHITE){
		white();
	} else if (n == MAGENTA){
		magenta();
	}
}
// Function declaration to print the date in the given colour
void datecol(colour_t n){			// Parameter of type colour_t 
        if (n == RED){
                red1();
        }else if (n==BLACK){
                black1();
        } else if (n==GREEN){
                green1();
        } else if (n == YELLOW){
                yellow1();
        } else if (n == BLUE){
                blue1();
        } else if (n == CYAN){
                cyan1();
        } else if (n == WHITE){
                white1();
        } else if (n == MAGENTA){
                magenta1();
        }

}
// Function declaration to print all the numbers and the colon
void zero(int a, int n) {						// Int a to determine the colour of the digit, Int n to determine the horizontal position of where the number should be.
	down();
	for (int row =  1; row <= 5 ; ++row){
		space(n, row);						// change the location of the cursor after every row
                // Pattern to print zero
		for (int col = 1 ; col <=3 ; ++col){
			printcol(a);
			if (row == 1 || row == 5){
				printf("  ");
			} else if ((row != 1 || row != 5) && (col == 1 || col == 3)){
				printf("  ");
			} else if ((row != 1 || row != 5) && col == 2){
				printf("\033[0;m");
				printf("  ");
			}
		}
		reset();						// Remove the whitespace colouring before moving to the next line
		printf("\n");
	}
	up();
}
// 1
void one(int a , int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space (n , row);

		for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
			if (col == 1 || col == 2){
				printf("\033[0;m");
				printf("  ");
			} else {
				printf("  ");
			}
		}
		reset();
		printf("\n");
	}
	up();
}
// 2
void two(int a , int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n , row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 1 || row == 3 || row == 5){
				printf("  ");
			}else if ((row == 2 && col == 3) ||(row == 4 && col == 1)){
				printf("  ");
			} else {
				printf("\033[0;m");
				printf("  ");
			}
		}
                reset();
                printf("\n");
      	}
	up();
}
// 3
void three (int a, int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n , row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 1 || row == 3 || row ==5){
                                printf("  ");
                        } else if ((row == 2 && col == 3) ||(row == 4 && col == 3)){                                
                                printf("  ");
                        } else {
                                printf("\033[0;m");
                                printf("  ");
                        }
                }
                reset();
                printf("\n");
        }
	up();
}
// 4
void four (int a , int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n , row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 3){
                                printf("  ");
                        } else if ((row == 1 && (col == 1 || col == 3)) || (row == 2 && (col == 1 || col == 3))){
				printf("  ");
			} else if ((row == 4 && col == 3) || (row == 5 && col == 3)){
				printf("  ");
			} else {
				printf("\033[0;m");
				printf("  ");
			}
                }
                reset();
                printf("\n");
        }
	up();
}
// 5
void five(int a , int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n , row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 1 || row == 3 || row ==5){                                
                                printf("  ");
                        } else if ((row == 2 && col == 1) ||(row == 4 && col == 3)){                               
                                printf("  ");
                        } else {
                                printf("\033[0;m");
                                printf("  ");
                        }
                }
                reset();
                printf("\n");
        }
	up();
}
// 6
void six(int a, int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n , row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 1 || row == 3 || row ==5){                   
                                printf("  ");
                        } else if ((row == 2 && col == 1) ||(row == 4 && (col == 1 || col == 3))){                                
                                printf("  ");
                        } else {
                                printf("\033[0;m");
                                printf("  ");
                        }
                }
                reset();
                printf("\n");
        }
	up();
}
// 7
void seven(int a, int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n, row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 1){                                
                                printf("  ");
                        } else if (row != 1 && col == 3){                                
                                printf("  ");
                        } else {
                                printf("\033[0;m");
                                printf("  ");
                        }
                }
                reset();
                printf("\n");
        }
	up();
}
// 8
void eight( int a, int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n, row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 1 || row == 3 || row ==5){                                
                                printf("  ");
                        } else if ((row == 2 && (col == 1 || col == 3 )) ||(row == 4 && (col == 1 || col == 3))){                                
                                printf("  ");
                        } else {
                                printf("\033[0;m");
                                printf("  ");
                        }
                }
                reset();
                printf("\n");
        }
	up();
}
// 9
void nine(int a , int n){
	down();
	for (int row = 1; row <= 5 ; ++row){
		space(n , row);

                for (int col = 1 ; col <= 3 ; ++col){
			printcol(a);
                        if (row == 1 || row == 3 || row ==5){                                
                                printf("  ");
                        } else if ((row == 2 && (col == 1 || col == 3 )) ||(row == 4 && col == 3)){                                
                                printf("  ");
                        } else {
                                printf("\033[0;m");
                                printf("  ");
                        }
                }
                reset();
                printf("\n");
        }
	up();
}
// :
void colon(int a , int n){
	down();
	for (int row = 1 ; row <= 5 ; ++row){
		printcol(a);
		space(n , row);

		if (row == 2 || row == 4){			
			printf("  ");
		} else {
			printf("\033[0;m");
			printf("  ");
		}
		reset();
		printf("\n");
	}
	up();
}
// Function declaration to determine which digit to print as the time changes.
void number(char b , int k , int a){			// Arguments - The character b is the digit on the clock , integer k to determine where to print the number,  integer to determine the colour
	if (b == '1'){						// If the digit is one						
                one(a , k);					// Call the function to print the number at location k horizontally in colour a
        } else if (b == '2'){
                two(a , k);
        } else if (b == '3'){
                three(a , k);
        } else if (b == '0'){
                zero(a , k);
        } else if (b == '4'){
                four(a , k);
        } else if (b == '5'){
                five(a , k);
        } else if (b == '6'){
                six(a , k);
        }  else if (b == '7'){
                seven(a , k);
        } else if (b == '8'){
                eight(a , k);
        } else if (b == '9'){
                nine(a , k);
        }
}
// Function declaration to print all the digits on the clock
void colour(char str[] , int size ,  int a){				// Parameters - char str[] that has the current system time aas a string , int size to keep the size of the character array str[] , int a to keep the colour code
	
	int n;								// Declare a variable of type int to store the right spacing after a colon
	char z = str[0] , b = str[1] , c = str[2], d = str[3] , e = str[4] , f = str[5] , g = str[6] , h = str[7];	// Break the string time down into chars

	space(0 , 2);							// Call the function space to place the cursor in the right place to print the first digit. 

	number(z , 0, a);						// Call the function to print the digit - the first digit
	
	space(1 , 2);							// Call the function space to move the cursor to the correct position horizontally
        printf("\033[5A");						// Move the cursor up to the correct vertical position 

	number(b , 1, a);						// Print the 2nd digit 
	// Place the cursor in the right place after the 2nd digit
	space(2 , 2);							
        printf("\033[5A");

	if (c == ':'){
		n = 2;							
		colon(a, n);						// Print the colon at location n and colour a
		// Cursor position after the colon
		space(3, 2);
                printf("\033[5A");

	}
	number(d , 3, a);						// 4th digit
	// Place the cursor in the right place after the 4th digit
	space(4,2);
	printf("\033[5A");

	number (e , 4 , a);						// 5th digit
	// Place the cursor in the right place after the 5th digit
	space(5, 2);
        printf("\033[5A");

	if (f == ':'){
		n = 5;							// Print the colon at location n and colour a
		colon(a , n);
		// Cursor position after the colon
		space(6, 2);
                printf("\033[5A");
	}

	number(g , 6, a);						// 6th digit
	// Position the cursor in the right place after the 6th digit
	space(7, 2);
        printf("\033[5A");

	number(h , 7,a);						// Last digit
	
	// Move the cursor to the position where the date should be printed
	printf("\033[2B");
	printf("\033[22C");
}

struct termios saved;

// A function declaration to hide the ^C characters
void restore(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}
