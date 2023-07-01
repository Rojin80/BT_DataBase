#include <iostream>
#include "Table.h"
#include "vector"

using namespace std;

void queryProcess(string s[], int n, int tableNumbers, string createQueries[]){
    Table *tables = new Table[tableNumbers];
    string createSyntaxValidation[2] = {"CREATE", "TABLE"};
    string createTypeValidation[3] = {"string", "int", "timestamp"};
    for (int i = 0; i < tableNumbers; ++i) {
        for (int j = 0; j < createQueries[i].length(); ++j) {
            int createIndex = 0;
            string name = "";
            string syntaxChecker = "";
            vector<vector<string>> nameType;
            vector<string> nameTypeTmp;
            while(createQueries[i][j] != ' ') {
                syntaxChecker += createQueries[i][j];
                j++;
            }
            if(syntaxChecker != createSyntaxValidation[0]){
                cout<<"Syntax ERROR!"<<endl;
                return;
            }
            while(createQueries[i][j] == ' ')
                j++;
            syntaxChecker = "";
            while(createQueries[i][j] != ' ') {
                syntaxChecker += createQueries[i][j];
                j++;
            }
            if(syntaxChecker != createSyntaxValidation[1]){
                cout<<"Syntax ERROR!"<<endl;
                return;
            }
            while(createQueries[i][j] == ' ')
                j++;
            while(createQueries[i][j] != ' '){
                name += createQueries[i][j];
                j++;
            }
            while(createQueries[i][j] == ' ')
                j++;
            if(createQueries[i][j] != '(' || createQueries[i][createQueries[i].length()-1] != ')') {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            j++;
            while(createQueries[i][j] != ')') {
                while (createQueries[i][j] == ' ')
                    j++;
                string nameTypeFirst = "", nameTypeSecond = "";
                while (createQueries[i][j] != ' ') {
                    nameTypeFirst += createQueries[i][j];
                    j++;
                }
                while (createQueries[i][j] == ' ')
                    j++;
                while (createQueries[i][j] != ' ' && createQueries[i][j] != ',' && createQueries[i][j] != ')') {
                    nameTypeSecond += createQueries[i][j];
                    j++;
                }
                if (createQueries[i][j] == ' ') {
                    while (createQueries[i][j] == ' ')
                        j++;
                }
                if (createQueries[i][j] == ',')
                    j++;
                if(nameTypeSecond != "int" && nameTypeSecond != "string" && nameTypeSecond != "timestamp"){
                    cout<<"!!!!!! Syntax ERROR: Invalid data type. !!!!!!!!"<<endl;
                    return;
                }
                nameTypeTmp.clear();
                nameTypeTmp.push_back(nameTypeFirst);
                nameTypeTmp.push_back(nameTypeSecond);
                nameType.push_back(nameTypeTmp);
            }

            tables[i].name = name;
            tables[i].columnNumbers = nameType.size();
            tables[i].nameTypeList = nameType;
            tables[i].btrees = new BTree[tables[i].columnNumbers+1];
            tables[i].btrees[0].name = "id";
            tables[i].btrees[0].type = "int";
            for (int k = 0; k < tables[i].columnNumbers; ++k) {
                tables[i].btrees[k+1].name = nameType[k][0];
                tables[i].btrees[k+1].type = nameType[k][1];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i][0] == 'I') {
            string insertSyntaxValidation[3] = {"INSERT", "INTO", "VALUES"};
            string insertTableName = "";
            string insertSyntaxTmp = "";
            int parantezFinderIndex = 0;
            while (s[i][parantezFinderIndex] != ' ') {
                insertSyntaxTmp += s[i][parantezFinderIndex];
                parantezFinderIndex++;
            }
            if (insertSyntaxTmp != insertSyntaxValidation[0]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][parantezFinderIndex] == ' ')
                parantezFinderIndex++;
            insertSyntaxTmp = "";
            while (s[i][parantezFinderIndex] != ' ') {
                insertSyntaxTmp += s[i][parantezFinderIndex];
                parantezFinderIndex++;
            }
            if (insertSyntaxTmp != insertSyntaxValidation[1]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][parantezFinderIndex] == ' ')
                parantezFinderIndex++;
            while (s[i][parantezFinderIndex] != ' ') {
                insertTableName += s[i][parantezFinderIndex];
                parantezFinderIndex++;
            }
            while (s[i][parantezFinderIndex] == ' ')
                parantezFinderIndex++;
            insertSyntaxTmp = "";
            while (s[i][parantezFinderIndex] != ' ') {
                insertSyntaxTmp += s[i][parantezFinderIndex];
                parantezFinderIndex++;
            }
            if (insertSyntaxTmp != insertSyntaxValidation[2]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][parantezFinderIndex] == ' ')
                parantezFinderIndex++;
            if (s[i][parantezFinderIndex] != '(' || s[i][s[i].length() - 1] != ')') {
                cout << "!!!!!!! Syntax ERROR !!!!!!!!" << endl;
                return;
            }
            for (int j = 0; j < tableNumbers; ++j) {
                if (tables[j].name == insertTableName) {
                    tables[j].insert(s[i], parantezFinderIndex + 1);
                    break;
                }
            }
        }
        else if (s[i][0] == 'D') {
            int conditionFinderIndex = 0;
            string deleteSyntaxValidation[3] = {"DELETE", "FROM", "WHERE"};
            string deleteSyntaxTmp = "";
            string deleteTableName = "";
            while (s[i][conditionFinderIndex] != ' ') {
                deleteSyntaxTmp += s[i][conditionFinderIndex];
                conditionFinderIndex++;
            }
            if (deleteSyntaxTmp != deleteSyntaxValidation[0]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][conditionFinderIndex] == ' ')
                conditionFinderIndex++;
            deleteSyntaxTmp = "";
            while (s[i][conditionFinderIndex] != ' ') {
                deleteSyntaxTmp += s[i][conditionFinderIndex];
                conditionFinderIndex++;
            }
            if (deleteSyntaxTmp != deleteSyntaxValidation[1]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][conditionFinderIndex] == ' ')
                conditionFinderIndex++;
            while (s[i][conditionFinderIndex] != ' ') {
                deleteTableName += s[i][conditionFinderIndex];
                conditionFinderIndex++;
            }
            while (s[i][conditionFinderIndex] == ' ')
                conditionFinderIndex++;
            deleteSyntaxTmp = "";
            while (s[i][conditionFinderIndex] != ' ') {
                deleteSyntaxTmp += s[i][conditionFinderIndex];
                conditionFinderIndex++;
            }
            if (deleteSyntaxTmp != deleteSyntaxValidation[2]) {
                cout << "!!!!!! Syntax ERROR !!!!!!!!" << endl;
                return;
            }
            while (s[i][conditionFinderIndex] == ' ')
                conditionFinderIndex++;
            string conditionColumnLeft = "", conditionColumnRight = "",
                    conditionColumnCombination = "",
                    conditionColumnLeft2 = "", conditionColumnRight2 = "";
            int opt = 0, opt2 = 0;
            while (s[i][conditionFinderIndex] != '=' && s[i][conditionFinderIndex] != '>' &&
                   s[i][conditionFinderIndex] != '<' && s[i][conditionFinderIndex] != ' ') {
                conditionColumnLeft += s[i][conditionFinderIndex];
                conditionFinderIndex++;
                if (conditionFinderIndex == s[i].length()) {
                    cout << "Syntax ERROR!" << endl;
                    return;
                }
            }
            if (s[i][conditionFinderIndex] == ' ') {
                while (s[i][conditionFinderIndex] == ' ')
                    conditionFinderIndex++;
            }
            if (s[i][conditionFinderIndex] == '=') {
                if (s[i][conditionFinderIndex + 1] != '=') {
                    cout << "Syntax ERROR!" << endl;
                    return;
                }
                opt = 0;
                conditionFinderIndex += 2;
            } else if (s[i][conditionFinderIndex] == '>') {
                opt = 2;
                conditionFinderIndex += 1;
            } else if (s[i][conditionFinderIndex] == '<') {
                opt = 1;
                conditionFinderIndex += 1;
            }
            while ((s[i][conditionFinderIndex] != ' ') && (conditionFinderIndex < s[i].length())) {
                conditionColumnRight += s[i][conditionFinderIndex];
                conditionFinderIndex++;
            }
            if (s[i][conditionFinderIndex] == ' ') {
                while (s[i][conditionFinderIndex] == ' ')
                    conditionFinderIndex++;
                conditionColumnCombination = s[i][conditionFinderIndex];
                conditionFinderIndex++;
                while (s[i][conditionFinderIndex] == ' ')
                    conditionFinderIndex++;
                while (s[i][conditionFinderIndex] != ' ' && s[i][conditionFinderIndex] != '=' &&
                       s[i][conditionFinderIndex] != '>' && s[i][conditionFinderIndex] != '<') {
                    conditionColumnLeft2 += s[i][conditionFinderIndex];
                    conditionFinderIndex++;
                }
                while (s[i][conditionFinderIndex] == ' ')
                    conditionFinderIndex++;
                if (s[i][conditionFinderIndex] == '=') {
                    if (s[i][conditionFinderIndex + 1] != '=') {
                        cout << "Syntax ERROR!" << endl;
                        return;
                    }
                    opt2 = 0;
                    conditionFinderIndex += 2;
                } else if (s[i][conditionFinderIndex] == '>') {
                    opt2 = 2;
                    conditionFinderIndex += 1;
                } else if (s[i][conditionFinderIndex] == '<') {
                    opt2 = 1;
                    conditionFinderIndex += 1;
                }
                while (conditionFinderIndex < s[i].length()) {
                    conditionColumnRight2 += s[i][conditionFinderIndex];
                    conditionFinderIndex++;
                }
            }
            for (int j = 0; j < tableNumbers; ++j) {
                if (tables[j].name == deleteTableName) {
                    if (conditionColumnCombination == "") {
                        tables[j].del(conditionColumnLeft, opt, conditionColumnRight);
                    } else if (conditionColumnCombination == "|") {
                        tables[j].del(conditionColumnLeft, opt, conditionColumnRight);
                        tables[j].del(conditionColumnLeft2, opt2, conditionColumnRight2);
                    } else if (conditionColumnCombination == "&") {
                        tables[j].delAnd(conditionColumnLeft, opt, conditionColumnRight,
                                          conditionColumnLeft2, opt2, conditionColumnRight2);
                    }
                    break;
                }
            }
        }
        else if (s[i][0] == 'U') {
            string updateTableName;
            string updateSyntaxValidation[3] = {"UPDATE", "SET", "WHERE"};
            string updateSyntaxTmp = "";
            int updateIndex = 0;
            while (s[i][updateIndex] != ' ') {
                updateSyntaxTmp += s[i][updateIndex];
                updateIndex++;
            }
            if (updateSyntaxTmp != updateSyntaxValidation[0]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][updateIndex] == ' ')
                updateIndex++;
            while (s[i][updateIndex] != ' ') {
                updateTableName += s[i][updateIndex];
                updateIndex++;
            }
            while (s[i][updateIndex] == ' ')
                updateIndex++;
            updateSyntaxTmp = "";
            while (s[i][updateIndex] != ' ') {
                updateSyntaxTmp += s[i][updateIndex];
                updateIndex++;
            }
            if (updateSyntaxTmp != updateSyntaxValidation[1]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][updateIndex] == ' ')
                updateIndex++;
            if (s[i][updateIndex] != '(') {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            updateIndex++;
            while (s[i][updateIndex] == ' ')
                updateIndex++;
            for (int j = 0; j < tableNumbers; ++j) {
                if (tables[j].name == updateTableName) {
                    tables[j].update(s[i], updateIndex);
                    break;
                }
            }
        }
        else if (s[i][0] == 'S') {
            string selectTablename;
            string selectSyntaxValidation[3] = {"SELECT", "FROM", "WHERE"};
            string selectSyntaxTmp = "";
            int selectTablenameIndex = 0;
            while (s[i][selectTablenameIndex] != ' ') {
                selectSyntaxTmp += s[i][selectTablenameIndex];
                selectTablenameIndex++;
            }
            if (selectSyntaxTmp != selectSyntaxValidation[0]) {
                cout << "Syntax ERROR!" << endl;
                return;
            }
            while (s[i][selectTablenameIndex] == ' ')
                selectTablenameIndex++;
            if (s[i][selectTablenameIndex] == '*') {
                selectTablenameIndex++;
                while (s[i][selectTablenameIndex] == ' ')
                    selectTablenameIndex++;
                selectSyntaxTmp = "";
                while (s[i][selectTablenameIndex] != ' ') {
                    selectSyntaxTmp += s[i][selectTablenameIndex];
                    selectTablenameIndex++;
                }
                if (selectSyntaxTmp != selectSyntaxValidation[1]) {
                    cout << "Syntax ERROR!" << endl;
                    return;
                }
                while (s[i][selectTablenameIndex] == ' ')
                    selectTablenameIndex++;
                while (s[i][selectTablenameIndex] != ' ') {
                    selectTablename += s[i][selectTablenameIndex];
                    selectTablenameIndex++;
                }

                for (int j = 0; j < tableNumbers; ++j) {
                    if (tables[j].name == selectTablename) {
                        tables[j].select(s[i]);
                        break;
                    }
                }
            } else if (s[i][selectTablenameIndex] == '(') {
                while (s[i][selectTablenameIndex] != ')') {
                    selectTablenameIndex++;
                    if (selectTablenameIndex == s[i].length()) {
                        cout << "Syntax ERROR!" << endl;
                        return;
                    }
                }
                selectTablenameIndex++;
                while (s[i][selectTablenameIndex] == ' ')
                    selectTablenameIndex++;
                selectSyntaxTmp = "";
                while (s[i][selectTablenameIndex] != ' ') {
                    selectSyntaxTmp += s[i][selectTablenameIndex];
                    selectTablenameIndex++;
                }
                if (selectSyntaxTmp != selectSyntaxValidation[1]) {
                    cout << "Syntax ERROR!" << endl;
                    return;
                }
                while (s[i][selectTablenameIndex] == ' ')
                    selectTablenameIndex++;
                while (s[i][selectTablenameIndex] != ' ') {
                    selectTablename += s[i][selectTablenameIndex];
                    selectTablenameIndex++;
                }
                for (int j = 0; j < tableNumbers; ++j) {
                    if (tables[j].name == selectTablename) {
                        tables[j].select(s[i]);
                        break;
                    }
                }
            } else {
                cout << "Syntax ERROR!" << endl;
                return;
            }
        }
    }
}