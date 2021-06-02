.SUFFIXES:
##.SECONDARY:
.PHONY: x0, test

cc_opts=-std=c++11 -Wfatal-errors -I.
latex_opts=-shell-escape -interaction nonstopmode --halt-on-error -file-line-error  --jobname borrar


v6: fig06-cuboid1.pdf	
	open -a skim $<

v5: fig05-frustum1.pdf	
	open -a skim $<

v4: fig04-rot3d.pdf
	open -a skim $<

v3: fig03-perp3d.pdf
	open -a skim $<

v2: fig02-rot2d.pdf
	open -a skim $<

v1: fig01-perp2d.pdf
	open -a skim $<

v0: fig00-test.pdf
	open -a skim $<

all: fig01-perp2d.pdf fig02-rot2d.pdf fig03-perp3d.pdf fig04-rot3d.pdf
	open -a skim *.pdf

fig%.pdf: fig%.tex header.tex footer.tex
	rm -rf borrar.*
	pdflatex $(latex_opts) $<
	mv borrar.pdf $@
	rm -rf borrar.*

fig%.tex : fig%_exe makefile
	./$< > $@
	
fig%_exe : fig%.cpp vec_mat.h utils.h makefile
	g++ $(cc_opts) -o $@  $<


clean:
	rm -rf *_exe fig*.tex fig*.pdf borrar.*
