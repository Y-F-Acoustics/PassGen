/* Library Header */
#include <stdio.h>  // standard I/O.
#include <stdint.h> // minimize memory.
#include <stdlib.h> // malloc & free.
#include <time.h>   // To generate random number seed.
#include "mt64.h"   // Random Number Generator to generate password.

/* Prototype Definition */
uint8_t is_valid_cond (uint8_t *cond, uint8_t l_pass);

/* Entry Point */
int main (void) {

    /* Variable definition */
    uint8_t isn = 0;     // Valid password length flag. (0: invalid, 1: valid)
    uint8_t l_pass;      // Password length (8 - 255).
    char    l_pass_a[3]; // Ascii password length to change l_pass. 
    char    *passwd;     // Password.
    char    *fp_pass;    // First pointer of passwd.
    uint8_t *cond;       // Password character condition.
    uint8_t *fp_cond;    // First pointer of cond.
    uint8_t i;           // for-loop index.

    /* 
    *   Password Length Input Section. 
    *   If cannot change into number or changed number is under 7,
    *   repeat this section.
    */
    do{
        printf("Input the password length. >>> ");
        scanf("%s", l_pass_a);
 
        if (atoi(l_pass_a) <= 7 || atoi(l_pass_a) > 255) {
            printf("Error: Please input the integer from 8 to 255.\n");
        }else{
            isn = 1;
            l_pass = atoi(l_pass_a);
        }
    }while(isn == 0); // If flag equals to 0, repeat this section.

    /* Dynamic Allocation. */
    passwd = (char *)    malloc(l_pass + 1); // Password
    cond   = (uint8_t *) malloc(l_pass);     // Password character condition

    /* Memorize first pointer. */
    fp_pass = passwd; // passwd[0]
    fp_cond = cond;   // cond[0]

    /*
    *    Password Character Condition Select Section.
    *    Memorize the password character condition as the integer vector.
    * 
    *    Condition:
    *       1. At least one uppercase letter.
    *       2. At least one lowercase letter.
    *       3. At least one integer number, from 0 to 9.
    *       4. At least one specific symbol.
    */
    do {
        /* Generate the random number seed. */
        init_genrand64((unsigned)time(NULL));

        for(i = 0; i < l_pass; i++){
            /* Generate the condition number from 1 to 4. */
            *cond = (genrand64_int64() % 4) + 1;

            /* Next condition index. */
            cond++;
        }

        /* First pointer. */
        cond = fp_cond;

    } while (is_valid_cond(cond, l_pass) == 0); // If condition number vector is not valid, repeat this section.
   
    /*
    *   Password Generation Section.
    *   Generates the password string from password character condition vector.
    * 
    *   Condtion:
    *       1. A - Z
    *       2. a - z
    *       3. 0 - 9
    *       4. !, ", #, $, %, &, ', (, ), *, +, ,, -, ., /
    */
    for (i = 0; i < l_pass; i++) {
        switch (*cond){
            case 1:
                /* A - Z */
                *passwd = (genrand64_int64() % 26) + 65;
                break;

            case 2:
                /* a - z */
                *passwd = (genrand64_int64() % 26) + 97;
                break;

            case 3:
                /* 0 - 9 */
                *passwd = (genrand64_int64() % 10) + 48;
                break;

            case 4:
                /* !, ", #, $, %, &, ', (, ), *, +, ,, -, ., / */
                *passwd = (genrand64_int64() % 15) + 33;
                break;

            default:
                break;
        }

        *cond = 0; // Fill the condition number.
        cond++;    // Next condition number index.
        passwd++;  // Next password index.
    }

    *passwd = '\0';   // Fill NULL letter.
    passwd = fp_pass; // First password index
    cond = fp_cond;   // First condition index.
    fp_cond = NULL;   // Erase first pointer.
    free(cond);

    /* Indicate the generated password */
    printf("\nYour new password: %s\n", passwd);

    /* Overwrite the password by NULL. */
    for (i = 0; i < l_pass; i++) {
        *passwd = '\0';
        passwd++;
    }
    passwd = fp_pass; // First password index
    //printf("\nErased password: %s\n", passwd); // for Debug.
    fp_pass = NULL; // Erase first pointer.
    free(passwd);

    /* Finalize this program. */
    printf("\nIf you made note, press Enter.");
    getchar();
    getchar();
    
    return 0;
}

/* Function Definition */
uint8_t is_valid_cond (uint8_t *cond, uint8_t l_pass) {
    
    uint8_t *fp_cond;  // First pointer of *cond
    uint8_t cond1 = 0; // The number of condition 1
    uint8_t cond2 = 0; // The number of condition 2
    uint8_t cond3 = 0; // The number of condition 3
    uint8_t cond4 = 0; // The number of condition 4
    uint8_t i;         // for-loop index

    /* Memorize first pointer of cond */
    fp_cond = cond;

    /* Count the number of each condition. */
    for (i = 0; i < l_pass; i++){
        switch (*cond) {
            case 1:
                /* At least one uppercase letter. */
                cond1 += 1;
                break;

            case 2:
                /* At least one lowercase letter. */
                cond2 += 1;
                break;

            case 3:
                /* At least one integer number, from 0 to 9 */
                cond3 += 1;
                break;

            case 4:
                /* At least one specific symbol. */
                cond4 += 1;
                break;

            default:
                break;
        }

        /* Next condition number. */
        cond++;
    }

    cond = fp_cond; // Return to first index.
    fp_cond = NULL; // Erase first pointer.

    /* Judge the condition vector meets all conditions. */
    return ((cond1 > 0) && (cond2 > 0) && (cond3 > 0) && (cond4 > 0));
}