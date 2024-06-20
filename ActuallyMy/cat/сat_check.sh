#!/bin/bash

MyUtilit="./s21_cat"
LinuxUtilit="cat"

file='TEST-FILE'
file_extense=".testing"

suite=('Cases/Input_case_2')

flags=(
    '-b' '-e' '-n' '-s' '-v' '-t' '-T' '-E'
    '--number-nonblank' '--number' '--squeeze-blank'
)

generate_combinations() {
    local n=${#flags[@]}
    for ((i = 0; i < n; i++)); do
        for ((j = i; j < n; j++)); do
            for ((k = j; k < n; k++)); do
                for ((l = k; l < n; l++)); do
                    for ((m = l; m < n; m++)); do
                        for ((o = m; o < n; o++)); do
                            echo "${flags[i]} ${flags[j]} ${flags[k]} ${flags[l]} ${flags[m]} ${flags[o]}"
                        done
                    done
                done
            done
        done
    done
}

all_var=($(generate_combinations))

success_count=0
failure_count=0

file_comparison() {
    local a="$1"
    local b="$2"

    if ! diff "$a" "$b" >/dev/null; then
        echo "===============A==============="
        cat "$a"
        echo "===============B==============="
        cat "$b"
        echo "==============================="
        failure_count=$((failure_count + 1))
    else
        echo -e "\033[42m\033[1m SUCCESS \033[0m"
        success_count=$((success_count + 1))
    fi
}

for test in "${!all_var[@]}"; do
    if ((test >= 462)); then
        break
    fi

    cur_flags="${all_var[$test]}"
    shuffled_suite=("${suite[@]}")
    shuffled_suite=( $(shuf -e "${shuffled_suite[@]}") )


    if [[ $cur_flags == *" -z"* ]]; then
        echo "Skipping invalid combination: $cur_flags"
        continue
    fi

    echo "Current TEST [$((test + 1)) ----- 462] - "
    for i in 0 1; do
        if [[ $i -eq 0 ]]; then
            func="$MyUtilit"
        else
            func="$LinuxUtilit"
        fi
        m_str="$func $cur_flags ${shuffled_suite[*]} > ${file}-${i}${file_extense}"
        echo "$m_str" >> commands.testing
        eval "$m_str"
    done
    file_comparison "${file}-0${file_extense}" "${file}-1${file_extense}"
done

total_tests=$((success_count + failure_count))
echo -e "\nTotal tests: $total_tests"
echo "Successful tests: $success_count"
echo "Failed tests: $failure_count"

rm -rf *"${file_extense}"

