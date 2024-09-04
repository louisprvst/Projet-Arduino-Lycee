#define K 0.5 //Le gain de 0.5V/m
#define Vcuve1 7 //Led verte cuve 1
#define Rcuve1 4 //Led rouge cuve 1
#define Vcuve2 5 //Led verte cuve 2
#define Rcuve2 6 //Led rouge cuve 2
#define cuve1B 1 //Le seuil bas de la cuve 1 est 1m 
#define cuve1H 9.5 //Le seuil haut de la cuve 1 est 9.5
#define cuve2B 0.5 //Le seuil bas de la cuve 2 est 0.5
#define cuve2H 8 //Le seuil haut de la cuve 2 est 8m
int entree_an0 , entree_an1 ; //Variable integer sur le niveau des 2 cuves
float Cuve1V , Cuve2V , Cuve1M , Cuve2M ; //Variable float en mètre et en volt des 2 cuves

void setup()
{
  pinMode(Vcuve1, OUTPUT); //defini les 4 led suivante comme sortie
  pinMode(Rcuve1, OUTPUT);
  pinMode(Vcuve2, OUTPUT);
  pinMode(Rcuve2, OUTPUT);
  Serial.begin(9600); //defini la liason a 9600bauds
}

void loop()
{
      entree_an0 = analogRead(0); //On definit A0 sur entree_an0
      Cuve1V = entree_an0 * 0.0048875 ; //On convertit la valeur analogique de la cuve 1 en Volt
      Cuve1M = Cuve1V / K ; //On convertit la valeur en volt en métre
      entree_an1 = analogRead(1); //On definit A0 sur entree_an0
      Cuve2V = entree_an1 * 0.0048875 ; //On convertit la valeur analogique de la cuve 1 en Volt
      Cuve2M = Cuve2V / K ; //On convertit la valeur en volt en métre

      if(Cuve1M < cuve1B) //Si le niveau en metre est inferieur au seuil bas de la cuve 1                         
      {
        digitalWrite(Vcuve1,0); //eteint la led verte 1                 
        digitalWrite(Rcuve1,1); //allume la led rouge 1                 
      }
      else if(Cuve1M > cuve1H) //Si le niveau en metre est superieur au seuil haut de la cuve 1
      {                     
        digitalWrite(Vcuve1,1); //allume la led verte 1                    
        digitalWrite(Rcuve1,0); //eteint la led rouge 1                  
      }
      else //sinon                                       
      {
        digitalWrite(Vcuve1,0); //eteint la led verte 1
        digitalWrite(Rcuve1,0); //eteint la led rouge 1
      }

      if(Cuve2M < cuve2B) //Si le niveau en metre est inferieur au seuil bas de la cuve 1 
      {
        digitalWrite(Vcuve2,0); //eteint la led verte 2
        digitalWrite(Rcuve2,1); //allume la led rouge 2
      }
      else if(Cuve2M > cuve2H) //Si le niveau en metre est superieur au seuil haut de la cuve 1
      {
        digitalWrite(Vcuve2,1); //allume la led verte 2
        digitalWrite(Rcuve2,0); //eteint la led rouge 2
      }
      else //sinon
      {
        digitalWrite(Vcuve2,0); //eteint la led verte 2
        digitalWrite(Rcuve2,0); //eteint la led rouge 2
      }

      Serial.print("Cuve 1 en metre = ");//envoie la phrase sur le ms
      Serial.println(Cuve1M);//envoie sur le ms le niveau en metre de la cuve 1 + passage de ligne
      Serial.print("Cuve 1 en volt = ");//envoie la phrase sur le ms
      Serial.println(Cuve1V);//envoie sur le ms le niveau de la cuve en volt + passage a la ligne
      Serial.print("Cuve 2 en metre = ");//envoie la phrase sur le ms
      Serial.println(Cuve2M);//envoie sur le ms le niveau en metre de la cuve 2
      Serial.print("Cuve 2 en volt = ");//envoie la phrase sur le ms
      Serial.println(Cuve2V);//envoie sur le ms le niveau de la cuve en volt + passage a la ligne
      
delay(500); //delai de 0.5secondes     
}