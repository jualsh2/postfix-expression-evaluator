# Postfix Expression Evaluator

A console program in C++ that evaluates postfix (Reverse Polish Notation) expressions using a **queue** and a **stack** that are implemented by hand with arrays, without the STL containers.

> CS2011 Data Structures · Effat University · Fall 2025
> Team: Osama Abutaha, Ahmad Baabod, **Joman Alsharbini**

## How it works

```
"5 1 2 + 4 * + 3 -"
        │  tokenize (split by spaces, validate each token)
        ▼
 Queue (circular array of string tokens)
        │  dequeue one token at a time
        ▼
 number   → push onto the Stack
 operator → pop b, pop a, push (a op b)
        ▼
 exactly one value left on the Stack → result (14)
```

## Features

- Operators `+ - * / ^` and signed integers such as `-3` or `+10`
- **Array-based stack** (`push`, `pop`, `top`, `isEmpty`, `isFull`)
- **Circular array queue** (`addQue`, `deQue`, `front`, `rear`)
- Clear error messages for:
  - invalid tokens
  - division by zero
  - missing operands
  - leftover operands
- O(n) time and O(n) extra space for n tokens

## Example runs

These are real outputs from the test script.

| Input | Output |
|---|---|
| `2 1 + 3 *` | `Result: 9` |
| `4 13 5 / +` | `Result: 6` |
| `5 1 2 + 4 * + 3 -` | `Result: 14` |
| `-3 4 *` | `Result: -12` |
| `3 0 /` | `Error: division by zero` |
| `2 +` | `Error: insufficient operands` |
| `1 2 3 +` | `Error: leftover operands` |
| `2 3 x` | `Error: invalid token x` |

## Build and run

```bash
g++ -std=c++17 -o postfix src/postfix_evaluator.cpp
./postfix
# Enter a postfix expression (space separated): 5 1 2 + 4 * + 3 -
# Result: 14
```

Run all test cases:

```bash
./tests/run_tests.sh   # 9 passed, 0 failed
```

## Project structure

```
├── src/postfix_evaluator.cpp   stack, queue and evaluator
└── tests/                      test cases and runner script
```

## Team

| Member | Part |
|---|---|
| Osama Abutaha | Stack and circular queue implementation |
| **Joman Alsharbini** | Tokenization, input parsing and invalid-token error handling |
| Ahmad Baabod | Integration and postfix evaluation logic |

## Portfolio

Case study: https://jualsh2.github.io
