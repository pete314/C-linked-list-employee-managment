#C linked lists - employee management  
###Project General Description 
This console application is based around employee management and tries to mimic a database. The data is kept on file system and read into linked list during execution.
The project was written in VS13, but C files can be found in folders to run in other IDE.

###Notes 
The application requires username and password in order to work, passwords and usernames are kept in plain text in **login_holder.dat**, login example:
```
LLEmp_db_v1.exe -u petern -p ******
```
Or to see the help menu:
```
LLEmp_db_v1.exe -h || --help
```

###File/folder structure

**Main.c** -> Contains main and all functions for related to general use

**MainHelper.c** -> Contains all helper functions

**stdafx.h** -> Contains the library headers

**MainHeader.h** -> Contains the main header for both the main and Mainhelper

**report_holder.dat** -> Option 6 report output

**employees_holder** -> Contains the employee details the program works with

**login_holder.dat** -> Contains the login credentials 
{DEBUG ONLY -> NEW_employees_holder.dat ->original data}


###Disclaimer
THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 
