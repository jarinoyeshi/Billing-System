#include <stdio.h>
#include <stdlib.h>

char current_session[100];
char current_mail[100];

struct user_information{
    char id[10];
    char name[100];
    char address[100];
    int phone;
    char month_name[100];
    float user_water_amount;
    float meter_charge;
    float water_bill;
    float cost;
    float rate;
    float service_charge;
    float total_bill;
    float gas_bill;
} user;

///*---- Main function ----*///

int main(){
    int option;
    printf("\n---- Welcome to Utility Billing Management System-----\n");
    printf("\n If you want to Sign up press: [1]");
    printf("\n If you want to Login press:   [2]");
    printf("\n If you want to exit press:    [3]\n\n");
    scanf("%d",&option);
    if(option == 1){
        signUp();
    }
    else if(option == 2){
        User_login();
    }
    else if(option == 3){
        exit(1);
    }
    else
        printf("\n *****[ INVALID INPUT ]*****\n");
    main();
}

///* FUNCTION: -----user sign up-----*/

void signUp(){
    char email[200];
    char name[200];
    char password[200];
    char re_password[200];
    gets(stdin);
    printf("\n\n Enter your Name: ");
    gets(name);
    printf(" Enter your email: ");
    gets(email);
    printf(" Password: ");
    gets(password);
    printf(" Re- enter your Password: ");
    gets(re_password);
    if(strcmp(re_password,password)==0){
        printf("\n*** Registration successful**\n");
    }
    else{
        printf(" Incorrect password\n");
        signUp();
    }
    char ext[]=".txt";
    char temp_mail[100];
    strcpy(temp_mail,email);
    strcat(temp_mail,ext);
    FILE *file;
    file=fopen(temp_mail,"w");
    fprintf(file,"%s %s %s",name,email,password);
    fclose(file);
    User_portal();
}

///* FUNCTION: -----user Log in-----*/

void User_login(){
    char mail[100];
    printf("\n Enter your mail: ");
    fflush(stdin);
    gets(mail);
    strcpy(current_mail,mail);
    char ext[]=".txt";
    strcat(mail,ext);
    FILE *file;
    file=fopen(mail,"r");
    if(file==NULL){
        printf("\n\nYou aren't Registered yet\n");
        printf("1.Sign UP\n");
        printf("2.Exit\n");
        int option;
        scanf("%d",&option);
        if(option == 1){
            signUp();
        }
        else{
            exit(0);
        }
    }
    else{
        char f[122],fetch_pass[100];
        fscanf(file,"%s %s %s",f,f,fetch_pass);
        fclose(file);
        char password[20];
        printf(" Enter password: ");
        fflush(stdin);
        gets(password);
        if(strcmp(fetch_pass,password)==0){
            strcpy(current_session,mail);
            User_portal();
        }
        else{
            printf("Pass incorrect\n");
            exit(0);
        }
    }
}
///* FUNCTION: ----- logout ///
void logout(){
    strcpy(current_session," ");
    gets(stdin);
    main();
}

/// FUNCTION *-------- menu bar-----*////

void User_portal(){
    int option,flag=0;
    char d;
    printf("\n -------------[ Main menu ]------------ \n\n");
    printf("\n Water Bill:          [1]");
    printf("\n Service Charge:      [2]");
    printf("\n Electricity Bill:    [3]");
    printf("\n Gas Bill:            [4]");
    printf("\n Display Bills:       [5]");
    printf("\n Log Out:             [6]");
    printf("\n EXIT:                [7]");
    printf("\n Your Input: ");
    scanf("%d",&option);
    switch(option){
    case 1:
        water_bill_calculation();
        break;
    case 2:
        service_charge_calculation();
        break;
    case 3:
        electricityBill();
        break;
    case 4:
        gasBill();
        break;
    case 5:
        do{
            printf("\n----- To view the Billing History ---- ");
            printf("\n Electricity bill press:    [E/e]");
            printf("\n Gas Bill press:            [G/g]");
            printf("\n Water bill press:          [W/w]");
            printf("\n Service Charge press:      [S/s]");
            printf("\n YOUR INPUT: ");
            fflush(stdin);
            scanf(" %c",&d);
            if(d=='E' || d=='e' || d=='G' || d=='g' || d=='W'|| d=='w' || d=='S' || d=='s'){
                flag=1;
            }
            else printf("\n *****[ INVALID INPUT ]*****\n");
        }
        while( flag==0 );
        display_bill(d);
        break;
    case 6:
        logout();
        break;
    case 7:
        exit(0);
        break;
    default :
        printf("\n *****[ INVALID INPUT ]*****\n");
        User_portal();
        break;
    }
}

///* FUNCTION: --------Water calculation *///

void water_bill_calculation(){
    printf("\n -------------[ Water bill ]------------ ");
    float user_water_amount,water_bill,res_rate,com_rate,per_liter,month_value,meter_charge,initial;
    int area,month;
    FILE *fptr;
    char f;
    user_water_amount=water_bill=month_value=initial=0;
    const char * month_name[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    res_rate= 15.18;                    ///* value assign of fixed rates || Residential= 100 liter-> 15.18 taka
    com_rate= 42.00;                    /// Commercial= 100 liter-> 42.00 taka
    per_liter= 100;                     /// meter charge fixed 200.
    user.meter_charge=200;
    /* month selection */
    do{
        printf("\n Enter a month number to check your bill \n");
        printf("\n January press:  [1]");
        printf("\n February press: [2]");
        printf("\n March press:    [3]");
        printf("\n April press:    [4]");
        printf("\n May press:      [5]");
        printf("\n June press:     [6]");
        printf("\n July press:     [7]");
        printf("\n August press:   [8]");
        printf("\n September press:[9]");
        printf("\n October press:  [10]");
        printf("\n November press: [11]");
        printf("\n December press: [12]\n");
        printf("\n YOUR INPUT: ");
        scanf("%d",&month);
        if((month ==1)||(month==3)||(month==5)||(month==7)||(month==8)||(month==10)||(month==12)){
            month_value=31;
        }
        else if((month==4)||(month==6)||(month==9)||(month==11)){
            month_value=30;
        }
        else month_value=28;

        if((month<1)||(month>12)){
            printf("\n *****[ INVALID INPUT ]*****\n");
        }
    }
    while((month<1)||(month>12));
    do{
        printf("\n If you are a 'Residential' user press: [1] ");      ///* do while loop for wrong input from user */
        printf("\n If you are a 'Commercial' user  press: [2] \n");    ///* Case selection for two types of Residential and Commercial */
        printf("\n YOUR INPUT: ");
        scanf("%d",&area);
        if((area<1)||(area>2)){
            printf("\n *****[ INVALID INPUT ]*****");
        }
    }
    while((area<1)||(area>2));
    switch(area){
    case 1:
        printf("\n -------------***************------------ \n");         /// residential bill case
        printf("\n Enter User ID: ");
        fflush(stdin);
        gets(user.id);
        printf("\n Enter you Name: ");
        fflush(stdin);
        gets(user.name);
        printf(" Enter your address: ");
        fflush(stdin);
        gets(user.address);
        printf(" Enter your phone number:");
        scanf("%d",&user.phone);
        printf(" Please enter your per day usages water amount (Liter) : ");
        printf("\n YOUR INPUT: ");
        scanf("%f",&user.user_water_amount);
        initial= ((res_rate*user.user_water_amount*month_value)/per_liter);       ///* bill calculation*/
        user.water_bill=initial+user.meter_charge;
        strcpy(user.month_name,month_name[month-1]);

        printf("\n\n *************************************** ");
        printf("\n *****    Water Bill Receipt        ***** ");
        printf("\n *************************************** ");
        printf("\n ID:                 %s   ",user.id);
        printf("\n Name:               %s   ",user.name);
        printf("\n Address:            %s   ",user.address);
        printf("\n Phone Number:       0%d   ",user.phone);
        printf("\n Month name:         %s",user.month_name);
        printf("\n Used amount:        %.2f Liter",user.user_water_amount);
        printf("\n Meter charge:       %.2f Taka",user.meter_charge);
        printf("\n ----------------------------------------- ");
        printf("\n Your bill:          %.2f Taka",user.water_bill);

        printf("\n Do you want to save your bill? Y/N: ");    //data save in file
        fflush(stdin);
        scanf(" %c",&f);
        if(f =='Y' || f =='y'){
            fptr=fopen("water_bill.txt","a");
            if(fptr == NULL){
                printf("\n\n** No data exist! **");
            }
            fprintf(fptr,"\n %s %s %s 0%d %s %f %f \n", user.id,user.name,user.address, user.phone, user.month_name, user.user_water_amount, user.water_bill);
            fclose(fptr);
            printf("\n  saved! \n");
        }
        printf("\n Do you want to Pay your bill? Y/N: ");
        fflush(stdin);
        scanf(" %c",&f);
        if(f =='Y' || f =='y'){
            methodPayment();
        }
        else User_portal();
        break;

    case 2:
        printf("\n -------------***************------------ \n");                      /// Commercial water bill case
        printf("\n Enter User ID: ");
        fflush(stdin);
        gets(user.id);
        printf("\n Enter you Name: ");
        fflush(stdin);
        gets(user.name);
        printf(" Enter your address: ");
        fflush(stdin);
        gets(user.address);
        printf(" Enter your phone number:");
        scanf("%d",&user.phone);
        printf(" Please enter your per day usages water amount (Liter) : ");
        printf("\n YOUR INPUT: ");
        scanf("%f",&user.user_water_amount);

        initial= ((com_rate*user.user_water_amount*month_value)/per_liter);           ///* bill calculation*/
        user.water_bill=initial+user.meter_charge;
        strcpy(user.month_name,month_name[month-1]);
        printf("\n\n *************************************** ");
        printf("\n *****    Water Bill Receipt        ***** ");
        printf("\n *************************************** ");
        printf("\n ID:                 %s   ",user.id);
        printf("\n Name:               %s   ",user.name);
        printf("\n Address:            %s   ",user.address);
        printf("\n Phone Number:       0%d   ",user.phone);
        printf("\n Month name:         %s",user.month_name);
        printf("\n Used amount:        %.2f Liter",user.user_water_amount);
        printf("\n Meter charge:       %d Taka",user.meter_charge);
        printf("\n ----------------------------------------- ");
        printf("\n Your bill:          %.2f Taka\n",user.water_bill);

        printf("\n Do you want to save your bill? Y/N: ");               ///data save in file
        fflush(stdin);
        scanf(" %c",&f);
        if(f=='Y' || f=='y'){
            fptr=fopen("water_bill.txt","a");
            if(fptr==NULL){
                printf("\n\n** No data exist! **");
            }
            fprintf(fptr,"\n %s %s %s 0%d %s %f %f \n", user.id,user.name,user.address, user.phone, user.month_name, user.user_water_amount, user.water_bill);
            fclose(fptr);
            printf("\n  saved! \n");
        }
        printf("\n Do you want to Pay your bill? Y/N: ");
        fflush(stdin);
        scanf(" %c",&f);
        if(f=='Y' || f=='y'){
            methodPayment();
        }
        else User_portal();
    default:
        User_portal();
        break;
    }
}

///* FUNCTION: ------service charge calculation *///

void service_charge_calculation(){
    FILE *fptr;
    char f;
    printf("\n -------------[ Service Charge ]------------ ");
    printf("\n\n*** You can calculate the service charge of anything you want ***\n");
    printf("\n Enter User ID: ");
    fflush(stdin);
    gets(user.id);
    printf("\n Enter you Name: ");
    fflush(stdin);
    gets(user.name);
    printf(" Enter your address: ");
    fflush(stdin);
    gets(user.address);
    printf(" Enter your phone number:");
    scanf("%d",&user.phone);
    printf(" Enter you cost:  ");
    scanf("%f",&user.cost);
    printf(" Percentage of tax: ");
    scanf("%f",&user.rate);
    user.service_charge=user.cost*(user.rate/100);            /// service charge calculation

    printf("\n\n *************************************** ");
    printf("\n *****    Service Charge Receipt    ***** ");
    printf("\n *************************************** ");
    printf("\n Name:               %s   ",user.name);
    printf("\n Address:            %s   ",user.address);
    printf("\n Phone Number:       0%d   ",user.phone);
    printf("\n Cost:               %.2f Taka",user.cost);
    printf("\n Rate:               %.2f",user.rate);
    printf("\n ----------------------------------------- ");
    printf("\n Your bill:          %.2f Taka",user.service_charge);

    printf("\n Do you want to save your bill? Y/N: ");               ///data save in file
    fflush(stdin);
    scanf(" %c",&f);
    if(f =='Y' || f =='y'){
        fptr=fopen("service_charge.txt","a");
        if(fptr==NULL){
            printf("\n\n** No data exist! **");
        }
        fprintf(fptr,"\n %s %s %s 0%d %f %f %f\n", user.id,user.name,user.address, user.phone,user.cost, user.rate, user.service_charge );
        fclose(fptr);
        printf("\n  saved! \n");
    }
    printf("\n Do you want to Pay your bill? Y/N: ");
    fflush(stdin);
    scanf(" %c",&f);
    if(f =='Y' || f =='y'){
        methodPayment();
    }
    else User_portal();
}

///* FUNCTION: -----electricity payment *///

void electricityBill(){
    FILE *fptr;
    char f;
    int units;
    int i;
    float total_bill;
    printf("\n -------------[ Electricity Bill ]------------ \n\n");
    printf("\n Upto 20 Units .............................. = Taka.5/Unit    |");
    printf("\n 21 To 30 Units ..............................= Taka.8/Unit    |");
    printf("\n 31 To 50 Units ..............................= Taka.10.5/Unit |");
    printf("\n 51 To 150 Units .............................= Taka.12/Unit   |");
    printf("\n 151 To 250 Units ............................= Taka.15.5/Unit |");
    printf("\n 251 To 400 Units ............................= Taka.18/Unit   |");
    printf("\n 400+ Units ................................. = Taka.20/Unit   |\n");

    printf("\n -------------***************------------ \n");
    printf("\n Enter User ID: ");
    fflush(stdin);
    gets(user.id);
    printf("\n Enter you Name: ");
    fflush(stdin);
    gets(user.name);
    printf(" Enter your address: ");
    fflush(stdin);
    gets(user.address);
    printf(" Enter your phone number:");
    scanf("%d",&user.phone);
    printf("\n Please Enter Your Total Units Consumed : ");
    //here we are using scanf(""); function to get input from end user
    scanf("%d", & units);
    //after getting input from user, we will check the conditions to calculate actual bill charges
    if (units <= 20)
        user.total_bill = units * 5;
    else if (units <= 30)
        user.total_bill = units * 8;
    else if (units <= 50)
        user.total_bill = units * 10.5;
    else if (units <= 150)
        user.total_bill = units * 12;
    else if (units <= 250)
        user.total_bill = units * 15.5;
    else if (units <= 400)
        user.total_bill = units * 18;
    else user.total_bill = units * 20;
    printf("\n\n *************************************** ");
    printf("\n *****  Electricity Bill Receipt     ***** ");
    printf("\n *************************************** ");
    printf("\n ID:                 %s   ",user.id);
    printf("\n Name:               %s   ",user.name);
    printf("\n Address:            %s   ",user.address);
    printf("\n Phone Number:       0%d  ",user.phone);
    printf("\n ----------------------------------------- ");
    //and finally, we will show result with bill charges
    printf("\n\n Total Bill        %.2f\n", user.total_bill);

    printf("\n Do you want to save your bill? Y/N: ");
    fflush(stdin);
    scanf(" %c",&f);
    if(f=='Y' || f=='y'){
        fptr=fopen("electricity_bill.txt","a");
        if(fptr == NULL){
            printf("\n\n** No data exist! **");
        }
        fprintf(fptr,"\n %s %s %s 0%d %f  \n", user.id,user.name,user.address, user.phone, user.total_bill);
        fclose(fptr);
        printf("\n  saved! \n");
    }

    // If the user wants to pay
    printf("\n Do you want to Pay your bill? Y/N: ");
    fflush(stdin);
    scanf(" %c",&f);
    if(f =='Y' || f =='y'){
        methodPayment();
    }
    else User_portal();
}

//Prints type of payment

void methodPayment(){  ///* FUNCTION: -----Payment function
    int ch;
    printf("\n Cash Payment [1]");
    printf("\n ATM Payment [2]\n ");
    scanf("%d",&ch);
    if(ch==1)
        printf(" Paid\n");
    else if(ch==2)
        printf(" Paid\n");
    else{
        printf("\n *****[ INVALID INPUT ]*****\n");
        methodPayment();
    }
    User_portal();
}

///* FUNCTION: -----Computes gas bill *///

void gasBill(){
    FILE *fptr;
    char f;
    float km,cost;
    printf("\n -------------[ Gas Bill ]--------------- \n\n");
    printf("\n -------------***************------------ \n");
    printf("\n Enter User ID: ");
    fflush(stdin);
    gets(user.id);
    printf("\n Enter you Name: ");
    fflush(stdin);
    gets(user.name);
    printf(" Enter your address: ");
    fflush(stdin);
    gets(user.address);
    printf(" Enter your phone number:");
    scanf("%d",&user.phone);
    printf(" Enter total hour: ");
    scanf("%f",&km);
    printf(" Enter cost: ");
    scanf("%f",&cost);
    user.gas_bill=(km*cost);
    printf("\n\n *************************************** ");
    printf("\n *****  Gas Bill Receipt       ***** ");
    printf("\n *************************************** ");
    printf("\n ID:                 %s   ",user.id);
    printf("\n Name:               %s   ",user.name);
    printf("\n Address:            %s   ",user.address);
    printf("\n Phone Number:       0%d  ",user.phone);
    printf("\n ----------------------------------------- ");
    //and finally, we will show result with bill charges
    printf("\n\n Total Bill       %.2f\n", user.gas_bill);

    printf("\n Do you want to save your bill? Y/N: ");
    fflush(stdin);
    scanf(" %c",&f);
    if(f =='Y' || f =='y'){
        fptr=fopen("gas_bill.txt","a");
        if(fptr==NULL)
        {
            printf("\n\n** No data exist! **");
        }
        fprintf(fptr,"\n %s %s %s 0%d %f \n", user.id,user.name,user.address, user.phone, user.gas_bill);
        fclose(fptr);
        printf("\n  saved! \n");
    }
    printf("\n Do you want to Pay your bill? Y/N: ");
    fflush(stdin);
    scanf(" %c",&f);
    if(f =='Y' || f =='y'){
        methodPayment();
    }
    else User_portal();
}

void display_bill(char d){   ///* FUNCTION: -----Display bill
    FILE *fptr;
    char id[100];
    if(d =='E' || d =='e'){
        printf("\n** Enter user id: ");
        fflush(stdin);
        gets(id);
        printf("\n----- Electricity Bill History---------\n");
        fptr = fopen ("electricity_bill.txt", "r");
        if(fptr ==NULL)
        {
            printf(" Error ");
            exit(1);
        }
        while(fscanf(fptr,"\n %s %s %s %d %f \n", user.id,user.name,user.address,&user.phone,&user.total_bill)!= EOF)
        {
            if(strcmp(user.id,id)==0)
            {
                printf("\n ID: %s \n Name: %s \n Address: %s \n Phone: 0%d ", user.id,user.name,user.address, user.phone);
                printf("\n--------------");
                printf("\n Bill    :%.2f Taka\n\n",user.total_bill);
            }

        }
        fclose(fptr);
        User_portal();
    }
    else if(d =='G' || d =='g'){
        printf("\n** Enter user id: ");
        fflush(stdin);
        gets(id);
        printf("\n----- Gas Bill History---------\n");
        fptr = fopen ("gas_bill.txt", "r");
        if(fptr == NULL){
            printf(" Error ");
            exit(1);
        }
        while(fscanf(fptr,"\n %s %s %s %d %f \n", user.id,user.name,user.address,&user.phone,&user.gas_bill)!= EOF){
            if(strcmp(user.id,id)==0){
                printf("\n ID: %s \n Name: %s \n Address: %s \n Phone: 0%d ", user.id,user.name,user.address, user.phone);
                printf("\n--------------");
                printf("\n Bill    :%.2f Taka\n\n",user.gas_bill);
            }
        }
        fclose(fptr);
        User_portal();
    }
    else if(d =='W'|| d =='w'){
        printf("\n** Enter user id: ");
        fflush(stdin);
        gets(id);

        printf("\n----- Water Bill History---------\n");
        fptr = fopen ("water_bill.txt", "r");
        if(fptr == NULL){
            printf(" Error ");
            exit(1);
        }
        while(fscanf(fptr," %s %s %s %d %s %f %f ", user.id,user.name,user.address,&user.phone, user.month_name,&user.user_water_amount,&user.water_bill)!= EOF){
            if(strcmp(user.id,id)==0){
                printf("\n ID: %s \n Name: %s \n Address: %s \n Phone: 0%d \n Month: %s \n Used amount %.2f Liter", user.id,user.name,user.address, user.phone, user.month_name, user.user_water_amount);
                printf("\n--------------");
                printf("\n Bill    :%.2f Taka\n\n",user.water_bill);
            }
        }
        fclose(fptr);
        User_portal();
    }
    else {
        printf("\n** Enter user id: ");
        fflush(stdin);
        gets(id);
        printf("\n----- Service Charge History---------\n");
        fptr = fopen ("service_charge.txt", "r");
        if(fptr == NULL){
            printf(" Error ");
            exit(1);
        }
        while(fscanf(fptr," %s %s %s %d %f %f %f ", user.id,user.name,user.address,&user.phone, &user.cost,&user.rate,&user.service_charge)!= EOF){
            fprintf(fptr,"\n %s %s %s %d %f %f %f\n", user.id,user.name,user.address, user.phone,user.cost, user.rate, user.service_charge );
            if(strcmp(user.id,id)==0){
                printf("\n ID: %s \n Name: %s \n Address: %s \n Phone: 0%d \n Cost: %.2f Taka \n Rate %.2f ", user.id,user.name,user.address, user.phone, user.cost, user.rate);
                printf("\n--------------");
                printf("\n Bill    :%.2f Taka\n\n",user.service_charge);
            }
        }
        fclose(fptr);
        User_portal();
    }
    return 0;
}
