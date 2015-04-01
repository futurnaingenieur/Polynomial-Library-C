#include <Polynomial.h>

int main(int argc,char**argv)
{
    Polynomial p1=init(p1),p2=init(p2);
    char file1[12]="polynomial1",file2[12]="polynomial2";
    char enter;
    int c=1,choice=0;
    float new_coeff=0; int new_degree=0,remove_degree=0;
    p1=createPolynomial(file1);
    p2=createPolynomial(file2);
    printf("\n\n--------------------------------------------------------------------------------\n\n");
    printf("\t\t\t*** POLYNOMIAL LIBRARY ***\n\nby Mehdi Brun\nJérémie Primas\n\n");

    while(c)
    {
    	printf("\t1 : test the library\n\t2 : view all functions provided\n\t");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 2:
    	      	printf("\n\nMain Functions :\n\n");
		printf("-> createMonomial\n\tbuilds a monomial structura with a real coefficient and an integer\n\tdegree\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();c=getchar();
   		printf("-> createPolynomial\n\tbuilds a polynomial by converting the text written in a file\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> addMonomial\n\tadd a new monomial and put it in the right place in a polynomial\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> removeMonomial\n\tremoves one monomial in a polynomial defined by his degree\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
 		printf("-> sum\n\tcomputes the sum between two polynomials\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> sub\n\tcomputes the substraction of a  polynomial by an other\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> mul\n\tcomputes the multiplication between two polynomials\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> divP\n\tcomputes the Euclidean division of a polynomial by an other and returns\n\tthe quotient\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> mDerivative\n\tcalculates the nth derivative of a monomial\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> pDerivative\n\tcalculates the nth derivative of a polynomial\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> gcd\n\tcalculates the greatest commom divisor of two polynomials\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> printMonomial\n\tdisplays a monomial\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> printPolynomial\n\tdisplays a polynomial\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
	      	printf("\nOther Functions :\n\n");
		printf("-> init\n\tinitializes a new polynomial created\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> derivatePolynomial\n\tcalculates the derivative of a polynomial\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> copyPolynomial\n\tcreates a new polynomials equals to an other polynomial\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> remainder\n\tcalculates the remainder of the Euclidean division of two polynomials\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> sizeint\n\treturns the number of characters in a given integer\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("-> pow10\n\tcalculates a power of ten within a given integer\n\n\n");
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");c=getchar();
		printf("1 : back\n0 : quit\n");
		scanf("%d",&c);
	    	break;
	    case 1:
		printf("\n\n'createPoynomial'\nTwo Polynomials will be created from the files ");
		printf("<polynomial1> and <polynomial2>\n");
		printf("P1 : ");printPolynomial(p1);printf("\nP2 : ");printPolynomial(p2);
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		enter=getchar();
		printf("\n\n'sum'\nP1 + P2 = ");printPolynomial(sum(p1,p2));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'sub'\nP1 - P2 = ");printPolynomial(sub(p1,p2));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'mul'\nP1 * P2 = ");printPolynomial(mul(p1,p2));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'div' and 'remainder'\nP1 = P2 ( ");
		printPolynomial(divP(p1,p2));printf(" ) + ");printPolynomial(remainder(p1,p2));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'pDerivative'\nThe 2nd derivative of the polynomial P1 is : ");printPolynomial(pDerivative(p1,2));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'gcd'\nThe greatest common divisor of P1 and P2 is : ");printPolynomial(gcd(p1,p2));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'createMonomial'\nChoose one coefficient : ");scanf("%f",&new_coeff);
		printf("Choose one degree : ");scanf("%d",&new_degree);
		printf("You have created the monomial : ");printMonomial(createMonomial(new_coeff,new_degree));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'addMonomial'\nYou have added the monomial in the polynomial P1");
		printf("\nP1 : ");printPolynomial(addMonomial(p1,createMonomial(new_coeff,new_degree)));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		printf("\n\n'removeMonomial'\nWhich monomial do you want to remove in the Polynomial (enter the degree) : ");
		scanf("%d",&remove_degree);
		printf("You have removed the monomial with the degree %d from the Polynomial\nP1 : ",remove_degree);
		printPolynomial(removeMonomial(p1,remove_degree));
		printf("\n\t\t\t\t\t\t\t\t    Press Enter");
		enter=getchar();
		enter=getchar();
		printf("\n\n'mDerivative'\nThe 2nd derivative of your first monomial is : ");
		printPolynomial(mDerivative(createMonomial(new_coeff,new_degree),2));
		printf("\n\n\n1 : back\n0 : quit\n");
		scanf("%d",&c);
		break;
	    default:
		break;

	}
	printf("\n\n\n");
    }
    enter++;
    printf("Thanks !\nLO27 Project\n\n--------------------------------------------------------------------------------\n\n");
    return 0;
}
