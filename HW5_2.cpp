#include<iostream>

using namespace std;

class chainNode
{
public:
    chainNode()
    {
        leftNode=0;
        rightNode=0;
        value=0;
        alpha='\0';
    }
    chainNode(chainNode* left, chainNode* right, int v, char a='\0')
    {
        leftNode=left;
        rightNode=right;
        value=v;
        alpha=a;
    }
    int value;
    char alpha;
    string code;
    int code_val;
    chainNode* leftNode;
    chainNode* rightNode;
};

int travers(chainNode* root, string encode, int encode_val, chainNode* ans[], int& ansLength)
{
    if(root->leftNode==0 && root->rightNode==0)
    {
        root->code=encode;
        root->code_val=encode_val;
        ans[ansLength]=root;
        ansLength++;
    }
    string temp1=encode;
    string temp2=encode;
    temp1.append("0");
    temp2.append("1");

    if(root->leftNode!=0)
        travers(root->leftNode, temp1, encode_val*2, ans, ansLength);
    if(root->rightNode!=0)
        travers(root->rightNode, temp2, encode_val*2+1, ans, ansLength);
}

string decTobin(int dec)
{
    string tempStr="";
    if(dec==0)
    {
        tempStr="0";
        return tempStr;
    }

    while(dec>1)
    {
        char tempChar;
        if(dec%2==1) tempChar='1';
        if(dec%2==0) tempChar='0';
        tempStr.insert(0, &tempChar);
        tempStr.erase(1, 1);
        dec=dec/2;
    }
    char a1='1';
    tempStr.insert(0, &a1);
    return tempStr;
}

int main()
{
    char inChar[10]={'\0'};
    int inInt[10]={0};
    int inLength=0;
    chainNode* nodes[10];
    for(int i=0;i<10;i++) nodes[i]=new chainNode();
    int nodesLength=0;

    //input
    {
        char temp;
        while(cin>>temp)
        {
            // check if it had appear
            int appearBefore=0;
            for(int i=0;i<inLength;i++)
            {
                if(inChar[i]==temp)
                {
                    inInt[i]++;
                    appearBefore=1;
                }
            }
            // new char
            if(appearBefore==0)
            {
                inChar[inLength]=temp;
                inInt[inLength]=1;
                inLength++;
            }

        }// while cin>>temp end

        //sort
        for(int j=0;j<inLength;j++){
        for(int i=0;i<inLength;i++)
        {
            if(i<inLength-1){
                if(inInt[i]>inInt[i+1])
                {
                    int tempInt=inInt[i];
                    inInt[i]=inInt[i+1];
                    inInt[i+1]=tempInt;
                    char tempChar=inChar[i];
                    inChar[i]=inChar[i+1];
                    inChar[i+1]=tempChar;
                }
            }
        }
        }//sort end

        // put all in node
        nodesLength=inLength;
        for(int i=0;i<inLength;i++)
        {
            nodes[i]->alpha=inChar[i];
            nodes[i]->value=inInt[i];
        }

        //test
        /*for(int i=0;i<inLength;i++)
        {
            cout<<nodes[i]->alpha;
        }
        cout<<endl;
        for(int i=0;i<inLength;i++)
        {
            cout<<nodes[i]->value;
        }*/

    }// input end

    // build tree
    while(nodesLength>1){
        int min1Index;
        int min2Index;

        //find two min
        int tempMin=100;
        for(int i=0;i<nodesLength;i++)
        {
            if(nodes[i]->value<tempMin)
            {
                min1Index=i;
                tempMin=nodes[i]->value;
            }

        }
        tempMin=100;
        for(int i=0;i<nodesLength;i++)
        {
            if(nodes[i]->value<tempMin && i!=min1Index)
            {
                min2Index=i;
                tempMin=nodes[i]->value;
            }
        }

        //keep min1<min2
        if(min1Index>min2Index)
        {
            int temp=min1Index;
            min1Index=min2Index;
            min2Index=temp;
        }

        // merge min1 and min2
        chainNode* tempNode;
        if(nodes[min1Index]->value>nodes[min2Index]->value)
            tempNode=new chainNode( nodes[min2Index]
                                   , nodes[min1Index]
                                   , nodes[min2Index]->value+nodes[min1Index]->value);
        if(nodes[min1Index]->value<=nodes[min2Index]->value)
            tempNode=new chainNode( nodes[min1Index]
                                   , nodes[min2Index]
                                   , nodes[min2Index]->value+nodes[min1Index]->value);
        nodes[min1Index]=tempNode;

        //adjust nodes array
        for(int i=min2Index;i<nodesLength-1;i++)
        {
            nodes[i]=nodes[i+1];
        }
        nodesLength--;
    }//build tree end


    chainNode* ans[10];
    int ansLength=0;
    string encode;
    int encode_val=0;
    // traversal the tree
    {
        travers(nodes[0], encode, encode_val, ans, ansLength);

        //sort by value
        for(int i=0;i<ansLength;i++)
        {
            for(int q=0;q<ansLength-1;q++)
            {
                if(ans[q]->code_val>ans[q+1]->code_val)
                {
                    chainNode* temp=ans[q];
                    ans[q]=ans[q+1];
                    ans[q+1]=temp;

                }
            }
        }


        /*****************************
        start here
        still stuck at how to sort in
        binary value
        *****************************/



        //output

        for(int i=0;i<ansLength;i++)
        {
            if(i!=0)
                cout<<endl;

            cout<<ans[i]->alpha<<":"<<ans[i]->code;
        }
    }



}
