import os
import platform
import re

srcfiles = []
files = os.listdir("src")
for file_index, filename in enumerate(files):
    # search for .c extesnion in a filename
    result = re.search(".*.c", filename)
    if result:
        # if a pattern match was found then we check to ensure that it is equal to the filename
        # and is a valid file extension then we append it to the list
        result = result.group()
        if filename == result:
            print(f"Building source file {filename}...")
            os.system(f"cd src && gcc -c {filename}")
print("Building flexlang compiler...")
os.system("gcc -ggdb main.c src/*.o -o flex")
print("Running flexlang compiler...")
if platform.system() == "Windows":
    os.system(".\\flex.exe")
else:
    os.system("./flex")
