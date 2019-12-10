#!/bin/bash

TESTS=()
while read line; do
	TESTS+=("$line")
done <teststrings.txt
i=0

if [ -f results.txt ]; then
	while [[ $CONFIRM != "y" && $CONFIRM != "n" ]]; do
		printf "\033[38;5;202mresults.txt already exists! overwrite?\n\033[0;0;00m"
		read CONFIRM
	done
	if [[ "$CONFIRM" == "n" ]]; then
		printf "\033[38;5;140mAborting!\n\033[0;0;00m"
		exit 1
	else
		printf "\033[38;5;140mOverwriting results.txt\n\033[0;0;00m"
		rm -f results.txt
	fi
fi
touch results.txt

for test in "${TESTS[@]}"; do
	i=$((i + 1))
	REAL=$(ls $test 2>realerror)
	FAKE=$(./ft_ls $test 2>fakeerror)
	if [[ "$REAL" != "$FAKE" ]]; then
		printf "}------------------------------------------------------------------------------{\n" >> results.txt
		printf "Test %i input: ft_ls %s\n\nOutput of ls:\n˜˜˜\n%s\n˜˜˜\nOutput of ft_ls:\n˜˜˜\n%s\n˜˜˜\n" $i "$test" "$REAL" "$FAKE" >> results.txt
		printf "\033[38;5;202mTEST %i FAILED!\n\033[38;5;140mdifference in output:\n\033[0;00m%s\n" $i "$(diff -du --label "ls output" --label "ft_ls output" <(echo "$REAL") <(echo "$FAKE"))"
		if [[ -n "$(cat realerror)" || -n "$(cat fakeerror)" ]] && [[ -n "$(diff realerror fakeerror)" ]]; then
			printf "\nError output of ls:\n˜˜˜\n%s\n˜˜˜\nError output of ft_ls:\n%s\n˜˜˜\n" "$(cat realerror)" "$(cat fakeerror)" >> results.txt
			printf "\033[38;5;202mTest %i - \033[38;5;140mdifference in error:\n\033[0;00m%s\n" $i "$(diff -du --label "ls output" --label "ft_ls output" realerror fakeerror)"
		fi
	else
		if [[ -n "$(cat realerror)" || -n "$(cat fakeerror)" ]] && [[ -n "$(diff realerror fakeerror)" ]]; then
			printf "}------------------------------------------------------------------------------{\n" >> results.txt
			printf "Test %i input: ft_ls %s\n\nError output of ls:\n˜˜˜\n%s\n˜˜˜\nError output of ft_ls:\n%s\n˜˜˜\n" $i "$test" "$(cat realerror)" "$(cat fakeerror)" >> results.txt
			printf "\033[38;5;202mTEST %i FAILED!\n\033[38;5;140mdifference in error:\n\033[0;00m%s\n" $i "$(diff -du --label "ls output" --label "ft_ls output" realerror fakeerror)"
		else
			printf "\033[38;5;140mTest $i \033[38;5;41msuccess! \033[38;5;140minput:\033[0;00m $test\n"
		fi
	fi
	rm -f realerror fakeerror
done
printf "\n\033[38;5;140mTests completed! for exact output of failed tests, see results.txt.\033[0;00m\n"
