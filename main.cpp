#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
#include <sstream>

#include "header.hpp"

using namespace std;

int main(){
    HashMap<string, File*>* files = new HashMap<string, File*>();
    
    cout << "-----WELCOME TO ATHARVA'S FILE SYSTEM-----" << endl << endl;
    HeapR recent_files;
    HeapT biggest_files;
    

    string s;
    
    while(getline(cin, s)){
        istringstream input_command(s);

        string function;
        string filename;

        input_command >> function;

        if (function == "SYSTEM_FILES"){
            //cout << "Segmentation error occuring. \nOriginal code present in cpp file but removed from final submission to prevent crashes." << endl;
            //continue;

            //the following code is my implementation but I couldn't fix errors on time.
            recent_files.buildHeap(recent_files.getSize());
            recent_files.heapSort(recent_files.getSize(), 0);

            for (int i = 0; i < recent_files.getSize(); i ++){
                cout << recent_files.heap[i].first << " " << 
                    recent_files.heap[i].second->active_version->created_timestamp << endl;
            }
            continue;

        }
        if (function == "BIGGEST_FILES"){
            
            //cout << "Segmentation error occuring. \nOriginal code present in cpp file but removed from final submission to prevent crashes." << endl;
            //continue;

            //the following code is my implementation but I couldn't fix errors on time.
            biggest_files.buildHeap(biggest_files.getSize());
            biggest_files.heapSort(biggest_files.getSize(), 0);

            for (int i = 0; i < biggest_files.getSize(); i ++){
                cout << biggest_files.heap[i].first << " " << 
                    biggest_files.heap[i].second->total_versions << endl;
            }
            continue;
        }
        

        if (function == "CREATE"){
            input_command >> filename;
            File* newFile = new File();

            files->insert(filename, newFile);
            recent_files.insert(filename, newFile);
            biggest_files.insert(filename, newFile);
            continue;

        }
        if (function == "READ"){
            input_command >> filename;
            string content;
            File* filePtr = files->search(filename);
            if (filePtr != nullptr) {
                content = filePtr->read();
                cout << content << endl;
            } else {
                cout << "File not found." << endl;
            }
            continue;
        }
        if (function == "INSERT"){
            input_command >> filename;
            string to_insert;
            getline(input_command, to_insert);
            
            

            File* filePtr = files->search(filename);
            if (filePtr != nullptr) {
                filePtr->insert(to_insert);
            } else {
                cout << "File not found." << endl;
            }
            continue;
        }
        if (function == "UPDATE"){
            input_command >> filename;
            string to_update;
            input_command >> to_update;

            File* filePtr = files->search(filename);
            if (filePtr != nullptr) {
                filePtr->update(to_update);
            } else {
                cout << "File not found." << endl;
            }
            continue;
        }
        if (function == "SNAPSHOT"){
            input_command >> filename;
            string message;
            input_command >> message;

            
            File* filePtr = files->search(filename);
            if (filePtr != nullptr) {
                filePtr->snapshot(message);
            } else {
                cout << "File not found." << endl;
            }
            continue;
        }

        if (function == "ROLLBACK"){
            input_command >> filename;

            string version_id;
            input_command >> version_id;

            File* filePtr = files->search(filename);
            if (filePtr == nullptr){
                cout << "File not found." << endl;
                continue;
            }
        
            
            for (char n: version_id){
                if (!isdigit(n)){
                    cout << "Invalid Version!" << endl;
                    continue;
                }
            }
            
            if (version_id.size()!=0){
                (files->search(filename))->rollback(stoi(version_id));
                continue;
            }

            else{
                (files->search(filename))->rollback();
                continue;
            }
        
        }

        if (function == "HISTORY"){
            input_command >> filename;
            continue;
        }

        if (function == "EXIT"){
            cout << "Quitting" << endl;
            break;
        }

        cout << "Invalid command entered." << endl;
        continue;
        
    }
}