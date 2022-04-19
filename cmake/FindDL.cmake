#############################################################################
#
# ViSP, open source Visual Servoing Platform software.
# Copyright (C) 2005 - 2019 by Inria. All rights reserved.
#
# This software is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# See the file LICENSE.txt at the root directory of this source
# distribution for additional information about the GNU GPL.
#
# For using ViSP with software that can not be combined with the GNU
# GPL, please contact Inria about acquiring a ViSP Professional
# Edition License.
#
# See http://visp.inria.fr for more information.
#
# This software was developed at:
# Inria Rennes - Bretagne Atlantique
# Campus Universitaire de Beaulieu
# 35042 Rennes Cedex
# France
#
# If you have questions regarding the use of this file, please contact
# Inria at visp@inria.fr
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# Description:
# Try to find dl library.
# Once run this will define: 
#
# DL_FOUND
# DL_LIBRARIES
#
# Authors:
# Fabien Spindler
#
#############################################################################


FIND_LIBRARY(DL_LIBRARY
    NAMES dl
    PATHS 
    $ENV{DL_HOME}/lib
    /usr/lib
    /usr/local/lib
    )
  
#MESSAGE("DBG DL_LIBRARY=${DL_LIBRARY}")
  
IF(DL_LIBRARY)
    SET(DL_LIBRARIES ${DL_LIBRARY})
    SET(DL_FOUND TRUE)
ELSE()
    SET(DL_FOUND FALSE)
ENDIF()
  
MARK_AS_ADVANCED(
    DL_LIBRARY
    )

