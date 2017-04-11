//#pragma once

#include "joueur_simple.hpp"
//#include "joueur_simple.hpp";
//#include "joueur_simple.hpp";
//#include "joueur_simple.hpp";

struct JoueurContainer {
	int type; //definie le type de joueurs stocké.
	JoueurSimple js;
	JoueurOrganise jo;
	//JoueurOpportuniste jp;
	JoueurUtilisateur ju;
};