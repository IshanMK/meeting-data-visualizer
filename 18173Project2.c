/*E / 18 / 173
 * Kasthuripitiya K.A.I.M.
 * Project - 02
 * Date - 08 / 10 / 21*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Function Prototypes*/
void noInputs(char *) ;
void invalidOption(char *) ;
void onlyCSV() ;
void negativeOption() ;
void moreFlags() ;
void notEnough() ;
void invalid_l_option() ;
void readfile(char *) ;
void noduplicates(int type) ;
void finalize(int) ;
void sortList(int) ;
int findLargest(int) ;
void printGraph(int , int , int) ;
char ** gargv ; //global variable
int gargc ;
int len(int) ;
int sum(int) ;
int linesCounter = 0  , x , y , length , total = 0;
int largestElement ;

/*Structures*/
typedef struct node1{
	char lineread[100] ;
	struct node1 * nextline ;
}details_t ;
details_t *readline , *head_details ;

typedef struct node2{
	char username[50] ;
	int participants ;
	int time_duration ;
	int no_of_meetings ;
	struct node2 * newnode ;
}finaldetails ;
finaldetails *head_finaldetails , *temp_finaldetails;
void reverse() ;

/*Main Function*/
int main(int argc , char **argv){
	gargv = argv ;	
	//Checking for --scaled flag
	int scaled_Flag = 0 ;
	for(int index = argc - 1 ; index >= 1 ; index--){
		if(strcmp(argv[index] , "--scaled") == 0){
			scaled_Flag = 1 ;
		}
	}
	
	//checking for -l flag
	int l_Flag = 0 ;
	for(int index = argc - 1 ; index >= 1 ; index--){
		if(strcmp(argv[index] , "-l") == 0){
			l_Flag = 1 ;
		}
	}

	//check for -m flag
	int m_Flag = 0 ;
	for(int index = argc - 1 ; index >= 1 ; index--){
		if(strcmp(argv[index] , "-m") == 0){
			m_Flag = 1 ;
		}
	}

	//checkinf for -p Flag
	int p_Flag = 0 ;
	for(int index = argc - 1 ; index >= 1 ; index--){
		if(strcmp(argv[index] , "-p") == 0){
			p_Flag = 1 ;
		}
	}

	//checking for -t Flag
	int t_Flag = 0 ;
	for(int index = argc - 1 ; index >= 1 ; index--){
		if(strcmp(argv[index] , "-t") == 0){
			t_Flag = 1 ;
		}
	}

	//If there is only one argument is there
	if(argc == 1){
		noInputs(argv[0]) ;
	}

	else if(argc > 1){
		/*If there are multiple args
		 * -m with -p
		 * -m with -t
		 * -p with -t
		 *  If any of the above cases found an error will occur*/
		if((m_Flag == 1) && (p_Flag == 1)){
			moreFlags() ;
		}
		if((m_Flag == 1) && (t_Flag == 1)){
			moreFlags() ;
		}
		if((p_Flag == 1) && (t_Flag == 1)){
			moreFlags() ;
		}

		/*If all of the argumets are not available then it checks for other args
		 * eg -x -g -f*/
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				//If there is a argument whose string length is <= 4
				if(strncmp(argv[index] , "-" , 1) == 0){
					invalidOption(argv[index]) ;
				}
			}
		}
		//gg ff
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				if(strlen(argv[index]) <= 4){
					onlyCSV() ;
				}
			}
		}
		/*If there isn;t any of the flags both (invalid / valid )*/
			
		int validFileFound = 0 ;
		char const split[] = "." ;
		char *token ;
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				//If there is an argumnet whose lenght is less than 4 , then it is not a file
					
				//check the whole string to find a "."
				int dotfound = 0 ;
				for(int i = 0 ; i < strlen(argv[index]) ; i++){
					if(argv[index][i] == '.'){
						dotfound = 1 ;
					}
				}

				//if there isn't a dot this is not a file
				if(dotfound == 0){
					onlyCSV() ;
				}

				//checking whether it can be splitted into parts
				//if dot is found
				else if(dotfound == 1){
					char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
					strcpy(str , argv[index]) ;
					token = strtok(argv[index] , split) ;
					token = strtok(NULL , split) ;
					if(strcmp(token , "csv")  == 0){
						validFileFound = 1 ;
						readfile(str) ;
						//printf("ReadFile %s\n" , str) ;
						free(str) ;
					}
					else{
						onlyCSV() ;
					}
				}
			}

			
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(0 , 10 , 0) ;
				//printf("Graph(0 , 10 , 0)\n") ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		if((scaled_Flag == 0) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = 1 ; index < argc ; index++){
				if(strncmp(argv[index],  "-" , 1) == 0){
					if(argv[index][1] != 'l'){
						invalidOption(argv[index]) ;
					}
				}
			}
		}
		if((scaled_Flag == 0) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			int elements ; 
			validFileFound = 0 ;
			token = NULL ;
			for(int index = 1 ; index < argc ; index++){				
				if(strcmp(argv[argc - 1] , "-l") == 0){
					notEnough() ;
				}
				if(strcmp(argv[index] , "-l") == 0){
					int isDigit = atoi(argv[index + 1]) ;
					
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					else if((isDigit == 0) && (isDigit > 0)){
						elements = isDigit ;
						for(int counter = 1 ; counter < argc ; counter++){
							if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							if(counter == elements){
								continue ;
							}
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
						}
						char split[] = "." ;
						int dotfound = 0 ;
						for(int counter = 1 ; counter < argc ; counter++){
							if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							if(counter == elements){
								continue ;
							}
							for(int i = 0 ; i < strlen(argv[counter]) ; i++){
							if(argv[counter][i] == '.'){
								dotfound = 1 ;
							}
						}
						//if there isn't a dot this is not a file
						if(dotfound == 0){
							onlyCSV() ;
						}

						//checking whether it can be splitted into parts
						//if dot is found
						else if(dotfound == 1){
							char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
							strcpy(str , argv[counter]) ;
							token = strtok(argv[counter] , split) ;
							token = strtok(NULL , split) ;
							if(strcmp(token , "csv")  == 0){
								validFileFound = 1 ;
								readfile(str) ;
								//printf("ReadFile %s\n" , str) ;
								free(str) ;
							}
							else{
								onlyCSV() ;
							}

						}
						}
					}

				}
			}
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(0 , elements , 0) ;
				//printf("Graph(0 , %d , 1)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}
		/*Only --scaled Flag is available*/
		/*First Of all We need to check whether the --scaled is available but other args are not available
		 * If --scaled -x*/
		if((scaled_Flag == 1) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			/*Then we need to check for other invalid args*/
			for(int index = argc - 1 ; index >= 1 ; index--){
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ; //no need to check again the --scaled flag  , it there are multiple --scaled flags all of them will be skipped.
				}
				/*If there is invalid argument eg. -x is available it will generate an error*/
				if(strncmp(argv[index] , "-" , 1) == 0){
					invalidOption(argv[index]) ;
				}
			}	
		}
		/*if --scaled hh*/
		if((scaled_Flag == 1) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ;
				}
				if(strlen(argv[index]) <= 4){
					onlyCSV() ;
				}
			}
		}
		/*If there is a string whose string length can be > 4
		 * Then we need to check whether the argument is a .csv file
		 * Here also only --scaled flag is available*/
		validFileFound = 0 ; //reset the valid file counter
		//char split[] = "." ;
		token  = NULL ; //reset the char pointer
		if((scaled_Flag == 1) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index --){
				//If there are multiple args of --scaled all of them will be skipped
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ;
				}
				
				//check the whole string to find a "."
				int dotfound = 0 ;
				for(int i = 0 ; i < strlen(argv[index]) ; i++){
					if(argv[index][i] == '.'){
						dotfound = 1 ;
					}
				}

				//if there isn't a dot this is not a file
				if(dotfound == 0){
					onlyCSV() ;
				}

				//checking whether it can be splitted into parts
				//if dot is found
				else if(dotfound == 1){
					char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
					strcpy(str , argv[index]) ;
					token = strtok(argv[index] , split) ;
					token = strtok(NULL , split) ;
					if(strcmp(token , "csv")  == 0){
						validFileFound = 1 ;
						readfile(str) ;
						//printf("ReadFile %s\n" , str) ;
						free(str) ;
					}
					else{
						onlyCSV() ;
					}
				}
			}
			
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(0 , 10 ,1) ;
				//printf("Graph(0 , 10 , 1)\n") ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}

		}
		
		/*If csv files are found then those will be read
		if(validFileFound == 1){
			printf("Graph(0 , 10 , 1)\n") ;
			exit(0) ;
		}
		else if(validFileFound == 0){
			noInputs(argv[0]) ;
		}
		*/
		/*If --scled -l -x */
		if((scaled_Flag == 1) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ;
				}
				if(strcmp(argv[index] , "-l") == 0){
					continue ;
				}
				if(strncmp(argv[index] , "-" , 1) == 0){
					invalidOption(argv[index]) ;
				}
			}
		
		}
		/*Then we need to check when --scaled flag and -l flag is available but no -m flag , -p flag , -t flag*/
		if((scaled_Flag == 1) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 0)){
			int elements = 0 , intPosition = 0 ;
			//There may be multiple --scaled and -l flags
			for(int index = 1 ; index < argc ; index++){
				//If there are multiple --scaled , all of them will be skipped
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ;
				}
				if(index == intPosition){
					continue ;
				}
				int isnum = atoi(argv[index]) ;
				//Then check for non -l args
				if((strcmp(argv[index] , "-l") != 0) && (isnum == 0)){
					if(strlen(argv[index]) <= 4){
						onlyCSV() ;
					}
					validFileFound = 0 ;
					char split[] = "." ;
					char *token ;
					//check the whole string to find a "."
					int dotfound = 0 ;
					for(int i = 0 ; i < strlen(argv[index]) ; i++){
						if(argv[index][i] == '.'){
							dotfound = 1 ;
						}
					}

					//if there isn't a dot this is not a file
					if(dotfound == 0){
						onlyCSV() ;
					}

					//checking whether it can be splitted into parts
					//if dot is found
					else if(dotfound == 1){
						char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
						strcpy(str , argv[index]) ;
						token = strtok(argv[index] , split) ;
						token = strtok(NULL , split) ;
						if(strcmp(token , "csv")  == 0){
							validFileFound = 1 ;
							readfile(str) ;
							//printf("ReadFile %s\n" , str) ;
							free(str) ;
						}
						else{
							onlyCSV() ;
						}
					}
					//invalidOption(argv[index]) ;
				}

				//check for -l args
				else if(strcmp(argv[index] , "-l") == 0){
					//Then the next element should be checked
					int isDigit = atoi(argv[index + 1]) ; //try to convert argument to integer
					//If it is not a digit it will return an error
					//if not a digit isDigit == 0
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					//If it is a positive number
					else if((isDigit != 0) && (isDigit > 0)){
						intPosition = index + 1 ;
						elements = isDigit ;
						//validFileFound = 0 ;
						//int validFileFound = 0 ;
						for(int counter = index + 2 ; counter < argc ; counter++){
							if(strcmp(argv[counter] , "--scaled") == 0){
								continue ;
							}
							else if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							else if(strncmp(argv[counter] , "-" , 1)  == 0){
								invalidOption(argv[counter]) ;
							}
						}
						
						for(int counter = index + 2; counter < argc ; counter++){
							if(strcmp(argv[counter] , "--scaled") == 0){
								continue ;
							}
							if(strcmp(argv[counter] , "-l") == 0){
								invalid_l_option() ;
							}
							if(strcmp(argv[argc - 1] , "-l") == 0){
								notEnough() ;
							}
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
									
							char split[] = "." ;
							char *token ;
							//check the whole string to find a "."
							int dotfound = 0 ;
							for(int i = 0 ; i < strlen(argv[counter]) ; i++){
								if(argv[counter][i] == '.'){
									dotfound = 1 ;
								}
							}

							//if there isn't a dot this is not a file
							if(dotfound == 0){
								onlyCSV() ;
							}

							//checking whether it can be splitted into parts
							//if dot is found
							else if(dotfound == 1){
								char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
								strcpy(str , argv[counter]) ;
								token = strtok(argv[counter] , split) ;
								token = strtok(NULL , split) ;
								if(strcmp(token , "csv")  == 0){
									validFileFound = 1 ;
									readfile(str) ;
									//printf("ReadFile %s\n" , str) ;
									free(str) ;
								}
								else{
									onlyCSV() ;
								}
							}
						}
						
					}
					//if -l is the last argument
					else if(strcmp(argv[index] , "-l") == 0){
						notEnough() ;
					}
				}
			}
			
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(0 , elements , 1) ;
				//printf("Graph(0 , %d , 1)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}
		/*If a single argument is found 
		 * -m -p -t
		 *  but it depends on -l and --scaled*/
		//1.Only -m flag is there + (-x -f )
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 1) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				if(strcmp(argv[index] , "-m") == 0){
					continue ;
				}
				if(strncmp(argv[index] , "-" , 1) == 0){
					invalidOption(argv[index]) ;
				}
			}
		}
		
		//Only -m flag is there are there + (gg , ff)
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 1) && (p_Flag == 0) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				//There can be multiple -m args  , all of them will be skipped
				if(strcmp(argv[index] , "-m") == 0){
					continue ;
				}
				//If there is a string whose length is <= 4 , it is not a .csv file  
				if(strlen(argv[index]) <= 4){
					onlyCSV() ;
				}
			}	
		}

		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 1) && (p_Flag == 0) && (t_Flag == 0)){
			validFileFound = 0 ; //reset
			for(int index = 1 ; index < argc ; index++){
				//There can be mutiple m arguments all of them will be skipped
				if(strcmp(argv[index] , "-m") == 0){
					continue ;
				}
				token = NULL ; //reset the token pointer
				int dotfound = 0 ;
				//checking for . in the given string
				for(int i = 0 ; i < strlen(argv[index]) ; i++){
					if(argv[index][i] == '.'){
						dotfound = 1 ;
					}
				}
				if(dotfound == 0){
					onlyCSV() ;
				}
				
				else if(dotfound == 1){
					char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
					strcpy(str , argv[index]) ;
					token = strtok(argv[index] , split) ;
					token = strtok(NULL , split) ;
					if(strcmp(token , "csv")  == 0){
						validFileFound = 1 ;
						readfile(str) ;
						//printf("ReadFile %s\n" , str) ;
						free(str) ;
					}
					else{
						onlyCSV() ;
					}
				}	
			}

			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(0 , 10 , 0) ;
				//printf("Graph(0 , 10 , 0)\n") ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		//1.Only -p flag is there + (-x -f )
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 1) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				if(strcmp(argv[index] , "-p") == 0){
					continue ;
				}
				if(strncmp(argv[index] , "-" , 1) == 0){
					invalidOption(argv[index]) ;
				}
			}
		}
		
		//Only -p flag is there are there + (gg , ff)
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 1) && (t_Flag == 0)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				//There can be multiple -p args  , all of them will be skipped
				if(strcmp(argv[index] , "-p") == 0){
					continue ;
				}
				//If there is a string whose length is <= 4 , it is not a .csv file  
				if(strlen(argv[index]) <= 4){
					onlyCSV() ;
				}
			}	
		}

		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 1) && (t_Flag == 0)){
			validFileFound = 0 ; //reset
			for(int index = 1 ; index < argc ; index++){
				//There can be mutiple -p arguments all of them will be skipped
				if(strcmp(argv[index] , "-p") == 0){
					continue ;
				}
				token = NULL ; //reset the token pointer
				int dotfound = 0 ;
				//checking for . in the given string
				for(int i = 0 ; i < strlen(argv[index]) ; i++){
					if(argv[index][i] == '.'){
						dotfound = 1 ;
					}
				}
				if(dotfound == 0){
					onlyCSV() ;
				}
				
				else if(dotfound == 1){
					char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
					strcpy(str , argv[index]) ;
					token = strtok(argv[index] , split) ;
					token = strtok(NULL , split) ;
					if(strcmp(token , "csv")  == 0){
						validFileFound = 1 ;
						readfile(str) ;
						//printf("ReadFile %s\n" , str) ;
						free(str) ;
					}
					else{
						onlyCSV() ;
					}
				}	
			}

			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(1 , 10 , 0) ;
				//printf("Graph(1 , 10 , 0)\n") ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		//1.Only -t flag is there + (-x -f )
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 1)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				if(strcmp(argv[index] , "-t") == 0){
					continue ;
				}
				if(strncmp(argv[index] , "-" , 1) == 0){
					invalidOption(argv[index]) ;
				}
			}
		}
		
		//Only -t flag is there are there + (gg , ff)
		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 1)){
			for(int index = argc - 1 ; index >= 1 ; index--){
				//There can be multiple -m args  , all of them will be skipped
				if(strcmp(argv[index] , "-t") == 0){
					continue ;
				}
				//If there is a string whose length is <= 4 , it is not a .csv file  
				if(strlen(argv[index]) <= 4){
					onlyCSV() ;
				}
			}	
		}

		if((scaled_Flag == 0) && (l_Flag == 0) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 1)){
			validFileFound = 0 ; //reset
			for(int index = 1 ; index < argc ; index++){
				//There can be mutiple m arguments all of them will be skipped
				if(strcmp(argv[index] , "-t") == 0){
					continue ;
				}
				token = NULL ; //reset the token pointer
				int dotfound = 0 ;
				//checking for . in the given string
				for(int i = 0 ; i < strlen(argv[index]) ; i++){
					if(argv[index][i] == '.'){
						dotfound = 1 ;
					}
				}
				if(dotfound == 0){
					onlyCSV() ;
				}
				
				else if(dotfound == 1){
					char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
					strcpy(str , argv[index]) ;
					token = strtok(argv[index] , split) ;
					token = strtok(NULL , split) ;
					if(strcmp(token , "csv")  == 0){
						validFileFound = 1 ;
						readfile(str) ;
						//printf("ReadFile %s\n" , str) ;
						free(str) ;
					}
					else{
						onlyCSV() ;
					}
				}	
			}

			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(2 , 10 , 0) ;
				//printf("Graph(2 , 10 , 0)\n") ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		/*If there can be a argument like -m -l
		 * -l should always followed by an integer*/
		if((scaled_Flag == 0) && (l_Flag == 1) && (m_Flag == 1) && (p_Flag == 0) && (t_Flag == 0)){
			int elements = 0 , intPosition = 0 , validFileFound = 0 ; 
			token = NULL ; //reset char pointer
			int last = 0 ;
			for(int index = 1 ; index < argc ; index++){
				if(strcmp(argv[index] , "-m") == 0){
					continue ;
				}
				if(last == argc -1){
					break ;
				}
				//Then check for non -l args
				int isnum = atoi(argv[index]) ;
				if((strcmp(argv[index] , "-l") != 0) && (isnum == 0)){
					if(index == intPosition){
						continue ;
					}
					validFileFound = 0 ;
					char split[] = "." ;
					char *token ;
					//check the whole string to find a "."
					int dotfound = 0 ;
					for(int i = 0 ; i < strlen(argv[index]) ; i++){
						if(argv[index][i] == '.'){
							dotfound = 1 ;
						}
					}

					//if there isn't a dot this is not a file
					if(dotfound == 0){
						onlyCSV() ;
					}

					//checking whether it can be splitted into parts
					//if dot is found
					else if(dotfound == 1){
						char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
						strcpy(str , argv[index]) ;
						token = strtok(argv[index] , split) ;
						token = strtok(NULL , split) ;
						if(strcmp(token , "csv")  == 0){
							validFileFound = 1 ;
							readfile(str) ;
							//printf("ReadFile %s\n" , str) ;
							free(str) ;
						}
						else{
							//printf("----\n") ;
							//exit(0) ;
							onlyCSV() ;
						}
					}
					//invalidOption(argv[index]) ;
				}

				//check for -l args
				else if(strcmp(argv[index] , "-l") == 0){
					//Then the next element should be checked
					int isDigit = atoi(argv[index + 1]) ; //try to convert argument to integer
					//If it is not a digit it will return an error
					//if not a digit isDigit == 0
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					//If it is a positive number
					else if((isDigit != 0) && (isDigit > 0)){
						intPosition = index + 1 ;
						elements = isDigit ;
						for(int counter = index + 2 ; counter < argc ; counter++){
							//If multiple -m flags available all of them will be skipped
							if(strcmp(argv[counter] , "-m") == 0){
								continue ;
							}
							//Skip all -l flags
							else if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							else if(strncmp(argv[counter] , "-" , 1)  == 0){
								invalidOption(argv[counter]) ;
							}
						}
						
						for(int counter = index + 2; counter < argc ; counter++){
							//If there are multiple -m all of them will be skipped
							if(strcmp(argv[counter] , "-m") == 0){
								continue ;
							}
							//If -x flag found
							if(strncmp(argv[counter] , "-" ,1) == 0){
								invalidOption(argv[counter]) ;
							}
							//If another -l is found
							if(strcmp(argv[counter] , "-l") == 0){
								invalid_l_option() ;
							}
							//If -l is the last argument
							if(strcmp(argv[argc - 1] , "-l") == 0){
								notEnough() ;
							}
							//If the string length is less than it couldn't  be a .csv file
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
							char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
							strcpy(str , argv[counter]) ;
							token = strtok(argv[counter] , split) ;
							token = strtok(NULL , split) ;
							if(strcmp(token , "csv")  == 0){
								validFileFound = 1 ;
								readfile(str) ;
								//printf("ReadFile %s\n" , str) ;
								free(str) ;
							}
							else{
								onlyCSV() ;
							}
							if(counter == argc - 1){
								last = argc - 1 ;
							}
							
						}
					}
					//if -l is the last argument
					else if(strcmp(argv[index] , "-l") == 0){
						notEnough() ;
					}
				}
			}
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(0 , elements , 0) ;
				//printf("Graph(0 , %d , 0)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		/*-p flag followed by -l */
		if((scaled_Flag == 0) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 1) && (t_Flag == 0)){
			int elements = 0 , intPosition = 0 ; 
			token = NULL ; //reset char pointer
			int last = 0 ;
			for(int index = 1 ; index < argc ; index++){
				if(strcmp(argv[index] , "-p") == 0){
					continue ;
				}
				if(last == argc - 1){
					break ; //If the function had read all the files
				}
				//Then check for non -l args
				int isnum = atoi(argv[index]) ;
				if((strcmp(argv[index] , "-l") != 0) && (isnum == 0)){
					if(index == intPosition){
						continue ;
					}
					if(strlen(argv[index]) <= 4){
						onlyCSV() ;
					}
					validFileFound = 0 ;
					char split[] = "." ;
					char *token ;
					//check the whole string to find a "."
					int dotfound = 0 ;
					for(int i = 0 ; i < strlen(argv[index]) ; i++){
						if(argv[index][i] == '.'){
							dotfound = 1 ;
						}
					}

					//if there isn't a dot this is not a file
					if(dotfound == 0){
						onlyCSV() ;
					}

					//checking whether it can be splitted into parts
					//if dot is found
					else if(dotfound == 1){
						char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
						strcpy(str , argv[index]) ;
						token = strtok(argv[index] , split) ;
						token = strtok(NULL , split) ;
						if(strcmp(token , "csv")  == 0){
							validFileFound = 1 ;
							readfile(str) ;
							//printf("ReadFile %s\n" , str) ;
							free(str) ;
						}
						else{
							onlyCSV() ;
						}
					}
					//invalidOption(argv[index]) ;
				}

				//check for -l args
				else if(strcmp(argv[index] , "-l") == 0){
					//Then the next element should be checked
					int isDigit = atoi(argv[index + 1]) ; //try to convert argument to integer
					//If it is not a digit it will return an error
					//if not a digit isDigit == 0
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					//If it is a positive number
					else if((isDigit != 0) && (isDigit > 0)){
						intPosition = index + 1 ;
						elements = isDigit ;
						for(int counter = index + 2 ; counter < argc ; counter++){
							//If there are multiple -p args , all of them will be skipped
							if(strcmp(argv[counter] , "-p") == 0){
								continue ;
							}
							//If there are multiple -l args , all if them will be skipped
							else if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							else if(strncmp(argv[counter] , "-" , 1)  == 0){
								invalidOption(argv[counter]) ;
							}
						}
						
						for(int counter = index + 2; counter < argc ; counter++){
							//If there are multiple -p args , all of them will be skipped
							if(strcmp(argv[counter] , "-p") == 0){
								continue ;
							}
							//If -x flags
							if(strncmp(argv[counter] , "-" ,1) == 0){
								invalidOption(argv[counter]) ;
							}
							//If another -l is found
							if(strcmp(argv[counter] , "-l") == 0){
								invalid_l_option() ;
							}
							//If -l is the last argument
							if(strcmp(argv[argc - 1] , "-l") == 0){
								notEnough() ;
							}
							//If the string is less than 4  , it is not a valid .csv file
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
							char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
							strcpy(str , argv[counter]) ;
							token = strtok(argv[counter] , split) ;
							token = strtok(NULL , split) ;
							if(strcmp(token , "csv")  == 0){
								validFileFound = 1 ;
								readfile(str) ;
								//printf("ReadFile %s\n" , str) ;
								free(str) ;
							}
							else{
								onlyCSV() ;
							}
							if(counter == argc -1){
								last = argc - 1 ;
							}
						}
					}
					//if -l is the last argument
					else if(strcmp(argv[index] , "-l") == 0){
						notEnough() ;
					}
				}
			}
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(1 , elements , 0) ;
				//printf("Graph(1 , %d , 0)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		/*If there is a arg with -t , and -l*/
		if((scaled_Flag == 0) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 1)){
			int elements = 0 , intPosition = 0 ; 
			token = NULL ; //reset char pointer
			int last = 0 ;
			for(int index = 1 ; index < argc ; index++){
				if(strcmp(argv[index] , "-t") == 0){
					continue ;
				}
				if(last == argc - 1){
					break ; //if the function had read all the files
				}
				//Then check for non -l args
				int isnum = atoi(argv[index]) ;
				if((strcmp(argv[index] , "-l") != 0) && (isnum == 0)){
					if(index == intPosition){
						continue ;
					}
					if(strlen(argv[index]) <= 4){
						onlyCSV() ;
					}
					validFileFound = 0 ;
					char split[] = "." ;
					char *token ;
					//check the whole string to find a "."
					int dotfound = 0 ;
					for(int i = 0 ; i < strlen(argv[index]) ; i++){
						if(argv[index][i] == '.'){
							dotfound = 1 ;
						}
					}

					//if there isn't a dot this is not a file
					if(dotfound == 0){
						onlyCSV() ;
					}

					//checking whether it can be splitted into parts
					//if dot is found
					else if(dotfound == 1){
						char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
						strcpy(str , argv[index]) ;
						token = strtok(argv[index] , split) ;
						token = strtok(NULL , split) ;
						if(strcmp(token , "csv")  == 0){
							validFileFound = 1 ;
							readfile(str) ;
							//printf("ReadFile %s\n" , str) ;
							free(str) ;
						}
						else{
							onlyCSV() ;
						}
					}
					//invalidOption(argv[index]) ;
				}

				//check for -l args
				else if(strcmp(argv[index] , "-l") == 0){
					//Then the next element should be checked
					int isDigit = atoi(argv[index + 1]) ; //try to convert argument to integer
					//If it is not a digit it will return an error
					//if not a digit isDigit == 0
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					//If it is a positive number
					else if((isDigit != 0) && (isDigit > 0)){
						intPosition = index + 1 ;
						elements = isDigit ;
						for(int counter = index + 2 ; counter < argc ; counter++){
							//If there are multiple -t args , all of them wil be skipped
							if(strcmp(argv[counter] , "-t") == 0){
								continue ;
							}
							//If there are multiple -l , args , all of them will be skipped
							else if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							//If -x arg found
							else if(strncmp(argv[counter] , "-" , 1)  == 0){
								invalidOption(argv[counter]) ;
							}
						}
						
						for(int counter = index + 2; counter < argc ; counter++){
							//If there are multiple -t args , all of them will be skipped
							if(strcmp(argv[counter] , "-t") == 0){
								continue ;
							}
							//If -x
							if(strncmp(argv[counter] , "-" ,1) == 0){
								invalidOption(argv[counter]) ;
							}
							//If aother -l is found
							if(strcmp(argv[counter] , "-l") == 0){
								invalid_l_option() ;
							}
							//If -l is the last arg
							if(strcmp(argv[argc - 1] , "-l") == 0){
								notEnough() ;
							}
							//If the string is less than 4  , it is not  a valid file
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
							char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
							strcpy(str , argv[counter]) ;
							token = strtok(argv[counter] , split) ;
							token = strtok(NULL , split) ;
							if(strcmp(token , "csv")  == 0){
								validFileFound = 1 ;
								printf("ReadFile %s\n" , str) ;
								free(str) ;
							}
							else{
								onlyCSV() ;
							}
							if(counter == argc -1){
								last = argc - 1 ;
							}
						}
					}
					//if -l is the last argument
					else if(strcmp(argv[index] , "-l") == 0){
						notEnough() ;
					}
				}
			}
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(2 , elements , 0) ;
				//printf("Graph(2 , %d , 0)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		/*If --scaled with -m and -l*/
		if((scaled_Flag == 1) && (l_Flag == 1) && (m_Flag == 1) && (p_Flag == 0) && (t_Flag == 0)){
			int elements = 0 , intPosition = 0 ; 
			token = NULL ; //reset char pointer
			int last = 0 ;
			for(int index = 1 ; index < argc ; index++){
				if(strcmp(argv[index] , "-m") == 0){
					continue ;
				}
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ;
				}
				if(last == argc - 1){
					break ; //if the function had read all the files
				}
				//Then check for non -l args
				int isnum = atoi(argv[index]) ;
				if((strcmp(argv[index] , "-l") != 0) && (isnum == 0)){
					if(index == intPosition){
						continue ;
					}
					if(strlen(argv[index]) <= 4){
						onlyCSV() ;
					}
					validFileFound = 0 ;
					char split[] = "." ;
					char *token ;
					//check the whole string to find a "."
					int dotfound = 0 ;
					for(int i = 0 ; i < strlen(argv[index]) ; i++){
						if(argv[index][i] == '.'){
							dotfound = 1 ;
						}
					}

					//if there isn't a dot this is not a file
					if(dotfound == 0){
						onlyCSV() ;
					}

					//checking whether it can be splitted into parts
					//if dot is found
					else if(dotfound == 1){
						char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
						strcpy(str , argv[index]) ;
						token = strtok(argv[index] , split) ;
						token = strtok(NULL , split) ;
						if(strcmp(token , "csv")  == 0){
							validFileFound = 1 ;
							readfile(str) ;
							//printf("ReadFile %s\n" , str) ;
							free(str) ;
						}
						else{
							onlyCSV() ;
						}
					}
					//invalidOption(argv[index]) ;
				}

				//check for -l args
				else if(strcmp(argv[index] , "-l") == 0){
					//Then the next element should be checked
					int isDigit = atoi(argv[index + 1]) ; //try to convert argument to integer
					//If it is not a digit it will return an error
					//if not a digit isDigit == 0
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					//If it is a positive number
					else if((isDigit != 0) && (isDigit > 0)){
						intPosition = index + 1 ;
						elements = isDigit ;
						for(int counter = index + 2 ; counter < argc ; counter++){
							//If there are multiple -t args , all of them wil be skipped
							if(strcmp(argv[counter] , "-m") == 0){
								continue ;
							}
							if(strcmp(argv[index] , "--scaled") == 0){
								continue ;
							}
							//If there are multiple -l , args , all of them will be skipped
							else if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							//If -x arg found
							else if(strncmp(argv[counter] , "-" , 1)  == 0){
								invalidOption(argv[counter]) ;
							}
						}
						
						for(int counter = index + 2; counter < argc ; counter++){
							//If there are multiple -t args , all of them will be skipped
							if(strcmp(argv[counter] , "-m") == 0){
								counter++ ;
								continue ;
							}
							if(strcmp(argv[argc - 1] , "--scaled") == 0){
								counter++ ;
								continue ;
							}
							if(strcmp(argv[counter] , "--scaled") == 0){
								counter++ ;
								continue ;
							}
							//If -x
							if(strncmp(argv[counter] , "-" ,1) == 0){
								invalidOption(argv[counter]) ;
							}
							//If aother -l is found
							if(strcmp(argv[counter] , "-l") == 0){
								invalid_l_option() ;
							}
							//If -l is the last arg
							if(strcmp(argv[argc - 1] , "-l") == 0){
								notEnough() ;
							}
							//If the string is less than 4  , it is not  a valid file
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
							char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
							strcpy(str , argv[counter]) ;
							token = strtok(argv[counter] , split) ;
							token = strtok(NULL , split) ;
							if(strcmp(token , "csv")  == 0){
								validFileFound = 1 ;
								readfile(str) ;
								//printf("ReadFile %s\n" , str) ;
								free(str) ;
							}
							else{
								onlyCSV() ;
							}
							if(counter == argc -1){
								last = argc - 1 ;
							}
						}
					}
					//if -l is the last argument
					else if(strcmp(argv[index] , "-l") == 0){
						notEnough() ;
					}
				}
			}
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(0 , elements , 1) ;
				//printf("Graph(0 , %d , 1)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		/*If -t -l with --scaled*/
		if((scaled_Flag == 1) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 1) && (t_Flag == 0)){
			int elements = 0 , intPosition = 0 ; 
			token = NULL ; //reset char pointer
			int last = 0 ;
			for(int index = 1 ; index < argc ; index++){
				if(strcmp(argv[index] , "-p") == 0){
					continue ;
				}
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ;
				}
				if(last == argc - 1){
					break ; //if the function had read all the files
				}
				//Then check for non -l args
				int isnum = atoi(argv[index]) ;
				if((strcmp(argv[index] , "-l") != 0) && (isnum == 0)){
					if(index == intPosition){
						continue ;
					}
					if(strlen(argv[index]) <= 4){
						onlyCSV() ;
					}
					validFileFound = 0 ;
					char split[] = "." ;
					char *token ;
					//check the whole string to find a "."
					int dotfound = 0 ;
					for(int i = 0 ; i < strlen(argv[index]) ; i++){
						if(argv[index][i] == '.'){
							dotfound = 1 ;
						}
					}

					//if there isn't a dot this is not a file
					if(dotfound == 0){
						onlyCSV() ;
					}

					//checking whether it can be splitted into parts
					//if dot is found
					else if(dotfound == 1){
						char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
						strcpy(str , argv[index]) ;
						token = strtok(argv[index] , split) ;
						token = strtok(NULL , split) ;
						if(strcmp(token , "csv")  == 0){
							validFileFound = 1 ;
							readfile(str) ;
							//printf("ReadFile %s\n" , str) ;
							free(str) ;
						}
						else{
							onlyCSV() ;
						}
					}
					//invalidOption(argv[index]) ;
				}

				//check for -l args
				else if(strcmp(argv[index] , "-l") == 0){
					//Then the next element should be checked
					int isDigit = atoi(argv[index + 1]) ; //try to convert argument to integer
					//If it is not a digit it will return an error
					//if not a digit isDigit == 0
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					//If it is a positive number
					else if((isDigit != 0) && (isDigit > 0)){
						intPosition = index + 1 ;
						elements = isDigit ;
						for(int counter = index + 2 ; counter < argc ; counter++){
							//If there are multiple -t args , all of them wil be skipped
							if(strcmp(argv[counter] , "-p") == 0){
								continue ;
							}
							if(strcmp(argv[index] , "--scaled") == 0){
								continue ;
							}
							//If there are multiple -l , args , all of them will be skipped
							else if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							//If -x arg found
							else if(strncmp(argv[counter] , "-" , 1)  == 0){
								invalidOption(argv[counter]) ;
							}
						}
						
						for(int counter = index + 2; counter < argc ; counter++){
							//If there are multiple -t args , all of them will be skipped
							if(strcmp(argv[counter] , "-p") == 0){
								counter++ ;
								continue ;
							}
							if(strcmp(argv[argc - 1] , "--scaled") == 0){
								counter++ ;
								continue ;
							}
							if(strcmp(argv[counter] , "--scaled") == 0){
								counter++ ;
								continue ;
							}
							//If -x
							if(strncmp(argv[counter] , "-" ,1) == 0){
								invalidOption(argv[counter]) ;
							}
							//If aother -l is found
							if(strcmp(argv[counter] , "-l") == 0){
								invalid_l_option() ;
							}
							//If -l is the last arg
							if(strcmp(argv[argc - 1] , "-l") == 0){
								notEnough() ;
							}
							//If the string is less than 4  , it is not  a valid file
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
							char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
							strcpy(str , argv[counter]) ;
							token = strtok(argv[counter] , split) ;
							token = strtok(NULL , split) ;
							if(strcmp(token , "csv")  == 0){
								validFileFound = 1 ;
								readfile(str) ;
								//printf("ReadFile %s\n" , str) ;
								free(str) ;
							}
							else{
								onlyCSV() ;
							}
							if(counter == argc -1){
								last = argc - 1 ;
							}
						}
					}
					//if -l is the last argument
					else if(strcmp(argv[index] , "-l") == 0){
						notEnough() ;
					}
				}
			}
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(1 , elements , 1) ;
				//printf("Graph(1 , %d , 1)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}

		/*If -t -l with --scaled*/
		if((scaled_Flag == 1) && (l_Flag == 1) && (m_Flag == 0) && (p_Flag == 0) && (t_Flag == 1)){
			int elements = 0 , intPosition = 0 ; 
			token = NULL ; //reset char pointer
			int last = 0 ;
			for(int index = 1 ; index < argc ; index++){
				if(strcmp(argv[index] , "-t") == 0){
					continue ;
				}
				if(strcmp(argv[index] , "--scaled") == 0){
					continue ;
				}
				if(last == argc - 1){
					break ; //if the function had read all the files
				}
				//Then check for non -l args
				int isnum = atoi(argv[index]) ;
				if((strcmp(argv[index] , "-l") != 0) && (isnum == 0)){
					if(index == intPosition){
						continue ;
					}
					if(strlen(argv[index]) <= 4){
						onlyCSV() ;
					}
					validFileFound = 0 ;
					char split[] = "." ;
					char *token ;
					//check the whole string to find a "."
					int dotfound = 0 ;
					for(int i = 0 ; i < strlen(argv[index]) ; i++){
						if(argv[index][i] == '.'){
							dotfound = 1 ;
						}
					}

					//if there isn't a dot this is not a file
					if(dotfound == 0){
						onlyCSV() ;
					}

					//checking whether it can be splitted into parts
					//if dot is found
					else if(dotfound == 1){
						char *str = (char *)malloc(sizeof(strlen(argv[index]))) ;
						strcpy(str , argv[index]) ;
						token = strtok(argv[index] , split) ;
						token = strtok(NULL , split) ;
						if(strcmp(token , "csv")  == 0){
							validFileFound = 1 ;
							readfile(str) ;
							//printf("ReadFile %s\n" , str) ;
							free(str) ;
						}
						else{
							onlyCSV() ;
						}
					}
					//invalidOption(argv[index]) ;
				}

				//check for -l args
				else if(strcmp(argv[index] , "-l") == 0){
					//Then the next element should be checked
					int isDigit = atoi(argv[index + 1]) ; //try to convert argument to integer
					//If it is not a digit it will return an error
					//if not a digit isDigit == 0
					int isnum = isdigit(argv[index + 1][0]) ; //to find out whether this string zero

					//but someone can give 0 as -0 or +0
					if(strlen(argv[index + 1]) == 2){
						if(strcmp(argv[index + 1] , "+0") == 0){
							exit(0) ;
						}
						else if(strcmp(argv[index + 1] , "-0") == 0){
							exit(0) ;
						}
					}

					if((isDigit != 0) && (isDigit < 0)){ //If it a negative number
						negativeOption() ;
					}
					//If it is just 0 , it will end the program
					else if((isDigit == 0) && (isnum != 0)){
						exit(0) ;
					}

					//If it no not an integer then , it is not a valid argument for -l
					else if(isDigit == 0){
						invalid_l_option() ;
					}
					//If it is a positive number
					else if((isDigit != 0) && (isDigit > 0)){
						intPosition = index + 1 ;
						elements = isDigit ;
						for(int counter = index + 2 ; counter < argc ; counter++){
							//If there are multiple -t args , all of them wil be skipped
							if(strcmp(argv[counter] , "-t") == 0){
								continue ;
							}
							if(strcmp(argv[index] , "--scaled") == 0){
								continue ;
							}
							//If there are multiple -l , args , all of them will be skipped
							else if(strcmp(argv[counter] , "-l") == 0){
								continue ;
							}
							//If -x arg found
							else if(strncmp(argv[counter] , "-" , 1)  == 0){
								invalidOption(argv[counter]) ;
							}
						}
						
						for(int counter = index + 2; counter < argc ; counter++){
							//If there are multiple -t args , all of them will be skipped
							if(strcmp(argv[counter] , "-t") == 0){
								counter++ ;
								continue ;
							}
							if(strcmp(argv[argc - 1] , "--scaled") == 0){
								counter++ ;
								continue ;
							}
							if(strcmp(argv[counter] , "--scaled") == 0){
								counter++ ;
								continue ;
							}
							//If -x
							if(strncmp(argv[counter] , "-" ,1) == 0){
								invalidOption(argv[counter]) ;
							}
							//If aother -l is found
							if(strcmp(argv[counter] , "-l") == 0){
								invalid_l_option() ;
							}
							//If -l is the last arg
							if(strcmp(argv[argc - 1] , "-l") == 0){
								notEnough() ;
							}
							//If the string is less than 4  , it is not  a valid file
							if(strlen(argv[counter]) <= 4){
								onlyCSV() ;
							}
							char *str = (char *)malloc(sizeof(strlen(argv[counter]))) ;
							strcpy(str , argv[counter]) ;
							token = strtok(argv[counter] , split) ;
							token = strtok(NULL , split) ;
							if(strcmp(token , "csv")  == 0){
								validFileFound = 1 ;
								readfile(str) ;
								//printf("ReadFile %s\n" , str) ;
								free(str) ;
							}
							else{
								onlyCSV() ;
							}
							if(counter == argc -1){
								last = argc - 1 ;
							}
						}
					}
					//if -l is the last argument
					else if(strcmp(argv[index] , "-l") == 0){
						notEnough() ;
					}
				}
			}
			/*If csv files are found then those will be read*/
			if(validFileFound == 1){
				printGraph(2 , elements , 1) ;
				//printf("Graph(2 , %d , 1)\n" , elements) ;
				exit(0) ;
			}
			else if(validFileFound == 0){
				noInputs(argv[0]) ;
			}
		}
	}
	return 0 ;
}

void noInputs(char *str){
	printf("No input files were given\n"
	       "usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n" , str) ;
	exit(0) ;
}

void invalidOption(char *str){
	printf("Invalid option [%s]\n"
	       "usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n" , str , gargv[0]) ;
	exit(0) ;
}

void invalid_l_option(){
	printf("Invalid options for [-l]\n"
	       "usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n" , gargv[0]) ;
	exit(0) ;
}
void notEnough(){
	printf("Not enough options for [-l]\n"
	       "usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n" , gargv[0]) ;
	exit(0) ;
}
void onlyCSV(){
	printf("Only .csv files should be given as inputs.\n") ;
	exit(0) ;
}
void moreFlags(){
	printf("Cannot plot multiple parameters in same graph.\n"
	       "usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n" , gargv[0]) ;
	exit(0) ;
}

void negativeOption(){
	printf("Invalid option(negative) for [-l]\n"
	       "usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n" , gargv[0]) ;
	exit(0) ;
}


void readfile(char *fileNamePtr){
	/*File pointer to hold reference*/
	FILE *filePtr = NULL ;

	/*
	 * Open the file in read mode(r)
	 *
	 * */
	filePtr = fopen(fileNamePtr , "r") ;
	/*If fopen() returns NULL the operation was unsuccessful*/
	if(filePtr == NULL){
		printf("Cannot open one or more given files\n") ;
		exit(0) ;
	}

	/*If the file opens successfully*/
	//printf("File Open successfully.\n") ;
	/*Read line by line until the End OF File*/
	head_details  = NULL ;
	readline = (details_t *)malloc(sizeof(details_t)) ;
	while(fscanf(filePtr , "%s" , (readline -> lineread)) != EOF){
		readline -> nextline = head_details ;
		head_details = readline ;
		readline = (details_t *)malloc(sizeof(details_t)) ;
		linesCounter++ ;
	}

}

void finalize(int type){
	details_t *current;
	head_finaldetails  = NULL;
	const char split1[] = "," ; //string will be splitted into parts by a comma(,)
	const char split2[] = ":" ; //string will be splitted into parts by a colon(:)
	//const char split3[] = "." ;
	char *token1 , *token2 /*, * token3*/;
	for(current = head_details ; current != NULL ; current = current -> nextline){

		//create a memory entry
		temp_finaldetails = (finaldetails *)malloc(sizeof(finaldetails)) ;

		//store the name of the user
		token1 = strtok((current -> lineread) , split1)  ;
		strcpy((temp_finaldetails -> username) , token1) ;
		if(type == 1){
			//store the no of participants
			token1 = strtok(NULL , split1) ;
			temp_finaldetails -> participants = atoi(token1) ;
		}
		if(type == 2){
			token1 = strtok(NULL , split1) ;

			//store the meeting time
			token1 = strtok(NULL , split1) ;
			//token3 = token1 ;
			//find no of hours
			token2 = strtok(token1 , split2) ;
			//if(token2 == NULL){
			int hours = atoi(token2) ;

			//find no of minutes
			token2 = strtok(NULL , split2) ;
			int minutes = atoi(token2) ;

			int avg_time = hours * 60 + minutes ;
			temp_finaldetails -> time_duration = avg_time ;
		}
		if(type == 0){
			//no of meetings
			temp_finaldetails -> no_of_meetings = 1 ;
		}

		temp_finaldetails -> newnode = head_finaldetails ;
		head_finaldetails = temp_finaldetails ;

		free(current) ;
	}
}

void noduplicates(int type){
	finaldetails *ptr1 , *ptr2 , *dup ;
	ptr1  = head_finaldetails ;
	if(head_finaldetails == NULL){
		exit(0) ;
	}
	else{
	/*Pick elements one by one*/
		while((ptr1 != NULL) && (ptr1 -> newnode != NULL)){
			ptr2 = ptr1 ;
			/*Compare the picked element with the rest
		 	* of the elements*/

			while(ptr2 -> newnode != NULL){
				/*If duplicate then delete it*/
				if(strcmp(ptr1 -> username , ptr2 -> newnode -> username) == 0){
					dup = ptr2 -> newnode ;
					if(type == 0){
						ptr1 -> no_of_meetings += dup -> no_of_meetings ;
					}
					else if(type == 1){
						ptr1 -> participants += dup -> participants ;
					}
					else if(type == 2){
						ptr1 -> time_duration += dup -> time_duration ;
					}

					ptr2 -> newnode = ptr2 -> newnode -> newnode ;
					free(dup) ;
				}
				else{
					ptr2 = ptr2 -> newnode ;
				}

			}
			ptr1 = ptr1 -> newnode ;
		}
	}
}

void reverse(){

// Initialize current, previous and next pointers
	finaldetails *prev = NULL ;
	finaldetails *current = head_finaldetails, *next = NULL;
	while (current != NULL){
		next = current -> newnode ;
		current -> newnode = prev ;
		prev = current ;
		current = next ;
	}
	head_finaldetails = prev ;

}

void sortList(int type){
	/*Sorting will be done according to the type
	 * type 0 default type - no_of_meetings
	 * type 1 - participants
	 * type 2 -time duration
	*/

	finalize(type) ;
	noduplicates(type) ;
	reverse() ;
		finaldetails *current = head_finaldetails , *index ;
		//this will point to head
		//finaldetails *prevNode1 = NULL , *prevNode2 = NULL , *node1 = head_finaldetails , *node2 = head_finaldetails , *temp = NULL ;
		//It first checks, whether the head is equal to null which means the list is empty.
		 /* If the head is NULL program will be terminated*/
		if(head_finaldetails == NULL){
			exit(0) ;
		}

		else{
			while(current != NULL){
				//index will point to node next to current/
				index = current -> newnode ;
				while(index != NULL){
					//If the current node's data < index node's data/
					if(type == 0){

						if(current -> no_of_meetings <= index -> no_of_meetings){
							char *temp_username = (char *)malloc(sizeof(char) * 50) ;

							//Copy the current node's details to temporary variables
							int temp_no_of_meetings = current -> no_of_meetings ;
							strcpy(temp_username , current -> username) ;

							//Data swapping
							strcpy(current -> username , index -> username) ;
							current -> no_of_meetings = index -> no_of_meetings ;

							//Restore the temp variables
							index -> no_of_meetings = temp_no_of_meetings ;
							strcpy(index -> username , temp_username) ;

							free(temp_username) ;

						}

					}
					else if(type == 1){
						if(current -> participants <= index -> participants){
							//Copy the current node's details to temporary variables/
							char *temp_username = (char *)malloc(sizeof(char) * 50) ;
							int temp_participants = current -> participants ;
							strcpy(temp_username , current -> username) ;

							//Data swapping/
							strcpy(current -> username , index -> username) ;
							current -> participants = index -> participants ;

							//Restore the temp variables/
							index -> participants = temp_participants ;
							strcpy(index -> username , temp_username) ;
							free(temp_username) ;
						}
					}
					else if(type == 2){
						if(current -> time_duration <= index -> time_duration){
							//Copy the current node's details to temporary variables/
							char *temp_username = (char *)malloc(sizeof(char) * 50) ;
							strcpy(temp_username , current -> username) ;
							int temp_time_duration = current -> time_duration ;

							//Data swapping/
							strcpy(current -> username , index -> username) ;
							current -> time_duration = index -> time_duration ;

							//Restore the temp variables/
							index -> time_duration = temp_time_duration ;
							strcpy(index -> username , temp_username) ;
							free(temp_username) ;
						}
					}
					index = index -> newnode ;
				}
				current = current -> newnode ;
			}

		}

}


int findLargest(int limit){
	int counter = 0 ;
	finaldetails *current = head_finaldetails , *index ;
	index = current -> newnode;
	largestElement = strlen(head_finaldetails -> username) ;
	while((counter < limit - 1) && (index != NULL)){
		/*If the current node's string length < index node's string lenght*/
		if(largestElement < strlen(index -> username)){
			largestElement = strlen(index ->username) ;
		}
		index = index -> newnode ;
		counter++ ;
	}
	return largestElement ;
}

int sum(int type){
	int sum = 0 ; ;
	if(type == 0){
		sum  = 0 ;
		finaldetails *current = head_finaldetails , *index ;
		index = current ;
		while(index != NULL){
			sum = index -> no_of_meetings + sum ;
			index = index -> newnode ;
		}
		total = sum ;
	}

	else if(type == 1){
		sum = 0 ;
		finaldetails *index = head_finaldetails ;
		while(index != NULL){
			sum = sum + index -> participants ;
			index = index -> newnode ;
		}
		total = sum ;
	}

	else if(type == 2){
		sum = 0 ;
		finaldetails *index = head_finaldetails ;
		while(index != NULL){
			sum = sum + index -> time_duration ;
			index = index -> newnode ;
		}
		total = sum ;
	}
	return total ;
}

void printGraph(int type , int limit , int scaled){
	if(type == 0){
		sortList(0) ;
		finaldetails *current = head_finaldetails ;
		printf("\n") ; //goto a newline
		x = findLargest(limit)  ;
		int default_x = x ; //store current x- value
		int maxPrintWidth = 80 - x - 3 ;
		int counter = 0 ;
		while((counter < limit) && (current != NULL)){
			float value ;
			if(scaled == 1){
				value = (float) (current -> no_of_meetings) / (float) (head_finaldetails -> no_of_meetings) ;
			}
			else if(scaled == 0){
				int sum_all = sum(0) ;
				value = (float)(current -> no_of_meetings) / (sum_all) ;
			}

			for(int i = 0 ; i < 3 ; i++){
				//move x - cells forward
				if(i == 1){
					printf(" %s" , (current -> username)) ;
					int max = x - strlen(current->username) + 1 ;
					for(int k = 0 ;k < max ; k++){
						printf(" ") ;
					}
				}
				else if(i != 1){
					for(int j = 0 ; j < x + 2 ; j++){
						printf(" ") ;
					}
				}
				int scale = maxPrintWidth - len(head_finaldetails -> no_of_meetings) ;
				printf("\u2502") ; //to print '|'
				for(int counter_1 = 0 ; counter_1 <(int) (scale* value)  ; counter_1++){
					printf("\u2591") ; //to color bar graph
				}
				if(i == 1){
					printf("%d" , current -> no_of_meetings) ;
				}
				x = default_x ; //reset x-coordinate to previous
				printf("\n") ;
			}
			for(int j = 0 ; j < x + 2 ; j++){
				printf(" ") ;
			}
			printf("\u2502") ; //print the '|'
			printf("\n") ;
			free(current) ;
			current = current -> newnode ;
			counter++ ;
		}
		//move cursor forward
		for(int j = 0 ; j < x + 2; j++){
			printf(" ") ;
		}
		printf("\u2514") ;
		for(int index = 0 ; index < maxPrintWidth; index++){
			printf("\u2500") ;
		}
		printf("\n") ;

	}

	else if(type == 1){
		sortList(1) ;
		finaldetails *current = head_finaldetails ;
		printf("\n") ; //goto a newline
		x = findLargest(limit) ;
		int default_x = x ; //store current x- value
		int maxPrintWidth = 80 - x - 3 ;

		int counter = 0 ;
		while((counter < limit) && (current != NULL)){
			float value ;
			int sum_all ;
			if(scaled == 1){
				value = (float) (current -> participants) / (float) (head_finaldetails -> participants) ;
			}
			//int sum_all ;
			else if(scaled == 0){
				sum_all = sum(1) ;
				value = (float)(current -> participants) / (float)(sum_all) ;
				//printf("%f\n" , value) ;
				//exit(0) ;
			}

			for(int i = 0 ; i < 3 ; i++){
				//move x - cells forward
				if(i == 1){
					printf(" %s" , (current -> username)) ;
					int max = x - strlen(current->username) + 1 ;
					for(int k = 0 ;k < max ; k++){
						printf(" ") ;
					}
				}
				else if(i != 1){
					for(int j = 0 ; j < x + 2 ; j++){
						printf(" ") ;
					}
				}
				int scale = maxPrintWidth - len(head_finaldetails -> participants)  ;
				//move x - cells forward
				printf("\u2502") ; //to print '|'
				for(int counter_1 = 0 ; counter_1 <(int)(scale* value) ; counter_1++){
					printf("\u2591") ; //to color bar graph
				}
				if(i == 1){
					printf("%d" , current -> participants) ;
				}
				x = default_x ; //reset x-coordinate to previous
				printf("\n") ;
			}
			//move x + 1 cells forward
			for(int j = 0 ; j < x + 2 ; j++){
				printf(" ") ;
			}
			printf("\u2502") ; //print the '|'
			printf("\n") ;
			//free(index) ;
			free(current) ;
			current = current -> newnode ;
			counter++ ;
		}
		//move cursor forward
		for(int j = 0 ; j < x + 2; j++){
			printf(" ") ;
		}
		//move x - cells forward
		printf("\u2514") ;
		for(int index = 0 ; index < maxPrintWidth; index++){
			printf("\u2500") ;
		}
		printf("\n") ;

	}

	else if(type == 2){
		sortList(2) ;
		finaldetails *current = head_finaldetails ;
		printf("\n") ; //goto a newline
		x = findLargest(limit) ;
		int default_x = x ; //store current x- value
		int maxPrintWidth = 80 - x - 3;

		int counter = 0 ;
		while((counter < limit) && (current != NULL)){
			float value ;
			if(scaled == 1){
				value = (float) (current -> time_duration) / (float) (head_finaldetails -> time_duration) ;
			}
			else if(scaled == 0){
				int sum_all = sum(2) ;
				value = (float)(current -> time_duration) / (sum_all) ;
			}

			for(int i = 0 ; i < 3 ; i++){
				if(i == 1){
					printf(" %s" , (current -> username)) ;
					int max = x - strlen(current->username) + 1 ;
					for(int k = 0 ;k < max ; k++){
						printf(" ") ;
					}
				}
				else if(i != 1){
					for(int j = 0 ; j < x + 2 ; j++){
						printf(" ") ;
					}
				}
				//move x - cells forward
				int scale = maxPrintWidth - len(head_finaldetails -> time_duration) ;
				printf("\u2502") ; //to print '|'
				for(int counter_1 = 0 ; counter_1 <(int) (scale * value) ; counter_1++){
					printf("\u2591") ; //to color bar graph
				}
				if(i == 1){
					printf("%d" , current -> time_duration) ;
				}
				x = default_x ; //reset x-coordinate to previous
				printf("\n") ;
			}
			for(int j = 0 ; j < x + 2 ; j++){
				printf(" ") ;
			}
			printf("\u2502") ; //print the '|'
			printf("\n") ;
			free(current) ;
			current = current -> newnode ;
			counter++ ;
		}
		//move x - cells forward
		for(int j = 0 ; j < x + 2 ; j++){
				printf(" ") ;
			}
		printf("\u2514") ;
		for(int index = 0 ; index < maxPrintWidth; index++){
			printf("\u2500") ;
		}
		printf("\n") ;

	}
}

int len(int n){
	if(n >= 1000000){
		length = 7 ;
	}
	else if(n >= 100000){
		length = 6 ;
	}
	else if(n >= 10000){
		length = 5 ;
	}
	else if(n >= 1000){
		length = 4 ;
	}
	else if(n >= 100){
		length = 3 ;
	}
	else if(n >= 10){
		length = 2 ;
	}
	else if(n >= 0){
		length = 1 ;
	}
	return length ;
}

