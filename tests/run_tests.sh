#!/usr/bin/env bash
# Compiles the evaluator and checks each case in tests/cases.txt ("input|expected text").
set -u
cd "$(dirname "$0")/.."
g++ -std=c++17 -O2 -o postfix src/postfix_evaluator.cpp || exit 1
pass=0; fail=0
while IFS='|' read -r input expected; do
  out=$(echo "$input" | ./postfix 2>&1)
  if grep -qiF -- "$expected" <<<"$out"; then pass=$((pass+1)); echo "PASS  $input"
  else fail=$((fail+1)); echo "FAIL  $input  -> $(tail -1 <<<"$out")"; fi
done < tests/cases.txt
echo "$pass passed, $fail failed"; [ "$fail" -eq 0 ]
