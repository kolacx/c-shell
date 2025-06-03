#ifndef __USERS_H
#define __USERS_H

struct user_s {
    char *name;
    int age;
};

typedef struct user_s user_t;

extern void init_users(void);
extern void show_user(void);
extern void del_user(char *name);
extern user_t *add_user(char *name, int age);

extern user_t *add_user_to_list(user_t *user);


#endif
