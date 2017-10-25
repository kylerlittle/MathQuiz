#ifndef EDUCATION_MATH_PROGRAM_7
#define EDUCATION_MATH_PROGRAM_7

/*Standard Libraries Included*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*Macro Constants*/
#define MAX_CHAR_PER_LINE 40
#define ASCII_LET_DIFF 97
#define NUM_QUESTIONS 10
#define NUM_LEVELS 5
#define MAX_PROB_LEN 30
#define MAX_NUM_SIZE 5
#define NAME 4
#define MAX_NAME_LEN 13

/*Defined Types*/
typedef enum usr_optn
{
	LEARN, INITIALS, DIFFICULTY, NEW_SET, SAVE_QUIT
} Usr_Optn;
typedef enum operator_t
{
	ADD, SUBTRACT, MULTIPLY, DIVIDE
} Operator_t;
typedef enum random
{
	NOT_RANDOM, RANDOM
} Random;
typedef enum answer
{
	INCORRECT, CORRECT
} Answer;
typedef enum level
{
	EASY = 1, FAIR, INTER, HARD, IMPOSS
} Level;
typedef struct qstn_info
{
	int num_correct;
	Level difficulty;
} Qstn_Info;
typedef struct user_stats
{
	int easy_score;
	int fair_score;
	int inter_score;
	int hard_score;
	int impsble_score;
	int total_score;
} User_Stats;


/*Function Protypes & Definitions*/

/**************************************************************************
* Function: welcome_menu
* Description: This function reads in each string (of size MAX_CHAR_PER_LINE),
			   and continues to print to the screen until the end of the file
			   is reached.
* Input parameters: File containing the rules of the game
* Returns: Nothing
* Preconditions: File "rules" has been opened successfully.
* Postconditions: Rules are printed to screen. Screen pause & clear.
**************************************************************************/
void welcome_menu(FILE *rules);

/**************************************************************************
* Function: prnt_usr_intrfce
* Description: This function prints off the user interface (options a to e)
* Input parameters: None
* Returns: Nothing
* Preconditions: None
* Postconditions: Interface printed to screen.
**************************************************************************/
void prnt_usr_intrfce(void);

/**************************************************************************
* Function: get_usr_optn
* Description: This function gets the user's selection (must be a char
			   within ASCII range (a-e). Else, the computer will continue
			   to prompt the user.
* Input parameters: Pointer to Usr_Option enum type
* Returns: Nothing
* Preconditions: None
* Postconditions: Usr_Optn is modified to one of five choices, based on
				  the user's input.
**************************************************************************/
void get_usr_optn(char *Usr_Optn); 

/**************************************************************************
* Function: lrn_game
* Description: This function reads in the each line of the text file
			   game_rules and prints to the screen.
* Input parameters: Text file
* Returns: Nothing
* Preconditions: File was opened successfully.
* Postconditions: game rules are printed to screen. Screen pause & clear.
**************************************************************************/
void lrn_game(FILE *game_rules);

/**************************************************************************
* Function: get_initials
* Description: This function assigns a maximum of three characters that the
			   user enters to the character array. However, the user may
			   enter up to 12 characters without the program crashing.
* Input parameters: String of max size 13 (including null char)
* Returns: Nothing
* Preconditions: Name_str points to contiguous memory.
* Postconditions: name_str is modified to having 0-3 characters & the null
				  character. System pause.
**************************************************************************/
void get_initials(char *name_str);

/**************************************************************************
* Function: get_difficulty
* Description: This function prints off a menu of level difficulties that 
			   the user may select from. It will ask the user to enter a
			   level (1-5). If the value is not within that range, it
			   will continue to prompt the user.
* Input parameters: Pointer to the plyr_info struct, lvl_names array
					of strings
* Returns: Nothing
* Preconditions: lvl_names contains strings
* Postconditions: difficulty level is assigned to the "Level" parameter of
				  the struct within the valid range
**************************************************************************/
void get_difficulty(Qstn_Info *plyr_info, char lvl_names[][MAX_NAME_LEN]);

/**************************************************************************
* Function: opratr_conv
* Description: This function returns a string with an appropriate operator
			   (as a char) as the first entry & null char as second entry.
			   This is either determined by the random number (based on
			   Div_op-- meaning # of operators possible) or it is nonrandom.
* Input parameters: Div_Op (gives the value to mod the random number by),
					rand_or_no (if not random, then div_op serves as the
					enum value of the operator to assign to the string
					(i.e. if Div_Op is 1 & NOT_RANDOM, this means subtract),
					op_str string
* Returns: String of size 2 (containing the operator & null char)
* Preconditions: op_str represents contiguous memory
* Postconditions: Op_Str's first entry is modified to the appropriate
				  operator (which is a char)
**************************************************************************/
char *opratr_conv(int div_op, char *op_str, Random rand_or_no);

/**************************************************************************
* Function: put_exprsion_togthr
* Description: This function generates random numbers (based on the divisor
			   to mod by) & combines the randomly generated operators into
			   a string. It returns a pointer to this string. Note that 
			   num_terms is ONE LESS than # terms in problem
* Input parameters: int divisor, int div_op (to pass into opratr_conv), 
					num_terms for particular level, range (to yield negative
					values if needed), prob string (to modify), and Random
					enumerated type
* Returns: Pointer to Problem String
* Preconditions: Prob has enough contiguous memory to support operations
* Postconditions: Prob is modified to contain a random mathematical expression
**************************************************************************/
char *put_exprsion_togthr(int divisor, int div_op, int num_terms, int range, char *prob,
	Random rand_or_not);

/**************************************************************************
* Function: generate_easy
* Description: This function determines the particular characteristics
			   of the math problem given the number of correct answers; 
			   will get more difficult as correct_answers increases; prob
			   will be "easy"
* Input parameters: plyr_info struct, problem string
* Returns: Pointer to Problem String
* Preconditions: Prob has enough contiguous memory to support operations
* Postconditions: Prob is modified to contain a random mathematical expression;
				  done via put_exprsion_togthr
**************************************************************************/
char *generate_easy(Qstn_Info *plyr_info, char *prob);

/**************************************************************************
* Function: generate_fair
* Description: This function determines the particular characteristics
			   of the math problem given the number of correct answers;
			   will get more difficult as correct_answers increases; prob
			   will be "fair"
* Input parameters: plyr_info struct, problem string
* Returns: Pointer to Problem String
* Preconditions: Prob has enough contiguous memory to support operations
* Postconditions: Prob is modified to contain a random mathematical expression;
				  done via put_exprsion_togthr
**************************************************************************/
char *generate_fair(Qstn_Info *plyr_info, char *prob);

/**************************************************************************
* Function: generate_inter
* Description: This function determines the particular characteristics
			  of the math problem given the number of correct answers;
			  will get more difficult as correct_answers increases; prob
			  will be "intermediate"
* Input parameters: plyr_info struct, problem string
* Returns: Pointer to Problem String
* Preconditions: Prob has enough contiguous memory to support operations
* Postconditions: Prob is modified to contain a random mathematical expression;
				  done via put_exprsion_togthr
**************************************************************************/
char *generate_inter(Qstn_Info *plyr_info, char *prob);

/**************************************************************************
* Function: generate_hard
* Description: This function determines the particular characteristics
			   of the math problem given the number of correct answers;
			   will get more difficult as correct_answers increases; prob
			   will be "hard"
* Input parameters: plyr_info struct, problem string
* Returns: Pointer to Problem String
* Preconditions: Prob has enough contiguous memory to support operations
* Postconditions: Prob is modified to contain a random mathematical expression;
				  done via put_exprsion_togthr
**************************************************************************/
char *generate_hard(Qstn_Info *plyr_info, char *prob);

/**************************************************************************
* Function: generate_impsble
* Description: This function determines the particular characteristics
			   of the math problem given the number of correct answers;
			   will get more difficult as correct_answers increases; prob
			   will be "impossible"
* Input parameters: plyr_info struct, problem string
* Returns: Pointer to Problem String
* Preconditions: Prob has enough contiguous memory to support operations
* Postconditions: Prob is modified to contain a random mathematical expression;
				  done via put_exprsion_togthr
**************************************************************************/
char *generate_impsble(Qstn_Info *plyr_info, char *prob);

/**************************************************************************
* Function: quiz
* Description: This function carries out the "quiz" based on the difficulty 
			   selected by the user; regardless, there are 10 questions;
			   within quiz, problem is generated, displayed, evaluated, and
			   compared to the user's answer. Additionally, the struct
			   scr_info is updated based on the difficulty of the level
			   and if the answer was correct of not.
* Input parameters: question info struct, scoring info struct
* Returns: Nothiung
* Preconditions: Structs are defined correctly
* Postconditions: User's Quiz Stats are updated.
**************************************************************************/
void quiz(Qstn_Info *plyr_info, User_Stats *scr_info);

/**************************************************************************
* Function: get_ansr
* Description: This function simply gets the user's answer and returns it.
* Input parameters: None
* Returns: User's Integral Answer
* Preconditions: None
* Postconditions: None
**************************************************************************/
int get_ansr(void);

/**************************************************************************
* Function: eval_prb
* Description: Given that the problem has been parsed into its constituent
			   integers and operators (via brk_down_prb), this function
			   will evaluate that expression using operator precedence and
			   return the result
* Input parameters: operator array, numbers_from_problem array, # of operators
* Returns: The Correct Answer
* Preconditions: Op_array & num_array have contiguous memory
* Postconditions: None
**************************************************************************/
int eval_prb(char *op_array, int *num_array, int num_ops);

/**************************************************************************
* Function: brk_down_prb
* Description: This function parses the "problem string" into its constituent
			   integers and operators & places each of these into the terms
			   and op arrays, respectively
* Input parameters: problem string, empty integer array, empty operator array
* Returns: # of operators (for use in eval_prb)
* Preconditions: Prb, terms, & op point to contiguous memory
* Postconditions: Terms Array contains the actual numbers from the problem
				  string, and op contains the operators (as chars)
**************************************************************************/
int brk_down_prb(char *prb, int terms[], char *op);

/**************************************************************************
* Function: chk_ans
* Description: This function compares the player's answer to the correct 
			   answer. If they are equal, returns CORRECT. Else, returns
			   INCORRECT.
* Input parameters: player's answer & correct answer
* Returns: CORRECT or INCORRECT
* Preconditions: None
* Postconditions: PNone
**************************************************************************/
Answer chk_ans(int plyr_ansr, int correct_ansr);

/**************************************************************************
* Function: update_pts
* Description: This functions adds 1 to num_correct (parameter of plyr_info)
			   if the answer is CORRECT.
* Input parameters: plyr_info struct, Answer correct_or_not
* Returns: nothing
* Preconditions: None
* Postconditions: +1 to plyr_info.num_correct if CORRECT
**************************************************************************/
void update_pts(Qstn_Info *plyr_info, Answer crrct__or_no);

/**************************************************************************
* Function: update_usr_stats
* Description: This function updates the user's score card based on the 
			   number of questions correct and the number of questions 
			   incorrect in a level. Note that different points are given
			   based on the difficulty. All points are added to total score.
* Input parameters: plyr_info struct, user_score_card struct
* Returns: Nothing
* Preconditions: None
* Postconditions: The User's "scorecard" is updated.
**************************************************************************/
void update_usr_stats(Qstn_Info plyr_info, User_Stats *usr_scr_crd);

/**************************************************************************
* Function: output_stats
* Description: This function simply outputs the user's game stats to a file.
* Input parameters: FILE, user_scr_crd struct, player's initials (as string)
* Returns: Nothing
* Preconditions: File was opened successfully.
* Postconditions: stats file is updated
**************************************************************************/
void output_stats(FILE *stats, User_Stats usr_scr_crd, char *init);

#endif