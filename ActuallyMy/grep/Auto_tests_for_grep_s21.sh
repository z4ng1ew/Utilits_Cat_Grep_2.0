#!/bin/bash

Custom_utility="./s21_grep"
Default_utility="grep"

sample_filename='TEST-FILE'
suffix=".testing"

digit_pattern='[0-9]'
directory_test='./Files_for_tests/Sample_1'
grep_pattern='./Files_for_tests/reg_exp'

grep_opt=(
    "-e $digit_pattern -e $grep_pattern $directory_test"
    "-f $grep_pattern -e $digit_pattern $directory_test"
    "-f $grep_pattern s21_grep.c s21_grep.h"
    "-vf $grep_pattern $directory_test"
    "-cf $grep_pattern $directory_test"
    "-lf $grep_pattern $directory_test"
    "-nf $grep_pattern $directory_test"
    "-hf $grep_pattern $directory_test"
    "-h if $directory_test s21_grep.h"
    "-ie $digit_pattern $directory_test"
    "-ve $digit_pattern $directory_test"
    "-ce $digit_pattern $directory_test"
    "-le $digit_pattern $directory_test"
    "-ne $digit_pattern $directory_test"
    "-he $digit_pattern $directory_test"
    "-se $digit_pattern $directory_test"
    "-oe $digit_pattern $directory_test"
    "-iv $digit_pattern $directory_test"
    "-ic $digit_pattern $directory_test"
    "-il $digit_pattern $directory_test"
    "-in $digit_pattern $directory_test"
    "-ih $digit_pattern $directory_test"
    "-is $digit_pattern $directory_test"
    "-io $digit_pattern $directory_test"
    "-vc $digit_pattern $directory_test"
    "-vl $digit_pattern $directory_test"
    "-vn $digit_pattern $directory_test"
    "-vh $digit_pattern $directory_test"
    "-vs $digit_pattern $directory_test"
    "-vo $digit_pattern $directory_test"
    "-cl $digit_pattern $directory_test"
    "-cn $digit_pattern $directory_test"
    "-ch $digit_pattern $directory_test"
    "-cs $digit_pattern $directory_test"
    "-co $digit_pattern $directory_test"
    "-ln $digit_pattern $directory_test"
    "-lh $digit_pattern $directory_test"
    "-ls $digit_pattern $directory_test"
    "-lo $digit_pattern $directory_test"
    "-nh $digit_pattern $directory_test"
    "-ns $digit_pattern $directory_test"
    "-no $digit_pattern $directory_test"
    "-hs $digit_pattern $directory_test"
    "-ho $digit_pattern $directory_test"
    "-l $digit_pattern $directory_test"
    "-v $digit_pattern $directory_test"
    "-c $digit_pattern $directory_test"
    "-n $digit_pattern $directory_test"
    "-o $digit_pattern $directory_test"
    "[0-9] $directory_test"
    "-i RY $directory_test"
)

check_file_similarity() {
    local file_a="$1"
    local file_b="$2"
    local diff_output=$(diff -u "$file_a" "$file_b")

    if [ "$?" -ne 0 ]; then
        local line=$(echo "$diff_output" | grep -n '^-' | head -n 1 | cut -d ':' -f 1)
        local char=$(echo "$diff_output" | grep -n '^-' | head -n 1 | awk '{print length($0)}')

        echo "*************** Difference Found ***************"
        echo "File A:"
        echo "$diff_output" | head -n "$line"
        echo "-------------------------------------------------"
        echo "File B:"
        echo "$diff_output" | tail -n +$((line+1))
        echo "-------------------------------------------------"
        echo "Difference at Line: $line, Char: $char"
        read -p "Press any key to continue:" -n1 -s
        return 1
    else
        echo -e "\033[45m\033[1m OK \033[0m"
        return 0
    fi
}

run_utility() {
    local utility=$1
    local flags="$2"
    local output_file="$3"

    eval "$utility $flags > $output_file"
}

total_tests=${#grep_opt[@]}
successful_tests=0
failed_tests=0

for index in "${!grep_opt[@]}"; do
    echo -n "Checking: $(($index + 1)) from $total_tests. Option: ${grep_opt[$index]} : "
    
    run_utility "$Custom_utility" "${grep_opt[$index]}" "${sample_filename}-0${suffix}"
    run_utility "$Default_utility" "${grep_opt[$index]}" "${sample_filename}-1${suffix}"
    
    check_file_similarity "${sample_filename}-0${suffix}" "${sample_filename}-1${suffix}"
    if [ $? -eq 0 ]; then
        ((successful_tests++))
        echo -e "\033[32mTest Passed\033[0m"
    else
        ((failed_tests++))
        echo -e "\033[31mTest Failed\033[0m"
    fi
done

echo "╔═══════════════════════════════╗"
echo "║ Total tests executed: $total_tests      ║"
echo "║ Successful tests:     $successful_tests      ║"
echo "║ Failed tests:         $failed_tests       ║"
echo "╚═══════════════════════════════╝"

rm -rf *"${suffix}"

