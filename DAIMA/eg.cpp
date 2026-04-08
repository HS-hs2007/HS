#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    vector<int> a;
    vector<int> b;
    vector<int> c;
    int n1, n2, m;
    cin >> n1;
    for (int i = 0; i < n1; i++)
    {
        cin >> m;
        a.push_back(m);
    }
    cin >> n2;
    for (int i = 0; i < n2; i++)
    {
        cin >> m;
        b.push_back(m);
    }
    cout << "List A:";
    for (int i = 0; i < n1; i++)
    {
        cout << a[i] << " ";
        c.push_back(a[i]);
    }
    cout << endl << "List B:";
    for (int i = 0; i < n2; i++)
    {
        cout << b[i] << " ";
        c.push_back(b[i]);
    }
    sort(c.begin(), c.end());
    cout << endl << "List C:";
    for (int i = 0; i < n1 + n2; i++)
    {
        cout << c[i] << " ";
    }
    return 0;
}
