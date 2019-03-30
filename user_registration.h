#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct user{
    char name[50],cpf[15];
    int age, id;
    float height, weight;
};

void open_file(FILE *file){
    file = fopen("users.txt","a+b");
    if(file == NULL){
        printf("Error in the file creation.");
        system("pause");
        exit(0);
    }
}

void line(){
    for(int i=0;i<50;i++)printf("-");
    printf("\n");
}

void menu(bool *leave, FILE *file, int *users);
struct user read_data();
bool repeat(FILE *file, struct user y);
bool insert_user(FILE *file,bool need_check,struct user y);
bool change_user(FILE *file, int id);
bool delete_user(FILE *file, int id);
void print_users(FILE *file);
void print_user(struct user x);

void menu(bool *leave, FILE *file, int *users){
    line();
    printf("\t(%d users)\n\n", *users);
    printf("\tOption 1 - Insert user\n");
    if(*users != 0)printf("\tOption 2 - Change user\n");
    if(*users != 0)printf("\tOption 3 - Delete user\n");
    if(*users != 0)printf("\tOption 4 - Print users\n");
    printf("\tOption 0 - Leave program\n");
    line();

    printf("Insert a option: ");
    int option,id;
    scanf("%d", &option);
    system("cls");
    line();

    open_file(file);
    bool operation_sucess = false;

    switch(option){
        case 0:
            printf("Leaving program...\n");
            line();
            *leave = true;
            return 0;

        case 1:
            operation_sucess = true;
            struct user x;
            if(insert_user(file,true,x))(*users)++;
            else operation_sucess = false;
            break;

        case 2:
            printf("Insert a number id for change: ");
            scanf("%d", &id);
            if(change_user(file,id))operation_sucess = true;
            break;

        case 3:
            printf("Insert a number id for delete: ");
            scanf("%d", &id);
            if(delete_user(file,id)){
                operation_sucess = true;
                (*users)--;
            }
            break;

        case 4:
            print_users(file);
            operation_sucess = true;
            break;
    }

    fclose(file);

    line();
    if(operation_sucess)printf("Sucess\n");
    else printf("Failure\n");
    line();

    system("pause");
    system("cls");
}

struct user read_data(){
    struct user x;

    printf("\tInsert a number id: ");
    scanf("%d", &x.id);
    printf("\n\tName: ");
    fflush(stdin);
    gets(x.name);
    fflush(stdin);
    printf("\n\tCPF: ");
    fflush(stdin);
    gets(x.cpf);
    fflush(stdin);
    printf("\n\tAge: ");
    scanf("%d", &x.age);
    printf("\n\tHeight: ");
    scanf("%f", &x.height);
    printf("\n\tWeight: ");
    scanf("%f", &x.weight);

    return x;
}

bool repeat(FILE *file, struct user y){
    fseek(file,SEEK_SET,0);
    struct user x;
    fread(&x,sizeof(struct user),1,file);

    while(!feof(file)){
        if(x.id==y.id)return true;
        fread(&x,sizeof(struct user),1,file);
    }

    return false;
}

bool insert_user(FILE *file,bool need_check,struct user y){
    if(need_check){
        y = read_data();
        if(repeat(file,y)){
            printf("\nThis id already exist\n");
            return false;
        }
    }

    fseek(file,SEEK_END,2);
    fwrite(&y,sizeof(struct user),1,file);

    return true;

}

bool change_user(FILE *file, int id){
    bool sucess = false;
    fseek(file,SEEK_SET,0);
    struct user x;
    fread(&x,sizeof(struct user),1,file);
    FILE *file_aux = fopen("auxiliar.txt","a+b");

    while(!feof(file)){
        if(x.id == id){
            printf("\n\tUser found:");
            print_user(x);
            x = read_data();
            sucess = true;
        }
        insert_user(file_aux,false,x);
        fread(&x,sizeof(struct user),1,file);
    }

    fclose(file_aux);
    fclose(file);
    remove("users.txt");
    rename("auxiliar.txt","users.txt");

    return sucess;
}

bool delete_user(FILE *file, int id){
    bool sucess = false;
    fseek(file,SEEK_SET,0);
    struct user x;
    fread(&x,sizeof(struct user),1,file);
    FILE *file_aux = fopen("auxiliar.txt","a+b");

    while(!feof(file)){
        if(x.id != id){
            insert_user(file_aux,false,x);
        }
        else{
            sucess = true;
            printf("\n\tUser found:");
            print_user(x);
        }
        fread(&x,sizeof(struct user),1,file);
    }

    fclose(file_aux);
    fclose(file);
    remove("users.txt");
    rename("auxiliar.txt","users.txt");

    return sucess;
}

void print_users(FILE *file){
    fseek(file,SEEK_SET,0);
    struct user x;
    fread(&x,sizeof(struct user),1,file);

    printf("\tUsers:\n");
    while(!feof(file)){
        print_user(x);
        fread(&x,sizeof(struct user),1,file);
    }
}

void print_user(struct user x){
    printf("\n\tId: %d\n",x.id);
    printf("\tName: %s\n",x.name);
    printf("\tCPF: %s\n",x.cpf);
    printf("\tAge: %d\n",x.age);
    printf("\tHeight: %.2f\n",x.height);
    printf("\tWeight: %.2f\n\n",x.weight);
}
