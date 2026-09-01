#!/usr/bin/bash

# section (A) answer
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo "Point (A)"
echo
grep '^S' employees.txt && grep '^s' employees.txt

# section (B) answer
echo
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo "Point (B)"
echo
grep 'HR' employees.txt

# section (C) answer
echo
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo "Point (C)"
echo
grep -i 'HR' employees.txt
