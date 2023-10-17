#include<stdio.h>
typedef struct node
{
char data;
struct node* next ;
} node ;

typedef node* list ;

typedef struct  lnode 
{
struct lnode* next ;
list l;
} lnode;

typedef struct queue 
{
lnode* rear,*front;
}queue;

typedef struct stack
{
lnode* top ;
}st ;

void initq (queue*q);
int isempty (queue* q);
lnode* newnode (list*k);
void enq (queue* q ,list k );
node* dq (queue *q);
void display (queue q);
void insertnode(list*l,char key);
void initlist (list*l);
void printlist (list l);
void printinfix (char infix[]);
int is_space (char c);
int is_symb (char c);
void intoq (char*filename,queue*q);

void init (st* s);
int is_empty(st *s);
int is_full (st* s);
void push (st*s,list i);
node* pop (st*s);
void displayst(st*s);
void intopost (queue i,queue*p );
void eval (queue* p , st*s);
void printans (st s);
int precedence (char c);
node* add(node*a,node*b);
node* subs(node*a,node*b);
node* divsn(node*a,node*b);
node* mul(node*a,node*b);
node* power(node*a,node*b);
void revl(list*l);
int length (list l);
int comparelist(node*a,node*b);
node* creatend (char c);
int is_decimal(node*a);
void remove_decimal(node*a);
node* count_dig (node*a);
void insert_decimal(node*a,node*count);
void add_zeros(node*a,node*count);
