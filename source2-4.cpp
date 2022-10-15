#include <iostream>
#include <vector>

using namespace std;

/*

// 구현 실습 대상임

vector<vector<int>>& Add(vector<vector<int>>& A, vector<vector<int>>& B);

void  Initialize(vector<vector<int>>& A);

int main()

{

    vector<vector<int> > A, B, C;

    initialize(A);

    initialize(B);

    C = Add(A, B);



    return 0;

}

*/

int main()
{
    vector<int> vs = {1, 2, 3, 4, 5};
    vector<int>::iterator it = vs.begin();
    for (it = vs.begin(); it != vs.end(); it++)
        cout << *it << " ";

    cout << endl;

    string a = "have";
    string b = "nice";
    string c = "fish";
    string d = "apple";

    int n = 3;

    vector<vector<string>> table(n);

    table[0].push_back(a); // I add string 'a' to end of first vector in 'arr'
    table[0].push_back(b);
    table[1].push_back(c);
    table[1].push_back(d);

    for (int i = 0; i < table[0].size(); i++)
    {

        for (int j = 0; j < table[i].size(); j++) // print all string in first vector of 'arr'

            cout << table[i][j] << " ";

        cout << endl;
    }

    /*

    vector <vector<int>> vvi = {{1,2,3},{4,5}, {0,1,0,1},{100,200}};

    vector< vector<int> >::iterator row;

    vector<int>::iterator col;

    for (row = vvi.begin(); row != vvi.end(); row++) {

        for (col = row->begin(); col != row->end(); col++) {

            cout <<*col<<"  ";

        cout<<endl;		}

    }

    */

    // system("pause");

    return 1;
}