/**
 * Assignment 3 - Wacky Marketing
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * There are also additional notes and clarifications on Quercus.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */



#include "marketing.c"
#include <assert.h>

/**
 * You may modify this file however you wish as it will not be submitted on
 * Quercus. Please ensure that your code still works and does not depend on this
 * file as the automarker will be using a different main().
 */

void clear_brand_names();

void given_tests(){
    printf("test basics\n");
     // Create new users
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    FriendNode *t = allUsers;
    int idx = 0;
    while (t != NULL && t->next != NULL) {
        if (strcmp(t->user->name, t->next->user->name) > 0) {
            printf("Test 1 failed. Users are not sorted.\n");
            exit(1);
        }

        idx++;
        t = t->next;
    }

    if (idx != 3) {
        printf("Test 1 failed. Users were not inserted.\n");
        exit(1);
    }

    add_friend(angela, brian);

    // Expect to see Angela with her friend Brian & see Brian with his friend Angela
    if (!in_friend_list(angela->friends, brian) || !in_friend_list(brian->friends, angela)) {
        printf("Test 2 failed. Friend connection was not made.\n");
        exit(1);
    }
    int angela_and_brian = get_degrees_of_connection(angela, brian);

    if (angela_and_brian != 1) {  // Expect 1
        printf("Test 3 failed. Friend connection was not made.\n");
        exit(1);
    }
    clear_brand_names();
    populate_brand_matrix("brands.txt");
    follow_brand(angela, "brandonRufino");

    // Angela should now follow brandonRufino.
    if (!in_brand_list(angela->brands, "brandonRufino")) {
        printf("Test 4 failed. Brand connection was not made.\n");
        exit(1);
    }
    connect_similar_brands("brandZero", "brandTwo");
    int zeroIdx = get_brand_index("brandZero");
    int twoIdx = get_brand_index("brandTwo");

    if (brand_adjacency_matrix[zeroIdx][twoIdx] != 1 || brand_adjacency_matrix[twoIdx][zeroIdx] != 1) {
        printf("Test 5 failed. Brand connection was not made.\n");
        exit(1);
    }
    add_friend(angela, william);
    int mutuals_brian_will = get_mutual_friends(brian, william);

    if (mutuals_brian_will != 1) {  // Expect 1
        printf("Test 6 failed. Mutual friends of Brian and William should be 1.\n");
        exit(1);
    }
    User *brianSuggested = get_suggested_friend(brian);

    if (brianSuggested != william) {  // We should see Will here again
        printf("Test 7 failed. Brian was not suggested William.\n");
        exit(1);
    }
    add_friend(angela, mustafa);
    add_suggested_friends(mustafa, 2);

    // Expect to see Mustafa with friends Angela, Brian, and Will
    if (!in_friend_list(mustafa->friends, brian) || !in_friend_list(mustafa->friends, william)) {
        printf("Test 8 failed. Mustafa was not suggested 2 friends correctly.\n");
        exit(1);
    }
    follow_brand(william, "brandTwo");
    follow_brand(mustafa, "brandZero");
    follow_suggested_brands(mustafa, 1);

    // Mustafa should now also follow brandonRufino. A tie is broken against brandTwo.
    if (!in_brand_list(mustafa->brands, "brandonRufino")) {
        printf("Test 9 failed. Mustafa did not follow brand 'brandonRufino'.\n");
        exit(1);
    }

     //remove all users
    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    printf("All basic test cases passed. :)\n");

}
void test_get_degrees_of_connection(){
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    User *benDover = create_user("Ben Dover");
    add_friend(william, angela);
    add_friend(angela, mustafa);
    add_friend(mustafa, brian);
    add_friend(brian, benDover);
    print_user_data(angela);
    print_user_data(william);
    print_user_data(mustafa);
    print_user_data(brian);
    print_user_data(benDover); 
    printf("test_get_degrees_of_connection\n");
    //sc
    assert(get_degrees_of_connection(NULL, NULL) == -1);
    assert(get_degrees_of_connection(william, NULL)== -1);
    assert(get_degrees_of_connection(NULL, william) == -1);
    //
    if(get_degrees_of_connection(william, benDover) != 4){
        printf("failed test 1.0 got %d expected 4\n", get_degrees_of_connection(william, benDover));
        exit(1);
    }
    add_friend(benDover, angela);
    if(get_degrees_of_connection(william, benDover) != 2){
        printf("failed test 1.1 got %d expected 2\n", get_degrees_of_connection(william, benDover));
        exit(1);
    }
    if(get_degrees_of_connection(william, brian) != 3){
        printf("failed test 1.2 got %d expected 3", get_degrees_of_connection(william, brian));
        exit(1);
    }
    add_friend(angela, brian);
    if(get_degrees_of_connection(william, brian) != 2){
        printf("failed test 1.3 got %d expected 2", get_degrees_of_connection(william, brian));
        exit(1);
    }
    add_friend(william, brian);
    if(get_degrees_of_connection(william, brian) != 1){
        printf("failed test 1.4 got %d expected 1", get_degrees_of_connection(william, brian));
        exit(1);
    }
    //remove all users
    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    delete_user(benDover);
    printf("get_degrees_of_connection pass\n");

}

void test_follow_suggested_brands(){
    printf("test follow suggested brands\n");
    User *charles = create_user("Charles");
    clear_brand_names();
    populate_brand_matrix("brands2.txt");
    char a[] = "A";
    char c[] = "C";
    char d[] = "D";
    follow_brand(charles, a);
    assert(follow_suggested_brands(charles, 2)== 2);
    if(!in_brand_list(charles->brands, a) || !in_brand_list(charles->brands, c) || !in_brand_list(charles->brands, d)){
        printf("t1 fail\n");
        /*
        BrandNode *qwe = charles->brands;
        printf("he;;p\n");
        while (qwe != NULL){
            printf("%s\n", qwe->brand_name);
            qwe = qwe->next;
        }
        */
        exit(1);
    }
    //sc
    assert(follow_suggested_brands(NULL, 100) == 0);
    //
    delete_user(charles);
    printf("test follow suggested brands pass\n");

}

/**
 * clear the elements of brand_namesto stop bugs
*/
void clear_brand_names(){
    for(int i = 0; i<MAT_SIZE; i++){
        for(int j = 0; j<MAX_STR_LEN; j++){
            brand_names[i][j] = (char)0;
        }
    }
}

void test_remove_friends(){
    printf("test remove friends\n");
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    User *benDover = create_user("Ben Dover");
    add_friend(william, angela);
    add_friend(angela, mustafa);
    add_friend(mustafa, brian);
    add_friend(brian, benDover);
    print_user_data(william);
    remove_friend(william, angela);
    print_user_data(william);
    remove_friend(angela, mustafa);
    remove_friend(mustafa, brian);
    remove_friend(brian, benDover);
    print_user_data(william);
    print_user_data(angela);
    assert(in_friend_list(william->friends, angela) == false);
    assert(in_friend_list(angela->friends, mustafa) == false);
    assert(in_friend_list(mustafa->friends, brian) == false);
    assert(in_friend_list(brian->friends, benDover) == false);
    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    delete_user(benDover);
    printf("test remove friends pass\n");

}

void test_unfollow_brand(){
    printf("test_unfollow_brand\n");
    clear_brand_names();
    populate_brand_matrix("brands2.txt");
    char a[] = "A";
    char b[] = "B";
    char c[] = "C";
    char d[] = "D";
    User *william = create_user("William");
    //User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    User *benDover = create_user("Ben Dover");
    follow_brand(william, a);
    follow_brand(william, b);
    follow_brand(william, c);
    follow_brand(william, d);
    //follow_brand(angela, b);
    follow_brand(mustafa, c);
    follow_brand(brian, d);
    unfollow_brand(william, a);
    unfollow_brand(william, b);
    unfollow_brand(william, c);
    unfollow_brand(william, d);
    //unfollow_brand(angela, b);
    unfollow_brand(mustafa, c);
    unfollow_brand(brian, d);
    ///sc
    assert(unfollow_brand(NULL, d) == -1);
    assert(unfollow_brand(brian, NULL) == -1);
    assert(unfollow_brand(NULL, NULL) == -1);
    ///
    assert(in_brand_list(william->brands, a) == false);
    assert(in_brand_list(william->brands, b) == false);
    assert(in_brand_list(william->brands, c) == false);
    assert(in_brand_list(william->brands, d) == false);
    //assert(in_brand_list(angela->brands, b) == false);
    assert(in_brand_list(mustafa->brands, c) == false);
    assert(in_brand_list(brian->brands, d) == false);
    delete_user(william);
    //delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    delete_user(benDover);
    printf("test_unfollow_brand pass\n");

}

void test_get_mutual_friends(){
    printf("test_get_mutual_friends\n");
    User *william = create_user("William");
    //User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    User *benDover = create_user("Ben Dover");
    //add_friend(william, angela);
    //add_friend(angela, mustafa);
    add_friend(mustafa, brian);
    add_friend(brian, benDover);
    ///sc
    assert(get_mutual_friends(NULL, brian) == 0);
    assert(get_mutual_friends(brian, NULL) == 0);
    assert(get_mutual_friends(NULL, NULL) == 0);
    ///
    assert(get_mutual_friends(william, benDover) == 0);
    add_friend(william, brian);
    assert(get_mutual_friends(william, benDover) == 1);
    add_friend(benDover, mustafa);
    add_friend(william, mustafa);
    assert(get_mutual_friends(william, benDover) == 2);
    delete_user(william);
    //delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    delete_user(benDover);
    printf("test_get_mutual_friends pass\n");

}

void test_create_user(){
    printf("test_create_user\n");
    User *bob = create_user("BOB");
    assert(strcmp(bob->name, "BOB") == 0);
    User *bobN = create_user("BOB");
    assert(bobN == NULL);
    assert(create_user(NULL) == NULL);
    delete_user(bob);
    printf("test_create_user pass\n");
}

void test_delete_user(){
    printf("test_delete_user\n");
    User *bob = create_user("BOB");
    assert(delete_user(bob) == 0);
    assert(delete_user(bob) == -1);
    assert(delete_user(NULL) == -1);
    printf("test_delete_user pass\n");
}

void test_add_friend(){
    printf("test_add_friend\n");
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");
    User *benDover = create_user("Ben Dover");
    assert(add_friend(william, angela)== 0);
    assert(add_friend(william, mustafa) == 0);
    assert(add_friend(william, brian) == 0);
    assert(add_friend(william, benDover) == 0);
    assert(add_friend(william, angela) == -1);
    assert(add_friend(NULL, NULL) == -1);
    assert(add_friend(william, NULL) == -1);
    assert(add_friend(NULL, william) == -1);
    printf("verify alpha order\n");
    print_user_data(william);
    delete_user(william);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);
    delete_user(benDover);
    printf("test_add_friend pass\n");
}

void test_follow_brand(){
    printf("test_follow_brand\n");
    clear_brand_names();
    populate_brand_matrix("brands2.txt");
    User *bob = create_user("bob");
    follow_brand(bob, "A");
    follow_brand(bob, "B");
    assert(in_brand_list(bob->brands, "A"));
    assert(in_brand_list(bob->brands, "B"));
    assert(!in_brand_list(bob->brands, "C"));
    assert(!in_brand_list(bob->brands, "FUCK CHARLES"));
    assert(!in_brand_list(NULL, NULL));
    //assert(!in_brand_list(bob->brands, NULL));
    assert(!in_brand_list(NULL, "A"));
    delete_user(bob);
    printf("test_follow_brand pass\n");
}

int main() {
    printf("1.===================================\n");
    //given_tests();
    printf("2.===================================\n");
    //test_get_degrees_of_connection();
    printf("3.===================================\n");
    test_follow_suggested_brands();
    printf("4.===================================\n");
    //test_remove_friends();
    printf("5.===================================\n");
    //test_unfollow_brand();
    printf("6.===================================\n");
    //test_get_mutual_friends();
    printf("7.===================================\n");
    //test_create_user();
    printf("8.===================================\n");   
    //test_delete_user();
    printf("9.===================================\n"); 
    //test_add_friend();
    printf("10.==================================\n"); 
    //test_follow_brand();
    printf("=====================================\n");
    printf("done :)(now use dr memory)\n");
    return 0;
}
