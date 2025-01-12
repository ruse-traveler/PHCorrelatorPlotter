#!/bin/bash
# =============================================================================
# @file   RunPHCorrelatorPlotter.sh
# @author Derek Anderson
# @date   01.02.2025
#
# Short script to run the driver macro for plotting,
# RunPHCorrelatorPlotter.sh
# =============================================================================

root -b -q "RunPHCorrelatorPlotter.C++(0)"
root -b -q "RunPHCorrelatorPlotter.C++(1)"
root -b -q "RunPHCorrelatorPlotter.C++(2)"

# end =========================================================================
