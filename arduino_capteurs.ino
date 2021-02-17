/* Initialisation des variables et broches utilisées*/

/* Variables Ultrason*/
/* Constantes pour les broches */
const byte TRIGGER_PIN = 4; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long TIMEOUT_MESURE = 6000; // 0.6ms = ~2*100mm à 340m/s

/* Vitesse du son dans l'air en mm/us pour avoir un résultat en millimètre*/
const float vitesse_son = 0.340;

/* Autres varialbes utilisées*/
long mesure = 0;
float distance_mm = 0.0;


/* Variables IR*/
int buttonpin = 2; //define switch port
int  val;      //define digital variable val


/* Variables Contact*/

int bouton = 1;



void  setup() {
  Serial.begin(9600); /*Initialisation du moniteur*/
  
  /* Setup des différentes entrées et sorties utilisées*/
  
  /* Ultrason*/
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);

  /* IR*/
  pinMode(buttonpin,INPUT);

  /* Contact*/
  pinMode(bouton, INPUT);
}


void  loop() {
  val=digitalRead(buttonpin);//read the value of the digital interface 3 assigned to val 


  /* Si bouton est activé, on l'indique et les autres capteurs ne sont pas utilisé*/
  if (digitalRead(bouton) == LOW) {
    Serial.print("Contact : obstacle détecté");
  }
  
  else { /* Tant que le bouton n'est pas activé, IR et Ultrason sont activés*/

    /* Quand signal IR capte quelque chose, il active le capteur ultrason pour mesurer la distance*/
    if(val==LOW) {
      
      /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER*/
      digitalWrite(TRIGGER_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIGGER_PIN, LOW);
      
      /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe)*/
      mesure = pulseIn(ECHO_PIN, HIGH, TIMEOUT_MESURE); 
   
      /* 3. Calcul la distance à partir du temps mesuré*/
      distance_mm = mesure / 2.0 * vitesse_son;

      
      if (distance_mm < 200.0) { /* Le capteur ultrason n'est précis que jusqu'à 20cm donc on ne mesure les distance uniquement en dessous de cette distance */
        
        /* Renvoi de la distance de l'obstacle en mm et en cm*/
        Serial.print("Distance: ");
        Serial.print(distance_mm);
        Serial.print("mm (");
        Serial.print(distance_mm / 10.0, 2);
        Serial.println("cm)");
      }

      else {
        Serial.println("Trop loin pour la précision de l'ultrason"); /* Si distance supérieure  20cm, on le notifie*/
      }
  }
  
  else { /* Si aucun des capteurs ne détecte d'obstacles, on rennvoie cette info*/
    Serial.println("Pas d'obstacle détecté");
    }
  }
  
  delay(500); /* Pour éviter de trop spam le moniteur*/
}
