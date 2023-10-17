#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct node{
  char data;
  struct node* next ;
} node ;

typedef node* list ;

typedef struct  lnode {
  struct lnode* next ;
  list l;
} lnode;

typedef struct queue {
  lnode* rear,*front;
} queue;

void initq (queue* q ){
    q->front =NULL;
    q->rear = NULL;
}

int isqempty (queue* q){
    if(q->front==NULL){
        return 1;
    }
    return 0 ;
}
node* creatend (char c){
    node*nn=(node*)malloc(sizeof(node));
    if (!nn) return NULL ;
    else{
         nn->next=NULL;
         nn->data=c;
    }
    return nn ;
}

lnode* newnode (list k){
    lnode* nn = (lnode*)malloc(sizeof(lnode));
    if(!nn){
        return 0 ;
    }
    else{
        nn->next=NULL;
        nn->l=k;
    }
    return nn ;
}

void enq (queue* q,list k){
   lnode* temp = newnode(k);
    if(!temp){
        return;
    }
    if(q->front==NULL){
        q->front=q->rear=temp;
	return;
    }
    else{
        q->rear->next=temp;
        q->rear=temp;
	return;
    }
    
}

node* dq (queue*q) {
    node* ele ;
    lnode* temp ;
    if(q->front==NULL){
        return NULL ;
    }
    temp = q->front;
    ele = temp->l;
    q->front=temp->next;
    if(q->front==NULL){
        q->rear=NULL;
    }
    free(temp);
    return ele;
}

void display(queue q){
    if(q.front==NULL){
        return;
    }
    lnode*temp = q.front;
    printf("queue :\n ");
    int i = 0;
         while(temp){
	       printf("ele %d :",i);
               node*t=temp-> l;
	       node*p=t;
	 while(p){
	       printf("%c-",p->data);
	       p=p->next;
	 }
	 printf("N");
	 i++;
	 printf("\n");
         temp=temp->next;
    }
    return;
}

typedef struct stack{
   lnode* top ;
}st ;

void init (st* s){
    s->top=NULL;
}
int is_empty(st *s){
    if (s->top==NULL){
        return 1;
    }
    else return 0 ;
} 
int is_full (st* s) {
    lnode* nn = (lnode*)malloc(sizeof(lnode));
    if(nn==NULL){
        return 1 ;
    }
    else {
        return 0;
    }
}

void push (st*s,list i){
    if(is_full(s)) return;
     lnode* nn = newnode(i);
     nn->next=s->top;
     nn->l=i;
     s->top=nn;    
}

node* pop (st*s){
    lnode *temp;
    node* ele ;
    if (is_empty(s)) {
        return NULL;
    }
    temp = s->top;
    ele=s->top->l;
    s->top=temp->next;
    free(temp);
    temp=NULL;
    return ele ;
}


void displayst(st*s){
    if (s->top==NULL){
         return ;
    }
    printf("stack: ");
    int i = 0 ;
    lnode* temp;
    temp=s->top;
    node*p;
    while(temp){
         p=temp->l;
         printf("ele %d:",i);
         while (p){
             printf ("%c-",p->data);
             p=p->next;
         }    
         printf("n");
         i++;
         printf("\n");
         temp=temp->next;
    }
    return;
    
}
    
void insertnode (list* l , char key ){
        node* nn = (node*)malloc(sizeof(node));
	if(!nn){
           return ; 
	}
	nn->next = NULL;
	nn->data = key ;

       	if (!(*l)){
	   *l=nn;
	   return;
	}
	node*temp = *l;
	while(temp->next){
	   temp= temp->next;
	}
        temp->next=nn;
	return;
}

void initlist (list*l){
       *l=NULL;
       return ;
}
void printlist (list l){
       node*p=l;
       if(!p){
          return;
       }
       printf("list :");
       while (p){
          printf("%c-",p->data);
          p=p->next;
       }
       printf("N");
       return ;

}
void printinfix (char infix[]){
      int i = 0 ;
      printf("expn : ");
      while(infix[i]!='\0'){
           printf("%c",infix[i]);
           i++;
      }
}
int is_space (char c){
     if (c==' ' || c == '\t'){
          return 1;
     }
     else {
           return 0 ;
     }    
}

int is_symb (char c ){
           switch (c){
                case '+' :
                //case '-' :
                case '*' :
                case '/' :
                case '^' :
                case '(' :
                case ')' :
                         return 1;
                default :
                         return 0 ;    
            }
}



void intoq (char*filename,queue*q){
          char c;
          double i = 0;
         list l ; 
         initlist(&l);
         char d;
          FILE*fp=fopen (filename,"r");
          if(!fp)return; 
          while (fscanf(fp,"%c",&c)!=EOF){
                  if ((c>='0' && c<='9')||c=='.') {
                     while ((c>='0' && c<='9')||c=='.'){
                             insertnode (&l,c);
                             d=c;
                             i++;
                            if( fscanf(fp,"%c",&c)==EOF){
                                       enq(q,l);
                                       return;
                             }
                     }                 
                     enq(q,l);
                     l=NULL;    
                  }
		  if (d=='-'&&c=='('){
                           insertnode(&l,'1');
                           enq(q,l);
                           l=NULL;
                           insertnode(&l,'*');
                           enq(q,l);
                           l=NULL;
                  }

              
                 if (is_space(c)){
                     d=c;
                     i++;
                     continue; 
                 } 
                 if (is_symb (c)){         
                     insertnode(&l,c);
                     d=c;
                     i++;
                     enq (q,l);
                     l=NULL;
                  }  
                  if(c=='-'){
                     if (i==0){
                           insertnode(&l,c);
                           d=c;     
                     }
                     else if (is_symb(d)){
                           insertnode(&l,'-');
                           d=c;
                     }
                     else{
                           insertnode(&l,'+');
                           enq(q,l);
                           l=NULL;
                           insertnode(&l,'-');
                           d=c;
                    }
                     
                } 
 
               i++;            
               }   
        fclose(fp);
        return ;         
}

int precedence (char c) {
             switch (c){
                    case '^':
                            return 3;
                    case '/':
                    case '*':
                            return 2;
                    case '+':
                  //  case '-':
                            return 1;
                    default :
                            return 0; 
                            
                  
             }
}           

void intopost (queue i,queue* p){ 
          st s ;
          init (&s);
          lnode* temp ;
          temp = i.front;
          char symb ;
          char symbst;
          node* eleinq;
          node* eleinst;
          node* t ;
          while (temp) {
                symb = temp->l->data;
                eleinq= temp->l;
                switch (symb) {
                     case '(':
                             push(&s,eleinq);
                             break;
                     case ')':  
                            t=pop(&s);
                             symbst=t->data; 
                             while (symbst!='('){
                                     enq(p,t);
                                     t=pop(&s);
                                     symbst=t->data;
                              } 
                              break;
                     case '+':
                   //  case '-':
                     case '*':
                     case '/':
                     case '^':
                             if (is_empty(&s)){
                                     push(&s,eleinq);
                                     break;
                             }
                             else{
                                     symbst=s.top->l->data;
                                     while ((!is_empty(&s))&&((precedence(symbst))>=(precedence(symb)))){
                                          eleinst=pop(&s);
                                          enq(p,eleinst);
                                          if(!is_empty(&s)){
                                          symbst=s.top->l->data;
                                          }
                                      }
                                      push(&s,eleinq);
                                      break;
                             }
                     default :
                             enq(p,eleinq);
                             break;
                             
                 }
                 temp=temp->next;          
           }
           while(!is_empty(&s)){
                     t=pop(&s);
                     enq(p,t);
           }
           return ;              
}
int length (list l){
     int count=0 ;
     node*p=l;
     while(p){
           count++;
           p=p->next;
      }
     return count;     
}

void revl (list*l){
       if (!l ||!((*l)->next)){
          return;    
        }
       node*p =*l;
       node*q=p->next;
       node*temp=NULL;
       p->next=NULL;
       while(q){
             temp=q->next;
             q->next=p;
             p=q;
             q=temp;  
       }
       *l=p;
       return;
}
int comparelist (node*a,node*b){
      node*p=a;
      node*q=b;
      int f,k;
      if (length(a)>length(b)){
            return 1;
      }
      else if (length(a)<length(b)){
            return -1 ;
     }
     else{  
            
            while (p&&q){
               f=p->data-'0';
               k=q->data-'0';
               if (f>k){
                     return 1;
                }
               else if (f<k){
                     return -1;
               }
               else {
                      p=p->next;
                      q=q->next;
               }
             }
      return 0;
     }       
}

node* subs (node*a,node*b){
     int d1,d2,bor=0,ans;
     node*p,*q;
     list c;
     initlist(&c);
     char dig;
     revl(&a);
     revl(&b);
     p=a,q=b;
     while(p && q){
         ans=0;
         d1=p->data-'0';
         d2=q->data-'0';
         if(d1<d2){
                ans=bor+10+d1-d2;
                bor=-1;
         }
         else{
               ans=bor+d1-d2;
               bor=0;
         } 
         dig=(char)(ans+48);
         insertnode(&c,dig);
         p=p->next;
         q=q->next;
     }          
     while (p){
          if (p->data-'0'==0 && bor==-1){
               ans=10+bor;
               bor=-1;
               dig=(char)(ans+48);
              insertnode(&c,dig);
               p=p->next;
          }
          else{
          
               d1=p->data-'0';
               ans=d1+bor;
               bor=0;
               dig=(char)(ans+48);
               insertnode(&c,dig);
               p=p->next;
          }
      }
      revl(&a);
      revl(&b);
      revl(&c);
      node*t;
      while(c->data-'0'==0&&c->next){
      t = c;
      c=t->next;
      free(t);   
      }       
      return c ;         
}

int is_decimal(node*a){
          node*p;
          p=a;
          while(p){
              if (p->data=='.'){
                    return 1;
              }
              p=p->next;
          }
          return 0 ;
}
void  remove_decimal (node*a){
         node*p = a;
         node*q;
         while(p->data!='.'){
               q=p;
               p=p->next;
         }
        q->next=p->next;
        p->next=NULL;
        free(p);
        
       
}
void insert_decimal (node*a,node*count){
             list one;
             initlist(&one);
             insertnode(&one,'1');
             list zero; 
             initlist(&zero);
             insertnode(&zero,'0');
             revl(&a);
             node*p=a;
             node*q=NULL;
             node*nn = creatend('.');
                   
             while (comparelist(count,zero)==1){
                    count=subs(count,one);
                    q=p;
                    p=p->next;     
             }
            if (!q){
                  revl(&a);
                  return ;
             }
             q->next=nn;
             nn->next=p;
             revl(&a);
             return;
}
void add_zeros (node*a,node*count){
             list one;
             initlist(&one);
             insertnode(&one,'1');
             list zero; 
             initlist(&zero);
             insertnode(&zero,'0');
             node*p=a;
             node*q;
              while(comparelist(count,zero)==1){
                    insertnode(&a,'0');
                    count=subs(count,one);
             }
             return ;

        
}




node* count_dig(node*a);

node* add(node*a,node*b){

               list count, count1,count2,digits;
               initlist(&count1);
               initlist(&count2);
               initlist(&count);
               initlist(&digits);
               insertnode(&digits,'0');
               node*n1=NULL,*n2=NULL,*n3=NULL,*t=NULL;
               if (is_decimal(a)&&is_decimal(b)){
                     count1=count_dig(a);
                     count2=count_dig(b);
                     if(comparelist(count1,count2)==1){
                             count=subs(count1,count2);
                             digits=count1;
                             add_zeros(b,count);
                             remove_decimal(a);
                             remove_decimal(b);
                     }
                    else if(comparelist(count1,count2)==-1){
                             count=subs(count2,count1);
                             digits=count2;
                             add_zeros(a,count);
                             remove_decimal(a);
                             remove_decimal(b);
                     }
                     else{
                             remove_decimal(a);
                             remove_decimal(b);
                             digits=count1;
                     }            
               }

               if (is_decimal(a)==1&&is_decimal(b)!=1){
                        count1=count_dig(a);
                        digits=count1;
                        add_zeros(b,count1);
                       remove_decimal(a);
              }
              if (is_decimal(a)!=1&&is_decimal(b)==1){
                        count2=count_dig(b);
                        digits=count2;
                        add_zeros(a,count2);
                        remove_decimal(b);
              }

               if (a->data=='-'&& b->data=='-'){
                   n1=a->next;
                   n2=b->next;
                   n3=add(n1,n2);
                   t=creatend('-');
                   t->next=n3;
                   n3=t;   
                    insert_decimal(n3,digits);
                   return n3;
               }
                if (a->data=='-'&& b->data!='-'){
                  n1=a->next;
                  n2=b;
                   
                         if(comparelist(n1,n2)==1){
                               n3=subs(n1,n2);
                               t=creatend('-');
                               t->next=n3;
                               n3=t;
                               insert_decimal(n3,digits);
                               return n3;
                          }
                         else {
                               n3=subs(n2,n1);
                                insert_decimal(n3,digits);
                               return n3;
                         }
                   }
                   if (a->data!='-'&&b->data=='-'){
                       n1=a;
                       n2=b->next;
                       if (comparelist(n2,n1)==1){
                               n3=subs(n2,n1);
                               t=creatend('-');
                               t->next=n3;
                               n3=t;
                               insert_decimal(n3,digits);
                               return n3;
                       }
                       else {
                               n3=subs(n1,n2);
                               insert_decimal(n3,digits);
                               return n3;
                       }
                   }

               revl(&a);
               revl(&b);
               int sum;
               int car=0;
               int d1,d2;
               char dig;
               list c;
               initlist(&c);
               node*p;
               node*q;
               p=a;
               q=b;
               while (p && q){
                  sum=0;
                  d1=(p->data)-'0';
                  d2=(q->data)-'0';
                  sum=(d1+d2+car)%10;
                  car=(d1+d2+car)/10;
                  dig=(char)(sum+48);
                  insertnode(&c,dig);
                  p=p->next;
                  q=q->next;    
               }
               while(p){ 
                  sum = 0;
                  d1=(p->data)-'0';
                  sum=(d1+car)%10;
                  car=(d1+car)/10;
                  dig=(char)(sum+48);
                  insertnode(&c,dig);
                  p=p->next;         
               }
               while (q){
                  sum = 0;
                  d2=(q->data)-'0';
                  sum=(d2+car)%10;
                  car = (d2+car)/10;
                  dig=(char)(sum+48);
                  insertnode(&c,dig);
                  q=q->next;
               }
               if (car){
                   dig=(char)(car+48);
                   insertnode(&c,dig);
               }
               revl(&c);
               revl(&a);
               revl(&b);
               insert_decimal(c,digits);
               return c;
               
}
node* count_dig (node*a){
        node*count;
        node*one;
        initlist(&one);
        insertnode(&one,'1');
        initlist(&count);
        insertnode(&count,'0');
        node*p=a;
        while (p->data!='.'){
               p=p->next;
        }        
        p=p->next;
        while (p){
             count=add(count,one);
             p=p->next;
        }
        return count;
 
}


node* mul(node*a,node*b){
           
               list count1,count2,digits;
               initlist(&count1);
               initlist(&count2); 
               initlist(&digits);
               insertnode(&digits,'0');
             if (is_decimal(a)&&is_decimal(b)){
                     count1=count_dig(a);
                     count2=count_dig(b);
                     digits=add(count1,count2);
                     remove_decimal(a);
                     remove_decimal(b);
             }
             if (is_decimal(a)!=1&&is_decimal(b)==1) {
                    count2=count_dig(b);
                    digits=count2;
                    remove_decimal(b);
            }
             if (is_decimal(a)==1&&is_decimal(b)!=1){
                      digits=count_dig(a);
                      remove_decimal(a);
            }
           
            node* n1=NULL,*n2=NULL,*n3=NULL,*t=NULL;
            if (a->data=='-'&&b->data=='-'){
                  n1 = a->next;
                  n2 = b->next;
                  n3=mul(n1,n2);
                  insert_decimal(n3,digits);
                  return n3;
            }
            if (a->data=='-'&&b->data!='-'){
                 n1=a->next;
                 n2=b;
                 n3=mul(n1,n2);
                 t=creatend('-');
                 t->next=n3;
                 n3=t;                 
                 insert_decimal(n3,digits);
                 return n3;
            }
            if (a->data!='-'&&b->data=='-'){
                 n1=a;
                 n2=b->next;
                 n3=mul(n1,n2);
                 t=creatend('-');
                 t->next=n3;
                 n3=t;
                 insert_decimal(n3,digits);
                 return n3;       
            }
            node*p=NULL,*q=NULL;
            list mul;
            initlist(&mul);
            insertnode(&mul,'0');
            list count;
            initlist(&count);
            insertnode(&count,'0');         
            list one;
            initlist(&one);
            insertnode(&one,'1');
            while (comparelist(count,b)!=0){
                    // p=mul;
                    // q=count;
                     count=add(count,one);
                    // free(q);
                     mul=add(mul,a);
                    // free(p);
                     
            }
            insert_decimal(mul,digits);
            return mul;      
}

node* divsn (node*a,node*b){
         list count, count1,count2,digits;
               initlist(&count1);
               initlist(&count2);
               initlist(&count);
               initlist(&digits);
                if (is_decimal(a)&&is_decimal(b)){
                     count1=count_dig(a);
                     count2=count_dig(b);
                     if(comparelist(count1,count2)==1){
                             count=subs(count1,count2);
                             digits=count1;
                             add_zeros(b,count);
                             remove_decimal(a);
                             remove_decimal(b);
                     }
                    else if(comparelist(count1,count2)==-1){
                             count=subs(count2,count1);
                             digits=count2;
                             add_zeros(a,count);
                             remove_decimal(a);
                             remove_decimal(b);
                     }
                     else{
                             remove_decimal(a);
                             remove_decimal(b);
                             digits=count1;
                     }            
               }
           
        
               if (is_decimal(a)==1&&is_decimal(b)!=1){
                        count1=count_dig(a);
                        digits=count1;
                        add_zeros(b,count1);
                       remove_decimal(a);
              }
              if (is_decimal(a)!=1&&is_decimal(b)==1){
                        count2=count_dig(b);
                        digits=count2;
                        add_zeros(a,count2);
                        remove_decimal(b);
              }

               

         node* n1=NULL,*n2=NULL,*n3=NULL,*t=NULL;
           /**if (b->data=='0'){
               n3=NULL;
               return n3;
            }**/

            if (a->data=='-'&&b->data=='-'){
                  n1 = a->next;
                  n2 = b->next;
                  n3=divsn(n1,n2);
                  return n3;
            }
            if (a->data=='-'&&b->data!='-'){
                 n1=a->next;
                 n2=b;
                 n3=divsn(n1,n2);
                 t=creatend('-');
                 t->next=n3;
                 n3=t;
                 return n3;
            }
            if (a->data!='-'&&b->data=='-'){
                 n1=a;
                 n2=b->next;
                 n3=divsn(n1,n2);
                 t=creatend('-');
                 t->next=n3;
                 n3=t;
                 return n3;       
            }
          
         list q;
         initlist(&q);
         list r;
         initlist (&r);
         list one;
         initlist(&one);
         insertnode(&one,'1');
         r=a;
         insertnode(&q,'0');
         list zero;
         initlist(&zero);
         insertnode(&zero,'0');
         if (comparelist(a,b)==-1){
           return zero;
         }
         while (comparelist(r,b)!=-1){
                        q=add(q,one);
                        r=subs(r,b);
        }
        return q;   
}
     
node* power (node*a,node*b){
          list p;
          initlist (&p);
          list count;
          initlist (&count);
          insertnode(&count,'1');
          p=a;
          list one ;
          initlist (&one);
          insertnode(&one,'1');
          if(b->data=='0'){
                return one;
          }
          while (comparelist(count,b)!=0){
                p=mul(p,a);
                count=add(count,one);  
          }
          return p;
}

void eval (queue*p,st*s ){
         lnode*temp;
         node*t;
         node*n1;
         node*n2;
         char symb ;
         node*c; 
         temp = p->front;
         while (temp){
              if (!(is_symb(temp->l->data))){
                 temp=temp->next;
                 t = dq(p);
                 push(s,t);     
              }
              else {
                symb = temp->l->data;
                temp=temp->next;
                n1= pop(s);
                n2= pop (s);
                t=dq(p);
                switch (symb){  
                            case '+':
                                    c=add(n1,n2);
                                    push(s,c);
                                    
                                    break;
                            case '-':
                                    c=subs(n2,n1);
                                    push(s,c);
                                    break;

                            case '*':
                                    c=mul(n1,n2);
                                    push(s,c);
                                   break;  
                            case '/':
                                    c=divsn(n2,n1);
                                    if (c==NULL){
                                            printf("div by 0 undefined");
                                            return;
                                    } 
                                    push(s,c);
                                    break;
                            case '^':
                                    c= power(n2,n1);
                                    push(s,c);
                                    break;
                                    
                }    
           
             } 
                   
         }
         return;
}

void printans(st s){
               lnode* temp = s.top;
               node*p=temp->l;
               while (p){
                     printf("%c",p->data);
                     p=p->next;
               }
               return;
}


