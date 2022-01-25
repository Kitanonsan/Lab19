#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

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

void importDataFromFile(string f,vector<string> &n,vector<int> &s,vector<char> &g){
    ifstream source;
    source.open(f);
    string text;
    char name[100];
    int score1,score2,score3,sum;
    while(getline(source,text)){
        const char * ctext = text.c_str();
        sscanf(ctext,"%[^:]: %d %d %d",name,&score1,&score2,&score3);
        n.push_back(name);
        sum = score1 + score2 + score3;
        s.push_back(sum);
        g.push_back(score2grade(sum));
    }
}

void getCommand(string &c,string &k){
    string cm;
    cout << "Please input your command: ";
    getline(cin,cm);
    char command[100];
    char key[100];
    const char *cstr = cm.c_str();
    sscanf(cstr,"%s %[^\n]",command,key);
    c = command;
    k = key;
}

void searchName(vector<string> name,vector<int> score,vector<char> grade,string key){
    int j = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < name.size(); i++){
        string y = toUpperStr(name[i]);
        if(y == key){
            cout << name[i] << "'s " << "score = "<< score[i] << endl;
            cout << name[i] << "'s " << "grade = "<< grade[i] << endl;  
            j = 1;
        }
    }
    if (j == 0){
        cout << "Cannot found.\n";  
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> name,vector<int> score,vector<char> grade,string key){
    int j = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < grade.size(); i++){
        string y(1,grade[i]);
        if(y == key){
            cout << name[i] << " "<< "(" << score[i] << ")" << endl;
            j = 1;
        }
    }
    if (j == 0){
        cout << "Cannot found.\n";
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
