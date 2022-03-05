#	NetHack Makefile.
#	SCCS Id: @(#)Makefile.dat	3.4	1992/09/18

# for Atari
# SHELL=E:/GEMINI2/MUPFEL.TTP
# UUDECODE=uudecode

VARDAT = data rumors quest.dat oracles options

all:	$(VARDAT) spec_levs quest_levs dungeon

../util/makedefs.js:
	(cd ../util ; make makedefs.js)

../util/dgn_comp.js:
	(cd ../util ; make dgn_comp.js)

../util/lev_comp.js:
	(cd ../util ; make lev_comp.js)

../util/tile2x11:
	(cd ../util ; make tile2x11)

../util/tile2beos:
	(cd ../util ; make tile2beos)

../util/tile2bmp:
	(cd ../util ; make tile2bmp)

x11tiles: ../util/tile2x11 ../win/share/monsters.txt ../win/share/objects.txt \
				../win/share/other.txt
	../util/tile2x11 ../win/share/monsters.txt ../win/share/objects.txt \
				../win/share/other.txt

beostiles: ../util/tile2beos ../win/share/monsters.txt ../win/share/objects.txt \
				../win/share/other.txt
	../util/tile2beos ../win/share/monsters.txt ../win/share/objects.txt \
				../win/share/other.txt

nhtiles.bmp: ../util/tile2bmp ../win/share/monsters.txt ../win/share/objects.txt \
				../win/share/other.txt
	../util/tile2bmp $@

NetHack.ad: ../win/X11/NetHack.ad
	cp ../win/X11/NetHack.ad NetHack.ad

pet_mark.xbm: ../win/X11/pet_mark.xbm
	cp ../win/X11/pet_mark.xbm pet_mark.xbm

rip.xpm: ../win/X11/rip.xpm
	cp ../win/X11/rip.xpm rip.xpm

mapbg.xpm: ../win/gnome/mapbg.xpm
	cp ../win/gnome/mapbg.xpm mapbg.xpm

nhsplash.xpm: ../win/Qt/nhsplash.xpm
	cp ../win/Qt/nhsplash.xpm nhsplash.xpm

nethack.icns: ../win/Qt/nhicns.uu
	$(UUDECODE) ../win/Qt/nhicns.uu

Info.plist: ../win/Qt/Info.pli
	cp ../win/Qt/Info.pli Info.plist

../util/tile2img.ttp:
	(cd ../util ; make tile2img.ttp)

../util/xpm2img.ttp:
	(cd ../util ; make xpm2img.ttp)
nh16.img: ../util/tile2img.ttp ../win/share/monsters.txt \
				../win/share/objects.txt ../win/share/other.txt
	../util/tile2img.ttp nh16.img

rip.img: ../util/xpm2img.ttp
	../util/xpm2img.ttp ../win/X11/rip.xpm rip.img
title.img:
	# cp ../win/gem/title.img title.img
	$(UUDECODE) ../win/gem/title.uu

GEM_RSC.RSC:
	# cp ../win/gem/GEM_RSC.RSC GEM_RSC.RSC
	$(UUDECODE) ../win/gem/gem_rsc.uu


data:	data.base ../util/makedefs.js
	node ../util/makedefs.js -d

rumors:	rumors.tru rumors.fal ../util/makedefs.js
	node ../util/makedefs.js -r

quest.dat:	quest.txt ../util/makedefs.js
	node ../util/makedefs.js -q

oracles:	oracles.txt ../util/makedefs.js
	node ../util/makedefs.js -h

# note: 'options' should have already been made when include/date.h was created
options:	../util/makedefs.js
	node ../util/makedefs.js -v


spec_levs: ../util/lev_comp.js \
	bigroom.des castle.des endgame.des gehennom.des knox.des medusa.des \
	mines.des oracle.des sokoban.des tower.des yendor.des
	node ../util/lev_comp.js bigroom.des
	node ../util/lev_comp.js castle.des
	node ../util/lev_comp.js endgame.des
	node ../util/lev_comp.js gehennom.des
	node ../util/lev_comp.js knox.des
	node ../util/lev_comp.js medusa.des
	node ../util/lev_comp.js mines.des
	node ../util/lev_comp.js oracle.des
	node ../util/lev_comp.js sokoban.des
	node ../util/lev_comp.js tower.des
	node ../util/lev_comp.js yendor.des
	touch spec_levs

quest_levs: ../util/lev_comp.js \
	Arch.des Barb.des Caveman.des Healer.des Knight.des Monk.des \
	Priest.des Ranger.des Rogue.des Samurai.des Tourist.des Valkyrie.des \
	Wizard.des
	node ../util/lev_comp.js Arch.des
	node ../util/lev_comp.js Barb.des
	node ../util/lev_comp.js Caveman.des
	node ../util/lev_comp.js Healer.des
	node ../util/lev_comp.js Knight.des
	node ../util/lev_comp.js Monk.des
	node ../util/lev_comp.js Priest.des
	node ../util/lev_comp.js Ranger.des
	node ../util/lev_comp.js Rogue.des
	node ../util/lev_comp.js Samurai.des
	node ../util/lev_comp.js Tourist.des
	node ../util/lev_comp.js Valkyrie.des
	node ../util/lev_comp.js Wizard.des
	touch quest_levs

dungeon: dungeon.def ../util/makedefs.js ../util/dgn_comp.js
	node ../util/makedefs.js -e
	node ../util/dgn_comp.js dungeon.pdf

spotless:
	-rm -f spec_levs quest_levs *.lev $(VARDAT) dungeon dungeon.pdf
	-rm -f nhdat x11tiles beostiles pet_mark.xbm rip.xpm mapbg.xpm
	-rm -f rip.img GEM_RSC.RSC title.img nh16.img NetHack.ad
