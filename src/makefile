.SUFFIXES:
##.SECONDARY:
.PHONY: x0, test

cc_opts=-std=c++11 -Wfatal-errors -I.
latex_opts=-shell-escape -interaction nonstopmode --halt-on-error -file-line-error  --jobname borrar


v1: fig01-rot2d.pdf
	open -a skim $<

v0: fig00-test.pdf
	open -a skim $<

fig%.pdf: fig%.tex
	rm -rf borrar.*
	pdflatex $(latex_opts) $<
	mv borrar.pdf $@
	rm -rf borrar.*

fig%.tex : fig%_exe makefile
	cat header.tex >$@
	./$< >> $@
	cat footer.tex >>$@

fig%_exe : fig%.cpp vec_mat.h makefile
	g++ $(cc_opts) -o $@  $<


clean:
	rm -rf *_exe fig*.tex fig*.pdf borrar.*
