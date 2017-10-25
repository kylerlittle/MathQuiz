#include "math_pa7.h"

void welcome_menu(FILE *rules)
{
	putchar('\n');
	char text_print[MAX_CHAR_PER_LINE] = { '\0' };
	while (!feof(rules))
	{
		fgets(text_print, 40, rules);
		fputs(text_print, stdout);
	}
	printf("\n\n\t\t");
	system("pause");
	system("cls");
}
void prnt_usr_intrfce(void)
{
	system("cls");
	printf("Please select an option below:\n");
	printf("a. Learn about how to use the program.\n");
	printf("b. Enter your initials (2-3 individual characters).\n");
	printf("c. Difficulty selection\n");
	printf("d. Start a new sequence of problems.\n");
	printf("e. Save and Quit.\n");
}
void get_usr_optn(char *Usr_Optn)
{
	char choice = '\0';
	do
	{
		scanf("%c", &choice);
		*Usr_Optn = (int)choice - ASCII_LET_DIFF;
	} while (*Usr_Optn > 4 | *Usr_Optn < 0);  //out of range of options 0-4
	system("cls");
}
void lrn_game(FILE *game_rules)
{
	putchar('\n');
	char text_print[MAX_CHAR_PER_LINE] = { '\0' };
	while (!feof(game_rules))
	{
		fgets(text_print, 40, game_rules);
		fputs(text_print, stdout);
	}
	printf("\n\n\t\t");
	system("pause");
	system("cls");
}
void get_initials(char *name_str)
{
	char buffer[MAX_NAME_LEN] = { '\0' };
	printf("Please enter your initials: <2-3 characters>\n");
	scanf("%s", buffer);
	strncpy(name_str, buffer, 3);
	printf("Initials entered: %s\n", name_str);
	system("pause");
}
void get_difficulty(Qstn_Info *plyr_info, char lvl_names[][MAX_NAME_LEN])
{
	int lev = 0, level = 0;
	printf("Please select a difficulty: <1-5> \n");
	for (lev = 0; lev < NUM_LEVELS; ++lev)
	{
		printf("%d. %s \n", lev + 1, lvl_names[lev]);
	}
	do
	{
		scanf("%d", &level);
	} while (level < 1 | level > 5);
	plyr_info->difficulty = level;
}
char *opratr_conv(int div_op, char *op_str, Random rand_or_no)
{
	int op = div_op;
	if (rand_or_no)
	{
		op = rand() % div_op;
	}
	if (op == ADD)
	{
		op_str[0] = '+';
	}
	else if (op == SUBTRACT)
	{
		op_str[0] = '-';
	}
	else if (op == MULTIPLY)
	{
		op_str[0] = '*';
	}
	else //DIVIDE
	{
		op_str[0] = '/';
	}
	return op_str;
}
char *put_exprsion_togthr(int divisor, int div_op, int num_terms, int range, char *prob,
	Random rand_or_not)
{
	int i = 0, rand_num = 0;
	char num[MAX_NUM_SIZE] = { '\0' }, op_str[2] = { '\0' };
	for (i = 0; i < num_terms; ++i)
	{
		do
		{
			rand_num = rand() % divisor - range;
		} while (rand_num == 0 && op_str[0] == '/'); //NO DIVISION BY 0
		itoa(rand_num, num, 10); //10 because it's a base 10 number system
		strcat(prob, num);
		strcat(prob, " ");
		strcat(prob, opratr_conv(div_op, op_str, rand_or_not));
		strcat(prob, " ");
	}
	do
	{
		rand_num = rand() % divisor - range;
	} while (rand_num == 0 && op_str[0] == '/'); //NO DIVISION BY 0
	itoa(rand_num, num, 10); //10 because it's a base 10 number system
	strcat(prob, num);
	return prob;
}
char *generate_easy(Qstn_Info *plyr_info, char *prob)
{
	int divisor = 0, div_op = 2;
	Random rand = RANDOM;
	if (plyr_info->num_correct > 3)
	{
		divisor = 6;
	}
	else if (plyr_info->num_correct > 6)
	{
		divisor = 10;
	}
	else
	{
		divisor = 3;
		div_op = ADD;
		rand = NOT_RANDOM;
	}
	return put_exprsion_togthr(divisor, div_op, 2, 0, prob, rand);
}
char *generate_fair(Qstn_Info *plyr_info, char *prob)
{
	int divisor = 0, div_op = MULTIPLY;
	Random rand = NOT_RANDOM;
	if (plyr_info->num_correct > 3)
	{
		divisor = 6;
	}
	else if (plyr_info->num_correct > 6)
	{
		divisor = 10;
	}
	else
	{
		divisor = 3;
	}
	return put_exprsion_togthr(divisor, div_op, 1, 0, prob, rand);
}
char *generate_inter(Qstn_Info *plyr_info, char *prob)
{
	int divisor = 0, div_op = DIVIDE;
	Random rand = NOT_RANDOM;
	if (plyr_info->num_correct > 3)
	{
		divisor = 6;
	}
	else if (plyr_info->num_correct > 6)
	{
		divisor = 10;
	}
	else
	{
		divisor = 3;
	}
	return put_exprsion_togthr(divisor, div_op, 1, 0, prob, rand);
}
char *generate_hard(Qstn_Info *plyr_info, char *prob)
{
	int divisor = 0, div_op = 4;
	Random rand = RANDOM;
	if (plyr_info->num_correct > 3)
	{
		divisor = 6;
	}
	else if (plyr_info->num_correct > 6)
	{
		divisor = 9;
	}
	else
	{
		divisor = 3;
	}
	return put_exprsion_togthr((divisor * 2), div_op, 2, divisor, prob, rand);
}
char *generate_impsble(Qstn_Info *plyr_info, char *prob)
{
	int divisor = 0, div_op = 4;
	Random rand = RANDOM;
	if (plyr_info->num_correct > 3)
	{
		divisor = 400;
	}
	else if (plyr_info->num_correct > 6)
	{
		divisor = 999;
	}
	else
	{
		divisor = 40;
	}
	return put_exprsion_togthr((divisor * 2), div_op, 3, divisor, prob, rand);
}
void quiz(Qstn_Info *plyr_info, User_Stats *scr_info)
{
	int q = 0, crct_ansr = 0, usr_ansr = 0, num_ops = 0;
	Answer ansr = 0;
	for (q = 0; q < NUM_QUESTIONS; ++q)
	{
		int terms[4] = { 0 }; //these two arrays should be reset every time
		char op[3] = { '\0' };
		char prob_act[MAX_PROB_LEN] = { '\0' }, prob[MAX_PROB_LEN] = { '\0' };
		if (plyr_info->difficulty == EASY)
		{
			strcpy(prob_act, generate_easy(plyr_info, prob));
		}
		else if (plyr_info->difficulty == FAIR)
		{
			strcpy(prob_act, generate_fair(plyr_info, prob));
		}
		else if (plyr_info->difficulty == INTER)
		{
			strcpy(prob_act, generate_inter(plyr_info, prob));
		}
		else if (plyr_info->difficulty == HARD)
		{
			strcpy(prob_act, generate_hard(plyr_info, prob));
		}
		else
		{
			strcpy(prob_act, generate_impsble(plyr_info, prob));
		}
		printf("\tProblem %d:\n %s\n", q + 1, prob_act);
		system("pause");
		num_ops = brk_down_prb(prob_act, terms, op);
		crct_ansr = eval_prb(op, terms, num_ops);  //calculates correct answer
		usr_ansr = get_ansr();  //gets user's answer
		ansr = chk_ans(usr_ansr, crct_ansr);  //is answer correct?
		update_pts(plyr_info, ansr);
	}
	printf("SCORE: %d out of 10\n", plyr_info->num_correct);
	update_usr_stats(*plyr_info, scr_info);
}
int get_ansr(void)
{
	int usr_ansr = 0;
	printf("Enter your answer: ");
	scanf("%d", &usr_ansr);
	return usr_ansr;
}
int eval_prb(char *op_array, int *num_array, int num_ops)
{
	int sum = 0, i = 0;
	for (i = 0; i < num_ops; ++i)  //does all multiplication/division
	{
		if (op_array[i] == '*')
		{
			num_array[1 + i] = num_array[i] * num_array[1 + i];
			num_array[i] = 0;
		}
		else if (op_array[i] == '/')
		{
			num_array[i + 1] = num_array[i] / num_array[i + 1];
			num_array[i] = 0;
		}
	}
	for (i = 0; i < (num_ops + 1); ++i) //sums up remaining entries (can do even if no add/sub)
	{
		sum += num_array[i];
	}
	for (i = 0; i < num_ops; ++i) //if subtraction exists, subtract off value at num_index + 1
	{
		if (op_array[i] == '-')
		{
			sum -= (2 * num_array[1 + i]); //needs to be twice since summing it prior.
		}
	}
	return sum;
}
int brk_down_prb(char *prb, int terms[], char *op)
{
	int i = 0, int_i = 0, op_i = 0, ASCII_conv = (int)'0', index_start = 0;
	while (prb[i] != '\0')
	{
		if ((int)prb[i] >= 48 && (int)prb[i] <= 57) //ENTRY IS AN INTEGER
		{
			terms[int_i] = (int)prb[i] - ASCII_conv;   //THIS PUTS EACH INTEGER INTO ENTRY OF TERMS[]
			index_start = i;
			if ((int)prb[i + 1] >= 48 && (int)prb[i + 1] <= 57)
			{
				terms[int_i] = (10 * terms[int_i]) + (int)prb[i + 1] - ASCII_conv;
				i += 1;
				if ((int)prb[i + 1] >= 48 && (int)prb[i + 1] <= 57)
				{
					terms[int_i] = (10 * terms[int_i]) + (int)prb[i + 1] - ASCII_conv;
					i += 1;
				}
			}
			if (prb[index_start - 1] == '-') //integer is negative
			{
				terms[int_i] *= -1; //make it negative
			}
			++int_i;
		}
		else if ((int)prb[i] >= 42 && (int)prb[i] <= 47 && prb[i+1] == ' ') //MUST BE AN OPERATOR
		{  //THIS PUTS EACH OPERATOR INTO ENTRY OF OP[]
			op[op_i] = prb[i];
			++op_i;
		}
		++i;
	}
	return op_i;  //number of operators
}
Answer chk_ans(int plyr_ansr, int correct_ansr)
{
	Answer n = INCORRECT;
	if (plyr_ansr == correct_ansr)
	{
		n = CORRECT;
		printf("Correct!\n");
	}
	else
	{
		printf("Sorry! The answer was actually %d.\n", correct_ansr);
	}
	return n;
}
void update_pts(Qstn_Info *plyr_info, Answer crrct__or_no)
{
	if (crrct__or_no == CORRECT)
	{
		plyr_info->num_correct += 1;
	}
}
void update_usr_stats(Qstn_Info plyr_info, User_Stats *usr_scr_crd)
{
	if (plyr_info.difficulty == EASY)
	{
		usr_scr_crd->easy_score += (plyr_info.num_correct * 10 * plyr_info.difficulty);
		usr_scr_crd->easy_score -= ((NUM_QUESTIONS - plyr_info.num_correct) * 5 * plyr_info.difficulty);
		usr_scr_crd->total_score += usr_scr_crd->easy_score;
	}
	else if (plyr_info.difficulty == FAIR)
	{
		usr_scr_crd->fair_score += (plyr_info.num_correct * 10 * plyr_info.difficulty);
		usr_scr_crd->fair_score -= ((NUM_QUESTIONS - plyr_info.num_correct) * 5 * plyr_info.difficulty);
		usr_scr_crd->total_score += usr_scr_crd->fair_score;
	}
	else if (plyr_info.difficulty == INTER)
	{
		usr_scr_crd->inter_score += (plyr_info.num_correct * 10 * plyr_info.difficulty);
		usr_scr_crd->inter_score -= ((NUM_QUESTIONS - plyr_info.num_correct) * 5 * plyr_info.difficulty);
		usr_scr_crd->total_score += usr_scr_crd->inter_score;
	}
	else if (plyr_info.difficulty == HARD)
	{
		usr_scr_crd->hard_score += (plyr_info.num_correct * 10 * plyr_info.difficulty);
		usr_scr_crd->hard_score -= ((NUM_QUESTIONS - plyr_info.num_correct) * 5 * plyr_info.difficulty);
		usr_scr_crd->total_score += usr_scr_crd->hard_score;
	}
	else if (plyr_info.difficulty == IMPOSS)
	{
		usr_scr_crd->impsble_score += (plyr_info.num_correct * 10 * plyr_info.difficulty);
		usr_scr_crd->impsble_score -= ((NUM_QUESTIONS - plyr_info.num_correct) * 5 * plyr_info.difficulty);
		usr_scr_crd->total_score += usr_scr_crd->impsble_score;
	}
}
void output_stats(FILE *stats, User_Stats usr_scr_crd, char *init)
{
	fprintf(stats, "FINAL SCORES & STATS for %s\n**********************\n", init);
	fprintf(stats, "Easy Score: %d\n", usr_scr_crd.easy_score);
	fprintf(stats, "Fair Score: %d\n", usr_scr_crd.fair_score);
	fprintf(stats, "Intermediate Score: %d\n", usr_scr_crd.inter_score);
	fprintf(stats, "Hard Score: %d\n", usr_scr_crd.hard_score);
	fprintf(stats, "Impossible Score: %d\n**********************\n", usr_scr_crd.impsble_score);
	fprintf(stats, "\tTotal Score: %d\n", usr_scr_crd.total_score);
}