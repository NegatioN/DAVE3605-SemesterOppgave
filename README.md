# DAVE3605-SemesterOppgave
C++ Doom-clone

## Screenshots
A few screenshots of how the game looks like. It doesn't seem like the controls for the mouse is working in Ubuntu, so they are a bit limited :)

![alt text](https://raw.githubusercontent.com/NegatioN/Spoomdre-DoomClone/master/ss.png "Screenshot of the game")
![alt text](https://raw.githubusercontent.com/NegatioN/Spoomdre-DoomClone/master/ss2.png "Screenshot of the game")


## Dokumentasjon


### Innledning
Vi har laget en DOOM-klone fra bunnen av, ved hjelp av grafikkbiblioteket SDL2. Utviklingen har i all hovedsak dreid seg mer om spillmotoren, enn å lage et komplett spill. Å få spillmiljøet opp og gå med mulighet for utvidelse av morsomme funksjoner har vært hovedfokus, og dette føler vi at vi har fått til. Vi har ikke optimalisert med tanke på ytelse eller perfekt struktur, men heller å utforske muligheten. Vi visste ikke helt hva vi bega oss ut på med dette prosjektet, da ingen av oss har prøvd oss på spillutvikling tidligere, så det var også vanskelig å sette en konkret avgrensning for prosjektet. Spesielt ble dette klart med tanke på hvordan koden utviklet seg. Det skulle gjerne vært brukt mer objektorientert kode i map og rendering. Vi valgte ofte å utvide funksjonaliteten litt underveis, noe som har vært både til positiv og negativ overaskelse for gruppen. Vi har klart mer enn vi trodde vi skulle få til ved starten, men det har vært vanskelig å bygge på et ugjevnt fundament til tider. Det gjenstår noen bugs og utjevninger i programmet ennå (disse er beskrevet under “bugs” i dokumentasjonen), men helhetlig syns vi vi har lagt et godt grunnlag.


### Dependencies:
Lastes ned med ‘sudo apt-get install’:

libsdl2-dev

libsdl2-image-dev

libeigen3-dev


### Kontrollere:

####Bevegelse:

Fram		-	W

Bakover	-	S

Høyre		-	D

Venstre	-	A

Hopp		-	Mellomromstasten

Dukk/Knebøy 	- 	Venstre-CTRL eller C

Løp		-	Venstre-Shift


#### Se rundt:   

Snu til høyre 	- 	Pil-høyre, L

Snu til venstre - 	Pil-venstre, K

Se opp		-	Pil-opp

Se ned		-	Pil-ned

#### Mer action:

Interager	-	E

Skyt		-	Enter


Man kan også bruke musa for å se rundt, og skyte med venstre muse-knapp


### Diagrammer:

#### Klasse-diagram:
![alt text](https://raw.githubusercontent.com/NegatioN/DAVE3605-SemesterOppgave/master/class-chart.png?token=AD2ciRRAq8GnoXs3G8IweqfIaIAJSZyGks5VT89wwA%3D%3D "Klasse-diagram")

#### Flyt-diagram:
![alt text](https://raw.githubusercontent.com/NegatioN/DAVE3605-SemesterOppgave/master/flow-chart.png?token=AD2ciXU_FrPgca3Yiungrlo1j4-J7lY3ks5VT8-JwA%3D%3D "Flyt-diagram")


### Hva er bra?
Vi har nådd minstekravene våre med å lage et spill som rendrer 3D-grafikk, hvor spiller kan bevege seg rundt i rommet, og skyte enemies som beveger seg på egenhånd. Vi er også generelt fornøyd med mengde funksjonalitet vi har fått med i programmet.

Med tanke på at vi ikke har tatt i bruk 3D-rendringsbiblioteker, føler vi vi har fått en godt fungerende motor for å rendre en 3D-verden vi selv kan lage og justere forholdsvis enkelt.

Vi syns også spillerbevegelser og spillfølelsen er god, og er fornøyde med å ha fått med både vanlig bevegelse, hopping, crouching, hodebevegelser (dette går blant annet ikke an i DOOM) og skyting. Disse føles responsive og fungerer som forventet.

Vi har gjort hele prosjektet objektorientert, og føler det er godt mulig å utvide spillet med ny funksjonalitet og nye variasjoner, som kan ta i bruk de nåværende metodene og strukturen.



### Forbedringspotensiale:
Objekter
Lines - Vi ønsket å definere veggene i en sektor med en linje istedenfor to punkter. Da ville det blir enklere og mer ryddig å holde styr på vegger når vi skulle bruke dem i utregninger eller i rendring.
Mapmaker - For å lage en level eller map, måtte vi hardcode hver enkelt vertex, sector, sector-naboer samt alle mulige forskjellige variabler. Vi ønsket å heller ha et map i en txt-fil og en metode som parser tekst-dokumentet til et map, men vi valgte å heller bruke tid på å få på plass de andre delene av prosjektet enn å lage en tekst-parser som kanskje ikke ville spart oss så mye i denne omgangen. Men i fremtiden eller hvis vi hadde mer tid ville vi nok laget en mye bedre løsning.

Optimalisering
Rendering-loop - Det er sikkert rom for optimalisering av både framerate og kodens lesbarhet. For lesbarhetens del kunne man separert ut behandling av sektorRendering, og innefor der igjen kunne nok nabosektorer blitt behandlet i en egen metode.
Bedre bruk av Eigen i utregninger - Ved bruk av vektorer og kryssprodukt fra eigen ville matematikken blitt mer oversiktlig. I starten ble det dog for fristende å komme seg gjennom den delen fort.

Bugs
Rendering av sector foran, hvor venstre vertex er “bak players vision”, og høyre er foran. Her ender floating-point matten vår med å gi “1721” som x kryssningspunkt, og rendrer ikke veggen da den tror den er bak player.

Rendering av textures utifra spillerbegelse fungerer ikke optimalt når deler av veggen er utenfor synsfeltet. Dette fordi det da blir vanskelig å finne ut hvor lang vegge faktisk er på skjerm i forhold til på kartet. Det samme gjelder textures på vegger som ikke når helt opp til taket i sektoren. Vi er ennå ikke helt sikre på hva dette kommer av.

Når en sector renderes framfor en enemy vil av og til enemy renderes over veggen, slik at du vil se enemy selv om han er bak den veggen. For å løse dette problemet måtte vi ha implementert metoder for å croppe texture til enemy på mange mulige måter. Dette ville blitt en ganske omfattende oppgave så vi valgte å ikke prioritere den.

Spillet har tester for å hindre spiller og andre entities å dette gjennom veggene. I de fleste situasjoner fungerer disse som de skal, men i enkelte hjørner er det fortsatt mulig å fall ut. Vi har en teori om at dette skyldes manglende test på om man treffer direkte i vinkelen etter man bytter sektor. Vi har forsøkt flere metoder for å fikse dette, men ingen har hittil fikset problemet uten å hindre bevegelighet på andre måter.


### Rendering:
Vi har gitt oss selv en liten utfordring ved å gå for 2D-biblioteket SDL, som vi så oversetter til 3D manuelt. Dette foregår ved at vi plasserer punkter(vertex) i et koordinatsystem, som så beveger seg utifra en stillestående “player” midt i kartet. Disse koordinatene fungerer som hjørner, og mellom dem tegnes vegger. De ulike rommene er delt opp i sektorer, som alltid er konvekse polygoner. På denne måten går det alltid an å avgjøre om spilleren står på innsiden eller utsiden av en vegg, og dermed kun rendre innsiden av veggen. Vegger rendres ved å kalkulere høyde for tak og gulv for hvert punkt langs x-aksen, og så tegne linjer mellom disse. Altså rendres hele viewet ved hjelp av vertikale linjer. Sektorer kan også ha nabosektorer, som spiller kan bevege seg mellom. Ulike sektorer kan også ha ulike tak- og gulvhøyder, som kan brukes til å lage trapper, tunneller og platåer.

På grunn av bruken av 2D-bibliotek, fant vi ingen måte å direkte perspektivtransformere teksturer til å vises på vegger med dybde. Derfor måtte vi også manuelt transformere teksturer. Det gjorde vi på samme måte ved å hente ut tilsvarende vertikale linje i texture og tegne disse ved siden av hverandre i viewet. Dette visste seg likevel å være en utfordring når player beveget seg, og fungerer ikke helt som det skal.

Enemies rendres enkelt som en 2D texture som tegnes ut ifra et koordinat på gulvet.

### Kilder:
* http://en.wikipedia.org/wiki/Perspective_%28graphical%29
* http://en.wikipedia.org/wiki/Rotation_%28mathematics%29
* http://en.wikipedia.org/wiki/Vector_projection
* http://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
* http://doom.wikia.com/wiki/Doom_rendering_engine#Node_building
