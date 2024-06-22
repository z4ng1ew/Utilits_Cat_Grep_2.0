#!/bin/bash
temp_dir="temp_test_files"
CustomCat="./s21_cat"
Default_utilit="cat"
checked_file=('Files_for_tests/Sample_2')

Opt=(
    '-b' '-e' '-n' '-s' '-v' '-t' '-T' '-E'
    '--number-nonblank' '--number' '--squeeze-blank'
)

mkdir -p "$temp_dir"

create_flag_combinations() {
    local n=${#Opt[@]}
    local max_flags=3  
    for ((i = 0; i < n; i++)); do
        for ((j = i; j < n && j < i + max_flags; j++)); do
            for ((k = j; k < n && k < j + max_flags; k++)); do
                echo "${Opt[i]} ${Opt[j]} ${Opt[k]}"
            done
        done
    done
}

all_var=($(create_flag_combinations))

success_count=0
failure_count=0

file_comparison() {
    local a="$1"
    local b="$2"

    if ! diff "$a" "$b" > /dev/null; then
        echo "*** Differences Found ***"
        echo "File A:"
        cat "$a"
        echo "File B:"
        cat "$b"
        ((failure_count++))
    else
        echo -n -e "\033[48;5;129m\033[1m OK \033[0m" # Зеленый фон и жирный текст
        ((success_count++))
    fi
}


for test in "${!all_var[@]}"; do

    cur_flags="${all_var[$test]}"
    shuffled_suite=("${checked_file[@]}")
    shuffled_suite=( $(shuf -e "${shuffled_suite[@]}") )

    if [[ $cur_flags == *" -z"* ]]; then
        echo "Skipping invalid combination: $cur_flags"
        continue
    fi

    echo -n "Checking $((test + 1)) from ${#all_var[@]}. Option name: $cur_flags. Result: "

   
    for i in 0 1; do
        if [[ $i -eq 0 ]]; then
            func="$CustomCat"
        else
            func="$Default_utilit"
        fi
        m_str="$func $cur_flags ${shuffled_suite[*]} > ${temp_dir}/TEST-FILE-${i}"
        echo "$m_str" >> commands.testing
        eval "$m_str" &
    done


    wait

    file_comparison "${temp_dir}/TEST-FILE-0" "${temp_dir}/TEST-FILE-1"
    echo  
done

total_tests=$((success_count + failure_count))

echo -e "\n╔════════════════════════════════════════════════╗"
echo -e "║                Test Summary                    ║"
echo -e "╠════════════════════════════════════════════════╣"
echo -e "║ Total tests executed:       $total_tests                ║"
echo -e "║ Number of successful tests: $success_count                ║"
echo -e "║ Number of failed tests:     $failure_count                  ║"
echo -e "╚════════════════════════════════════════════════╝"

rm -rf "$temp_dir"
