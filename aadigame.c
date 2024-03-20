#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#define BREADTH 9
#define HEIGHT 5

struct card
{
    char num[4];
    char color[100];
};
struct players
{
    int id;
    struct card player[108];
    struct players* llink;
    struct players* rlink;
};
struct stack
{
    struct card Card;
    struct stack* link;
};

int Randoms(int upper) 
{ 
    int i; 
    int num = (rand() % (upper)); 
    return num; 
} 
struct stack* push(struct stack* head,struct card Card)
{   
    struct stack* current=head;
    struct stack* newNode=(struct stack*) malloc(sizeof(struct stack));
    newNode->Card=Card;
    newNode->link=NULL;
    if(head==NULL)
    {
        return newNode;
    }
    else
    {
        newNode->link=head;
        head=newNode;
    }
    return head;
};
struct stack* shuffleDeck(struct stack* head,struct card Card[])
{
    int n=0;
    int a[200];
    while(n<108)
    {
        int con=0;
        int k;
        k=Randoms(108);
        for(int i=0;i<n;i++)
        {
            if(a[i]==k)
            {
                con=1;
                break;
            }
        }
        if(!con)
        {
            head=push(head,Card[k]);
            a[n]=k;
            n++;
        }

    }
    return head;
};
struct card pop(struct stack** head)
{
    struct card info;
    struct stack* current=*head;
    struct stack* previous=NULL;
        previous=*head;
        *head=previous->link;
        info=previous->Card;
        free(previous);
    
    return info;
   
};
void fill(struct card Card[])
{
    char data[][4]={"0","1","1","2","2","3","3","4","4","5","5","6","6","7","7","8","8","9","9","B","B","+2","+2","R","R"};
    char color[][20]={"\033[0;31m","\033[0;32m","\033[0;33m","\033[0;34m"};
    for(int i=0;i<4;i++)
    {
        for(int k=0;k<25;k++)
        {
            strcpy(Card[i*25+k].color,color[i]);
            strcpy(Card[i*25+k].num,data[k]);
        }
    }
    for(int i=100;i<104;i++)
    {
        strcpy(Card[i].num,"W");
        strcpy(Card[i].color,"\033[0;37m");
    }
     for(int i=104;i<108;i++)
    {
        strcpy(Card[i].num,"+4W");
        strcpy(Card[i].color,"\033[0;37m");
    }
}


void playerPattern(int cardCount,struct card Card[])
{
    if(cardCount<=9)
    {
    printf("  ");
    for(int i=0;i<cardCount;i++)
    {
        printf("%s",Card[i].color);
        for(int j=0;j<BREADTH;j++)
        {
            printf("_");
        }
        printf("   ");
    }
    printf("\n");
    for(int k=0;k<HEIGHT;k++)
    {
    for(int i=0;i<cardCount;i++)
    {
        printf(" ");
        printf("%s",Card[i].color);
        int n=0;
        printf("|");
        for(int j=0;j<BREADTH;j++)
        {
            if((j==0&&k==0)||(k==HEIGHT/2&&j==BREADTH/2))
            {
                n=strlen(Card[i].num);
                printf("%s",Card[i].num);
            } 
            if(k==HEIGHT-1&&j==BREADTH-strlen(Card[i].num))
            {
                n=strlen(Card[i].num);
                printf("%s",Card[i].num);
            }
            if(n>=1)
            {
                n--;
            }
            else
            printf(" ");
        }
        printf("|");
    }
    printf("\n");
    }
    printf("  ");
    for(int i=0;i<cardCount;i++)
    {
        
        printf("%s",Card[i].color);
        for(int j=0;j<BREADTH;j++)
        {
            printf("*");
        }
        printf("   ");
    }
    printf("\n");
    }
    else
    {
        int temp=cardCount-9;
        struct card a[100];
        int k=0;
        for(int i=0;i<cardCount;i++)
        {
            if(i>8)
            {
                a[k]=Card[i];
                k++;
            }
        }
        playerPattern(9,Card);
        playerPattern(temp,a);
    }
}
void distribute(struct card Card[],struct stack** head)
{
    for(int i=0;i<5;i++)
    {
        Card[i]=pop(head);
    }
}
int getcurrentsize(struct card car[])
{
    int count=0;
    int in=0;
    while(strcmp(car[in].num,"")!=0)
    {
count ++;
in++;
    }
    return count;
}
struct card removecard(int z,struct card cpu[])
{
int  car=0;
        struct card temp[2];
        temp[0]=cpu[z];
        for(int car=z;car<=getcurrentsize(cpu);car++)
        {
            cpu[car]=cpu[car+1];
        }
        return temp[0];
}

void addcard(struct card cpu[],struct stack **head)
{
    int i;
for(i=0;i<=getcurrentsize(cpu);i++);
cpu[--i]=pop(head);
}
void colorChange(struct card player[],struct card ondesk[],int z)
{
    char ch;
    printf("enter:");
    scanf(" %c",&ch);
    
    if(ch=='r')
    {
     strcpy(player[z].color,"\033[0;31m");
    }
    else if(ch=='g')
    {
        strcpy(player[z].color,"\033[0;32m");
    }
    else if(ch=='y')
    {
        strcpy(player[z].color,"\033[0;33m");
    }
    else if(ch=='b')
    {
        strcpy(player[z].color,"\033[0;34m");
    }
    else{
        printf("not recognized");
    }
    ondesk[0]=removecard(z,player);
}
bool isCardMatching(struct card player[],struct card ondesk[],int z)
{
    if(strcmp(player[z].num,"+2")!=0 && (strcmp(ondesk[0].color,player[z].color)==0 || strcmp(ondesk[0].num,player[z].num)==0))
        return true;
    else
        return false;
}
void colorcard(struct card ondesk[],struct card cpu[],struct stack **head )
{
    int ch;char p[20];
    printf("enter:");
    scanf("%d",&ch);
    if(ch==1)
    {
        strcpy(p,"\033[0;31m");}
    else if(ch==2)
    {
        strcpy(p,"\033[0;32m");
    }
    else if(ch==3)
    {
        strcpy(p,"\033[0;33m");
    }
    else{
        strcpy(p,"\033[0;34m");
    }
for(int i=0;i<getcurrentsize(cpu);i++)
{
    if(strcmp(p,cpu[i].color)==0)
    {
        ondesk[0]=removecard(i,cpu);
        return;
    }
}
int k=getcurrentsize(cpu);
while(strcmp(p,cpu[k].color)!=0)
{
    addcard(cpu,head);
    k++;
}
ondesk[0]=removecard(k,cpu);
}
struct players* circular(struct players* head,struct stack** stack,int id)
{
    struct players* newNode=(struct players*)malloc(sizeof(struct players));
    distribute(newNode->player,stack);
    newNode->id=id;
    if(head==NULL)
    {
        newNode->llink=newNode;
        newNode->rlink=newNode;
        return newNode;
    }
    else
    {
        struct players* current=head;
        while(current->rlink!=head)
        {
            current=current->rlink;
        }
        newNode->rlink=head;
        current->rlink=newNode;
        newNode->llink=current;
        head->llink=newNode;
        return head;
    }
};
bool isCardMatching2(struct card player[],struct card ondesk[],int z)
{
    if((strcmp(ondesk[0].color,player[z].color)==0 || strcmp(ondesk[0].num,player[z].num)==0))
        return true;
    else
        return false;
}
bool checkexsitence(struct card player[],struct card ondesk[])
{
    int c=0;
    for(int i=0;i<getcurrentsize(player);i++)
    {
        if(isCardMatching2(player,ondesk,i))
        {
          c++;
        }
    }
    if(c!=0)
    return true;
    else
    return false;

}
void cardacception(struct card ondesk[],struct card player[],int z,struct stack** head,struct card cpu[])
{
    if(isCardMatching(player,ondesk,z))
    {
        ondesk[0]=removecard(z,player);
       
    }
    else if(strcmp(player[z].num,"+4W")==0)
         {
            for(int i=0;i<4;i++)
            {
              addcard(cpu,head);
            }
            colorChange(player,ondesk,z);
          //  colorcard(ondesk,cpu,head);
            //ondesk[1]=removecard(z,player);
        }
    else if(strcmp(player[z].num,"W")==0)
    {
        colorChange(player,ondesk,z);
    }
        else if(strcmp(player[z].num,"+2")==0 && (strcmp(ondesk[0].color,player[z].color)==0) || strcmp(player[z].num,ondesk[0].num)==0){
                    for(int i=0;i<2;i++)
                    {
                        addcard(cpu,head);
                    }
                    ondesk[0]=removecard(z,player);

        }
        //else if(strcmp(player[z].num,"B")==0||strcmp(player[z].num,"R")==0)
        //{}
        else
        {
       // addcard(player,head);
       if(checkexsitence(player,ondesk))
       {
           printf("invalid input\n");
           int c;
         scanf("%d",&c);
          cardacception(ondesk,player,c-1,head,cpu);
       }
       else{
        int ch;
        printf("input D to draw card\n");
        scanf(" %c",&ch);
        addcard(player,head);
       }
    }

}


int main()
{
    int playcpu=0;
    int player1=1;
    struct card Card[109];
    struct stack* head=NULL;
    srand(time(0));
    fill(Card);
    head=shuffleDeck(head,Card);
    int numplayers;
    while(true)
    {
    printf("enter number of players:");
    scanf("%d",&numplayers);
    if(numplayers<2||numplayers>6)
    {
        printf("put valid player count");
    }
    else{
        break;
    }
    }
    struct players* players=NULL;
    for(int i=0;i<numplayers;i++)
    {
    players=circular(players,&head,i+1);
    }
    int z;
    struct card ondesk[2];
    ondesk[0]=pop(&head);
    while(strcmp(ondesk[0].num,"+4W")==0 || strcmp(ondesk[0].num,"W")==0)
    {
        ondesk[0]=pop(&head);
    }
    struct players* current=players;
    int rcount=0;
    while (true)
    { 
        playerPattern(1,ondesk);
        printf("player id: %d\n",current->id);
        playerPattern(getcurrentsize(current->player),current->player);
        scanf("%d",&z);
        z--;
        if(z==-2)
        {
            break;
        }
        if(strcmp(current->player[z].num,"R")==0)
        {
            rcount++;
        }
        if(strcmp(current->player[z].num,"B")==0)
        {
             if(rcount%2==0)
        {
            cardacception(ondesk,current->player,z,&head,current->rlink->player);
            current=current->rlink;
        }
        else
        {
            cardacception(ondesk,current->player,z,&head,current->llink->player);
            current=current->llink;
        }
        }
        else
        {
           if(rcount%2==0)
        {
        cardacception(ondesk,current->player,z,&head,current->rlink->player);
        }
        else
        {
        cardacception(ondesk,current->player,z,&head,current->llink->player);
        }
        }
        if(getcurrentsize(current->player)==0)
        {
            printf("player %d won\n",current->id);
            break;
        }
        if(rcount%2==0)
        {
            current=current->rlink;
        }
        else
        {
            current=current->llink;
        }

    }

return 0;
}