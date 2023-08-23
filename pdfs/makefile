.SUFFIXES:
##.SECONDARY:
.PHONY: x0, test

cc_opts=-std=c++11 -Wfatal-errors -I$(src)
src=../src
latex_opts=-shell-escape -interaction nonstopmode  --halt-on-error -file-line-error  --jobname borrar
##verpdf="open -a skim"
verpdf="open"


v15: fig15-refl.pdf	
	$(verpdf) $<

v14: fig14-matriz-vista-2.pdf	
	$(verpdf) $<

v13: fig13-matriz-vista-1.pdf	
	$(verpdf) $<

v12: fig12-cubo-arbitr.pdf	
	$(verpdf) $<

v11: fig11-cubo-lado-2.pdf	
	$(verpdf) $<

v10: fig10-ndc-dc.pdf	
	$(verpdf) $<

v9: fig09-persp2.pdf	
	$(verpdf) $<

v8: fig08-persp1.pdf	
	$(verpdf) $<

v7: fig07-cuboid1.pdf	
	$(verpdf) $<

v6: fig06-frustum2.pdf	
	$(verpdf) $<

v5: fig05-frustum1.pdf	
	$(verpdf) $<

v4: fig04-rot3d.pdf
	$(verpdf) $<

v3: fig03-perp3d.pdf
	$(verpdf) $<

v2: fig02-rot2d.pdf
	$(verpdf) $<

v1: fig01-perp2d.pdf
	$(verpdf) $<

v0: fig00-test.pdf
	$(verpdf) $<

all: fig01-perp2d.pdf fig02-rot2d.pdf fig03-perp3d.pdf fig04-rot3d.pdf fig05-frustum1.pdf \
     fig06-frustum2.pdf fig07-cuboid1.pdf fig08-persp1.pdf fig09-persp2.pdf fig10-ndc-dc.pdf \
	 fig11-cubo-lado-2.pdf	fig12-cubo-arbitr.pdf  fig13-matriz-vista-1.pdf fig14-matriz-vista-2.pdf \
	 fig15-refl.pdf
	$(verpdf) *.pdf

fig%.pdf: fig%.tex $(src)/header.tex $(src)/footer.tex
	rm -rf borrar.*
	pdflatex $(latex_opts) $<
	mv borrar.pdf $@
	rm -rf borrar.*

fig%.tex : fig%_exe makefile
	./$< > $@
	
fig%_exe : $(src)/fig%.cpp $(src)/vec_mat.h $(src)/utils.h makefile
	g++ $(cc_opts) -o $@  $<


clean:
	rm -rf *_exe fig*.tex fig*.pdf borrar.*
