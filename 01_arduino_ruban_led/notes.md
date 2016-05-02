## Matériel

**Arduino uno**

Environ 3,50$ pur un [équivalent de l'Arduino Uno](http://www.ebay.com/itm/NEW-ATmega328P-CH340G-UNO-R3-Board-USB-Cable-for-Arduino-DIY-MC-/161977675428)

**Ruban LED WS2812B**

Environ 10 € le [mètre à 60 leds](http://www.ebay.com/itm/371432213255)

**Jumper mâle-mâle**

Environ [1,50$ les 65](http://www.ebay.com/itm/65Pcs-Male-to-Male-Solderless-Flexible-Breadboard-Jumper-Cable-Wires-For-Arduino-/252107574004)

**Bonus**

Au delà de 80 LEDs, l'alimentation USB peut être insuffisante (en fonction de combien de led on éclaire), il faut alors une alimentation plus puissante
Environ de [8 € pour 6 ampères à 25 € pour 60 ampères](http://www.ebay.com/itm/Switch-Power-Supply-Driver-adapter-AC110-220V-TO-DC-5V-12V-24V-48V-For-LED-Strip-/222056370354)


## Généralités sur Arduino



**Code et téléversement**

Quand on démarre l'arduino, il y a 2 modes possibles :
- programmable (on lui injecte un programme)
- soit on utilise le programme qu'il y a dedans

Téléverser = injecter le programme dans l'arduino, et éxécuter un reset en mode exécution
Le logiciel arduino vient avec des programmes d'exemple de base, trouvables dans "fichier/exemples"
On peut vérifier le code d'un programme (icone vérifier) avant de le téléverser (icone téléverser)


**Alimentation**

Concernant la tension d'entrée, l'arduino est très permissif. On peut à priori sans problme l'alimenter entre 1,8V et 12V. L'arduino possède un régulateur intégré qui va convertir la tension d'entrée vers une tension de sortie en 5V

Si on se branche sur le pin v-in, on délivre la tension d'entrée, on ne passe plus par le régulateur. La tension en sortie de l'arduino sera la même que celle qu'on a balancé à la base.

**Structure d'un programme arduino**

2 fonctions : setup et loop
-setup(): exécutée au démarrage une fois, initialise des variables, l'état etc...
-loop(): exécutée en boucle à la vitesse du processeur après l'initialisation

**Debug**

Dans le code on peut utiliser la fonction println()
pour visualiser le debug aller dans "outil/moniteur série" et choisir la même vitesse que celle déclarée dans le code avant de téléverser

**Troubleshooting**

Si erreur de port openCL, aller dans "outil/port série" et choisir le bon port

## Généralités sur le ruban LED


**Alimentation**

Si on met on met 12v dans l'arduino et que nos guirlandes doivent être alimentées en 5v, ne surtout pas se brancher sur v-in sinon on risque de cramer les led. Il faut utiliser le régulateur, et donc se brancher sur 5V

Si on alimente à 1,8V les leds font la gueule

Lorsqu'on ne compte pas utiliser d'alimentation externe, on utilise l'USB du PC en 5V. Puisque la tension d'entrée est la même que la tension de sortie, on peut se brancher sur v-in

**Connectique**

Attention faut surtout pas que les fils rouge et blanc qui dépassent se touchent. Mettre du scotch.

3 fils:
-rouge : 5v
-blanc : 5v
-vert : horloge(c'est grâce au fil vert que l'on envoit l'état que les leds doivent prendre, donc leur couleur)

Branchements:
-rouge : sur v-in (si on alimente via USB)
-blanc sur gnd
-vert sur pin6 (on va déclerer le pin6 plus tard dans le code)

**Dépendances**

Pour allumer les rubans de led et faire fonctionner le code il faut télcharger les bonnes librairies

**Couleurs**

Si on veut eteindre les led, on assigne la couleur noire à une led


## Exemples


**Exemple 1 : blink.ino**

Il s'agit d'un programme basique, fournit par le logiciel arduino, qui fait clignoter une led verte présente sur la carte arduino (une led intégrée à la carte, donc besoin d'aucun matériel pour tester)

On trouve le code dans "fichier/exemples:basics/blink" via le logiciel arduino

La led L doit clignoter


**Exemple 2 : 2_leds.ino**

L'idée est de comprendre comment allumer les leds de la guirlande indépendamment chacunes. On utilise la librairie Adafruit_NeoPixel.h, qu'il faut inclure dans le programme. Elle est dans le dossier resources si besoin.










