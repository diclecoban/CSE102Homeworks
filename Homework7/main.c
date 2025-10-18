#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WORD_COUNT 136000
#define MAX_WORD_SIZE 13
#define VECTOR_SIZE 200
#define MAX_DICT_SIZE 1001

int read_text(const char * input_file, const char * ignore_file, char words[MAX_WORD_COUNT][MAX_WORD_SIZE]);
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]);
int vector_dict(const char *file_name, double vectors[MAX_DICT_SIZE][VECTOR_SIZE]);

int main()
{
    char words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    const char *input_file = "input.txt";
    const char *ignore_file = "ignore.txt";
    const char *file_name = "dictionary.txt";
    int word_counter = 0;
    char kelime[MAX_WORD_SIZE] = "";
    char dict[MAX_WORD_COUNT][MAX_WORD_SIZE];

    printf("Please enter your word(s): ");
    scanf("%s", kelime);

    for (int i = 0; i < strlen(kelime); ++i)
    {
        if (kelime[i] == ' ')
        {
            ++word_counter;
        }
    }

    if (word_counter > 1)
    {
        // Handle the case where multiple words are entered.
    }
    else
    {
        int num_words = read_text(input_file, ignore_file, words);
        
        int count = 0;
        
        for (int j = 0; j< num_words; ++j)
        {
            
            if (strcmp(words[j], kelime) == 0)
            {
                count++;
            }
        }
        
        if(count != 0)
        {
            printf("The word %s has %d times in the input.txt file\n",kelime, count);
        }
        else
        {
          int kelime_sayisi = read_dict(file_name,dict);
            
            int word_found = 0;
            int line_num = -1;
            for (int i = 0; i < num_words; ++i)
            {
                if (strcmp(kelime, dict[i]) == 0)
                {
                    word_found = 1;
                    line_num = i ;  // Line numbers start from 0
                    break;
                }
            }
            
            if (word_found)
            {
                double vectors[MAX_DICT_SIZE][VECTOR_SIZE];
                double temp=0;
                double sum=0;
                          
                vector_dict(file_name,vectors);
                
                double min_distance = 40; // initialize to a very large number
                int min_index = -1; // initialize to an invalid index

                for (int i = 0; i < 1001; ++i)
                {
                    if (i == line_num)
                    {
                        // skip comparing a word to itself
                        continue;
                    }
                    
                    double distance = 0;
                    for (int j = 0; j < 200; ++j)
                    {
                    double diff = vectors[line_num][j] - vectors[i][j];
                      distance += diff * diff;
    
                    }
                    distance = sqrt(distance);
                    
                    if (distance < min_distance)
                    {
                        min_distance = distance;
                        min_index = i;
                    }
                }

                if (min_index != -1)
                {
                    printf("The word %s's closest word is %s, with distance %f\n", kelime, dict[min_index], min_distance);
                }
                else
                 {
                     printf("No matches of \"%s\" \n", kelime);
                 }
            }
           else
            {
                printf("No matches of \"%s\" \n", kelime);
            }
        }
    }
        return 0;
}

int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE])
{
   int words=0;
   int character;
    
   FILE *dictionary = fopen(file_name,"r");
    
   if( dictionary == NULL)
   {
       printf("Warning! The file is empty! Please try again.\n");
       return -1;
   }
    
    character = fgetc(dictionary);
    
   while ((character = fgetc(dictionary)) != EOF)
   {
       fscanf(dictionary,"%s",dict[words]);
       
           if(character == '\n')
           {
               words++;
           }
   }
    
   dict[words-1][0] = '-';
    
   dict[words-1][1] = '\0';
    
   fclose(dictionary);
    
   return words;
}

int read_text(const char *input_file, const char *ignore_file, char words[][MAX_WORD_SIZE])
{
    // Open the text file
    FILE *text = fopen(input_file, "r");
    if (text == NULL)
    {
        printf("Error: could not open text file\n");
        return -1;
    }

    // Open the ignore file
    FILE *ignore = fopen(ignore_file, "r");
    if (ignore == NULL)
    {
        printf("Error: could not open ignore file\n");
        fclose(text);
        return -1;
    }

    // Read ignored words into an array
    char ignored_words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    int num_ignored_words = 0;
    char buffer[MAX_WORD_SIZE];
    while (fscanf(ignore, "%99s", buffer) == 1)
    {
        strcpy(ignored_words[num_ignored_words], buffer);
        num_ignored_words++;
    }
    fclose(ignore);

    // Read words from text file into an array
    int num_words = 0;
    while (fscanf(text, "%99s", buffer) == 1)
    {
        // Check if word is ignored
        int is_ignored = 0;
        for (int i = 0; i < num_ignored_words; i++)
        {
            if (strcmp(buffer, ignored_words[i]) == 0)
            {
                is_ignored = 1;
                break;
            }
        }
        if (!is_ignored)
        {
            strcpy(words[num_words], buffer);
            num_words++;
        }
        if (num_words >= MAX_WORD_COUNT)
        {
            printf("Error: too many words in text file\n");
            break;
        }
    }
    fclose(text);

    // Print the remaining words in the array
 /*   for (int i = 0; i < num_words; i++) {
        printf("%s ", words[i]);
    }
    printf("\n"); */
    return num_words;
}


int copyStr(char *dest, char dict[][MAX_WORD_SIZE],int position)
{
    int i = 0;
    while(dest[i] != '\0'){
        dict[position][i] = dest[i];
        i++;
    }
    dict[position][i] = '\0';
    return i;
}


int vector_dict(const char *file_name, double vectors[MAX_DICT_SIZE][VECTOR_SIZE])
{
    
   FILE *dictionary = fopen(file_name, "r");

        if(dictionary == NULL)
        {
            printf("Warning! The file is empty.\n");
            return -1;
        }

        // skip the first line
        int c;
        while((c = fgetc(dictionary)) != EOF)
        {
            if(c == '\n')
            {
                break;
            }
        }

        int row = 0;

        while(!feof(dictionary) && row < MAX_DICT_SIZE)
        {
            char word[MAX_WORD_SIZE];
            
            if(fscanf(dictionary, "%s", word) == 1)
            {
                for(int j = 0; j < VECTOR_SIZE; ++j)
                {
                    if(fscanf(dictionary, "%lf", &vectors[row][j]) != 1)
                    {
                        printf("Error reading vectors for word '%s'\n", word);
                        break;
                    }
                }
                row++;
            }
        }

        fclose(dictionary);

        // print the contents of the vectors array
     /*   for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < VECTOR_SIZE; j++)
            {
                printf("%lf ", vectors[i][j]);
            }
            printf("\n");
        } */
    
    return 0;
    
}



