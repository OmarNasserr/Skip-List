#include <bits/stdc++.h>
using namespace std;

// Class to implement node
class Node
{
public:
    int key;

    // Array to hold pointers to node of different level
    Node **PointerForward;
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;

    // Allocate memory to PointerForward
    PointerForward = new Node*[level+1];

    // Fill PointerForward array with 0(NULL)
    memset(PointerForward, 0, sizeof(Node*)*(level+1));
};

// Class for Skip list
class SkipList
{
    int MaxLevel;
    float FractionOfNode;
    int level;
    Node *header;
public:
    SkipList(int, float);
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(int);
    void deleteElement(int);
    void searchElement(int);
    void Display();
};

SkipList::SkipList(int MaxLevel, float FractionOfNode)
{
    this->MaxLevel = MaxLevel;
    this->FractionOfNode = FractionOfNode;
    level = 0;
    header = new Node(-1, MaxLevel);
};

int SkipList::randomLevel()
{
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;
    while(r < FractionOfNode && lvl < MaxLevel)
    {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
};

// create new node
Node* SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};

// Insert given key in skip list
void SkipList::insertElement(int key)
{
    Node *current = header;

    // create update array and initialize it
    Node *update[MaxLevel+1];
    memset(update, 0, sizeof(Node*)*(MaxLevel+1));

    for(int i = level; i >= 0; i--)
    {
        while(current->PointerForward[i] != NULL &&
              current->PointerForward[i]->key < key)
            current = current->PointerForward[i];
        update[i] = current;
    }
    current = current->PointerForward[0];

    if (current == NULL || current->key != key)
    {
        int rlevel = randomLevel();
        if(rlevel > level)
        {
            for(int i=level+1;i<rlevel+1;i++)
                update[i] = header;

            // Update the list current level
            level = rlevel;
        }

        // create new node with random level generated
        Node* n = createNode(key, rlevel);

        // insert node by rearranging pointers
        for(int i=0;i<=rlevel;i++)
        {
            n->PointerForward[i] = update[i]->PointerForward[i];
            update[i]->PointerForward[i] = n;
        }
        cout<<"Successfully Inserted key "<<key<<"\n";
    }
};

// Delete element from skip list
void SkipList::deleteElement(int key)
{
    Node *current = header;

    // create update array and initialize it
    Node *update[MaxLevel+1];
    memset(update, 0, sizeof(Node*)*(MaxLevel+1));
    for(int i = level; i >= 0; i--)
    {
        while(current->PointerForward[i] != NULL  &&
              current->PointerForward[i]->key < key)
            current = current->PointerForward[i];
        update[i] = current;
    }
    current = current->PointerForward[0];

    // If current node is target node
    if(current != NULL and current->key == key)
    {
        for(int i=0;i<=level;i++)
        {
            if(update[i]->PointerForward[i] != current)
                break;

            update[i]->PointerForward[i] = current->PointerForward[i];
        }

        // Remove levels having no elements
        while(level>0 &&
              header->PointerForward[level] == 0)
            level--;
         cout<<"Successfully deleted key "<<key<<"\n";
    }
};

// Search for element in skip list
void SkipList::searchElement(int key)
{
    Node *current = header;
    for(int i = level; i >= 0; i--)
    {
        while(current->PointerForward[i] &&
               current->PointerForward[i]->key < key)
            current = current->PointerForward[i];

    }
    current = current->PointerForward[0];
    if(current and current->key == key)
        cout<<"Found key: "<<key<<"\n";
};

// Display skip list level wise
void SkipList::Display()
{
    cout<<"\n*****Skip List*****"<<"\n";
    for(int i=0;i<=level;i++)
    {
        Node *node = header->PointerForward[i];
        cout<<"Level "<<i<<": ";
        while(node != NULL)
        {
            cout<<node->key<<" ";
            node = node->PointerForward[i];
        }
        cout<<"\n";
    }
};

int main()
{
    srand((unsigned)time(0));

    SkipList lst(3, 0.5);

    lst.insertElement(3);
    lst.insertElement(6);
    lst.insertElement(7);
    lst.insertElement(9);

    lst.Display();

    //Search for node 19
    lst.searchElement(9);

    //Delete node 19
    lst.deleteElement(9);
    lst.Display();
}
