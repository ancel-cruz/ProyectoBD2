#include "btree.h"

btree::btree() {
    this->root = nullptr;
    this->t = 2;
}

void btree::traverse() {
    if (root != nullptr) {
        root->traverse();
    }
}

// Insertion operation
void btree::insertion(int k, idata* &reg) {
    if (root == nullptr) {
        root = new bnode(t, true);
        root->keys.first[0] = k;
        root->n = 1;
    }else{
        if (root->n == 2 * t - 1) {
            bnode *s = new bnode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys.first[0] < k) {
                i++;
            }
            s->C[i]->insertNonFull(k);
            root = s;
        }else {
            root->insertNonFull(k);
        }
    }
}

// Delete Operation
void btree::deletion(int k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }
    root->deletion(k);
    if (root->n == 0) {
        bnode *tmp = root;
        if (root->leaf) {
            root = nullptr;
        }else {
            root = root->C[0];
        }
        delete tmp;
    }
    return;
}

void btree::get_info_btree(){
    cout<<"Root: "<<*(this->root->keys.first)<<endl;
}

void btree::set_types(types* type_data_, int total){
    this->type_data = new types[total];
    for (int i=0; i<total; i++) {
        this->type_data[i]=type_data_[i];
    }
}

void btree::get_set_types(int total){
    types* types_data = new types[total];
    for (int i=0; i<total; i++) {
        this->show_types();
        int i_type;
        cout<<"Tipo de Dato "<<i+1<<": "; cin>>i_type;
        //type_data[i] = types[i_type];
    }
    
}

void btree::read_file(string url){
    int count=0;
    cout<<"Read data"<<endl;
    ifstream myFile;
    myFile.open(url);
    string line, word;
    getline(myFile,line);
    stringstream str(line);
    getline(str,word,','); // reaad first line..
    while (getline(myFile,line)) {
        stringstream str2(line);
        idata* reg = new idata;
        int itype = 0;
        while (getline(str2,word,',')) {
            void* pv;
            cout<<word<<endl;
            if (0==type_data[itype]) { //type_int
                int* tmp = new int{stoi(word)}; pv = tmp;
            }
            else if (1==type_data[itype]){ //type_float
                float* tmp = new float{stof(word)}; pv = tmp;
            }
            else if (2==type_data[itype]){ //type_double
                double* tmp = new double{stod(word)}; pv = tmp;
            }
            else if (3==type_data[itype]){ //type_bool
                bool* tmp = new bool{istringstream(word)}; pv = tmp;
            }
            else if (4==type_data[itype]){ //type_pchar
                char* tmp = new char[25]; strcpy(tmp, word.c_str()); pv = tmp;
            }
            else if (5==type_data[itype]){ //type_str
                string* tmp = new string{word}; pv = tmp;
            }
            //reg->data.push_back(pv);
            
            itype++;
        }
        
        this->insertion(++count, reg);
        cout<<endl;
    }
    cout<<"count: "<<count<<endl;
    myFile.close();
}

void btree::show_types(){
    cout<<"mostrar tipos de datos"<<endl;
    
}

