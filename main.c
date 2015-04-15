// Justin Ting, 430203826 - Operating Systems Internals Assignment 1
// Monday 10am-12pm lab - Tutor: Jeshua

#include "helpers.h"
#include "internal_commands.h"
#include "external_commands.h"
#include "execute.h"

int main (int argc, char * argv[]) {
	set_shell_path_envvar();
	while (1) {

		//Print username, domain,and current
		// directory with user prompt
		print_prompt_line();

		FILE * input = fopen(argv[1], "r");
		int command_check = 0;
		
		if (input == NULL)
		{
			command_check = 1;
			input = stdin;
		}

    	//Read user input and remove newline character
		char str[1024];
		while (fgets(str, 1024, input) != NULL)
		{
			if (*str == '\n') break; //Do nothing on empty input
			str[strlen(str) - 1] = '\0'; //Remove newline

    		//Split string and store arguments
			int arg_count = 0;
			char **args;	
			parse_input(&arg_count, &args, str);
			store_args(&arg_count, str, &args);
			execute_commands(arg_count, args);

			free_args(&arg_count, &args);

			if (command_check == 1)	break; //Escape if not reading script
		}
		printf("\n");
		if (command_check == 0) exit(0);
	}
	return 0;
}