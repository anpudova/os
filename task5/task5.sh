#!/bin/bash

RED='\e[31m'
GREEN='\e[32m'
RESET='\e[0m'

declare -i step=1
declare -i hit=0
declare -i miss=0
declare -i total_attempts=0
declare -i correct_attempts=0
declare -a numbers=()

while :
do
    random_number=${RANDOM: -1}

    echo -e "Step: ${step}"
    
    read -p "Please enter number from 0 to 9 (q - quit): " user_input

    if [[ "${user_input}" == "q" ]]; then
        echo -e "Exit.."
        exit 0
    fi

    if [[ "${user_input}" =~ ^[0-9]$ ]]; then
        total_attempts+=1

        if [[ "${user_input}" -eq "${random_number}" ]]; then
            echo -e "Hit! My number: ${random_number}"
            hit+=1
            correct_attempts+=1
            number_string="${GREEN}${random_number}${RESET}"
        else
            echo -e "Miss! My number: ${random_number}"
            miss+=1
            number_string="${RED}${random_number}${RESET}"
        fi

        hit_percent=$((hit * 100 / total_attempts))
        miss_percent=$((100 - hit_percent))

        numbers+=("${number_string}")
        if [[ ${#numbers[@]} -gt 10 ]]; then
            numbers=("${numbers[@]:1}")
        fi

        echo -e "Hit: ${hit_percent}% Miss: ${miss_percent}%"
        echo -e "Numbers: ${numbers[@]}"
    else
        echo -e "Not a valid input. Repeat."
    fi

    step+=1
done
    numbers+=("${input}")

    counter+=1
done
