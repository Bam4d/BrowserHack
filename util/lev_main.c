/*	SCCS Id: @(#)lev_main.c	3.4	2002/03/27	*/
/*	Copyright (c) 1989 by Jean-Christophe Collet */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * This file contains the main function for the parser
 * and some useful functions needed by yacc
 */
#define SPEC_LEV	/* for MPW */
/* although, why don't we move those special defines here.. and in dgn_main? */

#include "hack.h"
#include "date.h"
#include "sp_lev.h"
#ifdef STRICT_REF_DEF
#include "tcap.h"
#endif

#ifdef MAC
# if defined(__SC__) || defined(__MRC__)
#  define MPWTOOL
#  define PREFIX ":dungeon:"	/* place output files here */
#  include <CursorCtl.h>
# else
#  if !defined(__MACH__)
#   define PREFIX ":lib:"	/* place output files here */
#  endif
# endif
#endif

#ifdef WIN_CE
#define PREFIX "\\nethack\\dat\\"
#endif

#ifndef MPWTOOL
# define SpinCursor(x)
#endif

#if defined(AMIGA) && defined(DLB)
# define PREFIX "NH:slib/"
#endif

#ifndef O_WRONLY
#include <fcntl.h>
#endif
#ifndef O_CREAT	/* some older BSD systems do not define O_CREAT in <fcntl.h> */
#include <sys/file.h>
#endif
#ifndef O_BINARY	/* used for micros, no-op for others */
# define O_BINARY 0
#endif

#if defined(MICRO) || defined(WIN32)
# define OMASK FCMASK
#else
# define OMASK 0644
#endif

#define ERR		(-1)

#define NewTab(type, size)	(type **) alloc(sizeof(type *) * size)
#define Free(ptr)		if(ptr) free((genericptr_t) (ptr))
#define Write(fd, item, size)	if (write(fd, (genericptr_t)(item), size) != size) return FALSE;

#if defined(__BORLANDC__) && !defined(_WIN32)
extern unsigned _stklen = STKSIZ;
#endif
#define MAX_ERRORS	25

extern int  NDECL (yyparse);
extern void FDECL (init_yyin, (FILE *));
extern void FDECL (init_yyout, (FILE *));

extern void NDECL(monst_init);
extern void NDECL(objects_init);
extern void NDECL(decl_init);

extern void NDECL(init_obj_classes);

extern int line_number;

const char *fname = "(stdin)";
int fatal_error = 0;
int want_warnings = 0;

int
main(argc, argv)
int argc;
char **argv;
{
	FILE *fin;
	int i;
	boolean errors_encountered = FALSE;
#if defined(MAC) && (defined(THINK_C) || defined(__MWERKS__))
	static char *mac_argv[] = {	"lev_comp",	/* dummy argv[0] */
				":dat:Arch.des",
				":dat:Barb.des",
				":dat:Caveman.des",
				":dat:Healer.des",
				":dat:Knight.des",
				":dat:Monk.des",
				":dat:Priest.des",
				":dat:Ranger.des",
				":dat:Rogue.des",
				":dat:Samurai.des",
				":dat:Tourist.des",
				":dat:Valkyrie.des",
				":dat:Wizard.des",
				":dat:bigroom.des",
				":dat:castle.des",
				":dat:endgame.des",
				":dat:gehennom.des",
				":dat:knox.des",
				":dat:medusa.des",
				":dat:mines.des",
				":dat:oracle.des",
				":dat:sokoban.des",
				":dat:tower.des",
				":dat:yendor.des"
				};

	argc = SIZE(mac_argv);
	argv = mac_argv;
#endif
	/* Note:  these initializers don't do anything except guarantee that
		we're linked properly.
	*/
	monst_init();
	objects_init();
	decl_init();
	/* this one does something... */
	init_obj_classes();

	init_yyout(stdout);
	if (argc == 1) {		/* Read standard input */
	    init_yyin(stdin);
	    (void) yyparse();
	    if (fatal_error > 0) {
		    errors_encountered = TRUE;
	    }
	} else {			/* Otherwise every argument is a filename */
	    for(i=1; i<argc; i++) {
		    fname = argv[i];
		    if(!strcmp(fname, "-w")) {
			want_warnings++;
			continue;
		    }
		    fin = freopen(fname, "r", stdin);
		    if (!fin) {
			(void) fprintf(stderr,"Can't open \"%s\" for input.\n",
						fname);
			perror(fname);
			errors_encountered = TRUE;
		    } else {
			init_yyin(fin);
			(void) yyparse();
			line_number = 1;
			if (fatal_error > 0) {
				errors_encountered = TRUE;
				fatal_error = 0;
			}
		    }
	    }
	}
	exit(errors_encountered ? EXIT_FAILURE : EXIT_SUCCESS);
	/*NOTREACHED*/
	return 0;
}
