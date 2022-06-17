#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int NumOfItems = 0,Total = 0,Profit=0,index1=0;
void SignUp();
void LogIn();
void Admin();
void AfterLog();
void Add();
void Delete();
int Invoice();
void Sales();
void AdminLogin();
int main()
{          
	remove("Invoice.txt");
	int choice;
	printf("**************************WELOCOME************************** \n");
	printf("**************************STORE.PK****************** \n");
	printf("############################################################ \n");
	printf("                      1. ADMIN LOG IN \n");
	printf("                      2. CUSTOMER SIGN UP \n");
	printf("                      3. CUSTOMER LOG IN \n");
	printf("                      4. EXIT \n");
	printf("############################################################ \n");
	printf("ENTER YOUR CHOICE: ");
	scanf("%d",&choice);
	if(choice == 1)
	{
		system("cls");
		AdminLogin();
	}else if(choice == 2)
	{
		system("cls");
		SignUp();
	}else if(choice == 3)
	{
		system("cls");
		LogIn();
	}else
	{
		return 0;
	}
}
void SignUp()
{
	FILE *USER;
	char Pass[100],CHECK[50],stId[5];
	USER = fopen("USERS.txt","r");
	do
	{
		fgets(stId,5,USER);
	}while(fgets(CHECK,50,USER) != NULL);
	fclose(USER);
	int Id = atoi(stId);
	printf("YOUR ASSIGNED ID IS: \n");
	printf("%d",Id+1);
	do
	{
		printf("\n ENTER YOUR PASSWORD(MAX 10 CHARACTERS): ");
		scanf("%s",Pass);	
	}while(strlen(Pass) > 10);
	USER = fopen("USERS.txt","a");
	fprintf(USER,"\n",1);
	fprintf(USER,"%d ",Id + 1);
	fprintf(USER,"%s",Pass);
	fclose(USER);
	printf("SIGNING UP............\n\n");
	sleep(1);
	int c;
	printf("ENTER 1 TO CONTINUE SHOPPING,ELSE PRESS ANY NUMBER KEY: ");
	scanf("%d",&c);
	if(c == 1)
	{
		system("cls");
		LogIn();
	}
	
}
void LogIn()
{
	FILE *USER;
	int Id,FId,Found=0,compare,c,i,len;
	char Pass[10],FPass[10],CHECK[50],sId[5];
	do
	{
		printf("ENTER YOUR ID: ");
		scanf("%d",&Id);
		printf("ENTER PASSWORD: ");
		scanf("%s",Pass);
		USER = fopen("USERS.txt","r");
		do
		{
			fgets(sId,5,USER);
			FId = atoi(sId);
			if(FId == Id)
			{
				fseek(USER,1,SEEK_CUR);
				len = strlen(Pass);
				fgets(FPass,len+1,USER);
				compare = strcmp(FPass,Pass);
				if(compare == 0)
				{
					Found = 2;
					break;
				}
				Found = 1;
			}
		}while(fgets(CHECK,50,USER) != NULL);
		fclose(USER);
		if(Found == 1)
		{
			printf("ID OR PASSWORD DID'NT MATCH...... \n");
		}else if(Found == 0)
		{
			printf("ACOUNT NO FOUND \n");
			printf("--------------------- \n");
			printf("SIGN UP IF NOT HAVE ACCOUNT \n");
			printf("PRESS 1 TO PROCEED TO SIGN UP: ");
			scanf("%d",&c);
			if(c == 1)
			{
				system("cls");
				SignUp();
			}
		}else if(Found == 2)
		{
			break;
		}
	}while(1);
	printf("LOGGING IN.......");
	sleep(1);
	system("cls");
	AfterLog();
}
void Admin()
{
	FILE *stock,*sales;
    int i,j,k,qt,qt1,choice,nqt,npp,nsp,c=0;
    char buffer[50],qty[3],qty1[3],np[3],np1[3],iname[35],compare[35],ch,Total[7],PR[7];
    while (1)
    {
	    printf("############### Welcome admin ##################\n\n");
	    sales = fopen("Sales.txt","r");
	    fgets(Total,7,sales);
	    fgets(PR,7,sales);
	    printf("\n Total Profit: %s",PR);
	    printf("\n Total Sales: %s",Total);
	    printf("\n\n");
	    stock = fopen("stock.txt","r");
	    //fgets(buffer,50,stock);
	    while (fgets(buffer,50,stock)!=NULL)
	    {
	        //fgets(buffer,50,stock);
	        for (i=0;i<3;i++)
	        {
	            qty[i]=buffer[i+43];
	        }
	        qt=atoi(qty);
	        if (qt<4)
	        {
	            printf("please restock ");
	            for (i=0;i<35;i++)
	            {
	                printf("%c",buffer[i]);
	            }
	            printf("\n");
	        }
	    }
	    fclose(stock);
	    printf ("\n\n");
	    printf("1.Restock.\n");
	    printf("2.Update Price.\n");
	    printf("3.Exit.\n");
	    scanf("%d",&choice);
	    switch (choice)
	    {
	        case 1:
	            printf("Enter item complete name: ");
	            scanf(" %[^\n]s",iname);
	            printf("Enter new quantity:");
	            scanf("%d",&nqt);
	            stock = fopen("stock.txt","r+");
	            k=strlen(iname);
	            fgets(buffer,50,stock);
	            do
	            {
	                for (i=0;i<k;i++)
	                {
	                    compare[i]=buffer[i];
	                }
	                //printf("%s",compare);
	                //printf("%d %d\n",strlen(compare),strlen(iname));
	                if (strcmp(iname,compare)==0)
	                {
	                	//printf("%d %d\n",strlen(compare),strlen(iname));
	                    for (i=0;i<3;i++)
	                    {
	                        qty[i]=buffer[i+43];
	                    }
	                    //printf("%s",qty);
	                    qt=atoi(qty);
	                    qt+=nqt;
	                    //printf("%d",qt);
	                    itoa(qt,qty1,10);
	                    fseek(stock, -5, SEEK_CUR);
	                    fprintf(stock,"%s",qty1);
	                    fseek(stock,0,SEEK_CUR);
	                    break;
	                }
	            } while (fgets(buffer,49,stock)!=NULL);
	            fclose(stock);
	            break;
	        case 2:
	        	getchar();
	        	printf("Enter for which item you want to update price: ");
	        	scanf(" %[^\n]s",iname);
				//gets(iname); 
				//printf("%s",iname);
	        	printf("Enter new purchase price: ");
	        	scanf("%d",&npp);
	        	printf("Enter new selling price: ");
	        	scanf("%d",&nsp);
	        	stock = fopen("stock.txt","r+");
	            while(fgets(buffer,49,stock)!=NULL)
	            {
	                for (i=0;i<strlen(iname);i++)
	                {
	                    compare[i]=buffer[i];
	                }
	                //printf("%d %d\n",strlen(compare),strlen(iname));
	                if (strcmp(iname,compare)==0)
	                {
	                    for (i=0;i<3;i++)
	                    {
	                        qty[i]=buffer[i+36];
	                    }
	                    qt=atoi(qty);
	                    qt=npp;
	                    itoa(qt,np,10);
	                    for (i=0;i<3;i++)
	                    {
	                        qty[i]=buffer[i+40];
	                    }
	                    qt=atoi(qty);
	                    qt=nsp;
	                    itoa(qt,np1,10);
	                    fseek(stock, -13, SEEK_CUR);
	                    fprintf(stock,"%s",np1);
	                    if (qt<10)
	                    	fseek(stock,3,SEEK_CUR);
	                    else if (qt>9&&qt<100)
	                    	fseek(stock,2,SEEK_CUR);
	                    else
	                    	fseek(stock,1,SEEK_CUR);
	                    fprintf(stock,"%s",np);
	                    fseek(stock,4,SEEK_CUR);
	                    break;
	                }
	            }
	            fclose(stock);
	        	break;
	        case 3:
	        	exit(0);
				break; 	
	    }
	    system("CLS");
	    Admin();
	}
}
void AfterLog()
{
	int choice;
	printf("LOGGED IN.\n");
	printf("1-ADD AN ITEM.\n");
	printf("2-DELETE AN ITEM.\n");
	printf("3-DISPLAY INVOICE.\n");
	printf("4-EXIT.\n");
	printf("ENTER CHOICE: ");
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
		case 1:
			Add();
			break;
		case 2:
			Delete();
			break;
		case 3:
			Invoice();
			break;		
	}
	
}
void Add()
{
	FILE *stock,*Invoice;
	int choice,i=1,c,j,Qty,k=0,q;
	char CHECK[50],SPrice[3],CPrice[3],Q[4],in[3];
	itoa(k,in,10);
	index1++;
	printf("LIST OF ITEMS \n");
	printf("ITEM NAME-------------------------------PRICE \n\n\n");
	stock  = fopen("stock.txt","r");
	fseek(stock,0,SEEK_SET);
	do
	{
		fgets(CHECK,40,stock);
		printf("%d) %s \n",i,CHECK);
		i++;
		if(i>19)
		{
			break;
		}
	}while(fgets(CHECK,50,stock) != NULL);
	fclose(stock);
	printf("\n\n");
	Invoice = fopen("Invoice.txt","a");
	do
	{
		printf("ENTER ITEM NUMBER: ");
		scanf("%d",&choice);
		printf("ENTER QUANTITY: ");
		scanf("%d",&Qty);
		if(choice < 1 || choice > 20)
		{
			printf("ENTER VALID CHOICE..\n");
			continue;
		}else
		{
			k++;
			NumOfItems++;
			stock = fopen("stock.txt","r+");
			fseek(stock,0,SEEK_SET);
			rewind(stock);
			for(j=1;j<choice*2;j++)
			{
				fgets(CHECK,40,stock);	
			}
			fprintf(Invoice,"%s  %d  ",CHECK,Qty);
			fseek(stock,-4,SEEK_CUR);
			fgets(SPrice,4,stock);
			//fseek(stock,1,SEEK_CUR);
			fprintf(Invoice,"%d\n",atoi(SPrice)*Qty);
			fgets(CPrice,4,stock);
			Profit += (atoi(SPrice)*Qty) - (atoi(CPrice)*Qty);
			fseek(stock,1,SEEK_CUR);
			fgets(Q,5,stock);
			q=atoi(Q)-Qty;
			//printf("%d-%s-%d",q,Q,Qty);
			fseek(stock,-3,SEEK_CUR);
			itoa(q,Q,10);
			if (q<10)
			{
				strcat(in,Q);
				fprintf(stock,"%s",in);
			}
			else
			{
				fprintf(stock,"%s",Q);
			}
			printf("DO YOU WANT TO ENTER MORE ITEMS?(IF YES ENTER 1 ELSE PRESS ANY NUMBER) ");
			scanf("%d",&c);
			fclose(stock);
		}	
		}while(c == 1);
		fclose(Invoice);
		system("cls");
		AfterLog();
}
void Delete()
{
	FILE *fp1, *fp2;
        char c,price[5];
        int del_line, temp = 1,ch,i;
    	fp1 = fopen("Invoice.txt", "r");
    	c = getc(fp1);
    	while (c != EOF)
    	{
     	 	printf("%c", c);
      		c = getc(fp1);
    	}
        rewind(fp1);
        printf(" \nEnter Item number to be deleted:");
        scanf("%d", &del_line);
		fp2 = fopen("copy.txt", "w");
        c = getc(fp1);
        while (c != EOF) {
        	if (c == '\n')
          		temp++;
          	if (temp != del_line)
          	{
            	putc(c, fp2);
          	}	
        	c = getc(fp1);
        }
        fclose(fp1);
        fclose(fp2);
        remove("Invoice.txt");
        rename("copy.txt", "Invoice.txt");
        printf("\nThe Invoice after being modified is as  follows:\n");
        fp1 = fopen("Invoice.txt", "r");
        c = getc(fp1);
        while (c != EOF) {
            printf("%c", c);
            c = getc(fp1);
        }
        sleep(2); 
        NumOfItems--;
        fclose(fp1);
    	system("cls");
		AfterLog();
}
int Invoice()
{	
	int ch,i;
	char c,price[5],Qty[2];
	FILE *fp1,*stock;
	printf("INVOICE\n\n");
	printf("ITEM NAME----------------PRICE OF 1----------------QTY---------------PRICE\n\n");
	fp1 = fopen("Invoice.txt", "r");
    c = getc(fp1);
    while (c != EOF)
    {
        printf("%c", c);
        c = getc(fp1);
    }
    rewind(fp1);
    Total = 0;
    for(i=1;i<=NumOfItems;i++)
	{
		fseek(fp1,44,SEEK_CUR);
		fgets(price,10,fp1);
		Total = Total + atoi(price);
	}
	printf("\n\n");
	printf("TOTAL BILL = %d\n\n",Total);
	printf("PROCEED TO PAYMENT(PRESS 1): ");
	scanf("%d",&ch);
	if(ch == 1)
	{
		Sales();
		return 0;
	}else
	{
		system("cls");
		AfterLog();	
	}     
}
void Sales()
{
	FILE *sales,*Temp;
	char TS[7],P[7];
	int T,PR;
	sales = fopen("Sales.txt","r");
	fgets(TS,7,sales);
	Temp = fopen("Temp.txt","w");
	T = atoi(TS);
	T = T + Total;
	fprintf(Temp,"%d\n",T);
	fgets(P,7,sales);
	PR = atoi(P);
	PR = PR + Profit;
	fprintf(Temp,"%d",PR);
	fclose(sales);
	remove("sales.txt");
	fclose(Temp);
	rename("Temp.txt","Sales.txt");
	system("cls");
}
void AdminLogin()
{
	FILE *Ad;
	int Id,FId,Found=0,compare,c,i,len;
	char Pass[10],FPass[10],CHECK[50],sId[5];
	do
	{
		printf("ENTER YOUR ID: ");
		scanf("%d",&Id);
		printf("ENTER PASSWORD: ");
		scanf("%s",Pass);
		Ad = fopen("Admins.txt","r");
		do
		{
			fgets(sId,5,Ad);
			FId = atoi(sId);
			if(FId == Id)
			{
				fseek(Ad,1,SEEK_CUR);
				len = strlen(Pass);
				fgets(FPass,len+1,Ad);
				compare = strcmp(FPass,Pass);
				if(compare == 0)
				{
					Found = 2;
					break;
				}
				Found = 1;
			}
		}while(fgets(CHECK,50,Ad) != NULL);
		fclose(Ad);
		if(Found == 1)
		{
			printf("ID OR PASSWORD DID'NT MATCH...... \n");
		}else if(Found == 0)
		{
			printf("ADMIN NOT FOUND \n");
			printf("--------------------- \n");
			printf("SIGN IN AS COUSTOMER IF NOT ADMIN \n");
			printf("PRESS 1 TO PROCEED TO LOGIN AS COUSTOMER: ");
			scanf("%d",&c);
			if(c == 1)
			{
				system("cls");
				LogIn();
			}
		}else if(Found == 2)
		{
			break;
		}
	}while(1);
	printf("LOGGING IN.......");
	sleep(1);
	system("cls");
	Admin();
}
