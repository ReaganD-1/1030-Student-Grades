#include "rmd0171Project2_header.h"
/*Function:		add_Student
  Parameters: 	file input stream, file output stream
  Returns:		VOID
  Description:	Takes information given from the user and adds the information to the text document.
*/
void add_Student(ifstream& fin, ofstream& fout)
{
	fout.open("student.dat", fstream::app);//opens the file in append mode
	string tempFname;
	string tempLname;
	int tempID;//variable declarations
	int* tempTestArray;
	int numTests;
	
	cout << "Please enter last name of student:";
	cin >> tempLname;
	cin.ignore();//ignore to fix the getline
	cout << "Please enter first name of student:";
	getline(cin, tempFname);
	cout << "Please enter ID of student:";
	cin >>tempID;
	cout << "Please enter number of tests taken by the student:";
	cin >> numTests; //cin/getlines that get all relevant information for the file
	
	tempTestArray = new int[numTests];//initializing dynamic array with size of numTests
	
	for(int i = 0; i < numTests; ++i)//collects the scores of the given tests
	{
		cout << "Please enter score for test #" <<i + 1 << endl;
		cin >> tempTestArray[i];
	}
	fout << tempLname << ',' << tempFname;
	fout << ',' << tempID << ',' << numTests << ',';//formatting and putting the information in the file
	for(int i = 0; i < numTests; ++i)
	{
		fout << tempTestArray[i] << ",";
	}//putting the test scores into file
	
	fout << endl;
	delete [] tempTestArray;//deallocating the dynamic memory
	fout.close();//closing the file
}
/*Function:		remove_Student
  Parameters: 	file input stream, file output stream
  Returns:		VOID
  Description:	Recieves a given ID from the user and removes the corresponding information from the text file.
*/
void remove_Student(ifstream& fin, ofstream& fout)
{
	fin.open("student.dat");//opening the file to grab current info
	int count = 0;
	string tempLname;
	string tempFname;//variable declarations
	int matchIndex;

	int tests[num_tests];
	bool matchFound = false;//boolean to determine if there is matching information
	int compID;
	int numStudents = getNumber();//calls the getNumber function to determine the lines in the file already filled
	int numTests;
	Student* tempArray ;
	tempArray = new Student[numStudents + 1];//allocates dynamic memory to the dynamic array
	
	cout << "Enter ID of student to remove:" << endl;
	cin >> compID;//user enters ID of student to remove
	string records[numStudents];//declares a string for grabbing test info without needing to manipulate it
	
	while(!fin.eof())
	{
		getline(fin,tempLname,',');
	    getline(fin,tempFname, ',');//gets name info from file
		fin >> tempArray[count].stdID;//gets ID from file
		if(tempArray[count].stdID == compID)//determines if the entered ID matches an ID in the file
		{
			matchFound = true;
			matchIndex = count;
		}
		getline(fin, records[count]);//grabs the test info from the line in the file
		tempArray[count].stdName = tempLname + ',' + tempFname;//formats the name data and inputs into the array
		++count;
		
	}
	fin.close();//closes the file for input
	if(matchFound)
	{
		fout.open("student.dat");//if there is a match found, opens file for output
		for(int i = 0; i < numStudents; ++i)//iterates a number of times = to students given without extra info
	    {
			if(i != matchIndex)//outputs info for indexes that do NOT match the index of ID to remove
			{
	        fout << tempArray[i].stdName << ',';
	        fout << tempArray[i].stdID;
	        fout << records[i] << endl;
			}
	    }
	}
	else
	{
	cout << "No matching student for input ID" << endl;	
	}
	
		
	delete [] tempArray;	//deallocates memory 
	fout.close();//closes file if opened 
}
/*Function:		display
  Parameters: 	file input stream
  Returns:		VOID
  Description:	Reads all data from file input stream into an array of the structure type Student,
				then prints data from array to screen.
*/
void display(ifstream& fin)
{
	fin.open("student.dat");	//opening student record file 
	string tempLname;	//temporary string to store last name
	string tempFname;	//temporary string to stre first name	
	int numStudents = getNumber();	//number of students in the file (returned by getNumber())
	
	Student* tempArray;		//stores each student's data
	tempArray = new Student[numStudents];	
	
	string charDump;	//stores the number of tests taken by a student
	
	for(int i=0;i<numStudents;++i)	//iterates through all students and copies their information to tempArray
	{
		if(i != 0)
		{
			fin.ignore(256, '\n');	//ignores unwanted newline characters from the input buffer
		}
		
		getline(fin,tempLname,',');		//reads last name
	    getline(fin,tempFname, ',');	//reads first name
		tempArray[i].stdName = tempLname + ',' + tempFname;		//fills struct member with first and last name in a single string

		fin >> tempArray[i].stdID;	//reads student ID into the struct
		
		fin.ignore(256, ',');	//ignores an unwanted ',' character
		
		
		getline(fin, charDump, ',');	//reads the number of tests taken by a student
		
		tempArray[i].numScores = atoi(charDump.c_str());	//converts the number of tests to an integer and puts in the structure member
		
		
		for(int j=0;j<tempArray[i].numScores;++j)	//reads as many test scores as have been specified by charDump/numScores member
		{
			string tempStr;	//string to read scores into
			
			getline(fin, tempStr, ',');	//reading scores into string
			
			tempArray[i].stdArray[j] = atoi(tempStr.c_str());	//converting string to int and storing in structure member
		
		}
	}
	
	for(int i = 0; i < numStudents; ++i)	//prints student information
	{
		cout << setw(30);
	    cout << tempArray[i].stdName;	//printing name
		cout << setw(15);
		cout << tempArray[i].stdID;		//printing ID number
		
		for(int j=0; j<tempArray[i].numScores;++j)	//prints test scores
		{
		cout << setw(5);
		cout << tempArray[i].stdArray[j];	//printing each score for the student
		}
		cout<<endl;
	}
	fin.close();
	
	delete [] tempArray;
	
	return;
}

/*Function:		search
  Parameters:	File input stream, ID# to search for
  Returns:		VOID
  Description:	searches the file for a user entered student ID number and prints the matching student information
  */
void search(ifstream& fin, int searchID)
{
	fin.open("student.dat");	//input file 	
	string tempLname;	//temporary string to store last name
	string tempFname;	//temporary string to store first name

	int numStudents = getNumber();	//number of students in the file (returned by getNumber()) 
	bool matchFound = false;	//flag to indicate an ID# match
	
	Student* tempStudent;		//stores student data one at a time as the file is iterated through
	tempStudent = new Student;
	
	string charDump;	//number of tests taken by a student
	
	for(int i=0;i<numStudents;++i)	//iterates through all students and and stores the current one in tempStudent
	{
		if(i != 0)
		{
			fin.ignore(256, '\n');	//ignores an unwated newline character in the input buffer
		}
		
		getline(fin,tempLname,',');		//reads last name
	    getline(fin,tempFname, ',');	//readsa first name
		tempStudent->stdName = tempLname + ',' + tempFname;		//fills struct member with first and last name in a single string
		fin >> tempStudent->stdID;
		
		fin.ignore(256, ',');	//ignores an unwanted ',' character
		
		getline(fin, charDump, ',');	//reads the number of tests take by a student

		tempStudent->numScores = atoi(charDump.c_str());	//converts charDump to an integer and stores it in the struct member
		
		
		for(int j=0;j<tempStudent->numScores;++j)	//reads as many test scores as indicated by numScores
		{
			string tempStr;	//string to read scores into
			
			getline(fin, tempStr, ',');		//reads exam score into tempStr
			
			tempStudent->stdArray[j] = atoi(tempStr.c_str());	//converts tempStr to int and stores it in struct member
		
		}
		
		if(searchID == tempStudent->stdID)	//sets matchFound flag to true if the ID# read from the file matches with the ID# argument from the user
		{
			matchFound = true;
			break;	//ends the loop to stop reading new student data
		}
		
	}
	
	if(matchFound == true)
	{
		cout << setw(30);
		cout << tempStudent->stdName;	//prints student name
		cout << setw(15);
		cout << tempStudent->stdID;		//prints student ID
		
		for(int j=0; j<tempStudent->numScores;++j)	//prints all exam scores
		{
			cout << setw(5);
			cout << tempStudent->stdArray[j];
		}
		cout<<endl;
	}
	
	else	//prints a search failure if no match is found
	{
		cout<<"No matching student ID found"<<endl;
	}
	fin.close();
	return;
}

/*Function:		findMinimum
  Parameters:	int pass by reference abc, Student pointer my_student
  Returns:		float
  Description:  find the minimum test scores of each student
  */

float findMinimum(int& abc, Student* my_student)
{
	float minS;
	int numbS = getNumber();  //get the number of students

	if (my_student[abc].numScores < 5)   //if kids take less than 5 test then there is no minimum
	{
		minS = 0;
	}
	else
	{
		for (int i =0; i < 5; ++i)    //if kids take all 5 tests then there is a minimum
		{
			minS = my_student[abc].stdArray[0];   //sets the minimum to be compared to all other test scores
			if (my_student[abc].stdArray[i] < minS)  //finds the minimum
			{
				minS = my_student[abc].stdArray[i];
			}
		}
		my_student[abc].numScores = my_student[abc].numScores-1;  //sets the number of scores back one becuase the minimum will be subrtractd from the sum
	}
	
return minS;
}
	
/*Function:		exportResults
Parameters:	File input stream, file output stream
Returns:		VOID
Description:	Gets information from input stream, then finds the average for each student and adds the student ID and average to the output file
*/
void exportResults(ifstream& fin, ofstream& fout)
{
	fout.open("averages.dat");
	fin.open("student.dat");
	Student* my_student;
	string hold;
	int numbStudent = getNumber();  //get the number of students
	
	my_student = new Student [numbStudent];
	
	for (int i = 0; i <numbStudent; ++i)   //reads all the information for each student into the pointer dynamic array 
	{
		getline(fin,my_student[i].stdName,',');
		getline(fin,hold,',');
		my_student[i].stdName = my_student[i].stdName + "," + hold;
		fin >> my_student[i].stdID;
		fin.ignore();
		fin >> my_student[i].numScores;
		fin.ignore();
		
		for (int j=0; j< my_student[i].numScores; ++j)
		{
			fin >> my_student[i].stdArray[j];
			fin.ignore();
		}
	}
	
	
	for (int abc=0; abc < numbStudent; ++abc)   //creates the average for each student
	{
		float sum = 0;
		for (int j=0; j < my_student[abc].numScores; ++j)
		{
			sum = sum + my_student[abc].stdArray[j];  //finds the sum of the test scores for each student
		}
		float min = findMinimum(abc, my_student);  //get the minimum for the students
		sum = sum - min;  //find the new sum after subtracting the minmum
		my_student[abc].stdAverage = sum/my_student[abc].numScores;  //find the adverage of each student
		fout << my_student[abc].stdID << "	" << fixed << setprecision(1)<< my_student[abc].stdAverage <<endl;  //Print each students ID and average in the output file
	}
	
	cout<< "Results exported to file." <<endl;
	
	fout.close();
	fin.close();
	delete [] my_student;   //deletes dynamic array
	
return;
}