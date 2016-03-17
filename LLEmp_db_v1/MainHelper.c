/*
MainHelper.c

@author			Peter Nagy (g00317399)
@description	This is a function holder for the Main.c
@version		0.1
@since			2015-03-19

Resources list:
stdafx.h				- Import library holder
	MainHeader.h			- The main header
	Main.c					- The main entry point for the program & function holder
	MainHelper.c			- Function holder
	Login_holder.dat		- User credentials
	Employee.dat			- The employee data
	report_holder.dat		- The employee report
	NEW_employees_holder.dat- DEBUG ONLY with original data
*/

#include "MainHeader.h"
#include "stdafx.h"

/*read_emp_file: reads and populates EMP linked list*/
EMP * read_emp_file(){
	EMP * head = NULL;
	EMP * currentEMP = NULL;
	FILE *fp = fopen(EMPLOYEES_HOLDER_FILE, "r");
	LGN *headPtr = malloc(sizeof(LGN));
	char tmpJoinDate[11];
	int iCnt = 0,
		iDateCnt = 0;
	char* dateParts;
	char tmpEmpName_1[100];
	char tmpEmpName_2[49];
	char tmpAdd_1[3];
	char tmpAdd_2[20];
	char tmpAdd_3[20];
	char tmpAdd_4[20];

	head = malloc(sizeof(EMP));

	if (fp == NULL)
		perror("Wohoo, file does not exist(or can't open)\n");

	while (!feof(fp)){
		currentEMP = malloc(sizeof(EMP));

		fscanf(fp, "%d", &currentEMP->emp_id);
		if (iEmpId < currentEMP->emp_id)
			iEmpId = currentEMP->emp_id;

		fscanf(fp, "%d", &currentEMP->department);
		fscanf(fp, "%d", &currentEMP->salary);
		fscanf(fp, "%s %s", tmpEmpName_1, tmpEmpName_2);
		strcpy(currentEMP->emp_name, tmpEmpName_1);
		strcat(currentEMP->emp_name, " ");
		strcat(currentEMP->emp_name, tmpEmpName_2);

		fscanf(fp, "%s %s %s %s", tmpAdd_1, tmpAdd_2, tmpAdd_3, tmpAdd_4);
		strcpy(currentEMP->emp_address, tmpAdd_1);
		strcat(currentEMP->emp_address, " ");
		strcat(currentEMP->emp_address, tmpAdd_2);
		strcat(currentEMP->emp_address, " ");
		strcat(currentEMP->emp_address, tmpAdd_3);
		strcat(currentEMP->emp_address, " ");
		strcat(currentEMP->emp_address, tmpAdd_4);

		fscanf(fp, "%s", currentEMP->email); //head->email[14] = '\0';
		fscanf(fp, "%s", tmpJoinDate);
		dateParts = strtok(tmpJoinDate, "-");
		while (dateParts != NULL) {
			switch (iDateCnt){
			case 0:
				currentEMP->join_date.day = atoi(dateParts);
				break;
			case 1:
				currentEMP->join_date.month = atoi(dateParts);
				break;
			case 2:
				currentEMP->join_date.year = atoi(dateParts);
				break;
			}
			dateParts = strtok(NULL, "-");
			++iDateCnt;
		}
		iDateCnt = 0;

		currentEMP->next = NULL;

		if (iCnt != 0)
			add_emp_node_to_end(head, currentEMP);
		else
			head = currentEMP;
		//printf("\n%d %s %s %s %d %d-%d-%d %d", currentEMP->emp_id, currentEMP->emp_name, currentEMP->emp_address, currentEMP->email, currentEMP->department, currentEMP->join_date.day, currentEMP->join_date.month, currentEMP->join_date.year, currentEMP->salary);
		iCnt++;
	}
	fclose(fp);

	return head;
}
/*add_emp_node_to_end: add nodes to the head*/
void add_emp_node_to_end(EMP *head, EMP *node){
	EMP *tmpNode = head;

	while (tmpNode->next != NULL)
		tmpNode = tmpNode->next;

	tmpNode->next = node;
}

/*get_user_login: handle the user login, populate LGN linked list*/
void get_user_login(LGN *userStatin){
	//read login credentials
	//add to linked list
	LGN *headLGN = read_login_file();
	LGN *loginCreds = NULL;
	
	for (int i = 0; i < 3; ++i){
		if (userStatin != NULL && i == 0){
			loginCreds = userStatin;
			printf("user : %s pass: %s ", loginCreds->user, loginCreds->pass);
			goto CHECK_USER;//I hate this solution but in this case it looks the best
		}
		else
			loginCreds = malloc(sizeof(LGN));
		//get username
		printf("Please enter your username: ");
		scanf("%s", loginCreds->user);

		//get password
		printf("Please enter your password: ");
		for (int i = 0; i < 6; i++){
			loginCreds->pass[i] = getch();
			putchar('*');
		}
		loginCreds->pass[6] = '\0';
		loginCreds->next = NULL;

		//loop on list
		CHECK_USER: if (add_search_lgn_node_to_end(headLGN, loginCreds, 1) == 0){
			system("cls");
			return;
		}
		else
			printf("\n\n============================\nWrong username or password\n\You have %d more login attemts!\n============================\n", 3 - i);
	}

	//wrong credentials, the place of no return
	puts("BYE NOW");
	Sleep(2000);
	exit(1);
}

/*read_login_file: does read the login file and creates linked list*/
LGN * read_login_file(){
	FILE *fp = fopen(LOGIN_HOLDER_FILE, "r");
	LGN *headPtr = malloc(sizeof(LGN));
	LGN *currentLGN = NULL;
	int iCnt = 0;

	if (fp == NULL)
		perror("Wohoo, file does not exist(or can't open)\n");

	while (!feof(fp)){
		currentLGN = malloc(sizeof(LGN));
		fscanf(fp, "%6s", &currentLGN->user);
		fscanf(fp, "%6s", &currentLGN->pass);
		currentLGN->next = NULL;

		if (iCnt != 0)
			add_search_lgn_node_to_end(headPtr, currentLGN, 0);
		else
			headPtr = currentLGN;
		iCnt++;
	}
	fclose(fp);
	return headPtr;
}

/*add_search_lgn_node_to_end: multi functions
	>search = 0, it adds the passed node to the end of linked L.
	>search = 1, search and return if found node
*/
short add_search_lgn_node_to_end(LGN *head,LGN *node, short isSearch){
	LGN *tmpNode = head;
	short result = 1;

	while (tmpNode->next != NULL){
		if (isSearch == 1 
				&& ((strcmp(tmpNode->pass, node->pass) == 0)
					&& (strcmp(tmpNode->user, node->user) == 0)
					)){
			result = 0;
		}
		tmpNode = tmpNode->next;
		
	}
	tmpNode->next = node;

	return result;
}

/*number_validator: validates values based on range*/
int number_validator(char *question, int * range){
	int userChoice;
	do{
		printf("\n%s", question);
		fflush(stdin);
		scanf("%d", &userChoice);
	} while (userChoice < range[0] || userChoice > range[1]);
	return --userChoice;
}

/*get_date: does set current date(Y-m-d) for passed pointers*/
void get_date(int * month, int * day, int * year) {
	struct tm *current;
	time_t timenow;
	time(&timenow);
	current = localtime(&timenow);
	*month = current->tm_mon + 1;
	*day = current->tm_mday;
	*year = current->tm_year + 1900;
}

/*write_new_employeeFile: ...*/
void write_new_employeeFile(EMP *head){
	FILE *fp = fopen(EMPLOYEES_HOLDER_FILE_N, "w");

	if (fp == NULL)
		perror("Wohoo, file does not exist(or can't open)\n");
	while (head != NULL){
		fprintf(fp, "%-3d %-3d %-6d %-20s %-40s %-25s %d-%d-%d\n", head->emp_id, head->department, head->salary, head->emp_name, head->emp_address, head->email, head->join_date.day, head->join_date.month, head->join_date.year);
		head = head->next;
	}
	fclose(fp);
}//end writeToFile(void)

/*get_valid_email: does validate the email based on in_array("@" && ".com")*/
char * get_valid_email(char *question){
	char userEmail[255];
	do{
		printf("%s", question);
		scanf("%s", userEmail);
		
		if (strstr(userEmail, ".com") != NULL && strstr(userEmail, "@") != NULL)
			return userEmail;
	} while (1);
	
	return NULL;
}

/*show_help: print help for failed console startin, exit after*/
void show_help(){
	char *outPut = "Starting options for main:\n- u || --user		feed in the username to unlock program\n- p || --password\t-- || -- password\t-- || --\n- h || --help		show the help menu\nSample run: -u petern -p ******";
	puts(outPut);
	exit(1);
}