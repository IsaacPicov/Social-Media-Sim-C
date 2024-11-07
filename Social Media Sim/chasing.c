#include "marketing.c"

/* READ FIRST:
I've modified brands.txt to contain a 9x9 matrix. Use the file chase_brands.txt. I've modified the code here to populate
the brand matrix in chase_brands.txt. Since the matrix I used is 9x9, modify the definition of MAT_SIZE in marketing.c to 
9 before running it, or else unexpected behavior could happen. I don't know if we have to change it back to 3 before submission.
*/


int main() {
    //Sousou no Frieren season 2 when
    User *pikachu = create_user("Pikachu"); //1
    User *frieren = create_user("Frieren"); //2
    User *fern = create_user("Fern"); //3
    User *stark = create_user("Stark"); //4
    User *land = create_user("Land"); //5
    User *land_clone = create_user("LAND"); //6
    User *land_clone_2 = create_user("Land"); //Same name as land ("Land"); shouldn't be created
    User *ubel = create_user("Ubel"); //7
    User *denken = create_user("Denken"); //8
    User *laufen = create_user("Laufen"); //9
    User *richter = create_user("Richter"); //10
    User *wirbel = create_user("Wirbel"); //11
    User *ehre = create_user("Ehre"); //12
    User *scharf = create_user("Scharf"); //13
    User *methode = create_user("Methode"); //14
    User *lawine = create_user("Lawine"); //15
    User *kanne = create_user("Kanne"); //16
    User *serie = create_user("Serie"); //17
    User *flamme = create_user("Flamme"); //18
    User *lernen = create_user("Lernen"); //19
    User *himmel = create_user("Himmel"); //20
    User *eisen = create_user("Eisen"); //21
    User *heiter = create_user("Heiter"); //22
    User *kraft = create_user("Kraft"); //23
    User *sense = create_user("Sense"); //24
    User *sein = create_user("Sein"); //25
    User *rowlet = create_user("Rowlet"); //26
    User *aura = create_user("Aura"); //27
    User *burg = create_user("Burg"); //28


    //Test 1.1 - Duplicate name included (land and land_clone_2)
    printf("\nTest 1.1 - Users printed in alphabetical order\n");
    FriendNode *t = allUsers;
    int idx = 0;
    while (t != NULL && t->next != NULL) {
        if (strcmp(t->user->name, t->next->user->name) > 0) {
            printf("Test 1.1 failed. Users are not sorted.\n");
            exit(1);
        }
        idx++;
        printf("%s, %d\n", t -> user -> name, idx);
        t = t->next;
    }
    printf("%s, %d\n", t -> user -> name, idx + 1);

    if (idx != 27) {
        printf("Test 1.1 failed. Users were not inserted. idx = %d\n", idx);
        exit(1);
    }

    printf("Test 1.1 passed. User count in allUsers: %d\n", idx + 1);

    //Test 1.2 - Delete User
    printf("\nTest 1.2 - Testing delete_user on existing target\n");
    int result = delete_user(aura);
    if (result != 0) {
        printf("Test 1.2 failed. User was not deleted.");
        exit(1);
    }
    
    if (in_friend_list(allUsers, aura)) {
        printf("Test 1.2 failed. User was not deleted.");
        exit(1);
    }

    printf("Test 1.2 passed. The user to be deleted was found.\n");

    //Test 1.3 - delete_user on an already deleted user
    printf("\nTest 1.3 - Testing delete_user a non-existent (already deleted) target\n");
    int result_2 = delete_user(aura);
    if (result_2 != -1) {
        printf("Test 1.3 failed. Return value was: %d: ", result_2);
        exit(1);
    }
    printf("Test 1.3 passed. The function correctly returned -1.\n");

    //Test 1.4 - Delete User on a user that was never created
    printf("\nTest 1.4 - Testing delete_user a target that wasn't created\n");
    int result_3 = delete_user(land_clone_2); //land_clone_2 was never created as he had the same name as land
    if (result_3 != -1) {
        printf("Test 1.4 failed. Return value was: %d: ", result_3);
        exit(1);
    }
    printf("Test 1.4 passed. The function correctly returned -1.\n");

    //Test 1.5
    add_friend(burg, serie);
    printf("\nTest 1.5 - Testing delete_user on a target that is in both allUsers and a friend list\n");
    int result_4 = delete_user(burg);
    if (result_4 != 0 || in_friend_list(allUsers, burg) || in_friend_list(serie -> friends, burg)) {
        printf("Test 1.5 failed. Return value was: %d: ", result_4);
        exit(1);
    }
    printf("Test 1.5 passed. The function correctly returned -1.\n");


    //Test 2.1 - Testing add_friend: Frieren and Wirbel
    printf("\nTest 2.1 - Frieren adds Wirbel as a friend\n"); //Tests add_friend
    int frieren_add_wirbel = add_friend(frieren, wirbel);

    if (!in_friend_list(frieren->friends, wirbel) || !in_friend_list(wirbel->friends, frieren) || frieren_add_wirbel != 0) {
        printf("Test 2.1 failed. Friend connection was not made.\n");
        exit(1);
    }
    printf("Test 2.1 passed.\n");


    //Test 2.2 - Testing 2nd instance of add_friend: Frieren and Pikachu
    printf("\nTest 2.2 - Frieren adds Pikachu as a friend\n"); //Tests add_friend
    int frieren_add_pikachu = add_friend(frieren, pikachu);

    if (!in_friend_list(frieren->friends, pikachu) || !in_friend_list(pikachu->friends, frieren) || frieren_add_pikachu != 0) {
        printf("Test 2.2 failed. Friend connection was not made.\n");
        exit(1);
    }
    printf("Test 2.2 passed.\n");


    //Test 2.3 - Testing remove_friend: Frieren and Pikachu
    printf("\nTest 2.3 - Frieren removes Pikachu as a friend as they are of different worlds\n"); //Tests remove_friend
    int frieren_remove_pikachu = remove_friend(frieren, pikachu);

    if (in_friend_list(frieren->friends, pikachu) || in_friend_list(pikachu->friends, frieren) || frieren_remove_pikachu != 0) {
        printf("Test 2.3 failed. Friend connection was not made.\n");
        exit(1);
    }
    printf("Test 2.3 passed.\n");


    //Test 2.4 - Testing add_friend on two people that are already friends
    printf("\nTest 2.4 - Frieren adds Wirbel as a friend. Both are already friends.\n"); 
    int frieren_add_wirbel_again = add_friend(frieren, wirbel);
    if (!in_friend_list(frieren->friends, wirbel) || !in_friend_list(wirbel->friends, frieren) || frieren_add_wirbel_again != -1) {
        printf("Test 2.4 failed. The integer returned is: %d\n", frieren_add_wirbel);
        exit(1);
    } 
    printf("Test 2.4 passed.\n");


    //Test 2.5 - Testing remove_friend on two people that were never friends
    printf("\nTest 2.5 - Frieren removes Serie as a friend. They were never friends.\n"); 
    int frieren_remove_serie = remove_friend(frieren, serie);
    if (in_friend_list(frieren->friends, serie) || in_friend_list(frieren->friends, serie) || frieren_remove_serie != -1) {
        printf("Test 2.5 failed. The integer returned is: %d\n", frieren_remove_serie);
        exit(1);
    } 
    printf("Test 2.5 passed.\n");


    /*There is a slight possibility my solutions for 3.x is faulty (if I misdrew something). If you run into errors consider 
    drawing the graph for yourself to verify that everything is correct*/

    //Test 3.1 - Degree of 1
    add_friend(frieren, fern);
    printf("\nTest 3.1 - Degree of connection between Frieren and Fern is 1\n");
    int frieren_and_fern = get_degrees_of_connection(frieren, fern);
    if (frieren_and_fern != 1) {  
        printf("Test 3.1 failed. Friend connection was not made. Return value: %d\n", frieren_and_fern);
        exit(1);
    }
    printf("Test 3.1 passed.\n");


    //Test 3.2 - Degree of 2
    add_friend(fern, ubel);
    printf("\nTest 3.2 - Degree of connection between Frieren and Ubel is 2\n");
    int frieren_and_ubel = get_degrees_of_connection(frieren, ubel);
    if (frieren_and_ubel != 2) {  
        printf("Test 3.2 failed. Friend connection was not made. Return value: %d\n", frieren_and_ubel);
        exit(1);
    }
    printf("Test 3.2 passed.\n");


    //Test 3.3 - No connection
    printf("\nTest 3.3 - Degree of connection between Frieren and Pikachu is non existent. -1 Must be returned\n");
    int frieren_and_pikachu = get_degrees_of_connection(frieren, pikachu);
    if (frieren_and_pikachu != -1) { 
        printf("Test 3.3 failed. Friend connection was not made. Return value: %d\n", frieren_and_pikachu);
        exit(1);
    }
    printf("Test 3.3 passed.\n");


    //Test 3.4 - Degree of 3
    add_friend(ubel, land);
    printf("\nTest 3.4 - Degree of connection between Frieren and Land is 3.\n");
    int frieren_and_land = get_degrees_of_connection(frieren, land);
    if (frieren_and_land != 3) { 
        printf("Test 3.4 failed. Friend connection was not made. Return value: %d\n", frieren_and_land);
        exit(1);
    }
    printf("Test 3.4 passed.\n");


    //Test 3.5 - Multiple paths: Degrees of 1 AND 4 exist.
    add_friend(frieren, laufen);
    printf("\nTest 3.5 - Degree of connection between Frieren and Laufen is 1. Multiple paths exist: \nFrieren -> Laufen (1) and Frieren -> Fern -> Ubel -> Denken -> Laufen (4)\n");
    int frieren_and_laufen = get_degrees_of_connection(frieren, laufen);
    if (frieren_and_laufen != 1) { 
        printf("Test 3.5 failed. Friend connection was not made. Return value: %d\n", frieren_and_laufen);
        exit(1);
    }
    printf("Test 3.5 passed.\n");


    //Test 3.6 - Multiple paths: Degrees of 5 AND 6 exist.
    add_friend(ehre, scharf);
    add_friend(wirbel, ehre);
    add_friend(frieren, flamme);
    add_friend(serie, flamme);
    add_friend(land_clone, scharf);
    printf("\nTest 3.6 - Degree of connection between Flamme and Scharf is 4.\nMultiple paths exist: Flamme -> Frieren -> Wirbel -> Ehre -> Scharf (4) and Flamme -> Frieren -> Fern -> Ubel -> Land -> land (land_clone) -> Scharf (6).\n");
    int flamme_and_scharf = get_degrees_of_connection(flamme, scharf);
    if (flamme_and_scharf != 4) { 
        printf("Test 3.6 failed. Friend connection was not made. Return value: %d\n", frieren_and_land);
        exit(1);
    }
    printf("Test 3.6 passed.\n");


    //Test 3.7 - Same person.
    printf("\nTest 3.7 - Degree of connection between the same person must be zero as per the instructions on Quercus.");
    int frieren_and_frieren = get_degrees_of_connection(frieren, frieren);
    if (frieren_and_frieren != 0) {
        printf("Test 3.7 failed. Return value: %d\n", frieren_and_land);
        exit(1);
    }
    printf("Test 3.7 passed.\n");


    //Test 3.8 - Multiple paths exist: Degrees of 3, 4 AND 5 exist.
    add_friend(richter, kanne);
    add_friend(kanne, lawine);
    add_friend(kanne, frieren);
    add_friend(lawine, frieren);
    add_friend(frieren, stark);
    add_friend(fern, stark);
    printf("\nTest 3.8 - Degree of connection between Richter and Stark is 3.\nMultiple paths exist: Richter -> Kanne -> Frieren -> Stark (3), Richter -> Denken -> Ubel -> Fern -> Stark (4),\nRichter -> Kanne -> Lawine -> Frieren -> Stark (4), Richter -> Kanne -> Lawine -> Frieren -> Fern -> Stark (5)\n");
    int richter_and_stark = get_degrees_of_connection(richter, stark);
    if (richter_and_stark != 3) {
        printf("Test 3.8 failed. Return value: %d\n", richter_and_stark);
        exit(1);
    }
    printf("Test 3.8 passed.\n");


    //Test 3.9 - Multiple paths exist: Degrees of 2, 3, 4, 7 (and probably longer ones too) exist. 2 is the shortest.
    add_friend(denken, methode);
    add_friend(frieren, methode);
    add_friend(serie, lernen);
    add_friend(frieren, himmel);
    add_friend(frieren, eisen);
    add_friend(frieren, heiter);
    add_friend(sense, frieren);
    add_friend(sense, serie);
    add_friend(sense, lernen);
    printf("\nTest 3.9 - Degree of connection between Lawine and Sense is 2.\nMultiple paths exist: Lawine -> Frieren -> Sense (2) is the shortest.\n");
    int lawine_and_sense = get_degrees_of_connection(lawine, sense);
    if (lawine_and_sense != 2) {
        printf("Test 3.9 failed. Return value: %d\n", lawine_and_sense);
        exit(1);
    }
    printf("Test 3.9 passed.\n");


    //Test 3.10 - Multiple paths exist: Degrees of 6, 7 exist. 
    add_friend(land_clone, land);
    printf("\nTest 3.10 - Degree of connection between land (land_clone) and lernen is 6.\nMultiple paths exist: land (land_clone) -> Land -> Ubel -> Fern -> Frieren -> Sense -> Lernen (6) is the shortest.\n");
    int land_clone_and_lernen = get_degrees_of_connection(land_clone, lernen);
    if (land_clone_and_lernen != 6) {
        printf("Test 3.10 failed. Return value: %d\n", land_clone_and_lernen);
        exit(1);
    }
    printf("Test 3.10 passed.\n");


    //Test 3.11 - Multiple paths exist: Two paths with degree of 2 (shortest)
    add_friend(frieren, sein);
    add_friend(sein, stark);
    printf("\nTest 3.11 - Degree of connection between land (land_clone) and lernen is 6.\nMultiple paths exist: land (land_clone) -> Land -> Ubel -> Fern -> Frieren -> Serie -> Lernen (6) is the shortest.\n");
    int fern_and_sein = get_degrees_of_connection(fern, sein);
    if (fern_and_sein != 2) {
        printf("Test 3.11 failed. Return value: %d\n", fern_and_sein);
        exit(1);
    }
    printf("Test 3.11 passed.\n");


    //Test 3.12 - Another case with no connection (i.e. return -1)
    add_friend(pikachu, rowlet);
    printf("\nTest 3.12 - There is no connection between Frieren and Rowlet. Must return -1\n");
    int frieren_and_rowlet = get_degrees_of_connection(frieren, rowlet);
    if (frieren_and_rowlet != -1) {
        printf("Test 3.12 failed. Return value: %d\n", frieren_and_rowlet);
        exit(1);
    }
    printf("Test 3.12 passed.\n");


    //Test 3.13 - Frieren, Fern, Stark form a triangle. The connection should be 1. Testing that cycles don't make the code malfunction.
    printf("\nTest 3.13 - Frieren and Stark are direct friends\n");
    int frieren_and_stark = get_degrees_of_connection(frieren, stark);
    if (frieren_and_stark != 1) {
        printf("Test 3.13 failed. Return value: %d\n", frieren_and_stark);
        exit(1);
    }
    printf("Test 3.13 passed.\n");


    //Test 3.14 - Kraft and Sein. Mult;iple paths of degrees 2, 3 (and more of higher degrees) exist. 2 is the shortest.
    add_friend(frieren, kraft);
    printf("\nTest 3.14 - Degree of connection between Sein and Kraft is 2: Sein -> Frieren/Stark -> Kraft (2)\n");
    int sein_and_kraft = get_degrees_of_connection(sein, kraft);
    if (sein_and_kraft != 2) {
        printf("Test 3.14 failed. Return value: %d\n", sein_and_kraft);
        exit(1);
    }
    printf("Test 3.14 passed.\n");


    //Test 3.15 - Richter and Sense. Multiple paths of degrees 3, 4, 5 (and more of higher degrees) exist. 3 is the shortest.
    printf("\nTest 3.15 - Degree of connection between Richter and Sense is 3: Richter -> Kanne -> Frieren -> Sense (3)\n");
    int richter_and_sense = get_degrees_of_connection(richter, sense);
    if (richter_and_sense != 3) {
        printf("Test 3.15 failed. Return value: %d\n", richter_and_sense);
        exit(1);
    }
    printf("Test 3.15 passed.\n");

    //Test 3.16 - Richter and Fern. Multiple paths of degrees 3, 4 9and more of higher degrees) exist. 3 is the shortest
    printf("\nTest 3.65 - Degree of connection between Richter and Fern is 3: Richter -> Denken -> Ubel -> Fern (3)\nor Richter -> Kanne -> Frieren -> Fern (3)");
    int richter_and_fern = get_degrees_of_connection(richter, fern);
    if (richter_and_fern != 3) {
        printf("Test 3.16 failed. Return value: %d\n", richter_and_fern);
        exit(1);
    }
    printf("Test 3.16 passed.\n");


    //Test 4.1
    printf("\nTest 4.1 - Frieren follows Brand 'LaundryMagic'\n");
    populate_brand_matrix("chase_brands.txt");
    follow_brand(frieren, "LaundryMagic");

    if (!in_brand_list(frieren -> brands, "LaundryMagic")) {
        printf("Test 4.1 failed. Brand connection was not made.\n");
        exit(1);
    }
    printf("Test 4.1 passed.\n");


    //Test 4.2
    printf("\nTest 4.2 - Heiter follows Brand 'Alcohol'\n");
    populate_brand_matrix("chase_brands.txt");
    follow_brand(heiter, "Alcohol");

    if (!in_brand_list(heiter -> brands, "Alcohol")) {
        printf("Test 4.2 failed. Brand connection was not made.\n");
        exit(1);
    }
    printf("Test 4.2 passed.\n");


    //Test 4.3
    printf("\nTest 4.3 - Heiter unfollows Brand 'Alcohol'\n");
    populate_brand_matrix("chase_brands.txt");
    unfollow_brand(heiter, "Alcohol");

    if (in_brand_list(heiter -> brands, "Alcohol")) {
        printf("Test 4.3 failed. Brand connection was not removed.\n");
        exit(1);
    }
    printf("Test 4.3 passed.\n");


    //Test 4.4 - Test on invalid brand name (not in brandNames global var)
    printf("\nTest 4.4 - Frieren follows an invalid Brand 'DragonSlayer'\n");
    populate_brand_matrix("chase_brands.txt");
    int frieren_follow_invalid_brand = follow_brand(frieren, "DragonSlayer");

    if (in_brand_list(frieren -> brands, "DragonSlayer") || frieren_follow_invalid_brand != -1) {
        printf("Test 4.4 failed. Invalid brand was inserted.\n");
        exit(1);
    }
    printf("Test 4.4 passed.\n");


    //Test 5.1
    printf("\nTest 5.1 - Connect Brands 'LaundryMagic' and 'CleaningMagic'\n");
    connect_similar_brands("LaundryMagic", "CleaningMagic");
    int zeroIdx = get_brand_index("LaundryMagic");
    int twoIdx = get_brand_index("CleaningMagic");

    if (brand_adjacency_matrix[zeroIdx][twoIdx] != 1 || brand_adjacency_matrix[twoIdx][zeroIdx] != 1) {
        printf("Test 5.1 failed. Brand connection was not made.\n");
        exit(1);
    }

    printf("Test 5.1 passed.\n");

    //Test 5.2
    printf("\nTest 5.2 - Connect Brands 'LaundryMagic' and 'Alcohol'\n");
    connect_similar_brands("LaundryMagic", "Alcohol");
    int zeroIdx2 = get_brand_index("LaundryMagic");
    int twoIdx2 = get_brand_index("Alcohol");

    if (brand_adjacency_matrix[zeroIdx2][twoIdx2] != 1 || brand_adjacency_matrix[twoIdx2][zeroIdx2] != 1) {
        printf("Test 5.2 failed. Brand connection was not made.\n");
        exit(1);
    }

    printf("Test 5.2 passed.\n");

    
    //Test 5.3
    printf("\nTest 5.3 - Disconnect Brands 'LaundryMagic' and 'Alcohol'\n");
    remove_similar_brands("LaundryMagic", "Alcohol");
    int zeroIdx3 = get_brand_index("LaundryMagic");
    int twoIdx3 = get_brand_index("Alcohol");

    if (brand_adjacency_matrix[zeroIdx3][twoIdx3] != 0 || brand_adjacency_matrix[twoIdx3][zeroIdx3] != 0) {
        printf("Test 5.3 failed. Brand connection was not made.\n");
        exit(1);
    }

    printf("Test 5.3 passed.\n");



    //Test 6.1
    printf("\nTest 6.1 - Frieren and Ehre have Wirbel as a mutual friend\n");
    int mutuals_frieren_ehre = get_mutual_friends(frieren, ehre);

    if (mutuals_frieren_ehre != 1) {  
        printf("Test 6.1 failed. Mutual friends of Frieren and Ehre should be 1. Return value: %d\n", mutuals_frieren_ehre);
        exit(1);
    }

    printf("Test 6.1 passed.\n");

    //Test 6.2
    printf("\nTest 6.2. - Frieren and Land don't have mutual friends\n");
    int mutuals_frieren_land = get_mutual_friends(frieren, land);

    if (mutuals_frieren_land != 0) {  
        printf("Test 6.2 failed. Mutual friends of Frieren and Land should be 0. Return value: %d\n", mutuals_frieren_land);
        exit(1);
    }

    printf("Test 6.2 passed.\n");

    //Test 6.3
    add_friend(stark, kraft);
    printf("\nTest 6.3. - Frieren and Stark have 3 mutual friends: Fern, Sein, Kraft.\n");
    int mutuals_frieren_stark = get_mutual_friends(frieren, stark);

    if (mutuals_frieren_stark != 3) {  
        printf("Test 6.3 failed. Mutual friends of Frieren and Stark should be 3. Return value: %d\n", mutuals_frieren_stark);
        exit(1);
    }

    printf("Test 6.3 passed.\n");


    //Test 7.1
    printf("\nTest 7.1 - Frieren is suggested 1 friend based on mutually followed Brands\n");
    follow_brand(denken, "LaundryMagic");
    User *frierenSuggested = get_suggested_friend(frieren);

    if (frierenSuggested != denken) {  
        printf("Test 7.1 failed. Frieren was not suggested Denken. Both follow 'LaundryMagic'. No one else does.\n");
        printf("Instead, %s was suggested.\n", frierenSuggested -> name);
        exit(1);
    }

    printf("Test 7.1 passed.\n");


    //Test 7.2
    printf("\nTest 7.2 - Sein is suggested 1 friend based on reverse alphanumerical order\n");
    User *seinSuggested = get_suggested_friend(sein);

    if (seinSuggested != wirbel) {  
        printf("Test 7.2 failed. Sein was not suggested Wirbel. Sein follows no brands as of yet. Wirbel is the first on reverse alphanumerical order.\n");
        printf("Instead, %s was suggested.\n", seinSuggested -> name);
        exit(1);
    }

    printf("Test 7.2 passed.\n");

    
    //Test 7.3
    printf("\nTest 7.3 - Fern is suggested 1 friend based on reverse alphanumerical order AND mutually followed brands\n");
    follow_brand(fern, "Zoltraak");
    follow_brand(serie, "Zoltraak");
    follow_brand(methode, "Zoltraak");
    User *fernSuggested = get_suggested_friend(fern);

    if (fernSuggested != serie) {  
        printf("Test 7.3 failed. Fern was not suggested Serie. Fern follows 'Zoltraak'. Denken, Serie and Methode follow Zoltraak\n");
        printf("Instead, %s was suggested.\n", fernSuggested -> name);
        exit(1);
    }

    printf("Test 7.3 passed.\n");


    //Test 7.4
    printf("\nTest 7.4 - Fern is suggested 1 friend based on mutually followed brands count\n");
    follow_brand(fern, "LaundryMagic"); //By this point Fern follows Zoltraak and LaundryMagic
    follow_brand(methode, "LaundryMagic"); //By this point Methode follows Zoltraak and LaundryMagic
    User *fernSuggested_2 = get_suggested_friend(fern);

    if (fernSuggested_2 != methode) {  
        printf("Test 7.4 failed. Fern was not suggested Methode. Fern follows 'Zoltraak' and 'LaundryMagic'. Only Frieren and Methode follow both. Frieren is already Fern's friend.\n");
        printf("Instead, %s was suggested.\n", fernSuggested_2 -> name);
        exit(1);
    }

    printf("Test 7.4 passed.\n");
    
    
    //Test 8.1
    printf("\nTest 8.1 - Frieren adds 2 suggested friends\n");
    add_friend(frieren, denken);
    int frieren_adds_2_friends = add_suggested_friends(frieren, 2);

    // Normally, Denken would be the first suggested friend but I added him manually above. The next test (8.2) removes all 
    // of the 3 suggested friends added during tests 7.1 and 8.1 from Frieren's friend list.
    if (!in_friend_list(frieren->friends, ubel) || !in_friend_list(frieren->friends, serie) || frieren_adds_2_friends != 2) {
        printf("Test 8.1 failed. Frieren was not suggested 2 friends: Ubel and Serie correctly. Or the return value is wrong.\n");
        exit(1);
    }
    printf("Test 8.1 passed.\n");


    //Test 8.2 - The 3 previous added suggested friends Denken, Ubel, Serie are removed from Frieren's list.
    //Denken is the first priority as he follows "LaundryMagic". Then Ubel and Serie by reverse alphanumerical value.
    printf("\nTest 8.2 - Frieren adds 3 suggested friends. The previous 3 added are removed\n");
    remove_friend(frieren, denken);
    remove_friend(frieren, serie);
    remove_friend(frieren, ubel);
    int frieren_adds_3_friends = add_suggested_friends(frieren, 3);
    if (!in_friend_list(frieren -> friends, ubel) || !in_friend_list(frieren -> friends, serie) || 
        !in_friend_list(frieren -> friends, denken) || frieren_adds_3_friends != 3) {
        printf("Test 8.2 failed. Frieren was not suggested 3 friends: Denken, Ubel and Serie correctly. Or the return value is wrong.\n");
        exit(1);
    }
    printf("Test 8.2 passed.\n");

    /*Brands followed by this point
    Frieren: 'LaundryMagic'
    Denken: 'LaundryMagic'
    Fern: 'LaundryMagic', 'Zoltraak'
    Methode: 'Laudnrymagic', 'Zoltraak'
    Serie: 'Zoltraak'
    Wirbel: None

    */

    //Test 8.3 - Fern adds 4 suggested friends — Methode by mutual brand count, Serie by 2nd mutual brand count and 
    //reverse alphanumerical order, Denken by 2nd mutual brand count and reverse alphanumerical order, 
    printf("\nTest 8.3 - Fern adds 4 suggested friends.\n");
    int fern_adds_4_friends = add_suggested_friends(fern, 4);
    if (!in_friend_list(fern -> friends, serie) || !in_friend_list(fern -> friends, methode) || 
        !in_friend_list(fern -> friends, denken) || !in_friend_list(fern -> friends, wirbel) || fern_adds_4_friends != 4) {
        printf("Test 8.3 failed. Fern was not suggested 4 friends: Methode, Serie, Denken and Wirbel correctly. Or the return value is wrong.\n");
        exit(1);
    }
    printf("Test 8.3 passed.\n");
    

    //Test 9.1 - 1 Suggested Brand: Similar Brand
    printf("\nTest 9.1 - Frieren follows 1 suggested brand. It should be CleaningMagic.\n");
    int frieren_follows_1_brand = follow_suggested_brands(frieren, 1);

    // Frieren should now also follow CleaningMagic. connect_similar_brands("CleaningMagic", "LaundryMagic") was ran earlier.
    if (!in_brand_list(frieren -> brands, "CleaningMagic") || frieren_follows_1_brand != 1) {
        printf("Test 9.1 failed. Frieren did not follow brand 'CleaningMagic'. Return value: %d\n", frieren_follows_1_brand);
        exit(1);
    }
    printf("Test 9.1 passed.\n");


    //Test 9.2 - 1 Suggested Brand: Reverse alphanumerical Order
    printf("\nTest 9.2 - Frieren follows 1 suggested brand. It should be Zoltraak. She's already followed CleaningMagic from test 9.1\n");
    follow_suggested_brands(frieren, 1);

    // Frieren should now also follow Zoltraak. It is the first in the reverse alpha-numerical order.
    if (!in_brand_list(frieren -> brands, "Zoltraak")) {
        printf("Test 9.2 failed. Frieren did not follow brand 'Zoltraak'.\n");
        exit(1);
    }
    printf("Test 9.2 passed.\n");


    //Test 9.3 - 3 Suggested Brands: 2 Similar Brands, 1 Reverse alphanumerical order
    printf("\nTest 9.3 - Sein follows 3 suggested brands. It should be Gambling, DefenseMagic and Zoltraak\n");
    connect_similar_brands("Sorganeil", "DefenseMagic");
    follow_brand(sein, "GoddessMagic");
    follow_brand(sein, "Alcohol");

    follow_suggested_brands(sein, 3);

    // Sein should now also follow Gambling & DefenseMagic. Both Gambling and DefenseMagic have a similarity of 1. Then Zoltraak wins reverse alphanumerically. 
    // Sorganeil shouldn't be followed in this call as it only gains similarity after DefenseMagic is followed.
    if (!in_brand_list(sein -> brands, "Gambling") || !in_brand_list(sein -> brands, "DefenseMagic") 
        || !in_brand_list(sein -> brands, "Zoltraak") || in_brand_list(sein -> brands, "Sorganeil")) {
        printf("Sein follows %s and %s at the moment", sein -> brands -> brand_name, sein -> brands -> next -> brand_name);
        printf("Test 9.3 failed. Sein did not follow brand 'Gambling' or (not xor) 'DefenseMagic'.\n");
        printf("Instead, %s and %s were followed.", sein -> brands -> next -> brand_name, sein -> brands -> next -> next -> brand_name);
        exit(1);
    }

    printf("Test 9.3 passed.\n");

    //Test 9.4
    printf("\nTest 9.4 - Fern follows 1 suggested brand. It should be CleaningMagic\n");

    follow_suggested_brands(fern, 1);

    //Fern follows both LaundryMagic and Zoltraak, which have similarity with CleaningMagic and Catastravia respectively. CleaningMagic wins reverse alphanumerically.
    if (!in_brand_list(fern -> brands, "CleaningMagic") || !in_brand_list(fern -> brands, "LaundryMagic") || !in_brand_list(sein -> brands, "Zoltraak")) {
        printf("Fern follows %s and %s at the moment", fern -> brands -> brand_name, fern -> brands -> next -> brand_name);
        printf("Test 9.4 failed. Fern did not follow brand 'CleaningMagic'.\n");
        printf("Instead, %s was followed.", fern -> brands -> next -> next -> next -> brand_name);
        exit(1);
    }

    printf("Test 9.4 passed.\n");

    
    //Test 9.5
    printf("\nTest 9.5 - Frieren unfollows Cleaning Magic and Zoltraak then follows 3 suggested brands. It should be CleaningMagic, Zoltraak and Sorganeil\n");
    unfollow_brand(frieren, "Zoltraak");
    unfollow_brand(frieren, "CleaningMagic");
    follow_suggested_brands(frieren, 3);

    // CleaningMagic 1st due to similarity to LaundryMagic, then Zoltraak and Sorganeil by reverse alphanumerical order.
    if (!in_brand_list(frieren -> brands, "Zoltraak") || !in_brand_list(frieren -> brands, "Sorganeil") || !in_brand_list(frieren -> brands, "CleaningMagic")) {
        printf("Test 9.5 failed. Frieren did not follow brand 'Zoltraak'.\n");
        exit(1);
    }
    printf("Test 9.5 passed.\n");
    


    //Test 9.6 - Similarity of 2 vs 1. By this point, Frieren follows LaundryMagic, CleaningMagic, Zoltraak, and Sorganeil 
    printf("\nTest 9.6 - Frieren follows 1 suggested brand. It should be Catastravia\n");
    //Catastravia: similarity score of 2 from Zoltraak & Sorganeil. 
    //DefenseMagic: similarity score of 1 from Sorganeil.
    follow_suggested_brands(frieren, 1);

    if (!in_brand_list(frieren -> brands, "Catastravia")) {
        printf("Test 9.6 failed. Frieren did not follow brand 'Catastravia'.\n");
        exit(1);    
    }
    printf("Test 9.6 passed.\n");


    printf("\nAll test cases in chase_test.c passed.\n");
}
