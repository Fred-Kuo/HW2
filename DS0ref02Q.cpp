//********************************************************************************/
// Exercise 02: Read/Write, Filter & Merge Files by Wu, Yi-Hung@ICE.CYCU    2021
//********************************************************************************/
// (1) Define SHOW to output 

#include <iostream>	                                            // cout, endl
#include <fstream>                                              // open, is_open, close, ignore
#include <string>                                               // string, find_last_of, substr
#include <vector>                                               // vector, push_back
#include <cstdlib>                                              // system, atoi
#include <iomanip>                                              // setw

#define PAGE        40                                          // amount of display on screen
#define BIG_INT     255                                         // integer upper bound
#define MAX_NO      9999                                        // maximum number of students/graduates

using namespace std;

typedef struct cT
{   string  rawR;                                               // raw data of one record
    string	cname;                                              // college name
    string  dname;                                              // department name
    int     sNO;                                                // number of students
    int     gNO;                                                // number of graduates
}	collegeType;

int getNO(int, int, string);                                    // get a number from user
bool readFile(string &, vector<collegeType> &, string);         // function declaration: read records from a file
void saveFile(string &, vector<collegeType> &, string);         // function declaration: save all records into a file
void putAllRecords(vector<collegeType> &);            	        // show the entire set of records on screen

int main(void)
{   int command = 0;									        // user command

    do
    {   vector<collegeType> cSet, cS2;                          // set of output records
        string              fileNO, fN2;                        // number to form a file name
        string              prefix;                             // prefix of a file name
        int                 sNO_t, gNO_t;                       // two thresholds

        cout << endl << "***  File Object Manipulator  ***";
        cout << endl << "* 0. QUIT                       *";
        cout << endl << "* 1. COPY (Read & Save a file)  *";
        cout << endl << "* 2. FILTER (Reduce a file)     *";
        cout << endl << "* 3. MERGE (Join two files)     *";
        cout << endl << "*********************************";
        cout << endl << "Input a choice(0, 1, 2, 3): ";
        cin >> command;										    // get a command
        switch (command)
        {	case 0: break;
            case 1: prefix = "input";                           // prefix of original file name
                    if (readFile(fileNO, cSet, prefix))         // function call: read records from a file
                    {   prefix = "copy";
                        saveFile(fileNO, cSet, prefix);         // function call: output all into a new file
#ifdef SHOW
                        putAllRecords(cSet);
#endif
                        cout << endl << "Number of records = " << cSet.size() << endl;                                         // clear up the space to keep output records
                    }   // end if
                    break;
            case 2: prefix = "copy";                            // prefix of intermediate file name
                    if (readFile(fileNO, cSet, prefix))         // function call: read records from a file
                    {   sNO_t = getNO(0, MAX_NO, "students");   // lower bound on the number of students
                        gNO_t = getNO(0, MAX_NO, "graduates");  // lower bound on the number of graduates
                        ;      // function call: remove records by filters
                        saveFile(fileNO, cSet, prefix);         // function call: output all into a new file
#ifdef SHOW
                        putAllRecords(cSet);
#endif
                        cout << endl << "Number of records = " << cSet.size() << endl;
                    }   // end if
                    break;
            case 3: prefix = "copy";                            // prefix of intermediate file name
                    if ((readFile(fileNO, cSet, prefix))        // function call: read records from a file
                         && (readFile(fN2, cS2, prefix)))       // function call: read records from a file
                    {   fileNO += "_" + fN2;                    // suffix of output file name
                        ;                   // function call: merge two sets of records
                        cS2.clear();                            // clear up the space to keep output records
                        prefix = "output";                      // prefix of output file name
                        saveFile(fileNO, cSet, prefix);         // function call: output all into a new file
#ifdef SHOW
                        putAllRecords(cSet);
#endif
                        cout << endl << "Number of records = " << cSet.size() << endl;
                    }   // end if
                    break;

            default: cout << endl << "Command does not exist!" << endl;
        }	// end switch
        cSet.clear();                                           // clear up the space to keep output records
    } while (command != 0);									    // '0': stop the program
    system("pause");										    // pause the display
    return 0;
}	// end main

//********************************************************************************/
// Utilities: getNO(), openData(), closeData()
//********************************************************************************/
int getNO(int minNO, int maxNO, string target)                  // get a number from user
{   // lower bound of M, upper bound of M, return a qualified number
    int     theNO;
    string  inputS;                                             // input string
    bool    isNum;                                              // whether it is a number

    do
    {   cout << endl << "Input a lower bound on the number of " << target << ": ";
        cin >> inputS;
        isNum = true;
        for (int i = 0; (i < inputS.length()) && (isNum); i++)
            if ((inputS[i] > '9') || (inputS[i] < '0'))         // ASCII code in ['1'~'9']
                isNum = false;
        if (!isNum)                                             // repeat it until getting a number
            continue;
        theNO = strtoul(inputS.c_str(), NULL, 10);              // string 2 a decimal number
        if ((theNO >= minNO) && (theNO <= maxNO))               // in the range of two bounds
            break;
        else
            cout << endl << "### It is NOT in [" << minNO << "," << maxNO << "] ###" << endl;
    } while (true);   // end do-while
    return theNO;										        // exit only if it succeeds
}   // end getNO


//****************************************************************************************************/
bool readFile(string &fileNO, vector<collegeType> &cSet, string prefix) // get records from a file
{   string		fileName;									    // input file name
	fstream     inFile;                                         // input file handle
    char        rBuf[BIG_INT];                                  // buffer to keep one whole record

    do {
        cout << endl << "Input 201, 202, ...[0]Quit): ";        // prompt message for input a file name
        cin >> fileNO;
        if (!fileNO.compare("0"))                               // No file to open, so quit
            return false;
        fileName = prefix + fileNO + ".txt";
// (2) Fill the code to open a file 
        ;             // open a file
        if (inFile.is_open())
            break;
        else                                                    // failure to open a file
            cout << endl << "### " << fileName << " does not exist! ###" << endl;                                                  // successfully open a file, so leave the loop
    } while(true);   //end while
    if (prefix == "input")
    {    ;                            // skip the first three line in file
// (3) Fill the code to skip the first 3 lines of the file
         ;                            // because they are file header
         ;                            // indicates meta-data such as field names
    }   // end if
    while (inFile.getline(rBuf, BIG_INT, '\n'))                 // retrieve one entire record from file
    {   string      temp;                                       // duplicate a string in another format
        collegeType oneC;                                       // keep one record with only the required fields
        int         cNo = 0, pre = 0, pos = 0;                  // indicators to extract each field in a record from left to right

        temp.assign(rBuf);                                      // make a duplicate of the entire record
        pos = temp.find_first_of('\t', pre);                    // move to the end of the first field
        while (pos != string::npos)
        {   string  aString;
            int     comma;

            aString = temp.substr(pre, pos - pre);
            switch (++cNo)
            {   case 2: oneC.cname = aString;                   // copy a college name
                        break;
                case 4: oneC.dname = aString;                   // copy a department name
                        break;
                case 7: if ((comma = aString.find(",")) != string::npos)    // number in the form of " , "
                        {   aString = temp.substr(pre + 1, pos - pre - 2);
                            aString.erase(comma - 1,1);
                        }   // end if
                        oneC.sNO = atoi(aString.c_str());       // copy the number of students
                        break;
                case 9: if ((comma = aString.find(",")) != string::npos)    // number in the form of " , "
                        {   aString = temp.substr(pre + 1, pos - pre - 2);
                            aString.erase(comma - 1,1);
                        }   // end if
                        oneC.gNO = atoi(aString.c_str());       // copy the number of graduates
                        break;
                default:    break;
            }   //end switch
            pre = ++pos;
            pos = temp.find_first_of('\t', pre);                // move to the end of the next field
        }   //end inner while
        oneC.rawR = temp;   	                            	// copy the raw data of one record
// (4) Save oneC into cSet
         ;                                   					// put a record into the collection
	}   //end outer while
    inFile.close();                                             // close input file
    if (cSet.size())
    	return true;										    // it succeeds if there is at least one records
	return false;
}   // end readFile

void saveFile(string &fileNO, vector<collegeType> &cSet, string prefix) // function definition: output all into a file
{   fstream     outFile;                                        // output file handle
    string      fileName = prefix + fileNO + ".txt";            // output file name


    outFile.open(fileName.c_str(), fstream::out);               // create a new file to write
    if (!outFile.is_open()) {                                   // unable to create a file
        cout << endl << "### " <<  fileName << " cannot be created! ###" << endl;
        return;
    }   //end if
    for (vector<collegeType>::iterator it = cSet.begin(); it < cSet.end(); ++it)
    {   //outFile << it->cname << "\t " << it->dname << "\t " << it->sNO << "\t " << it->gNO << "\t ";
// (5) Fill the code to write a line into outFlie
        ;
    }   // end for
    outFile.close();                                            // close file
}   // end saveFile

#ifdef SHOW
void putAllRecords(vector<collegeType> &stSet)             		// show the entire set of records on screen
{	// in: a set of records
    int idx = 0;

	for (vector<collegeType>::iterator it = stSet.begin(); it < stSet.end(); ++it)
 	{	cout << "[" << ++idx << "] " << it->rawR << endl;
        if (!(idx % PAGE))                                     	// pause the display when screen is full
            system("pause");
    }   //end for
}   // end putAllRecords
#endif
