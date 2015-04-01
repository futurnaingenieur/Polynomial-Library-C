#include <Polynomial.h> /* all other includes are present in the file "Polynomial.h" */

/*-------------------------------------------------------------*/

Monomial createMonomial(float new_coeff,int new_degree) /* FUNCTION WHICH CREATES A NEW MONOMIAL */
{
    Monomial m; /* declaration of the monomial we want to return */
    m.coeff=new_coeff; /* with these 2 lines, it defines both elements of the "Monomial" structura */
    m.degree=new_degree;
    return m; /* it returns the monomial */
}

/*-------------------------------------------------------------*/

Polynomial createPolynomial(char *filepath)
{
    FILE *file=NULL;
    int a;
    Polynomial l=init(l);
    Monomial m;
    char sign='+';
    char c='0';
    int pos;
    int e=0,d=0;

    file=fopen(filepath,"r");
    if(file!=NULL)
    {
        rewind(file);
        sign=fgetc(file);
        if(sign!='-' && sign!='+')
        {
            rewind(file);
        }
        while(sign!=-1)
        {

            if(fgetc(file)=='x')
            {
                m.coeff=1;
                if(sign=='-')
                {
                    m.coeff=-m.coeff;
                }
                fseek(file,-1,SEEK_CUR);
                c=fgetc(file);
            }
            else
            {
                fseek(file,-1,SEEK_CUR);
                pos=ftell(file);
                while(c!='.' && c!='+' && c!='-' && c!=EOF)
                {
                    c=fgetc(file);
                }
                if(c=='.')
                {
                    e=0;
                    d=0;
                    fseek(file,pos,SEEK_SET);printf("%d\n",pos);
                    a=fscanf(file,"%d.%d",&e,&d);

                    m.coeff=e+d/pow10(sizeint(d));
                }
                else
                {
                    fseek(file,pos,SEEK_SET);
                    a=fscanf(file,"%f",&(m.coeff));
                }
                if(sign=='-')
                {
                    m.coeff=-m.coeff;
                }
                c=fgetc(file);
            }
            if(c=='x')
            {
                c=fgetc(file);
                if(c=='^')
                {
                    a=fscanf(file,"%d",&(m.degree));
                    sign=fgetc(file);
                }
                else
                {
                    m.degree=1;
                    sign=c;
                }
            }
            else
            {
                m.degree=0;
                sign=c;
            }
            l=addMonomial(l,m);
        }
    }
    a++;
    return l;
}

/*-------------------------------------------------------------*/

Polynomial addMonomial(Polynomial l,Monomial new_m)
{
    ElemOfPolynomial *newel=(ElemOfPolynomial*) malloc(sizeof(ElemOfPolynomial));
    newel->m=new_m;
    if(l.head==NULL)
    {
        l=init(l);
        newel->next=NULL;
        newel->prev=NULL;
        l.head=newel;
        l.tail=newel;
        l.higherDegree=newel->m.degree;
        l.numberMonomials++;
    }
    else
    {
        ElemOfPolynomial *p=l.head;
        while(new_m.degree>p->m.degree && p->next!=NULL)
        {
            p=p->next;
        }
        if(p->next!=NULL || new_m.degree<=p->m.degree)
        {
            if(new_m.degree==p->m.degree)
            {
                p->m.coeff+=new_m.coeff;
            }
            else
            {
                if(p->prev!=NULL)
                {
                    newel->next=p;
                    newel->prev=p->prev;
                    p->prev->next=newel;
                    p->prev=newel;
                }
                else
                {
                    newel->next=p;
                    newel->prev=NULL;
                    p->prev=newel;
                    l.head=newel;
                }
                l.numberMonomials++;
            }
        }
        else
        {
            newel->next=NULL;
            newel->prev=p;
            p->next=newel;
            l.tail=newel;
            l.higherDegree=new_m.degree;
            l.numberMonomials++;
        }
    }
    return l;
}

/*-------------------------------------------------------------*/

Polynomial removeMonomial(Polynomial l,int taken_degree) /* FUNCTION WHICH REMOVES ONE POLYNOMIAL'S ELEMENT KNOWN WITH HIS DEGREE */
{
    if(l.head!=NULL && l.tail!=NULL) /* if the polynomial is not empty */
    {
        ElemOfPolynomial *p=l.head;
        while(p->m.degree<taken_degree && p->next!=NULL)
        {
            p=p->next; /* it traverses the polynomial until it meets the element with the known degree */
        }
        if(p->m.degree==taken_degree) /* if there is one element with the known degree */
        {
            if(p->prev!=NULL && p->next!=NULL) /* it removes it if the element is between 2 others elements */
            {
                ElemOfPolynomial *s=p->prev;
                s->next=p->next;
                p->next->prev=s;
                free(p);
            }
            if(p->prev==NULL && p->next!=NULL) /* here, if the element is the first of the polynomial */
            {
                l.head=p->next;
                p->next->prev=NULL;
                free(p);
            }
            if(p->next==NULL && p->prev!=NULL) /* here, if it is the last of the polynomial */
            {
                l.higherDegree=p->prev->m.degree;
                l.tail=p->prev;
                p->prev->next=NULL;
                free(p);
            }
            if(p->next==NULL && p->prev==NULL) /* here, if the polynomial had just one element and it has the known degree */
            {
                l=init(l);
            }
        }
    }
    return l;
}

/*-------------------------------------------------------------*/

Polynomial sum(Polynomial p1,Polynomial p2) /* FUNCTION WHICH ADDS ONE POLYNOMIAL BY AN OTHER */
{
    Polynomial l1=copyPolynomial(p1); /* it creates the polynomial equal to the sum of both present in parameters, it assigns it the first */
    Polynomial l2=copyPolynomial(p2);
    if(l2.head!=NULL) /* if the second polynomial is not empty */
    {
        ElemOfPolynomial *p=l2.head; /* it creates a new pointer of the head of the second polynomial */
        while(p!=NULL) /* it adds each element of the second polynomial in the final polynomial */
        {
            l1=addMonomial(l1,p->m); /* the sum is operated in the function "addMonomial" */
            p=p->next;
        }
    }
    if(l1.head!=NULL) /* that part removes again the elements containing null coefficients */
    {
        ElemOfPolynomial *p2=l1.head;
        while(p2!=NULL)
        {
            if(p2->m.coeff==0)
            {
                l1=removeMonomial(l1,p2->m.degree);
            }
            p2=p2->next;
        }
    }
    return l1;
}

/*-------------------------------------------------------------*/

Polynomial sub(Polynomial p1,Polynomial p2) /* FUNCTION WHICH SUBSTRACT ONE POLYNOMIAL BY AN OTHER */
{
    Polynomial newP=copyPolynomial(p1); /* it's the same concept that the function "sum" */
    Polynomial l2=copyPolynomial(p2);
    Monomial newM; /* it creates a new monomial */
    if(l2.head!=NULL)
    {
        ElemOfPolynomial *p=l2.head;
        while(p!=NULL)
        {
            newM.degree=p->m.degree; /* the monomial is equal to the monomials of each elements of the second polynomial but : */
            newM.coeff=-p->m.coeff; /* now, it adds the opposite of each element of the second polynomial */
            newP=addMonomial(newP,newM); /* it adds the first monomial by the opposite of the second */
            p=p->next;
        }
    }
    if(newP.head!=NULL) /* that parts remove one element if his element is equal to 0 */
    {
        ElemOfPolynomial *p2=newP.head;
        while(p2!=NULL)
        {
            if(p2->m.coeff==0)
            {
                newP=removeMonomial(newP,p2->m.degree);
            }
            p2=p2->next;
        }
    }
    return newP;
}

/*-------------------------------------------------------------*/

Polynomial mul(Polynomial p1,Polynomial p2) /* FUNCTION WHICH MULTIPLIES ONE POLYNOMIAL BY AN OTHER */
{
    Polynomial l1=copyPolynomial(p1);
    Polynomial l2=copyPolynomial(p2);
    Polynomial newP=init(newP); /* it creates the polynomial equal to the multiplication of the first and the second polynomial */
    Monomial newM; /* it creates a provisory monomial */
    if(l2.head!=NULL && l1.head!=NULL)
    {
        ElemOfPolynomial *p1=l1.head;
        ElemOfPolynomial *p2=l2.head;
        while(p1!=NULL)
        {
            p2=l2.head;
            while(p2!=NULL)
            {
                newM=createMonomial(p1->m.coeff*p2->m.coeff,p1->m.degree+p2->m.degree);
                newP=addMonomial(newP,newM);
                p2=p2->next;
            }
            p1=p1->next;
        }
    }
    return newP;
}

/*-------------------------------------------------------------*/

Polynomial divP(Polynomial p1,Polynomial p2)
{
    Polynomial l1=copyPolynomial(p1);
    Polynomial l2=copyPolynomial(p2);
    Polynomial c=copyPolynomial(l1);
    Polynomial q=init(q);
    Polynomial s=init(s);
    Polynomial t=init(t);
    Monomial m;
    while(c.higherDegree>=l2.higherDegree && c.higherDegree>=0)
    {
        m.coeff=c.tail->m.coeff/l2.tail->m.coeff;
        m.degree=c.tail->m.degree-l2.tail->m.degree;
        q=addMonomial(q,m);
        t=addMonomial(t,q.head->m);
        s=mul(l2,t);
        t=init(t);
        c=sub(c,s);
        if(c.head!=NULL)
        {
            c.higherDegree=c.tail->m.degree;
        }
        else
        {
            c.higherDegree=-1;
        }
    }
    return q;
}

/*-------------------------------------------------------------*/

Polynomial mDerivative(Monomial m,int n)
{
    int i;
    Polynomial newP=init(newP);
    newP=addMonomial(newP,m);
    for(i=0;i<n;i++)
    {
        newP=derivatePolynomial(newP);
    }
    return newP;
}

/*-------------------------------------------------------------*/

Polynomial pDerivative(Polynomial l,int n)
{
    int i;
    Polynomial newP=copyPolynomial(l);
    for(i=0;i<n;i++)
    {
        newP=derivatePolynomial(newP);
    }
    return newP;
}

/*-------------------------------------------------------------*/

Polynomial gcd(Polynomial l1,Polynomial l2)
{
    Polynomial a=l1;
    Polynomial b=l2;
    Polynomial r=remainder(l1,l2);
    while(r.head!=NULL)
    {
        a=copyPolynomial(b);
        b=copyPolynomial(r);
        r=remainder(a,b);

    }
    return b;
}

/*-------------------------------------------------------------*/

void printMonomial(Monomial m)
{
    if(m.degree>=0)
    {
        if(m.degree==0)
        {
            printf("%.1f ",m.coeff);
        }
        else if(m.degree==1)
        {
            printf("%.1fx ",m.coeff);
        }
        else
        {
            printf("%.fx^%d ",m.coeff,m.degree);
        }
    }
}

/*-------------------------------------------------------------*/

void printPolynomial(Polynomial l) /* FUNCTION WHICH DISPLAYS A POLYNOMIAL */
{
    if(l.head!=NULL) /* if the polynomial is not empty */
    {
        ElemOfPolynomial *p=l.head;  /* it creates a provisory pointer which begins in the head/beginning of the polynomial */
        while(p!=NULL) /* it prints all the elements one by one until it reaches the tail/end of the polynomial */
        {
            if(p->next!=NULL) /* if there is others elements after the actual, it displays a "+" */
            {
                if(p->m.degree==0)
                {
                    printf("%.1f + ",p->m.coeff); /* if the degree is 0, it just prints the coefficient */
                }
                else if(p->m.degree==1)
                {
                    if(p->m.coeff!=1 && p->m.coeff!=-1)
                    {
                        printf("%.1fx + ",p->m.coeff);
                    }
                    else if(p->m.coeff==-1)
                    {
                        printf("-x + ");
                    }
                    else
                    {
                        printf("x + ");
                    }
                }
                else
                {
                    if(p->m.coeff!=1 && p->m.coeff!=-1)
                    {
                        printf("%.1fx^%d + ",p->m.coeff,p->m.degree);
                    }
                    else if(p->m.coeff==-1)
                    {
                        printf("-x^%d + ",p->m.degree);
                    }
                    else
                    {
                        printf("x^%d + ",p->m.degree);
                    }
                }
            }
            else /* same thing, but now the actual element is the last of the polynomial */
            {
                if(p->m.degree==0)
                {
                    printf("%.1f",p->m.coeff);
                }
                else if(p->m.degree==1)
                {
                    if(p->m.coeff!=1 && p->m.coeff!=-1)
                    {
                        printf("%.1fx",p->m.coeff);
                    }
                    else if(p->m.coeff==-1)
                    {
                        printf("-x");
                    }
                    else
                    {
                        printf("x");
                    }
                }
                else
                {
                    if(p->m.coeff!=1)
                    {
                        printf("%.1fx^%d",p->m.coeff,p->m.degree);
                    }
                    else
                    {
                        printf("x^%d",p->m.degree);
                    }
                }
            }
            p=p->next; /* after each display it moves to the next element */
        }
    }
    else
    {
        printf("0"); /* if the polynomial is empty, it prints "0" */
    }
}

/*-------------------------------------------------------------*/
/* OTHERS FUNCTIONS */

Polynomial init(Polynomial l) /* FUNCTION WHICH INITIALIZES AN EMPTY POLYNOMIAL BEFORE THE FIRST USE */
{
    l.head=NULL; /* it initializes all elements of the "Polynomial" structura */
    l.tail=NULL;
    l.numberMonomials=0;
    l.higherDegree=0;
    return l; /* and it returns the initialized polynomial with zero elements */
}

/*-------------------------------------------------------------*/

Polynomial derivatePolynomial(Polynomial l)
{
    ElemOfPolynomial *p=l.tail;
    if(p==NULL || l.higherDegree==0)
    {
        l=init(l);
    }
    else
    {
            while(p!=NULL)
            {
                
		if(p->m.degree==0)
		{
		    l=removeMonomial(l,0);
		}
		else
		{
		    p->m.coeff=p->m.coeff*p->m.degree;
                    p->m.degree--;
                }
		p=p->prev;
	    }
        l.higherDegree=l.tail->m.degree;
    }
    if(l.head!=NULL)
    {
        ElemOfPolynomial *p2=l.head;
        while(p2!=NULL)
        {
            if(p2->m.coeff==0)
            {
                l=removeMonomial(l,p2->m.degree);
            }
            p2=p2->next;
        }
    }
    return l;
}

/*-------------------------------------------------------------*/

Polynomial copyPolynomial(Polynomial l)
{
    Monomial m;
    Polynomial newP=init(newP);
    if(l.head!=NULL && l.tail!=NULL)
    {
        ElemOfPolynomial *p=l.head;
        while(p!=NULL)
        {
            m.coeff=p->m.coeff;
            m.degree=p->m.degree;
            newP=addMonomial(newP,m);
            p=p->next;
        }
    }
    return newP;
}

/*-------------------------------------------------------------*/

Polynomial remainder(Polynomial l1,Polynomial l2)
{
    Polynomial c=copyPolynomial(l1);
    Polynomial q=init(q);
    Polynomial s=init(s);
    Polynomial t=init(t);
    Polynomial r=init(r);
    Monomial m;
    while(c.higherDegree>=l2.higherDegree && c.higherDegree>=0)
    {
        m.coeff=c.tail->m.coeff/l2.tail->m.coeff;
        m.degree=c.tail->m.degree-l2.tail->m.degree;
        q=addMonomial(q,m);
        t=addMonomial(t,q.head->m);
        s=mul(l2,t);
        t=init(t);
        c=sub(c,s);
        if(c.head!=NULL)
        {
            c.higherDegree=c.tail->m.degree;
        }
        else
        {
            c.higherDegree=-1;
        }
    }
    r=sub(copyPolynomial(l1),mul(l2,q));
    return r;
}

/*-------------------------------------------------------------*/

Polynomial add(Polynomial l,float coeff,int deg)
{
    Monomial m;
    m.coeff=coeff;
    m.degree=deg;
    l=addMonomial(l,m);
    return l;
}

/*-------------------------------------------------------------*/

int sizeint(int nb)
{
    char ch[5];
    sprintf(ch,"%d",nb);
    return strlen(ch);
}

/*-------------------------------------------------------------*/

int pow10(int p)
{
    if(p==0)
    {
        return 1;
    }
    else
    {
        return 10*pow10(p-1);
    }
}
