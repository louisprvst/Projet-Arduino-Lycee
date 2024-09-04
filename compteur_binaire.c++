#define BP 2 // Le bouton est relié à la pin 2
#define Led8 3 // Le bouton est relié à la pin 3
#define Led4 4 // Le bouton est relié à la pin 4
#define Led2 5 // Le bouton est relié à la pin 5
#define Led1 6 // Le bouton est relié à la pin 6
int delai_antirebond = 50; //Délai de blocage du programme
int compteur= 0;
int EtatBouton; // Etat du bouton
int ancienEtatBouton; //Ancien état du bouton
int binaire; 

void setup() 
{
  pinMode(BP, INPUT);
  pinMode(Led8, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led1, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
    EtatBouton = digitalRead(BP);  //si le bouton est appuyé et n'était pas appuyé avant
    binaire = compteur ;

      if(compteur==16){
        compteur = 0 ;
      }
    
      if ((EtatBouton == HIGH) && (EtatBouton!=ancienEtatBouton))
          {
            compteur= compteur + 1; // incrémentation du compteur 
            Serial.print("Vous avez appuye "); // Affichage du compteur dans le moniteur série
            Serial.print(compteur);
            Serial.println(" fois sur le bouton.");
          }

      if (binaire>=8){
        digitalWrite(Led8,1);
        binaire = binaire - 8;
      }
      else {
        digitalWrite(Led8,0);
      }
        
      if (binaire>=4){
        digitalWrite(Led4,1);
        binaire = binaire - 4;
      }
      else {
        digitalWrite(Led4,0);
      }

      if (binaire>=2){
        digitalWrite(Led2,1);
        binaire = binaire - 2;
      }
      else {
        digitalWrite(Led2,0);
      }

      if (binaire>=1){
        digitalWrite(Led1,1);
        binaire = binaire - 1;
      }
      else {
        digitalWrite(Led1,0);
      }
          
  ancienEtatBouton = EtatBouton;
  delay(delai_antirebond);
}