#!/bin/bash
latex tcs_solid_proposal;
bibtex tcs_solid_proposal;
latex tcs_solid_proposal;
latex tcs_solid_proposal;
dvipdf tcs_solid_proposal.dvi tcs_solid_proposal.pdf
rm tcs_tex.tar
tar cf tcs_tex.tar *.tex *.bib
chmod g+w *
