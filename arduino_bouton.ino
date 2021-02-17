/*Utilisation capteur contact, si bouton apuuyé alors on renvoie l'information dans le moniteur*/

/*Initialisation*/
int bouton = 4;


void setup() {
  Serial.begin(9600);
  pinMode(bouton, INPUT);

}

void loop() {
  if (digitalRead(bouton) == LOW) {
    Serial.print("Bouton appuyé");
  }
  
  else {
    Serial.print("Bouton relaché");
  }
}
