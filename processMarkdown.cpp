#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctype.h>

// This program reads a text file in markdown form and generate a new HTML file with respective HTML tags.
// This program impliments below mark down features.
// - Implement # to represent <H1>(HTML format)
// - Implement ## to represent <H2>(HTML format)
// - Implement ### to represent <H3>(HTML format)
// - Implement #### to represent <H4>(HTML format)
// - Implement orderlist(1.) to represent <ol><li>(HTML format)

using namespace std;

void GenerateHTML(vector<string> &values, string& path)
{
    FILE *pFile = NULL;
    pFile = fopen(path.c_str(), "w"); //open file in a write mode
    if (pFile != NULL)                    // file pointer checks untill not null
    {
        fputs("<html>", pFile); //write string output file
        fputs("<body>", pFile); //write string output file

        size_t count = values.size(); //cout variable  of unsighned int store size of vector
        bool olStartflag = false;     //to check true or false

        for (size_t index = 0; index < count; index++) //loop goes from 0 to end of vector
        {
            string str = values.at(index);
            if (isdigit(str[0]) && str[1] == '.')
            {
                if (!olStartflag) // check bool condition true (olStartflag == false)
                {
                    fputs("<ol>", pFile);
                    olStartflag = true;
                }

                if (values.at(index).find(".") != string::npos) //find . go in
                {
                    std::size_t pos = values.at(index).find(".");
                    std::string str3 = values.at(index).substr(pos + 1);
                    fprintf(pFile, "<li>%s</li>", str3.c_str());
                }

                else
                {
                    if (olStartflag) // check bool  condition true (olStartflag == true) to check after the orderlist completed
                    {
                        fputs("</ol>", pFile);
                        olStartflag = false;
                    }
                }
            }
            else
            {
                if (values.at(index).find("####") != string::npos) //find 4# go in
                {
                    std::size_t pos = values.at(index).find("####");     //4# store in position(pos)
                    std::string str3 = values.at(index).substr(pos + 4); //remove 4# remain substr store in str3
                    fprintf(pFile, "<H4>%s</H4>", str3.c_str());         // c_str-representing the current value of the string and write in to output file
                }
                else if (values.at(index).find("###") != string::npos) //find 3# go in
                {
                    std::size_t pos = values.at(index).find("###");
                    std::string str3 = values.at(index).substr(pos + 3);
                    fprintf(pFile, "<H3>%s</H3>", str3.c_str());
                }
                else if (values.at(index).find("##") != string::npos) // find ## go in
                {
                    std::size_t pos = values.at(index).find("##");
                    std::string str3 = values.at(index).substr(pos + 2);
                    fprintf(pFile, "<H2>%s</H2><hr></hr>", str3.c_str());
                }
                else if (values.at(index).find("#") != string::npos) // find # go in
                {
                    std::size_t pos = values.at(index).find("#");
                    std::string str3 = values.at(index).substr(pos + 1);
                    fprintf(pFile, "<H1>%s</H1><hr></hr>", str3.c_str());
                }
                else
                {
                    fprintf(pFile, "%s", values.at(index).c_str()); //find no # just print string
                }
            }
        }
        if (olStartflag)
        {
            fputs("</ol>", pFile);
            olStartflag = false;
        }

        fputs("</body>", pFile);
        fputs("</html>", pFile);
        fclose(pFile);
    }
}

void replaceExt(string& s, const string& newExt)
{
    size_t index = s.rfind('.', s.length());
    if(index != string::npos)
    {
        s.replace(index+1, newExt.length(), newExt);
    }
}

int main(int argc, char** argv)
{
    FILE *pFile = NULL; // Holds a file pointer
    char mystring[50];  // Holds each line texts from file

    vector<string> values; //vector declaration- vector <type> variable

    // Check for number of arguments
    if (argc != 2)
    {
        cout << "Arguments are missing, please provide input file" << endl;
        cout << "Unable to continue..." << endl;
        return 1;
    }

    // Process input file 
    string inputpath = argv[1];
    pFile = fopen(inputpath.c_str(), "r");
    if (pFile != NULL)
    {
        while (fgets(mystring, 50, pFile) != NULL)
        {
            values.push_back(mystring); // insert string
        }

        fclose(pFile);

        size_t count = values.size(); // get number of elements size in a vector
        for (size_t index = 0; index < count; index++)
        {
            cout << values.at(index) << endl; //std::string::at can be used to extract characters by characters from a given string.
        }
        
        string outpath = argv[1];
        replaceExt(outpath, "html");
        GenerateHTML(values , outpath);
    }
    else
    {
        cout << "error reading file" << endl;
    }
    return 0;
}
