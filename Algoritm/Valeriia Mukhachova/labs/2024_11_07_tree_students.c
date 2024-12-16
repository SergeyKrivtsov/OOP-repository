#include <stdio.h> 
#include <malloc.h> 
#include <ctype.h> 
#include <string.h>

typedef struct Student
{
    char name[50];
    int av_grade;
}Student;

typedef struct bitree
{
    Student stud;
    struct bitree *left;
    struct bitree *right;
}bitree;
 
bitree* create_node(Student student);
bitree* insert_node(bitree *root, Student student);
void display_left_right(bitree *tree);

bitree* delete_node(bitree *root, Student student);
bitree* findMin(bitree* Node);

void print_students(bitree* root, int grade);

int main() 
{    
    bitree *tree = NULL;
    int grade = 0;
    
    Student s1 = {"Darcy", 80};
    Student s2 = {"Jane", 98};
    Student s3 = {"Thor", 70};
    Student s4 = {"Brock", 75};
    Student s5 = {"Steve", 67};
    Student s6 = {"Natasha", 73};
    Student s7 = {"Tony", 85};
    Student s8 = {"Bruce", 59};
    Student s9 = {"Clint", 62};
    Student s10 = {"Wanda", 77};
    Student s11 = {"Pietro", 64};
    Student s12 = {"Peter", 70};
    Student s13 = {"Stephen", 66};
    Student s14 = {"Carol", 74};
    Student s15 = {"T'Challa", 69};
    Student s16 = {"Gamora", 58};

    
    tree = insert_node(tree, s1);
    tree = insert_node(tree, s2);
    tree = insert_node(tree, s3);
    tree = insert_node(tree, s4);
    tree = insert_node(tree, s5);
    tree = insert_node(tree, s6);
    tree = insert_node(tree, s7);
    tree = insert_node(tree, s8);
    tree = insert_node(tree, s9);
    tree = insert_node(tree, s10);
    tree = insert_node(tree, s11);
    tree = insert_node(tree, s12);
    tree = insert_node(tree, s13);
    tree = insert_node(tree, s14);
    tree = insert_node(tree, s15);
    tree = insert_node(tree, s16);

    
    display_left_right(tree);
    printf("\n");

    delete_node(tree, s7);

    display_left_right(tree);

    printf("Now we're gonna find all the students with grade less than set value. Please input the value\n");
    scanf("%d", &grade);
    print_students(tree, grade);
    return 0; 
} 

//симетричний зліва направо
void display_left_right(bitree *tree)
{
    if(tree!=NULL)
    {
        display_left_right(tree->left);
        printf("Student: %s, average grade: %d\n", tree->stud.name, tree->stud.av_grade);
        display_left_right(tree->right);
    }
}

//створює нову ноду
bitree* create_node(Student student)
{
    bitree* temp_tree = (bitree*)malloc(sizeof(bitree));
    temp_tree->stud = student;
    temp_tree->left = NULL;
    temp_tree->right = NULL;
    return temp_tree;
}

//вставляє нову в дерево
bitree* insert_node(bitree *root, Student student)
{
    //якщо пусте дерево створює корінь
    if(root == NULL)
    {
        return create_node(student);
    }
    //інакше, якщо менше ніж корінь, відправляє вліво
    if(student.av_grade < root->stud.av_grade)
        root->left = insert_node(root->left, student);
    //якщо більше ніж корінь вправо
    else
        root->right = insert_node(root->right, student);

    return root;
}

//here could have been your (ad) function to delete a node


bitree* delete_node(bitree *root, Student student)
{
    if(root == NULL)
    {
        printf("Error of delete\n");
        return NULL;
    }

    if (strcmp(root->stud.name, student.name) == 0 && root->stud.av_grade == student.av_grade)
    {
        if(root->left==NULL)
        {
            bitree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            bitree *temp = root->left;
            free(root);
            return temp;
        }

        bitree* temp =  findMin(root->right);
        root->stud = temp->stud;
        root->right = delete_node(root->right, temp->stud);
    }
    else
    {
        if(root->stud.av_grade>student.av_grade)
            root->left = delete_node(root->left, student);
        else
            root->right = delete_node(root->right, student);   
    }

    return root;
}


bitree* findMin(bitree* Node)
{
    while(Node->left!=NULL)
        Node = Node->left;

    return Node;
}
//here could have been your (ad) function to find student with grade lower than the set value


void print_students(bitree* root, int grade)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        print_students(root->left, grade);
        if(root->stud.av_grade < grade)
            printf("Student: %s, with grade %d\n", root->stud.name, root->stud.av_grade);
        print_students(root->right, grade);
    }
}