#!/bin/bash

STOPPEDSTEMMED="stoppedStemmed"
STEMMED="stemmed"
STOPPED="stopped"
PLAIN="plain"
INDEX="Index"
PAR="Par"


#deleting existing indices
rm -r $STOPPEDSTEMMED$INDEX  | >/dev/null
rm -r $STEMMED$INDEX | >/dev/null
rm -r $STOPPED$INDEX | >/dev/null
rm -r $PLAIN$INDEX | >/dev/null

#stopwords

PRE="<parameters>\n"
CORPUS1="<corpus>\n<path>"
CORPUS2="</path>\n<class>txt</class></corpus>\n"
MEMORY="<memory>300m</memory>\n"
INDEXPRE="<index>"
INDEXPOS="</index>"
STEMMER="<stemmer><name>hunStemmer</name></stemmer>"
SW="<stopper><word>a</word>\n<word>az</word>\n<word>abban</word>\n<word>abból</word>\n<word>adott</word>\n<word>ahhoz</word>\n<word>ahogy</word>\n<word>ahol</word>\n<word>akar</word>\n<word>akár</word>\n<word>aki</word>\n<word>akik</word>\n<word>akkor</word>\n<word>alá</word>\n<word>alapján</word>\n<word>alatt</word>\n<word>által</word>\n<word>általában</word>\n<word>amely</word>\n<word>amelyben</word>\n<word>amelyek</word>\n<word>amelyekben</word>\n<word>amelyeket</word>\n<word>amelyet</word>\n<word>amelyik</word>\n<word>amelynek</word>\n<word>ami</word>\n<word>amíg</word>\n<word>amikor</word>\n<word>amiről</word>\n<word>amit</word>\n<word>amolyan</word>\n<word>annak</word>\n<word>arra</word>\n<word>arról</word>\n<word>át</word>\n<word>az</word>\n<word>azért</word>\n<word>azok</word>\n<word>azokat</word>\n<word>azoknak</word>\n<word>azon</word>\n<word>azonban</word>\n<word>azt</word>\n<word>aztán</word>\n<word>azután</word>\n<word>azzal</word>\n<word>ban</word>\n<word>bár</word>\n<word>be</word>\n<word>belül</word>\n<word>ben</word>\n<word>benne</word>\n<word>bizony</word>\n<word>bizonyos</word>\n<word>biztos</word>\n<word>cikk</word>\n<word>cikkek</word>\n<word>cikkeket</word>\n<word>csak</word>\n<word>csupán</word>\n<word>de</word>\n<word>e</word>\n<word>ebben</word>\n<word>ebből</word>\n<word>eddig</word>\n<word>egész</word>\n<word>egészen</word>\n<word>egy</word>\n<word>egyéb</word>\n<word>egyébként</word>\n<word>egyértelműen</word>\n<word>egyes</word>\n<word>egyet</word>\n<word>egyetlen</word>\n<word>egyik</word>\n<word>egyre</word>\n<word>egyrészt</word>\n<word>egységes</word>\n<word>ehhez</word>\n<word>ekkor</word>\n<word>el</word>\n<word>elé</word>\n<word>elég</word>\n<word>ellen</word>\n<word>ellenére</word>\n<word>elő</word>\n<word>előbb</word>\n<word>először</word>\n<word>előtt</word>\n<word>előtti</word>\n<word>első</word>\n<word>elsősorban</word>\n<word>ember</word>\n<word>emilyen</word>\n<word>én</word>\n<word>ennek</word>\n<word>ennél</word>\n<word>éppen</word>\n<word>erre</word>\n<word>erről</word>\n<word>es</word>\n<word>és</word>\n<word>esetén</word>\n<word>esetleg</word>\n<word>ez</word>\n<word>ezek</word>\n<word>ezeket</word>\n<word>ezen</word>\n<word>ezért</word>\n<word>ezt</word>\n<word>ezzel</word>\n<word>fel</word>\n<word>felé</word>\n<word>fog</word>\n<word>fognak</word>\n<word>gondolom</word>\n<word>gyakorlatilag</word>\n<word>ha</word>\n<word>hanem</word>\n<word>hát</word>\n<word>helyett</word>\n<word>hiszem</word>\n<word>hiszen</word>\n<word>hogy</word>\n<word>hogyan</word>\n<word>hogyha</word>\n<word>hozzá</word>\n<word>ide</word>\n<word>igen</word>\n<word>így</word>\n<word>ill</word>\n<word>illetőleg</word>\n<word>illetve</word>\n<word>ilyen</word>\n<word>ilyenkor</word>\n<word>inkább</word>\n<word>is</word>\n<word>ismét</word>\n<word>itt</word>\n<word>jelenlegi</word>\n<word>jó</word>\n<word>jobban</word>\n<word>jól</word>\n<word>kapcsán</word>\n<word>kapcsolatban</word>\n<word>kapcsolatos</word>\n<word>kell</word>\n<word>kellene</word>\n<word>kellett</word>\n<word>képest</word>\n<word>képviselő</word>\n<word>képviselőtársaim</word>\n<word>kérem</word>\n<word>keressünk</word>\n<word>keresztül</word>\n<word>ki</word>\n<word>kicsit</word>\n<word>kíván</word>\n<word>kívül</word>\n<word>korábban</word>\n<word>korábbi</word>\n<word>köszönöm</word>\n<word>követően</word>\n<word>között</word>\n<word>közül</word>\n<word>különböző</word>\n<word>le</word>\n<word>legalább</word>\n<word>legyen</word>\n<word>lehet</word>\n<word>lehetett</word>\n<word>lehetséges</word>\n<word>lenne</word>\n<word>lenni</word>\n<word>lesz</word>\n<word>lett</word>\n<word>maga</word>\n<word>magát</word>\n<word>majd</word>\n<word>már</word>\n<word>más</word>\n<word>másik</word>\n<word>meg</word>\n<word>még</word>\n<word>megfelelő</word>\n<word>mégis</word>\n<word>mellett</word>\n<word>mely</word>\n<word>melyek</word>\n<word>mert</word>\n<word>mi</word>\n<word>miatt</word>\n<word>miért</word>\n<word>míg</word>\n<word>mikor</word>\n<word>miközben</word>\n<word>milyen</word>\n<word>mind</word>\n<word>minden</word>\n<word>mindenképpen</word>\n<word>mindenki</word>\n<word>mindent</word>\n<word>mindig</word>\n<word>minél</word>\n<word>mint</word>\n<word>mintegy</word>\n<word>mintha</word>\n<word>mit</word>\n<word>mivel</word>\n<word>módon</word>\n<word>mondjuk</word>\n<word>most</word>\n<word>nagy</word>\n<word>nagyobb</word>\n<word>nagyon</word>\n<word>ne</word>\n<word>néha</word>\n<word>néhány</word>\n<word>nekem</word>\n<word>neki</word>\n<word>nekünk</word>\n<word>nélkül</word>\n<word>nem</word>\n<word>nemcsak</word>\n<word>nincs</word>\n<word>nyilván</word>\n<word>oda</word>\n<word>olyan</word>\n<word>ott</word>\n<word>ő</word>\n<word>ők</word>\n<word>őket</word>\n<word>ön</word>\n<word>öné</word>\n<word>önök</word>\n<word>össze</word>\n<word>pedig</word>\n<word>például</word>\n<word>persze</word>\n<word>pontosan</word>\n<word>rá</word>\n<word>részéről</word>\n<word>s</word>\n<word>saját</word>\n<word>sajnos</word>\n<word>se</word>\n<word>sem</word>\n<word>semmi</word>\n<word>senki</word>\n<word>sok</word>\n<word>sokat</word>\n<word>sokkal</word>\n<word>során</word>\n<word>sőt</word>\n<word>számára</word>\n<word>szemben</word>\n<word>szépen</word>\n<word>szeretnék</word>\n<word>szeretném</word>\n<word>szeretnénk</word>\n<word>szerint</word>\n<word>szét</word>\n<word>szinte</word>\n<word>szintén</word>\n<word>szükséges</word>\n<word>t</word>\n<word>talán</word>\n<word>taps</word>\n<word>te</word>\n<word>tehát</word>\n<word>tekintettel</word>\n<word>teljes</word>\n<word>tényleg</word>\n<word>természetesen</word>\n<word>ti</word>\n<word>tisztelt</word>\n<word>tovább</word>\n<word>továbbá</word>\n<word>további</word>\n<word>több</word>\n<word>túl</word>\n<word>tűnik</word>\n<word>úgy</word>\n<word>ugyan</word>\n<word>ugyanakkor</word>\n<word>ugyancsak</word>\n<word>ugyanis</word>\n<word>új</word>\n<word>újabb</word>\n<word>újra</word>\n<word>után</word>\n<word>utána</word>\n<word>utolsó</word>\n<word>ügy</word>\n<word>vagy</word>\n<word>vagyis</word>\n<word>vagyok</word>\n<word>vagyunk</word>\n<word>vajon</word>\n<word>valaki</word>\n<word>valamennyi</word>\n<word>valami</word>\n<word>valamilyen</word>\n<word>valamint</word>\n<word>való</word>\n<word>valóban</word>\n<word>van</word>\n<word>vannak</word>\n<word>végre</word>\n<word>végül</word>\n<word>vele</word>\n<word>viszont</word>\n<word>vissza</word>\n<word>volna</word>\n<word>volt</word>\n<word>voltak</word>\n<word>voltam</word></stopper>"
FIELD="\n<field>\n   <name>date</name>\n    <numeric>true</numeric>\n   <parserName>HunDateFieldAnnotator</parserName>\n</field>\n<field>\n<name>weight</name><numeric>true</numeric>\n<parserName>UnitFieldAnnotator</parserName>\n</field>\n<field>\n<name>deviza</name><numeric>true</numeric>\n<parserName>UnitFieldAnnotator</parserName>\n</field>\n<field>\n<name>length</name><numeric>true</numeric>\n<parserName>UnitFieldAnnotator</parserName>\n</field>\n"
POST="</parameters>\n"

for i in ./ogy/annotated/sep/* ; do
    echo -e $PRE $CORPUS1$i$CORPUS2 $MEMORY $INDEXPRE$STOPPEDSTEMMED$INDEX$INDEXPOS $STEMMER $SW$FIELD $POST > 1.xml	
    echo -e $PRE $CORPUS1$i$CORPUS2 $MEMORY $INDEXPRE$STOPPED$INDEX$INDEXPOS $SW$FIELD $POST > 2.xml					
    echo -e $PRE $CORPUS1$i$CORPUS2 $MEMORY $INDEXPRE$STEMMED$INDEX$INDEXPOS $STEMMER$FIELD $POST > 3.xml			
    echo -e $PRE $CORPUS1$i$CORPUS2 $MEMORY $INDEXPRE$PLAIN$INDEX$INDEXPOS$FIELD $POST >4.xml					

    echo "Processing "$i
    ../indri/buildindex/buildindex 4.xml
    ../indri/buildindex/buildindex 3.xml
    ../indri/buildindex/buildindex 2.xml
    ../indri/buildindex/buildindex 1.xml
    
    du $PLAIN$INDEX     
    du $STEMMED$INDEX 
    du $STOPPED$INDEX 
    du $STOPPEDSTEMMED$INDEX 
done;



