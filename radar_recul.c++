#include "Adafruit_LiquidCrystal.h"

#define bp 2 
#define led 3

int EtatBouton = 0 ;                               
int ancienEtatBouton = 0 ;
int compteur = 0 ;

int seuil_danger ;
int seuil_alerte ;

int trig = 4;
int echo = 5;
unsigned long dure_echo;
float distance ;

int entree_an0 ;

Adafruit_LiquidCrystal afficheur(0x20);

void affichage_reglage()
{
  afficheur.clear();
  afficheur.home();
  afficheur.setCursor(0, 0);
  afficheur.print("Danger : ");
  afficheur.print(seuil_danger);
  afficheur.setCursor(0, 1);
  afficheur.print("Alerte : ");
  afficheur.print(seuil_alerte);
  delay(100);
}

void affichage_ok()
{
  afficheur.clear();
  afficheur.home();
  afficheur.setCursor(0, 0);
  afficheur.print("Distance : ");
  afficheur.print(distance);
  afficheur.setCursor(0, 1);
  afficheur.print("Tout va bien.");
}

void affichage_alerte()
{
  afficheur.clear();
  afficheur.home();
  afficheur.setCursor(0, 0);
  afficheur.print("Distance : ");
  afficheur.print(distance);
  afficheur.setCursor(0, 1);
  afficheur.print("Faite attention.");
}

void affichage_danger()
{
  afficheur.clear();
  afficheur.home();
  afficheur.setCursor(0, 0);
  afficheur.print("Distance : ");
  afficheur.print(distance);
  afficheur.setCursor(0, 1);
  afficheur.print("Danger.");
}

void reglage_danger()                                      
{
  entree_an0 = analogRead(0);
  seuil_danger = entree_an0*0.391006;
  affichage_reglage();
}

void reglage_alerte()                                      
{
  entree_an0 = analogRead(0);
  seuil_alerte = entree_an0*0.391006;
  affichage_reglage(); 
}

void lancement_mesure()
{
  digitalWrite(trig, 0);
  delayMicroseconds(5);
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);
}

float mesure_distance()
{
 dure_echo = pulseIn(echo, HIGH); 
 distance = dure_echo*0.017;
 Serial.println(distance);
}

void test()
{
  if(distance < seuil_danger)
      {
      affichage_danger();
      digitalWrite(led,HIGH);       
      }
   else if(distance < seuil_alerte)
      {
      affichage_alerte();
      digitalWrite(led,HIGH);
      delay(100);
      digitalWrite(led,LOW);
      delay(100); 
      }
    else
      {
      digitalWrite(led,LOW);
      affichage_ok();
      }
}

void setup()                                      
{
  Serial.begin (9600);
  afficheur.begin(16, 2);
  pinMode(bp,INPUT);
  pinMode(led, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop()                                      
{
  EtatBouton = digitalRead(bp);                    
  if ((EtatBouton == HIGH) && (EtatBouton != ancienEtatBouton))
  {
    compteur = compteur +1;
    if(compteur == 3)
    {
      compteur = 0;
    }
  }
  ancienEtatBouton = EtatBouton;

  switch(compteur)
  {
    case 0:                                        
      lancement_mesure();
      mesure_distance();
      test();
      break;
    case 1:                                       
      reglage_alerte();
      break;
    case 2:
      reglage_danger();
      break;
  }
}   