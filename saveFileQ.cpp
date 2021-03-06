#include <iostream> // cout, endl
#include <string>   // string
#include <cstdio>   // fopen, fwrite, fclose
#include <cstdlib>  // system

#define SID_LEN	12  // length of sid
#define SR_NUM  10  // number of student records

using namespace std;

typedef struct student
{	char	sid[SID_LEN];   // fixed-length ID
	int		score;          // integer score
}	studentType;

// (1) 恶糶ㄧ计把计絪亩Θ 
void saveFile( );

int main(void)
{   FILE        *outfile = NULL;    // handler of output file
	string      fileName = "DSsample1.dat";
	studentType allS[SR_NUM] = {{"10027113", 60}, {"10127102", 70}, {"10027213", 90}, {"10127256", 80}, {"10227108", 100},
                                {"10227143", 95}, {"10227115", 75}, {"10220107", 88}, {"10227201", 64}, {"10227236", 85}};

// (2) 竚传よNULL秨币郎fopenΘ糶郎把计郎﹃, 秨郎家Α 
    outfile = NULL;    // open a file to write
    if (outfile != NULL)
        saveFile(outfile, allS, SR_NUM);
    system("pause");
    return 0;
}	// end main

void saveFile(FILE *fp, studentType dA[], int no)
{   for (int i = 0; i < no; i++)    // write records one by one
    {   fwrite(&dA[i], sizeof(dA[i]), 1, fp);
        cout << dA[i].sid << ", " << dA[i].score << endl;
    }   // end for
    fclose(fp); // close the file handler
}
