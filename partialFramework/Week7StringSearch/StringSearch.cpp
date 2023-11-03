// CMP201.2022 AX1.5 String Search,
// Author: William Kavanagh
// Partial Framework

#include <string>
#include <iostream>
#include <vector>

const int ALPHABET_SIZE = 255;		// characters.

/*
* INPUT: pattern as string, length of pattern as in, int array of size alphabet to be filled.
* values in array should be -1 (if not in the pattern) or the index position of a character in the pattern.
* PERFORMANCE: O(m+n) (this is a hint as to what is provided).
*/
void badCharHeur(std::string pattern, int length, int in_pattern[ALPHABET_SIZE])
{
	// Assessed [1]: Information is provided in lecture 7B
	for (int i = 0; i < 255; ++i)
	{
		in_pattern[i] = -1;
	}

	for (int j = 0; j <= pattern.length() - 1; ++j)
	{
		in_pattern[int(pattern[j])] = j;
	}
}

/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: Boyer-Moore-Horspool should run in O(mn) in the worst-case and should be sublinear in the average case.
*/
std::vector<int> BMH(std::string text, std::string pattern)
{
	// Assessed [2]: Information is provided in lecture 7B
	int patternLength = pattern.size();
	int textLength = text.size();
	int shiftPos = 0;
	int badChar[ALPHABET_SIZE];
	std::vector<int> results;
	badCharHeur(pattern, patternLength, badChar);

	while (shiftPos <= textLength - patternLength)
	{
		int unMatchedChars = patternLength - 1;

		while (unMatchedChars >= 0 && pattern[unMatchedChars] == text[shiftPos + unMatchedChars])
		{
			unMatchedChars--;
		}
		if (unMatchedChars < 0)
		{
			results.push_back(shiftPos);
			if (shiftPos + patternLength < textLength)
			{
				shiftPos += patternLength - badChar[text[shiftPos + patternLength]];
			}
			else
			{
				shiftPos++;
			}
		}
		else
		{
			shiftPos += std::max(1, unMatchedChars - badChar[text[shiftPos + unMatchedChars]]);
		}
	}
	
	return results;
	
}

/*
* INPUT: pattern as string, length of pattern as in, pointer to array to be used as LPS structure.
* For each character in the pattern, fill the LPS structure with the length of the longest proper prefix-suffix,
*/
void computeLPS(std::string pat, int M, int* lps)
{
	// UNASSESSED: Information is provided in lecture 7C
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0) len = lps[len - 1];
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: O(m+h) in the worst case and similar in the average case.
*/
std::vector<int> KMP(std::string text, std::string pattern)
{
	// ASSESSED [2]: Information is provided in lecture 7C
	
	int patternLength = pattern.length();
	int textLength = text.length();
	

	int* lps = new int [patternLength];

	computeLPS(pattern, patternLength, lps);

	int i = 0; //index for text
	int j = 0; //index for pattern
	std::vector<int> results;

	while ((textLength - i) >= (patternLength - j))
	{
		if (pattern[j] == text[i])
		{
			++i;
			++j;
		}
		if (j == patternLength)
		{
			results.push_back(i - j);
			j = lps[j - 1];
		}
		else if (i < textLength && pattern[j] != text[i])
		{
			if (j != 0)
			{
				j = lps[j - 1];
			}
			else
			{
				++i;
			}
		}
	}
	

	return results; 
}


