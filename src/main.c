#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "person.h"

#define   DATABASE                "database.txt"

#define   TEXT_ADD_PERSON         "1. Add new person"
#define   TEXT_REMOVE_PERSON      "2. Remove a person"
#define   TEXT_UPDATE_PERSON      "3. Update a person"
#define   TEXT_LIST_PERSON        "4. List all person "
#define   TEXT_FIND_PERSON        "5. Find a person"
#define   TEXT_EXIT_PERSON        "6. Exit Program"
#define   TEXT_CURSOR             "> "

void print_menu(void);
bool option_select(int option);
int count_items(void);

void person_add_new(void);
void person_delete(void);
void person_update(void);
void person_list(void);
void person_find(void);

bool is_database_exists(void);


int main(void)
{
    int option;

    do
    {
        print_menu();
        scanf("%d",&option);
        getchar();  
    } while (option_select(option));

    return EXIT_SUCCESS;
}

void print_menu(void)
{
    printf("%s\n", TEXT_ADD_PERSON);
    printf("%s\n", TEXT_REMOVE_PERSON);
    printf("%s\n", TEXT_UPDATE_PERSON);
    printf("%s\n", TEXT_LIST_PERSON);
    printf("%s\n", TEXT_FIND_PERSON);
    printf("%s\n", TEXT_EXIT_PERSON);
    printf("%s", TEXT_CURSOR);    
}

bool option_select(int option)
{
    bool status = true;

    switch (option)
    {
    case 1:
        //Call a function to add new user 
        person_add_new();
        break;

    case 2:
        //Call a function to remove a user
        printf("Chamo a funcao delete\n");
        person_delete(); 
        break;

    case 3:
        //Call a function to update a user 
        person_update();
        break;  

    case 4:
        //Call a function to list all users 
        person_list();
        break;

    case 5:
        //Call a function to find a user 
        person_find();
        break;  

    case 6:
        status = false;
        break;
    
    default:
        //Show a error message
        break;
    }

    return status;
}

void person_add_new(void)
{
    person_t person;
    FILE *f;

    printf("Type a name: ");
    fgets(person.name, PERSON_NAME_LEN - 1, stdin);
    person.name[strlen(person.name)-1] = 0;

    printf("Type an address: ");
    fgets(person.address, PERSON_ADDRESS_LEN - 1, stdin);
    person.address[strlen(person.address)-1] = 0;
    
    printf("Type an age: ");
    scanf("%d", &person.age);
    getchar();

    if(is_database_exists() == false)
    {
        f = fopen(DATABASE, "w");
    }
    else
    {
        f = fopen(DATABASE, "a");
    }

    char format[250] = "";
    snprintf(format, 250, "%s , %s , %d\n", person.name, person.address, person.age);
    fprintf(f, "%s", format);
    fclose(f);
}

void person_delete(void)
{
    int items = count_items(); 

    person_t *persons = (person_t *) malloc(sizeof(person_t) * items);
    if(persons == NULL)
    {
        return;
    }
   
    printf("Foi abrir o arquivo para leitura\n");
    FILE *f = fopen(DATABASE, "r");
    printf("O arquivo foi abrto com sucesso\n");

    for(int i = 0; i < items; i++)
    {
        char buffer[240] = "";
        fgets(buffer, 240, f);

        char *data = strtok(buffer, ".");
        strncpy(persons[i].name, data, PERSON_NAME_LEN);
        data = strtok(NULL, ",");
        strncpy(persons[i].address, data, PERSON_ADDRESS_LEN);
        data = strtok(NULL, ",");
        persons[i].age = atoi(data);
    }

    fclose(f);

    char name_delete[PERSON_NAME_LEN] = ""; 
    printf("Type a name to delete");
    fgets(name_delete,PERSON_NAME_LEN - 1, stdin);
    name_delete[strlen(name_delete) - 1] = 0; 

    for(int i = 0; i < items; i++)
    {
        if(strncmp(name_delete, persons->name, PERSON_NAME_LEN) == 0)
        {
            memset(&persons[i], 0 , sizeof(person_t));
            break;
        }
    }

    f = fopen(DATABASE, "w");
    
    for(int i = 0; i < items; i++)
    {
        if(persons[i].name[0] == '\0' || persons[i].address[0] == '\0') 
        {
            continue;
        }
 
        fprintf(f, "%s,  %s,  %d\n", persons[i].name, persons[i].address, persons->age);
    }

    free(persons);
}

void person_update(void)
{
    printf("Update a user\n");
}

void person_list(void)
{
    printf("List all users\n");
}

void person_find(void)
{
    printf("Find a user\n");
}

bool is_database_exists(void)
{
    bool status = false;

    FILE *f = fopen(DATABASE, "r");
    if(f != NULL)
    {
        fclose(f);
        status = true;
    }

    return status;    
}

int count_items(void)
{

    FILE *f;
    int items = 0;
 
    printf("Entarda na funcao count items\n");

    if(is_database_exists())
    {
        f = fopen(DATABASE, "r");
    } 
    else
    {
        return -1;
    }

    char c = fgetc(f);
    
    while(c != EOF)
    {
        if(c == '\n')
        {
            items++;
        }    

        c = fgetc(f);
    }
    
    fclose(f);
    printf("Itens: %d\n", items);
    
    return items;  
}