
#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;
struct treeNode
{
    int data;
    treeNode* left;
    treeNode* right;
};
treeNode* FindMin(treeNode* node)
{
    if (node == NULL)
    {
        // нет элемента в дереве
        return NULL;
    }
    if (node->left) /* Go to the left sub tree to find the min element */
        return FindMin(node->left);
    else
        return node;
}
treeNode* FindMax(treeNode* node)
{
    if (node == NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if (node->right) /* Go to the left sub tree to find the min element */
        return(FindMax(node->right));
    else
        return node;
}
treeNode* Insert(treeNode* node, int data)
{
    if (node == NULL)
    {
        treeNode* temp;
        temp = new treeNode;
        temp = (treeNode*)malloc(sizeof(treeNode));
        temp->data = data;
        temp->left = temp->right = NULL;
        return temp;
    }
    if (data >= (node->data))
    {
        node->right = Insert(node->right, data);
    }
    else if (data <= (node->data))
    {
        node->left = Insert(node->left, data);
    }
    /* Else there is nothing to do as the data is already in the tree. */
    return node;
}
treeNode* Delet(treeNode* node, int data)
{
    treeNode* temp;
    if (node == NULL)
    {
        cout << "Element Not Found";
    }
    else if (data < node->data)
    {
        node->left = Delet(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = Delet(node->right, data);
    }
    else
    {
        /* Now We can delete this node and replace with either minimum element
        in the right sub tree or maximum element in the left subtree */
        if (node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
            temp = FindMin(node->right);
            node->data = temp->data;
            /* As we replaced it with some other node, we have to delete that node */
            node->right = Delet(node->right, temp->data);
        }
        else
        {
            /* If there is only one or zero children then we can directly
            remove it from the tree and connect its parent to its child */
            temp = node;
            if (node->left == NULL)
                node = node->right;
            else if (node->right == NULL)
                node = node->left;
            free(temp); /* temp is longer required */
        }
    }
    return node;
}
treeNode* Find(treeNode* node, int data)
{
    if (node == NULL)
    {
        /* Element is not found */
        return NULL;
    }
    if (data > node->data)
    {
        /* Search in the right sub tree. */
        return Find(node->right, data);
    }
    else if (data < node->data)
    {
        /* Search in the left sub tree. */
        return Find(node->left, data);
    }
    else
    {
        /* Element Found */
        return node;
    }
}
void Inorder(treeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    Inorder(node->left);
    cout << node->data << " ";
    Inorder(node->right);
}
void Preorder(treeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    cout << node->data << " ";
    Preorder(node->left);
    Preorder(node->right);
}
void Postorder(treeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    Postorder(node->left);
    Postorder(node->right);
    cout << node->data << " ";
}
void Sum(treeNode* node, int& sum)
{
    if (node != NULL)
    {
        sum += node->data;
        Sum(node->left, sum);
        Sum(node->right, sum);
    }
}
int main()
{
    int sum = 0;
    setlocale(LC_ALL, "russian");
    treeNode* root = NULL, * temp;
    int ch;
    //clrscr();
    while (1)
    {
        cout << "\n1.Вставка\n2.Удалить\n3.Симметричный обход\n4.Обход в ширину\n5.Обход в глубину\n6.Минимальный эллемент\n7.Максимальный эллемент\n8.Поиск\n9.Выход\n";
        cout << "Введите пункт меню:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "\nВведите эллемент для вставки:";
            cin >> ch;
            root = Insert(root, ch);
            cout << "\nЭллементы в BST:";
            Inorder(root);
            break;
        case 2:
            cout << "\nВведите эллемент для удаления:";
            cin >> ch;
            root = Delet(root, ch);
            cout << "\nПосле удаления , эллементв в BST :";
            Inorder(root);
            break;
        case 3:
            cout << "\nInorder Travesals is:";
            Inorder(root);
            break;
        case 4:
            cout << "\nPreorder Traversals is:";
            Preorder(root);
            break;
        case 5:
            cout << "\nPostorder Traversals is:";
            Postorder(root);
            break;
        case 6:
            temp = FindMin(root);
            cout << "\nМинимальный эллемент :" << temp->data;
            break;
        case 7:
            temp = FindMax(root);
            cout << "\nМаксимальный эллемент :" << temp->data;
            break;
        case 8:
            cout << "\nВведите эллемент для поиска:";
            cin >> ch;
            temp = Find(root, ch);
            if (temp == NULL)
            {
                cout << "Эллемент не найден ";
            }
            else
            {
                cout << "Эллемент " << temp->data << " Найден\n";
            }
            break;
        case 9:
            Sum(root, sum);
            cout << "\nСумма всех эллементов :" << sum;
            break;
        case 10:
            exit(0);
            break;
        default:
            cout << "\nНеверный пункт меню , введите ищё раз :";
            break;
        }
        //Sum(root, sum);
        //system("pause");
    }
    return 0;
}