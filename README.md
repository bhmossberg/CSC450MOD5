# CSC450MOD5 – File Append and Reverse in C++

A C++ program that appends a line of user input to a text file without overwriting what's already there. It then reads the whole file back and writes a character-by-character reversed copy to a second file.

## Overview

This is **CSU Global CSC450, Module 5 (Critical Thinking)**. The repository is an Eclipse workspace folder with one **Eclipse CDT** project, `CSC450_Mod5_CT_Mossberg/` (MinGW GCC toolchain):

| File | Role |
|---|---|
| `src/CSC450_Mod5_CT_Mossberg.cpp` | The program (Doxygen-documented) |
| `CSC450_CT5_mod5.txt` | **Input/append file.** It starts with the provided instructions ("Please be sure to append your data to this text file…") followed by the test lines appended so far. |
| `CSC450-mod5-reverse.txt` | **Output file.** The full contents of the input file reversed character by character, as produced by the last run. |

## How the code works

File names are fixed constants (`kSourceName`, `kReverseName`). What the user types is **never used as a file path**.

| Function | What it does |
|---|---|
| `readLine(label, out)` | Prompts and reads a full line, spaces included, with `std::getline`. Returns `false` on EOF or a stream error. |
| `appendLine(path, line)` | Opens an `std::ofstream` in **`std::ios::app`** mode, so the file is created if missing and never truncated, then writes the line and a newline. Returns whether the write succeeded. |
| `reverseFile(sourcePath, destPath)` | Reads the whole source file into a `std::string` using `std::istreambuf_iterator<char>`, which keeps newlines and whitespace exactly. It checks for read errors, calls **`std::reverse`**, and writes the result to the destination opened with `std::ios::trunc`. |
| `main()` | Read → append → reverse. Each step is checked, and on failure the program prints an error to `std::cerr` and returns `1` before doing anything else. On success it reports both file names. |

Because the reversal works on the whole file as one string, the line order and the characters within each line are both reversed. The last line of the input becomes the first line of the output, spelled backwards.

## Build and run

Any C++11 compiler. Run it from the folder that contains the text files (the CDT project folder), because the file names are relative:

```bash
cd CSC450_Mod5_CT_Mossberg
g++ -std=c++11 -o appendrev src/CSC450_Mod5_CT_Mossberg.cpp
./appendrev
```

```
Enter a line to append: Check
Appended to CSC450_CT5_mod5.txt.
Reversed copy written to CSC450-mod5-reverse.txt.
```

Each run adds one line to `CSC450_CT5_mod5.txt` and regenerates `CSC450-mod5-reverse.txt`. `system("pause")` keeps the Windows console open; on other systems it only prints a "not found" message.

## Concepts demonstrated
- File streams: `std::ifstream`/`std::ofstream`, and append versus truncate modes
- Reading a whole file with stream-buffer iterators
- STL algorithms (`std::reverse`)
- Checking every I/O operation and failing early with non-zero exit codes
- Secure-coding practice: fixed file paths, never paths taken from user input
