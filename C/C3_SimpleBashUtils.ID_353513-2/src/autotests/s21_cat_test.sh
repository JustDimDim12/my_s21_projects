#!/bin/sh

mkdir -p outputs

./cat/s21_cat texts/hello.txt > outputs/1.txt
cat texts/hello.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: texts/hello.txt"
else
    echo "FAIL: texts/hello.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat -b texts/how.txt > outputs/1.txt
cat -b texts/how.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -b texts/how.txt"
else
    echo "FAIL: -b texts/how.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat --number-nonblank texts/how.txt > outputs/1.txt
cat --number-nonblank texts/how.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: --number-nonblank texts/how.txt"
else
    echo "FAIL: --number-nonblank texts/how.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat -e texts/how.txt > outputs/1.txt
cat -e texts/how.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -e texts/how.txt"
else
    echo "FAIL: -e texts/how.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat -E texts/how.txt > outputs/1.txt
cat -E texts/how.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -E texts/how.txt"
else
    echo "FAIL: -E texts/how.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat -n texts/how.txt > outputs/1.txt
cat -n texts/how.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -n texts/how.txt"
else
    echo "FAIL: -n texts/how.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat -s texts/hope.txt > outputs/1.txt
cat -s texts/hope.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -s texts/hope.txt"
else
    echo "FAIL: -s texts/hope.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat --squeeze-blank texts/hope.txt > outputs/1.txt
cat --squeeze-blank texts/hope.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: --squeeze-blank texts/hope.txt"
else
    echo "FAIL: --squeeze-blank texts/hope.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat -t texts/hope.txt > outputs/1.txt
cat -t texts/hope.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -t texts/hope.txt"
else
    echo "FAIL: -t texts/hope.txt"
    diff outputs/1.txt outputs/2.txt
fi

./cat/s21_cat -T texts/hope.txt > outputs/1.txt
cat -T texts/hope.txt > outputs/2.txt
if diff outputs/1.txt outputs/2.txt
then
    echo "SUCCESS: -T texts/hope.txt"
else
    echo "FAIL: -T texts/hope.txt"
    diff outputs/1.txt outputs/2.txt
fi