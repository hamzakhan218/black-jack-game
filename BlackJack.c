#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int money=100;
int noofdecks;
int totalcards;
int shuff(int cards[])
{
	
	int t;
	int i;
	int desk[52];	
	for (i=0;i<52;i++)
		desk[i] = (i/13+3)*100 + i%13 + 1;

	srand(time(NULL));
	for (i = 0; i < 52; i++)
	{
		do
		{
			t = rand() % 52;
		} while (desk[t] == 0);
		cards[i] = desk[t];
		desk[t] = 0;
	}
	
	return 0;
}

int convert_jkq(int a)
{
	if ((a%100==11) ||(a%100==12) ||(a%100==13)) return (a/100)*100+10;
	else return a;
}

void pic(int num)
{
	char fl;
	int po_num;
	
	fl = num / 100;
	po_num = num % 100;
	switch (po_num)
	{
		case 1: 
		{
			printf("A%c",fl);
			break;
		}
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		{
			
			printf("%2d%c",po_num,fl);
			break;
		}
		case 11:
		{
			printf("J%c",fl);
			break;
		}
		case 12:
		{
			printf("Q%c",fl);
			break;
		}
		case 13:
		{
			printf("K%c",fl);
			break;
		}

	}
}

int play(void)
{
	int i;
	int psum=0;
	int bsum=0;
	int pcards[5]={0};
	int bcards[5]={0};
	int cards[52];
	char go_on;
	char d;
	shuff(cards);

	//give the cards
	pcards[0]=cards[0];
	pcards[1]=cards[1];
	bcards[0]=cards[2];
	bcards[1]=cards[3];
	
	//the 2 cards player get
	printf("Player Money: %d - Cards Left: %d",money,totalcards);
	printf("\nSelect your bet in [1,%d]: ",money);
	int bet=0;
	scanf("%d",&bet);
	printf("Dealer cards: ");
	pic(bcards[0]);
	printf("??\nPlayer cards: ");
	pic(pcards[0]);
	pic(pcards[1]);
	totalcards=totalcards-4;
	i=0;
	for (i=0; i<2; i++)
	{
		if (pcards[i]%100 == 1)
		{			
			if (psum+11<21)
			{
				psum = psum + 11;
			}
			else
			{
				psum = psum +1;
			}
		}
		else if (convert_jkq(pcards[i]) %100 ==10) psum = psum + 10;
		else psum = psum + pcards[i]%100;
		
		if (psum > 21)
		{
			printf("\nYou lose bet...\n");
			money=money-bet;
			return 1;
		}
		else if (psum == 21)
		{
			printf("\nYou win bet...\n");
			money=money+bet;
			return 0;
		}
	}
	
	//whether player get another cards
	i=0;
	for (i=0; i<3; i++)
	{
		char j = 'n';
		
		printf("\nDo you want to hit? [y=yess/n=no] ");
		do{
			j = getchar();
		} while (j!='y' &&j!='n');
		
		if (j=='y')
		{
			pcards[i+2]=cards[i+4];
			printf("You drew card: ");
			pic(pcards[i+2]);
			totalcards=totalcards-1;
			if (pcards[i+2]%100 == 1)
			{
				
				if (psum+11 <21)
				{
					psum = psum + 11;
				}
				else
				{
					psum = psum +1;
				}
			}
			else if (convert_jkq(pcards[i+2]) %100 ==10) psum = psum + 10;
			else psum = psum + pcards[i+2]%100;
			
			if (psum > 21)
			{
				printf("  your sum is: %d\n\n",psum);
				printf("You lose bet...\n");
				money=money-bet;
				return 1;
			}
			else if (psum == 21)
			{
				printf(" your sum is: %d\n\n",psum);
				printf("You win bet...\n");
				money=money+bet;
				return 0;
			}		
			else printf(" your sum is: %d\n\n",psum);
		}
		else 
		{
			break;
		}
	}
	if (i == 3)
	{
		printf("You win bet...\n");
		money=money+bet;
		return 0;
	}
	
	printf("Dealer cards: ");
	pic(bcards[0]);
	pic(bcards[1]);

	if (bcards[0]%100 + bcards[1]%100 == 2)
	{
		bsum=12; //two A cards
		printf(" the sum is: %d\n\n", bsum);
	}
	else if ((convert_jkq(bcards[0]))%100 + (convert_jkq(bcards[1]))%100 ==1)
	{
		bsum=21;
		printf("You lose bet...\n");
		money=money-bet;
		return 1;
	}
	else if (bcards[0]%100==1 || bcards[1]%100==1)
	{
		bsum=(bcards[0]+bcards[1])%100+(rand()%2)*10;
		printf(" the sum is: %d\n\n", bsum);
	}
	else
	{
		bsum = (convert_jkq(bcards[0]))%100 + (convert_jkq(bcards[1]))%100;
		printf(" the sum is: %d\n\n", bsum);
	}
	
	//whether Dealer get another cards until bsum>16
	for (i=0; i<3 && bsum<17; i++)
	{
		bcards[i+2]=cards[i+7];
		printf("Dealer drew card: ");
		pic(bcards[i+2]);
		totalcards=totalcards-1;
		if (bcards[i+2]%100 == 1)
		{
			if (bsum+11 <= 21)
			{
				bsum = bsum+11;
				printf(" the sum is:%d\n\n", bsum);
			}
			else
			{
				bsum = bsum+1;
				printf(" the sum is:%d\n\n", bsum);
			}
		}
		else
		{
			bsum = bsum + convert_jkq(bcards[i+2])%100;
			printf(" the sum is:%d\n\n", bsum);
		}
	}
	if (i == 3)
	{
		printf("You lose bet...\n");
		money=money-bet;
		return 1;
	}
	
	//the last step
	if (bsum>21 || psum>bsum)
	{
		printf("You win bet...\n");
		money=money+bet;
		return 0;
	}
	else if (psum == bsum)
	{
		printf("No body wins - Tie\n");
		return 3;
	}
	else if (psum < bsum)
	{
		printf("You lose bet...\n");
		money=money-bet;
		return 1;
	}
		
	return 3;
}

int main(void)
{
	char again;
	printf("Enter number of decks: ");
	scanf("%d",&noofdecks);
	totalcards=52*noofdecks;
	play();
	printf("\nDo you want to contiue? [y=yes/n=no] ");
	do{
		again = getchar();
	} while (again!='y' && again!='n');
	while (again=='y'){
		play();
		printf("\nDo you want to contiue? [y=yes/n=no] ");
			do{
				again = getchar();
			} while (again!='y' && again!='n');
	};
	printf("Player Money: %d - Cards Left: %d\nGoodbye",money,totalcards);
	return 0;
}
