#Ana Stanciulescu 312CA 1.12.2023

#####Octave#####

Programul de mai jos reprezinta propria mea implementare a software-ului GNU Octave.

###Task 1 - Incarcarea in memorie a unei noi matrice

Atunci cand primesc de la tastatura comanda L, verific daca, adaugand o noua matrice,
depasesc bufsize (buffer size). Daca spatiul nu este suficient, intru in functia
double_size_coll. 
Dupa dublarea memoriei, intru in functia read_matrix,
care are ca parametri celula din colectia de matrice, celula liniilor si cea a coloanelor.
In read_array se citesc numarul de linii si coloane al noii matrice si verifc daca se poate face alocarea memoriei.
Dupa ce a fost alocata memoria cu succes, se citesc elementele din matrice.

Functia double_size_coll: se foloseste functia realloc pentru a dubla memoria. Acest lucru
se face intr-un pointer temporar, pentru a ne asigura ca memoria poate fi realocata, inainte de a
trece la pointerul original.

Functia read_matrix: in afara de zonele unde s-a folosit programarea defensiva, este o functie tipica de citire 
a unor matrice de pointeri.


###Task 2 - Determinarea dimensiunilor unei matrice

Pentru ca am creat in main doi vectori care retin numarul de linii si de coloane
pentru fiecare matrice salvata in colectie, functia dimensions_matrix doar afiseaza
ce se afla memorat in vectorii linii si coloane, la indexul cerut.
Daca indexul depaseste intervalul alocat colectiei, se afiseaza mesajul de eroare.


###Task 3 - Afisarea unei matrice

Functia print_matrix are ca parametri intreaga colectie de matrice, vectorul pentru linii si cel pentru coloane.
De aceea, ne folosim de valorile memorate in acestia pentru a accesa matricea cu indexul cerut
si de a afisa fiecare element din ea.
Daca indexul depaseste intervalul alocat colectiei, se afiseaza mesajul de eroare.


###Task 4 - Redimensionarea unei matrice

Dupa ce se citesc de la tastatura litera C si indexul cerut, se creeaza in functia resize_matrix un nou vector pentru 
liniile care urmeaza a fi pastrate (new_l) si un vector pentru noile coloane (new_c).
Acestia sunt alocati dinamic si se verifica daca alocarea a avut succes.
Se construieste o matrice auxiliara de pointeri, care se construieste respectand noile dimensiuni primite de la
tastatura. Elementele din aceasta matrice sunt luate din cea originala, tinandu-se mereu cont care sunt liniile si coloanele
care trebuie sa ramana. Formula pentru acest lucru este a[i][j] = a_ptr[idx][x][y]; unde a_ptr este colectia originala.
Dupa ce matricea auxiliara a fost complet construita, stergem matricea initiala si pointam spre aceasta 
noua matrice.
Astfel, redimensionarea s-a facut in place.


###Task 5 - Inmultirea a doua matrice

In acest program exista doua functii in care se inmultesc matrice.
Functia care se ocupa cu acest task este: matrix_prod_in_coll;
Dupa ce se verifica ca dimensiunile matricelor sunt corespunzatoare, se creeaza o matrice auxiliara, in care se memoreaza
rezultatul. Dimensiunile acestei matrice sunt date de liniile primei matrice si coloanele celei de-a doua.

Pe acelasi principiu functioneaza si functia matrix_prod. Diferenta principala dintre cele doua e ca,
in matrix_prod_in_coll, matricea auxiliara este adaugata pe ultima pozitie din colectie.
Acest lucru implica marimea numarului de matrice si verificarea daca memoria este suficienta dupa marire.
De aceea, sunt cazuri in care se apeleaza din nou functia double_size_collection.


###Task 6 - Sortarea matricelor

Sortarea matricelor se face in functia org_matrix.
In aceasta functie, se creeaza o matrice auxiliara (numita suma), care are doua linii:
	- prima linie: fiecare coloana are indexul corespunzator numarului matricei;
	- a doua linie: fiecare coloana are suma matricei de la indexul de pe prima linie.
Suma matricei de la fiecare index se calculeaza accesand matricea din colectie si parcurgand-o element cu element.
Dupa ce intreaga matrice auxiliara a fost construita, se apeleaza functia selection_sort.

In selection_sort se afla algoritmul tipic pentru o astfel de sortare, modificat doar la final.
Modificarea vizeaza faptul ca nu doar un vector trebuie sortat, ci 4 (totul este facut in functie de valoarea sumei de la fiecare index).
	- in primul swap: se sorteaza a doua linie a matricei suma;
	- in al doilea swap: este deplasat si indexul din prima linie, pentru a nu se pierde numarul matricei;
	- in al treilea swap: este deplasat si indexul corespunzator din vectorul de linii;
	- in al patrulea sawp: este deplasat si indexul corespunzator din vectorul de coloane;
Aceste modificari se fac pentru a nu pierde niciodata legatura dintre sume si matricele lor (de ex: daca s0 este cea mai mare sum,
ea trece pe ultima coloana; tot pe ultima coloana trebuie sa fie si linii0, coloane 0 si index0)

Dupa ce matricea suma este sortata, se creeaza un vector auxiliar (numit colectie). Folosind formula colectie[idx] = a_ptr[0][nr];
unde nr = suma[0][idx], se umple fiecare celula din vector cu adresa catre matricea retinuta pe prima linie a matricei suma.
(de ex: in colectia initiala, prima matrice este pe pozitia 0. Dupa sortarea dupa suma, prima matrice este pe ultima pozitie a liniei 0
din matricea suma. Astfel, in noua colectie, in ultima coloana trebuie sa fie adresa catre matricea 0)
Dupa ce tot vectorul nou colectie este construit respectand indecsii de pe linia 0, se elibereaza vechea colectie si se pointeaza catre cea noua.


###Task 7 - Transpunerea unei matrice

Functia transp_matrix primeste ca parametri matricea de la indexul cerut si adresele vectorilor linii si coloane.
In niste variabile locale, se realizeaza conversia liniilor in coloane si invers.
Se creeaza o matrice auxiliara, care se construieste dupa formula a[i][j] = a_ptr[idx][j][i].
Se elibereaza memoria vechei matrice si se pointeaza catre aceasta noua matrice, proaspat transpusa.


###Task 8 - Ridicarea unei matrice la o putere in timp logaritmic

Pentru a face acest lucru se apeleaza 3 functii:
	- IN: in ea se creeaza matricea identitate; functia e de tip int**;
	- matrix_prod: este functia mentionata anterior; inmulteste doua matrice si retine rezultatul intr-o matrice auxiliara;
	- exp_matrix: functia in care se realizeaza propriu-zis ridicarea la putere;
In exp_matrix este creata o matrice auxiliara apeland functia IN. Se intra intr-o bucla while si se verifica constant paritatea puterii.
Daca este impara, se apeleaza matrix_prod, pentru a modifica valoarea matricei auxiliare. Astfel, matricea aux ia valoarea matricei initiale.
Daca este para, se apeleaza matrix_prod si se inmulteste matricea initiala cu ea insasi, produsul fiind stocat tot in colectie. se repeta pana se ajunge la putere = 1.
Odata iesit din while, se mai face o data matrix_prod. Daca puterea era initial impara, se inmulteste matricea initiala cu ce se afla
actual in colectie si rezultatul se adauga in colectie.
Daca puterea era initial para, chiar si apeland functia matrix_prod nu apare nicio diferenta, pentru ca aux este matricea identitate.
Se elibereaza matricea auxiliara.


###Task 9 - Eliminarea unei matrice din memorie

Functia remove_matrix primeste adresa catre colectia de matrice, indexul cerut, numarul total de matrice si bufsize-ul.
Se elibereaza toate resursele matricei de la indexul cerut, inclusiv adresa din colectia de matrice. 
Se face un for incepand de la index si toate adresele din colectie se muta o pozitie in stanga.
Se micsoreaza cu o unitate numarul total al matricelor si se verifica cata memorie se ocupa din bufsize.
Daca este ocupata doar o jumatate din memorie, se apeleaza functia half_size_coll.

Half_size_coll functioneaza la fel ca si double_size_coll, singura diferenta fiind faptul ca bufsize nu se dubleaza, ci se injumatateste.
Nu se verifica paritatea bufsize-ului, deoarece aceste este mereu par.


###Task 10 - Oprirea programului si dealocarea tuturor resurselor

Functia endgame intra in colectie si elibereaza resursele din fiecare matrice.
Dupa ce a terminat toate matricele, elibereaza colectia in sine, vectorul de linii si de coloane.
Cand se intoarce inapoi in main, programul intalneste break; si iese din marea bucla while, astfel oprind programul.
   

###Main:
	- este alocata memoria pentru colectia de matrice si vectorii linii si coloane.
	- bufsize are initial valoarea 2, pentru a nu folosi memorie degeaba.
	- se deschide o bucla infinita while, in care se citesc toate comenzile.
	- se iese din aceasta bucla doar dupa ce a fost citit Q de la tastatura.
