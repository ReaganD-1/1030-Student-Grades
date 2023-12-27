#include "rmd0171Project2_header.h"
int main()
{	
	bool exit = true;
	
	ifstream fin;
	ofstream fout;
	
	do{ //loop to keep the program running until the quit case is selected
		
	 cout << "1. Add" << endl;     //asks users what they want to do
     cout << "2. Remove" << endl;
     cout << "3. Display" << endl;
     cout << "4. Search" << endl;
     cout << "5. Results" << endl;
	 cout << "6. Quit" << endl;
	 cout << "Enter choice: " << endl;
	 
	 int choice;
	 
	 //gets menu choice from the user
	 cin >> choice;
	 
	 //changes the choice to where it can be read as an enum
	 MenuSelect my_Select = static_cast<MenuSelect>(choice);
	 
	 switch(my_Select)
	 {
		 case Add:   //if selectd user can add a student
		 
		 add_Student(fin, fout);
		 
		 break;
		 
		 case Remove:  //if selected user can remove a student
		  
		 remove_Student(fin, fout);
		 
		 break;
		 
		 case Display:  //if selected user can deisplay all student information
		 
		 display(fin);
		 
		 break;
		 
		 case Search:   //if selected user can search for a student
		 
		int searchID;
		cout<<"Please enter an ID number to search for"<<endl;
		cin>>searchID;
		search(fin, searchID);
		 
		 break;
		 
		 case Results:   //if selected user can go to output file to see the new averages for each student
		 
		 exportResults(fin, fout);
		 
		 break;
		 
		 case Quit:   //if selected user can exit the program
		 
		exit = false;
		cout<< "Goodbye"<<endl;
		 
		 break;
		 
		 default: //if none of the menu choices are chosen then this runs
		 
		cout << "Error: Please enter a menu choice" <<endl;
		 
		 break;
		 
	 }
		 
	 }while (exit == true);  //loop to keep the program running until the quit case is selected
	 
	return 0;
}