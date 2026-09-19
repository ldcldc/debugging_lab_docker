
#include <stdio.h>
#include <string.h>


static void append_field(char *buf, size_t cap, size_t *len, const char *field, char sep) {
    if (cap == 0 || *len >= cap - 1)
        return; 
    if (*len > 0)
        buf[(*len)++] = sep;

    size_t space_left = cap - *len - 1; 
    size_t flen = strlen(field);

    if (flen > space_left)
        flen = space_left;

    for (size_t i = 0; i < flen; i++)
        buf[(*len)++] = field[i];         

    buf[*len] = '\0';
}

static void append_field__(char *buf, size_t cap, size_t *len, const char *field, char sep) {
    int len_zero = 0;
    size_t flen = strlen(field);

    if (*len > 0 && *len + 1 != cap){
        if(*len != cap)
            buf[(*len)++] = sep; 
        len_zero = 1;
    }
    if (*len + flen + len_zero >= cap) 
        flen = cap - 1 - *len;

    for (size_t i = 0; i < flen; i++)
        buf[(*len)++] = field[i];         
    buf[*len] = '\0';
}

static void build_record(char *rec, size_t cap) {
    const char *fields[] = {
        "id=1042", "name=Jonathan", "department=Engineering", "role=maintainer",
    };
    int n = (int)(sizeof(fields) / sizeof(fields[0]));

    size_t len = 0;
    rec[0] = '\0';
    for (int i = 0; i < n; i++) {
        append_field(rec, cap, &len, fields[i], '|');   
    }
}

int main(void) {
    char rec[24];                         

    build_record(rec, sizeof rec);        

    printf("record = %s\n", rec);
    return 0;                            
}
