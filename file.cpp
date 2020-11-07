#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(void) {

 	std::string line;
   	std::string vectS[4][5000];
	std::string f,e[4];
	std::stringstream a[5000];
	int m = 0;
	int n = 0;
	int lengthline;
	int vect[4][5000];
	ifstream myfile ("monki.obj");
	while(!myfile.eof())
		{
    		getline (myfile,line);
    		if (line[0] == 'f')
    			{	
    				lengthline = line.lenght();
    				std::istringstream iss2( line );
				iss2 >> f>> vectS[0][m] >> vectS[1][m] >> vectS[2][m] >> vectS[3][m];
				for(int x = 0; x<4 ; x++){
					if((vectS[x][m].at(1)) == '/'){
        					e[x] = vectS[x][m].at(0);
					}
					if((vectS[x][m].at(2))=='/'){
						a[n] << vectS[x][m].at(0) << vectS[x][m].at(1);
        					e[x] = a[n].str();
					}
					
					if((vectS[x][m].at(3))=='/' && (vectS[x][m].at(1)) != '/'){
						a[n] << vectS[x][m].at(0) << vectS[x][m].at(1) << vectS[x][m].at(2);
        					e[x] = a[n].str();
					}
					n++;
					//cout << e[x] << "\t";
						
				}
				
				cout<<lengthline<<endl;	
				//vect[0][m] = std::stoi(e[0]);
				//vect[1][m] = std::stoi(e[1]);
				//vect[2][m] = std::stoi(e[2]);
				//vect[3][m] = std::stoi(e[3]);
        			//cout << vect[0][m] << "\t" << vect[1][m] << "\t" << vect[2][m] << "\t" << vect[3][m] << endl;
        			m++;
        		}
    		 	
    		}	  

 return 0;
}
