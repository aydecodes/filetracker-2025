#ifndef HEADER_HPP 
#define HEADER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;


template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};
template <typename K, typename V>
class HashMap {
private:
    std::vector<Node<K, V>*> table;
    int capacity;
    int count;

    // djb2 algorithm for string keys hashing
    size_t getHashValue(const std::string& key) const {
        size_t hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash;
    }

    size_t getHashValue(int key) const {
        return static_cast<size_t>(key);
    }

    int getIndex(const K& key) const {
        return getHashValue(key) % capacity;
    }

public:
    
    explicit HashMap(int size = 10) : capacity(size), count(0) {
        table.assign(capacity, nullptr);
    }
    
    ~HashMap() {
        for (int i = 0; i < capacity; ++i) {
            Node<K, V>* current = table[i];
            while (current != nullptr) {
                Node<K, V>* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    
    void insert(const K& key, const V& value) {
        int index = getIndex(key);

        for (Node<K, V>* current = table[index]; current != nullptr; current = current->next) {
            if (current->key == key) {
                current->value = value;
                return;
            }
        }

        Node<K, V>* newNode = new Node<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        count++;
    }

    
    V search(const K& key) const {
        int index = getIndex(key);
        Node<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    
    void remove(const K& key) {
        int index = getIndex(key);
        Node<K, V>* current = table[index];
        Node<K, V>* prev = nullptr;

        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) return;

        if (prev == nullptr) {
            table[index] = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        count--;
    }

    int size() const {
        return count;
    }
};

class TreeNode{
public:
    TreeNode* parent;
    int version_id;
    string content;
    string message;
    time_t created_timestamp;
    time_t snapshot_timestamp;
    vector<TreeNode*> children;

    TreeNode(){
        content = "";
        message = "";
        time(&created_timestamp);
    }
};

class File{
public:
    TreeNode* active_version;
    TreeNode* root;
    HashMap<int, TreeNode*> version_map;
    int total_versions = 0;

public:
    File() {
        root = new TreeNode();
        root->version_id = 0;
        root->content = "";
        root->message = "Root Snapshot";
        time(&root->created_timestamp);
        time(&root->snapshot_timestamp);
        root->parent = nullptr;

        active_version = root; 
        total_versions = 0;
        version_map.insert(0, root); 
    }
    string read(){
        return active_version->content;
    }

    /* TO DEAL WITH VERSION ID*/
    void insert(string to_insert){
        if (active_version->message == ""){
            active_version->content += to_insert;
            return;
        }

        //create a new version (timestamp created together)
        TreeNode* newNode = new TreeNode();

        //assign new version's parent pointer
        newNode->parent = active_version;

        //add the new node as the parent's child
        newNode->parent->children.push_back(newNode);

        //assign the new version as active
        active_version = newNode;
        active_version-> content = to_insert;

        total_versions+=1;
        newNode->version_id = total_versions;

        version_map.insert(total_versions, active_version); 
    }

    void update(string to_update){
        if (active_version->message == ""){
            active_version->content = to_update;
            return;
        }
        insert(to_update);
        return;
    }

    void snapshot(string snapshot_message){
        active_version->message = snapshot_message;
    }

    
    void rollback(int id = 0){
        
        if (id == 0 || id > total_versions){
            if (active_version->parent != nullptr) {
                active_version = active_version->parent;
            } else {
                cout << "No parent version to rollback to." << endl;
            }
            return;
        }

        TreeNode* target = version_map.search(id);
        if (target != nullptr) {
            active_version = target;
        } else {
            cout << "Version not found." << endl;
        }
    }

    //COULDN'T implement the function on time
    void history();
};


class HeapT{
public:
    vector<pair<string, File*>> heap;


    //HEAPIFY FUNCTION for TOTAL VERSIONS
    void heapify(int size, int i){
        //assert(i >= 0 && i < heap.size());

        
        //assert(heap[i].second != nullptr);
        int smallest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;
        
        if (l < size && 
            heap[l].second->active_version != nullptr &&
            heap[smallest].second->active_version != nullptr &&
            heap[l].second->total_versions < heap[smallest].second->total_versions){
            
            smallest = l;
        }
        if (r < size && 
            heap[r].second->active_version != nullptr &&
            heap[smallest].second->active_version != nullptr &&
            heap[r].second->total_versions < heap[smallest].second->total_versions){
            
            smallest = r;
        }

        if (smallest!= i){
            swap(heap[smallest], heap[i]);
            heapify(size, smallest);
        }
        return;
        
    }
    //BUILD HEAP FUNCTION
    void buildHeap(int size){
        for (int i = size/2 - 1; i >= 0; i--){
            heapify(size, i);
        }
        return;
    }

    //HEAPSORT FUNCTION
    void heapSort(int size, int i){
        for (int i = size-1; i>=0; i++){
            swap(heap[0], heap[i]);
            heapify(i, 0);
        }
        return;
    }

    //HEAP INSERTS
    void insert(string name, File* s){
        heap.push_back({name, s});
        

        int current_index = heap.size() -1;
    
        while(current_index!=0){
            int parent_index = (current_index-1)/2;

            if (heap[parent_index].second->total_versions > heap[current_index].second->total_versions){
                swap(heap[parent_index], heap[current_index]);
                current_index = parent_index;
                
                continue;
            }
            break;
        }
    }

    int getSize(){
        return heap.size();
    }


};

class HeapR{
public:
    vector<pair<string, File*>> heap;
    int size = heap.size();

    HeapR(){
        size = heap.size();
    }

    //HEAPIFY FUNCTION for TOTAL VERSIONS
    void heapify(int size, int i){
        //assert(i >= 0 && i < heap.size());

        
        //assert(heap[i].second != nullptr);
        int smallest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;
        
        if (l < size &&
            heap[l].second->active_version != nullptr &&
            heap[smallest].second->active_version != nullptr &&
            heap[l].second->active_version->created_timestamp < heap[smallest].second->active_version->created_timestamp) {
            
            smallest = l;
        }
        
        if (r < size &&
            heap[r].second->active_version != nullptr &&
            heap[smallest].second->active_version != nullptr &&
            heap[r].second->active_version->created_timestamp < heap[smallest].second->active_version->created_timestamp) {
            
            smallest = r;
        }

        if (smallest!= i){
            swap(heap[smallest], heap[i]);
            heapify(size, smallest);
        }
        return;
        
    }
    //BUILD HEAP FUNCTION
    void buildHeap(int size){
        for (int i = size/2 - 1; i >= 0; i--){
            heapify(size, i);
        }
        return;
    }

    //HEAPSORT FUNCTION
    void heapSort(int size, int i){
        for (int i = size-1; i>=0; i++){
            swap(heap[0], heap[i]);
            heapify(i, 0);
        }
        return;
    }

    //HEAP INSERTS
    void insert(string name, File* s){
        heap.push_back({name, s});
        size += 1;

        int current_index = size -1;
    
        while(current_index!=0){
            int parent_index = (current_index-1)/2;

            if (heap[parent_index].second->active_version->created_timestamp > heap[current_index].second->active_version->created_timestamp){
                swap(heap[parent_index], heap[current_index]);
                current_index = parent_index;
                
                continue;
            }
            break;
        }
    }

    int getSize(){
        return size;
    }


};

#endif