#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mergeFilesAndDisplayCommonStrings(FILE *file1, FILE *file2, FILE *outputFile) {
    char str1[15], str2[15];
    int commonExists = 0;   // assume initially no common strings present in both the files

    // Read the first strings from both files
    char *read1 = fgets(str1,15, file1); // read1 is a pointer, pointing to str1
    char *read2 = fgets(str2,15, file2);

    // Remove newline characters, if any
    if (read1) str1[strcspn(str1, "\n")] = '\0'; //if(read1) means successful reading of string from file1.
    if (read2) str2[strcspn(str2, "\n")] = '\0'; // if reading is successful, then replace the last character "\n" from str1 with '\0'.

    while (read1 != NULL && read2 != NULL) // continue reading until one of the file exhausts.
	{
        int cmp = strcmp(str1, str2);

        if (cmp < 0) {
            fprintf(outputFile, "%s\n", str1);// if string from file1 less than string from file2, copy string from file1 to outputfile.
            read1 = fgets(str1,15, file1);// read1 pointer points to next string that is stored  in str1.
            if (read1) str1[strcspn(str1, "\n")] = '\0';// replace a newline character "\n" in  str1 with '\0'-null character.
        } else if (cmp > 0) {
            fprintf(outputFile, "%s\n", str2);
            read2 = fgets(str2,15, file2);
            if (read2) str2[strcspn(str2, "\n")] = '\0';
        } else {
            // str1 == str2, write one of them to the output file and display the common string
            fprintf(outputFile, "%s\n", str1);
            printf("Common string: %s\n", str1);
            commonExists = 1;// indicates common string present in both the files.
            read1 = fgets(str1,15, file1);
            if (read1) str1[strcspn(str1, "\n")] = '\0';
            read2 = fgets(str2,15, file2);
            if (read2) str2[strcspn(str2, "\n")] = '\0';
        }
    }

    // Write the remaining strings from file1, if any
    while (read1 != NULL) {
        fprintf(outputFile, "%s\n", str1);
        read1 = fgets(str1,15, file1);
        if (read1) str1[strcspn(str1, "\n")] = '\0';
    }

    // Write the remaining strings from file2, if any
    while (read2 != NULL) {
        fprintf(outputFile, "%s\n", str2);
        read2 = fgets(str2,15, file2);
        if (read2) str2[strcspn(str2, "\n")] = '\0';
    }

    if (!commonExists) {
        printf("No common strings found.\n");
    }
}

int main() {
    FILE *file1, *file2, *outputFile;

    // Open the first input file
    file1 = fopen("C:/Users/shubha/OneDrive/Desktop/USN1.txt", "r");
    if (file1 == NULL) {
        printf("Could not open file1.txt\n");
        return 1;
    }

    // Open the second input file
    file2 = fopen("C:/Users/shubha/OneDrive/Desktop/USN2.txt", "r");
    if (file2 == NULL) {
        printf("Could not open file2.txt\n");
        fclose(file1);
        return 1;
    }

    // Open the output file
    outputFile = fopen("C:/Users/shubha/OneDrive/Desktop/USN3.txt", "w");
    if (outputFile == NULL) {
        printf("Could not open output.txt\n");
        fclose(file1);
        fclose(file2);
        return 1;
    }

    // Merge the files and display common strings
    mergeFilesAndDisplayCommonStrings(file1, file2, outputFile);

    // Close the files
    fclose(file1);
    fclose(file2);
    fclose(outputFile);

    return 0;
}
