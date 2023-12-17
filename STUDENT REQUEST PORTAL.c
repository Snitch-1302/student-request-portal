#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct info
{
    char fname[100];
    char lname[100];
    char roll_no[10];
    unsigned long long int num;
    char mail[100];
    char pass[50];
    char s_st[3];
}info;
struct studetails
{
    char meet[100];
    char id[10];
    char reason[500];
    char date[11];
}detail;
void login();
void signin()
{
    char roll[10];
    FILE *f;
    printf("\n\t===========");
    printf("\n\t= SIGN IN =\n");
    printf("\t===========");
    f=fopen("Register.txt","a");
    printf("\n\n\t\tStaff(S) / Student(STUD) : ");
    scanf("%s",info.s_st);
    printf("\n\t\tFirst Name : ");
    scanf("%s",info.fname);
    printf("\n\t\tLast Name : ");
    scanf("%s",info.lname);
    printf("\n\t\tRoll number / Staff ID : ");
    scanf("%s",info.roll_no);
    printf("\n\t\tMobile number : ");
    scanf("%llu",&info.num);
    printf("\n\t\tMail-ID : ");
    scanf("%s",info.mail);
    printf("\n\t\tPassword : ");
    scanf("%s",info.pass);
    fprintf(f,"%s  %s  %s  %s  %llu  %s  %s\n",info.s_st,info.fname,info.lname,info.roll_no,info.num,info.mail,info.pass);
    fclose(f);
    printf("\n\t==========");
    printf("\n\t= LOGIN =\n");
    printf("\t==========");
    printf("\n\t\tROLL NUMBER / STAFF ID : ");
    scanf("%s",roll);
    login(roll);
}
void login(char roll[10])
{
    int count1=0,count2=0;
    FILE *f;
    f=fopen("Register.txt","a+");
    while(!(feof(f)))
    {
        fscanf(f,"%s  %s  %s  %s  %llu  %s  %s\n",info.s_st,info.fname,info.lname,info.roll_no,&info.num,info.mail,info.pass);
        if (strcmp(info.roll_no,roll)==0)
        {
            count1+=1;
            if (strcmp(info.s_st,"STUD")==0)
            {
                count2+=1;
            }
        }
        continue;
    }
    if (count1==0)
    {
        printf("\n\t\tRoll Number / Staff ID not fount.Please SIGNIN\n");
        signin();
    }
    else
    {
        printf("\n\t\tPassword : ");
        scanf("%s",info.pass);
        if ( count2==0)
        {
            staff(roll);
        }
        else
        {
           student(roll);
        }
    }
}
void student(char roll[10])
{
    FILE *f1,*f2;
    f1 = fopen("Student.txt","a");
    int n,count3=0;
    char std_roll[10];
    printf("\n\n\t\tSelect a choose : \n\t\t\t1.Send a Requests\n\t\t\t2.Track Your Status.\n\t\t");
    scanf("%d",&n);
    if (n==1)
    {
        printf("\n\t\tEnter the name of the person you would like to meet:    ");
        scanf("%s",detail.meet);
        printf("\n\t\tEnter the faculty id of the person you wish to meet:    ");
        scanf("%s",detail.id);
        printf("\n\t\tEnter the date in dd-mmm-yyyy in words:    ") ;
        scanf("%s",detail.date);
        while (strlen(detail.date)!=11)
        {
            printf("Invalid Format! Please Try Again!");
            printf("\n\t\tDate : ");
            scanf("%s",detail.date);
        }

        printf("\n\t\tEnter the reason you would like to meet : ");
        scanf("%s",detail.reason);
        fprintf(f1,"%s  %s  %s  %s\n",detail.meet,detail.id,detail.reason,detail.date);
        f2=fopen(detail.id,"a");
        fprintf(f2,"%s  %s  %s\n",roll,detail.date,detail.reason);
        fclose(f1);
        fclose(f2);
        printf("\n\t\tYour query has been submitted successfully.");
    }
    else
    {
        printf("\n\t\tEnter the faculty id of the person whom your have requested : ");
        scanf("%s",detail.id);
        f2=fopen(detail.id,"r");
        rewind(f2);
        while(!(feof(f2)))
        {
            fscanf(f2,"%s  %s  %s\n",std_roll,detail.date,detail.reason);
            if (strcmp(std_roll,roll)==0)
            {
                count3+=1;
                continue;
            }
        }
        if (count3==0)
        {
            printf("\n\t\tRequest has been accepted and the document is sent to your official Mail ID.\n");
        }
        else
        {
            printf("\n\t\tREQUEST PENDING.\n");
        }
    }
}
void staff(char s_roll[10])
{
    char roll_no[10],roll[10];
    int count4;
    FILE *f1,*f2,*f3;
    f1=fopen(s_roll,"r+");
    f2=fopen("Temp.txt","w+");
    f3=fopen("Del.txt","w+");
    if (f1 == NULL)
    {
        printf("\n\t\tNO PENDING REQUEST ARE THERE.\n");
        printf("\n****************************************************************************************************************************************************************");
        printf("\n\t\t\t\t\t\t\t\t\tTHANK YOU.");
        printf("\n*****************************************************************************************************************************************************************");
        exit(1);
    }
    else
    {
        while(!(feof(f1)))
        {
            fscanf(f1,"%s  %s  %s\n",roll,detail.date,detail.reason);
            printf("\n\t\t");
            printf("%s  %s  %s\n",roll,detail.date,detail.reason);
            count4+=1;
            continue;
        }
        printf("\n\t\tEnter the Roll number of the student whose request is to be accepted.");
        printf("\n\t\tRoll Number : ");
        scanf("%s",roll_no);
        rewind(f1);
        while(!(feof(f1)))
        {
            fscanf(f1,"%s  %s  %s\n",roll,detail.date,detail.reason);
            if(strcmp(roll,roll_no)==0)
            {
               if (count4==1)
               {
                   f1=fopen(s_roll,"w");
                   fclose(f1);
                   break;
               }
               continue;
            }
            else
            {
                fprintf(f2,"%s  %s  %s\n",roll,detail.date,detail.reason);
            }
        }
        if (count4!=1)
        {
            f1=fopen(s_roll,"w");
            rewind(f2);
            while(!(feof(f2)))
            {
                fscanf(f2,"%s  %s  %s\n",roll,detail.date,detail.reason);
                fprintf(f1,"%s  %s  %s\n",roll,detail.date,detail.reason);
            }
        }
    }
    fclose(f1);
    fclose(f2);
}
void main()
{
    char ans1[1],ans2[1],roll[10];
    int count=0;
    printf("\n**************************************************************************************************************************************************************");
    printf("\n\t\t\t\t\t\t\t\t\tWELCOME TO ABC COLLEGE OF TECHNOLOGY");
    printf("\n**************************************************************************************************************************************************************");
    printf("\n\n\t\tHAVE AN ACCOUNT (Y/N): ");
    scanf("%s",ans1);
    if (strcmp(ans1,"Y")==0 | strcmp(ans1,"y")==0)
    {
        printf("\n\t==========");
        printf("\n\t= LOGIN =\n");
        printf("\t==========");
        printf("\n\t\tROLL NUMBER / STAFF ID : ");
        scanf("%s",roll);
        login(roll);
    }
    else
    {
        signin();
    }
    printf("\n\t\tDO TO WANT TO LOG OUT (Y/N): ");
    scanf("%s",ans2);
    if (strcmp(ans2,"Y")==0 | strcmp(ans2,"y")==0)
    {
        printf("\n****************************************************************************************************************************************************************");
        printf("\n\t\t\t\t\t\t\t\t\tTHANK YOU.");
        printf("\n*****************************************************************************************************************************************************************");
    }
    else
    {
        FILE *f;
        f=fopen("Register.txt","r");
        while(!(feof(f)))
        {
            fscanf(f,"%s  %s  %s  %s  %llu  %s  %s\n",info.s_st,info.fname,info.lname,info.roll_no,&info.num,info.mail,info.pass);
            if (strcmp(info.roll_no,roll)==0)
            {
                if (strcmp(info.s_st,"STUD")==0)
                {
                    count+=1;
                }
                continue;
            }
        }
        if (count==0)
        {
            staff(roll);
        }
        else
        {
           student(roll);
        }
    }
}
