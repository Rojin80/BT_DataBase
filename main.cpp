#include <iostream>
#include "query.h"

using namespace std;
int main() {
    int n;
    int tableNumbers = 0;
    int tableQueriesIndex = 0;
    cin>>n;
    string input[n];
    cin.ignore();
    for (int i = 0; i < n; ++i)
    {
        getline(cin, input[i]);
        if(input[i][0] == 'C')
            tableNumbers++;
    }
    string createQueries[tableNumbers];
    for (int i = 0; i < n; ++i) {
        if(input[i][0] == 'C') 
        {
            createQueries[tableQueriesIndex] = input[i];
            tableQueriesIndex++;
        }
    }
    queryProcess(input,n,tableNumbers, createQueries);
}

