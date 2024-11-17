#include <stdio.h>
#include <ctype.h>
#include <string.h>

int n, m = 0;       // Number of productions and position in result array
char a[10][10];     // Productions array
char f[10];         // Result array for FIRST and FOLLOW sets

void findFirst(char c);
void findFollow(char c);

int main() {
    int i, choice;
    char c, temp;
    
    printf("Enter the number of productions:\n");
    scanf("%d", &n);
    printf("Enter the productions:\n");
    for (i = 0; i < n; i++) {
        scanf("%s%c", a[i], &temp);
    }
    
    do {
        m = 0;
        printf("Enter the element whose FIRST & FOLLOW is to be found: ");
        scanf(" %c", &c);
        
        findFirst(c);
        printf("First(%c) = {", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        
        printf("}\n");
        
        m = 0;  // Reset for FOLLOW computation
        findFollow(c);
        printf("Follow(%c) = {", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        
        printf("Continue (0/1)? ");
        scanf("%d", &choice);
    } while (choice == 1);
    
    return 0;
}

void addToSet(char c) {
    for (int i = 0; i < m; i++) {
        if (f[i] == c) return;  // Avoid duplicates
    }
    f[m++] = c;
}

void findFirst(char c) {
    for (int k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (!isupper(a[k][2])) {
                addToSet(a[k][2]);
            } else {
                findFirst(a[k][2]);
            }
        }
    }
}

void findFollow(char c) {
    if (a[0][0] == c) addToSet('$');  // Add $ to FOLLOW of start symbol
    
    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0') {
                    if (!isupper(a[i][j + 1])) {
                        addToSet(a[i][j + 1]);
                    } else {
                        findFirst(a[i][j + 1]);
                    }
                } else if (a[i][0] != c) {
                    findFollow(a[i][0]);
                }
            }
        }
    }
}
