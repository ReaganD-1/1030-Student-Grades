/*Authors: 		Reid McCalpin: rmm0378, DJ Trammel: djt0163, Reagan Duke: rmd0171
  Date:			4/30/2023
  Instructor:	Dr.Shrestha
  Description:	A small code for a program that focuses on students test inforamtion. Student information include 
				name, ID, number of scores, and test scores. With this program the user can add, remove,display, 
				search or get the average of the test results for each student. The program is devised and 
				written with the knowledge of a week 4 CSE1030 student. 
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <istream>
#include <string>
using namespace std;

const int num_tests = 5;
enum MenuSelect {Add = 1, Remove = 2, Display = 3, Search = 4, Results = 5, Quit = 6};  //enum for menu selction
struct Student    //structure for students information
{
	string stdName;
	int stdID;
	int numScores;
	int* stdArray = new int[numScores];
	double stdAverage;
};