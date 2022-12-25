/*
 * concord3.c
 *
 * Starter file provided to students for Assignment #3, SENG 265,
 * Fall 2022.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "seng265-list.h"
#include <ctype.h>

#define EX_WORD_LEN 40 //max length for exclusion word plus \0
#define INPUT_LINE_LEN 100 // max length of a line of input plus \0
#define DEFAULT_SIZE 10 // default size of head pointer array

void print_word(node_t *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->text);
}


#ifdef DEBUG

/*
 * Just showing the use of the linked-list routines.
 */

void _demo() {
printf("DEBUG: in _demo\n");
    char *words_german[] = {"Der", "Kater", "mit", "Hut."};
    int   words_german_len = 4;

    char *words_english[] = {"The", "cat", "in", "the", "hat."};
    int   words_english_len = 5;

    node_t *temp_node = NULL;
    node_t *head = NULL;

    int i;

    /* Add the words in German, at the front. */
    for (i = 0; i < words_german_len; i++) {
        temp_node = new_node(words_german[i]);
        head = add_front(head, temp_node);
    }

    /* Add the words in English, at the end. */
    for (i = 0; i < words_english_len; i++) {
        temp_node = new_node(words_english[i]);
        head = add_end(head, temp_node);
    }

    /* Print the list of words. */

    apply(head, print_word, "--> %s");

    /* Free up the memory. This is done rather deliberately
     * and manually.  Asserts are liberally used here as they
     * express state that *must* be true if all of the code is
     * correctly working.
     */

    temp_node = head;
    while (temp_node != NULL) {
        assert(temp_node != NULL);
        head = remove_front(head);
        free(temp_node);
        temp_node = head;
    }
   
    assert(head == NULL); 
}

#endif

//reads exclusion words into a linked list and returns the head
node_t *read_exwords(){
	char buffer[EX_WORD_LEN + 1];
	fgets(buffer, EX_WORD_LEN, stdin);
	if(strncmp(buffer, "1\n", EX_WORD_LEN) == 0){
		printf("Input is version 1, concord3 expected version 2\n");
		exit(1);
	}
	
	node_t *head = NULL;
	node_t *node = NULL;

	fgets(buffer, EX_WORD_LEN, stdin); // gets rid of the ''''
	for(fgets(buffer, EX_WORD_LEN, stdin); strncmp(buffer, "\"\"\"\"\n", EX_WORD_LEN); fgets(buffer, EX_WORD_LEN, stdin)){
		buffer[strlen(buffer) - 1] = '\0'; //removes the new line character
		node = new_node(buffer);
		head = add_end(head, node);
	}
	return head;
	
}

//reads all the lines and stores them into an array of linked lists and stores the size into the integer passed
node_t **read_lines(int *num_lines){
	char buffer[INPUT_LINE_LEN];
	
	node_t *head = NULL;
	node_t *node = NULL;
	char *token = NULL;
	int index = 0;
	int max_size = DEFAULT_SIZE;
	node_t **words_array = (node_t **)emalloc(sizeof(node_t**) * DEFAULT_SIZE);

	while(fgets(buffer, INPUT_LINE_LEN, stdin) != NULL){
		head = NULL;
		buffer[strlen(buffer) - 1] = '\0';
		token = strtok(buffer, " ");
		while(token != NULL){
			node = new_node(token);
			head = add_end(head, node);
			token = strtok(NULL, " ");
		}
		words_array[index] = head;
		index++;
		if(index == max_size){
			max_size *= 2;
			words_array = (node_t **)realloc(words_array, sizeof(node_t**) * max_size); 
		}
	}

	//wont know size number of lines
	*num_lines = index; 
	return words_array;
}

//frees a list given the head pointer
void free_list(node_t *head){
	node_t *cur = head;
	while(head != NULL){
		cur = head;
		head = head->next;
		free(cur);
	}
}

//got from lab 8 part A but added some additional functionality
//this function adds a node to a list in order but ignores it if its a duplicate
node_t *add_inorder(node_t * list, node_t *new) {
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL) {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
	//doesnt add if its a duplicate
        if (strcasecmp(new->text, curr->text) == 0) {
		free(new);
		return list;
	}	
        if (strcasecmp(new->text, curr->text) > 0) {
	    prev = curr;
        } else {
            break;
        }
    }

    new->next = curr;

    if (prev == NULL) {
        return (new);
    } else {
        prev->next = new;
        return list;
    }
}

//makes a list of all non exclusion words sorted and returns the resulting list
node_t *make_word_list(node_t **words_array, node_t *ex_words, int num_lines){
	node_t *head = NULL;
	node_t *cur_list = NULL;
	node_t *cur = NULL;
	node_t *ex_words_cur = NULL;
	int add_node = 1;
	for(int i = 0; i < num_lines; i++){
		cur_list = words_array[i];
		cur = cur_list;
		while(cur != NULL){
			ex_words_cur = ex_words;
			while(ex_words_cur != NULL){
				if(strcasecmp(cur->text, ex_words_cur->text) == 0){
					add_node = 0;
				}
				ex_words_cur = ex_words_cur->next;
			}
			if(add_node){
				head = add_inorder(head, new_node(cur->text));
			}
			add_node = 1;
			cur = cur->next;
		}
	}
	return head;
	
}

//function that takes words list and word that needs to be capitalized and prints that line with proper formatting
void print_line(node_t *line, char* word){
	node_t *cur = line;
	node_t *front_p = line;
	int before_sum = 0;
	node_t *back_p = NULL;
	int after_sum = 0;
	
	//first two loops get a pointer at the node to start printing at
	while(strcasecmp(cur->text, word) != 0){
		before_sum += strlen(cur->text) + 1; //plus 1 for space maybe not needed
		cur = cur->next;
	}

	while(before_sum > 20){
		before_sum = before_sum - strlen(front_p->text) - 1;
		front_p = front_p->next;
	}
	
	//this loop find the last node that should be printed
	back_p = cur;
	while(back_p != NULL){
		after_sum += strlen(back_p->text) + 1;
		
		if(after_sum > 32){
			
			break;
		}
		back_p = back_p->next;
		
	}

	//prints out the correct number of spaces
	for(int i = 0; i < 29 - before_sum; i++){
		printf(" ");
	}

	//prints out all the words with the appropriate ones capitalised
	while(front_p != back_p){
		if(strcasecmp(front_p->text, word) == 0){
			for(int i = 0; i < strlen(word); i++){
				printf("%c", toupper(word[i]));
			}
		}else{
			printf("%s", front_p->text);
		}

		if(front_p->next != back_p){
			printf(" ");
		}

		front_p = front_p->next;
	}
	
	printf("\n");

}

//find each sentence that goes with the each word of the sorted words list and passes them to another function
//to get printed properly
void find_line_and_word(node_t **words_array, node_t *words_list, int size){
	node_t *cur_s = NULL;
	node_t *cur_w = words_list;
	node_t *cur_list = NULL;
	while(cur_w != NULL){
	//nest up
		for(int i = 0; i < size; i++){
			cur_list = words_array[i];
			cur_s = cur_list;
			while(cur_s != NULL){
				if(strcasecmp(cur_s->text, cur_w->text) == 0){
					print_line(cur_list, cur_w->text);
				}
				cur_s = cur_s->next;
			}
		}
	cur_w = cur_w->next;
	}
	//done nest up
}

//the main function that calls all the other functions
int main(int argc, char *argv[])
{
	node_t *ex_words = read_exwords();
	
	int num_lines = 0;	
	node_t **all_words = read_lines(&num_lines);
	for(int j = 0; j < num_lines; j++){
	}
	
	node_t *clean_words = make_word_list(all_words, ex_words, num_lines);	
	
	find_line_and_word(all_words, clean_words, num_lines);

	//frees all memory
	free_list(ex_words);
	for(int j = 0; j < num_lines; j++){
		free_list(all_words[j]);
	}
	
	free(all_words);
	free_list(clean_words);

/* 
 * Showing some simple usage of the linked-list routines.
 */

#ifdef DEBUG
   // _demo();
#endif

    exit(0);
}
