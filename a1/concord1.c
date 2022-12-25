#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EXCLUSION_WORDS 20
#define EXCLUSION_WORD_LEN 21 //one extra for \n
#define INPUT_LINES 100
#define INPUT_LEN 71 //one extra for \n
#define MAX_DIST_WORDS 101
#define WORDS_LEN MAX_DIST_WORDS + EXCLUSION_WORDS

char all_words[INPUT_LINES][INPUT_LEN];
//char all_words2[INPUT_LINES][INPUT_LEN];
char sentence_ref[INPUT_LINES][INPUT_LEN];
char words[WORDS_LEN][INPUT_LEN];
int words_count = 0;

void print_and_cap(char*, char*);
int forward_compare_str(const void *a, const void *b);
int backward_compare_str(const void *a, const void *b);

int main(){
		
	char junk_input[INPUT_LEN];
	fgets(junk_input, INPUT_LEN, stdin);	//gets rid of first two lines	
	fgets(junk_input, INPUT_LEN, stdin);
	
	//gets array of exclusion words
	char exclusion_words[EXCLUSION_WORDS][EXCLUSION_WORD_LEN]; //maybe put global scope
	
	fgets(exclusion_words[0], EXCLUSION_WORD_LEN - 1, stdin);
	int ex_words_count = 0;
	while(strncmp(exclusion_words[ex_words_count], "\"\"\"\"\n", EXCLUSION_WORD_LEN - 1) != 0 && ex_words_count < EXCLUSION_WORD_LEN - 1){
		ex_words_count++;
		fgets(exclusion_words[ex_words_count], EXCLUSION_WORD_LEN - 1, stdin);
			
	}
 
	strncpy(exclusion_words[ex_words_count], "\0", 1) ;
	
	
	
	//adding all main words to all_words array
	int all_words_count = 0;
	int nl_count = 0; //newline count
	while(fgets(all_words[all_words_count], INPUT_LEN, stdin)!= NULL){
		nl_count = 0;
		while(all_words[all_words_count][nl_count] != '\n' && nl_count <= INPUT_LEN ){
			nl_count++;	
		}
		all_words[all_words_count][nl_count] = '\0';
		//printf("%d: %s\n", all_words_count, all_words[all_words_count]);
		strncpy(sentence_ref[all_words_count], all_words[all_words_count], INPUT_LEN);
		//strncpy(all_words2[all_words_count], all_words[all_words_count], INPUT_LEN);
		all_words_count++;
		
	}
	
	//adds all words to words array
	for(int i = 0; i < WORDS_LEN; i++){

		char *token = strtok(all_words[i], " ");
		while(token != NULL && words_count < WORDS_LEN){
			strncpy(words[words_count], token, INPUT_LEN);
			words_count++;
			token = strtok(NULL, " ");
			
		}
		
	}
	//prints contents of words;
	/*
	for(int i = 0; i < words_count; i++){
		printf("%d: %s\n", i, words[i]);
	}
	*/	
	
	//removes exclusion words
	char cur_word[EXCLUSION_WORD_LEN];
	int new_cur_words = words_count;

	for(int i = 0; i < words_count; i++){
		strncpy(cur_word, words[i], EXCLUSION_WORD_LEN);
		strncat(cur_word, "\n", 1);
		for(int j = 0; j < EXCLUSION_WORDS; j++){
			if(strncmp(cur_word, exclusion_words[j], EXCLUSION_WORDS) == 0){
				strncpy(words[i], "\0", 1); //updates exclusion word to blank string
				new_cur_words--; //decrements number of words
			}

		}
	}

	qsort(words, words_count, sizeof(char) * INPUT_LEN, backward_compare_str);
	qsort(words, new_cur_words, sizeof(char) * INPUT_LEN, forward_compare_str);

	words_count = new_cur_words; // sets words_count to new value after removing exclusion words
	
	//remove copies
	for(int i = 1; i < words_count; i++){
		if(strncmp(words[i], words[i-1], INPUT_LEN) == 0){
			strncpy(words[i - 1], "\0", 1);
			new_cur_words--;
		}
	}
	
		
	qsort(words, words_count, sizeof(char) * INPUT_LEN, backward_compare_str);
	qsort(words, new_cur_words, sizeof(char) * INPUT_LEN, forward_compare_str);
	words_count = new_cur_words;
	

	//FINAL STRETCH finds words in sentence array and prints them capitalized 
	for(int w = 0; w < words_count; w++){
		for(int s = 0; s < all_words_count; s++){
			//char sentence_list[INPUT_LEN][INPUT_LINES];
			//copy lines back into all_words2
			char cur_line[INPUT_LEN];
			strncpy(cur_line, sentence_ref[s], INPUT_LEN);
			//int num_words
			char *tok = strtok(cur_line, " ");
			while(tok != NULL){
				if(strncmp(tok, words[w], INPUT_LEN) == 0){
					print_and_cap(sentence_ref[s], words[w]);
					//call function to do printing
				}
				tok = strtok(NULL, " ");
			
			}	
		}
	}
	 
	//Tokenize all words in all_words and add to words then remove exclusion words and sort
	//Have a function thats checks if a word is in a line and capaltalizes and prints it if it does then deCAP
	//add duplicate removal
	return 0;	

}

void print_and_cap(char *line, char *word_to_cap){
	char cur_line[INPUT_LEN];
	strncpy(cur_line, line, INPUT_LEN);
	char *tok = strtok(cur_line, " ");
	while(tok != NULL){
		if(strncmp(tok, word_to_cap, INPUT_LEN) == 0){ //maybe chage the INPUT_LENGTH TO be less if theres an error
			int word_len = strlen(word_to_cap);
			for(int i = 0; i < word_len; i++){
				printf("%c", toupper(word_to_cap[i]));
			}
			//printf(" ");			
		}else{
			printf("%s", tok);
		}
		//printf(" ");			
		tok = strtok(NULL, " ");
		if(tok != NULL){
			printf(" ");	
		}		
			
	}
	printf("\n");
	
}

int forward_compare_str(const void *a, const void *b) {
	char *s1 = (char *)a;
	char *s2 = (char *)b;
	return strncmp(s1, s2, EXCLUSION_WORD_LEN);
}


int backward_compare_str(const void *a, const void *b) {
	char *s1 = (char *)a;
	char *s2 = (char *)b;
	return strncmp(s1, s2, EXCLUSION_WORD_LEN) * -1;
}




