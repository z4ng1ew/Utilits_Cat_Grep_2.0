
#include "s21_cat.h"

int main(int num_comd_line_arg, char* array_strings_comd[]) {
    Opt short_opt = {false};
    bool error_opt = verify_options(num_comd_line_arg, array_strings_comd, &short_opt);

    if (error_opt) {
        for (int i = optind; i < num_comd_line_arg; i++) {
            open_and_read_file(short_opt, array_strings_comd[i]);
        }
    }

    return !error_opt;
}

bool verify_options(int num_comd_line_arg, char* array_strings_comd[], Opt* short_opt) {
    bool error_opt = true;
    int option, option_index = 0;

    while ((option = getopt_long(num_comd_line_arg, array_strings_comd, "beEnstTv", long_options, &option_index)) != -1 && error_opt) {
        switch (option) {
            case 'b':
                short_opt->b = true;
                short_opt->n = false;
                break;
            case 'e':
                short_opt->e = true;
                short_opt->v = true;
                break;
            case 'E':
                short_opt->e = true;
                break;
            case 'n':
                short_opt->n = !short_opt->b;
                break;
            case 's':
                short_opt->s = true;
                break;
            case 't':
                short_opt->t = true;
                short_opt->v = true;
                break;
            case 'T':
                short_opt->t = true;
                break;
            case 'v':
                short_opt->v = true;
                break;
            default:
                error_opt = false;
                break;
        }
    }

    if (!error_opt) {
        fprintf(stderr, "Возможно использование только следующих опций: -b -e -E -v -n -s -t -T\n");
    }

    return error_opt;
}

void open_and_read_file(const Opt short_opt, const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file != NULL) {
        display_file_with_flags(file, short_opt);
        fclose(file);
    } else {
        fprintf(stderr, "Could not open the file: %s\n", filename);
    }
}

void display_file_with_flags(FILE* file, const Opt short_opt) {
    int current_character, last_char = '\n';
    int counter_consecutive_empty_lines_s = 0, number_current_lines_b_n = 0;

    while ((current_character = fgetc(file)) != EOF) {
        if (current_character == '\n' && last_char == '\n') {
            counter_consecutive_empty_lines_s++;
        } else {
            counter_consecutive_empty_lines_s = 0;
        }

        if (short_opt.s && counter_consecutive_empty_lines_s > 1) continue;

        if (last_char == '\n' && (short_opt.n || (short_opt.b && current_character != '\n')))
            printf("%6d\t", ++number_current_lines_b_n);

        switch (current_character) {
            case '\t':
                if (short_opt.t) {
                    printf("^I");
                } else {
                    putchar(current_character);
                }
                break;
            case '\n':
                if (short_opt.e) {
                    printf("$");
                }
                putchar(current_character);
                break;
            default:
                if (short_opt.v && (current_character < 32 || current_character == 127 || current_character > 127)) {
                    if (current_character > 127) {
                        printf("M-");
                        current_character -= 128;
                    }
                    if (current_character < 32 || current_character == 127) {
                        printf("^");
                        current_character = (current_character == 127) ? '?' : (current_character + '@');
                    }
                }
                putchar(current_character);
                break;
        }
        last_char = current_character;
    }
}