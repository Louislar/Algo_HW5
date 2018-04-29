#include<iostream>
#include<algorithm>

using namespace std;

int max_adj(int a, int b, int c)
{
    a=max(a, b);
    a=max(a, c);
    return a;
}


int mcss(int s[], int l, int r)
{
    if(l==r) return s[l];
    int mid=(l+r)/2;
    int msl=mcss(s, l, mid);
    int msr=mcss(s, mid+1, r);
    int mbl=-100000;
    int temp=0;
    for(int i=mid;i>=l;i--)
    {
        temp=temp+s[i];
        if(temp>mbl)
            mbl=temp;
    }
    int mbr=-100000;
    temp=0;
    for(int i=mid+1;i<=r;i++)
    {
        temp+=s[i];
        if(temp>mbr)
            mbr=temp;
    }
    return max_adj(msl, msr, mbl+mbr);
}


int main()
{
    int n=0;
    cin>>n;
    for(int q=0;q<n;q++)
    {
        if(q!=0)
            cout<<endl;
        int k=0;
        cin>>k;
        int s[k]={0};

        //input series
        for(int w=0;w<k;w++)
        {
            cin>>s[w];
        }

        int ans=mcss(s, 0, k-1);
        cout<<ans;
    }
}
