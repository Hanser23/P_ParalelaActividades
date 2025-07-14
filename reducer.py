#!/usr/bin/env python3
import sys

current_word = None
current_count = 0

# Leer cada línea del mapper
for line in sys.stdin:
    word, count = line.strip().split("\t")
    count = int(count)

    if current_word == word:
        current_count += count
    else:
        if current_word:
            print(f"{current_word}\t{current_count}")
        current_word = word
        current_count = count

# No olvidar el último valor
if current_word:
    print(f"{current_word}\t{current_count}")