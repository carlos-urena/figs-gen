.SUFFIXES:
##.SECONDARY:
.PHONY: x0, test

cc_opts=-std=c++11 -Wfatal-errors -I$(src)
pdfs=../pdfs
pdftopng=pdftoppm -png -r 500 

v9: fig09-persp2.png
	open $<

v8: fig08-persp1.png	
	open $<

v7: fig07-cuboid1.png	
	open $<

v6: fig06-frustum2.png
	open $<

v5: fig05-frustum1.png	
	open $<

v4: fig04-rot3d.png
	open $<

v3: fig03-perp3d.png
	open $<

v2: fig02-rot2d.png
	open $<

v1: fig01-perp2d.png
	open $<

v0: fig00-test.png
	open $<

all: fig01-perp2d.png fig02-rot2d.png fig03-perp3d.png fig04-rot3d.png fig05-frustum1.png\
     fig06-frustum2.png fig07-cuboid1.png fig08-persp1.png fig09-persp2.png
	open *.png

fig%.png: $(pdfs)/fig%.pdf makefile
	cd $(pdfs) ; make $(basename $@).pdf
	rm -rf tmp*.png
	$(pdftopng) $<  tmp
	mv tmp-1.png $@


clean:
	rm -rf tmp*.png fig*.png
