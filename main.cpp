/*
 * @Author: Eternal4869 
 * @Date: 2021-11-02 14:16:35 
 * @Last Modified by: Eternal4869
 * @Last Modified time: 2021-11-02 16:25:00
 */
#include <iostream>
using namespace std;

template <class ElemType>
struct Node
{
    ElemType data;
    Node<ElemType> *next;

    Node()
    {
        next = nullptr;
    }

    Node(ElemType item, Node<ElemType> *link = nullptr)
    {
        data = item;
        next = link;
    }
};

template <class ElemType>
class LinkQueue
{
private:
    int count;                    //元素个数
    Node<ElemType> *front, *rear; //队头队尾指针
public:
    LinkQueue();
    virtual ~LinkQueue();
    int Length() const;                                              //计算队列长度
    bool Empty() const;                                              //判断队列是否为空
    void Clear();                                                    //清空队列
    void Traverse() const;                                           //遍历队列
    bool OutQueue(ElemType &e);                                      //出队
    bool InQueue(const ElemType &e);                                 //入队
    bool GetHead(ElemType &e) const;                                 //取队头
    bool GetTail(ElemType &e) const;                                 //取队尾
    LinkQueue(const LinkQueue<ElemType> &copy);                      //复制构造函数
    LinkQueue<ElemType> &operator=(const LinkQueue<ElemType> &copy); //重载赋值运算符
};

template <class ElemType>
LinkQueue<ElemType>::LinkQueue()
//构造一个空队列
{
    rear = front = new Node<ElemType>; //创建头结点
    count = 0;
}

template <class ElemType>
LinkQueue<ElemType>::~LinkQueue()
{
    Clear();
}

template <class ElemType>
int LinkQueue<ElemType>::Length() const
{
    return count;
}

template <class ElemType>
bool LinkQueue<ElemType>::Empty() const
{
    return count == 0;
}

template <class ElemType>
void LinkQueue<ElemType>::Clear()
{
    ElemType e; //临时元素，用于出队
    while (!Empty())
    {
        //队列非空时，逐一出队
        OutQueue(e);
    }
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse() const
{
    for (Node<ElemType> *pMove = front->next; pMove != nullptr; pMove = pMove->next)
    {
        cout << pMove->data << endl;
    }
}

template <class ElemType>
bool LinkQueue<ElemType>::InQueue(const ElemType &e)
//从队尾入队
{
    Node<ElemType> *t = new Node<ElemType>(e);
    if (t == nullptr) //动态内存耗尽
    {
        return false;
    }
    else
    {
        rear->next = t; //设置新节点的位置
        rear = t;       //队尾指针移动
        count++;        //计数器加一
        return true;
    }
}

template <class ElemType>
bool LinkQueue<ElemType>::OutQueue(ElemType &e)
//出队，当队列非空时，弹出队列头顶，并且将data返回给e
{
    if (!Empty()) //非空队列
    {
        Node<ElemType> *t = front->next; //指向队列头
        e = t->data;                     //取出元素数据
        front->next = t->next;           //向下传递队列头
        if (rear == t)                   //验证队列是否只有一个元素（被删除的元素）
        {
            rear = front; //现在队列为空队列
        }
        delete t; //释放内存
        count--;  //计数器减一
        return true;
    }
    else //空队列
    {
        return false;
    }
}

template <class ElemType>
bool LinkQueue<ElemType>::GetHead(ElemType &e) const
//队列非空，将队列头的元素赋值给e，返回true；否则，返回false
{
    if (!Empty()) //队列非空
    {
        e = front->next->data; //返回元素内容
        return true;
    }
    else //空队列
    {
        return false;
    }
}

template <class ElemType>
bool LinkQueue<ElemType>::GetTail(ElemType &e) const
//队列非空，将队列尾的元素赋值给e，返回true；否则，返回false
{
    if (!Empty())
    {
        e = rear->data;
        return true;
    }
    else
    {
        return false;
    }
}

template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
//复制构造函数:由已知队列copy建立一个新的队列
{
    rear = front = new Node<ElemType>;
    count = 0;
    for (Node<ElemType> *t = copy.front->next; t != nullptr; t = t->next)
    //遍历copy元素，入栈
    {
        InQueue(t->data);
    }
}

template <class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> &copy)
//重载赋值运算符
{
    if (copy != this) //copy与当前队列不相同
    {
        Clear();
        for (Node<ElemType> *t = copy.front->next; t != nullptr; t = t->next)
        {
            InQueue(t->data);
        }
    }
    return *this;
}

int main()
{
    LinkQueue<int> lq1;
    cout << "Please enter integers : " << endl;
    int tmp, t;
    cin >> tmp;
    lq1.InQueue(tmp);
    cout << "Please enter integers : " << endl;
    cin >> tmp;
    lq1.GetTail(t);
    while (tmp > t)
    {
        lq1.InQueue(tmp);
        cout << "Please enter integers : " << endl;
        cin >> tmp;
        lq1.GetTail(t);
    }
    cout << "Stop!It's wrong!" << endl;
    cout << "Here are the right numbers:" << endl;
    lq1.Traverse();
    return 0;
}
