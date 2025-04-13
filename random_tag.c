#include "random_tag.h"
#include <stdlib.h>

Attribute define_attribute(const char *name, const Option *options, int count, int required, float show_probability, int multi_select)
{
    Attribute attr;
    attr.name = name;
    attr.options = options;
    attr.count = count;
    attr.required = required;
    attr.show_probability = show_probability;
    attr.multi_select = multi_select;
    return attr;
}

void generate_random_character(Attribute *attributes, int length)
{
    for (size_t i = 0; i < length; i++)
    {
        const Attribute *attr = &attributes[i];
        if (attr->required || (get_random_probability() <= attr->show_probability))
        {
            if (attr->multi_select)
            {
                int exist = 0;
                for (int j = 0; j < attr->count; j++)
                {
                    if (get_random_probability() <= attr->options[j].probability)
                    {
                        if (exist == 0)
                        {
                            exist = 1;
                            printf("%-5s：", attr->name);
                        }

                        printf("%s ", attr->options[j].name);
                    }
                }

                if (exist == 1)
                {
                    printf("\n");
                }
                continue;
            }
            const Option *selected = select_option(attr->options, attr->count);
            print_attribute(attr, selected);
        }
    }
}

const Option *select_option(const Option *options, int count)
{
    float rand_val = get_random_probability();

    float total = 0.0f;
    for (int i = 0; i < count; i++)
    {
        total += options[i].probability;
    }

    if (total <= 0.0f)
        return &options[0];

    float current = 0.0f;
    float scale = 1.0f / total;
    for (int i = 0; i < count; i++)
    {
        current += options[i].probability * scale;
        if (rand_val <= current)
        {
            return &options[i];
        }
    }

    return &options[count - 1];
}

float get_random_probability(void)
{
    return (float)rand() / RAND_MAX;
}

void print_attribute(const Attribute *attr, const Option *option)
{
    printf("%-5s：%s\n", attr->name, option->name);
}