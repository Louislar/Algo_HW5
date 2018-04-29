#include<iostream>
#include<string>

using namespace std;

int main()
{
    int global_count=0;
    string str;
    while(getline(cin, str))
    {
        if(global_count!=0)
            cout<<endl;
        global_count=1;

        int temp_index=str.find_last_of(" ");
        str=str.substr(0, temp_index+1);

        int poly[100]={0};
        int polyLength=0;

        for(int i=0;i<str.length();i++)
        {
            int negative=0;
            int tempNum[1000];
            int tempNumLength=0;
            while(str[i]!=' ')
            {
                if(str[i]=='-') negative=1;
                else{
                    tempNum[tempNumLength]=(int)str[i]-'0';
                    tempNumLength++;
                }
                i++;
            }
            if(str[i]==' ')
            {
                int temp_sum=0;
                for(int q=0;q<tempNumLength;q++)
                {
                    int power10=1;
                    for(int w=1;w<tempNumLength-q;w++) power10*=10;
                    temp_sum=temp_sum+tempNum[q]*power10;
                }
                if(negative==1) temp_sum*=-1;

                poly[polyLength]=temp_sum;
                polyLength++;
            }
        }

        for(int i=0;i<polyLength;i++)
        {
            poly[i]=poly[i]*(polyLength-i);
        }

        //test
        //for(int i=0;i<polyLength;i++) cout<<poly[i]<<' ';

        for(int i=0;i<polyLength;i++)
        {
            if(poly[i]!=0)
            {
                if(i!=0&&poly[i]>0)
                    cout<<"+";
                if(polyLength-i-1!=0&&polyLength-i-1!=1)
                    cout<<poly[i]<<"X^"<<(polyLength-i-1);
                if(polyLength-i-1==0)
                    cout<<poly[i];
                if(polyLength-i-1==1)
                    cout<<poly[i]<<"X";
            }
        }

    }

}
