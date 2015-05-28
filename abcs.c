#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// states for code execution
#define ADD 1
#define SUBTRACT 2
#define MULTIPLY 3

// borrows from good example at http://www.sanfoundry.com/c-program-implement-queue-functions/
struct node {
    int value;
    struct node *next;
} *front, *rear;

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
        }
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
                    break;
                default:
                    break;
            }
        }
    }

    // closing stuff
    fclose(codeFile);
    return 0;
}

void queueAdd(int value) {
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->value = value;
    temp->next = NULL;
    if ( NULL == rear ) {
        front = rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
    }
}

void queueDelete() {
    struct node *temp;
    temp = front;
    if ( NULL == front ) {
        front = rear = NULL;
    } else {
        front = front->next;
        free(temp);
    }
}

