#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <elf.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	void* start = NULL;
	int i, fd;
	struct stat stat;
	char *strtab;
	int nb_symbols;

	// ouverture du fichier (pour être mappé)
	fd = open("./program", O_RDONLY, 660);
	if(fd < 0)
		perror("open");

	// récupération de la taille du fichier
	fstat(fd, &stat);

	//projection du fichier (MAP_SHARED importe peu ici)
	start = mmap(0, stat.st_size, PROT_READ , MAP_FILE | MAP_SHARED, fd, 0);
	if(start == MAP_FAILED)
	{
		perror("mmap");
		abort();
	}

	// le premier octet mappé est le premier octet du fichier ELF
	// Via un cast, on va pouvoir manipuler le fichier ELF mappé en mémoire
	Elf64_Ehdr* hdr = (Elf64_Ehdr *) start;
	Elf64_Sym* symtab;

	// Vérification du format ELF
	// Par exemple pour afficher le premier octet on cast
	// 'start' en pointeur d'octet (de char, ici). On peut ensuite l'afficher
	// en hexa (%x) ou en ASCII (%c).
	// Pour passer au prochain octet, on fait pointer 'start' sur
	// l'octet suivant: (start+1, on s'assure bien que 'start'
	// est un char* -- arithmétique de pointeurs).
	// Une fois déréférence, on obtient la valeur de l'octet
	printf("Check four first bytes: %x '%c' '%c' '%c'\n", *(char*)start,*((char*)start+1), *((char*)start+2), *((char*)start+3));


	// le header contient un champ donnant l'offset (en octet) où se trouve
	// les sections headers
	Elf64_Shdr* sections = (Elf64_Shdr *)((char *)start + hdr->e_shoff);

	// parcours des sections
	for (i = 0; i < hdr->e_shnum; i++)
	{
		// si la section courante est de type 'table de symbole'
		if (sections[i].sh_type == SHT_SYMTAB) {
			// on sauvegarde:
			// 1. le pointeur sur la table de symboles
			// 2. Le nombre de symboles dans cette table
			symtab = (Elf64_Sym *)((char *)start + sections[i].sh_offset);
			nb_symbols = sections[i].sh_size / sections[i].sh_entsize;

			// La table des strings peut se trouver dans la table
			// des sections (type SHT_STRTAB) mais attention !! Il 
			// existe plusieurs string tables (.strtab et .shstrtab par exemple)
			// il faut donc être sûr de récupérer la bonne.
			// Ici petite astuce, le Shdr dispose d'un champ (sh_link) qui pointe
			// vers une autre section header variant en fonction du contexte
			// Dans le cas d'un section header pour SYMTAB, le sh_link pointe vers
			// la table des strings (man elf).
			//
			// Facile donc de récupérer le pointeur sur le tableau :)
			strtab = (char*)((char*)start + sections[sections[i].sh_link].sh_offset);

		}
	}

	// on parcourt alors la table des symboles
	// pour chaque entrée, le champ st_name est un offset en octet depuis 
	// le début du tableau où se trouve le nom.
	for (i = 0; i < nb_symbols; ++i) {
		printf("%d: %s\n", i, strtab + symtab[i].st_name);
	}



	return 0;
}
