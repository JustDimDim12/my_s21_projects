#!/bin/sh

mkdir -p outputs

./grep/s21_grep "Hello" texts/hello.txt > outputs/1.txt
grep "Hello" texts/hello.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: "Hello" texts/hello.txt"
else
    echo "FAIL: "Hello" texts/hello.txt"
    diff outputs/1.txt outputs/2.txt
fi

./grep/s21_grep -e "I" -e "Fine" texts/hope.txt > outputs/1.txt
grep -e "I" -e "Fine" texts/hope.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -e "I" -e "Fine" texts/hope.txt"
else
    echo "FAIL: -e "I" -e "Fine" texts/hope.txt"
    diff outputs/1.txt outputs/2.txt
fi

./grep/s21_grep -i "hello" texts/hello.txt > outputs/1.txt
grep -i "hello" texts/hello.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -i "hello" texts/hello.txt"
else
    echo "FAIL: -i "hello" texts/hello.txt"
    diff outputs/1.txt outputs/2.txt
fi

./grep/s21_grep -v -e "I" -e "Fine" texts/hope.txt > outputs/1.txt
grep -v -e "I" -e "Fine" texts/hope.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -v -e "I" -e "Fine" texts/hope.txt"
else
    echo "FAIL: -v -e "I" -e "Fine" texts/hope.txt"
    diff outputs/1.txt outputs/2.txt
fi

./grep/s21_grep -c "bro" texts/bro.txt > outputs/1.txt
grep -c "bro" texts/bro.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -c "bro" texts/bro.txt"
else
    echo "FAIL: -c "bro" texts/bro.txt"
    diff outputs/1.txt outputs/2.txt
fi

./grep/s21_grep -l "Hello" texts/*.txt > outputs/1.txt
grep -l "Hello" texts/*.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -l "Hello" texts/*.txt"
else
    echo "FAIL: -l "Hello" texts/*.txt"
    diff outputs/1.txt outputs/2.txt
fi

./grep/s21_grep -n "Hello" texts/*.txt > outputs/1.txt
grep -n "Hello" texts/*.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -n "Hello" texts/*.txt"
else
    echo "FAIL: -n "Hello" texts/*.txt"
    diff outputs/1.txt outputs/2.txt
fi