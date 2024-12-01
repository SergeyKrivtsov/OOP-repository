// Розробіть систему для реєстрації гостей на подію,
// Реалізувавши АТД Відображення (Map) на базі
// хеш-таблиці у вигляді масиву списків, елементи яких
// є парами. Про кожного гостя зберігається інформація:
// унікальний ID, місто з якого прибув, телефон.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define table_size 10
#define name_length 50
#define city_length 50
#define phone_length 15
#define temp_length 50

typedef struct Guest 
{
    int id;
    char first_name[name_length];
    char last_name[name_length];
    char city[city_length];
    char phone[phone_length];
    struct Guest *next;
}Guest;

typedef struct HashTable 
{
    Guest *table[table_size];
}HashTable;

int Menu();
void Work(int i, HashTable *ht);
unsigned int hash(int id);
HashTable* create_table();
void add_guest(HashTable *ht, int id,const char *first_name, const char *last_name, const char *city, const char *phone);
void read_guests_from_file(const char *filename, HashTable *ht);
void print_table(HashTable *ht);
Guest* find_guest(HashTable *ht, int id);
void delete_guest(HashTable *ht, int id);
void free_table(HashTable *ht);
int get_number_in_range(int left, int right);


int main() 
{
    HashTable *ht = create_table();

    read_guests_from_file("guests.txt", ht);

    int menu_switch;
    char ch = 'y';
    while (ch=='y'||ch=='Y')
    {
        menu_switch = Menu();
        Work(menu_switch, ht);
        printf("Would you like to continue? Enter 'y' if yes, 'n' if no \n");
        ch = getchar();
        getchar();
    }

    free_table(ht);
    return 0;
}

int Menu()
{
    int i = 0;
    printf("Welcome to the menu!\n");
    printf("What whould you like to do?\n");
    printf("1. Output the whole table.\n");
    printf("2. Find a guest by ID.\n");
    printf("3. Delete guest by ID.\n");
    
    i = get_number_in_range (1, 3);
    return i;
}

void Work(int i, HashTable *ht)
{
    int id = 0;
    switch (i)
    {
        case 1:     
            printf("Table:\n");
            print_table(ht);
            break;
        case 2:
            printf("Input the ID:\n");
            id = get_number_in_range(0, __INT_MAX__);
            Guest *guest = find_guest(ht, id);
            if (guest) 
            {
                printf("Found - ID: %d, Name: %s %s, City: %s, Phone: %s\n", 
                    guest->id, guest->first_name, guest->last_name, guest->city, guest->phone);
            } 
            else 
            {
                printf("Guest not found.\n");
            }
            break;
        case 3:
            printf("Input the ID:\n");
            id = get_number_in_range(0, __INT_MAX__);
            printf("Deleting Guest with ID %d...\n", id);
            delete_guest(ht, id);
            break;
        default:
            printf("Sorry, that option is not found\n");

    }
}

//хеш-функція
unsigned int hash(int id) 
{
    return id % table_size;
}

//ініціалізація хеш-таблиці
HashTable* create_table() 
{
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < table_size; i++) 
    {
        ht->table[i] = NULL;
    }
    return ht;
}

//додавання гостя
void add_guest(HashTable *ht, int id, const char *first_name, const char *last_name, const char *city, const char *phone) 
{
    int index = hash(id);
    Guest *new_guest = (Guest*)malloc(sizeof(Guest));
    new_guest->id = id;
    strncpy(new_guest->first_name, first_name, name_length);
    strncpy(new_guest->last_name, last_name, name_length);
    strncpy(new_guest->city, city, city_length);
    strncpy(new_guest->phone, phone, phone_length);
    new_guest->next = ht->table[index];
    ht->table[index] = new_guest;
}

// Функція для читання гостей з файлу
void read_guests_from_file(const char *filename, HashTable *ht) 
{
    FILE *file = fopen(filename, "r");
    if (file==NULL) 
    {
        perror("Can't open the file.\n");
        return;
    }

    int id = 0;
    char city[city_length];
    char phone[phone_length]; 
    char first_name[name_length];
    char last_name[name_length];
    char line[city_length];
    while (fgets(line, sizeof(line), file)!=NULL) 
    {
        if (sscanf(line,  "%d %49s %49s %49s %15s", &id, first_name, last_name, city, phone) == 5) 
        {
            add_guest(ht, id, first_name, last_name, city, phone);
        } 
        else 
        {
            printf("Error during manipulating the line: %s\n", line);
        }
    }

    fclose(file);
}

//вивід усіх гостей
void print_table(HashTable *ht) 
{
    for (int i = 0; i < table_size; i++) 
    {
        Guest *current = ht->table[i];
        printf("Index %d:\n", i);
        while (current!=NULL) 
        {
            printf("    ID: %d, Name: %s %s, City: %s, Phone: %s\n", 
                current->id, current->first_name, current->last_name, current->city, current->phone);
            current = current->next;
        }
    }
}

//пошук гостя за ID
Guest* find_guest(HashTable *ht, int id) 
{
    int index = hash(id);
    Guest *current = ht->table[index];
    while (current!=NULL) 
    {
        if (current->id == id) 
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//видалення гостя
void delete_guest(HashTable *ht, int id) 
{
    int index = hash(id);
    Guest *current = ht->table[index];
    Guest *prev = NULL;
    while (current) 
    {
        if (current->id == id) 
        {
            if (prev!=NULL) 
            {
                prev->next = current->next;
            } 
            else 
            {
                ht->table[index] = current->next;
            }
            free(current);
            printf("Guest with ID %d deleted.\n", id);
            printf("Table After Deletion:\n");
            print_table(ht);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Guest with ID %d not found.\n", id);
}

//звільнення пам'яті
void free_table(HashTable *ht) 
{
    for (int i = 0; i < table_size; i++) 
    {
        Guest *current = ht->table[i];
        while (current!=NULL) 
        {
            Guest *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht);
}

//перевіряє, що користувач ввів саме число, і що воно попадає між заданих чисел 
int get_number_in_range(int left, int right) 
{ 
    int var = 0; 
    int bad_input = 0; 
    int i = 0; 
    int negative = 0;
     
    while(1) 
    { 
        var = 0, bad_input = 0, i = 0, negative = 0;
        char number[temp_length]; 
                 
        if (fgets(number, sizeof(number), stdin) == NULL) { 
            printf("Error reading input. Please try again.\n"); 
            clearerr(stdin); 
            continue;  
        } 
         
        //перевіряє, що користувач не натиснув тільки Enter 
        if(number[0]==10) 
        {     
            bad_input = 1; 
        } 
 
        //перевріяє, що користувач не ввів букви, або спец знаки. 
        while(number[i]!=' '&&number[i]!='\n'&&number[i]!='\0') 
        {
            if ((number[i] -'0')<0||(number[i] - '0')>9) 
            { 
                if(i==0&&number[i]=='-')
                {
                    negative = 1; 
                    i++;
                }
                else
                {
                    bad_input = 1;
                    break;
                } 
            } 
            else 
            {     
                //якщо це не буква або знак, переводить у число 
                var = var*10 + (number[i] - '0');  
                i++; 
            } 
        } 

        if(negative==1)
            var = -var;
 
        if(bad_input==1) 
            printf("Please, try again, only numbers.\n"); 
        else 
        { 
            //якщо не попадає в рамки, просить ввести знову 
            if(left==right && var != right) 
                printf("Please, try again and beware of the range.\n"); 
            else 
            { 
                if(var < left || var > right) 
                    printf("Please, try again and beware of the range.\n"); 
                else 
                    //якщо попадає в задані рамки виход з циклу  
                    break; 
            } 
        } 
    } 

    return var;   
} 