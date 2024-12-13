
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mergeFilesAndDisplayCommonStrings(FILE *f1, FILE *f2, FILE *out)
 {
    char str1[15], str2[15];
    int commonExists = 0;   // assume initially no common strings present in both the files

    // Read the first strings from both files
    char *read1 = fgets(str1,15, f1); // read1 is a pointer, pointing to str1
    char *read2 = fgets(str2,15, f2);

    // Remove newline characters, if any
    if (read1) str1[strcspn(str1, "\n")] = '\0'; //if(read1) means successful reading of string from file1.
    if (read2) str2[strcspn(str2, "\n")] = '\0'; // if reading is successful, then replace the last character "\n" from str1 with '\0'.

    while (read1 != NULL && read2 != NULL) // continue reading until one of the file exhausts.
	{
        int cmp = strcmp(str1, str2);

        if (cmp < 0) {
            fprintf(out, "%s\n", str1);// if string from file1 less than string from file2, copy string from file1 to outputfile.
            read1 = fgets(str1,15, f1);// read1 pointer points to next string that is stored  in str1.
            if (read1) str1[strcspn(str1, "\n")] = '\0';// replace a newline character "\n" in  str1 with '\0'-null character.
        } else if (cmp > 0) {
            fprintf(out, "%s\n", str2);
            read2 = fgets(str2,15, f2);
            if (read2) str2[strcspn(str2, "\n")] = '\0';
        } else {
            // str1 == str2, write one of them to the output file and display the common string
            fprintf(out, "%s\n", str1);
            printf("Common string: %s\n", str1);
            commonExists = 1;// indicates common string present in both the files.
            read1 = fgets(str1,15, f1);
            if (read1) str1[strcspn(str1, "\n")] = '\0';
            read2 = fgets(str2,15, f2);
            if (read2) str2[strcspn(str2, "\n")] = '\0';
        }
    }

    // Write the remaining strings from file1, if any
    while (read1 != NULL) {
        fprintf(out, "%s\n", str1);
        read1 = fgets(str1,15,f1);
        if (read1) str1[strcspn(str1, "\n")] = '\0';
    }

    // Write the remaining strings from file2, if any
    while (read2 != NULL) {
        fprintf(out, "%s\n", str2);
        read2 = fgets(str2,15, f2);
        if (read2) str2[strcspn(str2, "\n")] = '\0';
    }

    if (!commonExists) {
        printf("No common strings found.\n");
    }
}

int main() {
    FILE *f1, *f2, *out;

    // Open the first input file
    f1 = fopen("C:/Users/samik/.vscode/f1.txt", "r");
    if (f1 == NULL) {
        printf("Could not open file1.txt\n");
        return 1;
    }

    // Open the second input file
    f2 = fopen("C:/Users/samik/.vscode/f2.txt", "r");
    if (f2 == NULL) {
        printf("Could not open file2.txt\n");
        fclose(f1);
        return 1;
    }

    // Open the output file
    out = fopen("C:/Users/samik/.vscode/out.txt", "w");
    if (out == NULL) {
        printf("Could not open output.txt\n");
        fclose(f1);
        fclose(f2);
        return 1;
    }

    // Merge the files and display common strings
    mergeFilesAndDisplayCommonStrings(f1, f2, out);

    // Close the files
    fclose(f1);
    fclose(f2);
    fclose(out);

    return 0;
}
