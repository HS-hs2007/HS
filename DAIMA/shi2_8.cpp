#include <iostream>
using namespace std;
void hanoi(int n,char a,char b,char c)
{
    if(n==1)
{
    cout<<a<<"->1->"<<c<<endl;
}
else
{
    hanoi(n-1,a,c,b);
    cout<<a<<"->"<<n<<"->"<<c<<endl;
    hanoi(n-1,b,a,c);
}

}
int main()
{
    int m;
    char a ,c,b;
    cin>>m>>a>>b>>c;
    hanoi(m,a,c,b);
    return 0;
}