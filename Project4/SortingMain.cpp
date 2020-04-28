include<Sorting.cpp>
include<iostream>
include<fstream>

using namespace std;
int main(int argc, char** argv){
	int value;
	int sortArry[10000];
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile)
    {
        cout << "\nError opening file.\n";
        return 13;
    }
	
	int i = 0;
	while(inFile >>value){
		sortArry[i] = value;
	}
	inFile.close;
	//the array should be filled now
	
	
	
	bool userInput = false;
	while(!userInput){
		cout << "(i)insertion-sort	(m)merge-sort	(h)heep-sort	(q)quick-sort	(b)bonus-sort\n";
		cout << "Enter the algorithm: \n";
		char choice;
		cin >> choice;
		cout << choice << "\n";//checking if read corectly
		if(choice=='i'){
			
		}
		else if(choice=='m'){
			
		}
		else if(choice=='h'){
			
		}
		else if(choice=='q'){
			quickSort(sortArry,0,9999);
		}
		else if(choice=='b'){
			
		}
		else{
			cout << "ERR: unrecognized user input try again\n";
		}	
	}
		
}