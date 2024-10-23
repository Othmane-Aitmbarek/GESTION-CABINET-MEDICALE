#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structures

typedef struct client
{
    char *nom;
    char *adresse;
    int age;
    int Phone;
}client;

typedef struct Doctor
{
    char *nom;
    char *speciality;
    int start_hour;
    int end_hour;
}Doctor;

typedef struct paiement
{
    int date[3];
    char *doc;
    char *patient;
    float montant;
    char *service;
}paiement;

typedef struct rendez_vous
{
    int date[3];
    int hour;
    char *doc;
    char *patient;
}rendez_vous;

//Nodes

typedef struct NodeClient
{
    client CL;
    struct NodeClient *next;
    struct NodeClient *prev;

}NodeClient;



typedef struct NodeDoctor
{
    Doctor Doc;
    struct NodeDoctor *next;
    struct NodeDoctor *prev;
    struct NodeRDV *RDV;
}NodeDoctor;


typedef struct NodeRDV
{
    rendez_vous RDV;
    struct NodeRDV *next;
    struct NodeRDV *prev;
}NodeRDV;

typedef struct NodePaiement
{
    paiement PAY;
    struct NodePaiement *next;
    struct NodePaiement *prev;
}NodePaiement;

//function regarging reading string values
char *getString()
{
    fflush(stdin);
    char *string = malloc(100*sizeof(char));
    gets(string);
    return string;
}

//fonctions regarding adding new client , new doctor , new paiement and new rendez vous

NodeClient *newClient(client CL)
{
    NodeClient *tmp = (NodeClient*)malloc(sizeof(NodeClient));
    tmp->CL.nom = tmp->CL.adresse = malloc(100*sizeof(char));
    tmp->CL.nom = CL.nom;
    tmp->CL.adresse = CL.adresse;
    tmp->CL.age = CL.age;
    tmp->CL.Phone = CL.Phone;
    tmp->prev = NULL;
    return tmp;
}

NodeDoctor *newDoctor(Doctor DR)
{
    NodeDoctor *tmp = (NodeDoctor*)malloc(sizeof(NodeDoctor));
    tmp->Doc.nom = DR.nom;
    tmp->Doc.speciality = DR.speciality;
    tmp->Doc.start_hour = DR.start_hour;
    tmp->Doc.end_hour = DR.end_hour;
    tmp->prev = NULL;
    tmp->RDV = NULL;
    return tmp;
}

NodeRDV *newRDV(rendez_vous RDV)
{
    NodeRDV *tmp = (NodeRDV*)malloc(sizeof(NodeRDV));
    tmp->RDV.date[0] = RDV.date[0];
    tmp->RDV.date[1] = RDV.date[1];
    tmp->RDV.date[2] = RDV.date[2];
    tmp->RDV.hour = RDV.hour;
    tmp->RDV.doc = RDV.doc;
    tmp->RDV.patient = RDV.patient;
    tmp->prev = NULL;
    return tmp;
}

NodePaiement *newPAY(paiement PAY)
{
    NodePaiement *tmp = (NodePaiement*)malloc(sizeof(NodePaiement));
    tmp->PAY.date[0] = PAY.date[0];
    tmp->PAY.date[1] = PAY.date[1];
    tmp->PAY.date[2] = PAY.date[2];
    tmp->PAY.doc = PAY.doc;
    tmp->PAY.patient = PAY.patient;
    tmp->PAY.service = PAY.service;
    tmp->PAY.montant = PAY.montant;
    tmp->prev = NULL;
    return tmp;
}

// functions regarding the management of clients

NodeClient *insert_client(NodeClient *head, client CL)
{
    NodeClient *tmp = newClient(CL);
    if (head != NULL) {
        head->prev = tmp;
    }
    tmp->next = head;
    head = tmp;
    return head;
}

NodeClient *delete_client(NodeClient *head , NodeClient*client)
{
    if(head==client)
    {
        NodeClient *tmp = client->next;
        head = tmp;
        free(client);
        client=NULL;
        return head;
    }
    NodeClient *prev = client->prev;
    prev->next = client->next;
    if(client->next != NULL)
        client->next->prev = prev;
    free(client);
    client = NULL;
    printf("client a ete supprime\n");
    return head;
}



NodeClient *search_client_nom(NodeClient *head , char *name)
{
    if(head == NULL)
        return NULL;
    if(strcmp(head->CL.nom , name)==0)
        return head;
    return search_client_nom(head ->next, name);
}

NodeClient *search_client_number(NodeClient *head , int number)
{
    if(head == NULL)
        return NULL;
    if(head->CL.Phone == number)
        return head;
    return search_client_number(head->next , number);

}



NodeClient *modify_client(NodeClient *head , NodeClient *client , int mod)
{
    if(mod==1)
    {
        char *newName;
        printf("saisir le nouveau nom du client :");
        newName = getString();
        strcpy(client->CL.nom , newName);
        return head;
    }
    if(mod==2) {
        char *newAdress;
        printf("saisir la nouvelle adresse du client :");
        newAdress = getString();
        strcpy(client->CL.adresse , newAdress);
        return head;
    }
    if(mod==3)
    {
        int age;
        printf("saisir l'age du client:");
        scanf("%d",&age);
        client->CL.age = age;
        return head;
    }
    int phone;
    printf("saisir le numero de telephone nouveau du client:");
    scanf("%d",&phone);
    client->CL.Phone = phone;
    return head;
}

void afficher_client(NodeClient *head)
{
    if(head == NULL)
    {

        return;
    }

    printf("le nom : %s\n" ,head->CL.nom);
    printf("l'adresse : %s\n" , head->CL.adresse);
    printf("l'age : %d\n",head->CL.age);
    printf("telephone : %d\n",head->CL.Phone);
    printf("\n");
    afficher_client(head->next);
}

// functions regarding the management of doctors

NodeDoctor *insert_doctor(NodeDoctor *head , Doctor DR)
{
    NodeDoctor *tmp = newDoctor(DR);
    if(head!=NULL)
    {
        head->prev = tmp;
    }
    tmp->next = head;
    head = tmp;
    return head;
}

NodeDoctor *search_doctor(NodeDoctor *head , char *nom)
{
    if(head==NULL)
        return NULL;
    if(strcmp(head->Doc.nom , nom)==0)
    {
        return head;
    }
    return search_doctor(head->next , nom);
}


NodeDoctor *delete_doctor(NodeDoctor *head,NodeDoctor *doctor)
{
    if(head==doctor)
    {

        NodeDoctor *tmp = doctor->next;
        head = tmp;
        free(doctor);
        doctor=NULL;
        return head;
    }
    NodeDoctor *prev = doctor->prev;
    prev->next = doctor->next;
    if(doctor->next != NULL)
        doctor->next->prev = prev;
    free(doctor);
    doctor = NULL;
    printf("docteur a ete supprime\n");
    return head;
}

NodeDoctor *modify_doctor(NodeDoctor *head, NodeDoctor *doctor, int mod)
{
    if(mod==1){
        char *newName;
        printf("saisir le nouveau nom du docteur :");
        newName = getString();
        strcpy(doctor->Doc.nom , newName);
        return head;
    }
    if(mod==2){
        char *newSpeciality;
        newSpeciality = getString();
        strcpy(doctor->Doc.speciality , newSpeciality);
        return head;
    }
    if(mod==3){
        int SD;
        do{
            printf("saisir le nouveau horaire de depart :");
            scanf("%d",&SD);
            if(SD<9 || SD>22)
                printf("erreur , entrez un horaire entre 9H et 22H\n");
        }while(SD<9 || SD>22);
        doctor->Doc.start_hour = SD;
        return head;
    }
    int SE;
    do{
        printf("saisir le nouveau horaire de fin :");
        scanf("%d",&SE);
        if(SE<9 || SE>22)
            printf("erreur , entrez un horaire entre 9H et 22H\n");
    }while(SE<9 || SE>22);
    doctor->Doc.end_hour = SE;
    return head;
}


void afficher_doctor(NodeDoctor *head)
{
    if(head == NULL)
    {
        return;
    }

    printf("le nom : DR. %s\n" ,head->Doc.nom);
    printf("l'adresse : %s\n" , head->Doc.speciality);
    printf("l'heure depart : %dH\n",head->Doc.start_hour);
    printf("l'heure fin : %dH\n",head->Doc.end_hour);
    printf("\n");
    afficher_doctor(head->next);
}
// functions regarding the managements of appointments

void insert_RDV_beg(NodeRDV **head  , rendez_vous RDV)
{
    NodeRDV *tmp = newRDV(RDV);
    if(*head!=NULL)
    {
        (*head)->prev = tmp;
    }
    tmp->next = *head;
    tmp->prev = NULL;
    *head = tmp;
}

void insert_RDV_end(NodeRDV **head , rendez_vous RDV)
{
    NodeRDV *tmp = newRDV(RDV);
    NodeRDV *p = *head;
    while(p->next != NULL)
        p = p->next;
    tmp->prev = p;
    tmp->next = NULL;
    p->next = tmp;
}

void insert_RDV_mid(NodeRDV **head ,NodeRDV *left  , NodeRDV *right , rendez_vous RDV)
{
    NodeRDV *tmp = newRDV(RDV);
    tmp->next = right;
    tmp->prev = left;
    left->next = tmp;
    right->prev = tmp;
}

void enfiler(NodeRDV **head , rendez_vous RDV)
{
    if(*head==NULL || CompareDateAndTime((*head)->RDV , RDV)==1)
        insert_RDV_beg(head , RDV);
     else {
        NodeRDV *tmp = *head;
        while(tmp != NULL && CompareDateAndTime(tmp->RDV , RDV)!=1)
        {
            tmp = tmp->next;
        }
        if(tmp==NULL)
            insert_RDV_end(head , RDV);
        else
            insert_RDV_mid(head , tmp->prev , tmp , RDV);
    }
}

void defiler(NodeRDV **head)
{
    if (*head == NULL)
        return;
    NodeRDV *tmp = *head;
    *head = tmp->next;
    if (*head != NULL)
        (*head)->prev = NULL;
    free(tmp);
    tmp = NULL;
}


NodeRDV *annuler(NodeRDV *head , NodeRDV *RDV)
{   if(head == RDV)
        defiler(head);
    else
    {
            NodeRDV *left = RDV->prev;
    left->next = RDV->next;
    if(RDV->next != NULL)
        RDV->next->prev = left;
    free(RDV);
    RDV = NULL;
    return head;
    }

}

int CompareDateAndTime(rendez_vous NODE , rendez_vous RDV)
{
    if(RDV.date[2] < NODE.date[2])
        return 1;
    else if(RDV.date[2]== NODE.date[2])
        if(RDV.date[1] < NODE.date[1])
            return 1;
        else if(RDV.date[1] == NODE.date[1])
            if(RDV.date[0] < NODE.date[0])
                return 1;
            else if(RDV.date[0] == NODE.date[0])
                if(RDV.hour < NODE.hour)
                    return 1;
    return 0;
}

NodeRDV *modify_RDV(NodeRDV *head , NodeRDV *RDV ,NodeDoctor *Doc,int mod)
{
    if(mod==1){
        int jour,mois,annee;
        printf("saisir une nouvelle date :\n");
        printf("jour :");
        scanf("%d" ,&jour);
        printf("mois : ");
        scanf("%d",&mois);
        printf("annee : ");
        scanf("%d",&annee);
        RDV->RDV.date[0] = jour;
        RDV->RDV.date[1] = mois;
        RDV->RDV.date[2] = annee;
        return head;
    }
    int hour;
    do {
            printf("saisir l'heure de rendez vous :");
            scanf("%d" , &hour);
            if(hour > Doc->Doc.end_hour || hour < Doc->Doc.start_hour)
            {
                printf("erreur !!  saisir une heure correspondant a l'horaire du docteur %s\n",Doc->Doc.nom);
            }
    }while(hour > Doc->Doc.end_hour || hour < Doc->Doc.start_hour);
    RDV->RDV.hour = hour;
    return head;
}

NodeRDV *search_RDV(NodeRDV *DocRDV , char *nom)
{
    if(DocRDV == NULL)
        return NULL;
    if(strcmp(DocRDV->RDV.patient , nom) == 0)
        return DocRDV;
    return search_RDV(DocRDV->next , nom);
}

void afficher_RDV(NodeRDV *head) {
    NodeRDV *tmp = head;
    while (tmp != NULL) {
        printf("docteur : %s\n", tmp->RDV.doc);
        printf("Patient : %s\n", tmp->RDV.patient);
        printf("Date : %d/%d/%d\n", tmp->RDV.date[0], tmp->RDV.date[1], tmp->RDV.date[2]);
        printf("L'heure : %dH\n", tmp->RDV.hour);
        printf("\n");
        tmp = tmp->next;
    }
}


NodeRDV *merge(NodeRDV *first, NodeRDV *second) {
    if (!first) return second;
    if (!second) return first;
    if (CompareDateAndTime(first->RDV , second->RDV)==0) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    } else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
NodeRDV *split(NodeRDV *head) {
    NodeRDV *fast = head, *slow = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    NodeRDV *temp = slow->next;
    slow->next = NULL;
    return temp;
}

void mergeSort(NodeRDV **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    NodeRDV *second = split(*head);
    mergeSort(head);
    mergeSort(&second);
    *head = merge(*head, second);
}



//functions regarding the management of payments

NodePaiement *insert_paiement(NodePaiement *head , paiement PAY)
{
    NodePaiement *tmp = newPAY(PAY);
    if(head != NULL)
        head->prev = tmp;
    tmp->next = head;
    head = tmp;
    return head;
}

void afficher_paiement(NodePaiement *head)
{
    if(head == NULL)
        return;
    printf("patient : %s\n",head->PAY.patient);
    printf("docteur : %s\n",head->PAY.doc);
    printf("date du paiement : %d/%d/%d\n",head->PAY.date[0] , head->PAY.date[1] , head->PAY.date[2]);
    printf("service : %s\n",head->PAY.service);
    printf("montant : %.2f DH\n",head->PAY.montant);
    afficher_paiement(head->next);
}

//programme main commence
int main()
{
    NodeRDV *RV;
    NodeClient *P = NULL;
    NodeClient *res;
    NodeDoctor *resDoc;
    NodeDoctor *D = NULL;
    NodePaiement *Pay = NULL;
    int choix;
    do {
        menu:
            printf("========================MENU=========================\n");
        printf("1-GESTION DES PATIENTS\n");
        printf("2-GESTION DES MEDECINES\n");
        printf("3-GESTION DES RENDEZ VOUS\n");
        printf("4-GESTION DES PAIEMENTS\n");
        printf("0-POUR QUITTER LE PROGRAMME\n");
        printf("\tchoix :");
        scanf("%d",&choix);
        switch(choix)
        {
        case 1:     M:
                    printf("========================PATIENTS=========================\n");
                    printf("1-AJOUTER UN PATIENT:\n");
                    printf("2-AFFICHER LES PATIENTS\n");
                    printf("3-RECHERCHER UN PATIENT\n");
                    printf("4-SUPPRIMER UN PATIENT\n");
                    printf("5-MODIFIER LES INFOS D'UN PATIENT\n");
                    printf("0-POUR REVENIR AU MENU\n");
                    int c;
                    printf("\tchoix :");
                    scanf("%d",&c);
                    if(c==1)
                    {
                      client C;

                      printf("nom :");
                      C.nom = getString();
                      res = search_client_nom(P , C.nom);
                      if(res!=NULL)
                         printf("le client deja existe !!\n");
                      else
                      {
                            printf("adresse :");
                            C.adresse = getString();
                            fflush(stdin);
                            printf("Age :");
                            scanf("%d",&C.age);
                            printf("Phone :");
                            scanf("%d",&C.Phone);
                            P = insert_client(P , C);
                      }
                    }
                    else if(c==2)
                        afficher_client(P);
                    else if(c==3)
                    {

                        int Choix_recherche;
                        printf("1-RECHERCHE PAR NOM \n");
                        printf("2-RECHERCHE PAR TELEPHONE\n");
                        printf("\t choix :");
                        scanf("%d",&Choix_recherche);
                        if(Choix_recherche==1)
                        {

                            char *nom;
                            printf("saisir le nom du client :");
                            nom = getString();
                            res = search_client_nom(P , nom);
                            if(res==NULL)
                                printf("client n'existe pas !!!\n");
                            else
                                printf("client existe!!\n");
                        }else {
                            int number;
                            scanf("%d",&number);
                            res = search_client_number(P , number);
                            printf("%p" , res);
                            if(res==NULL)
                                printf("client n'existe pas !!!\n");
                            else
                                printf("client existe!!\n");
                        }
                    }
                    else if(c==4)
                    {
                        char *nom;
                        printf("saisir le nom du client pour le supprimer :");
                        nom = getString();
                        res = search_client_nom(P , nom);
                        if(res==NULL)
                            printf("client n'existe pas pour supprimer!!\n");
                        else{
                            P=delete_client(P , res);
                        }


                    }
                    else if(c==5)
                    {
                        char *nom;
                        printf("saisir le nom du client pour le modifier:");
                        nom = getString();
                        res = res = search_client_nom(P , nom);
                        if(res==NULL)
                            printf("client n'existe pas !!\n");
                        else
                        {
                            int ch;
                            printf("1-POUR MODIFIER LE NOM\n");
                            printf("2-POUR MODIFIER L'ADRESSE\n");
                            printf("3-POUR MODIFIER L'AGE\n");
                            printf("4-POUR MODIFIER LE NOMBRE DE TELEPHONE\n");
                            printf("choix :");
                            scanf("%d",&ch);
                            P = modify_client(P , res , ch);
                        }
                    }
                    else if(c==0)
                        goto menu;
                    else
                        printf("s'il vous plet , saisir un nombre correspondant a la liste\n");
                    goto M;
                    break;
            case 2: D:
                    printf("==================================DOCTEURS=====================\n");
                    printf("1-AJOUTER UN DOCTEUR\n");
                    printf("2-AFFICHER LES DOCTEURS\n");
                    printf("3-RECHERCHER UN DOCTEUR\n");
                    printf("4-SUPPRIMER UN DOCTEUR\n");
                    printf("5-MODIFIER LES INFOS D'UN DOCTEUR\n");
                    printf("0-POUR REVENIR AU MENU\n");
                    int cd;
                    printf("\tchoix :");
                    scanf("%d",&cd);
                    if(cd==1)
                    {
                      Doctor DR;

                      printf("nom :");
                      DR.nom = getString();
                      printf("Specialite:");
                      DR.speciality = getString();
                      fflush(stdin);
                      do{
                        printf("heure debut :");
                        scanf("%d",&DR.start_hour);
                        if(DR.start_hour<9 || DR.start_hour>22)
                            printf("erreur , entrez un horaire entre 9H et 22H\n");
                      }while(DR.start_hour<9 || DR.start_hour>22);
                      do{
                            printf("heure fin :");
                            scanf("%d",&DR.end_hour);
                            if(DR.end_hour<9 || DR.end_hour>22)
                                printf("erreur , entrez un horaire entre 9H et 22H\n");
                      }while(DR.end_hour<9 || DR.end_hour>22);
                      D = insert_doctor(D ,DR);
                    }
                    else if(cd==2)
                        afficher_doctor(D);
                    else if(cd==3)
                    {
                            char *nom;
                            printf("saisir le nom du docteur :");
                            nom = getString();
                            resDoc = search_doctor(D , nom);
                            if(resDoc==NULL)
                                printf("docteur n'existe pas !!!\n");
                            else
                                printf("docteur existe!!\n");
                    }
                    else if(cd==4)
                    {
                        char *nom;
                        printf("saisir le nom du docteur pour le supprimer :");
                        nom = getString();
                        resDoc = search_doctor(D , nom);
                        if(resDoc==NULL)
                            printf("docteur n'existe pas pour supprimer!!\n");
                        else{
                            printf("supression en cours...\n");
                            D=delete_doctor(D , resDoc);
                        }


                    }
                    else if(cd==5)
                    {
                        char *nom;
                        printf("saisir le nom du docteur pour le modifier:");
                        nom = getString();
                        resDoc = search_doctor(D , nom);
                        if(resDoc==NULL)
                            printf("docteur n'existe pas !!\n");
                        else
                        {
                            int ch;
                            printf("1-POUR MODIFIER LE NOM\n");
                            printf("2-POUR MODIFIER LA SPECIALITE\n");
                            printf("3-POUR MODIFIER L'HEURE DE DEBUT\n");
                            printf("4-POUR MODIFIER L'HEURE DE FIN\n");
                            printf("choix :");
                            scanf("%d",&ch);
                            D = modify_doctor(D , res , ch);
                        }
                    }
                    else if(cd==0)
                        goto menu;
                    else
                        printf("s'il vous plet , saisir un nombre correspondant a la liste\n");
                    goto D;
                    break;
             case 3 : R:
                      printf("================================RENDEZ-VOUS==================\n");
                      printf("1-POUR AJOUTER UN RENDEZ-VOUS\n");
                      printf("2-POUR MODIFIER UN RENDEZ VOUS\n");
                      printf("3-POUR ANNULER UN RENDEZ VOUS\n");
                      printf("4-POUR AFFICHER LES RENDEZ-VOUS\n");
                      printf("0-POUR REVENIR AU MENU\n");
                      printf("\t choix: ");
                      int crv;
                      scanf("%d",&crv);
                      if(crv==1)
                      {
                            char *nom;
                            NodeRDV *resRDV;
                            printf("saisir le nom du docteur :");
                            nom = getString();
                            resDoc = search_doctor(D , nom);
                            if(resDoc==NULL)
                                printf("docteur n'existe pas!!!\n");
                            else{
                                rendez_vous RDV;
                                char *nomPat;
                                printf("saisir le nom du patient :");
                                nomPat = getString();
                                res = search_client_nom (P , nomPat);
                                resRDV = search_RDV(resDoc->RDV , nomPat);
                                if(res==NULL)
                                {
                                    printf("client n'existe pas !!\n");
                                }else if(resRDV != NULL)
                                    printf("client a deja un rendez vous \n");
                                else {
                                    RDV.patient = nomPat;
                                    RDV.doc = nom;

                                    printf("saisir le jour du rendez vous :");
                                    scanf("%d",&RDV.date[0]);
                                    printf("saisir le mois du rendez-vous :");
                                    scanf("%d",&RDV.date[1]);
                                    printf("saisir l'annee du rendez-vous :");
                                    scanf("%d",&RDV.date[2]);
                                do {
                                    printf("saisir l'heure du rendez-vous :");
                                    scanf("%d",&RDV.hour);
                                    if(RDV.hour < resDoc->Doc.start_hour ||
                                        RDV.hour > resDoc->Doc.end_hour)
                                        printf("saisir une heure correspondat
                                               a l'horaire du docteur %s\n",
                                               resDoc->Doc.nom);
                                }while(RDV.hour < resDoc->Doc.start_hour ||
                                       RDV.hour > resDoc->Doc.end_hour);
                                     enfiler(&(resDoc->RDV) ,RDV);
                                }
                            }
                      }
                      else if(crv==2)
                      {
                            char *nomDoc;
                            char *nomPat;
                            printf("saisir le nom du docteur :");
                            nomDoc = getString();
                            resDoc = search_doctor(D , nomDoc);
                            if(resDoc == NULL)
                                printf("aucun docteur avec ce nom existe !!\n");
                            else {
                                printf("saisir le nom du client :");
                                nomPat = getString();
                                RV = search_RDV(resDoc->RDV , nomPat);
                                if(RV==NULL)
                                    printf("aucun patient existe avec ce nom\n");
                                else {
                                    printf("1-POUR MODIFIER LA DATE\n");
                                    printf("2-POUR MODIFIER L'HEURE\n");
                                    int mod;
                                    printf("\tchoix :");
                                    scanf("%d",&mod);
                                    resDoc->RDV = modify_RDV(resDoc->RDV , RV , resDoc , mod);
                                    mergeSort(&(resDoc->RDV));
                                }
                            }
                      }
                      else if(crv==3)
                      {
                          char *nomDoc;
                          char *nomPat;
                          printf("saisir le nom du docteur :");
                          nomDoc = getString();
                          resDoc = search_doctor(D , nomDoc);
                          if(resDoc == NULL)
                                printf("aucun docteur avec ce nom existe !!\n");
                          else {
                                printf("saisir le nom du client : ");
                                nomPat = getString();
                                RV = search_RDV(resDoc->RDV , nomPat);
                                if(RV==NULL)
                                    printf("aucun patient existe avec ce nom\n");
                                else {
                                    resDoc->RDV = annuler(resDoc->RDV, RV);
                                    //sorting function
                                }
                            }

                      }
                      else if(crv==4){
                        char *nomDoc;
                        printf("saisir le nom du docteur :");
                        nomDoc = getString();
                        resDoc = search_doctor(D , nomDoc);
                        if(resDoc==NULL)
                            printf("aucun docteur avec ce nom existe !! \n");
                        else {
                            if(resDoc->RDV == NULL)
                                printf("aucun rendez vous avec docteur %s\n",resDoc->Doc.nom);
                            else {
                                afficher_RDV(resDoc->RDV);
                            }
                        }
                      }

                      else if(crv==0)
                        goto menu;
                      else
                        printf("s'il vous plet , saisir un nombre correspondant a la liste\n");
                      goto R;
                      break;

             case 4:P:
                    printf("==========================PAIEMENT========================\n");
                    printf("1-POUR EFFECTUER UN PAIEMENT\n");
                    printf("2-POUR AFFICHER LES PAIEMENT\n");
                    printf("0-POUR REVENIR AU MENU PRINCIPAL\n");
                    int cp;
                    printf("\t choix : ");
                    scanf("%d",&cp);
                    if(cp==1) {
                          char *nomDoc;
                          char *nomPat;
                          printf("saisir le nom du docteur : ");
                          nomDoc = getString();
                          resDoc = search_doctor(D , nomDoc);
                          if(resDoc == NULL)
                             printf("aucun docteur avec ce nom existe !!\n");
                          else {
                             printf("saisir le nom du client : ");
                             nomPat = getString();
                             RV = search_RDV(resDoc->RDV , nomPat);
                             if(RV==NULL)
                                printf("aucun patient existe avec ce nom\n");
                              else {
                                if(RV == resDoc->RDV)
                                {
                                    paiement PAY;
                                    printf("saisir jour de paiement : ");
                                    scanf("%d",&PAY.date[0]);
                                    printf("saisir le mois de paiement : ");
                                    scanf("%d",&PAY.date[1]);
                                    printf("saisir l'annee de paiement : ");
                                    scanf("%d",&PAY.date[2]);
                                    printf("saisir le service du paiement : ");
                                    PAY.service = getString();
                                    printf("saisir le montant du paiement : ");
                                    scanf("%f",&PAY.montant);
                                    PAY.doc = resDoc->Doc.nom;
                                    PAY.patient = RV->RDV.patient;
                                    Pay = insert_paiement(Pay,PAY);
                                    defiler(&(resDoc->RDV));
                                }else{
                                    printf("vous avez encore un rendez vous !!\n");
                              }
                            }
                          }
                    }
                    else if(cp == 2)
                        afficher_paiement(Pay);
                    else if(cp==0)
                        goto menu;
                    else
                        printf("s'il vous plet , saisir un nombre correspondant a la liste\n");
                    goto P;
                    break;
        }
    }while(choix!=0);
    return 0;
}
