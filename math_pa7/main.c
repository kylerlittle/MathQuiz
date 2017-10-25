/*************************************************************************
* Programmer: Kyler Little
* Class: CptS 121; Lab Section 11
* Programming Assignment: Programming Project 7
* Date: 11/16/2016                                                                    *
* Description: This program is an educational math program for kids. It is 
			   designed to help someone learn math. In the program, the user
			   may work his/her way through a series of quizzes designed to 
			   help him/her improve his/her foundational math skills. These 
			   skills include addition, subtraction, multiplication, division, 
			   and order of operations.
************************************************************************/

#include "math_pa7.h"

int main(void)
{
	/*VARIABLE DECLARATIONS*/
	int levels = 0;
	char initials[NAME] = { '\0' },
		lvl_names[NUM_LEVELS][MAX_NAME_LEN] = { "Easy", "Fair", "Intermediate",
		"Hard", "Impossible" };
	FILE *scr_rprt = NULL, *welcome = fopen("welcome.txt", "r"),
		*game_rules = NULL;
	Usr_Optn choice = 0;
	Answer usr_ansrs[NUM_QUESTIONS] = { 0 };
	User_Stats stats = { 0 };
	Qstn_Info quiz_q = { 0, 0 };
	srand((unsigned int)time(NULL));  //seed value

	/*GAME EXECUTION*/
	welcome_menu(welcome);
	fclose(welcome);
	while (choice != SAVE_QUIT)
	{
		quiz_q.num_correct = 0; //num_correct reset to 0 each time
		prnt_usr_intrfce();
		get_usr_optn(&choice);
		if (choice == LEARN)
		{
			game_rules = fopen("game_rules.txt", "r");
			lrn_game(game_rules);
			fclose(game_rules);
		}
		else if (choice == INITIALS)
		{
			get_initials(initials);
		}
		else if (choice == DIFFICULTY)
		{
			get_difficulty(&quiz_q, lvl_names);
		}
		else if (choice == NEW_SET)
		{
			if (quiz_q.difficulty == NULL)  //no difficulty selected yet; default is previous
			{
				get_difficulty(&quiz_q, lvl_names);
			}
			quiz(&quiz_q, &stats);
			system("pause");
		}
		else  //SAVE & QUIT
		{
			if (initials[0] == '\0')
			{
				printf("Whoah! You forgot to enter your initials.\n");
				get_initials(initials);
			}
			scr_rprt = fopen("score_report.txt", "w");
			if (scr_rprt) //opened successfully
			{
				printf("Statistics were written to file successfully!\n");
				output_stats(scr_rprt, stats, initials);
			}
			fclose(scr_rprt);
		}
	}
	printf("Thanks for playing!\n");			
	return 0;
}