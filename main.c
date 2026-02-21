#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//heba dababat
//1230151
//sec 3
                             /* تم بحمد الله ,ان شاء الله العلامة الكاملة */


typedef struct Task_Node* Tree;
typedef struct Task_Node* ptr;

typedef struct Task_Node {
    int ID;        //task id
    char name[50];      //task name
    char date[50];       //task date
    float duration;         //task duration time
    ptr left;
    ptr right ;
}Task_Node;


//functions prototype :
Tree Create_Task(int ID,char name[],char date[],float duration);
Tree Insert_Task_ByID(Tree T,int ID,char name[],char date[],float duration);
void Print_Tasks(Tree T);
Tree Load_File(Tree T);
Tree Delete_Task(Tree T,int ID);
Tree Find_Min(Tree T);
int Is_ID_exist(Tree T,int ID);
int Is_Name_exist(Tree T, char name[]);
Tree Find_by_Name(Tree T,char name[]);
Tree Find_by_ID(Tree T,int ID);
Tree Insert_Task_ByName(Tree T,int ID,char name[],char date[],float duration);
Tree Rebuild (Tree T,int flag);
Tree Insert_Task_ByDate(Tree T,int ID,char name[],char date[],float duration);
Tree Insert_Task_ByDuration(Tree T,int ID,char name[],char date[],float duration);
Tree MakeEmpty_Task(Tree T);
int Tree_height (Tree T);
int Tree_Size(Tree T);
int numOfLeaves(Tree T);
int numOfInternlNodes(Tree T);


int ID;
char name[50];
char date[50];
float duration;
Tree copied_tree=NULL;
int main()
{

    Tree unperformed=NULL;
    Tree performed=NULL;
    int option,choice;
        do{
        //the menu :
        printf("\nchoose an option :\n");
        printf("1- Load Tasks File \n");
        printf("2- Add a New Task \n");
        printf("3- Delete a Task \n");
        printf("4- Search for a Task \n");
        printf("5- Perform a Task \n");
        printf("6- View Unperformed Tasks  \n");
        printf("7- View Performed Tasks \n");
        printf("8- Restructure the Tasks BST \n");
        printf("9- View the tasks BST info \n");
        printf("10- Exit \n");
        scanf("%d",&option);

    switch(option){
        case 1: //load form a file
            unperformed =Load_File(unperformed);
            printf("all tasks are loaded\n");
            break;
        case 2:
            printf("Enter Task ID :6\n");
            scanf("%d",&ID);
            int x =Is_ID_exist(unperformed,ID);
            if(x==1){
                printf("ID is already exist \n");
            }else{
            printf("Enter Task name : \n");
            gets(name);
            gets(name);
            printf("Enter Task Date : \n");
            gets(date);
            printf("Enter Task Duration Time : \n");
            scanf("%f",&duration);
            Insert_Task_ByID(unperformed,ID,name,date,duration);

            }
            break;
        case 3 :  //delete a task
            printf("enter the ID for the task you want to delete : \n");
            scanf("%d",&ID);
            if(!Is_ID_exist(unperformed,ID)){
              printf("There is no such ID\n");
              break;
            }else{
            Rebuild(unperformed,1);
            unperformed= Delete_Task(unperformed,ID);
            }
            break;
        case 4 : //search for a task
            printf("Enter Task name you want to Search for : \n");
            gets(name);
            gets(name);
            if(!Is_Name_exist(unperformed,name)){
                    printf("There is no such name \n");
                    break;
            }else {
                unperformed=Rebuild(unperformed,2);
                Tree Found =Find_by_Name(unperformed,name);
                printf("Task info you are searching for :\n");
                printf("ID = %-10dName = %-30sDate = %-20sduration time = %-10f\n",Found->ID,Found->name,Found->date,Found->duration);
            }
            break;
        case 5 :  // perform a task
            printf("Enter Task ID You want to perform:\n");
            scanf("%d",&ID);
            if(!Is_ID_exist(unperformed,ID))
                printf("there is no such ID \n");
            else{
                Tree Found = Find_by_ID(unperformed,ID);
                performed=Insert_Task_ByID(performed,Found->ID,Found->name,Found->date,Found->duration);
            }
            break;
        case 6 :  //view unperformed tasks
            copied_tree= MakeEmpty_Task(copied_tree);
            if(unperformed==NULL)
            {
                printf("empty tree\n");
                break;
            }
            copied_tree=Rebuild(unperformed,2);
            Print_Tasks(copied_tree);
            break;
        case 7 : // view performed tasks
            Print_Tasks(performed);
            break;
        case 8 :  //restructure the task BST
            printf("enter the option on which you want to rebuild the tree : \n");
            printf("1- ID\n");
            printf("2- Name\n");
            printf("3- Date\n");
            printf("4- duration time\n");
            scanf("%d",&choice);
            copied_tree=MakeEmpty_Task(copied_tree);
            if(choice==1){
                copied_tree=Rebuild(unperformed,1);
                Print_Tasks(copied_tree);
            }else if(choice==2){
                copied_tree=Rebuild(unperformed,2);
                Print_Tasks(copied_tree);
            }else if(choice==3){
               copied_tree= Rebuild(unperformed,3);
               Print_Tasks(copied_tree);
            }else if(choice==4){
              copied_tree=Rebuild(unperformed,4);
              Print_Tasks(copied_tree);
            }else
            printf("there is no such option :");
            Rebuild(unperformed,1);
            break;
        case 9 :  // view task info
            printf("tree information :\n");
            printf("1- Tree height : %d\n",Tree_height(unperformed));
            printf("2- Tree size : %d\n",Tree_Size(unperformed));
            printf("3- number of Tree leaves : %d\n",numOfLeaves(unperformed));
            printf("4- number of internal nodes : %d\n",numOfInternlNodes(unperformed));
            break;
        case 10 : //exist
            return 0;
            break;
        default : printf("There is no such option \n");
        break;
       }
    }while(option!=10);

    return 0;
}
Tree Create_Task(int ID,char name[],char date[],float duration){
    Tree new_Task =(Tree)malloc(sizeof(struct Task_Node));
    new_Task->ID=ID;
    strcpy(new_Task->name,name);
    strcpy(new_Task->date,date);
    new_Task->duration=duration;
    new_Task->left=new_Task->right=NULL;
    return new_Task;

}
Tree Insert_Task_ByID(Tree T,int ID,char name[],char date[],float duration){
    if(T==NULL)
        return Create_Task(ID,name,date,duration);
    if(ID<T->ID)
        T->left=Insert_Task_ByID(T->left,ID,name,date,duration);
    else
        T->right=Insert_Task_ByID(T->right,ID,name,date,duration);
    return T;
}
void Print_Tasks(Tree T){
   if(T==NULL)
     return NULL;
    else{
    Print_Tasks(T->left);
    printf("ID = %-10dName = %-30sDate = %-20sduration time = %-10f\n",T->ID,T->name,T->date,T->duration);
    Print_Tasks(T->right);
    }
}
Tree Load_File(Tree T){
    FILE *input=fopen("tasks.txt","r");
    if(input == NULL){
        printf("cant open file \n");
    }
    char Line[70];
    while(fgets(Line,sizeof(Line),input) !=NULL){

        char *token= strtok(Line,"#");
        ID =atoi(token);
        token=strtok(NULL,"#");
        strcpy(name,token);
        token=strtok(NULL,"#");
        strcpy(date,token);
        token=strtok(NULL,"#");
        duration=atof(token);
        T=Insert_Task_ByID(T,ID,name,date,duration);

    }
    fclose(input);
    return T;
}
Tree Delete_Task(Tree T,int ID){
    Tree tempCell,child;
    if(T==NULL)
        printf("element not found \n");
    else if(ID<T->ID)
        T->left=Delete_Task(T->left,ID);
    else if(ID>T->ID)
        T->right=Delete_Task(T->right,ID);
    else if(T->left && T->right){
            tempCell=Find_Min(T->right);
            T->ID=tempCell->ID;
            strcpy(T->name,tempCell->name);
            strcpy(T->date,tempCell->date);
            T->duration=tempCell->duration;
            T->right=Delete_Task(T->right,T->ID);
    }else{
        tempCell = T;
        if(T->left==NULL)
            child=T->right;
        else if(T->right ==NULL)
            child=T->left;
        free(tempCell);
        return child;
    }
    return T;
}
Tree Find_Min(Tree T){
    if(T!=NULL)
        while(T->left != NULL)
            T=T->left;
    return T;
}
int Is_ID_exist(Tree T,int ID){
    if(T==NULL)
        return 0;
    if(T->ID==ID)
        return 1;
    if(ID<T->ID)
        return Is_ID_exist(T->left,ID);
    else
        return Is_ID_exist(T->right,ID);
}
int Is_Name_exist(Tree T, char name[]){
    if(T==NULL)
        return 0;
    if(strcmp(name,T->name)==0)
        return 1;
    if (strcmp(name,T->name)>0)
        return Is_Name_exist(T->right,name);
    else
        return Is_Name_exist(T->left,name);
}
Tree Find_by_Name(Tree T,char name[]){
    if(T==NULL)
        printf("empty tree ");
    else if(strcmp(name,T->name)>0)
        return Find_by_Name(T->right,name);
    else if(strcmp(name,T->name)<0)
        return Find_by_Name(T->left,name);
    else
        return T;
}
Tree Find_by_ID(Tree T,int ID){
    if(T==NULL)
        printf("Empty Tree\n");
    if(ID<T->ID)
        return Find_by_ID(T->left,ID);
    else if (ID>T->ID)
        return Find_by_ID(T->right,ID);
    else return T;
}
Tree Insert_Task_ByName(Tree T,int ID,char name[],char date[],float duration){
    if(T==NULL)
       return Create_Task(ID,name,date,duration);
    if(strcmp(name,T->name)<0)
        T->left=Insert_Task_ByName(T->left,ID,name,date,duration);
    else if(strcmp(name,T->name)>0)
        T->right=Insert_Task_ByName(T->right,ID,name,date,duration);
    return T;
}
Tree Rebuild (Tree T,int flag){
    if(flag==1){
        if(T->left!=NULL)
          copied_tree=Rebuild(T->left,1);
          copied_tree=Insert_Task_ByID(copied_tree,T->ID,T->name,T->date,T->duration);
        if(T->right!=NULL)
            copied_tree=Rebuild(T->right,1);
    }
    else if(flag==2){
        if(T->left!=NULL)
        copied_tree=Rebuild(T->left,2);
          copied_tree=Insert_Task_ByName(copied_tree,T->ID,T->name,T->date,T->duration);
        if(T->right!=NULL)
            copied_tree=Rebuild(T->right,2);
    }
   else if(flag==3){
        if(T->left!=NULL)
        copied_tree=Rebuild(T->left,3);
        copied_tree=Insert_Task_ByDate(copied_tree,T->ID,T->name,T->date,T->duration);
        if(T->right !=NULL)
            copied_tree=Rebuild(T->right,3);
    }
    else if(flag==4){
        if(T->left!=NULL)
        copied_tree=Rebuild(T->left,4);
        copied_tree=Insert_Task_ByDuration(copied_tree,T->ID,T->name,T->date,T->duration);
        if(T->right!=NULL)
            copied_tree=Rebuild(T->right,4);
    }
    return copied_tree;
}
Tree Insert_Task_ByDate(Tree T,int ID,char name[],char date[],float duration){
    if(T==NULL)
       return Create_Task(ID,name,date,duration);
    if(strcmp(date,T->date)<0)
        T->left=Insert_Task_ByDate(T->left,ID,name,date,duration);
    else
        T->right=Insert_Task_ByDate(T->right,ID,name,date,duration);
    return T;

}
Tree Insert_Task_ByDuration(Tree T,int ID,char name[],char date[],float duration){
    if(T==NULL)
        return Create_Task(ID,name,date,duration);
    if(duration<T->duration)
        T->left=Insert_Task_ByDuration(T->left,ID,name,date,duration);
    else
        T->right=Insert_Task_ByDuration(T->right,ID,name,date,duration);
    return T;
}
Tree MakeEmpty_Task (Tree T){
    if(T!=NULL){
        MakeEmpty_Task(T->left);
        MakeEmpty_Task(T->right);
        free(T);
    }
    return NULL;
}
int Tree_height (Tree T){
    if(T==NULL)
        return -1;
    int left_side =Tree_height(T->left);
    int Right_side=Tree_height(T->right);

    if(left_side>Right_side)
        return left_side+1;
    else
        return Right_side+1;
}
int Tree_Size(Tree T){
    if(T==NULL)
        return 0;
    if(T != NULL ){
        return  Tree_Size(T->left)+Tree_Size(T->right)+1;
    }
}
int numOfLeaves(Tree T){
    if(T==NULL)
        return 0;
    if(T->left==NULL&&T->right ==NULL)
        return 1;
    return numOfLeaves(T->left)+numOfLeaves(T->right);
}
int numOfInternlNodes(Tree T){
    return Tree_Size(T)-numOfLeaves(T);
}
