#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUIT 10    //QUIT=10
#define BUFFER_LENGTH 1024   
#define MAX_CODES 500000  

/* Mhkh apo alfarithmitika gnwstoy megethoys */
/*#define anagnwristiko xarakthres
(o prometaglwttisths antikathista to anagnwristiko me toys xarakthres)*/
#define CODE_STRING_LENGTH 15 // mhkh kwdikwn kartwn=15  
#define PRODUCT_CODE_STRING_LENGTH 20  // mhkh kwdikwn proiontwn=20
#define TEAM_STRING_LENGTH 1  //mhkh kwdikwn omadwn=1
#define PRIZE_STRING_LENGTH	20 //mhkh dwrwn=20

/* Typoi Pinakwn [Xarakthrwn] gia ta alfarithmitika gnwstoy megethoys */
/*typedef typos onoma (xrhsimopoiei to onoma anti  gia typo)*/
typedef char code_string[CODE_STRING_LENGTH+1];
typedef char team_code_string[TEAM_STRING_LENGTH+1];
typedef char product_code_string[PRODUCT_CODE_STRING_LENGTH+1];
typedef char prize_code_string[PRIZE_STRING_LENGTH+1];

struct product  //domh proion
{
    product_code_string pcode;  //kwdikos proiontwn typoy product_code_string
    int quant; //posothta
};

struct products_list  //lista proiontwn
{
    int length;  //mhkos listas
    struct product * products; //lista proiontwn poy apoteleitai apo proionta
                               //(deikths products typoy product deixnei sth domh product)
}; 

struct product_data  //dedomena proiontwn (kathe grammh sto arxeio 1 apoteleitai apo):
{
    int day_of_week; // hmera poy agorastikan ta proionta
    code_string code;  //kwdikos kartas typoy (char code_string[CODE_STRING_LENGTH+1]=15)
    struct products_list p_list;  //lista proiontwn typoy product_list
    struct product_data * next; //deikths poy deixnei sto epomeno stoixeio ths listas proiontwn
};

struct hash_table  //hash table
{
    int length; // mikos pinakas
    int total_records;  //synolikos arithmos eggrafwn 
    struct product_data * p_data; //deikths poy deixnei sth domh product data (1 grammh - eggrafh)
};

struct code_vector //domh poy anaparista pinaka apo kwdikoys
{
    int length; //mhkos pinakas
    code_string * codes;//deikths typoy char code_string[CODE_STRING_LENGTH+1] 
};//card_team

struct product_codes_vector//domh me pinaka kwdikwn proiontwn
{
    int length;//mhkos pinakas
    product_code_string *codes; //deikths typoy (char product_code_string[PRODUCT_CODE_STRING_LENGTH+1])
};

struct team_data  // domh dedomena omadas
{
    team_code_string team_code;  //kwdikos omadas typoy (char team_code_string[TEAM_STRING_LENGTH+1])
    double factor;//syntelesths pontwn
    struct product_codes_vector pcv;// metablhth typoy product_codes_vector(pinakas kwdikwn proiontwn)
};

struct team_data_vector   //domh poy anaparista pinaka me dedomena omadas proiontwn
{
    int length;//mhkos pinakas
    struct team_data * data;//deikths poy deixnei sta dedomena omadas(team_data)
};//team_vector

typedef double price_array[8];

struct price_data//domh me dedomena timwn proiontwn
{
    product_code_string pcode;//kwdikos proiontwn typoy
                             //(char product_code_string[PRODUCT_CODE_STRING_LENGTH+1])
    price_array price;//timh monadas toy  kathe proiontos
};

struct price_data_vector //domh me pinaka apo dedomena timwn proiontwn 
{
    int length;// mhkos pinaka
    struct price_data * data;//deixnei sth domh dedomena timwn proiontwn(price_data)
};//price_vector

struct card_and_score  //domh me kartes kai pontoi kartwn
{
    char * card; 
    double score;  //pontoi kartwn
};

struct prize_data /* domh dedomena dwrwn */
{
    prize_code_string prize;//dwra typoy (char prize_code_string[PRIZE_STRING_LENGTH+1])
    double required_points;//apaitoymenoi pontoi
};

struct prize_data_vector //domh me pinaka apo dedomena dwrwn
{
    int length;//mhkos pinaka
    struct prize_data * data;//deixths data(dedomena) poy deixnei sth domh prize_data(dedomena dwrwn)
};//prize_vector

/* Synarthseis menou */
void show_menu();
int get_choice();
void handle(int choice);
/* Synarthseis epilogwn menou */
void diabase_arxeio_1();
void diabase_arxeio_2();
void diabase_arxeio_3();
void bres_top_10();  //epilogh 4
void diabase_arxeio_4();//epilogh 5
void diabase_arxeio_5(); //epilogh 6
void bres_dwra_omadas();  //epilogh 7
void ypologise_sygkroyseis(); //epilogh 8
void anazhthsh(); //epilogh 9
/* Loipes synarthseis */
void die_if(int condition, char * reason); /* Termatizei to programma an to condition einai True,              
                                              typwnontas to logo 'reason' */
struct product_data analyze(char * string);/* Analyei mia symboloseira poy exei dedomena apo to 
                                              kentriko arxeio kai epistrefei se mia domh thn 
                                              epithymhth morfh toys (int, ...). */
int compute_hash_length(int unique); /* Ypologizei to megethos toy pinaka katakermatismoy symfwna
                                        me to zhtoymeno */
double get_product_factor(product_code_string pcode);//pairnei syntelesth proiontwn
double get_product_price(product_code_string pcode, int day);//pairnei timh proiontwn

/* Synarthseis gia diaxeirish pinakwn dynamikoy megethoys gia apothikeysh kwdikwn kartwn. */
struct code_vector * init_code_vector(int num_codes);/* Arxikopoiei mia domh poy anaparista pinaka 
                                              apo kwdikoys, me bash to zhtoymeno plithos kwdikwn */
void free_code_vector(struct code_vector * cl_ptr);/* Apeleytheronei th mnhmh ths domhs poy 
                                                      epistrefei h init_code_vector */
void append_code(struct code_vector * cl_ptr, char * code);/* Prosartei ena kwdiko se mia domh 
                                                              struct code_vector */
int find_unique_codes(struct code_vector * cl_ptr);/* Ypologismos twn monadikwn kwdikwn se mia 
                                            domh code_vector,xrhsimopoiei qsort gia taksinomish */

/* Synarthseis gia ton pinaka katakermatismoy. */
unsigned hash_func(const char *s);
unsigned fnv_32_hash(const char *buf);
unsigned hash(const char *str);
struct hash_table * init_hash_table(int hashlen);/* Arxikopoiei to hash table mas,
                                                    na exei hashlen xwrhtikothta */
void free_hash_table(struct hash_table * ht);/* Apodesmeyei ton pinaka katakermatismoy */
void put_hash_table(code_string code, struct product_data data);/* Ypologizoyme poy prepei na mpoyn 
ta data. Einai o kwdikos sto hash_table[index] idios me ton dedomeno? Exoyme xwro gia na mpoyn ta data? 
Bres me linear probing adeia thesh.Oso o apothikeymenos kwdikos den einai to keno string,aykshse to 
index kai an kseperasei to  my_hash->length,pame pali apo to 0.*/
   
struct product_data * get_hash_table(code_string code);/*synarthsh gethashtable epistrefei mia 
                                                        domh product_data*/

/* Synarthseis gia th diaxeirish toy pinaka timwn proiontwn */
struct price_data analyze_price(char * string);
void price_vector_add(struct price_data pd);

/* O pinakas katakermatismoy mas. */
struct hash_table * my_hash = NULL;
/* Pinakas me ta dedomena omadwn proiontwn */
struct team_data_vector team_vector;
/* Pinakas me ta dedomena timwn proiontwn */
struct price_data_vector price_vector;
/* Pinakas me kwdikoys omadas */
struct code_vector card_team;
/* Pinakas me dedomena dwrwn */
struct prize_data_vector prize_vector;

int main(int argc, char *argv[])
{
    int choice = 0;
    printf("***************************************************\n");
    printf("********************** SUPERMARKET ****************\n");
    printf("***************************************************\n");
    printf("\n");
    /* Algorithmos menou */
    while (choice != QUIT)//(QUIT=10)
    {
        show_menu();
        choice = get_choice();
        handle(choice);
    }
    free_hash_table(my_hash);
    return 0;
}

/* Deixnei to menu gia to xrhsth me apla printf. */
void show_menu()
{
    printf("***********************************************************\n");
    printf("*--------------------->Menu Epilogwn<---------------------*\n");
    printf("***********************************************************\n\n");
    printf(" #Gia thn epilogh 4, prepei na exoyn ginei oi 1,2,3!!!    \n");
    printf(" #Gia thn epilogh 7, prepei na exoyn ginei oi 1,2,3,5,6!!!\n\n");


    printf(" 1. Fortwsh arxeioy 1 (agores)\n");
    printf(" 2. Fortwsh arxeioy 2 (omades proiontwn)\n");
    printf(" 3. Fortwsh arxeioy 3 (times proiontwn)\n");
    printf(" 4. Eyresh 10 kartwn me perissoteroys pontoys\n");
    printf(" 5. Fortwsh arxeioy kwdikwn omadas pelatwn\n");
    printf(" 6. Fortwsh arxeioy dedomenwn dwrwn\n");
    printf(" 7. Ypologismos dwrwn omadas\n");
    printf(" 8. Ypologismos sygkroysewn ston pinaka katakermatismoy\n");
    printf(" 9. Anazhthsh eggrafhs agora me bash kwdiko\n");
    printf(" 10. Termatismos\n");
}

/* Diabazei ena arithmo apo to plhktrologio kai ton epistrefei */
int get_choice()
{
    int choice;
    char buf[BUFFER_LENGTH];//buf==line(1024)
    do
    {
        printf(" Epilogh? ");
        /* Diabazoyme pio kathara ena arithmo etsi, para me th scanf...(h scanf otan prokeitai na 
        diabasei arithmhtikes times, agnoei toys xarakthres diasthmatos kai allaghs grammhs enw 
        otan diabasei xarakthres (char) den ta agnoei. se kathe periptwsh h scanf afhnei sto 
        buffer eisodoy to xarakthra allaghs grammhs ("\n"enter)) */
        fgets(buf, sizeof(buf), stdin);/*Diabazei mia grammh mexri kai to \n apo to arxeio stdin(plhktrologio) */
        /* Metatrepoyme to buf se akeraio */
        choice = atoi(buf);
        if (choice<1 || choice>10)
            printf("Parakalw grapste arithmo (1-10).\n");
    }
    while (choice<1 || choice>10);
    return choice;
}

/* Ektelei thn energeia poy antistoixei sto choice */
void handle(int choice)
{
    switch(choice)
    {
    case 1:
        diabase_arxeio_1();
        break;
    case 2:
        diabase_arxeio_2();
        break;
    case 3:
        diabase_arxeio_3();
        break;
    case 4:
        bres_top_10();
        break;
    case 5:
        diabase_arxeio_4();
        break;
    case 6:
        diabase_arxeio_5();
        break;
    case 7:
        bres_dwra_omadas();
        break;
    case 8:
        ypologise_sygkroyseis();
        break;
    case 9:
        anazhthsh();
        break;
    case 10:
        break;
    }
}

/* Afairei tis allages grammhs \r h \n apo mia symboloseira */
void remove_eol (char * buf)
{
    char * c;
    /* An brethei \r h \n sto telos ths grammhs, to afairoyme */
    c = strchr(buf, '\r');/*char * strchr ( char * str, int character );*/
    if ( c != NULL )
        *c = '\0';
    c = strchr(buf, '\n');
    if ( c != NULL )
        *c = '\0';
}

/* Diabazei mia grammh apo thn kyria eisodo (stdin). */
void diabase_keimeno(char * buf, int size)
{
    fgets(buf, size, stdin);
    remove_eol(buf);
}

/* Metablhth poy periexei to onoma arxeioy */
char onoma_arxeioy[BUFFER_LENGTH];

/* Synarthsh poy diabazei ena onoma arxeioy apo thn kyria eisodo kai to
 * swzei sthn katholikh metablhth "onoma_arxeioy". An o xrhsths patisei
 * mono Enter h metablhth pairnei thn timh ths parametroy "prokathorismeno". */
void diabase_onoma_arxeioy(char * prokathorismeno)
{
    char buf[BUFFER_LENGTH];

    printf("Onoma arxeioy? (Enter = %s)", prokathorismeno);
    diabase_keimeno(buf, sizeof(buf));
    /* An o xrhsths pathsei mono Enter, tote buf = prokathorismeno */
    if (strlen(buf) == 0)
        strcpy(buf, prokathorismeno);
    strcpy(onoma_arxeioy, buf);
}

/* Synarthsh poy diabazei to prwto arxeio me ta basika dedomena */
void diabase_arxeio_1()//(1...7) ΒΓΔΕ0134Α256789P1,2;P2,4; …
{
    FILE *fp;
    char line[BUFFER_LENGTH];
    struct product_data data;//domh me dedomena apo stoixeia kathe grammhs apo to arxeio1.txt
    int unique, hashlen;
    struct code_vector * cl_ptr;

  /* 1.Sth cl_ptr tha sosoyme oloys toys kwdikoys gia na doyme poioi einai monadikoi. */
    cl_ptr = init_code_vector(MAX_CODES);/* init_code_vector()[Arxikopoiei] mia domh poy anaparista 
                                        pinaka apo kwdikoys, me bash to zhtoymeno plithos kwdikwn */
    
    /* Epilogh onomatos arxeioy kai anoigma toy gia anagnwsh */
    diabase_onoma_arxeioy("arxeio1.txt");
    fp = fopen(onoma_arxeioy, "r");
    die_if(fp == NULL, "Sfalma! Den mporese na anoiksei to arxeio...");
    
  printf("\n1.Ypologismos arithmoy diaforetikwn kwdikwn gia kartes.... ");
        /* Diabasma dedomenwn arxeioy 1 */
        while(!feof(fp))
        {
            /* Diabasma mias grammhs apo to arxeio sth metablhth line */
            /*   void * memset ( void * ptr, int value, size_t num );
            Fill block of memory.Sets the first num bytes of the block of memory pointed
            by ptr to the specified value (interpreted as an unsigned char).Return Value ptr is returned.*/
            memset(line, 0, sizeof(line));	/* Ola ta byte sto line == 0 */
            fgets(line, sizeof(line), fp);
            remove_eol(line);/* Afairei tis allages grammhs \r h \n apo mia symboloseira */
            /* Agnooyme an yparxoyn kenes grammes */
            if (strlen(line) == 0)
                continue;
    /*2.Swzoyme th grammh se mia domh product_data */
            data = analyze(line);
            /*struct product_data analyze(char * string)-Analyei mia symboloseira
            poy exei dedomena apo to kentriko arxeio kai epistrefei se mia domh thn epithymhth morfh
            toys (int, ...).xrhsimopoiei thn strtok gia na afairesei " " ":""," kai epistrefei 
            domh product_data*/
            
    /*3. Apothikeyoyme ton kwdiko gia epeksergasia meta. */
            append_code(cl_ptr, data.code);/*Prosartei ena kwdiko se mia domh  */
            free(data.p_list.products);
        }
  printf("Egine\n"); 
       
   /*4.Ypologismos twn monadikwn kwdikwn se mia domh code_vector */
    unique = find_unique_codes(cl_ptr);
                                    	/* Kanoyme taksinomhsh sth lista twn kwdikwn */
 		                      /*qsort(cl_ptr->codes, cl_ptr->length, sizeof(code_string), codecmp);
                                   Elegxoyme apo 0 ews N-1 an enas kwdikos X[i] me ton X[i+1] einai
                                	  diaforetikoi, kai oso einai diaforetikoi ayksanoyme to
                                      num_unique, alliws  paraleipoyme tis epanalipseis. */ 
    printf(" -Codes length: %d, unique codes: %d\n", cl_ptr->length, unique);
    
    /* 5.Ypologismos megethoys pinaka katakermatismoy (>2*N kai prwtos)*/
    hashlen = compute_hash_length(unique);
    printf(" -Mhkos pinaka katakermatismoy: %d\n", hashlen);
    my_hash = init_hash_table(hashlen);/*init_hash_table()-Arxikopoiei to hash table mas, na exei hashlen xwrhtikothta */
    
  printf(" -Fortoma dedomenwn ston pinaka katakermatismoy.....");
        /* Fortwma dedomenwn ston pinaka katakermatismoy */
        rewind(fp);/*Sets the position indicator associated with stream to the beginning of the file.*/
        
        /* Diabasma dedomenwn arxeioy 1 */
        while(!feof(fp))
        {
            /* Diabasma mias grammhs apo to arxeio sth metablhth line */
            memset(line, 0, sizeof(line));	/* Ola ta byte sto line == 0 */
            fgets(line, sizeof(line), fp);
            remove_eol(line);//diagrafei \n \r
            /* Agnooyme an yparxoyn kenes grammes */
            if (strlen(line) == 0)
                continue;
            /* Swzoyme th grammh se mia domh product_data */
            data = analyze(line);
            /* Apothikeyoyme ton kwdiko gia epeksergasia meta. */
            put_hash_table(data.code, data);/* Ypologizoyme poy prepei na mpoyn ta data 
                                        Einai o kwdikos sto hash_table[index] idios me ton dedomeno?
                                        Exoyme xwro gia na mpoyn ta data? 
                                        Bres me linear probing adeia thesh.Oso o apothikeymenos 
                                        kwdikos den einai to keno string,aykshse to index kai an
                                        kseperasei to  my_hash->length,pame pali apo to 0.*/
        }
  printf("Egine\n");
    
    printf(" -Yparxoyn %d eggrafes ston pinaka.\n\n", my_hash->total_records);
    /* Apeleytheronoyme to cl_ptr, kai kleinoyme to arxeio */
    free_code_vector(cl_ptr);
    fclose(fp);
}

void diabase_arxeio_2()//arxeio omadwn proiontwn, A:χ2:P1,P6,P9, …
{
    FILE *fp;
    char line[BUFFER_LENGTH];
    char * str;
    char *c;
    int i, k;

    team_vector.length = 0;
    team_vector.data = NULL;

    /* Epilogh onomatos arxeioy kai anoigma toy gia anagnwsh */
    diabase_onoma_arxeioy("arxeio2.txt");
    fp = fopen(onoma_arxeioy, "r");
    die_if(fp == NULL, "Sfalma! Den mporese na anoiksei to arxeio...");
    printf("\n2.Diabasma arxeioy(arxeio2.txt) omadwn proiontwn .....");
        while(!feof(fp))
        {
            /* Diabasma mias grammhs apo to arxeio sth metablhth line */
            memset(line, 0, sizeof(line));	/* Ola ta byte sto line == 0 */
            fgets(line, sizeof(line), fp);
            remove_eol(line);
            /* Agnooyme an yparxoyn kenes grammes */
            if (strlen(line) == 0)
                continue;
            team_vector.length++;//pairnoyme to mhkos(length)
        }//desmeyoyme xwro sth mnhmh, length*sizeof()
        team_vector.data = calloc(team_vector.length, sizeof(struct team_data));
        die_if(team_vector.data == NULL, "Teleiwse h mnhmh");
        rewind(fp);
        k = 0;
        while(!feof(fp))//afairoyme ":"kai"," me th xrhsh strtok()
        {
            /* Diabasma mias grammhs apo to arxeio sth metablhth line */
            memset(line, 0, sizeof(line));	/* Ola ta byte sto line == 0 */
            fgets(line, sizeof(line), fp);
            remove_eol(line);
            /* Agnooyme an yparxoyn kenes grammes */
            if (strlen(line) == 0)
                continue;
            str = strtok(line, ":");//to format einai A:χ2:P1,P6,P9, …
            strcpy(team_vector.data[k].team_code, str);
            str = strtok(NULL, ":");
            team_vector.data[k].factor = atof(str);/*double atof (const char* str);Convert string to double
                                                    Parses the C string str, interpreting its content as a floating point number and returns its value as a double.*/
            str = strtok(NULL, ":");
            c = str;
            while (*c != '\0')
            {
                if (*c == ',')
                    team_vector.data[k].pcv.length++;//analoga me ta kommata einai kai to mhkos
                c++;
            }
            team_vector.data[k].pcv.length++;//twra poy kseroyme to mhkos(length) desmeyoyme to xwro poy xreiazetai
            team_vector.data[k].pcv.codes = calloc(team_vector.data[k].pcv.length, sizeof(product_code_string));
            die_if(team_vector.data[k].pcv.codes == NULL, "Den exoyme mnhmh");
            str = strtok(str, ",");//prwth klhsh
            i = 0;
            while (str != NULL)
            {
                strcpy(team_vector.data[k].pcv.codes[i], str);
                str = strtok(NULL, ",");//diadoxikes klhseis perilambanei to NULL ws prwto orisma ,afairei to","apo to str
                i++;
            }
            k++;
        }
    printf("Egine\n\n");
    fclose(fp);
    /*
    for (k=0; k<team_vector.length; k++)
    {
    	printf("Team code: %s, Factor: %f\n", team_vector.data[k].team_code, team_vector.data[k].factor);
    	for (i=0; i<team_vector.data[k].pcv.length; i++)
    		printf("%s,", team_vector.data[k].pcv.codes[i]);
    	printf("\n");
    }
    */
}

void diabase_arxeio_3()//arxeio me times proiontwn, P1  20 1 5 7
{
    FILE *fp;
    char line[BUFFER_LENGTH];
    struct price_data pd;
    int i, day;
    double max_price;
    /* Epilogh onomatos arxeioy kai anoigma toy gia anagnwsh */
    diabase_onoma_arxeioy("arxeio3.txt");
    fp = fopen(onoma_arxeioy, "r");
    die_if(fp == NULL, "Sfalma! Den mporese na anoiksei to arxeio...");
    printf("\n3.Diabasma arxeioy(arxeio3.txt) me times proiontwn .....");
        while(!feof(fp))
        {
            /* Diabasma mias grammhs apo to arxeio sth metablhth line */
            memset(line, 0, sizeof(line));	/* Ola ta byte sto line == 0 */
            fgets(line, sizeof(line), fp);
            remove_eol(line);
            /* Agnooyme an yparxoyn kenes grammes */
            if (strlen(line) == 0)
                continue;
            /* Synarthseis gia th diaxeirish toy pinaka timwn proiontwn */
            pd = analyze_price(line);//kanei analize kathe grammh (P1  20 1 5 7)
            price_vector_add(pd);
        }
        for (i=0; i<price_vector.length; i++)
        {
            max_price = price_vector.data[i].price[1];
            for (day = 1; day <= 7; day++)
                if (price_vector.data[i].price[day] > max_price)
                    max_price = price_vector.data[i].price[day];
            for (day = 1; day <= 7; day++)
                if (price_vector.data[i].price[day] == 0)
                    price_vector.data[i].price[day] = max_price;
        }
        /*
        for (i=0; i<price_vector.length; i++)
        {
        	printf("Code: %s. ", price_vector.data[i].pcode);
        	for (day = 1; day <= 7; day++)
        		printf(" %d : %.2f,", day, price_vector.data[i].price[day]);
        	printf("\n");
        }
        */
    printf("Egine.\n\n");
    fclose(fp);
}

double pontoi_kartas(code_string code)
{
    double pontoi;
    struct product_data * node;//deikths node poy deixnee se mia domh product_data
    double price;
    double factor;
    int i;

    pontoi = 0;
    node = get_hash_table(code);
    while(node != NULL)
    {
        for (i=0; i<node->p_list.length; i++)
        {
            price =  get_product_price(node->p_list.products[i].pcode, node->day_of_week);
            factor = get_product_factor(node->p_list.products[i].pcode);
            pontoi = pontoi + node->p_list.products[i].quant * price * factor;
        }
        node = node->next;
    }
    return pontoi;
}

int score_cmp(const void * p1, const void * p2)
{
    struct card_and_score * s1;
    struct card_and_score * s2;

    s1 = (struct card_and_score *) p1;
    s2 = (struct card_and_score *) p2;

    return (s2->score - s1->score);
}
void bres_top_10()
{
    struct card_and_score * pinakas_pontwn;
    int i, j;

    pinakas_pontwn = calloc(my_hash->length, sizeof(struct card_and_score));
    j = 0;
    for (i=0; i<my_hash->length; i++)
        if (strlen(my_hash->p_data[i].code) > 0)
        {
            pinakas_pontwn[j].score = pontoi_kartas(my_hash->p_data[i].code);
            pinakas_pontwn[j].card = my_hash->p_data[i].code;
            j++;
        }
    qsort(pinakas_pontwn, my_hash->length, sizeof(struct card_and_score),score_cmp);
    printf("\n4.Oi 10 kartes poy sygkentrwsan toys perissoteroys pontoys einai:\n");
    printf("===================================================================\n");
    printf(" Nr.   Kwdikos       Pontoi\n");
    for (i=0; i<10; i++)
    {
        printf(" %d. %s  %.2f\n", i+1, pinakas_pontwn[i].card, pinakas_pontwn[i].score);
    }
}

void diabase_arxeio_4()
{
    FILE *fp;
    char line[BUFFER_LENGTH];

    /* Epilogh onomatos arxeioy kai anoigma toy gia anagnwsh */
    diabase_onoma_arxeioy("arxeio4.txt");
    fp = fopen(onoma_arxeioy, "r");
    die_if(fp == NULL, "Sfalma! Den mporese na anoiksei to arxeio...");
    printf(" 5.Diabasma arxeioy(arxeio4.txt) kwdikwn omadas pelatwn .....");
        while(!feof(fp))
        {
            /* Diabasma mias grammhs apo to arxeio sth metablhth line */
            memset(line, 0, sizeof(line));	/* Ola ta byte sto line == 0 */
            fgets(line, sizeof(line), fp);
            remove_eol(line);
            /* Agnooyme an yparxoyn kenes grammes */
            if (strlen(line) == 0)
                continue;
            card_team.length++;
            card_team.codes = realloc(card_team.codes, card_team.length * sizeof(code_string));
            strcpy(card_team.codes[card_team.length-1], line);
        }
    printf("Egine.\n\n");
    fclose(fp);
}

void diabase_arxeio_5()
{
    FILE *fp;
    char line[BUFFER_LENGTH];
    int i;

    /* Epilogh onomatos arxeioy kai anoigma toy gia anagnwsh */
    diabase_onoma_arxeioy("arxeio5.txt");
    fp = fopen(onoma_arxeioy, "r");
    die_if(fp == NULL, "Sfalma! Den mporese na anoiksei to arxeio...");
    printf(" 6.Diabasma arxeioy (arxeio5.txt) dedomenwn dwrwn .....");
        while(!feof(fp))
        {
            /* Diabasma mias grammhs apo to arxeio sth metablhth line */
            memset(line, 0, sizeof(line));	/* Ola ta byte sto line == 0 */
            fgets(line, sizeof(line), fp);
            remove_eol(line);
            /* Agnooyme an yparxoyn kenes grammes */
            if (strlen(line) == 0)
                continue;
            prize_vector.length++;
            prize_vector.data = realloc(prize_vector.data, prize_vector.length * sizeof(struct prize_data));
            i = prize_vector.length - 1;
            sscanf(line, "%s %lf", prize_vector.data[i].prize, &prize_vector.data[i].required_points);
        }
    printf("Egine.\n\n");
    fclose(fp);
}

void bres_dwra_omadas()
{
    double synolo_pontwn;
    int i;

    synolo_pontwn = 0;
    printf("\n7.H omada poy apoteleitai apo tis kartes:\n");
    printf("========================================\n");
    for (i=0; i<card_team.length; i++)
    {
        synolo_pontwn += pontoi_kartas(card_team.codes[i]);
        printf("%s\n", card_team.codes[i]);
    }
    printf("Diakaioyta ta dwra: ");
    for (i=0; i<prize_vector.length; i++)
        if (synolo_pontwn > prize_vector.data[i].required_points)
            printf("%s ", prize_vector.data[i].prize);
    printf("\n");
}

void dokimase_hash_function(unsigned (*hash_function)(const char *))
{
    int i, idx;
    char * flag;
    int sygkroyseis = 0;

    flag = calloc(1, my_hash->length);
    die_if(flag == NULL, "Teleiwse h mnhmh.");
    for (i=0; i<my_hash->length; i++)
    {
        if (strlen(my_hash->p_data[i].code) > 0)
        {
            idx = hash_function(my_hash->p_data[i].code);
            if (flag[idx] != 0)
                sygkroyseis++;
            flag[idx] = 1;
        }
    }
    printf("Arithmos sygkroysewn gia th hash_func: %d\n", sygkroyseis);
}

void ypologise_sygkroyseis()
{
    printf("\nH synarthsh apo to paradeigma hash_func\n");
    dokimase_hash_function( hash_func );
    printf("\nH synarthsh fnv_32_hash\n");
    dokimase_hash_function( fnv_32_hash );
    printf("\nH synarthsh djb2 hash\n");
    dokimase_hash_function( hash );
}

void anazhthsh()
{
    struct product_data * pd;
    code_string code;
    char buf[BUFFER_LENGTH];
    int k;

    if (my_hash == NULL)
    {
        printf("Den exete fortosei to arxeio1!!!\n");
        return;
    }
    printf("Kwdikos? ");
    diabase_keimeno(buf, sizeof(buf));
    if (strlen(buf) != 15)
    {
        printf("Parakalw eisagete 15 xarakthrwn kwdiko.\n");
        return;
    }
    strcpy(code, buf);
    pd = get_hash_table(code);
    if (pd == NULL)
    {
        printf("De brethike eggrafh me kwdiko %s\n", code);
        return;
    }
    printf("Dokimh anakthshs. kwdikos: %s\n", code);
    while (pd != NULL)
    {
        printf("Hmera: %d, Proionta:", pd->day_of_week);
        for (k=0; k < pd->p_list.length; k++)
            printf("%s,%d;", pd->p_list.products[k].pcode, pd->p_list.products[k].quant);
        printf("\n");
        pd = pd->next;
    }
}

/* Analyei mia symboloseira poy exei dedomena apo to kentriko arxeio kai
 * epistrefei se mia domh thn epithymhth morfh toys (int, ...). */
struct product_data analyze(char * string)
{
    struct product_data result;
    char *str;
    char *c;
    int i;

    result.p_list.length = 0;
    result.p_list.products = NULL;
    result.next = NULL;
    /* Hmera ebdomadas. */
    str = strtok(string, " ");//to format einai(1...7) ΒΓΔΕ0134Α256789P1,2;P2,4; …
    result.day_of_week = atoi(str);
    /* kwdikos kartas */
    str = strtok(NULL, " ");
    strcpy(result.code, str);
    /*char *strtok( char *s1, const char *s2);Η πρώτη κλήση της strtok 
    περιέχει το s1 ως το πρώτο όρισμα, και διαδοχικές κλήσεις για τον κατακερματισμό του ίδιου 
    αλφαριθμητικού περιλαμβάνουν το NULL ως το πρώτο όρισμα. Με κάθε κλήση επιστρέφεται ένας
     δείκτης στο τρέχον κομμάτι (token). Όταν δεν υπάρχουν πλέον περισσότερα κομμάτια (tokens)
      όταν καλείται η συνάρτηση, επιστρέφεται NULL*/
    
    /* Lista agorasmenwn proiontwn */
    str = strtok(NULL, " ");
    /* An den exei tipota eimaste OK */
    if (str == NULL || strlen(str) == 0)
        return result;
    /* Alliws prepei na doyme posa diaforetika proionta dhlwnontai
     * Metrame ton arithmo apo ';' poy emfanizontai sto trexon str
     * kai to swzoyme sto p_list.length */
    c = str;
    while(*c != '\0')
    {
        if (*c == ';')
            result.p_list.length++;
        c++;
    }
    /* Desmeyoyme xwro gia ta proionta (kwdikos, posothta) */
    result.p_list.products = calloc(1, sizeof(struct product) * result.p_list.length);
    die_if (result.p_list.products == NULL, "Den exoyme mnhmh!");
    /* Edw to str deixei se keimeno morfhs: 'P12,3;P44,7;...'
     * Spame to str me bash ta ; me xrhsh ths strtok */
    str = strtok(str, ";");
    i = 0;
    /* Oso h strtok den exei epistrepsei ola ta kommatia, ... */
    while (str != NULL)
    {
        /* Den mporoyme na xrhsimopohsoyme thn strtok giati tha akyrwsoyme
         * thn prohgoymenh klhsh, epomenos prepei na xrhsimopoihsoyme aplh
         * anazhthsh. */
        /* Proxwrame to c mexri to xarakthra ',' */
        c = str;
        while(*c != ',')
            c++;
        /* Antigrafoyme ta byte toy kwdikoy, kai topothetoyme to '\0' gia na
         * termatisei to alfarithmitiko toy kwdikoy proiontos. */
        memcpy(result.p_list.products[i].pcode, str, c-str);
        result.p_list.products[i].pcode[c-str] = '\0';
        /* Proxwrame to c na deixnei sto xarakthra meta to , */
        c++;
        /* Metatrepoyme se akeraio ayto to kommati (einai h posothta) */
        result.p_list.products[i].quant = atoi(c);
        /* Zhtame apo thn strtok to epomeno kommati me kwdio,posothta */
        str = strtok(NULL, ";");
        /* Ayksanoyme to deikth ston pinaka proiontwn ths agoras */
        i++;
    }
    return result;
}

/* Arxikopoiei mia domh poy anaparista pinaka apo kwdikoys, me bash
 * to zhtoymeno plithos kwdikwn */
struct code_vector * init_code_vector(int num_codes)
{
    struct code_vector * cl_ptr;

    cl_ptr = malloc(sizeof(struct code_vector));
    die_if(cl_ptr == NULL, "Den exei mnhmh!");
    cl_ptr->length = 0;
    cl_ptr->codes = malloc(sizeof(code_string)*num_codes);
    die_if(cl_ptr->codes == NULL, "Den exei mnhmh!");
    return cl_ptr;
}

/* Apeleytheronei th mnhmh ths domhs poy epistrefei h init_code_vector */
void free_code_vector(struct code_vector * cl_ptr)
{
    free(cl_ptr->codes);
    free(cl_ptr);
}

/* Prosartei ena kwdiko se mia domh struct code_vector */
void append_code(struct code_vector * cl_ptr, char * code)
{
    cl_ptr->length++;
    strcpy(cl_ptr->codes[cl_ptr->length - 1], code);
}

/* Boithitikh synarthsh sygkrishs gia klhsh ths qsort */
int codecmp(const void * p1, const void * p2)
{
    return strcmp( (const char *)p2, (const char *)p1);
}

/* Ypologismos twn monadikwn kwdikwn se mia domh code_vector */
int find_unique_codes(struct code_vector * cl_ptr)
{
    int i;
    int num_unique = 0;
    /* Kanoyme taksinomhsh sth lista twn kwdikwn */
    qsort(cl_ptr->codes, cl_ptr->length, sizeof(code_string), codecmp);
    /* Elegxoyme apo 0 ews N-1 an enas kwdikos X[i] me ton X[i+1] einai
     * diaforetikoi, kai oso einai diaforetikoi ayksanoyme to num_unique, alliws
     * paraleipoyme tis epanalipseis. */
    for (i=0; i<cl_ptr->length-1; i++)
    {
        num_unique++;
        while( (i < cl_ptr->length-1) && (strcmp(cl_ptr->codes[i], cl_ptr->codes[i+1]) == 0) )
            i++;
    }
    /* Diorthonoyme th metrhsh gia toys kwdikoys N-1, N */
    if (strcmp(cl_ptr->codes[i], cl_ptr->codes[i+1]) != 0)
        num_unique++;
    return num_unique;
}

/* Termatizei to programma an to condition einai True, typwnontas to logo 'reason' */
void die_if(int condition, char * reason)
{
    if (condition)
    {
        printf("%s\n", reason);
        exit(1);
    }
}

/* Elegxei an to x einai prwtos kai an einai epistrefei 1, alliws 0 */
int is_prime(int x)
{
    int i;
    if (x == 2) return 1;
    for (i=3; i<x/2; i+=2)
        if ((x % i) == 0)
            return 0;
    return 1;
}

/* Ypologizei to megethos toy pinaka katakermatismoy symfwna me to zhtoymeno */
int	compute_hash_length(int unique)
{
    int N = 2*unique + 1;
    while (!is_prime(N))
        N += 2;
    return N;
}

/* Arxikopoiei to hash table mas, na exei hashlen xwrhtikothta */
struct hash_table * init_hash_table(int hashlen)
{
    struct hash_table * result;

    result = calloc(1, sizeof(struct hash_table));
    result->length = hashlen;
    result->p_data = calloc(hashlen, sizeof(struct product_data));

    return result;
}

/* Apodesmeyei ton pinaka katakermatismoy */
void free_hash_table(struct hash_table * ht)
{
    int i;

    if (ht == NULL)
        return;
    /* Apodesmeyoyme tis listes proiontwn an einai desmeymenes */
    for (i=0; i<ht->length; i++)
        if (ht->p_data[i].p_list.products != NULL)
            free(ht->p_data[i].p_list.products);
    free(ht->p_data);
    free(ht);
}

/*
 * djb2
 *
 * this algorithm (k=33) was first reported by dan bernstein many years
 * ago in comp.lang.c. another version of this algorithm (now favored by bernstein)
 * uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; the magic of number 33
 * (why it works better than many other constants, prime or not) has never been adequately explained.
 */

unsigned hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % my_hash->length;
}

/*
 * 32 bit magic FNV-0 and FNV-1 prime
 */
#define FNV_32_PRIME ((unsigned int)0x01000193)

unsigned fnv_32_hash(const char *buf)
{
    unsigned char *bp = (unsigned char *)buf;	/* start of buffer */
    unsigned hval = 0;
    /*
     * FNV-1 hash each octet in the buffer
     */
    while (*bp++ != '\0')
    {
        /* multiply by the 32 bit FNV magic prime mod 2^32 */
        hval *= FNV_32_PRIME;
        hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
        /* xor the bottom with the current octet */
        hval ^= (unsigned int)*bp++;
    }
    /* return our new hash value */
    return hval % my_hash->length;
}


/* Hash function */
unsigned hash_func(const char *s)
{

    unsigned hashval;

    for (hashval=0; *s!='\0'; s++)
    {
        hashval = *s + 31*hashval;
    }

    return hashval % my_hash->length;

}

void list_append(struct product_data * head, struct product_data * data_ptr)
{
    struct product_data * pd_ptr;

    pd_ptr = head;
    while (pd_ptr->next != NULL)
        pd_ptr = pd_ptr->next;
    pd_ptr->next = calloc(1, sizeof(struct product_data));
    *(pd_ptr->next) = *data_ptr;
}

void put_hash_table(code_string code, struct product_data data)
{
    int index;
    if (my_hash == NULL)
        return;
    /* Ypologizoyme poy prepei na mpoyn ta data */
    index = hash_func(code);
    /* Einai o kwdikos sto hash_table[index] idios me ton dedomeno? */
    if (strcmp(code, my_hash->p_data[index].code) == 0)
    {
        list_append(&my_hash->p_data[index], &data);
    }
    else
    {
        /* Exoyme xwro gia na mpoyn ta data? */
        if (my_hash->total_records == my_hash->length)
        {
            printf("Prosoxh o pinakas katakermatismoy mas gemise!!!\n");
            return;
        }
        /* Bres me linear probing adeia thesh.
         * Oso o apothikeymenos kwdikos den einai to keno string,
         * aykshse to index kai an kseperasei to my_hash->length,
         * pame pali apo to 0.
         */
        while (strlen(my_hash->p_data[index].code) != 0)
        {
            index = (index + 1) % my_hash->length;
            if (strcmp(my_hash->p_data[index].code, code) == 0)
            {
                list_append(&my_hash->p_data[index], &data);
                return;
            }
        }
        my_hash->p_data[index] = data;
        my_hash->total_records++;
    }
}

struct product_data * get_hash_table(code_string code)
{
    int start_index, index;
    if (my_hash == NULL)
        return NULL;
    /* Ypologizoyme poy prepei na briskontai ta data kai gia na apofygoume thn
     * atermonh epanalhpsh an to code den einai syndedemeno me kapoia eggrafh,
     * prepei na thymomaste to start_index giati tote o parakatw broxos kapoia
     * stigmh tha to ksanaftasei. Tote omws kseroyme oti to code den yparxei,
     * epomenws epistrefoyme NULL. */
    start_index = hash_func(code);
    index = start_index;
    while (strcmp(my_hash->p_data[index].code, code) != 0)
    {
        index = (index + 1) % my_hash->length;
        if (index == start_index)
            return NULL;
    }
    return &my_hash->p_data[index];
}

double get_product_factor(product_code_string pcode)
{
    int i,k;

    for (k=0; k<team_vector.length; k++)
    {
        for (i=0; i<team_vector.data[k].pcv.length; i++)
            if (strcmp(pcode, team_vector.data[k].pcv.codes[i]) == 0)
                return team_vector.data[k].factor;
    }
    return 0.5;
}

double get_product_price(product_code_string pcode, int day)
{
    int idx;
    /* Yparxei eggrafh me pcode? */
    for (idx=0; idx<price_vector.length; idx++)
        if (strcmp(pcode, price_vector.data[idx].pcode) == 0)
            break;
    if (idx < price_vector.length)
        return price_vector.data[idx].price[day];
    return 10.0;
}

struct price_data analyze_price(char * string)
{
    struct price_data result = {"", {0}};
    char * str;
    double price;
    int day;

    str = strtok(string, "\t");
    strcpy(result.pcode, str);
    str = strtok(NULL, "\t");
    str = strtok(str, " ");
    price = atof(str);
    str = strtok(NULL, " ");
    while (str != NULL)
    {
        day = atoi(str);
        result.price[day] = price;
        str = strtok(NULL, " ");
    }
    return result;
}

void price_vector_add(struct price_data pd)
{
    int idx, day;
    /* Yparxei eggrafh me pd.pcode? */
    for (idx=0; idx<price_vector.length; idx++)
        if (strcmp(pd.pcode, price_vector.data[idx].pcode) == 0)
            break;
    if (idx == price_vector.length)
    {
        price_vector.length++;
        price_vector.data = realloc(price_vector.data, sizeof(struct price_data) * price_vector.length);
        price_vector.data[price_vector.length-1] = pd;
    }
    else
    {
        for (day=1; day<=7; day++)
            if (pd.price[day] != 0)
                price_vector.data[idx].price[day] = pd.price[day];
    }
}
