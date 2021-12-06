#include <bits/stdc++.h>
using namespace std;

string format_name(string a)
{
    string ans = "";
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == ' ')
            ans.push_back('_');
        else
            ans.push_back(toupper(a[i]));
    }
    return ans;
}

int main()
{
    string a;
    while (cin >> a)
    {
        cout << "const material " << format_name(a) << " = material(";
        double d;
        for (int i = 0; i < 10; i++)
        {
            cin >> d;
            cout << d << ",";
        }
        cout << 1.0 << ");" << endl;
    }
}