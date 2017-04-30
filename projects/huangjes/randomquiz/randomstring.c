/**********************************************************************************
** Name: Jessica Huang
** Course: CS362-004-SP17
** Description: Explanation for how the solution for testme.c was developed.
***********************************************************************************/

The inputChar() function is a function that creates random characters. Based on the 
function testme(), I can see that the characters can be symbols or letters. Therefore,
using the ASCII chart, I noticed that there are 95 usable ASCII characters, and they
start at character 32, hence the expression rand() % 95 + 32. This way, the characters
returned will be able to satisfy one of the conditions in the testme() function.

In the testme() function, the conditions we are looking to satisfy only require an array
of 5 characters and a null character. Thus, I made my array be 5 characters long with 
a null character at the end. To satisfy the conditions, all random characters in the
string are only the lowercase letters of the alphabet. Therefore, for the string random
I narrowed it down to only pick from the 26 lower case letters of the alphabet. Then,
I made the last character a null character to end the string.

In testme(), we start at state 0. Once the inputChar() function returns '[', then the 
state changes to 1. The loop continues and if the conditions are met in the if statement,
the state increments by 1. This is until state 9 is reached. At this point, the function
begins checking each index of the string for characters that match the conditional. 
s[0] == 'r', s[1] == 'e', s[2] == 's', s[3] == 'e', s[4] == 't', and s[5] == '\0'. If this
condition is randomly met, then the function prints "error " and quits, freeing the malloc'd
array at the end. 
