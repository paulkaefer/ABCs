#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

// states for code execution
#define ADD 1
#define SUBTRACT 2
#define MULTIPLY 3
#define FUNCTION 4
#define JUMP 5
#define JUMP_Y 6
#define JUMP_N 7
#define BRANCH_0 8
#define BRANCH_1 9
#define WHILE 10

// borrows from good example at http://www.sanfoundry.com/c-program-implement-queue-functions/
struct node {
    int value;
    struct node *next;
    // bi-directional queue (a.k.a. linked list) to handle moving backwards
    // this is essentially inspired by the "tape" in Brainfuck
    struct node *prev;
} *head, *ptr, *tail;

void queueAdd(int value);
void queueDelete();

int main(int argc, char* argv[]) {

    // set default options
    int useLowercase = 1;
    int useLetterFile = 0;
    char* filename = NULL;
    char* letters = "abcdefghijklmnopqrstuvwxyz";
    char* version = "0.1";
    char* findCommand;
    int numCommand;

    // changed to 0 for help, version prints
    int interpretCode = 1;
    FILE *codeFile;
    char currentCommand = ' ';

    // setup values for executing code
    int accumulator = 0;
    int input = 0;
    int state = 0;

    // parse parser directives
    int iFlag;
    for(iFlag = 0; iFlag < argc; iFlag++) {
        // commands: -upper (-lower is default); -letterFile FILE -inputFile FILE <code file>
        // better: just pass string for letters (file maybe as an option)
        if ( !strcmp(argv[iFlag], "-upper") || !strcmp(argv[iFlag], "-u")) {
            printf("using upper case letters\n");
            letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            printf("%d\n",(int)strlen(letters));
        } else if ( !strcmp(argv[iFlag], "-letters") || !strcmp(argv[iFlag], "-l")) {
            char* newLetters = argv[iFlag + 1];
            iFlag++;
            if (26 == (int)strlen(newLetters)) {
                printf("New letters: %s\n",newLetters);
                letters = newLetters;
            } else {
                printf("Error: letters must have length of 26.\n");
            }
        } else if ( !strcmp(argv[iFlag], "-h") ) {
            printf("No help information yet!\n");
            interpretCode = 0;
        } else if ( !strcmp(argv[iFlag], "-v") ) {
            printf("ABCs, by Paul Kaefer\n");
            printf("Version %s\n",version);
            interpretCode = 0;
        } else {
            if ( (argc > 1) && (argc == iFlag + 1) ) {
                // end of arguments
                filename = argv[iFlag];
            }
        }
    }

    if (0 == interpretCode) {
        // ran with a terminal flag, like -h or -v
        exit(0);
    }

    if ( NULL == filename) {
        printf("Please specify a code file to interpret.\n");
        exit(0);
    } else {
        //printf("Running file %s\n",filename);
        codeFile = fopen(filename, "r");
    }

    while ( !feof(codeFile) ) {
        currentCommand = (char)fgetc(codeFile);
        findCommand = strchr(letters, currentCommand);
        if ( NULL != findCommand) {
            numCommand = findCommand - letters + 1;
            // else, ignore --> comment

         if ( state ) {
             switch ( state ) {
                 case ADD:
                     accumulator += numCommand;
                     break;
                 case SUBTRACT:
                     accumulator -= numCommand;
                     break;
                 case MULTIPLY:
                     accumulator *= numCommand;
                     break;
                 default:
                     printf("Unrecognized state %d.\n", state);
                     break;
             }
             state = 0;
         } else {
 
             switch ( numCommand ) {
                 case 1:
                     state = ADD;
                     break;
                 case 2:
                     state = SUBTRACT;
                     break;
                 case 3:
                     accumulator = 0;
                     break;
                 case 4:
                     queueDelete();
                     break;
                 case 5:
                     if ( DEBUG ) { 
                         printf("printing %d\n",accumulator);
                     }
 
                     printf("%c", 96+accumulator);
                     accumulator = 0;
                     break;
                 case 6:
                     state = FUNCTION;
                     break;
                 case 7:
                     break;
                 case 8:
                     printf("Paused -- hit ENTER to continue.");
                     getchar();
                     printf("\n");
                     break;
                 case 9:
                     input = getchar();
                     queueAdd( (int)input );
                     break;
                 case 10:
                     state = JUMP;
                     break;
                 case 11:
                     // redundant; handled in state switch statement
                     state = 0;
                     break;
                 case 12:
                     accumulator = ptr->value;
                     break;
                 case 13:
                     state = MULTIPLY;
                     break;
                 case 14:
                     ptr = ptr->next;
                     break;
                 case 15:
                     ptr = ptr->prev;
                     break;
                 case 16:
                     ptr = head;
                     break;
                 case 17:
                     printf("? ");
                     input = getchar();
                     while ( !( ('y' == input) || ('n' == input) ) ) {
                         printf("Please enter y or n: ");
                         input = getchar();
                     }
                     if ( 'y' == input ) {
                         state = JUMP_Y;
                     } else if ( 'n' == input ) {
                         state = JUMP_N;
                     } else {
                         printf("Invalid input to q query: %c\n", input);
                     }
                     break;
                 case 18:
                     // redundant; handled in state switch statement
                     state = 0;
                     break;
                 case 19:
                     // redundant; handled in state switch statement
                     state = 0;
                     break;
                 case 20:
                     if ( 0 == accumulator ) {
                         state = BRANCH_0;
                     } else if ( 1 == accumulator ){
                         state = BRANCH_1;
                     }
                     break;
                 case 21:
                     // redundant; handled in state switch statement
                     state = 0;
                     break;
                 case 22:
                     // redundant; handled in state switch statement
                     state = 0;
                     break;
                 case 23:
                     state = WHILE;
                     break;
                 case 24:
                     // redundant; handled in state switch statement
                     state = 0;
                     break;
                 case 25:
                     printf("%d\n", accumulator);
                     break;
                 case 26:
                     ptr->value = 0;
                     break;
                 default:
                     // "comment"
                     break;
             }
         }

         if ( DEBUG ) {
             printf("Command: %d, accumulator: %d\n", numCommand, accumulator);
         }

    
        }// end if (for valid commands)
    
    }// end while loop


    // closing stuff
    fclose(codeFile);
    return 0;
}

void queueAdd(int value) {
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = NULL;
    if ( NULL == tail ) {
        head = tail = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void queueDelete() {
    struct node *temp;
    temp = head;
    if ( NULL == head ) {
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
        free(temp);
    }
}

