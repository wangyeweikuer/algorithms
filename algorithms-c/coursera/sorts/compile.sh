#! /bin/bash
if [[ $# = 0 ]]
then
	echo "No any input file!"
	exit 1
fi

indent -kr -i8 *.[ch] --line-length120
find . -name "*~" | xargs rm -f
ctags -R
all=""
for a in $@
do
	if [[ ! $a =~ .*.~ ]]
	then
		all="$all $a"
	fi
done
gcc -std=c99 -o a.out -ggdb $all
#g++ -o a.out -ggdb $all

