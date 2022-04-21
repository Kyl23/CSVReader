#ifndef Gene_Algo_Lib_IO_Reader_CSV
#define Gene_Algo_Lib_IO_Reader_CSV

#include <iostream>
#include <vector>
#include <string>
#include <fstream> //stream

using namespace std;

class CSVReader{
private:
    string pathOfFile;
    char delim = 0;
    string temp,nextLine;
    string buffer;

    ifstream file ;
    vector<string> returnValue;
    vector<vector<string>> returnTable;
    void initBuffer(){
        buffer = "";
    }
    void initVectorAndBuffer(){
        initBuffer();
        returnValue.clear();
    }
    //for t_readLine, help for debug
    bool t_hasNextLine = true;
    string t_temp,t_nextLine;
    vector<string> t_readLine(ifstream &t_File){
        vector<string> t_file;
        string t_buffer;
        try {
            if(t_temp.empty()){
                getline(t_File, t_temp);
                getline(t_File, t_nextLine);
            }
            else{
                t_temp = t_nextLine;
                getline(t_File, t_nextLine);
            }
            if(t_File.eof()) {
                t_hasNextLine = false;
                t_File.close();
            }
            for(auto &i:t_temp){
                if(i == delim){
                    t_file.push_back(t_buffer);
                    t_buffer = "";
                    continue;
                }
                t_buffer += i;
            }
            t_file.push_back(t_buffer);//by last value
        } catch (exception) {
            std::cout << "temporary readLine error";
        }
        return t_file;
    }
public:
    explicit CSVReader(string path,char pattern = ','){
        pathOfFile = path;
        delim = pattern;
        file.open(pathOfFile);
        if(!file.is_open()) std::cout << "can't_file open file";
    }
    bool hasNextLine = true;
    vector<string> readLine(){
        try {
            initVectorAndBuffer();
            if(temp.empty()){
                getline(file, temp);
                getline(file, nextLine);
            }
            else{
                temp = nextLine;
                getline(file, nextLine);
            }
            if(file.eof()) {
                hasNextLine = false;
                file.close();
            }
            for(auto &i:temp){
                if(i == delim){
                    returnValue.push_back(buffer);
                    initBuffer();
                    continue;
                }
                buffer += i;
            }
            returnValue.push_back(buffer);//by last value
        } catch (exception) {
            std::cout << "readLine error";
        }
        return returnValue;
    }
    vector<vector<string>> readTable(){
        try{
            returnTable.clear();
            while(hasNextLine){
                returnTable.push_back(readLine());
            }
        }catch(exception){
            std::cout << "readTable err";
        }
        return returnTable;
    }
    void print(){
        ifstream t_File(pathOfFile);
        while(t_hasNextLine){
            for(auto &i : t_readLine(t_File))
                cout << i << " ";
            cout << endl;
        }
        t_File.close();
    }
};
#endif


