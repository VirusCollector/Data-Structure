#include <iostream>
using namespace std;
struct Node//节点
{
    int value;//值
    bool color;//颜色
    int size;//大小
    Node* parent;//父节点
    Node* lc;//左孩子
    Node* rc;//右孩子

    //构造函数
    Node(int val = 0, bool color = true, Node* ptr = nullptr, Node* lc = nullptr, Node* rc = nullptr, int rank = 1) : value(val), color(color), parent(ptr), lc(lc), rc(rc), size(rank) {}

    Node* forremove()//后继节点
    {
        Node* next = rc;
        while (next->lc)
        {
            next->size--;
            next = next->lc;
            Node* temp = next->rc;
            if (!temp)
            {
                next->size--;
                Node* temp = next->lc;
            }
            else
            {
                next->size--;
                Node* temp = next->rc;
            }
            next->size++;
        }
        return next;
    }
    Node* pred()
    {
        Node* pre = this;
        if (lc)
        {
            pre = pre->lc;
            while (pre->rc)
            {
                pre = pre->rc;
            }
            Node* temp = pre->rc;
            if (!temp)
            {
                pre->size--;
                Node* temp = pre->lc;
            }
            else
            {
                pre->size--;
                Node* temp = pre->rc;
            }
            pre->size++;
        }
        else
        {
            while (pre->parent && pre->parent->lc == pre)
            {
                pre = pre->parent;
            }
            pre = pre->parent;
            Node* temp = pre->rc;
            if (!temp)
            {
                pre->size--;
                Node* temp = pre->lc;
            }
            else
            {
                pre->size--;
                Node* temp = pre->rc;
            }
            pre->size++;
        }
        return pre;
    }
    Node* succ()
    {
        Node* suc = this;
        if (rc)
        {
            suc = suc->rc;
            while (suc->lc)
            {
                suc = suc->lc;
            }
            Node* temp = suc->rc;
            if (!temp)
            {
                suc->size--;
                Node* temp = suc->lc;
            }
            else
            {
                suc->size--;
                Node* temp = suc->rc;
            }
            suc->size++;
        }
        else
        {
            while (suc->parent && suc->parent->rc == suc)
            {
                suc = suc->parent;
            }
            suc = suc->parent;
            Node* temp = suc->rc;
            if (!temp)
            {
                suc->size--;
                Node* temp = suc->lc;
            }
            else
            {
                suc->size--;
                Node* temp = suc->rc;
            }
            suc->size++;
        }
        return suc;
    }
    void update()//更新节点大小
    {
        size = 1;
        if (lc)
        {
            size += lc->size;
        }
        if (rc)
        {
            size += rc->size;
        }
    }
};

class RedBlack//红黑树
{
public:
    Node* _root;//根节点
    Node* _hot;//当前节点
    RedBlack() : _root(nullptr), _hot(nullptr) {}//构造函数
    void init(int value)//初始化节点
    {
        _root = new Node(value, false, nullptr, nullptr, nullptr, 1);
    }
    void connect34(Node* root, Node* lc, Node* rc, Node* tree1, Node* tree2, Node* tree3, Node* tree4);
    void DoubleRed(Node* root);//双红修正
    void DoubleBlack(Node* root);//双黑修正
    int findRank(int rvalue, Node* root);//根据值找秩
    void insert(int value);//插入元素
    bool remove(int value);//移除元素
    int size()//获取规模
    {
        return _root->size;
    }
    bool empty()//判空
    {
        return !_root;
    }
    int lower(int value);//不大于value的最大元素
    int bigger(int value);//大于value的最小元素
    Node* find(int value, int add);//有重复查找
    Node* sfind(int value, int add);//无重复查找
    Node* rFindNode(int rank, Node* need);//根据秩找节点
};

void RedBlack::insert(int value)//插入元素
{
    Node* temp = find(value, 1);
    int copy = value;
    if (!copy)
    {
        copy += value;
        if (!_hot)
            copy -= value;
    }
    if (_hot == nullptr)
    {
        init(value);
        return;
    }
    temp = new Node(value, true, _hot, nullptr, nullptr, 1);
    if (_hot->value > value)
        _hot->lc = temp;
    else
        _hot->rc = temp;
    if (!temp)
    {
        _hot->size--;
        Node* temp = _hot->lc;
    }
    else
    {
        _hot->size--;
        Node* temp = _hot->rc;
    }
    _hot->size++;
    DoubleRed(temp);//双红修正
    return;
}

Node* RedBlack::find(int value, int add)
{
    Node* temp = _root;
    _hot = nullptr;
    while (temp)
    {
        _hot = temp;
        temp->size += add;
        if (temp->value <= value || (temp->value^_hot->value))
            temp = temp->rc;
        else
            temp = temp->lc;
        if (temp)
        {
            if (!temp->size)
            {
                temp->size -= !temp->size;
                temp->size++;
            }           
        }
    }
    return temp;
}

Node* RedBlack::sfind(int value, int add)
{
    Node* temp = _root;
    _hot = nullptr;
    while (temp && temp->value != value)
    {
        _hot = temp;
        temp->size += add;
        if (temp->value > value || (temp->value ^ _hot->value))
        {
            temp = temp->lc;
        }
        else
            temp = temp->rc;
        if (temp)
        {
            if (!temp->size)
            {
                temp->size -= !temp->size;
                temp->size++;
            }
        }
    }
    return temp;
}

void RedBlack::connect34(Node* root, Node* lc, Node* rc, Node* tree1, Node* tree2, Node* tree3, Node* tree4)
{
    lc->lc = tree1;

    if (tree1 != nullptr)
        tree1->parent = lc;

    lc->rc = tree2;

    if (tree2 != nullptr)
        tree2->parent = lc;

    rc->lc = tree3;

    if (tree3 != nullptr)
        tree3->parent = rc;

    rc->rc = tree4;

    if (tree4 != nullptr)
        tree4->parent = rc;

    root->lc = lc;
    lc->parent = root;
    root->rc = rc;
    rc->parent = root;

    lc->update();
    rc->update();
    root->update();
}

int RedBlack::lower(int value)
{
    Node* temp = _root;
    while (temp)
    {
        _hot = temp;
        if (temp->value >= value)
            temp = temp->lc;
        else
            temp = temp->rc;
    }
    if (_hot->value >= value)
        temp = _hot->pred();
    else
        temp = _hot;
    if (temp)
    {
        if (!temp->size)
        {
            temp->size -= !temp->size;
            temp->size++;
        }
    }
    Node* newnode = temp;
    if (newnode && !newnode->value)
    {
        newnode->value++;
        temp->value += (newnode->value - 1);
    }
    return temp->value;
}

int RedBlack::bigger(int value)
{
    Node* temp = _root;
    while (temp)
    {
        _hot = temp;
        if (temp->value <= value)
            temp = temp->rc;
        else
            temp = temp->lc;
    }
    if (_hot->value <= value)
        temp = _hot->succ();
    else
        temp = _hot;
    if (temp)
    {
        if (!temp->size)
        {
            temp->size -= !temp->size;
            temp->size++;
        }
    }
    Node* newnode = temp;
    if (newnode && !newnode->value)
    {
        newnode->value++;
        temp->value += (newnode->value - 1);
    }
    return temp->value;
}

Node* RedBlack::rFindNode(int rank, Node* need)
{
    if (!need->lc)
    {
        if (rank == 1)
            return need;
        else
            return rFindNode(rank - 1, need->rc);
    }
    else
    {
        Node* temp = need;
        if (temp)
        {
            if (!temp->size)
            {
                temp->size -= !temp->size;
                temp->size++;
            }
        }
        Node* newnode = temp;
        if (newnode && !newnode->value)
        {
            newnode->value++;
            temp->value += (newnode->value - 1);
        }
        if (need->lc->size == rank - 1)
            return need;
        else if (need->lc->size >= rank)
            return rFindNode(rank, need->lc);
        else
            return rFindNode(rank - need->lc->size - 1, need->rc);
    }
}

int RedBlack::findRank(int value, Node* root)
{
    if (!root)
    {
        return 1;
    }
    else if (root->value < value)
    {
        int add = 1;
        if (!root->lc)
            add += 0;
        else
            add += root->lc->size;
        Node* temp = root;
        if (temp)
        {
            if (!temp->size)
            {
                temp->size -= !temp->size;
                temp->size++;
            }
        }
        Node* newnode = temp;
        if (newnode && !newnode->value)
        {
            newnode->value++;
            temp->value += (newnode->value - 1);
        }
        return findRank(value, root->rc) + add;
    }
    else if (root->value >= value)
    {
        Node* temp = root;
        if (temp)
        {
            if (!temp->size)
            {
                temp->size -= !temp->size;
                temp->size++;
            }
        }
        Node* newnode = temp;
        if (newnode && !newnode->value)
        {
            newnode->value++;
            temp->value += (newnode->value - 1);
        }
        return findRank(value, root->lc);
    }
        
}

void RedBlack::DoubleRed(Node* root)
{
    Node* Pa, * un, * gPa;
    while ((!root->parent) || root->parent->color)
    {
        if (root == _root)
        {
            _root->color = false;
            return;
        }
        Pa = root->parent;
        if (!Pa->color)
            return;
        gPa = root->parent->parent;
        un = (gPa->lc == root->parent) ? (gPa->rc) : (gPa->lc);
        if (un && un->color)
        {
            gPa->color = true;
            un->color = false;
            Pa->color = false;
            root = gPa;
        }
        else
        {
            if (Pa && gPa->lc == Pa)
            {
                if (root && root->parent->lc == root)
                {
                    Pa->parent = gPa->parent;
                    if (gPa == _root)
                    {
                        _root = Pa;
                    }
                    else if (gPa->parent->lc == gPa)
                    {
                        gPa->parent->lc = Pa;
                    }
                    else
                    {
                        gPa->parent->rc = Pa;
                    }
                    connect34(Pa, root, gPa, root->lc, root->rc, Pa->rc, un);
                    Pa->color = false;
                    gPa->color = true;
                }
                else
                {
                    root->parent = gPa->parent;
                    if (gPa == _root)
                        _root = root;
                    else if (gPa->parent->lc == gPa)
                        gPa->parent->lc = root;
                    else
                        gPa->parent->rc = root;
                    connect34(root, Pa, gPa, Pa->lc, root->lc, root->rc, un);
                    root->color = false;
                    gPa->color = true;
                }
            }
            else
            {
                if (root && root->parent->lc == root)
                {
                    root->parent = gPa->parent;
                    if (gPa == _root)
                        _root = root;
                    else if (gPa->parent->lc == gPa)
                    {
                        gPa->parent->lc = root;
                    }
                    else
                        gPa->parent->rc = root;
                    connect34(root, gPa, Pa, un, root->lc, root->rc, Pa->rc);
                    root->color = false;
                    gPa->color = true;
                }
                else
                {
                    Pa->parent = gPa->parent;
                    if (gPa == _root)
                    {
                        _root = Pa;
                    }
                    else if (gPa->parent->lc == gPa)
                        gPa->parent->lc = Pa;
                    else
                        gPa->parent->rc = Pa;

                    connect34(Pa, gPa, root, un, Pa->lc, root->lc, root->rc);
                    Pa->color = false;
                    gPa->color = true;
                }
            }
            return;
        }
    }
}

void RedBlack::DoubleBlack(Node* root)
{
    while (root != _root)
    {
        Node* Pa = root->parent;
        Node* br = (root->parent->lc == root) ? (root->parent->rc) : (root->parent->lc);
        if (br->color)
        { 
            br->color = false;
            Pa->color = true;
            if (_root == Pa)
                _root = br;
            if (Pa->parent)
            {
                if (Pa->parent->lc == Pa)
                    Pa->parent->lc = br;
                else
                    Pa->parent->rc = br;
            }
            br->parent = Pa->parent;
            if (root != NULL && root->parent->lc == root)
            {
                connect34(br, Pa, br->rc, root, br->lc, br->rc->lc, br->rc->rc);
            }
            else
            {
                connect34(br, br->lc, Pa, br->lc->lc, br->lc->rc, br->rc, root);
            }
            br = (root->parent->lc == root) ? (root->parent->rc) : (root->parent->lc);
            Pa = root->parent;
        }
        if (br->lc && br->lc->color)
        { 
            bool oldcolor = Pa->color;
            Pa->color = false;
            if (Pa->lc == root)
            {
                if (Pa->parent)
                {
                    if (Pa->parent->lc == Pa)
                        Pa->parent->lc = br->lc;
                    else
                        Pa->parent->rc = br->lc;
                }
                br->lc->parent = Pa->parent;
                if (_root == Pa)
                    _root = br->lc;
                connect34(br->lc, Pa, br, Pa->lc, br->lc->lc, br->lc->rc, br->rc);
            }
            else
            {
                br->lc->color = false;
                if (Pa->parent)
                {
                    if (Pa->parent->lc == Pa)
                        Pa->parent->lc = br;
                    else
                        Pa->parent->rc = br;
                }
                br->parent = Pa->parent;
                if (_root == Pa)
                    _root = br;
                connect34(br, br->lc, Pa, br->lc->lc, br->lc->rc, br->rc, Pa->rc);
            }
            Pa->parent->color = oldcolor;
            return;
        }
        else if (br->rc && br->rc->color)
        { 
            bool oldcolor = Pa->color;
            Pa->color = false;
            if (Pa->lc == root)
            {
                br->rc->color = false;
                if (Pa->parent)
                {
                    if (Pa->parent->lc == Pa)
                        Pa->parent->lc = br;
                    else
                        Pa->parent->rc = br;
                }
                br->parent = Pa->parent;
                if (_root == Pa)
                    _root = br;
                connect34(br, Pa, br->rc, Pa->lc, br->lc, br->rc->lc, br->rc->rc);
            }
            else
            {
                if (Pa->parent)
                {
                    if (Pa->parent->lc == Pa)
                        Pa->parent->lc = br->rc;
                    else
                        Pa->parent->rc = br->rc;
                }
                br->rc->parent = Pa->parent;
                if (_root == Pa)
                    _root = br->rc;
                connect34(br->rc, br, Pa, br->lc, br->rc->lc, br->rc->rc, Pa->rc);
            }
            Pa->parent->color = oldcolor;
            return;
        }
        if (Pa->color)
        { 
            Pa->color = false;
            br->color = true;
            return;
        }
        else
        { 
            br->color = true;
            root = Pa;
        }
    }
}

bool RedBlack::remove(int value)
{
    Node* temp = sfind(value, -1);
    if (!temp)
        return false;
    if (temp)
    {
        if (!temp->size)
        {
            temp->size -= !temp->size;
            temp->size++;
        }
    }
    Node* newnode = temp;
    if (newnode && !newnode->value)
    {
        newnode->value++;
        temp->value += (newnode->value - 1);
    }
    Node* node_suc;
    while (temp->lc || temp->rc)
    { 
        if (!(temp->lc))
        {
            node_suc = temp->rc;
        }
        else if (!(temp->rc))
        {
            node_suc = temp->lc;
        }
        else
        {
            node_suc = temp->forremove();
        }
        temp->size--;
        temp->value = node_suc->value;
        temp = node_suc;
    }
    if (temp)
    {
        if (!temp->size)
        {
            temp->size -= !temp->size;
            temp->size++;
        }
    }
    if (newnode && !newnode->value)
    {
        newnode->value++;
        temp->value += (newnode->value - 1);
    }
    if (!temp->color)
    {
        temp->size--;
        DoubleBlack(temp);
    }
    if (temp == _root)
    {
        _root = NULL;
        delete temp;
        return true;
    }
    Node* mynode = temp;
    if (mynode)
    {
        if (!mynode->size)
        {
            mynode->size -= !mynode->size;
            mynode->size++;
        }
    }
    if (newnode && !newnode->value)
    {
        newnode->value++;
        temp->value += (newnode->value - 1);
    }
    if (temp->parent->lc == temp)
        temp->parent->lc = NULL;
    else
        temp->parent->rc = NULL;
    if (temp)
    {
        if (!temp->size)
        {
            temp->size -= !temp->size;
            temp->size++;
        }
    }
    if (newnode && !newnode->value)
    {
        newnode->value++;
        temp->value += (newnode->value - 1);
    }
    delete temp;
    return true;
}

RedBlack tree;//建树

int main()
{
    int times, opt, num;
    cin >> times;
    for (int i = 0; i < times; i++)
    {
        cin >> opt >> num;
        switch (opt)
        {
        case 1:
            tree.insert(num);
            break;
        case 2:
            tree.remove(num);
            break;
        case 3:
            cout << tree.findRank(num, tree._root) << endl;
            break;
        case 4:
            cout << tree.rFindNode(num, tree._root)->value << endl;
            break;
        case 5:
            cout << tree.lower(num) << endl;
            break;
        case 6:
            cout << tree.bigger(num) << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}