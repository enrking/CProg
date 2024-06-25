//use to count the number of strings inputed by the users without using any libraries.

#include <stdio.h>

int main(){

    char s[50];
    char s2[50];

    int slen = 0;
    int slen2 = 0;
    int words = 1;
    int words2 = 1;

    scanf("%[^\n]%*c", s);
    scanf("%[^\n]%*c", s2);

    //string 1
    for(int i = 0; s[i] != '\0'; i++){
        slen++;
        if(((s[i] == ' ') && (s[i + 1] != 0)) || (s[0] == 0)){
            words++;
        } else{}
    }
    if ((s[0] == ' ') || (s[0] == '\0')){
        words = 0;
    } else{}

    printf("\nThe size of string1 is %d.\n", slen);
    printf("The number of words is %d.\n\n", words1);

    for ( int j=0, k=slen-1; j != k || j < k; j++, k--){
        char tmp = s[j];
        s[j] = s[k];
        s[k] = tmp;
    }
    printf("%s\n", s);
    //string 2
    for( int i = 0; s2[i] != '\0'; i++){
        slen2++;
        if(((s2[i] == ' ') && (s2[i + 1] != '\0')) || (s2[0] == 0)){
            words2++;
        } else {}
    }
    if ((s2[0] == ' ')  || (s[0] == '\0')){
        words = 0;
    } else{}

    printf("\nThe size of string2 is %d.\n", slen2);
    printf("The number of words is %d.\n\n", words2);

    for( int j = slen2; j >= 0; j--){
        slen2--;
        printf("%c", s2[j]);
    }



    return 0;
}