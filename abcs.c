#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    // set default options
    int useLowercase = 1;
    int useLetterFile = 0;
    char* filename = NULL;
    char* letters = "abcdefghijklmnopqrstuvwxyz";
    char* version = "0.1";
    // changed to 0 for help, version prints
    int interpretCode = 1;
    FILE *codeFile;
    char currentCommand = ' ';

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
            if (argc == iFlag + 1) {
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
    } else {
        //printf("Running file %s\n",filename);
        codeFile = fopen(filename, "r");
    }

    while ( !feof(codeFile) ) {
        currentCommand = (char)fgetc(codeFile);
        char * findCommand = strchr(letters, currentCommand);
        if ( NULL != findCommand) {
            printf("%c -- findCommand: %lu\n", currentCommand, findCommand-letters+1);
        } else {
            printf("%c -- comment\n", currentCommand);
        }
        // find character in letters using strchr
        // if not in string, ignore
        // if in string, go through switch statement to determine how to handle it
    }

    // closing stuff
    fclose(codeFile);
    return 0;
}
