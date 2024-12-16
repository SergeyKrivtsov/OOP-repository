#include <stdio.h> 
#include <malloc.h> 
#include <ctype.h> 


typedef struct bitree
{
    int val;
    struct bitree *left;
    struct bitree *right;
}bitree;
 

bitree* formTree();
void display_top_down(bitree *tree);
void display_left_right(bitree *tree);
void display_down_top(bitree *tree);
int return_equal(bitree *tree, int info);
 

 
int main() 
{    
    bitree *tree = NULL;
    int value = 0;


    printf("lets form a tree\n");
    tree = formTree();
    display_top_down(tree);
    printf("\n");
    display_left_right(tree);
    printf("\n");
    display_down_top(tree);
    printf("\n");

    printf("were gonna find all that equal to an inputed value\n");
    printf("please, input the value, except 0\n");
    scanf("%d", &value);

    printf("%d", return_equal(tree, value));
   
    return 0; 
} 
 
//100 28 -4 0 0 33 0 0 115 110 0 112 0 0 134 0 0
//          100
//    28        115
// -4  33     110  134
//           112
bitree* formTree()
{
    bitree *t;
    int val;
    printf("input a new branch/leaf. if you want to end this branch input 0\n");
    scanf("%d", &val);
    if(val==0)
        return NULL;
    t = (bitree*)malloc(sizeof(bitree));
    t->val = val;
    t->left = formTree();
    t->right = formTree();
    return t;
}

//прямий зверху вниз
void display_top_down(bitree *tree)
{
    if(tree!=NULL)
    {
        printf("%d ", tree->val);
        display_top_down(tree->left);
        display_top_down(tree->right);
    }
}


//симетричний зліва направо
void display_left_right(bitree *tree)
{
    if(tree!=NULL)
    {
        display_left_right(tree->left);
        printf("%d ", tree->val);
        display_left_right(tree->right);
    }
}


//зворотній зниву до верху
void display_down_top(bitree *tree)
{
    if(tree!=NULL)
    {
        display_down_top(tree->left);
        display_down_top(tree->right);
        printf("%d ", tree->val);
    }
}

int return_equal(bitree *tree, int info)
{
    if(tree!=NULL)
    {
        if (tree->val==info)
            return 1+return_equal(tree->right, info)+return_equal(tree->left, info);
        else
            return return_equal(tree->right, info)+return_equal(tree->left, info);
    }
    else
        return 0;
}