#!/bin/bash

TESTS=()
while read line; do
	TESTS+=("$line")
done <test_files/teststrings.txt
i=0
failed=0

if [ -f testresults.txt ]; then
	if [[ "$1" == "-y" ]]; then
		CONFIRM="y"
	fi
	while [[ $CONFIRM != "y" && $CONFIRM != "n" ]]; do
		printf "\033[38;5;215mtestresults.txt already exists! overwrite?\033[0;0;00m y/n\n"
		read CONFIRM
	done
	if [[ "$CONFIRM" == "n" ]]; then
		printf "\033[38;5;140mAborting!\n\033[0;0;00m"
		exit 1
	fi
fi

for test in "${TESTS[@]}"; do
	i=$((i + 1))
	REAL=$(ls -1 $test 2>realerror)
	FAKE=$(./ft_ls $test 2>fakeerror)
	FAKEERROR=$(cat fakeerror)
	FAKEERROR="${FAKEERROR//ft_ls/ls}"
	echo "${FAKEERROR//Ralrt/ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1}" > fakeerror_temp
	if grep -q -E "([r-][w-][xsS-]){2}[r-][w-][-xtT][@+]" <<< "$REAL"; then
		printf "replacing @ and + ACL signs for test %i!\n" $i
		REAL=$(sed -E "s/(([r-][w-][xsS-]){2}[r-][w-][-xtT])[@+]/\1 /g" <<< "$REAL")
	fi
	if [[ "$REAL" != "$FAKE" ]]; then
		if [ -f testresults.txt ] && [[ "$failed" == "0" ]]; then
			echo "" > testresults.txt
			printf "\033[38;5;215mOverwriting testresults.txt\n\033[0;0;00m"
		fi
		failed=$((failed + 1))
		printf "}------------------------------------------------------------------------------{\n" >> testresults.txt
		printf "Test %3i input: ft_ls %s\n\nOutput of ls:\n~~~~~~\n%s\n~~~~~~\nOutput of ft_ls:\n~~~~~~\n%s\n~~~~~~\n" $i "$test" "$REAL" "$FAKE" >> testresults.txt
		printf "\033[38;5;202mTEST %3i FAILED!  \033[38;5;140mInput:\033[0;00m %s\n\033[38;5;140mdifference in output:\n\033[0;00m%s\n" $i "$test" "$(diff -du --label "ls output" --label "ft_ls output" <(echo "$REAL") <(echo "$FAKE"))"
		if [[ -n "$(cat realerror)" || -n "$(cat fakeerror_temp)" ]] && [[ -n "$(diff realerror fakeerror_temp)" ]]; then
			printf "\nError output of ls:\n~~~~~~\n%s\n~~~~~~\nError output of ft_ls:\n%s\n~~~~~~\n" "$(cat realerror)" "$(cat fakeerror_temp)" >> testresults.txt
			printf "\033[38;5;202mTest %3i - \033[38;5;140mdifference in error:\n\033[0;00m%s\n" $i "$(diff -du --label "ls output" --label "ft_ls output" realerror fakeerror)"
		fi
	else
		if [[ -n "$(cat realerror)" || -n "$(cat fakeerror_temp)" ]] && [[ -n "$(diff realerror fakeerror_temp)" ]]; then
			if [ -f testresults.txt ] && [[ "$failed" == "0" ]]; then
				echo "" > testresults.txt
				printf "\033[38;5;215mOverwriting testresults.txt\n\033[0;0;00m"
			fi
			failed=$((failed + 1))
			printf "}------------------------------------------------------------------------------{\n" >> testresults.txt
			printf "Test %3i input: ft_ls %s\n\nError output of ls:\n~~~~~~\n%s\n~~~~~~\nError output of ft_ls:\n%s\n~~~~~~\n" $i "$test" "$(cat realerror)" "$(cat fakeerror)" >> testresults.txt
			printf "\033[38;5;202mTEST %3i FAILED!  \033[38;5;140mInput:\033[0;00m %s\n\033[38;5;140mdifference in error:\n\033[0;00m%s\n" $i "$test" "$(diff -du --label "ls output" --label "ft_ls output" realerror fakeerror_temp)"
		else
			printf "\033[38;5;140mTest %3i \033[38;5;41msuccess!\033[38;5;140m Input:\033[0;00m %s\n" $i "$test"
		fi
	fi
done
rm -f realerror fakeerror fakeerror_temp
if [[ "$failed" != "0" ]]; then
	printf "\n\033[38;5;140mTests completed, \033[38;5;202mfailed %i out of %i tests.\033[38;5;140m for exact output of failed tests, see testresults.txt.\033[0;00m\n" $failed $i
	exit 1
else
	printf "\n\033[38;5;140mTests completed,\033[38;5;41m all %i tests passed!\033[0;00m\n" $i
	exit 0
fi
