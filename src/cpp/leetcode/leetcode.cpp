#include <math>
/*
670. Maximum Swap

Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
Note:
The given number is in the range [0, 108]
Accepted
30,165
Submissions
77,309
*/
class Solution
{
  public:
    /**
     * @param num: a non-negative intege
     * @return: the maximum valued number
     */
    int maximumSwap(int num)
    {
        // Write your code here
        int last[8] = {0};
        int index = 0;
        int calc = num;

        while (calc)
        {
            last[index++] = calc % 10;
            calc = calc / 10;
        }

        for (int i = index - 1; i >= 0; --i)
        {
            for (int j = 9; j > last[i]; --j)
            {
                for (int t = 0; t < i; ++t)
                {
                    if (last[t] == j)
                    {
                        int temp = last[i];
                        last[i] = j;
                        last[t] = temp;

                        int result = 0;
                        for (int m = 0; m <= index - 1; ++m)
                        {
                            result += last[m] * pow(10, m);
                        }
                        return result;
                    }
                }
            }
        }
        return num;
    }
};
/*
697. Degree of an Array
Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.
Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6
Note:

nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.
*/

class Solution
{
  public:
    int findShortestSubArray(vector<int> &nums)
    {
        std::map<int, int> left;
        std::map<int, int> right;
        std::map<int, int> count;

        for (int i = 0; i < nums.size(); ++i)
        {
            if (left.find(nums[i]) == left.end())
            {
                left[nums[i]] = i;
            }
            right[nums[i]] = i;
            count[nums[i]] += 1;
        }

        int degree = 0;
        for (std::map<int, int>::iterator it = count.begin(); it != count.end(); ++it)
        {
            if (degree < it->second)
            {
                degree = it->second;
            }
        }

        int result = 50000;
        for (std::map<int, int>::iterator it = count.begin(); it != count.end(); ++it)
        {
            if (it->second == degree)
            {
                result = min(result, right[it->first] - left[it->first] + 1);
            }
        }
        return result;
    }
};

/*
632. Smallest Range (todos)
You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

Example 1:
Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
Note:
The given list may contain duplicates, so ascending order means >= here.
1 <= k <= 3500
-105 <= value of elements <= 105.
For Java users, please note that the input type has been changed to List<List<Integer>>. And after you reset the code template, you'll see this point.
*/

class Solution
{
  public:
    vector<int> smallestRange(vector<vector<int>> &nums)
    {
        bool flag = true;
        int minx = 0, miny = INT_MAX;
        vector<int> next(nums.size(), 0);

        for (int i = 0; i < nums.size() && flag; ++i)
        {
            for (int j = 0; j < nums[i].size() && flag; ++j)
            {
                int min_i = 0;
                int max_i = 0;

                for (int k = 0; k < nums.size(); ++k)
                {
                    if (nums[min_i][next[min_i]] > nums[k][next[k]])
                    {
                        min_i = k;
                    }
                    if (nums[max_i][next[max_i]] > nums[k][next[k]])
                    {
                        max_i = k;
                    }
                }

                if (miny - minx > nums[max_i][next[max_i]] - nums[min_i][next[min_i]])
                {
                    miny = nums[max_i][next[max_i]];
                    minx = nums[min_i][next[min_i]];
                }

                next[min_i]++;

                if (next[min_i] == nums[min_i].size())
                {
                    flag = false;
                }
            }
        }
        return vector<int>{minx, miny};
    }
};

/*
443. String Compression
Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.

 
Follow up:
Could you solve it using only O(1) extra space?

 
Example 1:

Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
 

Example 2:

Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
 

Example 3:

Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.
 

Note:

All characters have an ASCII value in [35, 126].
1 <= len(chars) <= 1000.
*/

class Solution
{
  public:
    int compress(vector<char> &chars)
    {
        int total = 0;
        std::vector<char>::iterator cur_it = chars.begin();

        for (std::vector<char>::iterator it = chars.begin(); it != chars.end();)
        {
            char last = *it;
            int count = 0;
            total++;
            for (; it != chars.end() && *it == last; it++)
            {
                count++;
            }
            if (count != 1)
            {
                *cur_it++ = last;
                std::string count_str = std::to_string(count);
                for (int i = 0; i < count_str.size(); i++)
                {
                    *cur_it++ = count_str[i];
                }
                total += count_str.size();
            }
            else
            {
                *cur_it++ = last;
            }
        }
        return total;
    }
};

/*
Lintcode => 213. String Compression
Description
Implement a method to perform basic string compression using the counts of repeated characters. 
For example, the string aabcccccaaa would become a2b1c5a3.

If the "compressed" string would not become smaller than the original string, your method should return the original string.

You can assume the string has only upper and lower case letters (a-z).

Example
str=aabcccccaaa return a2b1c5a3
str=aabbcc return aabbcc
str=aaaa return a4
*/
class Solution
{
  public:
    /**
     * @param originalString: a string
     * @return: a compressed string
     */
    string compress(string &originalString)
    {
        // write your code here
        int total = 0;
        std::string::iterator cur_it = originalString.begin();
        std::string result_str;

        for (std::string::iterator it = originalString.begin(); it != originalString.end();)
        {
            char last = *it;
            int count = 0;
            total++;
            for (; it != originalString.end() && *it == last; it++)
            {
                count++;
            }

            result_str.push_back(last);
            std::string count_str = std::to_string(count);
            for (int i = 0; i < count_str.size(); i++)
            {
                result_str.push_back(count_str[i]);
            }
            total += count_str.size();
        }
        if (total >= originalString.size())
        {
            return originalString;
        }
        else
        {
            return result_str;
        }
    }
};