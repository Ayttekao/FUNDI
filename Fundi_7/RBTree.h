//
// Created by ayttekao on 4/9/21.
//

#ifndef FUNDI_7_RBTREE_H
#define FUNDI_7_RBTREE_H

#define RED 1
#define BLACK 0

template <class T>
class RBNode : public TreeNode<T>
{
public:
    bool color;
    RBNode *left, *right, *parent;
    explicit RBNode(T _value, bool _color = RED, RBNode *_left = nullptr, RBNode *_right = nullptr, RBNode *_parent = nullptr)
    {
        this->value = _value;
        color = _color;
        left = _left;
        right = _right;
        parent = _parent;
    }
    explicit RBNode(T inputValue)
    {
        color = RED;
        this->value = inputValue;
        parent = left = right = nullptr;
    }
    ~RBNode() = default;
};

template <class T>
class RBTree : public BinaryTree<T>
{
protected:
    RBNode<T> *NIL;

    void innerPrintBT(const std::string& prefix, const RBNode<T>* pTreeNode, bool isLeft)
    {
        if(pTreeNode != NIL )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the pTreeNode
            std::cout << pTreeNode->value << "(" << pTreeNode->color << ")" << std::endl;

            // enter the next tree level - left and right branch
            innerPrintBT(prefix + (isLeft ? "│   " : "    "), reinterpret_cast<RBNode<T>*>(pTreeNode->left),
                         true);
            innerPrintBT(prefix + (isLeft ? "│   " : "    "), reinterpret_cast<RBNode<T>*>(pTreeNode->right),
                         false);
        }
    }
    void leftRotate(RBNode<T> *x)
    {
        // x is the node about which we have to left rotate by 1 notch

        RBNode<T> *y = x->right;
        x->right = y->left;

        if (y->left != NIL)
            y->left->parent = x;

        if (x->parent == NIL)
            this->root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->parent = x->parent;
        x->parent = y;
        y->left = x;
    }

    void rightRotate(RBNode<T> *x)
    {
        // x is the node about which we have to right rotate by 1 notch

        RBNode<T> *y = x->left;
        x->left = y->right;

        if (y->right != NIL)
            y->right->parent = x;

        if (x->parent == NIL)
            this->root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->parent = x->parent;
        x->parent = y;
        y->right = x;
    }
    void innerInsert(T&& data)
    {
        RBNode<T> *node = new RBNode<T>(data, RED, NIL, NIL, NIL);

        if (this->root)
        {
            RBNode<T> *temp = reinterpret_cast<RBNode<T>*>(this->root);
            RBNode<T> *ptr;

            /* first we insert a new RED node at proper place
               just like BST taking O(lgn)
            */
            int comparisonResult;
            while (temp != NIL)
            {
                ptr = temp;
                comparisonResult = this->strategy_->compare(data, temp->value);
                if (comparisonResult == 1)
                    temp = temp->right;
                else if (comparisonResult == -1)
                    temp = temp->left;
                else
                    throw std::invalid_argument("The value is already in the tree!");
            }

            comparisonResult = this->strategy_->compare(data, ptr->value);
            if (comparisonResult == 1)
                ptr->right = node;
            else if (comparisonResult == -1)
                ptr->left = node;
            else
                throw std::invalid_argument("The value is already in the tree!");

            node->parent = ptr;

            insertFixup(node);
        }
        else
        {
            this->root = node;
            reinterpret_cast<RBNode<T>*>(this->root)->color = BLACK;
        }
    }

    void insertFixup(RBNode<T> *z)
    {
        while (z->parent != NIL and z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                RBNode<T> *y = z->parent->parent->right; // y is uncle of z
                if (y->color == RED)
                {
                    /*
                    case 1 :- when both z's parent and uncle are RED.
                    solution :- make both z's parent and uncle BLACK
                                and make z's grandparent RED and then
                                point z to it's grandparent ie., up
                                by a level of 2 in the RBT
                    conclusion :- this case will not sures the loop to
                                  terminate as we make z's grandparent
                                  RED and again it may voilate property
                                  4 of RBT.
                    */

                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else if (z == z->parent->right)
                {
                    /*
                    case 2 :- when z's parent is RED but uncle is BLACK
                              and z is it's parent's left child.
                    solution :- point z to it's parent and then left-rotate
                                about z.
                    conclusion :- this case will never let the loop to
                                  terminate as now z and it's parent are
                                  RED violating prop 4. This case always
                                  take us to case 3.
                    */

                    z = z->parent;
                    leftRotate(z);
                }
                else
                {
                    /*
                    case 3 :- when z's parent is RED but uncle is BLACK
                              and z is it's parent's right child.
                    solution :- make z's parent BLACK and z's grandparent
                                RED and then right-rotate about z's grandp.
                                about z.
                    conclusion :- this case will terminate
                    */

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                RBNode<T> *y = z->parent->parent->left; // y is uncle of z

                if (y != NIL and y->color == RED)
                {
                    //case 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else if (z == z->parent->left)
                {
                    //case 2
                    z = z->parent;
                    rightRotate(z);
                }
                else
                {
                    //case 3
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        reinterpret_cast<RBNode<T>*>(this->root)->color = BLACK;
    }
    void deleteFixup(RBNode<T> *x)
    {
        while (x != this->root and x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                RBNode<T> *w = x->parent->right; // w is x's sibling

                if (w->color == RED)
                {
                    /*
                    case 1 :- w is RED
                    conclusion :- Always take control to case 2,3 or 4.
                    */

                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    /*
                    case 2 :- w and both it's children are BLACK.
                    solution :- take BLACK from both x and w.
                    conclusion :- terminates if came from case 1
                    */

                    w->color = RED;
                    x = x->parent;
                }
                else if (w->right->color == BLACK)
                {
                    /*
                    case 3 :- w=BLACK , w->left=RED and w->right=BLACK
                    conclusion :- case 3 take us to case 4
                    */

                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                else
                {
                    /*
                    case 4 :- w is BLACK and w->right is RED
                    conclusion :- terminates
                   */

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = reinterpret_cast<RBNode<T>*>(this->root);
                }
            }
            else
            {
                RBNode<T> *w = x->parent->left; // w is x's sibling

                if (w->color == RED)
                {
                    //case 1
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    //case 2
                    w->color = RED;
                    x = x->parent;
                }
                else if (w->left->color == BLACK)
                {
                    //case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                else
                {
                    //case 4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = reinterpret_cast<RBNode<T>*>(this->root);
                }
            }
        }

        x->color = BLACK;
    }
    RBNode<T> *successor(RBNode<T> *z) const
    {
        if (z->right == NIL)
            return NIL;

        RBNode<T> *temp = z->right;

        while (temp->left != NIL)
            temp = temp->left;

        return temp;
    }
    RBNode<T> *innerFindNode(T&& find) const
    {
        /*
        Submodule to return pointer to the first node
        containing find
        */
        RBNode<T> *temp = reinterpret_cast<RBNode<T>*>(this->root);
        int comparisonResult;
        while (temp != NIL && temp->value != find)
        {
            comparisonResult = this->strategy_->compare(find, temp->value);
            if (comparisonResult == -1)
                temp = temp->left;
            else
                temp = temp->right;
        }

        return temp;
    }
    void innerDeleteNode(T&& data)
    {
        RBNode<T> *z = innerFindNode(static_cast<T &&>(data));
        if (z != NIL)
        {
            /*
            z :- node which the user wants to delete
            y :- node which is actually deleted
            x :- y's child
            */

            RBNode<T> *y;
            RBNode<T> *x;

            if (z->left == NIL || z->right == NIL)
            {
                // If z has at most 1 child
                y = z;
            }
            else
            {
                // If z has both children
                y = successor(z);
            }

            if (y->left != NIL)
                x = y->left;
            else
                x = y->right;

            //make x's grandparent it's new parent
            x->parent = y->parent;

            //make x's new parent to point it
            if (y->parent == NIL)
                this->root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;

            //copy data of y to z before deleting y
            if (y != z)
                z->value = y->value;

            if (y->color == BLACK)
                deleteFixup(x);

            delete y; // add
        }
        else
            std::cout << "\nNo such data present";
    }
    void freeMem(RBNode<T> *current)
    {
        if (current != NIL and current != nullptr)
        {
            freeMem(reinterpret_cast<RBNode<T>*>(current->left));
            freeMem(reinterpret_cast<RBNode<T>*>(current->right));

            delete current;
        }
        this->root = nullptr;
    }
public:
    RBTree() { this->root = nullptr; NIL = new RBNode<T>(-1, BLACK); }
    RBTree(std::vector<T> values, Strategy<T>* strategy) : RBTree(strategy)
    {
        NIL = new RBNode<T>(-1, BLACK);
        vectorToTree(values);
    }
    explicit RBTree(Strategy<T>* strategy) : BinaryTree<T>(strategy)
    {
        this->root = nullptr;
        NIL = new RBNode<T>(-1, BLACK);
    }
    void printTree()
    {
        innerPrintBT("", reinterpret_cast<RBNode<T>*>(this->root), false);
    }
    ~RBTree()
    {
        freeMem(reinterpret_cast<RBNode<T>*>(this->root));
        if (this->strategy_ != nullptr)
            delete this->strategy_;
        delete NIL;
    }
    void vectorToTree(std::vector<T> values)
    {
        for (auto& item : values)
            addNode(static_cast<T &&>(item));
    }
    void addNode(T&& data) override
    {
        innerInsert(static_cast<T &&>(data));
    }
    void deleteNode(T&& data) override
    {
        innerDeleteNode(static_cast<T &&>(data));
    }
    TreeNode<T>* searchByValue(T&& data) override
    {
        return innerFindNode(static_cast<T &&>(data));
    }
    bool empty()
    {
        return (this->root) ? 0 : 1;
    }
};

#endif //FUNDI_7_RBTREE_H
