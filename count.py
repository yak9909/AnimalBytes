import glob
import os
import re

files = \
  glob.glob("Sources/**/*.cpp", recursive=True) + \
  glob.glob("Includes/**/*.h", recursive=True)

total = 0

for i in files:
  with open(i,encoding='utf-8') as f:
    l = len(f.readlines())
    total += l
    print(f"{i}\t{l}")

print(f"total = {total}")

