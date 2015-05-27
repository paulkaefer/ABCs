#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // set default options
    int useLowercase = 1;
    int useLetterFile = 0;
    char* filename = NULL;

    // parse parser directives
    int iFlag;
    for(iFlag = 0; iFlag < argc; iFlag++) {
        // commands: -upper (-lower is default); -letterFile FILE -inputFile FILE <code file>
        if (!strcmp(argv[iFlag], "-upper")) {
            printf("using upper case letters\n");
        } else {
            if (argc == iFlag + 1) {
                // end of arguments
                filename = argv[iFlag];
            }
        }
    }

    if ( NULL == filename) {
        printf("Please specify a code file to interpret.\n");
    } else {
        printf("Running file %s\n",filename);
    }

    return 0;
}
