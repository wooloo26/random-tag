#ifndef GET_INPUT_H
#define GET_INPUT_H

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
bool get_input(void *value, DataType type, const char *prompt);

#endif // GET_INPUT_H
