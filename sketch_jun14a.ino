#include <Gamebuino-Meta.h>


// ======== V A R  &  C O N S T ===========


//  Taille barre
const int barreSizeX = 2;
const int barreSizeY = 15;

//  Vitesse barre
const int barreSpeedY = 5;

//  Vitesse balle
int balleSpeedX = 1;
int balleSpeedY = 1;

//  Objet balle
int ballePositionX = gb.display.width()/2;
int ballePositionY = gb.display.height()/2;
const int balleSize = 2;
int ballColor = 0;

//  Rebond balle
const int ballePixelBoundX = gb.display.width() - balleSize - barreSizeX;
const int ballePixelBoundY = gb.display.height() - balleSize - barreSizeY;

//  Position barre 1
int barrePositionX1 = 0;
int barrePositionY1 = gb.display.height()/2;

//  Position barre 2
int barrePositionX2 = gb.display.width() - barreSizeX;
int barrePositionY2 = gb.display.height()/2;

//  Déplacement max barre
int barreMaxPositionYHaut =  0 ;
int barreMaxPositionYBas = gb.display.height() - barreSizeY;

int compteurScore1 = 0;
int compteurScore2 = 0;

int compteurReb1 = 0;
int compteurReb2 = 0;


// ======== F U N C ===========


void funcRebond()
{
  //  Vérification balle rebond gauche
  if(ballePositionX < 0)
  {
    //  Vérification balle collision barre 1 
    if (gb.collide.rectRect(barrePositionX1, barrePositionY1, barreSizeX, barreSizeY,ballePositionX, ballePositionY, balleSize, balleSize))
    {
      compteurReb1++;
      balleSpeedX = 1;
      gb.sound.playTick();
    }
    else
    {
      gb.sound.playCancel();
      compteurScore2++;
      delay(1000);
      ballePositionX = gb.display.width()/2;
    }
  }

  //  Vérification balle rebond droite
  if(ballePositionX > ballePixelBoundX)
  {
    //  Vérification balle collision barre 2
    if (gb.collide.rectRect(barrePositionX2, barrePositionY2, barreSizeX, barreSizeY,ballePositionX, ballePositionY, balleSize, balleSize))
    {
      compteurReb2++;
      balleSpeedX = -1;
      gb.sound.playTick();
    }
    else
    {
      gb.sound.playOK();
      compteurScore1++;
      delay(1000);
      ballePositionX = gb.display.width()/2;
    }
  }
}


void funcDeplacementBalleBarre()
{
  //  Déplacement balle Y
  if (ballePositionY < 0) {balleSpeedY = 1;}
  if (ballePositionY > ballePixelBoundY) {balleSpeedY = -1;}


  //  Déplacement barre 1
  if (gb.buttons.pressed(BUTTON_UP)) 
  {
    if(barrePositionY1 > barreMaxPositionYHaut)
    {
      barrePositionY1 -= barreSpeedY;
    }
  }
  
  if (gb.buttons.pressed(BUTTON_DOWN)) 
  {
    if(barrePositionY1 < barreMaxPositionYBas)
    {
      barrePositionY1 += barreSpeedY;
    }
  }

  //  Déplacement barre 2
  if (gb.buttons.pressed(BUTTON_A)) 
  {
    if(barrePositionY2 > barreMaxPositionYHaut)
    {
      barrePositionY2 -= barreSpeedY;
    }
  }
  
  if (gb.buttons.pressed(BUTTON_B)) 
  {
    if(barrePositionY2 < barreMaxPositionYBas)
    {
      barrePositionY2 += barreSpeedY;
    }
  }
}


//  Func Setup
void setup() {
  gb.begin();
}



//  Func Loop
void loop() {
  while (!gb.update());
  gb.display.clear();

  ballePositionX += balleSpeedX;
  ballePositionY += balleSpeedY;

  funcRebond();

  funcDeplacementBalleBarre();
  


  
  //  Couleur de la balle
  ballColor = compteurScore1 + 1;
  if (compteurScore2 > ballColor)
  {
    ballColor = compteurScore2 + 1;
  }
  

  //  Affichage de la balle
  gb.display.setColor(ballColor);
  gb.display.fillRect(ballePositionX, ballePositionY, balleSize, balleSize);

  //  Affichage de la raquette 1
  gb.display.setColor(BLUE);
  gb.display.printf("Player 1 =  %d", compteurScore1);
  gb.display.fillRect(barrePositionX1, barrePositionY1, barreSizeX, barreSizeY);

  //  Affichage de la raquette 2
  gb.display.setColor(RED);
  gb.display.printf("\nPlayer 2 =  %d", compteurScore2);
  gb.display.fillRect(barrePositionX2, barrePositionY2, barreSizeX, barreSizeY);

  //  rebond
  //gb.display.printf("\nReb 1   =  %d ", compteurReb1);
  //gb.display.printf("\nReb 2   =  %d", compteurReb2);

}
