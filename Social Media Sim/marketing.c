

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3// A small graph
#endif

typedef struct user_struct {
    char name[MAX_STR_LEN];
    struct friend_node_struct *friends;
    struct brand_node_struct *brands;
    bool visited;
} User;

typedef struct friend_node_struct {
    User *user;
    struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct {
    char brand_name[MAX_STR_LEN];
    struct brand_node_struct *next;
} BrandNode;

// Note: These are global variables.
FriendNode *allUsers = NULL;
int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];



bool in_friend_list(FriendNode *head, User *node) {
    if(node == NULL) return false; 
    for (FriendNode *cur = head; cur != NULL; cur = cur->next) {
            if (strcmp(cur->user->name, node->name) == 0) {
            return true;
        }
    }
    return false;
}


bool in_brand_list(BrandNode *head, char *name) {
    for (BrandNode *cur = head; cur != NULL; cur = cur->next) {
        if (strcmp(cur->brand_name, name) == 0) {
            return true;
        }
    }
    return false;
}


FriendNode *insert_into_friend_list(FriendNode *head, User *node) {
    if (node == NULL) return head;

    if (in_friend_list(head, node)) {
        printf("User already in list\n");
        return head;
    }

    FriendNode *fn = calloc(1, sizeof(FriendNode));
    fn->user = node;
    fn->next = NULL;

    if (head == NULL) return fn;

    if (strcmp(head->user->name, node->name) > 0) {
        fn->next = head;
        return fn;
    }

    FriendNode *cur;
    for (cur = head;
         cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
         cur = cur->next)
        ;

    fn->next = cur->next;
    cur->next = fn;

    return head;
}


BrandNode *insert_into_brand_list(BrandNode *head, char *node) {
    if (node == NULL) return head;

    if (in_brand_list(head, node)) {
        printf("Brand already in list\n");
        return head;
    }

    BrandNode *fn = calloc(1, sizeof(BrandNode));
    strcpy(fn->brand_name, node);
    fn->next = NULL;

    if (head == NULL) return fn;

    if (strcmp(head->brand_name, node) > 0) {
        fn->next = head;
        return fn;
    }

    BrandNode *cur;
    for (cur = head;
         cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
         cur = cur->next)
        ;

    fn->next = cur->next;
    cur->next = fn;

    return head;
}


FriendNode *delete_from_friend_list(FriendNode *head, User *node) {
    if (node == NULL) return head;

    if (!in_friend_list(head, node)) {
        printf("User not in list\n");
        return head;
    }

    if (strcmp(head->user->name, node->name) == 0) {
        FriendNode *temp = head->next;
        free(head);
        return temp;
    }

    FriendNode *cur;
    for (cur = head; cur->next->user != node; cur = cur->next)
        ;

    FriendNode *temp = cur->next;
    cur->next = temp->next;
    free(temp);

    return head;
}


BrandNode *delete_from_brand_list(BrandNode *head, char *node) {
    if (node == NULL) return head;

    if (!in_brand_list(head, node)) {
        printf("Brand not in list\n");
        return head;
    }

    if (strcmp(head->brand_name, node) == 0) {
        BrandNode *temp = head->next;
        free(head);
        return temp;
    }

    BrandNode *cur;
    for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
        ;

    BrandNode *temp = cur->next;
    cur->next = temp->next;
    free(temp);

    return head;
}


void print_user_data(User *user) {
    printf("User name: %s\n", user->name);

    printf("Friends:\n");
    for (FriendNode *f = user->friends; f != NULL; f = f->next) {
        printf("   %s\n", f->user->name);
    }

    printf("Brands:\n");
    for (BrandNode *b = user->brands; b != NULL; b = b->next) {
        printf("   %s\n", b->brand_name);
    }
}

int get_brand_index(char *name) {
    for (int i = 0; i < MAT_SIZE; i++) {
        if (strcmp(brand_names[i], name) == 0) {
            return i;
        }
    }

    printf("Brand '%s' not found\n", name);
    return -1;  // Not found
}


void print_brand_data(char *brand_name) {
    int idx = get_brand_index(brand_name);
    if (idx < 0) {
        printf("Brand '%s' not in the list.\n", brand_name);
        return;
    }

    printf("Brand name: %s\n", brand_name);
    printf("Brand idx: %d\n", idx);

    printf("Similar brands:\n");
    for (int i = 0; i < MAT_SIZE; i++) {
        if (brand_adjacency_matrix[idx][i] == 1 &&
            strcmp(brand_names[i], "") != 0) {
            printf("   %s\n", brand_names[i]);
        }
    }
}


void populate_brand_matrix(char *file_name) {
    // Read the file
    char buff[MAX_STR_LEN];
    FILE *f = fopen(file_name, "r");
    fscanf(f, "%s", buff);
    char *line = buff;
    // Load up the brand_names matrix
    for (int i = 0; i < MAT_SIZE; i++) {
        if (i == MAT_SIZE - 1) {
            strcpy(brand_names[i], line);
            break;
        }
        int index = strchr(line, ',') - line;
        strncpy(brand_names[i], line, index);
        line = strchr(line, ',') + sizeof(char);
    }
    // Load up the brand_adjacency_matrix
    for (int x = 0; x < MAT_SIZE; x++) {
        fscanf(f, "%s", buff);
        for (int y = 0; y < MAT_SIZE; y++) {
            int value = (int)buff[y * 2];
            if (value == 48) {
                value = 0;
            } else {
                value = 1;
            }
            brand_adjacency_matrix[x][y] = value;
        }
    }
}


User *create_user(char *name) {
    if(name == NULL){
        return NULL; 
    }
    User* new_user = (User*)malloc(sizeof(User)); 
    if(new_user== NULL) return NULL;
    strcpy(new_user->name, name);
    new_user -> friends = NULL;
    new_user -> brands = NULL;
    if(in_friend_list(allUsers, new_user)){
        free(new_user); 
        return NULL; 
    } 
        allUsers = insert_into_friend_list(allUsers, new_user);
        return new_user; 
}


BrandNode* delete_brands(BrandNode* head){
    if (head == NULL) return NULL; 
    if(head->next == NULL){
        BrandNode* temp = head;
        free(temp);
        head = NULL; ;
        return head;
    }
    BrandNode* p = head;
    BrandNode* q = head->next; 
    while(p != NULL){
        q = q->next;
        free(p);
        p = q; 
    }
    return head; 
}
FriendNode* delete_friends(FriendNode* head){
    if (head == NULL) return NULL; 
    if(head->next == NULL){
        FriendNode* temp = head;
        free(temp);
        head = NULL; 
        return head;
    }
    FriendNode* p = head;
    FriendNode* q = head->next; 
    while(p != NULL){
        q = q->next;;
        free(p);
        p = q;
    }
    return head; 
}


int delete_user(User *user) {
    if (user == NULL|| allUsers == NULL ||!in_friend_list(allUsers, user))
         return -1;
    FriendNode* p = allUsers;
    while(p != NULL){
       p->user->friends = delete_from_friend_list(p->user->friends, user);
       p = p->next; 
    }
    allUsers = delete_from_friend_list(allUsers, user); 
    delete_friends(user->friends);
    delete_brands(user->brands);
    free(user); 
    return 0; 
 
}

bool is_valid_friend(char* user){
   FriendNode* check = allUsers; 
   while(check != NULL){
        if(strcmp(check->user->name, user) == 0){
            return true; 
        }
        check = check -> next;  
   }
   return false; 
}


int add_friend(User *user, User *friend) {
    if (user == NULL || friend == NULL||in_friend_list(user->friends, friend) || !(is_valid_friend(user->name)) || !(is_valid_friend(friend->name))) return -1; 
    user->friends = insert_into_friend_list(user->friends, friend); 
    friend->friends = insert_into_friend_list(friend->friends, user); 
    return 0;  
}


int remove_friend(User *user, User *friend) {
    if (user == NULL || friend == NULL|| !(is_valid_friend(user->name)) || !(is_valid_friend(friend->name))) return -1; 
    if(in_friend_list(user->friends, friend)){
        user->friends = delete_from_friend_list(user-> friends, friend);
        friend->friends = delete_from_friend_list(friend->friends, user); 
        return 0; 
    }
    return -1;
}

bool is_valid_brand(char* brand_name){
    for(int i = 0; i < MAT_SIZE; i++){
        if(strcmp(brand_name, brand_names[i]) == 0){
            return true; 
        }
    }
    return false; 
}


int follow_brand(User *user, char *brand_name) {
    if(user == NULL || brand_name == NULL|| in_brand_list(user -> brands, brand_name)|| !is_valid_brand(brand_name)|| !is_valid_friend(user->name)) return -1;
    user ->brands = insert_into_brand_list(user->brands, brand_name);
    return 0; 
}


int unfollow_brand(User *user, char *brand_name) {
    if(user == NULL || brand_name == NULL ||!is_valid_friend(user->name)||!is_valid_brand(brand_name)) return -1; 
    if(in_brand_list(user->brands, brand_name)){
        user->brands = delete_from_brand_list(user->brands, brand_name);
        return 0; 
    }
    return -1;
}


int get_mutual_friends(User *a, User *b) {
    if(a == NULL || b == NULL||!(is_valid_friend(a->name))|| !(is_valid_friend(b->name))) return 0; 
   int counter = 0; 
    FriendNode* p = a->friends; 
    while(p!= NULL){
        FriendNode* q = b->friends; 
        while(q != NULL){
            if(strcmp(p->user->name, q->user->name) == 0 && (strcmp(a->name, q->user->name) != 0|| strcmp(b->name, p->user->name) != 0)) counter++;
            q = q->next; 
        }
        p = p->next; 
    }
    return counter;
}



typedef struct queue{
    User* user;
    int degree_of_connection; 
    struct queue* next; 
} queue;    

queue* new_queue(User* user, int dgc){
    queue* front = (queue*)malloc(sizeof(queue));
    front->degree_of_connection= dgc; 
    front -> user = user;
    front ->next = NULL;
    return front; 
}


bool found_user(User* a,User* b){
    FriendNode* start = a->friends;
    if(start -> next == NULL && strcmp(start->user->name, b->name) == 0) return true; 
    while(start != NULL){
        if(strcmp(start->user->name, b->name) == 0) return true;
        start = start->next; 
    }
    return false; 
}


queue* add_to_queue(queue* start,  FriendNode* head, int degree){
    if(start == NULL) return NULL; // Handle case where start is NULL
    queue* front = start; 
    while(front->next != NULL){
        front = front->next; // Traverse to the end of the queue
    }
    while(head != NULL){
        if(!head->user->visited && is_valid_friend(head->user->name)){
            front->next = new_queue(head->user, degree);
            front = front->next;
            head->user->visited = true; 
        } 
        head = head->next; 
    }
    return start; 
}


queue* free_from_queue(queue* head){
    if(head == NULL) return NULL;
    queue* p = head->next; 
    free(head);
    return p;
}

void free_queue(queue* head){
    if(head == NULL) return;
    if(head->next == NULL){
        free(head);
        return;
    }
    queue* next = head->next;
    while(head != NULL){
        next = next -> next;
        free(head);
        head = next; 
    }
    return; 
}

void reset_visited(FriendNode* all){
    FriendNode* all_copy = all; 
    if(all_copy -> next == NULL && all_copy->user->visited){
        all_copy->user->visited = false;
        return;
    }
    while(all_copy != NULL){
        if(all_copy->user->visited){
            all_copy->user->visited = false;
        }
        all_copy = all_copy->next;
    }
    return; 
}

int get_degrees_of_connection(User *a, User *b) {
    if(a == NULL||b == NULL|| !is_valid_friend(a->name) || !is_valid_friend(b->name)|| a->friends == NULL) return -1; 
    if(strcmp(a->name, b->name ) == 0) return 0; 
    int depth = 1; 
    queue* head = new_queue(a , depth);
    while(head != NULL){
        if(found_user(head->user,b)){
            depth = head->degree_of_connection; 
            reset_visited(allUsers);
            free_queue(head); 
            return depth; 
        } 
        else{ 
            head = add_to_queue(head, head->user->friends,(head->degree_of_connection)+1);
            head = free_from_queue(head);
        }
    }
    free_queue(head); 
    reset_visited(allUsers);
    return -1; 
}



void connect_similar_brands(char *brandNameA, char *brandNameB) {
    if(brandNameA == NULL || brandNameB == NULL|| (!is_valid_brand(brandNameA) && !is_valid_brand(brandNameB))) return; 
    int a_index;
    int b_index; 
    for(int i = 0; i < MAT_SIZE; i++){
        if(strcmp(brandNameA, brand_names[i])==0) a_index =i;
        if(strcmp(brandNameB, brand_names[i])==0) b_index = i; 
    }
    brand_adjacency_matrix[a_index][b_index] =1;
    brand_adjacency_matrix[b_index][a_index] =1; 
    return;
}



int get_mutual_brands(User* a, User* b){
    int counter =0;
    BrandNode*brandA, *brandB; 
    brandA = a->brands;
    brandB = b -> brands;
    if(brandA == NULL||brandB == NULL) return 0; 
    while(brandA != NULL){
        BrandNode* parseB = brandB; 
        while(parseB != NULL){
            if(strcmp(brandA->brand_name, parseB->brand_name) == 0){
                counter++; 
            } 
            parseB = parseB->next; 
        }
        brandA = brandA -> next; 
    }
    return counter; 
}
User* first_nonFriend(FriendNode* all, User* user){
    FriendNode* all_copy = all; 
    while(all_copy != NULL){
        if(strcmp(all_copy->user->name, user->name) != 0 && !in_friend_list(user->friends, all_copy->user))
            return all_copy->user; 
        all_copy = all_copy->next; 
    }
    return NULL; 
}

User *get_suggested_friend(User *user) {
    if (user == NULL || allUsers == NULL) 
        return NULL; 

    int max = 0; 
    FriendNode* new_friend = allUsers; 
    User* suggest = first_nonFriend(new_friend, user); 
    if (suggest == NULL) 
        return NULL;
    while (new_friend != NULL) {
        int current = get_mutual_brands(new_friend->user, user);
        
        if (current > max || (current == max && strcmp(new_friend->user->name, suggest->name) > 0)) {
            if (!in_friend_list(user->friends, new_friend->user) && strcmp(user -> name, new_friend->user->name) != 0) {
                suggest = new_friend->user;
                max = current;
            }
        }
        
        new_friend = new_friend->next; 
    }
    return suggest; 
}



int add_suggested_friends(User *user, int n) {
    if(user == NULL|| !is_valid_friend(user -> name)) return 0; 
    int count = 0; 
    User* current_friend = NULL; 
    for(int i =0; i < n; i++){
        current_friend = get_suggested_friend(user); 
        if(current_friend == NULL) break; 
        add_friend(user, current_friend);
        count++; 
    }
    return count;
}


bool is_similar_brand(BrandNode* user, char* brand_name){
    if(is_valid_brand(brand_name)){
        int user_index = get_brand_index(user->brand_name);
        int suggest_index = get_brand_index(brand_name); 
        if(brand_adjacency_matrix[user_index][suggest_index] == 1 && brand_adjacency_matrix[suggest_index][user_index]==1) return true;
        }
    return false; 
}

int count_similarities(BrandNode* user, char* brand_name){
    {
    int counter = 0;
    while (user != NULL) {
        if (is_similar_brand(user, brand_name))
            counter++;
        user = user->next;
    }
    return counter;
    } 
}

typedef struct suggest_node{
    char name[MAX_STR_LEN];
    int similarities;
    struct suggest_node* next; 
}Suggest_node; 

Suggest_node* new_suggestion (char* name, int similarities){
   Suggest_node* node = (Suggest_node*)malloc(sizeof(Suggest_node));
    if (node != NULL) {
        strcpy(node->name, name);
        node->similarities = similarities;
        node->next = NULL;
    }
    return node; 
}

void free_suggestions(Suggest_node* head){
     Suggest_node *temp;
        while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);}
    return; 
}

int follow_suggested_brands(User *user, int n) {
     if (user == NULL || user->brands == NULL|| n == 0)
        return 0;

    Suggest_node* head = NULL;
    int p = 0;
    while(p<MAT_SIZE){
        char* suggest = brand_names[p];
        if (suggest == NULL || in_brand_list(user->brands, suggest)){
            p++;
            continue;
        }  
        int similarities = count_similarities(user->brands, suggest); 
        if(head == NULL){
            head = new_suggestion(suggest, similarities);
        }
        else if (head -> next == NULL){
            Suggest_node* temp = new_suggestion(suggest, similarities);
            if (similarities > head-> similarities || (similarities == head-> similarities && strcmp(suggest, head->name) > 0)){
                temp -> next = head;
                head = temp; 
            }
            else{
                head -> next = temp; 
            }
        } else {
            if(similarities > head->similarities || ((strcmp(suggest, head->name) > 0) && similarities == head -> similarities)){
                Suggest_node* temp = new_suggestion(suggest, similarities);
                temp -> next = head;
                head = temp; 
            }
            
            else{
            Suggest_node* parse = head; 
            while(parse -> next != NULL && (similarities < parse->next->similarities || ((strcmp(suggest, parse->next-> name) < 0) && similarities == parse ->next -> similarities))){
        
                parse = parse -> next; 
            }
            
            Suggest_node* temp = new_suggestion(suggest, similarities); 
               if (parse->next == NULL) {
                    parse->next = temp;  
                } 
                else {
                    temp->next = parse->next;
                    parse->next = temp;
                }
            }           
        }
        p++; 
    }
    //add to brandlist
    if(head == NULL) return 0;
    if(head->next  == NULL){
        user ->brands = insert_into_brand_list(user->brands, head->name);
        free(head);
        return 1; 
    }
    Suggest_node *temp;
    int j = 0;
    while (head != NULL && j < n) {
        user->brands = insert_into_brand_list(user->brands, head->name);
        temp = head;
        head = head->next;
        free(temp);
        j++;
    }
    return j; 
}

