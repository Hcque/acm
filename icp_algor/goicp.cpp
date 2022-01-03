#include <queue>
#include <iostream>

using namespace std;

class ICP;

struct RotNode
{
    float a,b,c,w;
    int l;
    float lb,ub;
    
};

struct TransNode
{
    float a,b,c,w;
    float lb,ub;
};

class GoIcp
{
public:

    PointCloudTPtr pModel, pData;
    RotNode InitRotNode; TransNode InitTransNode;
    ICP icp;

    float OuterLoop();
    float InnnerLoop();
};

float GoIcp::OuterLoop()
{
    float lb,ub;


    priority_queue<RotNode> que;
    que.push(InitRotNode);

    while (1)
    {
        if (que.empty()) 
        {
            cout << "que is empty" << endl;
            break;
        }

        // stop condition

        //
        auto now = que.top(); que.pop();
        for (int i = 0; i < 8; i++)
        {
            // 8 child space


            // go to transNode

            ub = InnnerLoop();
            if (ub < _best)
            {
                // do icp
            }

            lb = InnnerLoop();
            if (lb > _best)
            {
                //skip
            }
            que.push(child);
        }

    }

}


float GoIcp::InnnerLoop()
{
    priority_queue<TransNode> que;
    que.push(InitTransNode);

    while (1)
    {
        // empty

        // 
        auto now = que.top(); que.pop();

        for (int i =0; i < 8 ; i ++ )
        {



            // que push
        }



    }

}