#include "BTree.h"
#ifndef PROJECT_TABLE_H
#define PROJECT_TABLE_H
#include "vector"
#include "Hashing.h"
class Table{
public:
    string name;
    int columnNumbers;
    vector<vector<string>> nameTypeList;
    vector<int> copysOfId;
    vector<Node> selectAnswerBeforeSort;
    BTree *btrees;
    string hashtable[999999];
    int idlist[500];
    Table(){
        for (int i = 0; i < 25; ++i)
            hashtable[i] = '0'+i;
    }
    int getId(){
        for (int i = 1; i < 500; ++i) {
            if(idlist[i] == 0) {
                idlist[i] = 1;
                return i;
            }
        }
        return -1;
    }
    void BTreeNodeTraverseForDeletion(int ind, BTreeNode *btn,int op, int rightside){
        int i;
        for (i = 0; i < btn->n; i++) {
            if (btn->leaf == false)
                BTreeNodeTraverseForDeletion(ind, btn->nextPtr[i], op, rightside);
            if(op == 0){
                if(btn->keys[i].data == rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        btrees[(ind + j)%(columnNumbers+1)].remove(temp);
                        if(btrees[(ind+j)%(columnNumbers+1)].name == "id")
                            idlist[temp2.data] = 0;
                        temp = *(temp2.nextField);
                    }
                    i = 0;
                }
            }
            else if(op == 1){
                if(btn->keys[i].data < rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        btrees[(ind + j)%(columnNumbers+1)].remove(temp);
                        if(btrees[(ind+j)%(columnNumbers+1)].name == "id")
                            idlist[temp2.data] = 0;
                        temp = *(temp2.nextField);
                    }
                    i = 0;
                }
            }
            else if(op == 2){
                if(btn->keys[i].data > rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        btrees[(ind + j)%(columnNumbers+1)].remove(temp);
                        if(btrees[(ind+j)%(columnNumbers+1)].name == "id")
                            idlist[temp2.data] = 0;
                        temp = *(temp2.nextField);
                    }
                    i = 0;
                }
            }
        }
        if (btn->leaf == false) {
            BTreeNodeTraverseForDeletion(ind, btn->nextPtr[i], op, rightside);
        }
    }
    void btreeTraverseForDeletion(int ind, int op, int rightside) {
        if (btrees[ind].root != NULL)
            BTreeNodeTraverseForDeletion(ind, btrees[ind].root, op, rightside);
    }
    void BTreeNodeTraverseForDeletionAnd(int ind, BTreeNode *btn,int op, int rightside,int ind2,int op2, int rightside2){
        int i;
        for (i = 0; i < btn->n; i++) {
            if (btn->leaf == false)
                BTreeNodeTraverseForDeletionAnd(ind, btn->nextPtr[i], op, rightside, ind2, op2, rightside2);
            if(op == 0){
                if(btn->keys[i].data == rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int hazf = 0;
                        if( ((ind + j)%(columnNumbers+1)) == ind2 ){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    hazf = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    hazf = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    hazf = 1;
                            }
                        }
                        if(hazf == 1){
                            Node tempSecond = btn->keys[i];
                            for (int b = 0; b < columnNumbers+1; ++b) {
                                Node tempSecond2 = tempSecond;
                                btrees[(ind + b)%(columnNumbers+1)].remove(tempSecond);
                                if(btrees[(ind+b)%(columnNumbers+1)].name == "id")
                                    idlist[tempSecond2.data] = 0;
                                tempSecond = *(tempSecond2.nextField);
                            }
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
            else if(op == 1){
                if(btn->keys[i].data < rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int hazf = 0;
                        if( ((ind + j)%(columnNumbers+1)) == ind2 ){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    hazf = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    hazf = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    hazf = 1;
                            }
                        }
                        if(hazf == 1){
                            Node tempSecond = btn->keys[i];
                            for (int b = 0; b < columnNumbers+1; ++b) {
                                Node tempSecond2 = tempSecond;
                                btrees[(ind + b)%(columnNumbers+1)].remove(tempSecond);
                                if(btrees[(ind+b)%(columnNumbers+1)].name == "id")
                                    idlist[tempSecond2.data] = 0;
                                tempSecond = *(tempSecond2.nextField);
                            }
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
            else if(op == 2){
                if(btn->keys[i].data > rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int hazf = 0;
                        if( ((ind + j)%(columnNumbers+1)) == ind2 ){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    hazf = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    hazf = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    hazf = 1;
                            }
                        }
                        if(hazf == 1){
                            Node tempSecond = btn->keys[i];
                            for (int b = 0; b < columnNumbers+1; ++b) {
                                Node tempSecond2 = tempSecond;
                                btrees[(ind + b)%(columnNumbers+1)].remove(tempSecond);
                                if(btrees[(ind+b)%(columnNumbers+1)].name == "id")
                                    idlist[tempSecond2.data] = 0;
                                tempSecond = *(tempSecond2.nextField);
                            }
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
        }
        if (btn->leaf == false) {
            BTreeNodeTraverseForDeletionAnd(ind, btn->nextPtr[i], op, rightside,ind2, op2, rightside2);
        }
    }
    void btreeTraverseForDeletionAnd(int ind, int op, int rightside,int ind2, int op2, int rightside2) {
        if (btrees[ind].root != NULL && btrees[ind2].root != NULL)
            BTreeNodeTraverseForDeletionAnd(ind, btrees[ind].root, op, rightside,ind2, op2, rightside2);
    }
    void BTreeNodeTraverseForUpdate(int ind, BTreeNode *btn,int updateList[], int op, int rightside){
        int i;
        for (i = 0; i < btn->n; i++) {
            if (btn->leaf == false)
                BTreeNodeTraverseForUpdate(ind, btn->nextPtr[i], updateList, op, rightside);
            if(op == 0){
                if(btn->keys[i].data == rightside) {
                    int updateIdFounderIndex = 0;
                    Node temp = btn->keys[i];
                    while(btrees[(ind + updateIdFounderIndex)%(columnNumbers+1)].name != "id"){
                        temp = *(temp.nextField);
                        updateIdFounderIndex++;
                    }
                    copysOfId.push_back(temp.data);
                    temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        btrees[(ind + j)%(columnNumbers+1)].remove(temp);
                        if(btrees[(ind+j)%(columnNumbers+1)].name == "id")
                            idlist[temp2.data] = 0;
                        temp = *(temp2.nextField);
                    }
                    i = 0;
                }
            }
            else if(op == 1){

                if(btn->keys[i].data < rightside) {
                    int updateIdFounderIndex = 0;
                    Node temp = btn->keys[i];
                    while(btrees[(ind + updateIdFounderIndex)%(columnNumbers+1)].name != "id"){
                        temp = *(temp.nextField);
                        updateIdFounderIndex++;
                    }
                    copysOfId.push_back(temp.data);
                    temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        btrees[(ind + j)%(columnNumbers+1)].remove(temp);
                        if(btrees[(ind+j)%(columnNumbers+1)].name == "id")
                            idlist[temp2.data] = 0;
                        temp = *(temp2.nextField);
                    }
                    i = 0;
                }
            }
            else if(op == 2){
                if(btn->keys[i].data > rightside) {
                    int updateIdFounderIndex = 0;
                    Node temp = btn->keys[i];
                    while(btrees[(ind + updateIdFounderIndex)%(columnNumbers+1)].name != "id"){
                        temp = *(temp.nextField);
                        updateIdFounderIndex++;
                    }
                    copysOfId.push_back(temp.data);
                    temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        btrees[(ind + j)%(columnNumbers+1)].remove(temp);
                        if(btrees[(ind+j)%(columnNumbers+1)].name == "id")
                            idlist[temp2.data] = 0;
                        temp = *(temp2.nextField);
                    }
                    i = 0;
                }
            }
        }
        if (btn->leaf == false)
            BTreeNodeTraverseForUpdate(ind, btn->nextPtr[i], updateList, op, rightside);
    }
    void btreeTraverseForUpdate(int ind, int updateList[], int op, int rightside) {
        if (btrees[ind].root != NULL)
            BTreeNodeTraverseForUpdate(ind, btrees[ind].root, updateList, op, rightside);
    }
    void BTreeNodeTraverseForUpdateAnd(int ind, BTreeNode *btn,int updateList[], int op, int rightside,int ind2, int op2, int rightside2){
        int i;
        for (i = 0; i < btn->n; i++) {
            if (btn->leaf == false)
                BTreeNodeTraverseForUpdateAnd(ind, btn->nextPtr[i], updateList, op, rightside,ind2, op2, rightside2);
            if(op == 0){
                if(btn->keys[i].data == rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int uphazf = 0;
                        if( ((ind+j)%(columnNumbers+1)) == ind2){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    uphazf = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    uphazf = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    uphazf = 1;
                            }
                        }
                        if(uphazf == 1){
                            Node tempSecond = btn->keys[i];
                            for (int b = 0; b < columnNumbers+1; ++b) {
                                if(btrees[(ind+b)%(columnNumbers+1)].name == "id") {
                                    idlist[tempSecond.data] = 0;
                                    copysOfId.push_back(tempSecond.data);
                                }
                                Node tempSecond2 = tempSecond;
                                btrees[(ind + b)%(columnNumbers+1)].remove(tempSecond);
                                tempSecond = *(tempSecond2.nextField);
                            }
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
            else if(op == 1){
                if(btn->keys[i].data < rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int uphazf = 0;
                        if( ((ind+j)%(columnNumbers+1)) == ind2){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    uphazf = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    uphazf = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    uphazf = 1;
                            }
                        }
                        if(uphazf == 1){
                            Node tempSecond = btn->keys[i];
                            for (int b = 0; b < columnNumbers+1; ++b) {
                                if(btrees[(ind+b)%(columnNumbers+1)].name == "id") {
                                    idlist[tempSecond.data] = 0;
                                    copysOfId.push_back(tempSecond.data);
                                }
                                Node tempSecond2 = tempSecond;
                                btrees[(ind + b)%(columnNumbers+1)].remove(tempSecond);
                                tempSecond = *(tempSecond2.nextField);
                            }
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
            else if(op == 2){
                if(btn->keys[i].data > rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int uphazf = 0;
                        if( ((ind+j)%(columnNumbers+1)) == ind2){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    uphazf = 1;
                            }else if(op2 == 1){

                                if(temp.data < rightside2)
                                    uphazf = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    uphazf = 1;
                            }
                        }
                        if(uphazf == 1){
                            cout<<"done"<<endl;
                            Node tempSecond = btn->keys[i];
                            for (int b = 0; b < columnNumbers+1; ++b) {
                                if(btrees[(ind+b)%(columnNumbers+1)].name == "id") {
                                    idlist[tempSecond.data] = 0;
                                    copysOfId.push_back(tempSecond.data);
                                }
                                Node tempSecond2 = tempSecond;
                                btrees[(ind + b)%(columnNumbers+1)].remove(tempSecond);
                                tempSecond = *(tempSecond2.nextField);
                            }
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
        }
        if (btn->leaf == false)
            BTreeNodeTraverseForUpdateAnd(ind, btn->nextPtr[i], updateList, op, rightside,ind2, op2, rightside2);
    }
    void btreeTraverseForUpdateAnd(int ind, int updateList[], int op, int rightside, int ind2, int op2, int rightside2) {
        if (btrees[ind].root != NULL && btrees[ind2].root != NULL)
            BTreeNodeTraverseForUpdateAnd(ind, btrees[ind].root, updateList, op, rightside, ind2, op2, rightside2);
    }
    void BTreeNodeTraverseForSelect(int ind, BTreeNode *btn,vector<string> selectTreeList, int op, int rightside){
        int i;
        for (i = 0; i < btn->n; i++) {
            if (btn->leaf == false)
                BTreeNodeTraverseForSelect(ind, btn->nextPtr[i], selectTreeList, op, rightside);
            if(op == 0){
                if(btn->keys[i].data == rightside) {
                    int selectIdFounderIndex = 0;
                    Node temp = btn->keys[i];
                    while(btrees[(ind + selectIdFounderIndex)%(columnNumbers+1)].name != "id"){
                        temp = *(temp.nextField);
                        selectIdFounderIndex++;
                    }
                    int selectSameFlag = 0;
                    for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                        if(temp.data == selectAnswerBeforeSort[k].data)
                            selectSameFlag = 1;
                    }
                    if(selectSameFlag == 0)
                        selectAnswerBeforeSort.push_back(temp);
                }
            }
            else if(op == 1){
                if(btn->keys[i].data < rightside) {
                    int selectIdFounderIndex = 0;
                    Node temp = btn->keys[i];
                    while(btrees[(ind + selectIdFounderIndex)%(columnNumbers+1)].name != "id"){
                        temp = *(temp.nextField);
                        selectIdFounderIndex++;
                    }
                    int selectSameFlag = 0;
                    for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                        if(temp.data == selectAnswerBeforeSort[k].data)
                            selectSameFlag = 1;
                    }
                    if(selectSameFlag == 0)
                    selectAnswerBeforeSort.push_back(temp);
                }
            }
            else if(op == 2){
                if(btn->keys[i].data > rightside) {
                    int selectIdFounderIndex = 0;
                    Node temp = btn->keys[i];
                    while(btrees[(ind + selectIdFounderIndex)%(columnNumbers+1)].name != "id"){
                        temp = *(temp.nextField);
                        selectIdFounderIndex++;
                    }
                    int selectSameFlag = 0;
                    for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                        if(temp.data == selectAnswerBeforeSort[k].data)
                            selectSameFlag = 1;
                    }
                    if(selectSameFlag == 0)
                    selectAnswerBeforeSort.push_back(temp);
                }
            }
        }
        if (btn->leaf == false)
            BTreeNodeTraverseForSelect(ind, btn->nextPtr[i], selectTreeList, op, rightside);
    }
    void btreeTraverseForSelect(int ind, vector<string> selectTreeList, int op, int rightside) {
        if (btrees[ind].root != NULL)
            BTreeNodeTraverseForSelect(ind, btrees[ind].root, selectTreeList, op, rightside);
    }
    void BTreeNodeTraverseForSelectAnd(int ind, BTreeNode *btn,vector<string> selectTreeList, int op, int rightside,int ind2, int op2, int rightside2){
        int i;
        for (i = 0; i < btn->n; i++) {
            if (btn->leaf == false)
                BTreeNodeTraverseForSelectAnd(ind, btn->nextPtr[i], selectTreeList, op, rightside, ind2, op2, rightside2);
            if(op == 0){
                if(btn->keys[i].data == rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int selectFlag = 0;
                        if( ((ind+j)%(columnNumbers+1)) == ind2){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    selectFlag = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    selectFlag = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    selectFlag = 1;
                            }
                        }
                        if(selectFlag == 1){
                            temp = btn->keys[i];
                            int selectIdFounderIndex = 0;
                            while(btrees[(ind + selectIdFounderIndex)%(columnNumbers+1)].name != "id"){
                                temp = *(temp.nextField);
                                selectIdFounderIndex++;
                            }
                            int selectSameFlag = 0;
                            for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                                if(temp.data == selectAnswerBeforeSort[k].data)
                                    selectSameFlag = 1;
                            }
                            if(selectSameFlag == 0)
                                selectAnswerBeforeSort.push_back(temp);
                            break;
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
            else if(op == 1){
                if(btn->keys[i].data < rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int selectFlag = 0;
                        if( ((ind+j)%(columnNumbers+1)) == ind2){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    selectFlag = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    selectFlag = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    selectFlag = 1;
                            }
                        }
                        if(selectFlag == 1){
                            temp = btn->keys[i];
                            int selectIdFounderIndex = 0;
                            while(btrees[(ind + selectIdFounderIndex)%(columnNumbers+1)].name != "id"){
                                temp = *(temp.nextField);
                                selectIdFounderIndex++;
                            }
                            int selectSameFlag = 0;
                            for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                                if(temp.data == selectAnswerBeforeSort[k].data)
                                    selectSameFlag = 1;
                            }
                            if(selectSameFlag == 0)
                                selectAnswerBeforeSort.push_back(temp);
                            break;
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
            else if(op == 2){
                if(btn->keys[i].data > rightside) {
                    Node temp = btn->keys[i];
                    for (int j = 0; j < columnNumbers+1; ++j) {
                        Node temp2 = temp;
                        int selectFlag = 0;
                        if( ((ind+j)%(columnNumbers+1)) == ind2){
                            if(op2 == 0){
                                if(temp.data == rightside2)
                                    selectFlag = 1;
                            }else if(op2 == 1){
                                if(temp.data < rightside2)
                                    selectFlag = 1;
                            }else if(op2 == 2){
                                if(temp.data > rightside2)
                                    selectFlag = 1;
                            }
                        }
                        if(selectFlag == 1){
                            temp = btn->keys[i];
                            int selectIdFounderIndex = 0;
                            while(btrees[(ind + selectIdFounderIndex)%(columnNumbers+1)].name != "id"){
                                temp = *(temp.nextField);
                                selectIdFounderIndex++;
                            }
                            int selectSameFlag = 0;
                            for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                                if(temp.data == selectAnswerBeforeSort[k].data)
                                    selectSameFlag = 1;
                            }
                            if(selectSameFlag == 0)
                                selectAnswerBeforeSort.push_back(temp);
                            break;
                        }
                        temp = *(temp2.nextField);
                    }
                }
            }
        }
        if (btn->leaf == false)
            BTreeNodeTraverseForSelectAnd(ind, btn->nextPtr[i], selectTreeList, op, rightside, ind2, op2, rightside2);
    }
    void btreeTraverseForSelectAnd(int ind, vector<string> selectTreeList, int op, int rightside, int ind2, int op2, int rightside2) {
        if (btrees[ind].root != NULL && btrees[ind2].root != NULL)
            BTreeNodeTraverseForSelectAnd(ind, btrees[ind].root, selectTreeList, op, rightside,ind2, op2, rightside2);
    }
    void checkInputType(string input, string type){
    if(type == "string"){
        input = input.substr(1, input.length()-2);
        if(!isalpha(input[0])){
            cout << "Input must start with a letter" << endl;            
        }    
        else {
            for(int i = 1; i < input.length(); i++){
                if(!isdigit(input[i])){
                    cout << "Remaining characters must be digits" << endl;
                    return;             
                }
            }
        }    
    }
}
    void insert(string query,int indexOnQuiery){
        Node *mainNodeRecord = new Node[columnNumbers+1];
        string record[columnNumbers];
        int recordIndex = 0;
        for (int j = 0; j < columnNumbers; ++j) {
            mainNodeRecord[j].data = 0;
            mainNodeRecord[j].nextField = NULL;
        }
        int jj = indexOnQuiery;
        while(recordIndex != columnNumbers) {
            while(query[jj] == ' ')
                jj++;
            while(query[jj] != ' ' && query[jj] != ',' && query[jj] != ')'){
                record[recordIndex] += query[jj];
                jj++;
            }
            if(!record[recordIndex].empty())
                recordIndex++;
            if(query[jj] != ')'){
                jj++;
            }else
                break;
        }
        for (int i = 0; i < columnNumbers; ++i) {
            checkInputType(record[i], nameTypeList[i][1]);
        }
        mainNodeRecord[0].data = getId();
        for (int j = 0; j < columnNumbers; ++j) {
            if(nameTypeList[j][1] == "string")
                mainNodeRecord[j+1].data = hashh(record[j]);
            else if(nameTypeList[j][1] == "int")
                mainNodeRecord[j+1].data = stoi(record[j]);
            else if(nameTypeList[j][1] == "timestamp") {
                string year = "", month = "", day = "";
                int timeStringIndex = 0;
                while(record[j][timeStringIndex] != '/'){
                    year += record[j][timeStringIndex];
                    timeStringIndex++;
                    if(timeStringIndex == record[j].length()){
                        cout<<"Invalid timestamp!"<<endl;
                        return;
                    }
                }
                if(year == ""){
                    cout<<"Invalid timestamp!"<<endl;
                    return;
                }
                timeStringIndex++;
                while(record[j][timeStringIndex] != '/'){
                    month += record[j][timeStringIndex];
                    timeStringIndex++;
                    if(timeStringIndex == record[j].length()){
                        cout<<"Invalid timestamp!"<<endl;
                        return;
                    }
                }
                if(month == ""){
                    cout<<"Invalid timestamp!"<<endl;
                    return;
                }
                timeStringIndex++;
                while(timeStringIndex < record[j].length()){
                    day += record[j][timeStringIndex];
                    timeStringIndex++;
                }
                mainNodeRecord[j+1].data = hashTimestamp(year,month,day);
            }
        }
        for (int j = 0; j < columnNumbers+1; ++j) {
            if(j != columnNumbers)
                mainNodeRecord[j].nextField = &mainNodeRecord[j+1];
            else
                mainNodeRecord[j].nextField = &mainNodeRecord[0];
        }
        for (int j = 0; j < columnNumbers; ++j) {
            hashtable[mainNodeRecord[j+1].data] = record[j];
        }
        for (int j = 0; j < columnNumbers+1; ++j) {
            btrees[j].insert(mainNodeRecord[j]);
        }
    }
    void del(string conditionColumnLeft, int opt, string conditionColumnRight){
        for (int j = 0; j < columnNumbers; ++j) {
            if(btrees[j+1].name == conditionColumnLeft){
                if(btrees[j+1].type == "int") {
                    btreeTraverseForDeletion(j+1, opt, stoi(conditionColumnRight));
                    btreeTraverseForDeletion(j+1, opt, stoi(conditionColumnRight));
                }else if(btrees[j+1].type == "string") {
                    int ar = hashh(conditionColumnRight), flag2 = 0;
                    btreeTraverseForDeletion(j+1, opt, ar);
                    btreeTraverseForDeletion(j+1, opt, ar);
                }else if(btrees[j+1].type == "timestamp") {
                    string year = "", month = "", day = "";
                    int timeStringIndex = 0, flag2 = 0;
                    while(conditionColumnRight[timeStringIndex] != '/'){
                        year += conditionColumnRight[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while(conditionColumnRight[timeStringIndex] != '/'){
                        month += conditionColumnRight[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while(timeStringIndex < conditionColumnRight.length()){
                        day += conditionColumnRight[timeStringIndex];
                        timeStringIndex++;
                    }
                    btreeTraverseForDeletion(j+1, opt, hashTimestamp(year, month, day));
                    btreeTraverseForDeletion(j+1, opt, hashTimestamp(year, month, day));
                }
                break;
            }
        }
    }
    void delAnd(string conditionColumnLeft, int opt, string conditionColumnRight,
                 string conditionColumnLeft2, int opt2, string conditionColumnRight2){
        int hashedConditionRightside = 0, hashedConditionRightside2 = 0;
        for (int j = 0; j < columnNumbers; ++j) {
            if(btrees[j+1].name == conditionColumnLeft){
                for (int i = 0; i < columnNumbers; ++i) {
                    if(btrees[i+1].name == conditionColumnLeft2){
                        if(btrees[j+1].type == "int")
                            hashedConditionRightside = stoi(conditionColumnRight);
                        else if(btrees[j+1].type == "string")
                            hashedConditionRightside = hashh(conditionColumnRight);
                        else if(btrees[j+1].type == "timestamp") {
                            string year = "", month = "", day = "";
                            int timeStringIndex = 0;
                            while(conditionColumnRight[timeStringIndex] != '/'){
                                year += conditionColumnRight[timeStringIndex];
                                timeStringIndex++;
                            }
                            timeStringIndex++;
                            while(conditionColumnRight[timeStringIndex] != '/'){
                                month += conditionColumnRight[timeStringIndex];
                                timeStringIndex++;
                            }
                            timeStringIndex++;
                            while(timeStringIndex < conditionColumnRight.length()){
                                day += conditionColumnRight[timeStringIndex];
                                timeStringIndex++;
                            }
                            hashedConditionRightside = hashTimestamp(year, month, day);
                        }
                        if(btrees[i+1].type == "int")
                            hashedConditionRightside2 = stoi(conditionColumnRight2);
                        else if(btrees[i+1].type == "string")
                            hashedConditionRightside2 = hashh(conditionColumnRight2);
                        else if(btrees[i+1].type == "timestamp") {
                            string year = "", month = "", day = "";
                            int timeStringIndex = 0;
                            while(conditionColumnRight2[timeStringIndex] != '/'){
                                year += conditionColumnRight2[timeStringIndex];
                                timeStringIndex++;
                            }
                            timeStringIndex++;
                            while(conditionColumnRight2[timeStringIndex] != '/'){
                                month += conditionColumnRight2[timeStringIndex];
                                timeStringIndex++;
                            }
                            timeStringIndex++;
                            while(timeStringIndex < conditionColumnRight.length()){
                                day += conditionColumnRight2[timeStringIndex];
                                timeStringIndex++;
                            }
                            hashedConditionRightside2 = hashTimestamp(year, month, day);
                        }
                        btreeTraverseForDeletionAnd(j+1, opt, hashedConditionRightside,i+1, opt2, hashedConditionRightside2);
                        btreeTraverseForDeletionAnd(j+1, opt, hashedConditionRightside,i+1, opt2, hashedConditionRightside2);
                        break;
                    }
                }
            }
        }
    }
    void updateHelper(string updateConditionLeft, string updateRecord[],int hashedUpdateRecord[], int updateOpt, int hashedUpdateConditionRightside){
        for (int j = 0; j < columnNumbers+1; ++j) {
            if(btrees[j].name == updateConditionLeft){
                btreeTraverseForUpdate(j, hashedUpdateRecord, updateOpt, hashedUpdateConditionRightside);
                btreeTraverseForUpdate(j, hashedUpdateRecord, updateOpt, hashedUpdateConditionRightside);
                while(!copysOfId.empty()){
                    int copysOfIdSize = copysOfId.size();
                    Node *updateNode = new Node[columnNumbers+1];
                    updateNode[0].data = copysOfId[copysOfIdSize-1];
                    copysOfId.pop_back();
                    for (int k = 0; k < columnNumbers; ++k) {
                        updateNode[k+1].data = hashedUpdateRecord[k];
                    }
                    for (int k = 0; k < columnNumbers+1; ++k) {
                        if(k != columnNumbers)
                            updateNode[k].nextField = &updateNode[k+1];
                        else
                            updateNode[k].nextField = &updateNode[0];
                    }
                    for (int k = 0; k < columnNumbers; ++k) {
                        hashtable[updateNode[k+1].data] = updateRecord[k];
                    }
                    for (int k = 0; k < columnNumbers+1; ++k) {
                        btrees[k].insert(updateNode[k]);
                    }
                }
                break;
            }
        }
    }
    void updateHelperAnd(string updateConditionLeft, string updateRecord[],int hashedUpdateRecord[], int updateOpt, int hashedUpdateConditionRightside,
                           string updateConditionLeft2, int updateOpt2, int hashedUpdateConditionRightside2){
        for (int j = 0; j < columnNumbers+1; ++j) {
            if(btrees[j].name == updateConditionLeft){
                for (int i = 0; i < columnNumbers+1; ++i) {
                    if(btrees[i].name == updateConditionLeft2){
                        btreeTraverseForUpdateAnd(j, hashedUpdateRecord, updateOpt, hashedUpdateConditionRightside, i, updateOpt2, hashedUpdateConditionRightside2);
                        btreeTraverseForUpdateAnd(j, hashedUpdateRecord, updateOpt, hashedUpdateConditionRightside, i, updateOpt2, hashedUpdateConditionRightside2);
                        while(!copysOfId.empty()){
                            int copysOfIdSize = copysOfId.size();
                            Node *updateNode = new Node[columnNumbers+1];
                            updateNode[0].data = copysOfId[copysOfIdSize-1];
                            copysOfId.pop_back();
                            for (int k = 0; k < columnNumbers; ++k) {
                                updateNode[k+1].data = hashedUpdateRecord[k];
                            }
                            for (int k = 0; k < columnNumbers+1; ++k) {
                                if(k != columnNumbers)
                                    updateNode[k].nextField = &updateNode[k+1];
                                else
                                    updateNode[k].nextField = &updateNode[0];
                            }
                            for (int k = 0; k < columnNumbers; ++k) {
                                hashtable[updateNode[k+1].data] = updateRecord[k];
                            }
                            for (int k = 0; k < columnNumbers+1; ++k) {
                                btrees[k].insert(updateNode[k]);
                            }
                        }
                        break;
                    }
                }

            }
        }
    }
    void update(string query, int updateIndex) {
        int recordCounter = 0, updateRecordInx = 0, updateOpt = 0, updateOpt2 = 0;
        string updateRecord[columnNumbers];
        string updateConditionLeft = "", updateConditionRight = "",
                updateConditionLeft2 = "", updateConditionRight2 = "",
                updateConditionCombination = "";
        while (recordCounter < columnNumbers) {
            while (query[updateIndex] == ' ')
                updateIndex++;
            while (query[updateIndex] != ' ' && query[updateIndex] != ',' && query[updateIndex] != ')') {
                updateRecord[updateRecordInx] += query[updateIndex];
                updateIndex++;
            }
            while (query[updateIndex] == ' ')
                updateIndex++;
            recordCounter++;
            updateRecordInx++;
            if (query[updateIndex] == ',')
                updateIndex++;
            else
                break;
        }
        if (query[updateIndex] != ')') {
            cout << "Syntax ERROR!" << endl;
            return;
        }
        updateIndex++;
        while (query[updateIndex] == ' ')
            updateIndex++;
        string updateSyntaxTmp = "";
        while (query[updateIndex] != ' ') {
            updateSyntaxTmp += query[updateIndex];
            updateIndex++;
        }
        if (updateSyntaxTmp != "WHERE") {
            cout << "Syntax ERROR!" << endl;
            return;
        }
        while (query[updateIndex] == ' ')
            updateIndex++;
        while (query[updateIndex] != '=' && query[updateIndex] != '>' && query[updateIndex] != '<') {
            updateConditionLeft += query[updateIndex];
            updateIndex++;
            if (updateIndex == query.length()) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
        }
        if (query[updateIndex] == '=') {
            if (query[updateIndex + 1] != '=') {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            updateOpt = 0;
            updateIndex += 2;
            while (query[updateIndex] != ' ' && updateIndex < query.length()) {
                updateConditionRight += query[updateIndex];
                updateIndex++;
            }
        } else if (query[updateIndex] == '<') {
            updateOpt = 1;
            updateIndex++;
        } else if (query[updateIndex] == '>') {
            updateOpt = 2;
            updateIndex++;
        }
        while ((query[updateIndex] != ' ') && (updateIndex < query.length())) {
            updateConditionRight += query[updateIndex];
            updateIndex++;
        }
        if (query[updateIndex] == ' ') {
            while (query[updateIndex] == ' ')
                updateIndex++;
            updateConditionCombination = query[updateIndex];
            updateIndex++;
            while (query[updateIndex] == ' ')
                updateIndex++;
            while (query[updateIndex] != ' ' && query[updateIndex] != '=' && query[updateIndex] != '>' &&
                   query[updateIndex] != '<') {
                updateConditionLeft2 += query[updateIndex];
                updateIndex++;
            }
            while (query[updateIndex] == ' ')
                updateIndex++;
            if (query[updateIndex] == '=') {
                if (query[updateIndex + 1] != '=') {
                    cout << "Syntax ERROR!" << endl;
                    return;
                }
                updateOpt2 = 0;
                updateIndex += 2;
            } else if (query[updateIndex] == '>') {
                updateOpt2 = 2;
                updateIndex += 1;
            } else if (query[updateIndex] == '<') {
                updateOpt2 = 1;
                updateIndex += 1;
            }
            while (updateIndex < query.length()) {
                updateConditionRight2 += query[updateIndex];
                updateIndex++;
            }
        }
        int hashedUpdateRecord[columnNumbers];
        int hashedUpdateConditionRightside = 0, hashedUpdateConditionRightside2 = 0;
        for (int j = 0; j < columnNumbers; ++j) {
            if (nameTypeList[j][1] == "int")
                hashedUpdateRecord[j] = stoi(updateRecord[j]);
            else if (nameTypeList[j][1] == "string")
                hashedUpdateRecord[j] = hashh(updateRecord[j]);
            else if (nameTypeList[j][1] == "timestamp") {
                string year = "", month = "", day = "";
                int timeStringIndex = 0;
                while (updateRecord[j][timeStringIndex] != '/') {
                    year += updateRecord[j][timeStringIndex];
                    timeStringIndex++;
                }
                timeStringIndex++;
                while (updateRecord[j][timeStringIndex] != '/') {
                    month += updateRecord[j][timeStringIndex];
                    timeStringIndex++;
                }
                timeStringIndex++;
                while (timeStringIndex < updateRecord[j].length()) {
                    day += updateRecord[j][timeStringIndex];
                    timeStringIndex++;
                }
                hashedUpdateRecord[j] = hashTimestamp(year, month, day);
            }
        }
        for (int j = 0; j < columnNumbers+1; ++j) {
            if (btrees[j].name == updateConditionLeft) {
                if (btrees[j].type == "int")
                    hashedUpdateConditionRightside = stoi(updateConditionRight);
                else if (btrees[j].type == "string")
                    hashedUpdateConditionRightside = hashh(updateConditionRight);
                else if (btrees[j].type == "timestamp") {
                    string year = "", month = "", day = "";
                    int timeStringIndex = 0;
                    while (updateConditionRight[timeStringIndex] != '/') {
                        year += updateConditionRight[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while (updateConditionRight[timeStringIndex] != '/') {
                        month += updateConditionRight[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while (timeStringIndex < updateConditionRight.length()) {
                        day += updateConditionRight[timeStringIndex];
                        timeStringIndex++;
                    }
                    hashedUpdateConditionRightside = hashTimestamp(year, month, day);
                }

            }
        }
        for (int j = 0; j < columnNumbers+1; ++j) {
            if (btrees[j].name == updateConditionLeft2) {
                if (btrees[j].type == "int")
                    hashedUpdateConditionRightside2 = stoi(updateConditionRight2);
                else if (btrees[j].type == "string")
                    hashedUpdateConditionRightside2 = hashh(updateConditionRight2);
                else if (btrees[j].type == "timestamp") {
                    string year = "", month = "", day = "";
                    int timeStringIndex = 0;
                    while (updateConditionRight2[timeStringIndex] != '/') {
                        year += updateConditionRight2[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while (updateConditionRight2[timeStringIndex] != '/') {
                        month += updateConditionRight2[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while (timeStringIndex < updateConditionRight2.length()) {
                        day += updateConditionRight2[timeStringIndex];
                        timeStringIndex++;
                    }
                    hashedUpdateConditionRightside2 = hashTimestamp(year, month, day);
                }
            }
        }
        if (updateConditionCombination == "|") {
            updateHelper(updateConditionLeft, updateRecord, hashedUpdateRecord, updateOpt,
                          hashedUpdateConditionRightside);
            updateHelper(updateConditionLeft2, updateRecord, hashedUpdateRecord, updateOpt2,
                          hashedUpdateConditionRightside2);
        }else if(updateConditionCombination == "&"){
            updateHelperAnd(updateConditionLeft, updateRecord, hashedUpdateRecord, updateOpt, hashedUpdateConditionRightside,
                          updateConditionLeft2, updateOpt2, hashedUpdateConditionRightside2);
        }else if(updateConditionCombination == "")
            updateHelper(updateConditionLeft, updateRecord, hashedUpdateRecord, updateOpt,
                          hashedUpdateConditionRightside);
    }
    void selectHelper(string selectConditionLeftside, int selectOpt, string selectConditionRightside, vector<string> selectList){
        for (int j = 0; j < columnNumbers; ++j) {
            if(btrees[j+1].name == selectConditionLeftside){
                int hashedSelectConditionRightside = 0;
                if(btrees[j+1].type == "int"){
                    hashedSelectConditionRightside = stoi(selectConditionRightside);
                }if(btrees[j+1].type == "string"){
                    hashedSelectConditionRightside = hashh(selectConditionRightside);
                }else if(btrees[j+1].type == "timestamp"){
                    string year = "", month = "", day = "";
                    int timeStringIndex = 0;
                    while(selectConditionRightside[timeStringIndex] != '/'){
                        year += selectConditionRightside[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while(selectConditionRightside[timeStringIndex] != '/'){
                        month += selectConditionRightside[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while(timeStringIndex < selectConditionRightside.length()){
                        day += selectConditionRightside[timeStringIndex];
                        timeStringIndex++;
                    }
                    hashedSelectConditionRightside = hashTimestamp(year,month,day);
                }
                btreeTraverseForSelect(j+1, selectList, selectOpt, hashedSelectConditionRightside);
                for (int q = 0; q < selectAnswerBeforeSort.size()-1; q++) {
                    for (int p = 0; p < selectAnswerBeforeSort.size() - q - 1; p++) {
                        Node tmp;
                        if (selectAnswerBeforeSort[p].data > selectAnswerBeforeSort[p + 1].data) {
                            tmp = selectAnswerBeforeSort[p];
                            selectAnswerBeforeSort[p] = selectAnswerBeforeSort[p + 1];
                            selectAnswerBeforeSort[p + 1] = tmp;
                        }
                    }
                }
                int sifi = 0;
                for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                    Node selectTempAfterSort = selectAnswerBeforeSort[k];
                    for (int l = 0; l < columnNumbers + 1; ++l) {
                        for (int m = 0; m < selectList.size(); ++m) {
                            if(btrees[l%(columnNumbers+1)].name == selectList[m]){
                                if(selectList[m] != "id") {
                                    if (btrees[l%(columnNumbers+1)].type == "string") {
                                        for (int i1 = 1;i1 < hashtable[selectTempAfterSort.data].length() - 1; ++i1) {
                                            cout << hashtable[selectTempAfterSort.data][i1];
                                        }
                                        cout << " ";
                                    }else
                                        cout << hashtable[selectTempAfterSort.data] << " ";
                                }else
                                    cout<<selectTempAfterSort.data<<" ";
                                break;
                            }
                        }
                        selectTempAfterSort = *(selectTempAfterSort.nextField);
                    }
                    cout<<endl;
                }
            }
        }
    }
    void selectHelperAnd(string selectConditionLeftside, int selectOpt, string selectConditionRightside, vector<string> selectList,
                           string selectConditionLeftside2, int selectOpt2, string selectConditionRightside2){
        for (int j = 0; j < columnNumbers; ++j) {
            if(btrees[j+1].name == selectConditionLeftside){
                int hashedSelectConditionRightside = 0;
                if(btrees[j+1].type == "int"){
                    hashedSelectConditionRightside = stoi(selectConditionRightside);
                }if(btrees[j+1].type == "string"){
                    hashedSelectConditionRightside = hashh(selectConditionRightside);
                }else if(btrees[j+1].type == "timestamp"){
                    string year = "", month = "", day = "";
                    int timeStringIndex = 0;
                    while(selectConditionRightside[timeStringIndex] != '/'){
                        year += selectConditionRightside[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while(selectConditionRightside[timeStringIndex] != '/'){
                        month += selectConditionRightside[timeStringIndex];
                        timeStringIndex++;
                    }
                    timeStringIndex++;
                    while(timeStringIndex < selectConditionRightside.length()){
                        day += selectConditionRightside[timeStringIndex];
                        timeStringIndex++;
                    }
                    hashedSelectConditionRightside = hashTimestamp(year,month,day);
                }
                for (int i = 0; i < columnNumbers; ++i) {
                    if(btrees[i+1].name == selectConditionLeftside2){

                        int hashedSelectConditionRightside2 = 0;
                        if(btrees[i+1].type == "int"){
                            hashedSelectConditionRightside2 = stoi(selectConditionRightside2);
                        }if(btrees[i+1].type == "string"){
                            hashedSelectConditionRightside2 = hashh(selectConditionRightside2);
                        }else if(btrees[i+1].type == "timestamp"){
                            string year = "", month = "", day = "";
                            int timeStringIndex = 0;
                            while(selectConditionRightside2[timeStringIndex] != '/'){
                                year += selectConditionRightside2[timeStringIndex];
                                timeStringIndex++;
                            }
                            timeStringIndex++;
                            while(selectConditionRightside2[timeStringIndex] != '/'){
                                month += selectConditionRightside2[timeStringIndex];
                                timeStringIndex++;
                            }
                            timeStringIndex++;
                            while(timeStringIndex < selectConditionRightside2.length()){
                                day += selectConditionRightside2[timeStringIndex];
                                timeStringIndex++;
                            }
                            hashedSelectConditionRightside2 = hashTimestamp(year,month,day);
                        }

                        btreeTraverseForSelectAnd(j+1, selectList, selectOpt, hashedSelectConditionRightside,
                                                          i+1, selectOpt2, hashedSelectConditionRightside2);
                        for (int q = 0; q < selectAnswerBeforeSort.size()-1; q++) {
                            for (int p = 0; p < selectAnswerBeforeSort.size() - q - 1; p++) {
                                Node tmp;
                                if (selectAnswerBeforeSort[p].data > selectAnswerBeforeSort[p + 1].data) {
                                    tmp = selectAnswerBeforeSort[p];
                                    selectAnswerBeforeSort[p] = selectAnswerBeforeSort[p + 1];
                                    selectAnswerBeforeSort[p + 1] = tmp;
                                }
                            }
                        }
                        int sifi = 0;
                        for (int k = 0; k < selectAnswerBeforeSort.size(); ++k) {
                            Node selectTempAfterSort = selectAnswerBeforeSort[k];
                            for (int l = 0; l < columnNumbers + 1; ++l) {
                                for (int m = 0; m < selectList.size(); ++m) {
                                    if(btrees[l%(columnNumbers+1)].name == selectList[m]){
                                        if(selectList[m] != "id") {
                                            if (btrees[l%(columnNumbers+1)].type == "string") {
                                                for (int i1 = 1;i1 < hashtable[selectTempAfterSort.data].length() - 1; ++i1) {
                                                    cout << hashtable[selectTempAfterSort.data][i1];
                                                }
                                                cout << " ";
                                            }else
                                                cout << hashtable[selectTempAfterSort.data] << " ";
                                        }else
                                            cout<<selectTempAfterSort.data<<" ";
                                        break;
                                    }
                                }
                                selectTempAfterSort = *(selectTempAfterSort.nextField);
                            }
                            cout<<endl;
                        }
                    }
                }
            }
        }
    }
    void select(string query){
        vector<string> selectList;
        string selectConditionLeftside = "", selectConditionRightside = "",
               selectConditionCombination = "",
               selectConditionLeftside2 = "", selectConditionRightside2 = "";
        int selectOpt = 0, selectOpt2 = 0, selectIndex = 0;
        while(query[selectIndex] != ' ')
            selectIndex++;
        while(query[selectIndex] == ' ')
            selectIndex++;
        if(query[selectIndex] == '*'){
            for (int j = 0; j < columnNumbers+1; ++j)
                selectList.push_back(btrees[j].name);
            selectIndex++;
        }
        else{
            while(query[selectIndex] == ' ' || query[selectIndex] == '(')
                selectIndex++;
            while(query[selectIndex] != ')'){
                string selectListTmp = "";
                while(query[selectIndex] != ' ' && query[selectIndex] != ',' && query[selectIndex] != ')'){
                    selectListTmp += query[selectIndex];
                    selectIndex++;
                }
                selectList.push_back(selectListTmp);
                while(query[selectIndex] == ' ')
                    selectIndex++;
                if(query[selectIndex] == ','){
                    selectIndex++;
                    while(query[selectIndex] == ' ')
                        selectIndex++;
                }
            }
            selectIndex++;
        }
        while(query[selectIndex] == ' ')
            selectIndex++;
        while(query[selectIndex] != ' ')
            selectIndex++;
        while(query[selectIndex] == ' ')
            selectIndex++;
        while(query[selectIndex] != ' ')
            selectIndex++;
        while(query[selectIndex] == ' ')
            selectIndex++;
        while(query[selectIndex] != ' ')
            selectIndex++;
        while(query[selectIndex] == ' ')
            selectIndex++;
        while(query[selectIndex] != '=' && query[selectIndex] != ' ' && query[selectIndex] != '<' && query[selectIndex] != '>'){
            selectConditionLeftside += query[selectIndex];
            selectIndex++;
        }
        while(query[selectIndex] == ' ')
            selectIndex++;
        if(query[selectIndex] == '='){
            selectOpt = 0;
            selectIndex += 2;
        }else if(query[selectIndex] == '<'){
            selectOpt = 1;
            selectIndex++;
        }else if(query[selectIndex] == '>'){
            selectOpt = 2;
            selectIndex++;
        }
        while(query[selectIndex] == ' ')
            selectIndex++;
        while(query[selectIndex] != ' ' && selectIndex < query.length()){
            selectConditionRightside += query[selectIndex];
            selectIndex++;
        }
        if (query[selectIndex] == ' ') { 
            while (query[selectIndex] == ' ')
                selectIndex++;
            selectConditionCombination = query[selectIndex];
            selectIndex++;
            while (query[selectIndex] == ' ')
                selectIndex++;
            while (query[selectIndex] != ' ' && query[selectIndex] != '=' && query[selectIndex] != '>' &&
                   query[selectIndex] != '<') {
                selectConditionLeftside2 += query[selectIndex];
                selectIndex++;
            }
            while (query[selectIndex] == ' ')
                selectIndex++;
            if (query[selectIndex] == '=') {
                if (query[selectIndex + 1] != '=') {
                    cout << "Syntax ERROR!" << endl;
                    return;
                }
                selectOpt2 = 0;
                selectIndex += 2;
            } else if (query[selectIndex] == '>') {
                selectOpt2 = 2;
                selectIndex += 1;
            } else if (query[selectIndex] == '<') {
                selectOpt2 = 1;
                selectIndex += 1;
            }
            while (selectIndex < query.length()) {
                selectConditionRightside2 += query[selectIndex];
                selectIndex++;
            }
        }
        if(selectConditionCombination == "|"){
            selectAnswerBeforeSort.clear();
            selectHelper(selectConditionLeftside, selectOpt, selectConditionRightside,selectList);
            selectHelper(selectConditionLeftside2, selectOpt2, selectConditionRightside2,selectList);
        }else if(selectConditionCombination == "&"){
            selectAnswerBeforeSort.clear();
            selectHelperAnd(selectConditionLeftside, selectOpt, selectConditionRightside,selectList,
                              selectConditionLeftside2, selectOpt2, selectConditionRightside2);
        }else if(selectConditionCombination == "") {
            selectAnswerBeforeSort.clear();
            selectHelper(selectConditionLeftside, selectOpt, selectConditionRightside,selectList);
        }
    }
    void trv(BTreeNode *tn) {
        int i;
        for (i = 0; i < tn->n; i++) {
            if (tn->leaf == false)
                trv(tn->nextPtr[i]);
            cout<<hashtable[tn->keys[i].data]<<" : "<<hashtable[tn->keys[i].nextField->data]<<", ";
        }
        if (tn->leaf == false)
            trv(tn->nextPtr[i]);
    }
    void print(){
        cout<<"Name of table: "<<name<<endl;
        cout<<endl;
        for (int j = 0; j < columnNumbers+1; ++j) {
            trv(btrees[j].root);
            cout<<endl;
        }
    }
};
#endif //PROJECTTABLEH