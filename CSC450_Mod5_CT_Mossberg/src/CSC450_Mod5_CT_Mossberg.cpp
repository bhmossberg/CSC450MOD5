/**
 * @file CSC450_Mod5_CT_Mossberg.cpp
 * @brief Appends one user line to CSC450_CT5_mod5.txt and writes a reversed copy.
 *
 * The source file is opened in append mode so the existing lines stay in place.
 * After the append, the whole file is read into a std::string, reversed by
 * character, and written to CSC450-mod5-reverse.txt. User string is not
 * used as a path.
 *
 * @author Benjamin Mossberg
 * @date 2026-10-08
 * @version 1.0
 */

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

const char* kSourceName = "CSC450_CT5_mod5.txt";
const char* kReverseName = "CSC450-mod5-reverse.txt";

/**
 * @brief Reads one line from standard input, include spaces.
 *
 * @param label	Prompt written before the read.
 * @param out	Receives the line on success. Unchanged on failure.
 * @return true if a line was read; false on EOF or a stream error.
 */
bool readLine(const char* label, std::string& out)
{
	std::cout << label;
	return static_cast<bool>(std::getline(std::cin, out));
}

/**
 * @brief Appends one line to path. Does not truncate an existing file.
 *
 * @param path Destination file. Created if it does not exist.
 * @param line Text to append. Includes writing newline at end of string.
 * @return true if the file was opened and the write succeeded.
 */
bool appendLine(const char* path, const std::string& line)
{
	std::ofstream out(path, std::ios::app);
	if (!out)
		return false;
	out << line << '\n';
	return static_cast<bool>(out);
}

/**
 * @brief Reverses every character of sourcePath into destPath.
 *
 * The destination is replaced. The source is only read.
 *
 * @param sourcePath File whose characters are reversed.
 * @param destPath   File that receives the reversed text.
 * @return true if both files were opened and the write succeeded.
 */
bool reverseFile(const char* sourcePath, const char* destPath)
{
	std::ifstream in(sourcePath);
	if (!in)
		return false;

	std::string text((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
	if (!in && !in.eof())
		return false;

	std::reverse(text.begin(), text.end());

	std::ofstream out(destPath, std::ios::trunc);
	if (!out)
		return false;
	out << text;
	return static_cast<bool>(out);
}

/**
 * @brief Appends one user line, then writes a character-reversed copy of the file.
 *
 * A failed read or a failed file operation exits before any later step.
 * The source file is never opened for truncation.
 *
 * @return 0 on success; 1 if input or a file operation fails.
 */

int main()
{
	std::string userLine;
	if (!readLine("Enter a line to append: ", userLine))
	{
		std::cerr << "Input ended before a line was read. File not changed.\n";
		std::system("pause");
		return 1;
	}

    if (!appendLine(kSourceName, userLine))
    {
    	std::cerr << "Could not append to " << kSourceName << ".\n";
    	std::system("pause");
    	return 1;
    }

    if (!reverseFile(kSourceName, kReverseName))
    {
    	std::cerr << "Could not write the reversed file.\n";
    	std::system("pause");
    	return 1;
    }

    std::cout << "Appended to " << kSourceName << ".\n";
    std::cout << "Reversed copy written to " << kReverseName << ".\n";
    std::system("pause");
    return 0;
}

