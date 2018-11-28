#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct database{
    int year;
    int month;
    int day;
    int type;
    int category;
    double amount;
}database;


database * db=NULL;
int N=0;


void PrintWallet(database s){
    printf("\n\n\t\t\t\tDate: %d/%d/%d\n", s.day, s.month,s.year);
    if(s.type==0) printf("\t\t\t\tType: Income\n");
    if(s.type==1) printf("\t\t\t\tType: Expense\n");
    switch(s.category){
        case 0: printf("\t\t\t\tCategory: Household\n");break;
        case 1: printf("\t\t\t\tCategory: Food\n");break;
        case 2: printf("\t\t\t\tCategory: Party\n");break;
        case 3: printf("\t\t\t\tCategory: Travel\n");break;
        case 4: printf("\t\t\t\tCategory: Scholarship\n");break;
        case 5: printf("\t\t\t\tCategory: Salary\n");break;
        case 6: printf("\t\t\t\tCategory: Poker games\n");break;
        case 7: printf("\t\t\t\tCategory: Other\n");break;
    }
    printf("\t\t\t\tAmount: %3.f HUF\n\n", s.amount);
}

database ScanWallet () {
database j;
    printf("Date: day/month/year: ");
    scanf("%d/%d/%d", &j.day,&j.month,&j.year);
    printf("Type:\n0:Income\n1:Expense\n");
    scanf("%d", &j.type);
    printf("Category:\n0: Household\n1: Food\n2: Party\n3: Travel\n4: Scholarship\n5: Salary\n6: Poker games\n7: Other\n");
    scanf("%d", &j.category);
    printf("Amount: ");
    scanf("%lf", &j.amount);
    while(getchar()!='\n');
    return j;
}

void printdatabase () {
    for (int i=0; i<N; i++)
        PrintWallet(db[i]);
}

int LoadDatabase (char* file) {

    FILE* infile;
    int i;
    free(db);
    infile = fopen(file,"r");
    if (infile==NULL)  return 0;
    fscanf(infile, "%d", &N);
    db = (database*)malloc(sizeof(database)*N);
    for (i=0; i<N; i++) {
        fscanf(infile, "%d\n", &db[i].day);
        fscanf(infile, "%d\n", &db[i].month);
        fscanf(infile, "%d\n", &db[i].year);
        fscanf(infile, "%d\n",&db[i].type);
        fscanf(infile, "%d\n", &db[i].category);
        fscanf(infile, "%lf\n", &db[i].amount);
    }
    fclose(infile);
    return 1;
}


void addWallet (database j) {
    database* tmp;
    int i;
    tmp = (database*)malloc((N+1)*sizeof(database));
    for (i=0; i<N; i++)
        tmp[i] = db[i];
    tmp[N] = j;
    free (db);
    db = tmp;
    N++;
}

int savedatabase (char* filename) {
    FILE* f;
    int i;
    f = fopen (filename, "w");
    if (f==NULL)
        return 0;

    fprintf (f, "%d\n", N);
    for (i=0; i<N; i++)
        fprintf (f, "%d\n %d\n %d\n %d\n %d\n %3.f\n", db[i].day, db[i].month, db[i].year, db[i].type, db[i].category,db[i].amount);

    fclose (f);
    return 1;
}


void menu(){
    printf("\n\t\t\t\t      MENU");
    printf("\n\t\t\t------------------------------");
    printf("\n\n\t\t\t 1. Load existing income/expense");
    printf("\n\t\t\t 2. Add new income/expense");
    printf("\n\t\t\t 3. Save your database into a file");
    printf("\n\t\t\t 4. Global Statistics");
    printf("\n\t\t\t 5. Selected time statistics");
    printf("\n\t\t\t 6. EXIT");
  }

  void MostExpensive(){
      int i, great=db[0].amount, index=0;
      for(i=0;i<N;i++){
            if(db[i].amount>great) {great=db[i].amount; index=i;}}

                   switch(db[index].category){
        case 0: printf("\t\t\t\tThe most expensive category is: Household\n");break;
        case 1: printf("\t\t\t\tThe most expensive category is: Food\n");break;
        case 2: printf("\t\t\t\tThe most expensive category is: Party\n");break;
        case 3: printf("\t\t\t\tThe most expensive category is: Travel\n");break;
        case 4: printf("\t\t\t\tThe most expensive category is: Scholarship\n");break;
        case 5: printf("\t\t\t\tThe most expensive category is: Salary\n");break;
        case 6: printf("\t\t\t\tThe most expensive category is: Poker games\n");break;
        case 7: printf("\t\t\t\tThe most expensive category is: Other\n");break;}

        printf("\t\t\t\tAmount spent: %d HUF\n", great);
  }


  void Statistics(){
      int TotalIncome=0;
      int TotalExpense=0;
      double Balance=0;
      for(int i=0;i<N;i++){
            if(db[i].type==0) TotalIncome+=db[i].amount;
            if(db[i].type==1) TotalExpense+=db[i].amount;
            Balance=TotalIncome-TotalExpense;
      }
      printf("\n\t\t\t\tTotal income: %d HUF\n", TotalIncome);
      printf("\t\t\t\tTotal expenses: %d HUF\n", TotalExpense);
 MostExpensive();
 printf("\t\t\t\tYour balance is: %3.f HUF\n", Balance);

  }


  void SelectedTime(){
      int TotalIncome=0,TotalExpense=0,i,tmp;
      double Balance;
      int time[10]={0,0,0,0,0,0,0,0,0,0};
      printf("Please enter from which day/month/year to which day/month/year: \n");
      scanf("%d/%d/%d", &time[0],&time[1],&time[2]);
      scanf("%d/%d/%d",&time[3],&time[4],&time[5]);
      printf("Statistics from %d/%d/%d till %d/%d/%d", time[0],time[1],time[2],time[3],time[4],time[5]);
      LoadDatabase("wallet.txt");
      for(i=0;i<N;i++){
            if(db[i].year>time[2] && db[i].year<time[5]){
                    if(db[i].type==0) TotalIncome+=db[i].amount;
                    if(db[i].type==1) TotalExpense+=db[i].amount;
                                                     }

            if(db[i].year==time[2] || db[i].year==time[5])
                {
                    if(db[i].month==time[1] || db[i].month==time[4])
                    {
                            if(db[i].day==time[0] || db[i].day==time[3] || (db[i].day>time[0] && db[i].day<time[3]))
                            {
                                if(db[i].type==0) TotalIncome+=db[i].amount;
                                if(db[i].type==1) TotalExpense+=db[i].amount;
                          }

                    if(db[i].month>time[1] || db[i].month>time[4])
                        {
                            if(db[i].type==0) TotalIncome+=db[i].amount;
                            if(db[i].type==1) TotalExpense+=db[i].amount;
                    }  }     }   }

      printf("\n\t\t\t\tTotal incomes: %d HUF\n", TotalIncome);
       printf("\t\t\t\tTotal expenses: %d HUF\n", TotalExpense);
       Balance=TotalIncome-TotalExpense;
       printf("\t\t\t\tYour balance is: %3.f HUF\n", Balance);
        MostExpensive();
  }


int main () {
int choice=0;
LoadDatabase("wallet.txt");
while(choice!=6){
         menu();
        printf("\n\n\t\t\t Enter Your Choice: ");
        scanf("%d", &choice);
                                switch(choice){
                    case 1: printdatabase();break;
                    case 2: addWallet(ScanWallet());break;
                    case 3: savedatabase("wallet.txt");break;
                    case 4: Statistics();break;
                    case 5: SelectedTime();break;
}}
    return 0;
}
