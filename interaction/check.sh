#!/bin/sh -e


RESULT=$(echo "adam" | nc -q 1 "$1" "$2")
echo "$RESULT" | grep "How good are you around the corners?"
echo "$RESULT" | grep "Send me your ride"
echo "$RESULT" | grep "You ain't ready."


RESULT=$(python -c "print('a'*25 + '\x00')" | nc -q 1 "$1" "$2")
echo "$RESULT" | grep "You're not up to code."
