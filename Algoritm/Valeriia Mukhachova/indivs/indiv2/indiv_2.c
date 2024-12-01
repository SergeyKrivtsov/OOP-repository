#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum 
{ 
    Sign, Terminal 
}NodeType;

typedef struct Node 
{
    NodeType type;
    char symbol;
    struct Node* left;
    struct Node* right;
} Node;

Node* simplify(Node* root);
Node* transform(Node* root);
Node* create_node(NodeType type, char value);
void skip_spaces(const char** str);
Node* parse_term(const char** str);
Node* parse_formula(const char** str);
void print_tree(Node* root);
void free_tree(Node* root);
void process_formulas(const char* filename);

int main() 
{
    const char* filename = "formulas.txt";
    process_formulas(filename);
    return 0;
}



//cпрощення дерева за правилами:(f+0), (0+f), (f-0), (f*1), (1*f), (f*0), (0*f)
Node* simplify(Node* root) 
{
    if (root == NULL) 
        return NULL;

    //спрощуємо праве та ліве піддерево
    root->left = simplify(root->left);
    root->right = simplify(root->right);

    //якщо це знак, то перевіряємо знак та піддерева
    if (root->type == Sign) 
    {
        if (root->symbol == '+') 
        {
            if (root->left!=NULL && root->left->type == Terminal && root->left->symbol == '0') 
            {
                //(0+f)->f
                return root->right;
            }
            if (root->right!=NULL && root->right->type == Terminal && root->right->symbol == '0') 
            {
                //(f+0)->f
                return root->left;
            }
        } 
        else if (root->symbol == '-') 
        {
            if (root->right!=NULL && root->right->type == Terminal && root->right->symbol == '0') 
            {
                //(f-0)->f
                return root->left;
            }
        } 
        else if (root->symbol == '*') 
        {
            if (root->left!=NULL && root->left->type == Terminal && root->left->symbol == '1') 
            {
                //(1*f)->f
                return root->right;
            }
            if (root->right!=NULL && root->right->type == Terminal && root->right->symbol == '1') 
            {
                //(f*1)->f
                return root->left;
            }
            if (root->left!=NULL && root->left->type == Terminal && root->left->symbol == '0') 
            {
                //(0*f)->0
                return create_node(Terminal, '0');
            }
            if (root->right!=NULL && root->right->type == Terminal && root->right->symbol == '0') 
            {
                //(f*0)->0
                return create_node(Terminal, '0');
            }
        }
    }
    return root;
}

//перетворення дерева за заданними правилами:
//(f1 + f2)*f3 --->   (f1 * f3) + (f2 * f3)
//(f1 - f2)*f3 --->   (f1 * f3) - (f2 * f3)
//(f1*(f2 + f3)) ---> (f1 * f2) + (f1 * f3)
//(f1*(f2 - f3)) ---> (f1 * f2) - (f1 * f3)
Node* transform(Node* root) 
{
    if (root == NULL)
        return NULL;

    //перетворюємо ліве і праве піддерево
    root->left = transform(root->left);
    root->right = transform(root->right);

    //якщо це знак, перевіряємо чи формула попадає під одне з правил
    if (root->type == Sign) 
    {
        //(f1+f2)*f3 -> (f1*f3)+(f2*f3)
        if (root->symbol == '*' && root->left!=NULL && root->left->type == Sign && root->left->symbol == '+' && root->right!=NULL) 
        {
            Node *f1 = root->left->left; 
            Node *f2 = root->left->right;
            Node *f3 = root->right;
            //створюємо (f1*f3)
            Node *part1 = create_node(Sign, '*');
            part1->left = f1;
            part1->right = f3;
            //створюємо (f2*f3)
            Node *part2 = create_node(Sign, '*');
            part2->left = f2;
            part2->right = f3;
            //(f1*f3)+(f2*f3)
            Node *combined = create_node(Sign, '+');
            combined->left = part1;
            combined->right = part2;
            return combined;
        }

        //(f1-f2)*f3->(f1*f3)-(f2*f3)
        if (root->symbol == '*' && root->left!=NULL && root->left->type == Sign && root->left->symbol == '-' && root->right!=NULL) 
        {
            Node *f1 = root->left->left;
            Node *f2 = root->left->right;
            Node *f3 = root->right;
            //створюємо (f1*f3)
            Node *part1 = create_node(Sign, '*');
            part1->left = f1;
            part1->right = f3;
            //створюємо (f2*f3)
            Node *part2 = create_node(Sign, '*');
            part2->left = f2;
            part2->right = f3;
            //створюємо (f1*f3)-(f2*f3)
            Node *combined = create_node(Sign, '-');
            combined->left = part1;
            combined->right = part2;
            return combined;
        }

        //(f1*(f2+f3))->(f1*f2)+(f1*f3)
        if (root->symbol == '*' && root->right!=NULL && root->right->type == Sign && root->right->symbol == '+') 
        {
            Node *f1 = root->left;
            Node *f2 = root->right->left;
            Node *f3 = root->right->right;
            //створюємо (f1*f2)
            Node *part1 = create_node(Sign, '*');
            part1->left = f1;
            part1->right = f2;
            //створюємо (f1*f3)
            Node *part2 = create_node(Sign, '*');
            part2->left = f1;
            part2->right = f3;
            //створюємо (f1*f2)+(f1*f3)
            Node *combined = create_node(Sign, '+');
            combined->left = part1;
            combined->right = part2;
            return combined;
        }

        //(f1*(f2-f3))->(f1*f2)-(f1*f3)
        if (root->symbol == '*' && root->right!=NULL && root->right->type == Sign && root->right->symbol == '-') 
        {
            Node *f1 = root->left;
            Node *f2 = root->right->left;
            Node *f3 = root->right->right;
            //створюємо (f1*f2)
            Node *part1 = create_node(Sign, '*');
            part1->left = f1;
            part1->right = f2;
            //створюємо (f1*f3)
            Node *part2 = create_node(Sign, '*');
            part2->left = f1;
            part2->right = f3;
            //створюємо (f1*f2)-(f1*f3)
            Node *combined = create_node(Sign, '-');
            combined->left = part1;
            combined->right = part2;
            return combined;
        }
    }
    return root;
}

//створення нового вузла
Node* create_node(NodeType type, char value) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->symbol = value;
    node->left = node->right = NULL;
    return node;
}

//виводить дерево у вигляді формули
void print_tree(Node* root) 
{
    if (root == NULL) return;
    //якщо термінал - виводить символ
    if (root->type == Terminal) 
    {
        printf("%c", root->symbol);
    } 
    //якщо знак - cпочатку рекурсивно виводить ліве піддерево, знак, праве дерево
    else 
    {
        printf("(");
        print_tree(root->left);
        printf(" %c ", root->symbol);
        print_tree(root->right);
        printf(")");
    }
}

//пропустити пробели
void skip_spaces(const char** str) 
{
    while (**str == ' ') 
        (*str)++;
}

//парсинг терминалу(цифра або літера)
Node* parse_term(const char** str) 
{
    skip_spaces(str);
    if (isdigit(**str)||isalpha(**str)) 
    {
        Node* node = create_node(Terminal, **str);
        (*str)++;
        return node;
    }
    else 
    {
        printf("Mistake: waiting for a terminal but got the '%c'\n", **str);
        exit(1);
    }
}

//парсинг формули
Node* parse_formula(const char** str) 
{
    skip_spaces(str);
    //якщо формула починається з дужки
    if (**str == '(') 
    {
        //пропустити дужку
        (*str)++; 
        //рекурсинвно ліву частину формули
        Node* left = parse_formula(str); 

        skip_spaces(str);

        //зчитати знак
        if (**str == '+' || **str == '-' || **str == '*') 
        {
            char operator = **str;
            Node* root = create_node(Sign, operator);
            (*str)++;
            //ліва частина дерева
            root->left = left; 
            skip_spaces(str);
            //права частина дерева
            root->right = parse_formula(str); 
            skip_spaces(str);

            if (**str == ')') 
            {
                (*str)++;
                return root;
            }
            else 
            {
                printf("Mistake: waiting for a ')'\n");
                exit(1);
            }
        } 
        else 
        {
            printf("Mistake: waited for an sign, but got the '%c'\n", **str);
            exit(1);
        }
    }

    //якщо не починається з дужки - повиннен бути термінал
    return parse_term(str);
}

//обробляємо формули з файлу
void process_formulas(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file==NULL) 
    {
        perror("coulnd't open the file");
        exit(1);
    }
    char line[256];
    while (fgets(line, sizeof(line), file)!=NULL) 
    {
        const char* cursor = line;
        Node* root = parse_formula(&cursor);

        printf("Original formula:    ");
        print_tree(root);
        printf("\n");

        root = simplify(root);
        printf("Simplified formula:  ");
        print_tree(root);
        printf("\n");

        root = transform(root);
        printf("Transformed formula: ");
        print_tree(root);
        printf("\n");

        free_tree(root);
        printf("----------------------------\n");
    }

    fclose(file);
}

//рекурсивно звільнює пам'ять для дерева
void free_tree(Node* root) 
{
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}