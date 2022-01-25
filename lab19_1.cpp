#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file,vector<string> &name,vector<int> &score,vector<char> &grade){
   char names[100];
   int a,b,c,sum;
   ifstream myfile(file);
   string text;
   
    while (getline(myfile,text))
    {  
      string y = text; 
      char *point = new char[y.size()+1];
      char score1[] = "%[^:] : %d %d %d";
      strcpy(point,y.c_str());
      sscanf(point,score1,names,&a,&b,&c);
      sum = a+b+c;
      name.push_back(names);
      score.push_back(sum);
      grade.push_back(score2grade(sum));
      
    }
    
}

void getCommand(string &command,string &key){
    
    cout << "Please input your command: ";
    cin >> command;
    if (toUpperStr(command)== "NAME" || toUpperStr(command) == "GRADE")
    {
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> &name,vector<int> &score,vector<char> &grade,string &key){
    bool check = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < name.size(); i++)
    {   
        if(toUpperStr(key)==toUpperStr(name.at(i))) {
        check = true;
        cout << name.at(i) << "'s score = " << score.at(i) << endl;
        cout << name.at(i) << "'s grade = " << grade.at(i) << endl;
        }
    }   
        if (check == false) 
        {
            cout << "Cannot found." << endl;
        }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &name,vector<int> &score,vector<char> &grade,string &key){
    const char *x = key.c_str();
    bool check = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < name.size(); i++)
    {   
        if(*x == grade.at(i)) {
        check = true;
        cout << name.at(i) << " (" << score.at(i) <<")" << endl;
        }
    }   
        if (check == false) 
        {
            cout << "Cannot found." << endl;
        }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
