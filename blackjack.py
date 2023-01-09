import random
N=int(input('Enter number of decks: '))
#array holding the total cards in the game 
totalCards=[]
#deck representation
deck=['2♥','3♥','4♥','5♥','6♥','7♥','8♥','9♥','10♥','J♥','Q♥','K♥','A♥'
     ,'2♦','3♦','4♦','5♦','6♦','7♦','8♦','9♦','10♦','J♦','Q♦','K♦','A♦'
     ,'2♣','3♣','4♣','5♣','6♣','7♣','8♣','9♣','10♣','J♣','Q♣','K♣','A♣'
     ,'2♠','3♠','4♠','5♠','6♠','7♠','8♠','9♠','10♠','J♠','Q♠','K♠','A♠'
]
#adding number of decks in total cards
for b in range(N):
    for i in range(len(deck)):
        totalCards.append(deck[i])

# print(len(totalCards))
# print(totalCards)

#shuffling total cards
random.shuffle(totalCards)

# print(totalCards)
playerMoney=100
flag=True
while(flag):
    if (len(totalCards)>int(0.25*N*52)):
        print('Player Money: ',playerMoney,' - Cards Left: ',len(totalCards))
        print('Select your bet in [1,{}]:'.format(playerMoney))
        bet=input()
        print('Dealer cards: ',totalCards[0],'??')
        dealerCards=[totalCards[0],totalCards[1]]
        print('Player Cards: ',totalCards[2],totalCards[3])
        game=True
        playerScore=0
        dealerScore=0
        if totalCards[2][0]=='A' or totalCards[2][0]=='J' or totalCards[2][0]=='K' or totalCards[2][0]=='Q':
            if totalCards[2][0]=='A':
                playerScore+=11
            else:
                playerScore+=10
        else:
            playerScore+=int(totalCards[2][0])
        if totalCards[3][0]=='A' or totalCards[3][0]=='J' or totalCards[3][0]=='K' or totalCards[3][0]=='Q':
            if totalCards[3][0]=='A':
                playerScore+=11
            else:
                playerScore+=10
        else:
            playerScore+=int(totalCards[3][0])

        if totalCards[0][0]=='A' or totalCards[0][0]=='J' or totalCards[0][0]=='K' or totalCards[0][0]=='Q':
            if totalCards[0][0]=='A':
                dealerScore+=11
            else:
                dealerScore+=10
        else:
            dealerScore+=int(totalCards[0][0])
        if totalCards[1][0]=='A' or totalCards[1][0]=='J' or totalCards[1][0]=='K' or totalCards[1][0]=='Q':
            if totalCards[1][0]=='A':
                dealerScore+=11
            else:
                dealerScore+=10
        else:
            dealerScore+=int(totalCards[1][0])
        totalCards=totalCards[4:]
        if playerScore==21 and dealerScore!=21:
            print('You win bet...')
            playerMoney+=int(bet)
            game=False
            break
        if dealerScore==21 and playerScore!=21:
            print('You lose bet...')
            playerMoney-=int(bet)
            game=False
            break
        if dealerScore==21 and playerScore==21:
            print('No body wins - Tie')
            game=False
            break
        if game:
            hit=input('Do you want ot hit? [y=yess/n=no] ')
            if hit=='y':
                bust=False
                while not bust:
                    if totalCards[0][0]=='A' or totalCards[0][0]=='K' or totalCards[0][0]=='J' or totalCards[0][0]=='Q':
                        if totalCards[0][0]=='A':
                            if playerScore+11<21:
                                playerScore+=11
                            else:
                                playerScore+=1
                        else:
                            playerScore+=10
                    else:
                        playerScore+=int(totalCards[0][0])
                    print('You drew card: ',totalCards[0],' your sum is: ',playerScore)
                    totalCards=totalCards[1:]
                    if playerScore<21:
                        hit=input('Do you want ot hit? [y=yess/n=no] ')
                        if hit=='y':
                            bust=False
                        if hit=='n':
                            bust=True
                    if playerScore>21:
                        bust=True
    if (len(totalCards)>int(0.25*N*52)):
        print('Dealer cards: ',dealerCards[0],dealerCards[1])
        bust=False
        while not bust:
            if totalCards[0][0]=='A' or totalCards[0][0]=='K' or totalCards[0][0]=='J' or totalCards[0][0]=='Q':
                if totalCards[0][0]=='A':
                    if dealerCards+11<17:
                        dealerScore+=11
                    else:
                        dealerScore+=1
                else:
                    dealerScore+=10
            else:
                dealerScore+=int(totalCards[0][0])
            print('Dealer drew card: ',totalCards[0],' the sum is: ',dealerScore)
            if dealerScore>playerScore:
                print('You lose bet...')
                playerMoney-=int(bet)
                bust=True
                break
            elif playerScore>dealerScore:
                print('You win bet...')
                playerMoney+=int(bet)
                bust=True
                break
            elif playerScore==dealerScore:
                print('No body wins - Tie')
                bust=True
                break
            totalCards=totalCards[1:]
            if dealerScore>=17:
                bust=True

    else:
        flag=False

    

    x=input('\nDo you want to continue? [y=yess/n=no] ')
    if x=='y':
        flag=True
    if x=='n':
        flag=False
print('Player Money: ',playerMoney,' - Cards Left: ',len(totalCards))
print('Goodbye')