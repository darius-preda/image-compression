/*Preda Ionut Darius Teodor 313CB*/
#include "define.h"

int main(int argc, char *argv[]) {
    int flag;
    int factor_value = -1;
    char *input = NULL, *output = NULL;

    while ((flag = getopt(argc, argv, "c:1:2:d")) != -1 ) {
        switch(flag) {
            case 'c':
                if (optarg[0] == '1') {
                    factor_value = atoi(argv[optind]);
                    if (optind >= argc) {
                        printf("Input or output file missing\n");
                        break;
                    } else {
                        input = argv[optind + 1];
                        output = argv[optind + 2];
                    }
                    Task1(input, output, factor_value); //executa task1
                    break;
                }
                else if (optarg[0] == '2') {
                    factor_value = atoi(argv[optind]);
                    if (optind >= argc) {
                        printf("Input or output file missing\n");
                        break;
                    } else {
                        input = argv[optind + 1];
                        output = argv[optind + 2];
                    }
                    Task2(input, output, factor_value); //executa task2
                    break;
                }
            case 'd':
                if (optind >= argc) {
                    printf("Input or output file missing\n");
                    break;
                } else {
                    input = argv[optind];
                    output = argv[optind + 1];
                }
                Task3(input, output); //executa task3
                break;
        }
    }
    return 0;
}