#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

FILE* fp;
FILE* fp1;
FILE* fp2;
struct User
{

    int id;
    char name[20];
    int age;
    char num[15];    //phoneNumber;
    char email[20];  //emailId
    char college[20];   //collegeName
    char rno[10];   //registration number
    char branch[25];
    int sem;
    char pwd[20];
    char lng[10];
    char cgpa[5];
    //int batch;
};

struct userInternship
{
    int id;
    int uid;
    int iid;
    int batch;
    struct userInternship* link;
};

struct Internship
{

    int id;
    char name[20];
    char desc[100];
    char req[50];
    char branch[20];
    int sem;
    int spb;
};

void push(struct userInternship **head,struct userInternship b)
{
struct userInternship *NN=(struct userInternship *)malloc(sizeof(struct userInternship));
NN->uid=b.uid;
NN->id=b.id;
NN->iid=b.iid;
NN->batch=b.batch;
NN->link=NULL;
//printf("PUSH %d ",b->uid);
//b->link=NULL;
struct userInternship *temp=*head;
temp=*head;
if(*head==NULL)
{
*head=NN;
//printf("push 1:%d\n",NN->uid);
return;
}
while(temp!=NULL)
{
if(temp->uid==NN->uid)
{
//printf("Error here\n");
return;
}
temp=temp->link;
}
temp=*head;
while(temp->link!=NULL)
temp=temp->link;
temp->link=NN;
//printf("push 2:%d\n",NN->uid);
}
void pop(struct userInternship **a,struct userInternship* b)
{
struct userInternship* temp=(*a);
struct userInternship* temp1=(*a);
if((*a)->uid==b->uid)
{
    //printf("here1\n");
    temp1=*a;
    //printf("uid=%d\n",temp1->uid);
    (*a)=(*a)->link;
    temp=(*a);
    while(temp->link!=NULL)
        temp=temp->link;
    temp->link=temp1;
    temp1->link=NULL;
}
else
{
    while(temp->link->uid!=b->uid)
        temp=temp->link;
    temp1=temp->link;
    temp->link=temp1->link;
    while(temp!=NULL)
        temp=temp->link;
    temp=temp1;
    temp1->link=NULL;

}
}

/*void pop(struct userInternship **a,struct userInternship* b)
{
//printf("CASE3");
struct userInternship *temp=*a,*temp2=*a;
//if(temp->link==NULL)
//return;
while(temp2->link!=NULL)
temp2=temp2->link;
while(temp->link!=NULL && temp->link!=b)
{
//printf("CASE3qwsw");
temp=temp->link;
}
//printf("CASE3");
temp->link=b->link;
temp2->link=b;
b->link=NULL;
}*/


void createbatch(struct userInternship **a)
{
//FILE *fp2=fopen("userInternship.txt","a+");
struct userInternship *temp=*a;
struct Internship t;
/*fseek(fp,0,SEEK_END);
int size=(ftell(fp)/sizeof(struct userInternhip))+1;
t1=(struct userInternship*)malloc(sizeof(struct userInternship)*size);
*ptr*/

int id=temp->id,spb;
//fclose(fp2);
fp1=fopen("Internship.txt","a+");
fseek(fp1,0,SEEK_SET);
while(fread(&t,sizeof(struct Internship),1,fp1))
{
if(t.id==id)
{
spb=t.spb;
break;
}
}
//printf("SPB=%d\n",spb);
int count=0,batch=1;
//printf("HERE");
while(temp!=NULL)
{
    //printf("HEREeeeee\n");
if(count>=spb)
{
batch++;
count=0;
}
count++;
temp->batch=batch;
//t1=*temp;
//fwrite(&t1,sizeof(struct userInternship),1,fp1);
temp=temp->link;
}
//fclose(fp);
fclose(fp1);
}

void finalbatch(struct userInternship** temphead,struct userInternship** head)
{
    struct userInternship* temp1=*temphead;
    struct userInternship* temp=*head;

                                        while(temp1!=NULL)
                                        {
                                            temp=*head;
                                            while(temp!=NULL)
                                            {
                                                if(temp1->uid==temp->uid)
                                                {
                                                    temp1->batch=temp->batch;
                                                    break;
                                                }
                                                temp=temp->link;
                                            }
                                            temp1=temp1->link;
                                        }
    /*temp1=*temphead;
    while(temp1!=NULL)
    {
        printf("uid=%d      batch=%d\n",temp1->uid,temp1->batch);
        temp1=temp1->link;
    }*/
    struct userInternship x;
    temp1=*temphead;
    fp2=fopen("userInternship.txt","w+");
    while(temp1!=NULL)
    {
        x.id=temp1->id;
        x.iid=temp1->iid;
        x.uid=temp1->uid;
        x.batch=temp1->batch;
        //x.link=temp1->link;

        fwrite(&x,sizeof(struct userInternship),1,fp2);
        temp1=temp1->link;
    }
    fclose(fp2);
}

void inputinternships(struct Internship i)
{
    fp1=fopen("Internship.txt","a+");

    //printf("Here");

    fwrite(&i,sizeof(struct Internship),1,fp1);
    fclose(fp1);
}
/*struct User signin(char* username,char* password)
{

}*/

/*void displayInternshipDetails(struct Internship* u)
{
    int i;
    for(i=0;i<6;i++)
    {


    printf("INTERNSHIP DETAILS - \n");
    //printf("ID                  -  %d\n",(u+i)->id);
    printf("Name                -  %s\n",(u+i)->name);
    //printf("Description         -  %s\n",(u+i)->desc);
    //printf("Requirements        -  %s\n",(u+i)->req);
   // printf("Branch              -  %s\n",(u+i)->branch);
   // printf("Semester            -  %d\n",(u+i)->sem);
   // printf("NOS                 -  %d\n\n\n\n",(u+i)->spb);
    }
}*/
void enroll(struct User s,int ID)
{
    int temp=0,flag=0;
    struct userInternship t;
    struct userInternship u;

    fp2=fopen("userInternship.txt","ab+");
    rewind(fp2);
    while(fread(&t,sizeof(struct userInternship),1,fp2))
    {

        if(t.uid==s.id)
            flag++;
        if(t.id==ID)
            temp++;
    }
    if(flag!=0)
    {
        printf("You have a pending Intenrship!!\n");
    }
    else
    {
        u.id=ID;
    u.uid=s.id;
    u.iid=temp+1;
    u.batch=0;
    fseek(fp2,0,SEEK_END);
    fwrite(&u,sizeof(struct userInternship),1,fp2);
    }

    //s.batch=0;
    fclose(fp2);

}
/*struct Internship* listOfInternship()
{
    struct Internship s;
    struct Internship* temp=(struct Internship*)malloc(6*sizeof(struct Internship));
    fp1=fopen("Internship.txt","r");
    int i=0;
    rewind(fp1);
    for(i=0;i<7;i++)
            {
                //temp=(struct Internship*)malloc(sizeof(struct Internship));
                fread(&s,sizeof(struct Internship),1,fp1);
                //printf("Here %d\n",i);
                printf("%s\n",s.name);
                //printf("%s\n",s.name);
                //*(temp+i)=s;
                //printf("Also");
                //i++;

            }
    printf("%d\n",i);
    /*for(i=0;i<6;i++)
        printf("%s\n",(*(temp+i)->name));

    printf("HERE");


    fclose(fp1);
    return temp;
}*/
 void displayUserDetails(struct User u)
{
    int i;
    printf("USER DETAILS - \n");
    printf("ID                  -  %d\n",u.id);
    printf("Name                -  %s\n",u.name);
    printf("Age                 -  %d\n",u.age);
    printf("Phone number        -  %s\n",u.num);
    /*for(i=0;i<10;i++)
        printf("%c",u.num[i]);*/
    //printf("\n");
    printf("Email ID            -  %s\n",u.email);
    printf("College Name        -  %s\n",u.college);
    printf("Registration number -  %s\n",u.rno);
    printf("Branch              -  %s\n",u.branch);
    printf("Semester            -  %d\n",u.sem);
    printf("Language            -  %s\n",u.lng);
    printf("CGPA                -  %s",u.cgpa);
}
int isempty(char* t)
{
    if(t[0]==' '||strlen(t)==0)
        return 0;
    return 1;

}
void signup(struct User u)
{
    fwrite(&u,sizeof(struct User),1,fp);
}
void display(struct userInternship *q)
{
//printf("Error");
while(q!=NULL)
{
//printf("Loop\n");
printf("%d batch no : %d\n",q->uid,q->batch);
q=q->link;
}
}
int main()
{
    int flag,i,j,size,choice;
    char temp[30];

    struct User u;
    struct User s;

    fp=fopen("user.txt","ab+");

    do
    {
        printf("\n\n===============================================   WELCOME TO I-BOX   ==================================================\n\n1) Sign up\n2) Already an user? Sign in\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            {

                fseek(fp,0,SEEK_END);
                size=ftell(fp);
                //printf("%d\n",size);
                /*if(size==0)
                {
                    u.id=1;
                }
                else
                {
                fread(&s,sizeof(struct User),1,fp);
                u.id=s.id+1;
                }*/
                u.id=(size/sizeof(struct User))+1;

                //u.batch=0;
            //ENTER NAME

            printf("Enter your name :\n");
            getchar();
            do
            {
                gets(u.name);
                if(isempty(u.name)==0)
                    printf("Name can't be empty!!!\n");
            }while(isempty(u.name)==0);

            //ENTER AGE
            flag=0;
            char temp_age[5];
            printf("Enter your age:\n");
            do
            {
                scanf("%s",temp_age);
                if(atoi(temp_age)!=0)
                {
                    u.age=atoi(temp_age);
                    flag++;
                }
                else
                    printf("Invalid age\n");
            }while(flag==0);

            //PHONE NUMBER
            flag=0;
            printf("Enter your Phone Number:\n");
            do
            {
                flag=0;
                scanf("%s",u.num);
            for(i=0;u.num[i]!='\0';i++)
            {
                if(!isdigit(u.num[i]))
                    flag++;
            }
            {
               if(strlen(u.num)!=10)
                   flag++;

            }
            if(flag!=0)
                printf("Invalid Phone number\n");
            }
            while(flag);
            //printf("%s\n",u.num);

            //Check EMAIL ID
           /* flag=0;
            //rewind(fp);
            printf("Enter your Email ID :\n");
            do
            {
                flag=0;i=0;j=0;
                scanf("%s",u.email);
                rewind(fp);
                while(!feof(fp))
                {
                    //fscanf(fp,"%*s %*d %*ld %s %*s %*s %*s %*d %*s %*s %*s",temp);
                    fread(&s,sizeof(struct User),1,fp);
                    if(strcmp(u.email,s.email)==0)
                    {
                        printf("Email ID in use. Please enter another email ID\n");
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    while(i<strlen(u.email)&&u.email[i]!='@')
                        i++;
                    if(i==strlen(u.email)||i==0)
                    {
                        printf("Invalid email\n");
                        flag=1;
                    }
                    if(flag==0)
                    {
                         j=i;
                        while(j<strlen(u.email)&&u.email[j]!='.')
                            j++;
                        if(j==strlen(u.email)||j-i<=1)
                        {
                            printf("Invalid email\n");
                            flag=1;
                        }
                    }
               }
            }while(flag==1);*/


            //COLLEGE NAME
            printf("Enter the name of your College :\n");
            do
            {
                getchar();
                gets(u.college);
                if(isempty(u.college)==0)
                    printf("College name can't be empty\n");

            }while(!isempty(u.college));

            //EMAIL
            flag=0;
            //rewind(fp);
            printf("Enter your Email ID :\n");
            //getchar();
            do
            {
                flag=0;i=0;j=0;
                gets(u.email);
                rewind(fp);
                while(!feof(fp))
                {
                    //fscanf(fp,"%*s %*d %*ld %s %*s %*s %*s %*d %*s %*s %*s",temp);
                    fread(&s,sizeof(struct User),1,fp);
                    if(strcmp(u.email,s.email)==0)
                    {
                        printf("Email ID in use. Please enter another email ID\n");
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    while(i<strlen(u.email)&&u.email[i]!='@')
                        i++;
                    if(i==strlen(u.email)||i==0)
                    {
                        printf("Invalid email\n");
                        flag=1;
                    }
                    if(flag==0)
                    {
                         j=i;
                        while(j<strlen(u.email)&&u.email[j]!='.')
                            j++;
                        if(j==strlen(u.email)||j-i<=1)
                        {
                            printf("Invalid email\n");
                            flag=1;
                        }
                    }
               }
            }while(flag==1);



            //REGISTRATION NUMBER
            printf("Enter your Registration Number :\n");
            do
            {
                flag=0;
                scanf("%s",u.rno);
                if(isempty(u.rno)==0)
                    printf("Registration name can't be empty\n");
                if(u.rno[0]=='4')
                {
                    if(u.rno[1]=='N'&&u.rno[2]=='I')
                        flag++;
                    else if(u.rno[1]=='M'&&u.rno[2]=='H')
                        flag++;
                    else if(u.rno[1]=='V'&&u.rno[2]=='V')
                        flag++;
                    else if(u.rno[1]=='G'&&u.rno[2]=='S')
                        flag++;
                }
                else if(u.rno[0]==0&&u.rno[1]=='1'&&u.rno[2]=='J'&&u.rno[3]=='S'&&u.rno[4]=='T')
                    flag++;
                if(flag==0)
                    printf("Entered registration number doesn't belong to list\n");

            }while(!isempty(u.rno)||flag==0);

            //BRANCH
            char br[100];
            printf("Enter your branch :\n");
            //scanf("%s",u.branch);
            getchar();
            do
                {
                    flag=0;
                    //getchar();
                    gets(u.branch);
                    strcpy(br,u.branch);
                    //printf("branch= %s\n",br);
                    if(strcmp(br,"computer science")!=0&& strcmp(br,"information science")!=0 && strcmp(br,"electronics and communication")!=0 && strcmp(br,"electrical")!=0 && strcmp(br,"electronics and instrumentation")!=0)
                        {
                            printf("Entered branch doesn't belong to list\n");
                            flag=1;
                        }
                }while(flag==1);

            //SEMESTER
            flag=0;
            char temp_sem[5];
            printf("Enter your semester :\n");
            do
            {
                flag=0;
                scanf("%s",temp_sem);
                if(atoi(temp_sem)!=0)
                {
                    u.sem=atoi(temp_sem);

                }
                else
                 {
                     printf("Invalid Semester\n");
                     flag++;
                 }
                if(flag==0)
                {
                    if(u.sem<0||u.sem>8)
                    {
                        printf("Semester can't be greater than 8\n");
                        flag++;
                    }
                }
            }while(flag!=0);

            //PASSWORD
            flag=0;
            int upper,lower,special,digit;
            printf("Enter your Password :\n");
            do
            {
                flag=0,upper=0,lower=0,digit=0,special=0;
                //getchar();
                scanf("%s",u.pwd);
                for(i=0;i<strlen(u.pwd);i++)
                {
                    if(isalpha(u.pwd[i]))
                    {
                        if(isupper(u.pwd[i]))
                        upper++;
                    else if(islower(u.pwd[i]))
                        lower++;
                    }

                    else if(isdigit(u.pwd[i]))
                        digit++;
                    else if(((int)u.pwd[i]>=33&&(int)u.pwd[i]<=42)||u.pwd[i]=='@'||u.pwd[i]=='^')
                        special++;
                }
                    if(upper<2||lower<2||digit<2||special<2)
                    {
                        printf("%d %d %d %d\n",upper,lower,digit,special);
                        flag++;
                        printf("Password must consist of at least 2[a-z], 2[A-Z], 2[0-9],2[!@..+*] charecters\n");
                    }


            }while(flag!=0);
            char temp_pwd[30];
            printf("Confirm password :\n");
            do
            {
                scanf("%s",temp_pwd);
                if(strcmp(u.pwd,temp_pwd)!=0)
                    printf("Password doesn't match\nRe-enter password :\n");
            }while(strcmp(u.pwd,temp_pwd)!=0);

            printf("Enter your language :\n");
            scanf("%s",u.lng);

            printf("Enter your cgpa :\n");
            do
            {
                flag=0;
                scanf("%s",u.cgpa);
                if(u.cgpa[0]>'0'&&u.cgpa[0]<='9')
                {
                    if(u.cgpa[1]=='.')
                    {
                        if(u.cgpa[2]>='0'&&u.cgpa[2]<='9')
                            flag++;

                    }

                }
            else if(u.cgpa[0]=='1'&&u.cgpa[1]=='0'&&u.cgpa[2]=='.'&&u.cgpa[3]=='0')
                    flag++;
                if(flag==0)
                    printf("CGPA should be equal to or less than 10, and numeric value\n");

            }while(flag==0);


            fseek(fp,0,SEEK_END);
            signup(u);
            system("cls");
            printf("\nYou have succesfully registered!!\n\nRedirecting to Home Page. . . . . .\n\n");
            break;
        }

        case 2:
            {

            char temp_email[50],temp_pwd[30];
            flag=0;
            printf("Enter your E-mail ID :\n");
            scanf("%s",temp_email);
            if(strcmp(temp_email,"admin")==0)
            {
                printf("Enter Password:\n");
                scanf("%s",temp_pwd);
                if(strcmp(temp_pwd,"admin")!=0)
                {
                    printf("Invalid Password\n");
                    break;
                }
                else
                {
                    int c;
                    struct Internship i;
                    printf("1) Add Internships\n\n2)Display Internships\n\n3)Create Batches\n\n3)Log Out\n\n");
                    scanf("%d",&c);
                    switch(c)
                    {
                    case 1:
                        {
                            char ch;
                            do
                            {
                                 printf("Enter ID:\n");
                                scanf("%d",&i.id);
                                getchar();
                                printf("Enter name:\n");
                                //getchar();
                                gets(i.name);
                                //printf("%s\n",i.name);
                                printf("Enter Description:\n");
                                gets(i.desc);
                                //printf("%s\n",i.desc);
                                //printf("HERE\n");
                                printf("Enter Requirements:\n");
                                gets(i.req);
                                printf("Enter branch:\n");
                                gets(i.branch);
                                printf("Enter sem:\n");
                                scanf("%d",&i.sem);
                                printf("Enter number of students per branch:\n");
                                scanf("%d",&i.spb);
                                inputinternships(i);
                                printf("Do you want to enter another Internship? Type y/n\n");
                                scanf("%*c %c",&ch);
                            }while(ch=='y');
                            break;

                        }
                    case 2:
                        {
                            struct Internship i;
                            int j=0,t;
                            fp1=fopen("Internship.txt","ab+");
                            fseek(fp1,0,SEEK_SET);
                            while(fread(&i,sizeof(struct Internship),1,fp1)>0)
                            {

                                printf("%d)  Name of the Internship:     %s\n",j+1,i.name);
                                j++;
                                //printf("%s\n\n",i.desc);
                            }

                            fclose(fp1);
                            break;
                        }

                    case 3:
                        {
                            int choice,count=0,c;
                            struct userInternship a;
                            struct userInternship* head;
                            int sem;
                            head=NULL;
                            struct Internship s;
                            fp1=fopen("Internship.txt","a+");
                            fp2=fopen("userInternship.txt","a+");
                            int j1;
                            do
                            {

                              j1=0;
                            printf("Enter the Internship ID:\n");
                            scanf("%d",&c);

                            fseek(fp1,0,SEEK_SET);
                            fseek(fp2,0,SEEK_SET);
                            while(fread(&s,sizeof(struct Internship),1,fp1))
                            {
                            //printf("def");
                                if(s.id==c)
                                    {
                                        j1++;
                                        break;
                                    }
                            }
                            if(j1==0)
                                printf("Enter a valid internship ID\n");
                            }while(j1==0);
                            while(fread(&a,sizeof(struct userInternship),1,fp2))
                            {
                                if(a.id==c)
                                    {
                                    //printf("abc");

                                        push(&head,a);

                                        count++;
                                    }

                            }
                            //display(head);
                            do
                            {

                                if(count==0)
                                    {
                                        printf("Empty\n");
                                        choice=4;
                                    }
                                else
                                {

                                printf("1)First Come Basis\n\n2)Semester Basis\n\n3)Branch Basis\n\n4)Finalize Batch");
                                scanf("%d",&choice);
                                switch(choice)
                                {
                                    case 1:
                                    {
                                        printf("DONE!!\n");
                                        display(head);
                                        break;
                                    }
                                    case 2:
                                    {

                                         int w=0;int g,sem,k=0;
                                        struct User u;
                                        struct userInternship* ptr;
                                        struct userInternship np;
                                        ptr=head;
                                        //printf("count is %d\n",count);
                                        printf("Enter the preferred semester:\n");
                                        scanf("%d",&sem);
                                        //display(ptr);
                                        while(ptr!=NULL&&w<count)
                                        {
                                            //g=0;
                                           // printf("TTTT\n");
                                           //printf("w=%d\n",w);


                                            fseek(fp,0,SEEK_SET);
                                             while(fread(&u,sizeof(struct User),1,fp))
                                             {
                                                 //printf("ptr uid=%d     user  id=%d\n",ptr->uid,u.id);

                                                 if(ptr->uid==u.id)
                                             {
                                                //printf("Match found\n\n");
                                                w++;
                                                 if(u.sem!=sem)
                                                 {
                                                     //printf("Sem isnt equal\n");
                                                     pop(&head,ptr);
                                                     //printf("head is %d\n",head->uid);
                                                     //ptr=head;
                                                     k++;
                                                     //display(head);
                                                 }

                                                 break;
                                             }

                                             }

                                             //printf("HERE\n");
                                             if(k>0)
                                           {
                                               ptr=head;
                                               k=0;
                                           }
                                           else
                                             ptr=ptr->link;

                                        }
                                        /*ptr=head;
                                        int c1=0;
                                        while(ptr->sem==sem)
                                        {
                                            ptr=ptr->link;
                                            c1++;
                                        }
                                        count=c1;
                                        display(head);*/
                                        printf("DONE!!\n\n");
                                        break;
                                    }

                                    case 3:
                                    {

                                         int v=0,g,k=0;
                                        char pb[30];
                                        struct User u;
                                        struct userInternship* ptr;
                                        ptr=head;
                                        getchar();
                                        printf("Enter the preferred branch:\n");

                                        gets(pb);
                                        while(ptr!=NULL&&v<count)
                                        {
                                            g=0;
                                            fseek(fp,0,SEEK_SET);
                                             while(fread(&u,sizeof(struct User),1,fp)&&g==0)
                                             {
                                                 if(ptr->uid==u.id)
                                             {
                                                 g++;
                                                 v++;
                                                 //*(sa+i)=u.sem;
                                                 //i++;
                                                 if(strcmp(u.branch,pb)!=0)
                                                 {
                                                     pop(&head,ptr);
                                                     k++;
                                                 }
                                             }

                                             }
                                             if(k>0)
                                             {
                                                 ptr=head;
                                                 k=0;
                                             }
                                             else
                                             ptr=ptr->link;

                                        }
                                        /*ptr=head;
                                        int c1=0;
                                        while(strcmp(ptr->branch,branch)==0)
                                        {
                                            ptr=ptr->link;
                                            c1++;
                                        }
                                        count=c1;*/
                                        printf("DONE!!\n\n");
                                        break;
                                    }
                                    case 4:
                                    {

                                        createbatch(&head);
                                        //display(head);
                                        struct userInternship* temphead;
                                        temphead=NULL;
                                        struct userInternship t;
                                        fp2=fopen("userInternship.txt","r");
                                        fseek(fp2,0,SEEK_SET);
                                        while(fread(&t,sizeof(struct userInternship),1,fp2))
                                        {
                                            push(&temphead,t);
                                        }
                                        fclose(fp2);
                                        finalbatch(&temphead,&head);
                                        struct userInternship x;
                                        fp2=fopen("userInternship.txt","r");
                                        fseek(fp2,0,SEEK_SET);
                                        while(fread(&x,sizeof(struct userInternship),1,fp2))
                                        {
                                            printf("User ID=%d    Internship chosen=%d      Internship ID=%d     batch=%d\n",x.uid,x.id,x.iid,x.batch);
                                        }
                                        fclose(fp2);
                                        break;

                                    }





                                }


                        }
                            }while(choice!=4);
                    }
                    }

                }
            }
            //printf("%s\n",temp_email);
            else
            {


            rewind(fp);
            while(!feof(fp))
            {
                //printf("HERE");
                fread(&s,sizeof(struct User),1,fp);
                //printf("%s\n",s.email);
                if(strcmp(s.email,temp_email)==0)
                {
                    //printf("%ld\n",s.num);
                   flag++;
                   break;
                }
            }
            //printf("HERE");
            if(flag==0)
            {
                //system("cls");
                printf("User not found\n\nRedirecting to Home Page. . . . .\n\n");
                break;
            }
            else
            {
                char temp_pwd[30];
                int c;
                int internid;
                printf("Enter the Password :\n");
                do
                {
                    scanf("%s",temp_pwd);
                if(strcmp(s.pwd,temp_pwd)==0)
                   {
                       system("cls");
                       printf("Login Succesful!!\n\n");
                       //fp1=fopen("Internship.txt","ab+");
                       displayUserDetails(s);
                       printf("\n\n");
                       //struct Internship* temp=listOfInternship();
                       //printf("HERE");
                      // displayInternshipDetails(temp);
                        int i;
                        struct Internship u;
                        fp1=fopen("Internship.txt","a+");
                        /*fseek(fp,0,SEEK_END);
                        int k=ftell(fp1);
                        if(k==0)
                        {
                            getchar();
                            for(i=0;i<6;i++)
                            {
                                gets(u.name);
                                fwrite(&u,sizeof(struct Internship),1,fp1);
                            }

                        }*/

                        //rewind(fp1);
                        printf("INTERNSHIP DETAILS - \n");
                        int j=0;
                        //fp1=fopen("Internship.txt","ab+");
                            fseek(fp1,0,SEEK_SET);
                            while(fread(&u,sizeof(struct Internship),1,fp1)>0)
                            {

                                printf("%d)  Name of the Internship:     %s\n",j+1,u.name);
                                j++;
                                //printf("%s\n\n",i.desc);
                            }

                            fclose(fp1);

                       printf("Enter the Index of the Internship you are interested in:\n\n");
                       scanf("%d",&internid);
                       enroll(s,internid);
                       //printf("%d\n",s.batch);
                       printf("\n\nPress 0 to exit\n\n");
                       scanf("%d",&c);
                       if(c==0)
                        return 0;
                       else
                       break;
                   }
                else
                {
                    printf("Incorrect Password\nRe-Enter Password :\n");//Press 1 to retry\nPress 2 to go back to Home Page\n");
                    /*scanf("%d",c);
                    if(c==2)
                    {
                        system("cls");
                        printf("Redirecting to Home Page. . . . .\n\n");
                        break;
                    }*/

                }
                }while(strcmp(s.pwd,temp_pwd)!=0);


            }
            break;
            }
            }



        }
    }while(choice==1||choice==2);
    fclose(fp);
    //fclose(fp1);


    return 0;

}
