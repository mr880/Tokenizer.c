/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
   
   	//string entered
    char* string1;
    //string locator
    char* stringlocation;
    
    
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
    
   if(strlen(ts)== 0){
		return NULL;
	}

   //makes tokenizer array
    TokenizerT *tokenizer =  malloc(sizeof(TokenizerT));
    
    tokenizer->string1 = malloc(sizeof(char) * strlen(ts) +1);
     //makes string = command line argument
    strcpy(tokenizer->string1,ts); 
    //sets stringlocation pointer = string1
    tokenizer-> stringlocation = tokenizer->string1; 

	

    return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {

	tk->string1 = NULL;
	free(tk->string1);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */
int escapeChars(char* tk){
	//create pointer
	int stringLength = 2;
	//creates pointer
	char* pointer = tk;
	// check the start of the input is '\'
	if(*pointer == '\\'){
		pointer++;
		//check for escape characters 
		if(*pointer == 'a'){
			printf("ERROR: Escape Character Entered: [0x%02x]\n", '\a');
			return stringLength; 
		}
		else if(*pointer == 'b'){
			printf("ERROR: Escape Character Entered: [0x%02x]\n", '\b');
			return stringLength; 
		}
		else if(*pointer == 'f'){
			printf("ERROR: Escape Character Entered: [0x%02x]\n", '\f');
			return stringLength; 
		}
		else if(*pointer == 'n'){
			printf("ERROR: Escape Character Entered: [0x%02x]\n", '\n');
			return stringLength; 
		}
		else if(*pointer == 'r'){
			printf("ERROR: Escape Character Entered: [0x%02x]\n", '\r');
			return stringLength; 
		}
		else if(*pointer == 't'){
			printf("ERROR: Escape Character Entered: [0x%02x]\n", '\t');
			return stringLength; 
		}
		else if(*pointer == 'v'){
			printf("ERROR: Escape Character Entered: [0x%02x]\n", '\v');
			return stringLength; 
		}
		else 
			return 0;
		
	}
	else
		return 0;
}

//checks for mal tokens
int malCheck(char* tk){
	//creates new pointer
	char *pointer = tk;
	//length of string to be returned
	int stringLength =1;

	//make sure first char is a digit
	if(	*pointer != '0'&&*pointer != '1'&&*pointer != '2'&&*pointer != '3'&&*pointer != '4'&&
		*pointer != '5'&&*pointer != '6'&&*pointer != '7'&&*pointer != '8'&&*pointer != '9')
		return 0;
	
	//while a digit, extend length of string and move pointer
	while(isdigit(*(++pointer)) != 0){
 		stringLength++;
 	
	}

	if(*pointer == '.'){
		stringLength++;
		pointer++;
		
		if(	*pointer != '0'&&*pointer != '1'&&*pointer != '2'&&*pointer != '3'&&*pointer != '4'&&
			*pointer != '5'&&*pointer != '6'&&*pointer != '7'&&*pointer != '8'&&*pointer != '9'){

			return stringLength;
		}
		else
		{
			stringLength++;
			pointer++;
		
			while(	*pointer == '0'||*pointer == '1'||*pointer == '2'||*pointer == '3'||*pointer == '4'||
					*pointer == '5'||*pointer == '6'||*pointer == '7'||*pointer == '8'||*pointer == '9')
			{
				stringLength++;
				pointer++;
			}
			if(*pointer =='E'||*pointer == 'e'){

				stringLength++;
				pointer++;

				if(*pointer =='-'||*pointer =='+')
				{
					stringLength++;
					pointer++;

				}	
				else if(	*pointer != '0'&&*pointer != '1'&&*pointer != '2'&&*pointer != '3'&&*pointer != '4'&&
							*pointer != '5'&&*pointer != '6'&&*pointer != '7'&&*pointer != '8'&&*pointer != '9')
				{
					stringLength++;
					pointer++;
				}
				else
					return 0;
			}
		}
	}

	else if(*pointer == 'E' || *pointer =='e')
	{
		stringLength++;
		pointer++;

		if(*pointer == '-'||*pointer =='+')
		{
			stringLength++;


		}
		if(	*pointer != '0'&&*pointer != '1'&&*pointer != '2'&&*pointer != '3'&&*pointer != '4'&&
			*pointer != '5'&&*pointer != '6'&&*pointer != '7'&&*pointer != '8'&&*pointer != '9')
		{

			return stringLength;
		}
		else
			return 0;
	}
	//being hacky.. sorry
	if(*pointer==' ')
		return stringLength;
	
	return stringLength+1;

	
}
int malcheckAlt(char *tk){
	//make new pointer
	char *pointer = tk;
	int stringLength = 1;

	if(*pointer != '0'){
		return 0;
	}

	pointer ++;

	if(*pointer == 'X'||*pointer == 'x')
	{
		stringLength++;
		if(	*pointer == '0'||*pointer == '1'||*pointer == '2'||*pointer == '3'||*pointer == '4'||
			*pointer == '5'||*pointer == '6'||*pointer == '7'||*pointer == '8'||*pointer == '9'||
			*pointer == 'a'||*pointer == 'A'||*pointer == 'b'||*pointer == 'B'||*pointer == 'c'||
			*pointer == 'C'||*pointer == 'd'||*pointer == 'D'||*pointer == 'e'||*pointer == 'E'||
			*pointer == 'f'||*pointer == 'F')
		{
			return stringLength;
		}
		else
			return stringLength;
	}
	return 0;
}

 //check if string is a zero function
int zeroCheck(char* tk){
	//create new pointer
	char *pointer = tk;
	//length of string to be returned;
	int stringLength = 1;

	//check if first char is zero
	if(*pointer == '0')
	{


		//move pointer along
		pointer++;
		if(*pointer=='8'||*pointer=='9'){
			return stringLength;
		}
		//check if the string is not a hex value or octal
		if(isxdigit(*pointer)!=0){
			return stringLength;
		}

		//found zero function, return stringlength of 1
		if(*pointer == 'x'||*pointer == 'X'){
			return 0;
		}
		else
			return stringLength;
	}
	//first char is not a zero, return 0(error)
	else
		return 0;
}

//check if string is a float
int floatToken(char *tk) {

 	//create new pointer
 	char *pointer = tk;
 	
 	//length of string to be returned
 	int stringlength = 1;


 	//starts with 0
 	if(*pointer=='0'){
 		pointer++;
 		//check if second char is a '.'
 		if(*pointer== '.'){
 			pointer++;
 			stringlength++;
 			
 			//make sure next char is a digit..
 			if(isdigit(*pointer)!=0){
 				pointer++;
 				stringlength++;
 				//check for more digits...
 				while(isdigit(*pointer)!=0){
 					
 					pointer++;
 					stringlength++;
 				}
 				//if we reach end of string, return a float
 				if(*pointer=='\0')
 					return stringlength;
 				//if next char is an E or e, continue to grow string
 				else if(*pointer =='E'||*pointer =='e'){
 					pointer++;
 					stringlength++;
 					
 					//float must have a + or - after an E or e... 
 					if(*pointer == '+'|| *pointer == '-'){
 						pointer++;
 						stringlength++;
 						//float must have a digit after a + or -
 						if(isdigit(*pointer)!=0){
 							pointer++;
 							stringlength++;
 							//check for more digits
 							while(*pointer != '\0'){
 								if(isdigit(*pointer)!=0){
 									pointer++;
 									stringlength++;
 								}
 								else
 									return stringlength;
 							}
 							return stringlength;
 						}
 						else
 							return 0;
 					}
 					else
 						return 0;

 				
 				}
 				else
 					return stringlength;
 				//

 			}
 			else
 				return 0;
 		}
 		//if not a '.' not a float
 		else
 			return 0;

 	}
 	//starts with 1-9
 	else if(*pointer=='1'||*pointer=='2'||*pointer=='3'||*pointer=='4'||*pointer=='5'||
 			*pointer=='6'||*pointer=='7'||*pointer=='8'||*pointer=='9'){
 		
 		pointer++;
 		//check for more digits...
 		while(isdigit(*pointer)!=0){
 			stringlength++;
 			pointer++;
 		}
 		//if after digit(s) is a '.' we continue..
 		if(*pointer=='.'){
 			pointer++;
 			stringlength++;
 			
 			//make sure a digit comes after the '.'
 			if(isdigit(*pointer)!=0){
 				pointer++;
 				stringlength++;
 				if(*pointer == '\0')
 					return stringlength;
 			}	//check for more digits
 			
 			else
 				return 0;

 				while(isdigit(*pointer)!=0){
 					pointer++;
 					stringlength++;
 				}
 				
 				//check if char is an E or e otherwise return string
 				if(*pointer == 'E'|| *pointer =='e'){
 					pointer++;
 					stringlength++;

 					if(*pointer=='+'||*pointer=='-'){
 						pointer++;
 						stringlength++;
 						if(isdigit(*pointer)!=0){
 							pointer++;
 							stringlength++;
 							while(isdigit(*pointer)!=0){
 								pointer++;
 								stringlength++;
 							}
 							return stringlength;

 						}
 						else
 							return 0;
 					}
 					else
 						return 0;
 				}
 				else
 					return stringlength;

 			
 			


 		}
 		//if after digit(s) is an E or e, we continue...
 		else if(*pointer=='E'||*pointer=='e'){
 			pointer++;
 			stringlength++;
 			
 			//+ or - must come after an E or e
 			if(*pointer == '+'||*pointer == '-'){
 				pointer++;
 				stringlength++;
 				//if next char is a digit, continue
 				if(isdigit(*pointer)!=0){
 					pointer++;
 					stringlength++;
 					//check for more digits
 					while(isdigit(*pointer)!=0){
 						pointer++;
 						stringlength++;
 					}
 					return stringlength;

 				}
 				else
 					return 0;
 			}
 			else
 				return 0;
 		}
 		else
 			return 0;

 	}
 	else
 		return 0;

}



//check if string is a decimal
int decimal(char* tk){
	//create pointer
	char *pointer = tk;
	//length of string to be returned
	int strlth = 1;
	int i;
	
	//check if the first char is a digit from 0-9
	
	if( *pointer == '1' ||*pointer == '2' ||*pointer == '3'||
		*pointer == '4' ||*pointer == '5' ||*pointer == '6' ||*pointer == '7'||
		*pointer == '8'	||*pointer == '9'){
		
		for(i=0; i<strlen(tk); i++){
			
			//if the rest of the chars are equal to digits 0-9, then it remains of decimal type
			
			char c = tk[i];

			
			if(	c == '0' ||c == '1' ||c == '2' ||c == '3'||
				c == '4' ||c == '5' ||c == '6' ||c == '7'||
				c == '8' ||c == '9'){
			
				//increase length of string
				strlth++;
				//move pointer along
				
			}

			//check if it is NOT a decimal
			else if(c=='e'||c=='E'||c=='.')
				return 0;
			
			else
				//if not a digit
				return strlth-1;
		}

		
		return strlth;

	//if first char is not a digit, end function
	}

	else
		return 0;

}

//check if string is an octal
int octalCheck(char *tk) {

	//create pointer
	char *pointer = tk;
	//length of string to return for memory allocation 
	int strLength = 1;

	//check that the string starts with 0
	if(*pointer == '0'){
		
		pointer++;
		//check for second octal digit
		if(*pointer == '0' ||*pointer == '1' ||*pointer == '2' ||*pointer == '3' ||
			*pointer == '4' ||*pointer == '5' ||*pointer == '6' ||*pointer == '7')
			{
			//found, incraese string length
			strLength++;
			//move pointer for further checks
			pointer++;
			//check for octal digits after the second
			while(*pointer!='\0'){
				//is it an octal digit?
				if(	*pointer == '0' ||*pointer == '1' ||*pointer == '2' ||*pointer == '3' ||
					*pointer == '4' ||*pointer == '5' ||*pointer == '6' ||*pointer == '7'){
					//yes? incrase string length
					strLength++;
					//incrase pointer for further checks in loop
					pointer++;
				}
				//has a value other then an octal digit of 0-7
				else
					//return the string length from this point
					return strLength;
			}
			// after loop ends with no errors, return the full string length..
			return strLength;

		//if second char in the string is not an octal digit, end the function as not an octal
		}
		else
			return 0;
	}
	//if the string doesnt start with a '0' it cannot be an octal, end the function
	else
		return 0;


		
}
// check if string is a hexidecimal
int hexCheck(char *tk) {

	char *pointer = tk;
	//length of hex
	int stringLength = 1;
	//eligible to be hex??
	if(*pointer == '0'){
		//if yes
		pointer++;
		//check for 'x' of 'X' as next char
		
		if(*pointer == 'x' || *pointer =='X'){
			//if yes, add 1 to length of hex string
			stringLength++;
			//make sure the 'x or 'X' is followed by a digit from 0-9
			
			pointer++;

			if( (*pointer) == '0' || (*pointer) == '1' || (*pointer) == '2' || (*pointer) == '3' ||
				(*pointer) == '4' || (*pointer) == '5' || (*pointer) == '6' || (*pointer) == '7' || 
				(*pointer) == '8' || (*pointer) == '9' || (*pointer) == 'a' || (*pointer) == 'A' ||
				(*pointer) == 'b' || (*pointer) == 'B' || (*pointer) == 'c' || (*pointer) == 'C' ||
				(*pointer) == 'd' || (*pointer) == 'D' || (*pointer) == 'e' || (*pointer) == 'E' ||
				(*pointer) == 'f' || (*pointer) == 'F')

			{
				
				//if yes, add 1 to length of hex string
				stringLength++;
				
				while(*pointer != '\0'){
				
					if(	*pointer == '0'||*pointer == '1'||*pointer == '2'||*pointer == '3'||*pointer == '4'||
						*pointer == '5'||*pointer == '6'||*pointer == '7'||*pointer == '8'||*pointer == '9'||
						*pointer == 'a'||*pointer == 'A'||*pointer == 'b'||*pointer == 'B'||*pointer == 'c'||
						*pointer == 'C'||*pointer == 'd'||*pointer == 'D'||*pointer == 'e'||*pointer == 'E'||
						*pointer == 'f'||*pointer == 'F'){
						
						

						stringLength++;
						pointer++;
					}
					else
						break;
					
				}
			}
			else
				return 0;
		}
		else
			return 0;


	}
	else
		return 0;

	return stringLength -1; 

}




char* TKGetNextToken( TokenizerT * tk ) {

	//char* pointer for iteration
	char* pointer = tk->stringlocation; 
	//int for location of pointer
	int stringLength = 0;
	//token to be returned
	char* returnToken = NULL;
	int counter = 0;
	
	
	// start with a check for whitespace 
	while (*pointer == ' '){
		//printf("dwhewh\n");
		pointer++;
	}
	//this now becomes our starting point as a check
	tk->stringlocation = pointer;

	//begin iteration through our input string
	while(*pointer != '\0'){

	

		//finds the size of our first token by building up to the next whitespace
		while(*pointer == ' '){
			pointer++;
		}
		//halts the string iteration at the end of the first token
		tk->stringlocation = pointer;
		

			/*Begin check with the hex check*/
		
		stringLength = hexCheck(pointer);
		if (stringLength != 0) {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (stringLength + 1));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, stringLength);
			//add in order to signify that the string has ended
			returnToken[stringLength] = '\0';
			//catch pointer up
			counter=stringLength;
			while(counter!=0){
				counter--;
				pointer++;
			}

			//move pointer to after the current token
			tk->stringlocation = pointer;
			//gets rid of white space
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//print 
			printf("Hexadecimal : '%s' \n", returnToken);
			//return token
			return returnToken;

		}

		else 
			stringLength = octalCheck(pointer);

					/* octal check */


		if(stringLength != 0) {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (stringLength + 1));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, stringLength);
			//string end check
			returnToken[stringLength] = '\0';
			//catch pointer up
			counter=stringLength;
			while(counter!=0){
				counter--;
				pointer++;
			}
			
			tk->stringlocation = pointer;
			//gets rid of white space
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//print
			printf("Octal : '%s'\n", returnToken);
			//return token
			return returnToken;

		}

		else
			stringLength = decimal(pointer);

					/* decimal check */
		if (stringLength != 0) {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (stringLength + 1));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, stringLength);
			//string end check
			returnToken[stringLength] = '\0';
			//catch pointer up
			counter=stringLength;
			while(counter!=0){
				counter--;
				pointer++;
			}
			
			tk->stringlocation = pointer;
			//gets rid of white space
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//print 
			printf("Decimal : '%s'\n", returnToken);
			//return token
			return returnToken;

		}

		else
			stringLength = floatToken(pointer);

				/* float check */
		if (stringLength != 0) {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (stringLength + 1));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, stringLength);
			//string end check
			returnToken[stringLength] = '\0';
			//catch pointer up
			counter=stringLength;
			while(counter!=0){
				counter--;
				pointer++;
			}
		
			tk->stringlocation = pointer;
			//gets rid of white space
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//print
			printf("Floating-Point : '%s'\n", returnToken);
			//return token
			return returnToken;

		}

		else 
			stringLength = zeroCheck(pointer);

						/* zero check */
		if (stringLength != 0) {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (stringLength + 1));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, stringLength);
			//string end check
			returnToken[stringLength] = '\0';
			//catch pointer up
			counter=stringLength;
			while(counter!=0){
				counter--;
				pointer++;
			}
			
			tk->stringlocation = pointer;
			//gets rid of white space
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//print
			printf("Decimal (Zero): '%s'\n", returnToken);
			//return token
			return returnToken;

		}

		else
			stringLength = escapeChars(pointer);

				/* escape char check */
		if (stringLength != 0) {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (stringLength + 1));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, stringLength);
			//string end check
			returnToken[stringLength] = '\0';
			//catch pointer up
			counter=stringLength;
			while(counter!=0){
				counter--;
				pointer++;
			}
			
			tk->stringlocation = pointer;
			//gets rid of white space
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//return token
			return returnToken;

		}

		else {

			stringLength = malCheck(pointer);

			if (stringLength == 0)
				stringLength = malcheckAlt(pointer);

		}

		//check if token is malformed
		if (stringLength != 0) {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (stringLength + 1));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, stringLength);
			//string end check
			returnToken[stringLength] = '\0';
			//catch pointer up
			counter=stringLength;
			while(counter!=0){
				counter--;
				pointer++;
			}
			
			tk->stringlocation = pointer;
			//keep moving pointer until there is no more Whitespace, just the next token
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//print
			printf("Malformed : '%s'\n", returnToken);
			//return token
			return returnToken;

		}


		/* if nothing else */
		
		else {

			//creates token in memory
			returnToken = malloc(sizeof(char) * (2));
			//copies chars to token
			strncpy(returnToken, tk->stringlocation, 1);
			//string end check
			returnToken[1] = '\0';
			//catch pointer up
			pointer++;
			//move pointer to after the current token
			tk->stringlocation = pointer;
			
			while (isspace(*tk->stringlocation) != 0)
				tk->stringlocation++;
			//print
			printf("Error [Escape Character '%s'] - [0x%02x]\n", returnToken, *returnToken);
			//return token
			return returnToken;

		}
	}

	returnToken = malloc(sizeof(char) * (1));
	
	returnToken[0] = '\0';
  
  	return returnToken;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv){

	int index = 1;
	//create pointer
	char* pointer;

	//create a check for the minimum number of arguments needed to run pgrm
	if(argc <2){
		printf("Error: Enter A String\n");
		//return error
		return 1; 
	}
	//'-' check
	while (argc > index) {

		if(*argv[index] == '-')
			index++;

		else
			break;

	}

	TokenizerT * newToken = TKCreate(argv[index]); //creates token
	
	if(newToken==NULL)	// makes sure that if tp is returned as null, we return an error message to user.
	{
		printf("Error: No String\n");
		return 1;
	}

	while(*(pointer = TKGetNextToken(newToken)) != '\0')
		free(pointer);

	
	TKDestroy(newToken);
	return 0;
}