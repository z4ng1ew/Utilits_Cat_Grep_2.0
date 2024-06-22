#include "s21_cat.h"
 
int main(int num_args, char* av[]) {
    Struct_singl_lett_opt single_letter_opt = {false};
    bool valid_flag = check_options(num_args, av, &single_letter_opt);
    if (valid_flag) {
        for (int i = optind; i < num_args; i++) {
            handle_file(single_letter_opt, av[i]);
        }
    }
    return !valid_flag;
}

bool check_options(int num_args, char* av[], Struct_singl_lett_opt* single_letter_opt) {
    bool valid_flag = true;
    int option, option_index = 0;
    while ((option = getopt_long(num_args, av, "beEnstTv", long_options, &option_index)) != -1 && valid_flag) {
        switch (option) {
            case 'b':
                single_letter_opt->fl_b = true;
                single_letter_opt->fl_n = false;
                break;
            case 'e':
                single_letter_opt->fl_e = true;
                single_letter_opt->fl_v = true;
                break;
            case 'E':
                single_letter_opt->fl_e = true;
                break;
            case 'n':
                single_letter_opt->fl_n = !single_letter_opt->fl_b;
                break;
            case 's':
                single_letter_opt->fl_s = true;
                break;
            case 't':
                single_letter_opt->fl_t = true;
                single_letter_opt->fl_v = true;
                break;
            case 'T':
                single_letter_opt->fl_t = true;
                break;
            case 'v':
                single_letter_opt->fl_v = true;
                break;
            default:
                valid_flag = false;
                break;
        }
    }
    if (!valid_flag) {
        fprintf(stderr, "Допустимые опции: -b, -e, -E, -v, -n, -s, -t, -T\n");
    }
    return valid_flag;
}

void handle_file(Struct_singl_lett_opt single_letter_opt, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        print_file_with_options(file, single_letter_opt);
        fclose(file);
    } else {
        fprintf(stderr, "Could not open the file: %s\n", filename);
    }
}

void process_current_character(int current_character, int *last_char, const Struct_singl_lett_opt single_letter_opt, int *counter_consecutive_empty_lines_s, int *number_current_lines_b_n) {
    if (current_character == '\n' && *last_char == '\n') {
        (*counter_consecutive_empty_lines_s)++;
    } else {
        *counter_consecutive_empty_lines_s = 0;
    }
    if (single_letter_opt.fl_s && *counter_consecutive_empty_lines_s > 1) return;

    if (*last_char == '\n' && (single_letter_opt.fl_n || (single_letter_opt.fl_b && current_character != '\n'))) {
        printf("%6d\t", ++(*number_current_lines_b_n));
    }
    if (single_letter_opt.fl_t && current_character == '\t') {
        printf("^");
        current_character += 64;
    }
    if (single_letter_opt.fl_e && current_character == '\n') {
        printf("$");
    }
    if (single_letter_opt.fl_v && current_character != '\t' && current_character != '\n') {
        if (current_character > 127) {
            printf("M-");
            current_character -= 128;
        }
        if (current_character < 32 || current_character == 127) {
            printf("^");
            current_character = (current_character == 127) ? current_character - 128 + 64 : current_character + 64;
        }
    }
    printf("%c", current_character);
    *last_char = current_character;
}

void print_file_with_options(FILE* file, const Struct_singl_lett_opt single_letter_opt) {
    static int current_character, last_char = '\n';
    static int counter_consecutive_empty_lines_s = 0, number_current_lines_b_n = 0;
    while ((current_character = fgetc(file)) != EOF) {
        process_current_character(current_character, &last_char, single_letter_opt, &counter_consecutive_empty_lines_s, &number_current_lines_b_n);
    }
}
