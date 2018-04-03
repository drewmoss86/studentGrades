/**********************************************************
*AUTHOR           : Andrew Moss
*Assignment #3    : Student Records
*CLASS            : CS 003A
*SECTION          : MW:  1:00p - 2:25p
*                 : TTh: 1:00p - 3:05p
*Due Date         : 3/12/18
**********************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <cstring>
/**********************************************************
 * Student Records
 * ________________________________________________________
 * Program Description: This program reads and stores student
 *     data from an input file, computes and stores each student's
 *     test average, then prints a report to an output file, along
 *     with class averages.
 * ________________________________________________________
 * OUTPUT:
 *   student[].lastname    : last name for student
 *   student[].firstname   : first name for student
 *   student[].testAverage : student average test score
 *   classAvg              : average test score of entire class
 *   measuringStick        : series of dashes for printing lines
 *
***********************************************************/
using namespace std;

//Global const
const int SIZE = 20;

struct Student
{
    char lastName[SIZE];
    char firstName[SIZE];
    char course;
    int test1Grade;
    int test2Grade;
    int finalGrade;
    double testAverage;

};

//prototype
/********************************************************************
*  readFile
*     Reads from a file
*********************************************************************/
void readFile(ifstream &inFile);

/********************************************************************
*  openFile
*     Writes to a file.
*********************************************************************/
void openFile(ofstream &outFile);

/********************************************************************
*  printSummary
*     Prints the student grades summary
*********************************************************************/
void printSummary(Student student[],
                  char course,
                  int REC_NUM,
                  string measuringStick,
                  ofstream &outFile);

/********************************************************************
*  printLetterGrade
*     Prints the letter grade based on test averages
*********************************************************************/
char printLetterGrade(double avg);

int main(int argc, char *argv[])
{
    ifstream inFile;                     //IN - input stream
    ofstream outFile;                    //IN - output stream
    char lastName[SIZE];                 //IN - char array for last name
    char firstName[SIZE];                //IN - char array for first name
    char course;                         //IN - char for course type
    int REC_NUM = 0;                     //IN - integer for number of records
    int test1Grade = 0;                  //IN - integer for test 1 score
    int test2Grade = 0;                  //IN - integer for test 2 score
    int finalGrade = 0;                  //IN - integer for final test score
    string records;                      //IN - string to store records
    string measuringStick(64, '-');      //IN - string of dashes for printing
                                         //grades summary


    //Your program should start by asking the user to type the names of the
    //input and output files (in that order). Whenever a bad filename is
    //entered, print an error message and prompt the user to re-enter the
    //filename.

    //Asking user to type name of input file.
    do
    {
        readFile(inFile);
    }while(!inFile);

    //Asking user to type name of output file
    openFile(outFile);

    //Grab number of records from file
    getline(inFile, records, '\n');

    //PROCESSING: converts number of records from string to integer
    REC_NUM = atoi(records.c_str());

    Student student[REC_NUM];

    //PROCESSING: Grab and store values in corresponding members of Student
    //struct
    for(int i = 0; i < REC_NUM; i++)
    {
            getline(inFile, records, ',');
            records = records + ", ";
            strncpy(lastName, records.c_str(), 20);
            strncpy(student[i].lastName, lastName, 20);


            getline(inFile, records, ',');
            strncpy(firstName, records.c_str(), 20);
            strncpy(student[i].firstName, firstName, 20);

            getline(inFile, records, ',');
            course = records[0];
            student[i].course = course;

            getline(inFile, records, ',');
            test1Grade = atoi(records.c_str());;
            student[i].test1Grade = test1Grade;

            getline(inFile, records, ',');
            test2Grade = atoi(records.c_str());
            student[i].test2Grade = test2Grade;

            getline(inFile, records, '\n');
            finalGrade = atoi(records.c_str());
            student[i].finalGrade = finalGrade;

            //CALC: For each student, compute the test average and store it
            //in the test average member variable for that student struct.
            student[i].testAverage = ((student[i].test1Grade * .3) +
            (student[i].test2Grade * .3) + (student[i].finalGrade * .4));

    }

    //Close the file
    inFile.close();

    //OUTPUT: Title for grades summary
    outFile << "Student Grade Summary" << endl;
    outFile << "---------------------\n" << endl;
    outFile << endl;

    //OUTPUT: Tile for English class grades
    outFile << "ENGLISH CLASS" << endl;
    outFile << endl;
    outFile << setw(37) << left << "Student Name" << setw(13) << left
            << "Test Avg" << "Grade" << endl << measuringStick << endl;

    //printSummary - function prints out summary of student test averages and
    //organizes them based on class type
    printSummary(student, 'E', REC_NUM, measuringStick, outFile);

    //OUTPUT: Tile for English class grades
    outFile << "HISTORY CLASS" << endl;
    outFile << endl;
    outFile << setw(37) << left << "Student Name" << setw(13) << left
            << "Test Avg" << "Grade" << endl << measuringStick << endl;

    //printSummary - function prints out summary of student test averages and
    //organizes them based on class type
    printSummary(student, 'H', REC_NUM, measuringStick, outFile);

    //OUTPUT: Tile for English class grades
    outFile << "MATH CLASS" << endl;
    outFile << endl;
    outFile << setw(37) << left << "Student Name" << setw(13) << left
            << "Test Avg" << "Grade" << endl << measuringStick << endl;

    //printSummary - function prints out summary of student test averages and
    //organizes them based on class type
    printSummary(student, 'M', REC_NUM, measuringStick, outFile);

    outFile.close();

    return 0;
}

/************************************************************
*  readFile
* ___________________________________________________________
*  Reads from a file. Passes by reference the file for the
*    input stream.
* ___________________________________________________________
*  PRE-CONDITIONS:
*    &inFile : passes by input file
*
*  POST-CONDITIONS:
*    passes input file by reference, returns nothing.
*************************************************************/
void readFile(ifstream &inFile)
{
    string inFilename;   //IN - input file

    //OUTPUT: Asks user to enter name of file to read
    cout << "Please enter the name of the input file." << endl;
    cout << "Filename: " << endl;

    //INPUT: Input file name
    getline(cin, inFilename);

    //Open output input file
    inFile.open(inFilename.c_str());
}
/************************************************************
*  openFile
* ___________________________________________________________
*  Creates a file to write to. Passes by reference the file
*    output stream.
* ___________________________________________________________
*  PRE-CONDITIONS:
*    &outfile : passes by output file
*
*  POST-CONDITIONS:
*    passes output file by reference, returns nothing.
*************************************************************/
void openFile(ofstream &outFile)   //IN - output file
{
    string outFilename;   //IN - string representing outfile name

    //OUTPUT: Ask user to enter name of output file
    cout << endl << "Please enter the name of the output file." << endl;
    cout << "Filename: " << endl;

    //INPUT: Output file name
    getline(cin, outFilename);

    //Open output file
    outFile.open(outFilename.c_str());
    cout << "Processing Complete" << endl << endl;
}

/************************************************************
*  printSummary
* ___________________________________________________________
*  Prints student grades summary. Passes by value an
*    array of student, course type, and number of records.
*    Returns nothing.
*  Also reads current drawer's points to determind value of
*    aces
* ___________________________________________________________
*  PRE-CONDITIONS:
*    student : passes array of student
*    course : passes type of course type
*    REC_NUM : reads number of student records
*    measuringStick : reads in 64 dashes
*    &outfile : writes to file
*
*  POST-CONDITIONS:
*    passes array of student info, writes student info to file
*       returns nothing
*
*************************************************************/
void printSummary(Student student[],        //IN - student info
                  char course,            //IN - course type
                  int REC_NUM,              //IN - number of records
                  string measuringStick,    //IN - string for dashes
                  ofstream &outFile)        //IN - output file
{
    int count = 0;
    double sum = 0;
    double classAvg;

    for(int i = 0; i < REC_NUM; i++)
    {
        if(student[i].course == course)
        {
            outFile << setw(40) << left
                    << strcat(student[i].lastName, student[i].firstName)
                    << setprecision(2) << fixed << setw(8) << left
                    << student[i].testAverage << setw(5) << right
                    << printLetterGrade(student[i].testAverage) << endl;
            sum += student[i].testAverage;
            count++;
        }

    }

    classAvg = sum / count;
    outFile << endl << setw(40) << left << "Class Average" << setw(8) << left
            << classAvg << setw(5) << right << printLetterGrade(classAvg)
            << endl << measuringStick << endl;
}

/************************************************************
*  printLetterGrade
* ___________________________________________________________
*  Prints the letter grade. Passes by value the
*    average test score.
* ___________________________________________________________
*  PRE-CONDITIONS:
*    avg : passes average test score
*
*  POST-CONDITIONS:
*    passes average test score by value, returns letter grade char
*      value
*************************************************************/
char printLetterGrade(double avg)   //IN - Average test score
{
    char letterGrade;    //character value representing the letter grade

    //PROCESSING: Calculating letter grade based on numerical test score
    if(avg >= 90)
    {
        letterGrade = 'A';
    }
    else if(avg >= 80 && avg <= 89.99)
    {
        letterGrade = 'B';
    }
    else if(avg <= 79.99 && avg >= 70)
    {
        letterGrade = 'C';
    }
    else if(avg <= 69.99 && avg >= 60)
    {
        letterGrade = 'D';
    }
    else if(avg < 60)
    {
        letterGrade = 'F';
    }

    return letterGrade;

}
