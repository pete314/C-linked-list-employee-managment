/*
Main.c
@author			Peter Nagy (g00317399)
@description	This is one of the files holding the functions for the program.
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

int iEmpId = 0;
/*
	Starting options for main:
		-u || --user		feed in the username to unlock program
		-p || --password	--||--		password --||--
		-h || --help		show the help menu
*/
main(int argc, char *argv[]){
	EMP * ptrHead = NULL;
	argc > 1 ? handle_cmd_startin(argc, argv) : get_user_login(NULL);
	//EMP * ptrHead = init_list();//this option is for inti the list if empty input, NEVER CALLED
	ptrHead = read_emp_file();
	do{
		switch (menu_selector_input_listener(ptrHead)){
		case 1:
			//add employee
			add_employee(ptrHead);
			break;
		case 2:
			display_search_employee(ptrHead, NULL, 0);
			break;
		case 3:
			display_search_employee(ptrHead, NULL, 1);
			break;
		case 4:
			display_search_employee(ptrHead, &ptrHead, 2);
			break;
		case 5:
			//this is not the correct functionality it should display by department
			loop_on_list(ptrHead, 0);//puts("case 5");
			break;
		case 6:
			loop_on_list(ptrHead, 1);
			break;

		}
	} while (1);
	system("pause");
}//end main

void handle_cmd_startin(int argc, char *argv[]){
	//show_help();
	int iCnt = 1;

	if (argc < 5)
		show_help();

	LGN *loginCred = malloc(sizeof(LGN));

	while (argc >= iCnt){
		if (strcmp(argv[iCnt], "-h") == 0
			|| strcmp(argv[iCnt], "--help") == 0)
			show_help();
		else if (strcmp(argv[iCnt], "-u") == 0
			|| strcmp(argv[iCnt], "--user") == 0){
			if (argc > (++iCnt)){
				strcpy(loginCred->user, argv[iCnt]);
				--iCnt;
			}
			else
				show_help();
		}//end else if (strcmp(argv[iCnt], "-u")
		else if (strcmp(argv[iCnt], "-p") == 0
			|| strcmp(argv[iCnt], "--password") == 0){
			if (argc > (++iCnt)){
				strcpy(loginCred->pass, argv[iCnt]);
				break;
			}
			else
				show_help();
		}//end else if (strcmp(argv[iCnt], "--password")

		iCnt += 2;
	}//end while
	loginCred != NULL ? get_user_login(loginCred) : get_user_login(NULL);
}

/*init_list: creates the first node in the linked list
	@param null
	@return void
*/
EMP * init_list(EMP* firstNode){
	EMP* head = malloc(sizeof(EMP));
	head->emp_id = 1; ++iEmpId;
	head->next = NULL; 
	return head;
}


/*add_employee: add a new employee
	@return void
*/
void add_employee(EMP *head){
	add_emp_node_to_end(head, create_employee());
}//end add_employee

/*create_node: creates a new employee
	@return EMP * (employee pointer)
*/
EMP * create_employee(){
	EMP *ptrTmpEMP = malloc(sizeof(EMP));
	char *emp_name,
		 *emp_address,
		 *email;
	unsigned int dep, salary;
	int depRange[] = { 1, 3 };
	int monthRange[] = { 1, 13 };
	int yearRange[] = { 1900, 2015 };
	int dateRnage[3][2] = { { 1, 31 }, { 1, 29 }, {1, 32} };
	int day;
	fflush(stdin);
	
	ptrTmpEMP->emp_id = ++iEmpId;
	printf("Please give the employee name:");
	gets(ptrTmpEMP->emp_name);
	fflush(stdin);
	
	printf("Please give the employee address:");
	gets(ptrTmpEMP->emp_address);
	fflush(stdin);
	
	//gets(emp_name);
	ptrTmpEMP->department = number_validator("Please give the department: \n\t\t1) Developer\n\t\t2) Clerk \n\t\t3) Manager\n", depRange);
	fflush(stdin);
	
	printf("Please give the join date:");
	//gets(emp_name);
	ptrTmpEMP->join_date.year = ( 1 + number_validator("Please give the year(1900-2015)> ", yearRange)) ; //function does return -1, so add 1
	ptrTmpEMP->join_date.month = (1 + number_validator("Please give the month(1-12)> ", monthRange));//			--||--
	
	switch (ptrTmpEMP->join_date.month){
		case 1: 
		case 3: 
		case 5:
		case 7: 
		case 8:
		case 10: 
		case 12:
			ptrTmpEMP->join_date.day = number_validator("Please give the day(1-31)> ", dateRnage[0]);
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			number_validator("Please give the day(1-30)> ", dateRnage[2]);
			break;
		case 2:
			number_validator("Please give the day(1-28)> ", dateRnage[1]);
			break;

	}
	
	fflush(stdin);
	
	printf("Please give the salary:");
	scanf("%d", &(ptrTmpEMP->salary));
	fflush(stdin);
	
	strcpy(ptrTmpEMP->email, get_valid_email("Please give the eamil> "));
	fflush(stdin);
	ptrTmpEMP->next = NULL;

	return ptrTmpEMP;
}

/*display_search_employee: this is a multi functional function it can be called as follows:
	>head(true), ptrptrHead(null), 0 -> display the employees
	>head(true), ptrptrHead(null), 1 -> update employee(notice the isUpdate = 1)
	>head(true), ptrptrHead(null), 2 -> delete the found(!) employee
	>head(null), ptrptrHead(true), 2 -> delete the found(!) employee which is in the head node position
*/
void display_search_employee(EMP *head, EMP **ptrptrHead, int isUpdate){
	EMP *foundUser = (EMP *)malloc(sizeof(EMP));
	//unsigned int iEmpId = 0;
	char chEmpName[MAX_CHAR_LENGHT];
	char chUserChoice;
	char charrQuestion[] = "Would you like to search for ID or Name? (I/N)> ";
	printf("\n--------------------\n%7s DISPLAY EMPLOYEE DETAILS \n--------------------\n", "");
	do{
		fflush(stdin);
		printf("%s", charrQuestion);
	}while ((chUserChoice = getchar()) != 73 && chUserChoice != 'N');

	if (chUserChoice == 'I'){
		fflush(stdin);
		printf("Please give the Employee id: ");
		scanf("%d", &iEmpId);
	} else {
		fflush(stdin);
		printf("Please give the Employee name: ");
		gets(chEmpName);
	}

	foundUser = chUserChoice == 'I' ? search_list(head, iEmpId, NULL) : search_list(head, 0, chEmpName);

	if (foundUser != NULL){
		switch (isUpdate){
			case 0:
				print_table_header();
				print_employee(foundUser);
				print_table_footer();
				break;
			case 1:
				update_employee(foundUser);
				puts("New Employee data");
				print_table_header();
				print_employee(foundUser);
				print_table_footer();
				break;
			case 2:
				head == foundUser ? delete_head(ptrptrHead) : delete_employee(head, foundUser->emp_id);
				puts("Employee removed");
				break;
		}//end switch (isUpdate)
	} else
		puts("User not found!");
}//end display_search_employee(EMP *head, int isUpdate)

/*search_list: searchis the list for a particular item, does return first found*/
EMP * search_list(EMP *head, int id, char *name){
	EMP *tmpEmp = (EMP *)malloc(sizeof(EMP));
	tmpEmp = head;
	while (tmpEmp != NULL){
		if (id != 0 && tmpEmp->emp_id == id)
			return tmpEmp;
		else if (name != NULL && strcmp(tmpEmp->emp_name, name) == 0)
			return tmpEmp;
		tmpEmp = tmpEmp->next;
	}
	return NULL;
}
/*loop_on_list: prints out results either in report or normal format*/
void loop_on_list(EMP *head, short isReport){
	EMP *tmpEmp				= head;
	EMP *tmpResetHead		= head;
	int reportNumEmp[]		= { 0, 0, 0};
	int reportTotSalary[]	= { 0, 0, 0 };
	double reportTotBonuses[]	= { 0, 0, 0 };
	Date *currDate = malloc(sizeof(Date));
	get_date(&currDate->month, &currDate->day, &currDate->year);

	isReport == 1 ? print_report_table_header() : print_table_header();
	
	for (int i = 0; i < 3; i++){
		while (tmpEmp != NULL){
			if (tmpEmp->department == i)
				if (isReport == 0)
					print_employee(tmpEmp);
				else{
					++reportNumEmp[i];
					reportTotSalary[i] += tmpEmp->salary;
					reportTotBonuses[i] += (tmpEmp->salary * get_bonus_level(currDate, &(tmpEmp->join_date)));
				}
			tmpEmp = tmpEmp->next;
		}//end while
		if (isReport == 1){
			print_report_record(i, reportNumEmp[i], reportTotSalary[i], reportTotBonuses[i]);
			i == 0 ? write_report_record(i, reportNumEmp[i], reportTotSalary[i], reportTotBonuses[i], "w")
					: write_report_record(i, reportNumEmp[i], reportTotSalary[i], reportTotBonuses[i], "a");//if multiple not first row append
		}
		tmpEmp = tmpResetHead;
	}//end for
	print_table_footer();
}
/*get_bonus_level: does return the bonus level based on the join date*/
double get_bonus_level(Date *currDate, Date *joinDate){
	double bonusRate = 5;
	int bonusYears[] = { 10, 4, 5};
	for (int i = 0; i < 3; ++i){
		if (currDate->year - bonusYears[i] > joinDate->year)
			return (bonusRate - i) / 100;
		else if ((currDate->year - bonusYears[i] >= joinDate->year) && currDate->month < joinDate->month){
			if (currDate->day < joinDate->day)
				return (bonusRate - i) / 100;
		}
	}
	return 3/100;
}

/*print_table_header: print nice table header for normal output*/
void print_table_header(){
	printf("\n%6s RESULTS\n", "");
	printf("___________________________________________________________________________________________________________________");
	printf("\n| id | employee name     | email address      | employee address             | department | salary  | join date   |");
	printf("\n-------------------------------------------------------------------------------------------------------------------");
}

/*print_table_footer: prints nice table footer*/
void print_table_footer(){
	printf("\n___________________________________________________________________________________________________________________");
}

/*print_report_table_header: print nice table header for report*/
void print_report_table_header(){
	printf("\n%6s RESULTS\n", "");
	printf("___________________________________________________________________________________________________________________");
	printf("\n| Department | Number of employees | Total Salary / annum | Total Bonuses    | Total Financial Outlay   |");
	printf("\n-------------------------------------------------------------------------------------------------------------------");
}

/*print_report_record: does print report record*/
void print_report_record(int depId, int empNum, int totSal, double totBonus){
	printf("\n| %-10s | %-19d | %-20d | %-12s%-4.2lf | %7.2lf", get_department_name(depId), empNum, totSal, "", totBonus, (totBonus + totSal));
}

/*write_report_record: output the report record, append if not first row*/
void write_report_record(int depId, int empNum, int totSal, double totBonus, char *modifier){
	FILE *fp = fopen(REPORT_HOLDER_FILE, modifier);

	if (fp == NULL)
		perror("Wohoo, file does not exist(or can't open)\n");
	if (strcmp(modifier, "w") == 0){
		fprintf(fp, "\n| Department | Number of employees | Total Salary / annum | Total Bonuses    | Total Financial Outlay   |");
		fprintf(fp, "\n-------------------------------------------------------------------------------------------------------------------");
	}
	fprintf(fp, "\n| %-10s | %-19d | %-20d | %-17.2lf| %7.2lf", get_department_name(depId), empNum, totSal, totBonus, (totBonus + totSal));
	fclose(fp);
}

/*update_employee: update an employee node*/
void update_employee(EMP *tmpEmp){
	int depRange[] = { 1, 3 };
	int updateOpRange[] = { 1, 3 };
	int updateOption = number_validator("1) Address\n2) Department\n3) Salary\nSelect one> ", updateOpRange);

	switch (updateOption){
		case 0:
			printf("\nCurrent address: %s\n", tmpEmp->emp_address);
			fflush(stdin);
			printf("Please give the employee address: ");
			gets(tmpEmp->emp_address);
			break;
		case 1:
			printf("\nCurrent department: %s\n", get_department_name(tmpEmp->department));
			tmpEmp->department = number_validator("Please give the department: \n\t\t1) Developer\n\t\t2) Clerk \n\t\t3) Manager\nSelect one> ", depRange);
			break;
		case 2:
			printf("\nCurrent salary: %d\n", tmpEmp->salary);
			printf("Please give the salary:");
			scanf("%d", &(tmpEmp->salary));
			fflush(stdin);
			break;
	}
}

/*print_employee: does what is says*/
void print_employee(EMP *tmpEmp){
	//puts("\n");
	//for (int i = 0; i < 120; ++i) printf("_");
	printf("\n|%3d | ", tmpEmp->emp_id);
	printf("%-17s | ", tmpEmp->emp_name);
	printf("%-18s | ", tmpEmp->email);
	printf("%-28s | ", tmpEmp->emp_address);
	printf("%-10s | ", get_department_name(tmpEmp->department));
	printf("%-6d  |", tmpEmp->salary);
	printf(" %d-%d-%d  |", tmpEmp->join_date.day, tmpEmp->join_date.month, tmpEmp->join_date.year);
}

/*get_department_name: return the repartment string from int passed*/
char* get_department_name(int depId){
	switch (depId){
		case 0:
			return "Developer";
		case 1:
			return "Clerk";
		case 2:
			return "Manager";
		default:
			return "Not set yet";
	}
}

/*menu_selector_input_listener: get input, and validate for user menu choice*/
int menu_selector_input_listener(EMP *head){
	unsigned short usUserChoice = -1;
	char *chQuestion = "\nPlease select an option> ";
	printf("\n--------------------\n%7s MENU OPTIONS\n--------------------", "");
	puts("\n\t1) Add employee\n\t2) Display employee details\n\t3) Update employee\n\t4) Delete employee\n\t5) Display all employees by department\n\t6) Employee Report\n\t0) Exit program\n");
	do{
		printf(chQuestion);
		scanf("%hd", &usUserChoice);
	} while (usUserChoice < 0 && usUserChoice > 6);
	if (usUserChoice == 0) exit_now(head);
}//end user_menu_selection

/*exit_now: quit the app after user aproved and tidy data*/
void exit_now(EMP *head){
	char cUserChoice;
	puts("Are you sure to exit?(Y/n)");
	while ((cUserChoice = getchar()) != 'y'
									&& cUserChoice != 'Y'
									&& cUserChoice != 'n'
									&& cUserChoice != 'N')
		;
	if (cUserChoice == 'Y' || cUserChoice == 'y'){
		write_new_employeeFile(head);
		puts("BYE NOW");
		Sleep(2000);//just give a chance to realize
		exit(1);
	}
}

/*delete_employee: remove employee from linked list*/
void delete_employee(EMP *head, int empId){
	EMP *currentEMP = head;
	EMP *oldEMP = head;
	while (currentEMP != NULL){
		if (currentEMP->emp_id == empId){
			oldEMP->next = currentEMP->next;
			free(currentEMP);
			return;
		}

		oldEMP = currentEMP;
		currentEMP = currentEMP->next;
	}
}

/*delete_head: delete the head node*/
void delete_head(EMP **head){
	EMP *tmpHead = *head;
	//newHead = (*head)->next;
	//free(head);
	*head = tmpHead->next;
	free(tmpHead);
}//end delete_head()
