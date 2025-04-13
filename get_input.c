#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

// Define data type enumeration
typedef enum
{
    TYPE_INT,
    TYPE_DOUBLE
} DataType;

/**
 * Generic input function (supports int/double)
 * @param value    Pointer to store the input result (must point to int or double)
 * @param type     Data type (TYPE_INT or TYPE_DOUBLE)
 * @param prompt   Input prompt message (e.g., "Please enter an integer:")
 * @return         true if input is successful, false otherwise
 */
bool get_input(void *value, DataType type, const char *prompt)
{
    char buffer[256];
    char *endptr;
    bool success = false;

    while (!success)
    {
        // Display the prompt message
        printf("%s", prompt);

        // Read the input line
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            // User pressed Ctrl+D (EOF) or an error occurred
            return false;
        }

        // Remove the trailing newline character (if any)
        buffer[strcspn(buffer, "\n")] = '\0';

        // Parse the input based on the type
        switch (type)
        {
        case TYPE_INT:
        {
            long num = strtol(buffer, &endptr, 10);
            if (endptr == buffer)
            {
                printf("Error: The input is not an integer!\n");
            }
            else if (*endptr != '\0')
            {
                printf("Error: The input contains non-numeric characters!\n");
            }
            else if (num < INT_MIN || num > INT_MAX)
            {
                printf("Error: The integer is out of range!\n");
            }
            else
            {
                *(int *)value = (int)num;
                success = true;
            }
            break;
        }

        case TYPE_DOUBLE:
        {
            double num = strtod(buffer, &endptr);
            if (endptr == buffer)
            {
                printf("Error: The input is not a floating-point number!\n");
            }
            else if (*endptr != '\0')
            {
                printf("Error: The input contains non-numeric characters!\n");
            }
            else
            {
                *(double *)value = num;
                success = true;
            }
            break;
        }

        default:
            printf("Error: Unknown data type!\n");
            return false;
        }

        if (!success)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    }

    return true;
}