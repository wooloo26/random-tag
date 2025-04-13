#ifndef RANDOM_ROLE_H
#define RANDOM_ROLE_H

#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define DEFINE_ATTRIBUTE(name, options, required, show_probability, multi_select) \
    {name, options, ARRAY_SIZE(options), required, show_probability, multi_select}

typedef struct
{
    const char *name;
    float probability;
} Option;

typedef struct
{
    const char *name;
    const Option *options;
    int count;
    int required;
    float show_probability;
    int multi_select;
} Attribute;

float get_random_probability(void);
void print_attribute(const Attribute *attr, const Option *option);
const Option *select_option(const Option *options, int count);
Attribute define_attribute(const char *name, const Option *options, int count, int required, float show_probability, int multi_select);
void generate_random_character(Attribute *attributes, int length);

#endif // RANDOM_ROLE_H
