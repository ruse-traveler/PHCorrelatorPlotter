#!/usr/bin/env ruby
# =============================================================================
# @file   RunPHCorrelatorPlotter.rb
# @author Derek Anderson
# @data   02.10.2025
#
# Short script to run the driver macro for plotting,
# RunPHCorrelatorPlotter.C
# =============================================================================

# set which plots to generate
plots = [0, 1, 2, 3]

# run macro for each option
plots.each { |plot|
  system("root -b -q \"RunPHCorrelatorPlotter.C++(#{plot})\"")
}

# clean up
exec("./scripts/clean")

# end =========================================================================
