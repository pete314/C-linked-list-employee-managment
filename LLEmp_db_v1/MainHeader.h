/*
MainHeader.h

@author			Peter Nagy (g00317399)
@description	This is of the header files, main for the Main.c
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
#ifndef MAIN_HEADER "MainHeader.h"
#define MAIN_HEADER
#define MAX_CHAR_LENGHT			255
#define LOGIN_HOLDER_FILE		"login_holder.dat"
#define EMPLOYEES_HOLDER_FILE	"employees_holder.dat"
#define EMPLOYEES_HOLDER_FILE_N	"employees_holder.dat" // for testing reasons keep "NEW_employees_holder.dat"
#define REPORT_HOLDER_FILE		"report_holder.dat"
#define LOGIN_CRED_LENGTH		6

typedef enum {DEVELOPER, CLERK, MANAGER} departments;
typedef struct date Date;
typedef struct employee EMP;
typedef struct login_struct LGN;

struct date {
	unsigned short day;
	unsigned short month;
	unsigned short year;
};

struct employee{
	unsigned int emp_id; //unique, index
	char emp_name[MAX_CHAR_LENGHT];
	char emp_address[MAX_CHAR_LENGHT];
	departments department;
	Date join_date;
	unsigned int salary;
	char email[MAX_CHAR_LENGHT];
	EMP * next;
};

struct login_struct{
	char user[LOGIN_CRED_LENGTH+1];
	char pass[LOGIN_CRED_LENGTH+1];
	LGN * next;
};

extern void exit_now(EMP *);//user aproved exit, tidy data
extern int menu_selector_input_listener();//get user selection for menu option(validate)
extern void add_employee(EMP *);//add new employee to list
extern EMP * create_employee();//creates a new employee in memory
extern EMP * init_list();//never called from current context, TEST ONLY
extern void display_search_employee(EMP *, EMP **, int);//see main.c
extern EMP * search_list(EMP *, int, char *);//can search for id or name
void update_employee(EMP *);//updates the specified fileds for found employee
extern void print_employee(EMP *);//prints an employee's data on screen
extern void loop_on_list(EMP *head, short isReport);//see main.c
extern void delete_head(EMP **head);//removes the head node
extern void delete_employee(EMP *head, int empId);//removes not head nodes
extern EMP * read_emp_file();//see MainHelper.c 
extern LGN * read_login_file();//see MainHelper.c
extern LGN * init_login_list(LGN *headLGN);//see mainHelper.c
extern void add_emp_node_to_end(EMP *head, EMP *node);//add emp node to end of list
extern char* get_department_name(int depId);//returns the department char*
extern void print_table_header();//prints the nice table header
extern void print_table_footer();//prints nice table footer
extern void print_report_table_header();//prints nice table header for riport
extern void get_date(int * month, int * day, int * year);//sets the pointers to current date 
extern double get_bonus_level(Date *currDate, Date *joinDate);//calculates the bonus level based on join date
extern void print_report_record(int depId, int empNum, int totSal, double totBonus);//print the report to screen
extern void get_user_login(LGN *userStatin);//manage user login
extern short add_search_lgn_node_to_end(LGN *head, LGN *node, short);//add LGN node to the end
extern int number_validator(char *question, int * range);//validate number and print question till not in range
extern void write_new_employeeFile(EMP *head);//writes the employee file
extern void write_report_record(int depId, int empNum, int totSal, double totBonus, char *modifier);//see MainHelper.c
extern char * get_valid_email(char *question);//validates the email
extern void show_help();//help output for console startin
extern void handle_cmd_startin(int argc, char *argv[]);//sort out the console startin options

extern int iEmpId;//employye counter used in Main.c & helper to keep track of highest id
#endif