#include <getopt.h>
#include "multiplier.h"

int main(){
	

/*
 * -n NUM	définit le nombre de calculs parallèles utilisés (défaut = 2).
 *  -o OUTPUT_FILE	spécifie le fichier de sortie dans lequel le résultat du produit doit être enregistré, si cet argument n’est pas définit, affiche à la sortie standard
 *  INPUT_FILE	le fichier d’entrée qui défini une liste ordonnée de matrices
 */	
multiplier_start(4, "testing/test_files/gen.txt", "output");                                     
	return 0;
}
