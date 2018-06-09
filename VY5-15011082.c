//VY-5 Vefa Uður Bilge
//15011082
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define stackSize 100
char stack[stackSize]; //Stack for postfix
int stack_int[stackSize]; //Stack for inverting postfix to arithmetical process
int variables_i[stackSize]; //It keeps variables' values
char variables_c[stackSize]; //It keep which valuables exist with name
short int top=0; //Stacks' indicator

void push(char value) {	//Push characters for postfix's stack
	if(top==stackSize){
		printf("Stack Dolu");
		return;
	}
	stack[top]=value;
	top++;
}
void push_int(int value) { //Push integers for aritmetical calculations
	if(top==stackSize){
		printf("Stack Dolu");
		return;
	}
	stack_int[top]=value;
	top++;
}

void pop()	{			//Popping stacks with reducing indicator 
	if(top==0)	{
		printf("Stack Bos");
		return;
	}
	top--;
}
//Select priority due to operations
short int returnValue(char text)	{
	if(text == '*' || text == '/')
		return 2;
	else if(text == '+' || text == '-')		
		return 1;
		else return -1;
}

void printStack(){
	int i;
	for(i=0;i<=top;i++)
		printf("Stack : %c\n",stack[i]);
}
void printStack_int(){
	int i;
	printf("\nStack: ");
	for(i=0;i<top;i++)
		printf("%d ",stack_int[i]);	
}
//Find variables' values
int find_variable(char c){
	int i=sizeof(variables_c)-1;
	while(c!=variables_c[i])	
		i--;
	return variables_i[i];	
	

}
void infixtopostfix(char text[0],char postfix[0]){
	int i,j=0;
	while(text[i]!=';'){	//End of process
		if(text[i]=='('){	//If it has first priority
			push(text[i]);
		}
		//if text is a operator
		else if(text[i]=='+' || text[i]=='-'|| text[i]=='*' || text[i]=='/' ){
		//If stack is empty
			if(top==0){
				push(text[i]);
				}
			else{
				while(returnValue(stack[top])>returnValue(text[i])) {	//First priority to least priority
					postfix[j]=stack[top-1];
					j++;
					pop();
				}
			push(text[i]);
			}
		}
		
		else if(text[i]==')')	{
			while(stack[top-1]!='(') { //If a closing paranthesis is exist do while seeing a openin paranthesis
				postfix[j]=stack[top-1];
				j++;
				pop();
			}
			pop(); //pop last paranthesis
			}
			else if (text[i]!=' '){
				postfix[j]=text[i];			
				j++;		
		}
		i++;
	}

	while(top>0){
		postfix[j]=stack[top-1];
		j++;
		pop();
	}
	postfix[j]='\0';	//End of postfix

}
void postfix_edit(char postfix[0]){
	int j,i,k,flag=0;
	j=0;i=1;
	int value;
	char tmp[5];
	while(postfix[i]!='\0'){
		if ((postfix[i]>47)&&(postfix[i]<58)){	//If it is a number
			k=i;
			while((postfix[k]>47)&&(postfix[k]<58)){		//if it is not only digit
			tmp[j]=postfix[k];	
			j++;
			k++;						//Char to integer
			}
			value=atoi(tmp);
			if(j>1) i++;		//if it is not only digit
			push_int(value);
			printStack_int();	
			memset(tmp,0,sizeof(tmp));
			j=0;	
		}
			else if(((postfix[i]>=97)&&(postfix[i]<=122))){			//if it is a variable					
				push_int(find_variable(postfix[i]));
				printStack_int();
							
							}
				else if (postfix[i]=='*'){				//and for operations...
					pop();
					value=stack_int[top]*stack_int[top-1];
					pop();
					push_int(value);
					printStack_int();
			
				}
					else if (postfix[i]=='/'){
						pop();
						value=stack_int[top-1]/stack_int[top];
						pop();
						push_int(value);
						printStack_int();
					
					}
						else if (postfix[i]=='-'){
							pop();
							value=stack_int[top-1]-stack_int[top];
							pop();
							push_int(value);
							printStack_int();
						
						}							
						else if (postfix[i]=='+'){
							pop();
							value=stack_int[top]+stack_int[top-1];
							pop();
							push_int(value);
							printStack_int();
		
			}	
		i++;		
									
}
}

main(){
	char text[100];
	int j,i=0; 
	char postfix[sizeof(text)];
	FILE *fi;
	fi=fopen("input.txt","r");
	printf("*****ARITHMETICAL CALCULATOR*****\n\n");
	while(!feof(fi)){
		fgets(text,50,fi);
		printf("-Operation -> %s",text);		
		infixtopostfix(&text[0],&postfix[0]);
		printf("\nPostfix :%s ",postfix);
		postfix_edit(&postfix[0]);
		variables_c[i]=text[0];
		variables_i[i]=stack_int[0];
		printf("\n\n");	
		memset(text,0,sizeof(text));
		memset(stack,0,sizeof(stack));
		top=0;
		i++;
			
	}	
	
	printf("\n\nVariables: ");
	for(j=0;j<i;j++){
		printf("%c=",variables_c[j]);
		printf("%d ",variables_i[j]);
	}

return 0;
}
